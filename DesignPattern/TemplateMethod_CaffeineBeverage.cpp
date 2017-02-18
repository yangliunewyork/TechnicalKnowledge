#include <iostream>

// Abstract classs.
class CaffeineBeverage {
public:
  CaffeineBeverage() {}
  virtual ~CaffeineBeverage() {}
  // PrepareRecipe is the template method here since it serves as a template
  // for an algorithm, in this case, an algorithm for making caffeinated bevarages.
  // We should put a final keyword if we are using Java
  // since it should not be overriden.
  void PrepareRecipe() {
    BoilWater();
    Brew();
    PourInCup();
    AddCondiments();
  }
  void BoilWater() { std::cout << "Boiling water" << std::endl;}
  void PourInCup() { std::cout << "Pour in cup" << std::endl;}
  virtual void Brew() = 0;
  virtual void AddCondiments() = 0;
};

class Tea : public CaffeineBeverage {
public:
  Tea() {}
  virtual ~Tea(){}
  virtual void Brew() {std::cout << "Steeping the tea" << std::endl;}
  virtual void AddCondiments() {std::cout << "Adding Lemon" << std::endl;}
};

class Coffee : public CaffeineBeverage {
public:
  Coffee() {}
  virtual ~Coffee(){}
  virtual void Brew() {std::cout << "ripping Coffee through filter" << std::endl;}
  virtual void AddCondiments() {std::cout << "Adding Sugar and Milk" << std::endl;}
};

int main() {
  Tea tea;
  Coffee coffee;
  std::cout << "### Making tea ###" << std::endl;
  tea.PrepareRecipe();
  std::cout << "### Making coffee ###" << std::endl;
  coffee.PrepareRecipe();
  return 0;
}





