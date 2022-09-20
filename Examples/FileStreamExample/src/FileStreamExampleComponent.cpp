#include "FileStreamExampleComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "FileStreamExampleLibrary.hpp"

#include "Arp/System/Commons/Io/FileStream.hpp"
#include "Arp/System/Commons/Io/File.hpp"
#include "Arp/System/Commons/Exceptions/Exceptions.h"


namespace FileStreamExample {

FileStreamExampleComponent::FileStreamExampleComponent(IApplication &application, const String &name) :
    ComponentBase(application,::FileStreamExample::FileStreamExampleLibrary::GetInstance(), name, ComponentCategory::Custom),
    programProvider(*this),
    ProgramComponentBase(::FileStreamExample::FileStreamExampleLibrary::GetInstance().GetNamespace(), programProvider) {
    log.Info("---Constructor:{0}",GetFullName());
}

void FileStreamExampleComponent::Initialize() {
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
    log.Info("---Initialize - Compile on {0}", __TIMESTAMP__);
}

void FileStreamExampleComponent::LoadConfig() {

    // load project config here
    log.Info("---LoadConfig");

    String out{__TIMESTAMP__};
    String in = ReadFromFile();

    log.Info("Last Date: {0} ", in);
    log.Info("Current Date: {0}", out);

    if (in != out &&  in != "Error"){
        newbin = true;
        // Keep in mind that this does not mean that the component has been reconstructed.
        log.Warning("--- New Binary has been loaded!");
    }
}

void FileStreamExampleComponent::SetupConfig() {
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
    log.Info("--- SetupConfig");
    if (newbin||nofile) WriteToFile (__TIMESTAMP__);

}

void FileStreamExampleComponent::ResetConfig() {
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
    log.Info("---ResetConfig");
    if (bReset) {
        log.Info("--- Delete File {0}", filePath);
        try {
            if (Io::File::Exists(filePath))
            {
                Io::File::Delete(filePath);
            }

        } catch (const Arp::Exception &e) {
            log.Error("--- Cannot Delete File. Error message: {0}.",
                    e.GetMessage());
        }
    }
}
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
            stream.Write((Arp::byte*) str.CStr(), str.Length(), 0, str.Length());
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
            stream.Read((Arp::byte*) str.CStr(), stream.GetLength(), 0, stream.GetLength());
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
        nofile = true;
        return  "Error";
    } catch (const Arp::Exception &e) {
        log.Error("--- Cannot Open File. Error message: {0}.", e.GetMessage());
        return "Error";
    }
}
} // end of namespace FileStreamExample
