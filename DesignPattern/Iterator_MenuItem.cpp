#include <iostream>
#include <string>
#include <vector>
#include <list>

class MenuItem {
public:
  MenuItem(const std::string & description) : m_description(description) {}
  std::string GetDescription() const {return m_description;}
private:
  std::string m_description;
};

// If we don't use Iterator Pattern here
// we may have to expose the actual container
// LunchMenu and DinerMenu are using so that we
// can loop the items. We also need two explicity loops.
// Imagine if we add many different Menus based on holidays
// and seasons.
// The Iterator Pattern here make sure our client, which is the main
// function here, is code against interface instead of implementation.
// Also we can update the container of any Menu class and the client
// won't even know it!
class IteratorInterface {
public:
  IteratorInterface(){}
  virtual ~IteratorInterface(){}
  virtual bool HasNext() const = 0;
  virtual MenuItem GetNext() = 0;
};

class LunchMenu : public IteratorInterface{
public:
  LunchMenu():m_pos(0) {}
  void AddMenuItem(const MenuItem & menu_item) {
    m_items.push_back(menu_item);
  }
  virtual bool HasNext() const { return m_pos != m_items.size();}
  virtual MenuItem GetNext() {return m_items[m_pos++];}
private:
  // The designer of LunchMenu class chosed
  // vector because he need random access;
  std::vector<MenuItem> m_items;
  std::size_t m_pos;
};

class DinerMenu : public IteratorInterface{
public:
  DinerMenu() {
  }
  void AddMenuItem(const MenuItem & menu_item) {
    m_items.push_back(menu_item);
  }
  virtual bool HasNext() const { return !m_items.empty();}
  virtual MenuItem GetNext() {
    MenuItem reval = m_items.front();
    m_items.pop_front();
    return reval;
  }
private:
  // The designer of DinerMenu class chosed list
  // because DinerMenu get updated very frequently.
  std::list<MenuItem> m_items;
};

void PrintMenu(IteratorInterface & iter) {
  while(iter.HasNext()) {
    std::cout << iter.GetNext().GetDescription() << std::endl;
  }
}

int main() {
  LunchMenu lunch_menu;
  lunch_menu.AddMenuItem(MenuItem("Waffles"));
  lunch_menu.AddMenuItem(MenuItem("Omelet"));
  lunch_menu.AddMenuItem(MenuItem("Fruit Salad"));
  lunch_menu.AddMenuItem(MenuItem("Egg Sanwiches"));

  DinerMenu diner_menu;
  diner_menu.AddMenuItem(MenuItem("Steak"));
  diner_menu.AddMenuItem(MenuItem("Hotdog"));
  diner_menu.AddMenuItem(MenuItem("Fried Salmon"));
  diner_menu.AddMenuItem(MenuItem("Chicken wings"));

  std::cout << " Here is the Lunch Menu "<< std::endl;
  PrintMenu(lunch_menu);

  std::cout << " Here is the Diner Menu "<< std::endl;
  PrintMenu(diner_menu);
  return 0;
}
