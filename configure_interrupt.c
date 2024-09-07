// This file contains code for configuring an interrupt on BBB pwm pin:
#include "configure_gpio_input.c"


void configure_interrupt(int gpio_number){
    configure_gpio_input(gpio_number); // configs GPIO

    // Now configure interrupt

    char InterruptEdge[40];
    sprintf(InterruptEdge, "/sys/class/gpio/gpio%d/edge", gpio_number);
    FILE* fp =fopen(InterruptEdge, "w");
    if (fwrite("rising", sizeof(char), 7, fp) != sizeof(gpio_number)){
        // Failure to write condition
        perror("Error writing to GPIO export file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp); // Close FP
}