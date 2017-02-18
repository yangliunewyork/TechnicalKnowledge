//http://www.newthinktank.com/2012/10/state-design-pattern-tutorial/


// Implement the default behavior.
class ATMState{
public:
  virtual InsertCard(ATM* atm) {/*implementation*/}
  virtual float GetBalanceInfo(ATM* atm){/*implementation*/}
  virtual bool Deposit(ATM* atm,float val){/*implementation*/}
  virtual bool Withdraw(ATM* atm,float val){/*implementation*/}
  virtual bool VerifyPIN(ATM* atm,int pinVal){/*implementation*/}
private:
  friend class ATM;
};

// Maintain no local state,
// so it can be shared and only one instance is required.
class NoCardState : public ATMState {
public:
  static NoCardState& Instance(){
    static NoCardState instance;
    return instance;
  }
  virtual InsertCard(ATM* atm) {atm->ChangeState(HasCardState::Instance);}
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"Please insert card"<<std::endl;}
  virtual bool VerifyPIN(ATM* atm,int pinVal){std::cout<<"Please insert card"<<std::endl;}
  //.........
private:
  NoCardState(){}
  NoCardState(const NoCardState& other) = delete;
  NoCardState& operator=(const NoCardState& other) = delete;
};

class HasCardState : public ATMState {
public:
  static HasCardState& Instance(){
    static HasCardState instance;
    return instance;
  }
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"You hasn't input PIN yet"<<std::endl;}
  bool VerifyPIN(ATM* atm,int pinVal) {atm->ChangeState(HasPINState::Instance);}
private:
  HasCardState(){}
  HasCardState(const HasCardState& other) = delete;
  HasCardState& operator=(const HasCardState& other) = delete;
};

class HasPINState : public ATMState {
public:
  static HasPINState& Instance(){
    static HasPINState instance;
    return instance;
  }
  virtual bool Withdraw(ATM* atm,float val){std::cout<<"You have withdrawn "<<val<<std::endl;}
private:
  HasPINState(){}
  HasPINState(const HasPINState& other) = delete;
  HasPINState& operator=(const HasPINState& other) = delete;
};

class ATM{
private:
  ATMState *m_state; // keeps an instance of state class ATMState
  void ChangeState(ATMState *new_state) {m_state = new_state;}
public:
  ATM(){m_state = & NoCardState::Instance();} // initial state is no card
  void InsertCard() {m_state->InsertCard(this);}
  float GetBalance(){return m_state->GetBalance(this);}
  bool Deposit(float val){return m_state->Deposit(this,val);}
  bool Withdraw(float val){return m_state->Withdraw(this,val);}
  bool VerifyPIN(int pinVal){return m_state->VerifyPIN(this,pinVal);}
};

int main(){
  ATM atm;
  atm.Withdraw();
  atm.InsertCard();
  atm.VerifyPin(1234);
  atm.Withdraw(100.50);
}
