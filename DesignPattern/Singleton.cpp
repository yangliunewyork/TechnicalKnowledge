/*
  This design pattern and methodology ensures that only one instance of the C++ class is instantiated. 
  It assures that only one object is created and no more. 
  It is often used for a logging class so only one object has access to log files, 
  or when there is a single resource, where there should only be a single object in charge of accessing the single resource. 
*/

/*In general,the thread-safe C++ singleton class goes like this*/
class Singleton {
  Singleton() {}
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
public:
  static Singleton& instance() {
    static Singleton s;
    return s;
  }
};


/* Logger example */
class Logger{
public:
  static Logger& Instance();
  bool openLogFile(std::string logFile);
  void writeToLogFile();
  bool closeLogFile();
private:
  Logger(){};  // Private so that it can  not be called
  Logger(Logger const&) = delete;             
  Logger& operator=(Logger const&) = delete;
  static Logger* m_pInstance;
};
