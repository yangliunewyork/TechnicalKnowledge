/*
Define a family of algorithms, encapsulate each one, and make them interchangeable.
Strategy lets the algorithm vary independently fromclients that use it. 
*/

#include <iostream>

class ICalculate {
public:
  ICalculate(){}
  virtual ~ICalculate(){}
  virtual int Calculate(int value1, int value2) = 0;
};


class Minus : public ICalculate {
public:
  Minus(){}
  ~Minus(){}
  virtual int Calculate(int value1, int value2)
  {
    return value1 - value2;
  }
};

class Add : public ICalculate {
public:
  Add(){}
  ~Add(){}
  virtual int Calculate(int value1, int value2)
  {
    return value1 + value2;
  }
};


class CalculateClient {
public:
  CalculateClient() {}
  void SetCalculate(ICalculate* s) {
    m_strategy = s;
  }
  int Calculate(int l,int r) {
    return m_strategy->Calculate(l,r);
  }
private:
  ICalculate*  m_strategy;
};

int main() {
  CalculateClient client;
  Add add;
  Minus minus;
  client.SetCalculate(&add);
  std::cout << "7 + 1 =  " << client.Calculate(7, 1) << std::endl;
  client.SetCalculate(&minus);
  std::cout << " 7 - 1 =  " << client.Calculate(7, 1) << std::endl;
  return 0;
}


