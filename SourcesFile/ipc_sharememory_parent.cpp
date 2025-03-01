#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

int main() {
    key_t key = ftok("shmfile", 65);
    std::string input_value ;
    while (true)
    {
        std::cout << "Please Enter the string you want to send: "<< std::endl;
        std::cin >> input_value;
        int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
        char *str = (char*) shmat(shmid, nullptr, 0);

        strcpy(str, "Shared Memory IPC");
        std::cout << "Data written: " << str << std::endl;

        shmdt(str);
        /* code */
    }
}
