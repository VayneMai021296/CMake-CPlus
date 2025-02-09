#include <iostream>
#include "Header/virtual_destructor.h"
#include "Header/std_unique_ptr.h"

using namespace std ;

int main(int argc, char* argv[]){
    
    virtual_destructor vir;
    vir.run();

    {
        std::cout << " ------------------------------ Unique Pointer Example ------------------------------ "<<std::endl;
        // ? Sử dụng std::unique_ptr với custom deleter
        std::unique_ptr<MyClass, CustomDeleter<MyClass>> ptr(new MyClass(), CustomDeleter<MyClass>());
        std::cout << "Address of ptr: " << ptr.get() << std::endl;
        // ? Ở đây, ptr sở hữu đối tượng MyClass
        std::cout << "Trong phạm vi của khối, đối tượng đang được quản lý.\n";
    }
    
    return 0;
}
