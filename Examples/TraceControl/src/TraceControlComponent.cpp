///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////
#include "TraceControlComponent.hpp"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "TraceControlLibrary.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/System/Core/Exception.hpp"

namespace TraceControl
{

using Arp::System::Rsc::ServiceManager;
using namespace Arp::Plc::Commons::Domain;

TraceControlComponent::TraceControlComponent(IApplication& application, const String& name)
: ComponentBase(application, ::TraceControl::TraceControlLibrary::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::TraceControl::TraceControlLibrary::GetInstance().GetNamespace())
, traceThread(this, &TraceControlComponent::TraceActions, 1000, "TraceThread")
{
}

void TraceControlComponent::Initialize()
{
    // never remove next line
    PlcDomainProxy::GetInstance().RegisterComponent(*this, true);
    
    // initialize singletons here, subscribe notifications here
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // register all Plc event handler
    plcDomainProxy.PlcLoaded += make_delegate(this, &TraceControlComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted += make_delegate(this, &TraceControlComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping += make_delegate(this, &TraceControlComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading += make_delegate(this, &TraceControlComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging += make_delegate(this, &TraceControlComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged += make_delegate(this, &TraceControlComponent::OnPlcChanged);
}

void TraceControlComponent::SubscribeServices()
{
    // gets the ITraceControllerService pointer
    this->traceServicePtr = ServiceManager::GetService<ITraceControllerService>();
}

void TraceControlComponent::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void TraceControlComponent::SetupSettings()
{
    // never remove next line
    MetaComponentBase::SetupSettings();

	// setup firmware settings here
}

void TraceControlComponent::PublishServices()
{
	// publish the services of this component here
}

void TraceControlComponent::LoadConfig()
{
    // load project config here
}

void TraceControlComponent::SetupConfig()
{
    // setup project config here
}

void TraceControlComponent::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void TraceControlComponent::Dispose()
{
    // never remove next line
    MetaComponentBase::Dispose();

    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
    PlcDomainProxy& plcDomainProxy = PlcDomainProxy::GetInstance();

    // unregister all Plc event handler
    plcDomainProxy.PlcLoaded -= make_delegate(this, &TraceControlComponent::OnPlcLoaded);
    plcDomainProxy.PlcStarted -= make_delegate(this, &TraceControlComponent::OnPlcStarted);
    plcDomainProxy.PlcStopping -= make_delegate(this, &TraceControlComponent::OnPlcStopping);
    plcDomainProxy.PlcUnloading -= make_delegate(this, &TraceControlComponent::OnPlcUnloading);
    plcDomainProxy.PlcChanging -= make_delegate(this, &TraceControlComponent::OnPlcChanging);
    plcDomainProxy.PlcChanged -= make_delegate(this, &TraceControlComponent::OnPlcChanged);}

void TraceControlComponent::PowerDown()
{
	// implement this only if data must be retained even on power down event
}

void TraceControlComponent::OnPlcLoaded()
{
}

void TraceControlComponent::OnPlcStarted()
{
    this->StartTrace();
}

void TraceControlComponent::OnPlcStopping()
{
    this->StopTrace();
}

void TraceControlComponent::OnPlcUnloading(bool)
{
}

void TraceControlComponent::OnPlcChanging()
{
    this->StopTrace();
}

void TraceControlComponent::OnPlcChanged(bool /*success*/)
{
    this->StartTrace();
}

void TraceControlComponent::StartTrace()
{
    this->traceThread.Start();
}

void TraceControlComponent::StopTrace()
{
    this->traceThread.Stop();
}

void TraceControlComponent::TraceActions()
{
    // This is implemented as a step sequencer.
    // Each step demonstrates different features of the Trace Controller service.
    //
    // This sequence is designed to be used with the default TraceController configuration in firmware 2021.0.3.
    //
    // Not demonstrated here:
    // The default trace configuration will only log information after a Task Watchdog event,
    // which is not demonstrated here.
    //
    //  Also not demonstrated here:
    // - TriggerSavingTraceOutputs()
    //
    //   This example uses the session configuration that comes with the firmware, by default:
    //   /opt/plcnext/lttng/plcnexttrace_snapshot.lttng
    //   If the user creates their own LTTng session configuration file, then they can load it using this method.
    //
    // - DestroySession()
    //   This example does not load its own session configuration file, and we do not want to unload/destroy the
    //   default session that is loaded by the firmware.
    //

    switch(step)
    {
        case 1:
        {
            // Check if the session daemon is alive
            boolean isAlive;
            isAlive = this->traceServicePtr->IsSessionDaemonAlive();
            this->log.Info("Is the Trace Controller session daemon alive? {0}", isAlive);

            break;
        }

        case 2:
        {
            // Check if a named session is loaded
            boolean isLoaded;
            RscString<512> session = "plcnexttrace_snapshot";
            isLoaded = this->traceServicePtr->IsSessionLoaded(session);
            this->log.Info("Is the '{0}' session loaded? {1}", session, isLoaded);

            break;
        }

        case 3:
        {
            // Check if a named session is in snapshot mode.
            // In the default case, an error will be thrown,
            // because the named session is not loaded.
            boolean isSnapshot;
            RscString<512> session = "plcnexttrace_snapshot";
            try
            {
                isSnapshot = this->traceServicePtr->IsSessionInSnapshotMode(session);
                this->log.Info("Is the '{0}' session in snapshot mode? {1}", session, isSnapshot);
            }
            catch(const Arp::Exception& e)
            {
                this->log.Error("Exception in method '{0}' : {1}", __FUNCTION__, e.GetMessage());
            }
            
            break;
        }

        case 4:
        {
            //Load a named session configuration
            boolean isLoaded;
            RscString<512> session = "plcnexttrace_snapshot";
            RscString<512> path = "/opt/plcnext/lttng/plcnexttrace_snapshot.lttng";
            this->log.Info("Loading session '{0}'.", session);
            isLoaded = this->traceServicePtr->LoadSessionConfiguration(session, path);
            this->log.Info("Has the '{0}' session been loaded successfully? {1}", session, isLoaded);
            
            break;
        }

        case 5:
        {
            // Check if a named session is in snapshot mode.
            // Now that the session is loaded, this will work.
            boolean isSnapshot;
            RscString<512> session = "plcnexttrace_snapshot";
            isSnapshot = this->traceServicePtr->IsSessionInSnapshotMode(session);
            this->log.Info("Is the '{0}' session in snapshot mode? {1}", session, isSnapshot);
            
            break;
        }

        case 6:
        {
            // Get a list of all loaded sessions.
            // If no changes have been made to the Trace Controller configuration file,
            // then this will return one session named "plcnexttrace_snapshot".
            std::vector<RscString<512>> sessions;
            this->log.Info("Getting a list of Trace Controller sessions.");
            sessions = this->traceServicePtr->ListSessions();
            for (const auto& session: sessions)
            {
                this->log.Info(">> Trace Controller session {0} is loaded.", session);
            }

            break;
        }

        case 7:
        {
            // Check if a named session is enabled/started
            boolean isEnabled;
            RscString<512> session = "plcnexttrace_snapshot";
            isEnabled = this->traceServicePtr->IsSessionEnabled(session);
            this->log.Info("Is the '{0}' session enabled/started? {1}", session, isEnabled);

            break;
        }

        case 8:
        {
            // Load the userspace tracepoint library
            this->log.Info("Loading the userspace tracepoint library.");
            this->traceServicePtr->LoadTracepointLib();

            break;
        }

        case 9:
        {
            // Start a named session
            boolean isStarted;
            RscString<512> session = "plcnexttrace_snapshot";
            this->log.Info("Starting the '{0}' session.", session);
            isStarted = this->traceServicePtr->StartSession(session);
            this->log.Info("Is the '{0}' session started? {1}", session, isStarted);

            break;
        }

        case 15:
        {
            // Stop a named session
            boolean isStopped;
            RscString<512> session = "plcnexttrace_snapshot";
            this->log.Info("Stopping the '{0}' session.", session);
            isStopped = this->traceServicePtr->StopSession(session);
            this->log.Info("Is the '{0}' session stopped? {1}", session, isStopped);

            break;
        }

        case 16:
        {
            // Unload the userspace tracepoint library
            this->log.Info("Unloading the userspace tracepoint library.");
            this->traceServicePtr->UnloadTracepointLib();

            break;
        }

        case 17:
        {
            // Destroy/Unload a named session
            boolean isDestroyed;
            RscString<512> session = "plcnexttrace_snapshot";
            this->log.Info("Destroying/unloading the '{0}' session.", session);
            isDestroyed = this->traceServicePtr->DestroySession(session);
            this->log.Info("Is the '{0}' session destroyed? {1}", session, isDestroyed);

            break;
        }

        default:
            break;
    }

    // Increment the step and reset the sequence after a time
    if (++step > 100) step = 0;
}

} // end of namespace TraceControl
