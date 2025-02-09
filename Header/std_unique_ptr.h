#include <iostream>
#include <memory.h>
using namespace std ;


template<typename T>
struct CustomDeleter{
    // * Overload operator để huỷ đối tương
    void operator() (T * ptr) const {
        std::cout << "CustomDeleter: deleting object at address " << ptr << std::endl;
        delete ptr; // Hủy đối tượng như std::default_delete
    }
};

class MyClass {
    public:
    MyClass();
    ~MyClass();
};

