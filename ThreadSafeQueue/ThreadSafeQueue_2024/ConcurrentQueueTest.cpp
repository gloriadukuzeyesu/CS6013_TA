#include "ConcurrentQueue.hpp"
#include <vector>
#include <iostream>
#include <thread>         // std::thread

void producerThreadFunction(ConcurrentQueue<int> concurrentQueue, int num_ints)
{
    // role for each producer thread
    for (int i = 0; i < num_ints; i++)
    {
        concurrentQueue.enqueue(i);
    }
}

void consumerThreadFunction(ConcurrentQueue<int> concurrentQueue, int num_ints)
{
    // role for each consumer thread
    for (int i = 0; i < num_ints; i++)
    {
        concurrentQueue.dequeue(&i);
    }
}

bool testQueue(int num_producers, int num_consumers, int num_ints) {

    int verification = (num_producers - num_consumers) * num_ints; // will be used to verify
    std::cout << "Verification " << verification << "\n"; 

    // a&&b. create a vector of threads
    std::vector<std::thread> vectorOfThreads(num_producers + num_consumers);
    // std::vector<std::thread> consumers(num_consumers);

    // c. Create a ConcurrentQueue object statically.
    ConcurrentQueue<int> concurrentQueue;

    // d. Create num_producer producer threads that enqueue num_ints ints into the ConcurrentQueue.
    for (int j = 0; j < num_producers; j++)
    {

        // using lamda function 
        vectorOfThreads[j] = std::thread([&concurrentQueue, num_ints]() {
                for(int i = 0; i < num_ints; i++) {
                    concurrentQueue.enqueue(i); 
                } });


        // TODO using function ---- NOT WORKING 
        // vectorOfThreads.push_back(std::thread(producerThreadFunction, concurrentQueue, num_ints)); 
    }

   // std::cout << "done enqueuing and queue size is : " << concurrentQueue.size() << "\n";

    // e. Create num_consumer consumer threads that dequeue num_ints ints from the ConcurrentQueue.
    for (int j = num_producers; j < (num_consumers + num_producers); j++)
    {
        vectorOfThreads[j] = std::thread([&concurrentQueue, num_ints]() {
                for(int i = 0; i < num_ints; i++) {
                    concurrentQueue.dequeue(&i); 
                } });
        // TODO Fix me => use a fx instead of lamda fx
        // vectorOfThreads.push_back(std::thread(consumerThreadFunction, concurrentQueue, num_ints)); 
        // vectorOfThreads[j] = std::thread(consumerThreadFunction, concurrentQueue, num_ints);

    }

    //std::cout << "done dequeing and queue size is : " << concurrentQueue.size() << "\n";

    // f.Wait for all threads to join (ie, finish).
    for (auto &thread: vectorOfThreads) {
        thread.join();
    }

    // another way of doing for each loop inline.
    // std::for_each(vectorOfThreads.begin(), vectorOfThreads.end(), [](std::thread &currentThread)
    //               { currentThread.join(); });

    if (verification == concurrentQueue.size()) {
        std::cout << "Test Passed\n" << "Verif: " << verification << "\nQueue size: " << concurrentQueue.size() << "\n";
        return true;
    } else{
        std::cout << "Test Failed \n" << "Verif: " << verification << "\nQueue size: " << concurrentQueue.size() << "\n";
    }
    // g. verification
    return false;
}
// the goal is
// to compare is the number of element in the queue is equal to (num_producer - num_consumer) * num_ints

void testSimpleInts()
{

    ConcurrentQueue<int> concurrentQueue;
    for (int i = 1; i < 5; i++)
    {
        concurrentQueue.enqueue(i);
    }

    std::cout << "Size: " << concurrentQueue.size() << "\n";
    std::cout << "Head: " << concurrentQueue.getHead() << "\n";
    std::cout << "Tail: " << concurrentQueue.getTail() << "\n";

    int ret;

    concurrentQueue.dequeue(&ret);
    concurrentQueue.dequeue(&ret);
    concurrentQueue.dequeue(&ret);

    concurrentQueue.dequeue(&ret);
    concurrentQueue.dequeue(&ret);

    std::cout << "After dequeing\n";
    std::cout << "Size: " << concurrentQueue.size() << "\n";
    std::cout << "Head: " << concurrentQueue.getHead() << "\n";
    std::cout << "Tail: " << concurrentQueue.getTail() << "\n";
}
int main(int argc, char **argv)
{

    // testSimpleInts();

    // testQueue();

    int num_producers;
    int num_consumers;
    int num_ints;
    if (argc == 4)
    {
        num_producers = atoi(argv[1]);
        num_consumers = atoi(argv[2]);
        num_ints = atoi(argv[3]);
        std::cout << "you provided num_producers: " << num_producers
                  << " num_consumers: " << num_consumers
                  << " num_ints: " << num_ints << std::endl;

        bool res = testQueue(num_producers, num_consumers, num_ints);

        std::cout << "TEST: " << std::boolalpha << res << std::endl;
    }
    else
    {
        std::cout << "Invalid argument\n";
    }
}