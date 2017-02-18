#include <memory>
#include <iostream>
#include <string>

// Abstract class 
class Beverage {
public:
  Beverage() : m_description("Unkown Beverage"){}
  
  virtual ~Beverage(){}
  
  virtual std::string GetDescription() const  {
    return m_description;
  }
  
  virtual double GetCost() const = 0;
  
protected:
  std::string m_description;
};
typedef std::shared_ptr<Beverage> BeveragePtr;

class CondimentDecorator : public Beverage {
public:
  CondimentDecorator(){}
  virtual ~CondimentDecorator(){}
};

class Espresso : public Beverage {
public :
  Espresso() { m_description = "Espresso";}
  virtual double GetCost() const { return 1.99;}
};

class HouseBlend : public Beverage {
public :
  HouseBlend() { m_description = "HouseBlend";}
  virtual double GetCost() const { return 0.89;}
};

class DarkRoast : public Beverage {
public :
  DarkRoast() { m_description = "DarkRoast";}
  virtual double GetCost() const { return 0.91;}
};

class Chocolate : public CondimentDecorator {
public:
  Chocolate(const BeveragePtr & beverage_ptr) {
    m_beverage_ptr = beverage_ptr;
  }
  virtual std::string GetDescription() const {
    return m_beverage_ptr->GetDescription() + ", Chocolate";
  }
  virtual double GetCost() const { return 0.2 + m_beverage_ptr->GetCost();}
private:
  BeveragePtr m_beverage_ptr;
};

class Soy : public CondimentDecorator {
public:
  Soy(const BeveragePtr & beverage_ptr) {
    m_beverage_ptr = beverage_ptr;
  }
  virtual std::string GetDescription() const {
    return m_beverage_ptr->GetDescription() + ", Soy";
  }
  virtual double GetCost() const { return 0.1 + m_beverage_ptr->GetCost();}
private:
  BeveragePtr m_beverage_ptr;
};

class Whip : public CondimentDecorator {
public:
  Whip(const BeveragePtr & beverage_ptr) {
    m_beverage_ptr = beverage_ptr;
  }
  virtual std::string GetDescription() const {
    return m_beverage_ptr->GetDescription() + ", Whip";
  }
  virtual double GetCost() const { return 0.3 + m_beverage_ptr->GetCost();}
private:
  BeveragePtr m_beverage_ptr;
};

int main() {
  // Order an espresso, add nothing
  BeveragePtr beverage_ptr =  std::make_shared<Espresso>();
  std::cout << beverage_ptr->GetDescription() << " $" << beverage_ptr->GetCost() << std::endl;

  // Order DarkRoast, add double Chocolate and Whip
  beverage_ptr = std::make_shared<DarkRoast>();
  beverage_ptr = std::make_shared<Chocolate>(beverage_ptr);
  beverage_ptr = std::make_shared<Chocolate>(beverage_ptr);
  beverage_ptr = std::make_shared<Whip>(beverage_ptr);
  std::cout << beverage_ptr->GetDescription() << " $" << beverage_ptr->GetCost() << std::endl;
  
  // Order HouseBlend, add soy, chocolate and whip
  beverage_ptr = std::make_shared<HouseBlend>();
  beverage_ptr = std::make_shared<Soy>(beverage_ptr);
  beverage_ptr = std::make_shared<Chocolate>(beverage_ptr);
  beverage_ptr = std::make_shared<Whip>(beverage_ptr);
  std::cout << beverage_ptr->GetDescription() << " $" << beverage_ptr->GetCost() << std::endl;
  
  return 0;
}
