#pragma once

#include <iostream>
#include <vector>
using namespace std;

class House {
    public:
        std::string walls = "White";
        int prices = 100;
        double ratio = 3.4;
        double PI = 4.13;
        House(){
            cout << "Calling House Constructor ..." <<endl;
        }
        ~House (){
            cout << "Calling House Destructor" << endl;
        }
};
class Base {
public:
    Base (){
        cout << "Calling Base Construcotr ..." << endl;
    }
    ~Base (){
        cout << "Calling Base Destructor ..." << endl;
    }

    /*
        Nếu dùng virtual ~Base()=0; thì sẽ không khởi tạo được đối tượng từ lớp Base này.
        Dùng Hàm huỷ thuần ảo ở lớp Cha, những con trỏ lớp cha trỏ đến lớp con, khi con trỏ lớp cha bị huỷ
        thì chắc chắn con trỏ lớp con cũng bị huỷ, đảm bảo việc quản lý bộ nhớ,
        để những tài nguyên động ở lớp con cũng được thu hồi một cách đúng đắn

        ** Nếu không có virtual destructor thì khi con trỏ của lớp cha trỏ đến lớp con bị huỷ đi
        thì hàm destructor của lớp con không được huỷ, dẫn tới những tài nguyên động của lớp con không được huỷ đi

    */
};

class  Derived : public Base {
    public:
        Derived(){
            cout << "Caliing Derived Constructor ..." << endl;
            house = new House();
            walls = "White";
        };
        ~Derived () {
            cout << "Calling Derived Destructor ..." << endl;
            delete house;
        };
    private:
        House* house;
        std::string walls = "White";
};

class virtual_destructor{

public:
    void run(){
        cout << " ------------------ Pure Virtual Destructor ------------------" << endl;
        Base* obj  = new Derived();
        cout << "Size of obj: " << sizeof(*obj) << endl;
        delete obj;

        cout << " ------------------ Virtual Destructor ------------------" << endl;
        Derived* obj1 = new Derived();
        cout << "Size of obj1: " << sizeof(*obj1) << endl;
        delete obj1;
    };
};  