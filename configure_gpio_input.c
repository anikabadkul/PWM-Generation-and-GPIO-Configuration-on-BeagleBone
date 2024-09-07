#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// This file contains code to be called to configure a GPIO pin on BeaglBoardBlack

void configure_gpio_input(int gpio_number) {
    char gpio_num[15]; 
    sprintf(gpio_num, "export %d", gpio_number); 
    const char* GPIOExport="/sys/class/gpio/export";

    // export gpio to user space
    FILE* fp = fopen(GPIOExport, "w");
    if (fwrite(gpio_num, sizeof(char), sizeof(gpio_num), fp) != sizeof(gpio_num)) {
        perror("Error writing to GPIO export file");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    // access GPIO
    char GPIODirection[50]; // Increase buffer size
    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", gpio_number);
    // Declare state of GPIO
    fp = fopen(GPIODirection, "w");
    if (fp == NULL) {
        perror("Error opening GPIO direction file");
        exit(EXIT_FAILURE);
    }
    fwrite("in", sizeof(char), 2, fp);
    fclose(fp);
    printf("GPIO%s Configured as input \n",gpio_num);}

