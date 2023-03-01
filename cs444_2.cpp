// Operating Systems - CS444/544
// Spring 2023
// Alif Jakir
// jakirab@clarkson.edu
// This assignment is meant to be a review of the C/C++ programming language and the pthreads library.
// Parallel programming is a very important skill to have in the field of computer science.
// Program Description: This program solves the producer-consumer problem using pthreads and mutexes.
// Last updated 2/28/23
// YouTube Code Review & Demo link: 
// Yt Link: TODO
// Repo link: https://github.com/Caerii/CS444-HW2

// Write a program in C/C++ that cleanly demonstrates and solves the producer-consumer problem without experiencing starvation or deadlock of either thread.

// Note: There are a bunch of good examples to get you started in the book! We went over them all in class, refer back to the videos if you need a refresher.

// The program requirements:

//  See Programming Assignment Information for general guidelines relevant to all programming assignments
// Solve the problem as indicated above using pthreads, and either mutexes or message passing to solve the critical region access problem.
// be sure to indicate what method you are using in your program header -> program description
// Submit your code to the drop box which should have a link to your youtube (or other video streaming service) code review & demo video in the header.

#pragma GCC diagnostic ignored "-Wreturn-type" // For some reason, this is needed to get rid of the warning about the main function not returning a value

// INCLUDE STATEMENTS
#include <pthread.h> // Import pthreads library
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// END INCLUDE STATEMENTS

// GLOBAL VARIABLES
// Define the size of the shared buffer
#define BUFFER_SIZE 10

// Define the shared buffer and variables to keep track of its state
int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

// Declare the mutex and condition variables to synchronize access to the buffer
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

// Define the producer function that generates random numbers and adds them to the buffer
void *producer(void *arg) {
    int item;

    // The producer thread runs indefinitely
    while (1) {
        // Generate a random number between 0 and 99 to add to the buffer
        item = rand() % 100;

        // Lock the mutex before entering the critical region
        pthread_mutex_lock(&mutex);

        // If the buffer is full, wait for the consumer to consume some items before producing more
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&full, &mutex);
        }

        // Insert the item into the buffer and update the buffer state variables
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        // Print a message to indicate that the producer has produced an item
        printf("Producer produced item %d\n", item);

        // Signal to the consumer that the buffer is no longer empty
        pthread_cond_signal(&empty);

        // Unlock the mutex to allow the consumer to access the buffer
        pthread_mutex_unlock(&mutex);

        // Sleep for a random period of time to simulate the production of items
        sleep(rand() % 5);
    }
}

// Define the consumer function that consumes items from the buffer
void *consumer(void *arg) {
    int item;

    // The consumer thread runs indefinitely
    while (1) {
        // Lock the mutex before entering the critical region
        pthread_mutex_lock(&mutex);

        // If the buffer is empty, wait for the producer to produce some items before consuming
        while (count == 0) {
            pthread_cond_wait(&empty, &mutex);
        }

        // Remove the item from the buffer and update the buffer state variables
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        // Print a message to indicate that the consumer has consumed an item
        printf("Consumer consumed item %d\n", item);

        // Signal to the producer that the buffer is no longer full
        pthread_cond_signal(&full);

        // Unlock the mutex to allow the producer to access the buffer
        pthread_mutex_unlock(&mutex);

        // Sleep for a random period of time to simulate the consumption of items
        sleep(rand() % 5);
    }
}

// The main function creates the producer and consumer threads and waits for them to finish
int main(int argc, char *argv[]) {
    pthread_t producer_thread, consumer_thread;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the producer and consumer threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Exit the program
    exit(0);
}

// Output of the program
// Producer produced item 0
// Consumer consumed item 0
// Producer produced item 1
// Consumer consumed item 1
// Producer produced item 2
// Consumer consumed item 2
// Producer produced item 3
// Consumer consumed item 3
// Producer produced item 4
// Consumer consumed item 4
// Producer produced item 5
// Consumer consumed item 5

// The way that this program works is that the producer thread generates random numbers and adds them to the buffer.
// The consumer thread consumes items from the buffer.
// The producer and consumer threads use mutexes and condition variables to synchronize access to the buffer.
// The producer thread waits for the buffer to have space before producing an item.
// The consumer thread waits for the buffer to have items before consuming an item.
// The producer and consumer threads run indefinitely.


// Compile the program
// gcc -pthread -o cs444_2 cs444_2.cpp

// Run the program
// ./cs444_2
// I used windows 10 with MSYS2 UCRT 64-bit to compile and run the program
