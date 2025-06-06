//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
//

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Base/Acf/Commons/ComponentBase.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CounterComponentProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

#include "Helpers/Enums.hpp"

namespace ProgramComponentInteraction
{

using namespace Arp;
using namespace Arp::Base::Acf::Commons;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

#ifdef DEBUG
#define DEBUG_FUNCTION_CALL log.Info("'{0}' invoked of object with instance name '{1}'", __FUNCTION__, this->GetFullName());
#else
#define DEBUG_FUNCTION_CALL
#endif

//#component
class CounterComponent : public ComponentBase, public ProgramComponentBase, private Loggable<CounterComponent>
{
public: // typedefs

public: // construction/destruction
    CounterComponent(ILibrary& library, const String& name);

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void PowerDown() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods

private: // fields
    CounterComponentProgramProvider programProvider;

public: // Component Interaction operations
    /// Toggles the Command
    void RefreshState();

    // Set progress of the DownCounterProgram
    void SetProgressDC(Progress p) { progress_DC = p; }
    // Set progress of the UpCounterProgram
    void SetProgressUC(Progress p) { progress_UC = p; }

    // returns the current command
    Command GetCommand(void) { return command; }

private: // member variables for Program Component Interaction
    Progress progress_UC = Progress::Stopped;
    Progress progress_DC = Progress::Stopped;
    Command command{Command::CountDown};

public: // ports

    //#port
    //#name(StopCounting)
    boolean IP_Stop{false};
};

} // end of namespace ProgramComponentInteraction
