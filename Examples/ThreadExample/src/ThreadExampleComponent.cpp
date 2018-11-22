#include "ThreadExampleComponent.hpp"

namespace ThreadExample 
{

void ThreadExampleComponent::Initialize()
{
}

void ThreadExampleComponent::LoadSettings(const String& settingsPath)
{
}

void ThreadExampleComponent::SetupSettings()
{
}

void ThreadExampleComponent::SubscribeServices()
{
}

void ThreadExampleComponent::LoadConfig()
{
}

void ThreadExampleComponent::SetupConfig()
{
    // DO NOT REMOVE THIS!
    ThreadExampleComponent::RegisterComponentPorts();
}

void ThreadExampleComponent::ResetConfig()
{
	//this->dataInfoProvider.Reset();
}

void ThreadExampleComponent::PublishServices()
{
}

void ThreadExampleComponent::Dispose()
{
}

void ThreadExampleComponent::PowerDown()
{
}

void ThreadExampleComponent::Start(void) {
	stopTheThread = false;
	Log::Info("-------------------------------workerThreadInstance start");
	workerThreadInstance.Start();
	Log::Info("-------------------------------workerThreadInstance started");
}

void ThreadExampleComponent::Stop(void) {
	// if you want to stop some loops of your thread during execution
	// add something like "stoptheThread" before executing workerThreadStop.
	stopTheThread = true;

	Log::Info("-------------------------------workerThreadInstance stop");
	workerThreadInstance.Stop();
	Log::Info("-------------------------------workerThreadInstance stopped");
}

/// Thread Body
void ThreadExampleComponent::workerThreadBody(void) {

	// some time intensive stuff
	while((x < y) && !stopTheThread)
	{
		x++;
	}
	Log::Info("-------------------------------workerThreadBody: Count = {0}", (int)x);
}

void ThreadExampleComponent::delegateThreadBody(void* pParameter) {
	// has access to this*
	int *i =  reinterpret_cast<int*>(pParameter);
	while(!stopTheThread)
	{
		if(this->myparameter < *i){
			i++;
		}
		Thread::Sleep(5000);
	}
}

void ThreadExampleComponent::staticThreadBody(void* pParameter) {
	bool* pValue = (bool*) pParameter;
	// has NO access to this*
	while(!*pValue){
		//Do something and sleep for specifiedTime.
		Thread::Sleep(5000);
	}
}

} // end of namespace ThreadExample
