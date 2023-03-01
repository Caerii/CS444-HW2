# Homework-2-CS444
 Producer Consumer Problem with mutexes

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

# Program description
 The way that this program works is that the producer thread generates random numbers and adds them to the buffer.
 The consumer thread consumes items from the buffer.
 The producer and consumer threads use mutexes and condition variables to synchronize access to the buffer.
 The producer thread waits for the buffer to have space before producing an item.
 The consumer thread waits for the buffer to have items before consuming an item.
 The producer and consumer threads run indefinitely.

# Compilation instructions
 Compile the program
 gcc -pthread -o cs444_2 cs444_2.cpp

 Run the program
 ./cs444_2
 I used windows 10 with MSYS2 UCRT 64-bit to compile and run the program

Operating Systems - CS444/544
Spring 2023
Alif Jakir
jakirab@clarkson.edu
This assignment is meant to be a review of the C/C++ programming language and the pthreads library.
Parallel programming is a very important skill to have in the field of computer science.
Program Description: This program solves the producer-consumer problem using pthreads and mutexes.
Last updated 2/28/23
YouTube Code Review & Demo link: 
Yt Link: https://www.youtube.com/watch?v=hG3C_GhvEnk
Repo link: https://github.com/Caerii/CS444-HW2
