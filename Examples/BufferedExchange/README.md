# Table of contents

<!-- TOC depthFrom:1 orderedList:true -->
1. [Introduction](#introduction)
2. [Example details](#example-details)
3. [Preconditions](#preconditions)
4. [Project compiling in Eclipse](#project-compiling-in-eclipse)
5. [PLCnext Engineer project](#plcnext-engineer-project)
6. [Application Description](#application-description)
7. [FileStream Operations ](#filestream-operations)
8. [Exception Handling](#exceptions)
9. [General Notes](#general-notes)
<!-- /TOC -->

# Introduction

This example shows how to transfere and process larger amounts of data from your C++ RealTime application without impacing the RealTime.

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

1. In Eclipse, create the project "BufferedExchange" with Component "BufferedExchangeComponent" and Program "BufferedExchangeProgram".
1. In the project, replace the files "BufferedExchangeComponent.cpp", "BufferedExchangeComponent.hpp", "BufferedExchangeProgram.cpp", and "BufferedExchangeProgram.hpp" with the according files from this repository. Alternatively, you can create your own project with component and programs and include the source code in your application.
1. Compile the Eclipse project.
1. After successfull project compilation, the PLCnext Engineer library will be created automatically. You can find it in your Eclipse workspace folder, e.g.: "workspace\BufferedExchange\bin\BufferedExchange.pcwlx"

## PLCnext Engineer project

1. In PLCnext Engineer, create a new project and include the "BufferedExchange.pcwlx" in the project.
1. Instantiate the "BufferedExchangeProgram" under a previously defined task.
1. Download the PLCnext Engineer project to the PLCnext Control.

## Application Description

In this Project we show how to publish data from a [RealTimeProgram](src/BufferedExchangeProgram.cpp) in a cyclic manner and storage them in the  [PLMComponent](src/BufferedExchangeComponent.hpp) for further processing. The processing happens inside a thread and by doing that we decouple this processing from the RealTime sceduling of the Program.

The class [MyWorker](src/MyWorker.hpp ) holds all the data and methods the Thread is interacting with.
It implenents methods for each Type of thread as well as an interface to recive data.

The data storage is realised by swaping two queues.
One `std::Queue` to recieve data and another `std::Queue` for processing.
Whenever data are added or beeing processed the Queues are locked up using a Mutex to aussure thread safety.
This process works fine in a single producer/single consumer environment.
As long as the time requirement or the forwarded data are not to large it will also work fine with multiple producers.

Watch out the `SetData()` function is curently implemented as blocking, it actively waits for the Mutex to be locked and this might infulence your RealTime. If you are producing more data then you can handle.
You can switch this Blocking behavior from `Mutex.Lock()` to `Mutex.TryLock()` and add a timeout loop if necessary.
e.g
```cpp
while(!Mutex.TryLock() && !timeout){}
```

```cpp
///BufferedExchangeComponent.hpp
MyWorker wD; // Thread execution environment
Thread delegateThread;
...
///BufferedExchangComponent.cpp
delegateThread(ThreadSettings("-DelegateThread", 20, 0, 0),	Arp::make_delegate(&wD, &BufferedExchange::MyWorker::Run))
```
This means that the `MyWorker::Run` method of the instance  `wD` is called.

Every Task Cycle the BufferedExchangeProgram::Exceute() method pushes data to the MyWorker instance `wD`.

```cpp
/// BufferedExchangeProgram.cpp
bufferedExchangeComponent.wD.SetData(count)
```
Every 1000 Cycles the Execute() method will print a hint that it is still running. If data can not be set a Warning is beeing written to the Output.log file.
When data are beeing stored we also store a timestamp that shows the passed time since the last data were added.
```cpp
data_storage.push(std::pair<double, int>( duration_cast<duration<double>>(time - last_time).count(), x));
```

The method `MyWorker::process()` is responsible for processing the collected data.
It prints the first and last element of a queue, this way we are able to compare the timestamps of the the critical area of swaping between `Queue::data_storage` and `queue::data_toproceess`. This timestamp should always approximatly show the TaskCycle of the RealTime sheduled Program.

### Example Output
This Example Output shows a ESM Task with a cycle time of 1 ms.
Because the Thread sleep time is set to 1000ms and the MAX_QUEUE_SIZE is set to 1000 elements this is an area where a slight jitter in the cycletime of the Thread (sleep(999)+ execution time of process()) can cause an OutOfMemory exception to occure.
```cpp
//"Endless loop" for normal thread
void Run(void *t)
{
    while (!this->Stop)
    {
        RunSingle();
        // Sleep for X ms until next RunSingle execution.
        Arp::Thread::Sleep(999);
    }
};
```
So if processing the stored data plus the sleep time results in more then 1000ms the storage might overflow.

It is important that you take these cases as well as external factors (another application might take all the free memory!) into consideration and handle them according to your application requirements.
It also is recomended to set fixed limits for your application storage size as this will make testing the boundaries much easier.
Also other users of your library will be able to determine how much resources your appliication requires at max. and set the dimension of their applicaiton.

```bash
27.03.18 17:36:15.417 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 0
27.03.18 17:36:15.433 root                                                         INFO  - -----------------DelegateThread Swap queue pointers data_store<<-->>data_toprocess
27.03.18 17:36:16.417 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 1000
27.03.18 17:36:16.434 root                                                         INFO  - ---------------- -DelegateThread firstElement: time:362614  data:1
27.03.18 17:36:16.435 root                                                         INFO  - -----------------DelegateThread lastElement time:0.00099717  data:17
27.03.18 17:36:16.435 root                                                         INFO  - -----------------DelegateThread Swap queue pointers data_store<<-->>data_toprocess
27.03.18 17:36:17.417 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 2000
27.03.18 17:36:17.435 root                                                         INFO  - ---------------- -DelegateThread firstElement: time:0.0012245  data:18
27.03.18 17:36:17.436 root                                                         INFO  - -----------------DelegateThread lastElement time:0.00102634  data:1018
27.03.18 17:36:17.436 root                                                         INFO  - -----------------DelegateThread Swap queue pointers data_store<<-->>data_toprocess
27.03.18 17:36:18.417 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 3000
27.03.18 17:36:18.436 root                                                         INFO  - ---------------- -DelegateThread firstElement: time:0.00120248  data:1019
27.03.18 17:36:18.437 root                                                         INFO  - -----------------DelegateThread lastElement time:0.00100479  data:2019
27.03.18 17:36:18.437 root                                                         INFO  - -----------------DelegateThread Swap queue pointers data_store<<-->>data_toprocess
27.03.18 17:36:19.417 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 4000
27.03.18 17:36:19.437 root                                                         INFO  - ---------------- -DelegateThread firstElement: time:0.00130645  data:2020
27.03.18 17:36:19.438 root                                                         INFO  - -----------------DelegateThread lastElement time:0.00100336  data:3020
27.03.18 17:36:19.444 root                                                         ERROR - --- Exception in ThreadProcess:T_FastTask
27.03.18 17:36:19.444 root                                                         ERROR - --- DataStore has to many elements already!
27.03.18 17:36:19.444 root                                                         ERROR - --- Process Queue:0, Store Queue:1001
27.03.18 17:36:19.444 BufferedExchange.BufferedExchangeProgram                     WARN  - -------------- Instance:BufferedExchangeComponent1/BufferedExchangeProgram1 DataLost: 4022
27.03.18 17:36:19.445 root                                                         INFO  - -----------------DelegateThread Swap queue pointers data_store<<-->>data_toprocess
27.03.18 17:36:20.423 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 5000
27.03.18 17:36:20.445 root                                                         INFO  - ---------------- -DelegateThread firstElement: time:0.00134554  data:3021
27.03.18 17:36:20.446 root                                                         INFO  - -----------------DelegateThread lastElement time:0.00101738  data:4021
27.03.18 17:36:21.423 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 6000
27.03.18 17:36:22.423 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 7000
27.03.18 17:36:23.423 BufferedExchange.BufferedExchangeProgram                     INFO  - ---------------- Execute: 8000

```

## General notes:
Please make sure that your Buffer meets your speed requirements and implement a overflow exception.

You have to be able to process the data faster then they are beeing created or else this setup will create issues.

The logging is used mainly for demonstration purposes in this application in productive systems it should now be used as excecively e.g. Change `Log.Info()` to `Log.Debug()`.