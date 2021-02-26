# Table of contents

<!-- TOC depthFrom:1 orderedList:true -->
1. [Introduction](#introduction)
2. [Example details](#example-details)
3. [Preconditions](#preconditions)
4. [Project compiling in Eclipse](#project-compiling-in-eclipse)
5. [PLCnext Engineer project](#plcnext-engineer-project)
6. [Project Execution](#project-execution)
7. [FileStream Operations ](#filestream-operations)
8. [Exception Handling](#exceptions)
9. [General Notes](#general-notes)
<!-- /TOC -->

# Introduction

This Example shows how to use a FileStream to check the binary generation timestamp whenever a Component is reinitialized.

## Example details

|Description | Value |
|------------ |-----------|
|Controller| AXC F 2152 |
|FW | 2021.0 LTS or later |
|SDK | 2021.0 LTS or later |
|PLCnext Engineer| 2021.0 LTS or later |

## Preconditions

- AXC F 2152 controller with firmware 2021.0 LTS or later
- Eclipse IDE "2020.9" or later
- PLCnext Engineer 2021.0 LTS or later

## Project compiling in Eclipse

1. In Eclipse, create the project "FileStreamExample" with Component "FileStreamExampleComponent" and Program "FileStreamExampleProgram".
1. In the project, replace the files "FileStreamExampleComponent.cpp", "FileStreamExampleComponent.hpp", "FileStreamExampleProgram.cpp", and "FileStreamExampleProgram.hpp" with the according files from this repository. Alternatively, you can create your own project with component and programs and include the source code in your application.
1. Compile the Eclipse project.
1. After successfull project compilation, the PLCnext Engineer library will be created automatically. You can find it in your Eclipse workspace folder, e.g.: "workspace\FileStreamExample\bin\FileStreamExample.pcwlx"

## PLCnext Engineer project

1. In PLCnext Engineer, create a new project and include the "FileStreamExample.pcwlx" in the project.
1. Instantiate the "FileStreamExampleProgram" under a previously defined task.
1. Download the PLCnext Engineer project to the PLCnext Control.

## Project Execution
During the Setup of the PLCnext Runtime our PLM component is loaded and the Initialize, LoadConfig , etc. are executed.
This application writes a at compiletime generated localtime string [__TIMESTAMP__](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html) into a file.
This way, whenever the PLC Starts it will first load the last generated file, compare it to the Timestamp of the current binary and then overwrite the Binary.

1. Component::LoadConfig 
    1. `ReadFromFile`        
    1.  On success reads the creationtime from file and compares it to the creationtime of the currently used binary.
1. Component::SetupConfig 
    1. `WriteToFile` executes        
    1. On success localtime of currently used binary is written to file overwriting its contents.
1. Component::ResetConfig (called at system shutdown or during `PLC::Start` after `PLC::Stop`)
    1. If the Inport `bReset`  is set true `DeleteFile` is executed at the next Shutdown / Stop-Start.


### Example output

Here is some example output this Component will create if you download some changes to the running PLC.
```bash
24.02.21 14:40:47.921 FileStreamExample.FileStreamExampleComponent                 INFO  - ---Initialize - Compile on Wed Feb 24 14:14:21 2021
24.02.21 14:40:47.923 FileStreamExample.FileStreamExampleComponent                 INFO  - ---LoadConfig
24.02.21 14:40:47.924 FileStreamExample.FileStreamExampleComponent                 INFO  - --- Read from file: Wed Feb 24 14:28:59 2021
24.02.21 14:40:47.926 FileStreamExample.FileStreamExampleComponent                 INFO  - Last Date: Wed Feb 24 14:28:59 2021
24.02.21 14:40:47.927 FileStreamExample.FileStreamExampleComponent                 INFO  - Current Date: Wed Feb 24 14:14:21 2021
24.02.21 14:40:47.929 FileStreamExample.FileStreamExampleComponent                 WARN  - --- New Binary has been loaded!
24.02.21 14:40:47.932 FileStreamExample.FileStreamExampleComponent                 INFO  - --- SetupConfig
24.02.21 14:40:47.935 FileStreamExample.FileStreamExampleComponent                 INFO  - --- File:logs/TestFile.txt of Length:24 created
```

### FileStream Operations
#### FileStream::Write
```cpp
void FileStreamExampleComponent::WriteToFile(String textToWrite) {
	try {
		// Create a FileStream that force creates a file.
		Arp::System::Commons::Io::FileStream stream(filePath,
				Arp::System::Commons::Io::FileMode::Create);

		// String
		Arp::String str = textToWrite;
		try {
			// Write String
			if (stream.CanWrite())
				stream.Write((byte*) str.CStr(), str.Length(), 0, str.Length());
		} catch (const Arp::Exception &e) {
			log.Error("--- Cannot Write to File. Error message: {0}.",
					e.GetMessage());
		}

		//Get File Length
		size_t filelen = stream.GetLength();
		log.Info("--- File:{0} of Length:{1} created", filePath, filelen);

		stream.Close();
	} catch (const Arp::Exception &e) {
		log.Error("--- Cannot Create File:{0}", e.GetMessage());
	}
}
```

#### FileStream::Read
```cpp
String FileStreamExampleComponent::ReadFromFile() {
	try {
		Arp::System::Commons::Io::FileStream stream(filePath,
				Arp::System::Commons::Io::FileMode::Open);

		//init string
		String str((String::size_type) stream.GetLength(),
				(String::CharType) '0');
		try {
			// Read String
			if (stream.CanRead()) {
				stream.Read((byte*) str.CStr(), stream.GetLength(), 0,
						stream.GetLength());
				log.Info("--- Read from file: " + str);
			}
		}
		//Here you could catch all exceptions separately
		catch (const Arp::Exception &e) {

			log.Error("--- Cannot read: {0}.", e.GetMessage());
			str = e.GetMessage();
		}
		stream.Close();
		return str;
	} catch (Arp::System::Commons::Io::NotExistException &e) {
		// Example of catching InvalidPathException
		log.Error("--- File does not exist. Message: {0}.", e.GetMessage());
		return e.GetMessage();
	} catch (const Arp::Exception &e) {
		log.Error("--- Cannot Open File. Error message: {0}.", e.GetMessage());
		return e.GetMessage();
	}
}
```
### Exceptions
There are a lot of exceptions that you should handle when working with files.
There are [Function Specific Exceptions](https://api.plcnext.help/api_docs_2021-0-LTS/classArp_1_1System_1_1Commons_1_1Io_1_1FileStream.html) like a `NotExistException` that might indicate that something went wrong during the last shutdown.

But also common exceptions like [Commons::Io::](https://api.plcnext.help/api_docs_2021-0-LTS/namespaceArp_1_1System_1_1Commons_1_1Io.html)`OutOfSpaceException`s. These might indicated that the whole application should better stop. 

### General Notes
File or IO activities can take quite a long time and might inhibit your RealTime operation.
That is why it is generally recommended to move all file operaitons you need into [threads](../ThreadExample/README.md).