
#include "ConcurrentQueueTest.h"
#include "ConcurrentQueue.hpp"

bool ConcurrentQueueTest::testQueue(int num_producers, int num_consumers, int num_ints) {

    std::vector<std::thread> vecOfThreads(num_producers + num_consumers);
    ConcurrentQueue<int> concurrentQueue;

    // producers
    for (int i = 0; i < num_producers; i++) {
        vecOfThreads[i] = std::thread([&concurrentQueue, num_ints]() {
            for (int k = 0; k <= num_ints; k++) {
                concurrentQueue.enqueue(k);
            }
        });
    }

    // consumers
    for (int i = num_producers; i < (num_consumers + num_producers); i++) {
        vecOfThreads[i] = std::thread([&concurrentQueue, num_ints]() {
            for (int k = 0; k <= num_ints; k++) {
                concurrentQueue.dequeue(&k);
            }
        });
    }

    for (auto &thread: vecOfThreads) {
        thread.join();
    }

    int verification = (num_producers - num_consumers) * num_ints;
    if (concurrentQueue.size() == verification) {
        std::cout << "test passed\n";
        return true;
    }
    std::cout << "test failed\n";
    std::cout << "Queue size: " << concurrentQueue.size() << "\n";
    return false;
}
