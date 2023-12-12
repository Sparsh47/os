#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include <unistd.h>

const int BUFFER_SIZE = 5;

std::queue<int> buffer;
sem_t empty, full, mutex;

void produce(int id)
{
    while (true)
    {
        usleep(1000000); // Simulate some work

        int item = rand() % 100; // Generate a random item

        sem_wait(&empty); // Wait if the buffer is full
        sem_wait(&mutex); // Lock the buffer

        // Produce item and add to buffer
        buffer.push(item);
        std::cout << "Producer " << id << " produces: " << item << std::endl;

        sem_post(&mutex); // Unlock the buffer
        sem_post(&full);  // Signal that buffer is no longer empty
    }
}

void consume(int id)
{
    while (true)
    {
        usleep(2000000); // Simulate some work

        sem_wait(&full);  // Wait if the buffer is empty
        sem_wait(&mutex); // Lock the buffer

        // Consume item from buffer
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumes: " << item << std::endl;

        sem_post(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that buffer is no longer full
    }
}

int main()
{
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Number of empty slots in the buffer
    sem_init(&full, 0, 0);            // Number of items in the buffer
    sem_init(&mutex, 0, 1);           // Mutual exclusion for buffer access

    // Create producer and consumer threads
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < 2; ++i)
    {
        producers.emplace_back(produce, i);
    }

    for (int i = 0; i < 3; ++i)
    {
        consumers.emplace_back(consume, i);
    }

    // Join threads
    for (auto &producer : producers)
    {
        producer.join();
    }

    for (auto &consumer : consumers)
    {
        consumer.join();
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
