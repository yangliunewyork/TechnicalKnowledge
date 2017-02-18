#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

// in order for the composite to work transparently to the client,
// you must implement the same interface for all objects in the composite,
// otherwise, the client has to worry about which interface each object
// is implementing, which kind of defeats the purpose. Obviously that means that at times
// you’ll have objects for which some of the method calls don’t make sense.

class MenuComponent {
public:
  MenuComponent() {}
  virtual ~MenuComponent(){}
  virtual void Print() const {} // do nothing
  virtual std::string GetDescription() {return "";} // return empty string
  virtual void AddMenuComponent(const MenuComponentPtr & item) {} // do nothing
};
typedef std::shared_ptr<MenuComponent> MenuComponentPtr;

class MenuItem : public MenuComponent {
public:
  MenuItem(const std::string & description) : m_description(description) {}
  virtual std::string GetDescription() const {return m_description;}
  virtual void Print() const {std::cout << m_description << std::endl;}
private:
  std::string m_description;
};

class Menu : public MenuComponent {
public:
  Menu(const std::string & description) : m_description(description) {}
  std::string GetDescription() const {return m_description;}
  virtual void AddMenuComponent(const MenuComponentPtr & item) {m_sub_items.push_back(item);}
  virtual void Print() const {
    std::cout << "###" << m_description << "###" << std::endl;
    for (const MenuComponentPtr & sub_item : m_sub_items) {
      sub_item->Print();
    }
  }
private:
  std::string m_description;
  // It can has any number of MenuComponent
  std::list<MenuComponentPtr> m_sub_items;
};
typedef std::shared_ptr<Menu> MenuPtr;

int main() {
  MenuPtr lunch_menu_ptr = std::make_shared<Menu>("Lunch");
  
  lunch_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Waffles"));
  lunch_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Omelet"));
  lunch_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Fruit Salad"));
  lunch_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Egg Sanwiches"));

  MenuPtr diner_menu_ptr = std::make_shared<Menu>("Diner");
  diner_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Steak"));
  diner_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Hotdog"));
  diner_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Fried Salmon"));
  diner_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Chicken wings"));

  MenuPtr dessert_menu_ptr = std::make_shared<Menu>("Dessert");
  dessert_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Tiramisu"));
  dessert_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Cheesecake"));
  dessert_menu_ptr->AddMenuComponent(std::make_shared<MenuItem>("Macaron"));
  

  diner_menu_ptr->AddMenuComponent(dessert_menu_ptr);
  
  std::cout << "### Here is the Lunch Menu ###"<< std::endl;
  lunch_menu_ptr->Print();

  std::cout << "\n\n\n";
  
  std::cout << "### Here is the Diner Menu ###"<< std::endl;
  diner_menu_ptr->Print();
  
  return 0;
}
