#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

/***
    Notice how Token,Operand,Operator classes. share the same interface here.
    This can help us avoid casting.
    However,it is NOT composite pattern since we are not treating a group of objects 
    the same way as a single instance of an object.
***/

// Forward declaration
class Token;
typedef std::shared_ptr<Token> TokenPtr;


class Token {
public:
  Token(){}
  virtual ~Token() {}
  virtual bool IsOperator() const = 0;
  virtual void Execute(std::vector<TokenPtr> & tokens) = 0;
  virtual double GetValue() const {return 0;}
  virtual void SetValue(double value) {} // do nothing
};


class Operand : public Token {
public:
  Operand(double value) : m_value(value) {}
  virtual ~Operand() {}
  virtual bool IsOperator() const {return false;}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    tokens.push_back(std::make_shared<Operand>(m_value));
  }
  virtual double GetValue() const  { return m_value;}
  virtual void SetValue(double value) {m_value = value;}
private:
  double m_value;
};

class Operator : public Token{
public:
  Operator() {}
  virtual ~Operator() {}
  virtual bool IsOperator() const {return true;}
};

class Add : public Operator {
public:
  Add() {}
  virtual ~Add() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    TokenPtr right_operand_ptr = tokens.back();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() + right_operand_ptr->GetValue());
  }
};

class Sub : public Operator {
public:
  Sub() {}
  virtual ~Sub() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    TokenPtr right_operand_ptr = tokens.back();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() - right_operand_ptr->GetValue());
  }
};

class Mul : public Operator {
public:
  Mul() {}
  virtual ~Mul() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
   TokenPtr right_operand_ptr = tokens.back();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() * right_operand_ptr->GetValue());
  }
};

class Div : public Operator {
public:
  Div() {}
  virtual ~Div() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    TokenPtr right_operand_ptr = tokens.back();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() / right_operand_ptr->GetValue());
  }
};

/***
    Factory Method.
Here we define an interface Creator for creating operator,
but let subclasses decide which operator to instantiate.
Notice how the Creator interface defer the instantiation to its
sub-classes by using the abstract method Create() ?
That's why its called Factory Method pattern, not Factory pattern.
***/
class Creator {
public:
  Creator() {}
  virtual ~Creator() {}
  virtual TokenPtr Create() = 0 ; // Factory method
};
typedef std::shared_ptr<Creator> CreatorPtr;

class AddCreator : public Creator {
public:
  AddCreator() {}
  virtual ~AddCreator() {}
  virtual TokenPtr Create() { TokenPtr reval =  std::make_shared<Add>(); return reval;}
};

class SubCreator : public Creator {
public:
  SubCreator() {}
  virtual ~SubCreator() {}
  virtual TokenPtr Create() { TokenPtr reval =  std::make_shared<Sub>(); return reval;}
};

class DivCreator : public Creator {
public:
  DivCreator() {}
  virtual ~DivCreator() {}
  virtual TokenPtr Create() { TokenPtr reval =  std::make_shared<Div>(); return reval;}
};

class MulCreator : public Creator {
public:
  MulCreator() {}
  virtual ~MulCreator() {}
  virtual TokenPtr Create() { TokenPtr reval =  std::make_shared<Mul>(); return reval;}
};

/***
    Simple Factory pattern.
This is not a design pattern, at least it is not in GoF book.
***/
class Factory {
public:
  Factory() {}

  TokenPtr GetToken(const std::string & str) {
    TokenPtr reval;
    if (m_mapper.count(str)==0) {
      reval = std::make_shared<Operand>(std::stod(str));
    } else {
      reval = m_mapper[str]->Create();
    }
    return reval;
  }

  void Register(const std::string & str, const CreatorPtr & creator_ptr) {
    if (creator_ptr) {
      m_mapper[str] = creator_ptr;
    }
  }
private:
  std::unordered_map<std::string,CreatorPtr> m_mapper;
};


double EvalRPN(std::vector<std::string> & strs) {
  CreatorPtr add_creator = std::make_shared<AddCreator>();
  CreatorPtr sub_creator = std::make_shared<SubCreator>();
  CreatorPtr mul_creator = std::make_shared<MulCreator>();
  CreatorPtr div_creator = std::make_shared<DivCreator>();

  std::vector<TokenPtr> tokens;

  Factory factory;
  factory.Register("+",add_creator);
  factory.Register("-",sub_creator);
  factory.Register("*",mul_creator);
  factory.Register("/",div_creator);

  for (const std::string & str : strs) {
    factory.GetToken(str)->Execute(tokens);
  }

  return tokens.back()->GetValue();
}

int main() {
  std::vector<std::string> tokens = {"3","2","-"};
  std::cout << EvalRPN(tokens) << std::endl;

  tokens = {"3","2","5","/","+","2","4","*","-"};
  std::cout << EvalRPN(tokens) << std::endl;

  return 0;
}
