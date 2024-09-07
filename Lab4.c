#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "configure_interrupt.c"

// Thread and Events libs
#include <pthread.h> 
#include <sys/epoll.h> // Add this line to import the necessary function declaration

// Function to be executed by the thread
void epollThread(void* Array) {
    printf("Begin Thread Process \n");

    // Cast the void pointer back to the appropriate type
    long *Buffer = (long*)Array;
    
    // GPIO number to monitor for interrupts
    int gpio_number = 67;
    
    // File path to read the interrupt value
    char InterruptPath[40];
    sprintf(InterruptPath, "/sys/class/gpio/gpio%d/value", gpio_number);
    
    // File pointer for reading interrupt value
    FILE *fp = fopen(InterruptPath, "r");
    int fd = fileno(fp); // Get file descriptor
    
    // Create an epoll instance
    int epfd = epoll_create(1);
    struct epoll_event ev;
    
    // Configure event to monitor for input events (EPOLLIN) and edge-triggered mode (EPOLLET)
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;
    
    // Register file descriptor with epoll
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    
    int capture_interrupt;
    struct timespec tm;
    struct epoll_event ev_wait;
    
    // Loop to capture interrupts
    for (int i = 0; i < 10; i++) {
        // Wait indefinitely for an interrupt event
        capture_interrupt = epoll_wait(epfd, &ev_wait, 1, -1);
        
        // Get current time
        clock_gettime(CLOCK_MONOTONIC, &tm);
        
        // Store the timestamp of the interrupt
        Buffer[i] = tm.tv_sec;
        
        // Print the interrupt event and timestamp
        printf("Interrupt Received %d at %ld \n", capture_interrupt, tm.tv_sec);
    }
    
    // Close epoll instance
    close(epfd);
    
    printf("End Thread Process \n");
}

int main() {
    // Array to store timestamps of interrupts
    long Buffer[10];
    
    pthread_t thd_id;
    
    printf("Thread has NOT YET been executed \n");
    
    // Create thread to execute epollThread function
    pthread_create(&thd_id, NULL, epollThread, (void*)Buffer);
    
    // Wait for thread to finish execution
    pthread_join(thd_id, NULL);
    
    printf("Thread Executed \n");
    
    // Print the timestamps stored in the buffer
    for (int j = 0; j < 10; j++) {
        printf("Entry %d, Value %ld \n", j, Buffer[j]);
    }
    
    pthread_exit(0);
}
