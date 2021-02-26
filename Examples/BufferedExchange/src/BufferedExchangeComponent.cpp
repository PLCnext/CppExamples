#include "BufferedExchangeComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "BufferedExchangeLibrary.hpp"

namespace BufferedExchange {

BufferedExchangeComponent::BufferedExchangeComponent(IApplication &application,const String &name) :
		ComponentBase(application,::BufferedExchange::BufferedExchangeLibrary::GetInstance(), name,ComponentCategory::Custom),
		programProvider(*this),
		ProgramComponentBase(::BufferedExchange::BufferedExchangeLibrary::GetInstance().GetNamespace(), programProvider),
		//
		delegateThread(ThreadSettings("-DelegateThread", 20, 0, 0),	Arp::make_delegate(&wD, &MyWorker::Run)),
		//
		staticThread(ThreadSettings("-StaticThread", 20, 0, 0), &MyWorker::RunStatic,(void*)&wS),
		//
		workerThread(make_delegate(&wT, &MyWorker::RunSingle), 1000,"-WorkerThread")
{
	log.Info("------------------- BufferedExchangeComponent Constructor");
}

void BufferedExchangeComponent::Initialize() {
	// never remove next line
	ProgramComponentBase::Initialize();

	// subscribe events from the event system (Nm) here
}

void BufferedExchangeComponent::LoadConfig() {
	// load project config here

}

void BufferedExchangeComponent::SetupConfig() {
	// never remove next line
	ProgramComponentBase::SetupConfig();

	// setup project config here
}

void BufferedExchangeComponent::ResetConfig() {
	// never remove next line
	ProgramComponentBase::ResetConfig();
	log.Info("--- ResetConfig");

	// implement this inverse to SetupConfig() and LoadConfig()
}

void BufferedExchangeComponent::Start(void) {
	log.Info("--- Start");
	try {
		wT.Stop = false;
		workerThread.Start();

		wS.Stop = false;
		staticThread.Start();

		wD.Stop = false;
		delegateThread.Start();
	} catch (Exception &e) {
		log.Error("--- Error thread start:{0}",	e.GetMessage());
	}
}

void BufferedExchangeComponent::Stop(void) {
	log.Info("--- Stop:");
	try {
		StopWT(wT, workerThread);
		StopT(wD, delegateThread);
		StopT(wS, staticThread);

	} catch (Exception &e) {
		log.Error("--- Error thread Stop:{0}",	e.GetMessage());
	}
}

void BufferedExchangeComponent::StopWT(MyWorker &W, WorkerThread &T) {
	log.Info("--- Thread:{0} Running:{1} ", "Worker", T.IsRunning());
	W.Stop = true;
	// Stopping WorkerThread synchronously.
	T.Stop();
}

void BufferedExchangeComponent::StopT(MyWorker &W, Thread &T) {
	log.Info("--- Thread:{0} Running:{1} Joinable:{2} }",
		T.GetName(), T.IsRunning(), T.IsJoinable());
	// Stopping thread synchronously.
	W.Stop = true;
	T.Interrupt();
	if (T.IsJoinable()) {
		T.Join();
	}
}
} // end of namespace BufferedExchange
