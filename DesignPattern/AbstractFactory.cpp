#include <memory>

enum PizzaType {
  CHEESE,
  PEPPERONI,
  CLAM,
  VEGGIE
};

class Dough;
class Sauce;
class Cheese;
class Pepperoni;
typedef std::shared_ptr<Dough> DoughPtr;
typedef std::shared_ptr<Sauce> SaucePtr;
typedef std::shared_Ptr<Cheese> CheesePtr;
typedef std::shared_ptr<Pepperoni> PepperoniPtr;

class PizzaIngredientFactoryInterface {
public:
  PizzaIngredientFactoryInterface(){}
  virtual ~PizzaIngredientFactoryInterface{}
  virtual DoughPtr CreateDough() = 0;
  virtual SaucePtr CreateSauce() = 0;
  virtual CheesePtr CreateCheese() = 0;
  virtual Pepperoni CreatePepperoni() = 0;
};
typedef std::shared_ptr<PizzaIngredientFactoryInterface> PizzaIngredientFactoryPtr;

class PizzaInterface {};
typedef std::shared_ptr<PizzaInterface> PizzaPtr;

class CheesePizza : public PizzaInterface {
public:
  CheesePizza(const PizzaIngredientFactoryPtr & factory_ptr){
    m_factory_ptr = factory_ptr;
  }
private:
  PizzaIngredientFactoryPtr m_factory_ptr;
};

class PepperoniPizza : public PizzaInterface {
public:
  PepperoniPizza(const PizzaIngredientFactoryPtr & factory_ptr){
    m_factory_ptr = factory_ptr;
  }
private:
  PizzaIngredientFactoryPtr m_factory_ptr;
};
class ClamPizza : public PizzaInterface {};
class VeggiePizza : public PizzaInterface {} ;

/***
Here is an example of factory pattern.
What we're going to do is pub the CreatePizza method into PizzaStore,
but this time as an abstract method.
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
    case CHEESE : return std::make_shared<NYCheesePizza>(PizzaIngredientFactoryPtr);
    case PEPPERONI : return std::make_shared<NYPepperoniPizza>(PizzaIngredientFactoryPtr);
    case CLAM : return std::make_shared<NYClamPizza>(PizzaIngredientFactoryPtr);
    case VEGGIE : return std::make_shared<NYVeggiePizza>(PizzaIngredientFactoryPtr);
    default : return nullptr;
    }
  }
  PizzaIngredientFactoryPtr m_ingredient_factory_ptr;
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

// New York ingredient factory. It specializes in Marinara sauce, Reggiano Cheese,...
class ThinCrustDough;
class MarinaraSauce;
class ReggianoCheese;
class SlicedPepperoni;
class NYPizzaIngredientFactory : public PizzaIngredientFactoryInterface {
public:
  NYPizzaIngredientFactory(){}
  virtual ~NYPizzaIngredientFactory{}
  virtual DoughPtr CreateDough() { return std::make_shared<ThinCrustDough>();}
  virtual SaucePtr CreateSauce()  { return std::make_shared<MarinaraSauce>();}
  virtual CheesePtr CreateCheese() { return std::make_shared<ReggianoCheese>();}
  virtual Pepperoni CreatePepperoni() { return std::make_shared<SlicedPepperoni>();}
};



int main() {
  PizzaStorePtr ny_store = std::make_shared<NYPizzaStore>();
  PizzaStorePtr chicago_store = std::make_shared<ChicagoPizzaStore>();

  PizzaPtr ny_cheese_pizza_ptr = ny_store->OrderPizza(CHEESE);
  PizzaPtr chicago_cheese_pizza_ptr = chicago_store->OrderPizza(CHEESE);
  return 0;
}
