#include <iostream>
#include <memory>
#include <vector>


enum VehicleType{
  LARGE,
  MEDIUM,
  SMALL,
  HANDICAPPED
};

class ParkingSpace;
typedef std::shared_ptr<ParkingSpace> ParkingSpacePtr;
class ParkingLot;
typedef std::shared_ptr<ParkingLot> ParkingLotPtr;

class ParkingSpace {
  friend class ParkingLot;
public:
  ParkingSpace(const VehicleType & type) : m_vehicle_type(type),m_is_occupied(false) {
  }
  bool IsOccupied() const {return m_is_occupied;}
  VehicleType GetVehicleType() const {return m_vehicle_type;}
  void SetOccupied(bool val) {
    m_is_occupied = val;
  }
private:
  VehicleType m_vehicle_type;
  bool m_is_occupied;
};

class Car {
public:
  Car(const VehicleType & type) : m_vehicle_type(type){
  }
  void Park(ParkingSpacePtr & parking_space) {
    if (!m_parking_space) { // Can't occupy two slots, can't it?
      m_parking_space = parking_space;
      m_parking_space->SetOccupied(true);
    }
  }
  void UnPark() {
    m_parking_space->SetOccupied(false);
    m_parking_space = nullptr;
  }
  VehicleType GetVehicleType() const {
    return m_vehicle_type;
  }
private:
  VehicleType m_vehicle_type;
  ParkingSpacePtr m_parking_space;
};
typedef std::shared_ptr<Car> CarPtr;


class ParkingLot {
  friend class ParkingLotBuilder;
public:
  ParkingLot() {
  }
  ParkingSpacePtr FindSpace(const VehicleType & type) {
    for (std::size_t i=0;i<m_parking_spaces.size();++i) {
      if (m_parking_spaces[i]->GetVehicleType() == type && !m_parking_spaces[i]->IsOccupied()) {
        return m_parking_spaces[i];
      }
    }
    return nullptr;
  }
private:
  void AddParkingSpace(const ParkingSpacePtr & parking_space) {
    m_parking_spaces.push_back(parking_space);
  }
  std::vector<ParkingSpacePtr> m_parking_spaces;
};


//Builder pattern: build the complex parking lot step by step.
class ParkingLotBuilder {
public:
  ParkingLotBuilder(){
    m_parking_lot_ptr = std::make_shared<ParkingLot>();
  }
  ParkingLotPtr GetParkingLot() {
    return m_parking_lot_ptr;
  }
  void AddParkingSpace(std::size_t num, const VehicleType & type) {
    for (std::size_t i=0;i<num;++i) {
      m_parking_lot_ptr->AddParkingSpace(std::make_shared<ParkingSpace>(type));
    }
  }
private:
  ParkingLotPtr m_parking_lot_ptr;
};

int main() {
  ParkingLotBuilder parking_lot_builder;
  parking_lot_builder.AddParkingSpace(2,MEDIUM);
  parking_lot_builder.AddParkingSpace(1,SMALL);
  parking_lot_builder.AddParkingSpace(1,LARGE);
  parking_lot_builder.AddParkingSpace(1,HANDICAPPED);
  ParkingLotPtr parking_lot  = parking_lot_builder.GetParkingLot();

  CarPtr large_car = std::make_shared<Car>(LARGE);
  ParkingSpacePtr empty_slot = parking_lot->FindSpace(large_car->GetVehicleType());
  if (empty_slot) {
    large_car->Park(empty_slot);
    std::cout << "large car one has been parked" << std::endl;
  }
  empty_slot = parking_lot->FindSpace(LARGE);
  if (!empty_slot) std::cout << "No Large slot available" << std::endl;
  large_car->UnPark();
  empty_slot = parking_lot->FindSpace(LARGE);
  if (empty_slot) std::cout << "Large slot available" << std::endl;
  return 0;
}
