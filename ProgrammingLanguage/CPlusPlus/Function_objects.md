In computer programming, a __function object__ is a construct allowing an object to be invoked or called as if it were an ordinary function, usually with the same syntax (a function parameter that can also be a function). Function objects are often called __functors__.

### Description

A typical use of a function object is in writing callback functions. A callback in procedural languages, such as C, may be performed by using function pointers. However it can be difficult or awkward to pass a state into or out of the callback function. This restriction also inhibits more dynamic behavior of the function. A function object solves those problems since the function is really a façade for a full object, carrying its own state.

In C++, a function object may be used instead of an ordinary function by defining a class that overloads the function call operator by defining an operator() member function. In C++, this may appear as follows:

```cpp
// comparator predicate: returns true if a < b, false otherwise
struct IntComparator
{
  bool operator()(const int &a, const int &b) const
  {
    return a < b;
  }
};

int main()
{
    std::vector<int> items { 4, 3, 1, 2 };
    std::sort(items.begin(), items.end(), IntComparator());
    return 0;
}
```

Notice that the syntax for providing the callback to the std::sort() function is identical, but an object is passed instead of a function pointer. When invoked, the callback function is executed just as any other member function, and therefore has full access to the other members (data or functions) of the object. Of course, this is just a trivial example. To understand what power a functor provides more than a regular function, consider the common use case of sorting objects by a particular field. In the following example, a functor is used to sort a simple employee database by each employee's ID number.

```cpp
struct CompareBy
{
    const std::string SORT_FIELD;
    CompareBy(const std::string& sort_field="name")
      : SORT_FIELD(sort_field)
    {
        /* validate sort_field */
    }
    
    bool operator()(const Employee& a, const Employee& b)
    {
        if (SORT_FIELD == "name")
            return a.name < b.name;
        else if (SORT_FIELD == "age")
            return a.age < b.age;
        else if (SORT_FIELD == "idnum")
            return a.idnum < b.idnum;
        else
            /* throw exception or something */
    }
};

int main()
{
    std::vector<Employee> emps;
    
    /* code to populate database */
    
    // Sort the database by employee ID number
    std::sort(emps.begin(), emps.end(), CompareBy("idnum"));
    
    return 0;
}
```

In C++11, the lambda expression provides a more succinct way to do the same thing.

```cpp
int main()
{
    std::vector<Employee> emps;
    /* code to populate database */
    const std::string sort_field = "idnum";
    std::sort(emps.begin(), emps.end(), [&sort_field](const Employee& a, const Employee& b){ /* code to select and compare field */ });
    return 0;
}
```

