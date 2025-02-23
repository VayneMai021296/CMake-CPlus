#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, nullptr, 0);

    std::cout << "Data read: " << str << std::endl;
    
    shmdt(str);
    shmctl(shmid, IPC_RMID, nullptr); // Xóa shared memory
    return 0;
}
