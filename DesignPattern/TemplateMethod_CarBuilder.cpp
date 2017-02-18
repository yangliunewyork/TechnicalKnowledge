/*
Define the skeleton of an algorithm in an operation, deferring somesteps to
subclasses. Template Method lets subclasses redefinecertain steps of an algorithm
without changing the algorithm'sstructure. 
*/

class CarBuilder {
public:
  CarBuilder(){}
  ~CarBuilder(){}
  void BuildCar() {
    BuildSkeleton();
    AddEngine();
    // other
  }
protected:
  virtual BuildSkeleton() = 0;
  virtual AddEngine() = 0;
  // Other
};

class PorcheBuilder : public CarBuilder {
public:
  PorcheBuilder(){}
  ~PorcheBuilder(){}
  virtual BuildSkeleton() {
    std::cout << "Building Porche Skeleton" << std::endl;
  }
  virtual AddEngine() {
    std::cout << "Adding Porche Skeleton" << std::endl;
  }
};

class LamborghiniBuilder : public CarBuilder {
public:
  LamborghiniBuilder(){}
  ~LamborghiniBuilder(){}
  virtual BuildSkeleton() {
    std::cout << "Building Lamborghini Skeleton" << std::endl;
  }
  virtual AddEngine() {
    std::cout << "Adding Lamborghini Skeleton" << std::endl;
  }
};
