#include <unordered_set>
#include <memory>
#include <iostream>

class ObserverInterface; // Forward declaration
typedef ObserverInterface* ObserverPtr;

// Subject Interface
class SubjectInterface {
public:
  SubjectInterface(){}
  virtual ~SubjectInterface() {}
  virtual void RegisterObserver(const ObserverPtr & ob) = 0;
  virtual void RemoveObserver(const ObserverPtr & ob) = 0;
  virtual void NotifyObservers() = 0;
};

// Observer Interface
class ObserverInterface {
public:
  ObserverInterface(){}
  virtual ~ObserverInterface(){}
  virtual void Update(float temp, float humidity, float pressure) = 0;
};


class WeatherData : public SubjectInterface {
public:
  WeatherData(){}
  virtual ~WeatherData(){}
  void SetMeasurement(float temperature, float humidity, float pressure) {
    this->m_temperature = temperature;
    this->m_humidity = humidity;
    this->m_pressure = pressure;
    this->NotifyObservers();// Notify observers if state changes
  }
  
  virtual void RegisterObserver(const ObserverPtr & ob_ptr) {
    m_observers.insert(ob_ptr);
  }
  
  virtual void RemoveObserver(const ObserverPtr & ob_ptr) {
    m_observers.erase(ob_ptr);
  }
  
  virtual void NotifyObservers() {
    for (auto iter = m_observers.begin(); iter!=m_observers.end();++iter) {
      (*iter)->Update(m_temperature,m_humidity,m_pressure);
    }
  }
private:
  // You can use any container to store observers.
  std::unordered_set<ObserverPtr> m_observers;
  float m_temperature;
  float m_humidity;
  float m_pressure;
};

class DisplayWebApp : public ObserverInterface {
public:
  DisplayWebApp(){}
  virtual ~DisplayWebApp(){}
  virtual void Update(float temp, float humidity, float pressure) {
    m_temperature = temp, m_humidity = humidity, m_pressure = pressure;
    std::cout <<"DisplayWebApp : "<<"Updated weather -- temperature="<< m_temperature
              << ", humidity=" << m_humidity << ", pressure=" << m_pressure << std::endl;
  }
private:
  float m_temperature,m_humidity,m_pressure;
};
  
int main() {
  WeatherData weather_data;
  weather_data.SetMeasurement(80, 65, 30.4);
  DisplayWebApp display_web_app;
  weather_data.RegisterObserver(&display_web_app);
  weather_data.SetMeasurement(80, 64, 30.4);
  weather_data.SetMeasurement(80, 61, 30.4);
}
