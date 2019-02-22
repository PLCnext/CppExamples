# Program Componenent Interaction 
This example shows how data can be exchanged from a `Program` to a `Component`.
The `Program`  can also recieve data by calling public `Getter` methods of the `Component`.

The programms `UpCounterProgram` and `DownCounterProgram` access the Component `CounterComponent` with these methods.
They use the `CounterComponent.get_command()` to recieve an enum of `Commands` and a `setProgress()` method to inform the Component of the state the Program is in.
Once the programm has got a command it will continue to execute this command and when finnished 
execute the`CounterComponent.RefreshState()` method wich will then initiate a state change.

```mermaid
sequenceDiagram
    participant CounterComponent
    participant UpCounterProgram
    participant DownCounterProgram
    CounterComponent->>DownCounterProgram: create
 CounterComponent->>DownCounterProgram: create
Note left of CounterComponent: Command::CountUp
    loop Execute
        UpCounterProgram->>CounterComponent: get command
       
        UpCounterProgram->UpCounterProgram: count Up   
        UpCounterProgram->>CounterComponent: set current State 
 end
UpCounterProgram->>CounterComponent: Refresh Command 
Note left of CounterComponent: Command::CountDown
loop Execute
        DownCounterProgram->>CounterComponent: get command 
        DownCounterProgram->DownCounterProgram: count Down
        DownCounterProgram->>CounterComponent: Refresh State 
    end

DownCounterProgram->>CounterComponent: Refresh Command 
Note left of CounterComponent: Command::CountUp
```

## Example details
|Description | Value |
|------------ |-----------|
|Controller | AXC F 2152 | 
|FW | 2019.0 |
|SDK | 2019.0 |


## Preconditions
You need to have PLCnext Engineer installed and a installed C++ SDK.


## Start-Up instructions
1. instantiate one instance of each Program
2. start the PLC
3. Login with PLCnext Engineer Debug or SSH.
4. Check Progress
4. You can now see the Counters going up and down in the `PLCNext - Datalist` in the PLCnext Engineer.
4. You can also see the progress in the Output.log file with `tail -f /opt/plcnext/logs/Output.log`.