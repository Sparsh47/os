#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>

// Define the shared resource
int sharedResource = 0;

// Define semaphores and mutex
sem_t rwMutex; // Binary semaphore for controlling access to the resource
sem_t mutex;   // Binary semaphore for controlling access to the readCount variable
int readCount = 0; // Number of readers currently reading

// Function prototypes
void reader(int id);
void writer(int id);

int main() {
    // Initialize semaphores
    sem_init(&rwMutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader and writer threads
    std::thread readers[3];
    std::thread writers[2];

    for (int i = 0; i < 3; ++i) {
        readers[i] = std::thread(reader, i);
    }

    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer, i);
    }

    // Join threads
    for (int i = 0; i < 3; ++i) {
        readers[i].join();
    }

    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    // Destroy semaphores
    sem_destroy(&rwMutex);
    sem_destroy(&mutex);

    return 0;
}

void reader(int id) {
    while (true) {
        usleep(1000000); // Simulate some work

        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&rwMutex); // If it's the first reader, lock the resource
        }
        sem_post(&mutex);

        // Read from the shared resource
        std::cout << "Reader " << id << " reads: " << sharedResource << std::endl;

        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&rwMutex); // If it's the last reader, release the resource
        }
        sem_post(&mutex);
    }
}

void writer(int id) {
    while (true) {
        usleep(2000000); // Simulate some work

        sem_wait(&rwMutex); // Lock the resource for writing

        // Write to the shared resource
        sharedResource++;
        std::cout << "Writer " << id << " writes: " << sharedResource << std::endl;

        sem_post(&rwMutex); // Release the resource
    }
}
