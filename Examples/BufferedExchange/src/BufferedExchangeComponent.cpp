#include "BufferedExchangeComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "BufferedExchangeLibrary.hpp"

namespace BufferedExchange {

BufferedExchangeComponent::BufferedExchangeComponent(IApplication &application,
		const String &name) :
		ComponentBase(application,::BufferedExchange::BufferedExchangeLibrary::GetInstance(),name, ComponentCategory::Custom),
		programProvider(*this),
		ProgramComponentBase(::BufferedExchange::BufferedExchangeLibrary::GetInstance().GetNamespace(),	programProvider),
		//
		delegateThread(ThreadSettings("-DelegateThread", 0, 0, 0),	Arp::make_delegate(&wD, &BufferedExchange::MyWorker<long int>::Run)) {
	log.Info("-------------------BufferedExchangeComponent Constructor");
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
	log.Info("---------------- ResetConfig");

	// implement this inverse to SetupConfig() and LoadConfig()
}

void BufferedExchangeComponent::Start(void) {
	log.Info("---------------- Start");
	try {
		wD.Stop = false;
		delegateThread.Start();
	} catch (Exception &e) {
		log.Error("---------------- Error thread start:{0}", e.GetMessage());
	}
}

void BufferedExchangeComponent::Stop(void) {
	log.Info("----------------Stop:");
	try {
		StopT(wD, delegateThread);
	} catch (Exception &e) {
		log.Error("---------------- Error thread Stop:{0}", e.GetMessage());
	}
}
template<typename S>
void BufferedExchangeComponent::StopWT(MyWorker<S> &W, WorkerThread &T) {
	log.Info("---------------- Thread:{0} Running:{1} ", "Worker",
			T.IsRunning());
	W.Stop = true;
	// Stopping WorkerThread synchronously.
	T.Stop();
}
template<typename S>
void BufferedExchangeComponent::StopT(MyWorker<S> &W, Thread &T) {
	log.Info("---------------- Thread:{0} Running:{1} Joinable:{2}",
			T.GetName(), T.IsRunning(), T.IsJoinable());

	// Stopping thread loops
	W.Stop = true;

	// If thread is still running after setting "Stop" call interrupt
	// to ensure thread shutdown.
	if (T.IsRunning()){
		T.Interrupt();
	}

	// Wait for the thread to finish.
	if (T.IsJoinable()) {
		T.Join();
	}
}
} // end of namespace BufferedExchange
