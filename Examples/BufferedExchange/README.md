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

1. In Eclipse, create the project "BufferedExchange" with Component "BufferedExchangeComponent" and Program "BufferedExchangeProgram".
1. In the project, replace the files "BufferedExchangeComponent.cpp", "BufferedExchangeComponent.hpp", "BufferedExchangeProgram.cpp", and "BufferedExchangeProgram.hpp" with the according files from this repository. Alternatively, you can create your own project with component and programs and include the source code in your application.
1. Compile the Eclipse project.
1. After successfull project compilation, the PLCnext Engineer library will be created automatically. You can find it in your Eclipse workspace folder, e.g.: "workspace\BufferedExchange\bin\BufferedExchange.pcwlx"

## PLCnext Engineer project

1. In PLCnext Engineer, create a new project and include the "BufferedExchange.pcwlx" in the project.
1. Instantiate the "BufferedExchangeProgram" under a previously defined task.
1. Download the PLCnext Engineer project to the PLCnext Control.

## Project Execution

In this Project we show how to publish data from a [RealTimeProgram](src/BufferedExchangeProgram.cpp) in a cyclic manner and store them in a component for further processing inside a thread.


The [class MyWorker](src/MyWorker.hpp ) holds all the data and methods the Thread is interacting with.
It implenents methods for each Type of thread as well as an interface to publish data.

The data storage is realised by swaping two queues.
One to recieve data and another Queue for processing.
Whenever data are added or beeing processed the Queues are locked up using a Mutex to aussure thread safety.
This process works fine in a single producer/single consumer environment.
As long as the time requirement or the forwarded data are not to large it will also work fine with multiple producers.

Watch out the `SetData()` function is blocking, it actively waits for the Mutex to be locked and might infulence your RealTime.
You can switch the Lock() to TryLock() and add a timeout loop if necessary.

## General notes:
Please make sure that your Buffer meets your speed requirements and implement a overflow exception.
You have to be able to process the data faster then they are created or else this setup will create issues. 