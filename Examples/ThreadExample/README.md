# Table of contents

<!-- TOC depthFrom:1 orderedList:true -->

1. [Introduction](# Introduction)
2. [Example details](## Example details)
3. [Preconditions](## Preconditions)
4. [Project compiling in Eclipse](## Project compiling in Eclipse)
5. [PLCnext Engineer project](## PLCnext Engineer project)
6. [Start-Up instructions](## Start-up instructions)
7. [Manually basic Setup](### Basic manual setup)
8. [Commons::WorkerThread and Commons::Thread](### Commons::WorkerThread and Commons::Thread)
9. [General Notes](#### General Notes)

<!-- /TOC -->

# Introduction

This example demonstrates the creation and usage of workerThread, staticThread and delegateThread in a C++ application. All threads are implemented in a component in a non real-time context.

The purpose of workerThread implementation is to relocate time-consuming blocking operation from the real-time program into a separate thread, because otherwise this would have an unwanted impact on the real-time process.

The purpose of staticThread implementation is to start a non real-time task, e.g. methods of RSC services.

The purpose of the delegateThread implementation is to use a call-back function (the thread has access to this*).


## Example details

|Description | Value |
|------------ |-----------|
|Controller| AXC F 2152 | 
|FW | 2019.3|
|SDK | 2019.3|
|PLCnext Engineer| 2019.3 | 


## Preconditions

- AXC F 2152 controller with firmware 2019.3
- Eclipse IDE "Photon" 
- PLCnext Engineer 2019.3


## Project compiling in Eclipse

1. In Eclipse, create the project "ThreadExample" with Component "ThreadExampleComponent" and Program "ThreadExampleProgram".
2. In the project, replace the files "ThreadExampleComponent.cpp", "ThreadExampleComponent.hpp", "ThreadExampleProgram.cpp", and "ThreadExampleProgram.hpp" with the according files from this repository. Alternatively, you can create your own project with component and programs and include the source code in your application.
3. Compile the Eclipse project. 
4. After successfull project compilation, the PLCnext Engineer library will be created automatically. You can find it in your Eclipse workspace folder, e.g.: "workspace\ThreadExample\bin\ThreadExample.pcwlx" 


## PLCnext Engineer project 

1. In PLCnext Engineer, create a new project and include the "ThreadExample.pcwlx" in the project.
2. Instantiate the "ThreadExampleProgram" under a previously defined task.
3. Declare a port variable of "INT" datatype, e.g. in the "main" program.
4. In the "PLANT" area of the PLCnext Engineer, unfold the "PLCnext" node and connect the C++ port variable "i_pCounter" and the IEC 61131 port variable.
5. Download the PLCnext Engineer project to the PLCnext Control.


## Start-up instructions

- If the project is successfully implemented and downloaded, you can follow the value incrementation of variable "i_pCounter" in PLCnext Engineer debug mode and/or in a watchwindow and threads status in the Output.log file on the plcnext target; see: /opt/plcnext/logs/Output.log
- If the project does not start successfully, please see the error messages in Output.log file on the PLCnext target, see: /opt/plcnext/logs/Output.log


### Basic manual setup

1. Add `#include "Arp/System/Acf/IControllerComponent.hpp"` and inherit the `IControllerComponent` interface.
2. Implement the `Component.Start()` and `Component.Stop()` method.
3. Include the threading headers:
```cpp
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Commons/Threading/ThreadSettings.hpp"
```

### Commons::WorkerThread and Commons::Thread

1.) Create a `workerThreadInstance`, `delegateThreadInstance` and `staticThreadInstance`:

```cpp
WorkerThread workerThreadInstance;
Thread delegateThreadInstance;
Thread staticThreadInstance;
```

2.) Create a `private methods` with parameters, that implements the threads bodys - what should be done in this threads. 

```cpp
//... Header
bool xStopThread = false;
int myparameter{123};

private: void WorkerThreadBody(void);
void delegateThreadBody(void * pParameter);
static void staticThreadBody(void* pParameter);
```

3.) Initialize the `WorkerThread`, `delegateThread` and `staticThread` in your Components constructor:
    
```cpp
inline ThreadExampleComponent::ThreadExampleComponent(IApplication& application, const String& name)
: ComponentBase(application, ::ThreadExample::ThreadExampleLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), programProvider)

// Added: data info provider
, dataInfoProvider(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), &(this->programProvider))

//// Worker Thread Example
, workerThreadInstance(make_delegate(this, &ThreadExampleComponent::workerThreadBody) , 10000, "WorkerThreadName")

//// Delegate Thread Example
, delegateThreadInstance(this,&ThreadExampleComponent::delegateThreadBody,(void*)&myparameter)

//// Static Thread Example
, staticThreadInstance(&ThreadExampleComponent::staticThreadBody,(void*)&xStopThread)
```


4.) Add `workerThreadInstance.Start()`, `workerThreadInstance.Stop()`, `delegateThreadInstance.Start()`, `staticThreadInstance.Start()` to the Component. The Start method is used to start or stop the threads during start of the controller or/and component, respectively.
The Thread body will be executed, and after this, the thread sleeps for the specified idle time. The `WorkerThread.Stop()` method blocks until the thread finishes its current work, if it is not sleeping. 
When component `Stop` is called, the staticThread or delegateThread will be synchronously executed one last time and started again by the `Start` component. 

```cpp
void ThreadExampleComponent::Start(void) {
	xStopThread = false;
	Log::Info("-------------------------------workerThreadInstance start");
	workerThreadInstance.Start();
	Log::Info("-------------------------------workerThreadInstance started");

	Log::Info("-------------------------------delegateThreadInstance start");
	delegateThreadInstance.Start();
	Log::Info("-------------------------------delegateThreadInstance started");


	Log::Info("-------------------------------staticThreadInstance start");
	staticThreadInstance.Start();
	Log::Info("-------------------------------staticThreadInstance started");

    }
    
    void ThreadExampleComponent::Stop(void) {
    	// if you want to stop some loops of your thread during execution
    	// add something like "stoptheThread" before executing workerThreadStop.
    	xStopThread = true;
    	Log::Info("-------------------------------workerThreadInstance stop");
    	workerThreadInstance.Stop();
    	Log::Info("-------------------------------workerThreadInstance stopped");
    }
    
    /// worker Thread Body
    void ThreadExampleComponent::workerThreadBody(void) {
    
    	if(xStopThread == false)
    	{
    		if(iCountervalue < iEndValue)
    			iCountervalue ++;
    		else
    			iCountervalue = iStartValue;
    
    		Log::Info("-------------------------------workerThreadInstance is running, iCountervalue={0}", iCountervalue);
    	}
    	else
    		Log::Info("-------------------------------workerThreadInstance is stopped, iCountervalue={0}", iCountervalue);
    }
    
    
    /// delegate Thread Body (non-static)
    void ThreadExampleComponent::delegateThreadBody(void* pParameter) {
    	// has access to this*
    	int *i = reinterpret_cast<int*>(pParameter);
    
    	while(!xStopThread)
    	{
    		if(this->myparameter == *i)
    			Log::Info("-------------------------------ThreadExampleComponent::delegateThreadBody is running successful i={0} , myparameter = {1}", *i, this->myparameter);
    
    		else
    			Log::Info("-------------------------------ThreadExampleComponent::delegateThreadBody is running with ERROR: i={0} , myparameter = {1}", *i, this->myparameter);
    
    		Thread::Sleep(1000);
    	}
    
    	Log::Info("-------------------------------ThreadExampleComponent::delegateThreadBody stopped");
    }
    
    
    /// static Thread Body
    void ThreadExampleComponent::staticThreadBody(void* pParameter) {
    	bool* pValue = (bool*) pParameter;
    	// has NO access to this*
    	while(!*pValue){
    
    		//Do something and sleep for specifiedTime.
    		Log::Info("-------------------------------ThreadExampleComponent::staticThreadBody is running  pParameter={0}", (int) *pValue);
    		Thread::Sleep(500);
    	}
    
    		Log::Info("-------------------------------ThreadExampleComponent::staticThreadBody stopped");
    }
```

#### General Notes

It is not recommended to instantiate threads inside a RT (real-time) program because the thread's lifetime management and controlling should be done by the component.

To exchange data between the real-time program and the worker thread, add the data portion (e.g. port variables or methods) to the component, and each instantiated program should obtain a pointer to its component by adjusting the program provider (see method *Program::Execute()* in ThreadExampleProgram.cpp).

Please remember to make your data exchange structure thread safe, otherwise the data exchange will result in undefined behavior. Also consider about the cycle time of your *Program::Execute()* if you decide to use blocking mechanisms to guarantee thread safety.