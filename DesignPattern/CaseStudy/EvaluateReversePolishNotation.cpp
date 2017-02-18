#include <stack>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <vector>
#include <cassert>

// Here we are using Interpreter Pattern and Composite Pattern
class Operator{
public:
  virtual ~Operator(){}
  virtual double GetResult(double left,double right)=0;
};

class Add : public Operator{
public:
  double GetResult(double left,double right){
    return left+right;
  }
};

class Sub : public Operator{
public:
  double GetResult(double left,double right){
    return left-right;
  }
};

class Mul : public Operator{
public:
  double GetResult(double left,double right){
    return left*right;
  }
};

class Div : public Operator{
public:
  double GetResult(double left,double right){
    return left/right;
  }
};

typedef std::shared_ptr<Operator> OperatorPtr;


class OperatorFactory{
public:
  OperatorFactory(){
    operator_mapper["+"] = std::make_shared<Add>();
    operator_mapper["-"] = std::make_shared<Sub>();
    operator_mapper["*"] = std::make_shared<Mul>();
    operator_mapper["/"] = std::make_shared<Div>();
  }

  float Calculate(float f1,float f2,std::string s){
    return operator_mapper[s]->GetResult(f1,f2);
  }
private:
  std::unordered_map<std::string,OperatorPtr> operator_mapper;
};
typedef std::shared_ptr<OperatorFactory> OperatorFactoryPtr;

class Calculator {
public:
  Calculator(){}
  double Calculate(const std::vector<std::string> & tokens) const {
    std::stack<double> operands;
    for (const std::string & token : tokens) {
      if (token.size()==1 && !std::isdigit(token[0])) {
        double right = operands.top();
        operands.pop();
        double left = operands.top();
        operands.pop();
        operands.push(m_operator_factory->Calculate(left,right,token));
      } else {
        // it is a number,push it into stack
        operands.push(std::stoi(token));
      }
    }
    return operands.top();
  }
  void SetOperatorFactory(const OperatorFactoryPtr& operator_factory_ptr) {
    m_operator_factory = operator_factory_ptr;
  }
private:
  OperatorFactoryPtr m_operator_factory;
};

void UnitTest() {
  Calculator calculator;
  OperatorFactoryPtr factory_ptr = std::make_shared<OperatorFactory>();
  calculator.SetOperatorFactory(factory_ptr);
  std::vector<std::string> tokens = {"3","2","5","/","+","2","4","*","-"};
  std::cout << calculator.Calculate(tokens)  << std::endl;
  //  assert (calculator.Calculate(tokens) == -4.6 );                                                
  tokens = {"4","3","2","-","1","+","*"};
  std::cout << calculator.Calculate(tokens) << std::endl;

}

int main() {
  UnitTest();
  return 0;
}
