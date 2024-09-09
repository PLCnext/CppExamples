/******************************************************************************
 *
 * Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 * Licensed under the MIT. See LICENSE file in the project root for full license information.
 *
 *  ThreadExampleComponent.cpp
 *
 *  Created on: 16.05.2019
 *  Author: Eduard Münz, Oliver Warneke
 *
 ******************************************************************************/

/******************************************************************************/
/*  INCLUDES                                                                  */
/******************************************************************************/

#include "ThreadExampleComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "ThreadExampleLibrary.hpp"

namespace ThreadExample
{
ThreadExampleComponent::ThreadExampleComponent(ILibrary& library, const String& name)
    : ComponentBase(library, name, ComponentCategory::Custom, GetDefaultStartOrder())
    , programProvider(*this)
    , ProgramComponentBase(::ThreadExample::ThreadExampleLibrary::GetInstance().GetNamespace(), programProvider)
	// Worker Thread Example
	, workerThreadInstance(make_delegate(this, &ThreadExampleComponent::workerThreadBody) , 10000, "WorkerThreadName")
	//Commons/Thread Example
	, delegateThreadInstance(ThreadSettings("DelegateThreadName", 20, 0, 0),this,&ThreadExampleComponent::delegateThreadBody,(void*)&myparameter)
	, staticThreadInstance(ThreadSettings("StaticThreadName", 20, 0, 0),&ThreadExampleComponent::staticThreadBody,(void*)&xStopThread)
{
}

void ThreadExampleComponent::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void ThreadExampleComponent::LoadConfig()
{
    // load project config here
}

void ThreadExampleComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void ThreadExampleComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void ThreadExampleComponent::PowerDown()
{
	// implement this only if data shall be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

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

    Log::Info("-------------------------------staticThreadInstance stop");
    staticThreadInstance.Interrupt();
    if (staticThreadInstance.IsJoinable()){
    staticThreadInstance.Join();
    }
    Log::Info("-------------------------------staticThreadInstance stopped");

    Log::Info("-------------------------------delegateThreadInstance stop");
    delegateThreadInstance.Interrupt();
    if (delegateThreadInstance.IsJoinable()){
    delegateThreadInstance.Join();
    }
    Log::Info("-------------------------------delegateThreadInstance stopped");
}

/// Thread Body
void ThreadExampleComponent::workerThreadBody(void) {

    if(!xStopThread)
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


int ThreadExampleComponent::GetCounterValue(){
    return iCountervalue;
}

} // end of namespace ThreadExample
