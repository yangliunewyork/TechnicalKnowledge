/*
  The command pattern is a behavioral design pattern in which an object is used to encapsulate 
  all information needed to perform an action or trigger an event at a later time. This information 
  includes the method name, the object that owns the method and values for the method parameters.
  Four terms always associated with the command pattern are command, receiver, invoker and client. 
  A command object knows about receiver and invokes a method of the receiver. 
  Values for parameters of the receiver method are stored in the command. 
  The receiver then does the work. 
  An invoker object knows how to execute a command, and optionally does bookkeeping about the command execution. 
  The invoker does not know anything about a concrete command, it knows only about command interface. 
  Both an invoker object and several command objects are held by a client object. 
  The client decides which commands to execute at which points. To execute a command, it passes the command object to the invoker object.
*/

#include <iostream>
#include <memory>

// Command Interface
class ICommand {
public:
  ICommand(){}
  virtual ~ICommand(){}
  virtual void Execute() = 0;
};
typedef std::shared_ptr<ICommand> CommandPtr;

// Invoker, you can define a remote control class as well =)
class Switch {
public:
  Switch(const CommandPtr & open,const CommandPtr & close) :
    m_open_command(open),m_close_command(close){}
  void SetReceiverCommand(const CommandPtr & open,const CommandPtr & close) {m_open_command = open; m_close_command = close;}
  void Open() {m_open_command->Execute();}
  void Close() {m_close_command->Execute();}
private:
  CommandPtr m_open_command;
  CommandPtr m_close_command;
};

class ISwitchable {
public:
  ISwitchable(){}
  virtual ~ISwitchable(){}
  virtual void PowerOn() = 0;
  virtual void PowerOff() = 0;
};
typedef std::shared_ptr<ISwitchable> ISwitchablePtr;

// Receiver, it's function will be called in
// concrete command instance. We can pass reference
// of the receiver or just the function we needed to
// the concrete command.
class Light : public ISwitchable {
public:
  Light(){}
  virtual void PowerOn() {std::cout <<"Power On Light" << std::endl;}
  virtual void PowerOff() {std::cout <<"Power Off Light" << std::endl;}
};

class AirConditioner : public ISwitchable {
public:
  AirConditioner(){}
  virtual void PowerOn() {std::cout <<"Power On AirConditioner" << std::endl;}
  virtual void PowerOff() {std::cout <<"Power Off AirConditioner" << std::endl;}
};

// The concrete command to turn on/off light/air conditioner.
// Notice that we stores receiver's method here, that's
// because in general concrete command should define a binding
// between Receiver object and an action.
class PowerOnSwitch : public ICommand {
public:
  PowerOnSwitch(const ISwitchablePtr & sw):m_switchable(sw){}
  virtual void Execute(){m_switchable->PowerOn();}
private:
  ISwitchablePtr m_switchable;
};

class PowerOffSwitch : public ICommand {
public:
  PowerOffSwitch(const ISwitchablePtr & sw):m_switchable(sw){}
  virtual void Execute(){m_switchable->PowerOff();}
private:
  ISwitchablePtr m_switchable;
};



int main () {
  
  ISwitchablePtr light = std::make_shared<Light>();
  CommandPtr light_on_command = std::make_shared<PowerOnSwitch>(light);
  CommandPtr light_off_command = std::make_shared<PowerOffSwitch>(light);
  
  Switch remote_control(light_on_command,light_off_command);
  
  remote_control.Open();
  remote_control.Close();

  ISwitchablePtr air_conditioner = std::make_shared<AirConditioner>();
  CommandPtr air_conditioner_on_command = std::make_shared<PowerOnSwitch>(air_conditioner);
  CommandPtr air_conditioner_off_command = std::make_shared<PowerOffSwitch>(air_conditioner);
  remote_control.SetReceiverCommand(air_conditioner_on_command,air_conditioner_off_command);
  remote_control.Open();
  remote_control.Close();
  return 0;
}
