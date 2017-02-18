#include <memory>

enum PizzaType {
  CHEESE,
  PEPPERONI,
  CLAM,
  VEGGIE
};

class PizzaInterface {};
typedef std::shared_ptr<PizzaInterface> PizzaPtr;

class CheesePizza : public PizzaInterface {};
class PepperoniPizza : public PizzaInterface {};
class ClamPizza : public PizzaInterface {};
class VeggiePizza : public PizzaInterface {} ;

/***
The Simple Factory isn’t actually a Design Pattern; it’s more of a programming idiom.
It is not Factory Method Pattern !
**/
class SimplePizzaFactory {
public:
  SimplePizzaFactory(){}
  PizzaPtr CreatePizza(const PizzaType & pizza_type) {
    switch (pizza_type) {
    case CHEESE : return std::make_shared<CheesePizza>();
    case PEPPERONI : return std::make_shared<PepperoniPizza>();
    case CLAM : return std::make_shared<ClamPizza>();
    case VEGGIE : return std::make_shared<VeggiePizza>();
    default : return nullptr;
    }
  }
};

/***
Here is an example of Factory Method pattern.
NOTICE our lovely virtual method CreatePizza!
It is a method which acts like a factory, which
defer the instantion to sub-classes!
That's why it is called Factory Method pattern!
The switch clause has nothing to do with Factory Method!
***/
class PizzaStore {
public:
  PizzaStore(){}
  virtual ~PizzaStore(){}
  PizzaPtr OrderPizza(const PizzaType & pizza_type) {
    return CreatePizza(pizza_type);
  }
protected:
  // All the responsibility for instantiating Pizzas has been moved
  // into a method that acts as a factory.
  virtual PizzaPtr CreatePizza(const PizzaType & pizza_type) = 0;
};
typedef std::shared_ptr<PizzaStore> PizzaStorePtr;

/* New York Pizza Store */
class NYCheesePizza : public PizzaInterface {};
class NYPepperoniPizza : public PizzaInterface {};
class NYClamPizza : public PizzaInterface {};
class NYVeggiePizza : public PizzaInterface {} ;

class NYPizzaStore : public PizzaStore {
public:
  NYPizzaStore(){}
  virtual ~NYPizzaStore(){}
protected:
  PizzaPtr CreatePizza(const PizzaType & pizza_type) {
    switch (pizza_type) {
    case CHEESE : return std::make_shared<NYCheesePizza>();
    case PEPPERONI : return std::make_shared<NYPepperoniPizza>();
    case CLAM : return std::make_shared<NYClamPizza>();
    case VEGGIE : return std::make_shared<NYVeggiePizza>();
    default : return nullptr;
    }
  }
};

/* Chicago pizza store */
class ChicagoCheesePizza : public PizzaInterface {};
class ChicagoPepperoniPizza : public PizzaInterface {};
class ChicagoClamPizza : public PizzaInterface {};
class ChicagoVeggiePizza : public PizzaInterface {} ;

class ChicagoPizzaStore : public PizzaStore {
public:
  ChicagoPizzaStore(){}
  virtual ~ChicagoPizzaStore(){}
protected:
  PizzaPtr CreatePizza(const PizzaType & pizza_type) {
    switch (pizza_type) {
    case CHEESE : return std::make_shared<ChicagoCheesePizza>();
    case PEPPERONI : return std::make_shared<ChicagoPepperoniPizza>();
    case CLAM : return std::make_shared<ChicagoClamPizza>();
    case VEGGIE : return std::make_shared<ChicagoVeggiePizza>();
    default : return nullptr;
    }
  }
};

int main() {
  PizzaStorePtr ny_store = std::make_shared<NYPizzaStore>();
  PizzaStorePtr chicago_store = std::make_shared<ChicagoPizzaStore>();

  PizzaPtr ny_cheese_pizza_ptr = ny_store->OrderPizza(CHEESE);
  PizzaPtr chicago_cheese_pizza_ptr = chicago_store->OrderPizza(CHEESE);
  return 0;
}
