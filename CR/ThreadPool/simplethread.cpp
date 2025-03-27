#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int a = 0;

void add(int& a) {
    for (int i = 0; i < 100000; i++) {
        mtx.lock();
        a++;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(add, std::ref(a));
    std::thread t2(add, std::ref(a));

    t1.join();
    t2.join();

    std::cout << a << std::endl;

    return 0;
}