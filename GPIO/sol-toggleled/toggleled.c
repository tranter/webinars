/*

Example of programming GPIO from C or C++ using the sysfs interface on
a Raspberry Pi or Toradex Colibri.

Will toggle a GPIO pin at a 100 millisecond rate for 10 seconds and
then exit.

This program is valid C and C++.

Jeff Tranter <jtranter@ics.com>

*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Uncomment the appropriate line below for the hardware it is runnning on.
//#define pin "24" // Pin 24 on Raspberry Pi
#define pin "52" // Pin 52 on Toradex Colibri

int main()
{
    // Paths for GPIO sysfs access.

    const char *exprt = "/sys/class/gpio/export";
    const char *unexport = "/sys/class/gpio/unexport";
    const char *direction = "/sys/class/gpio/gpio" pin "/direction";
    const char *value = "/sys/class/gpio/gpio" pin "/value";

    // Export the desired pin by writing to /sys/class/gpio/export

    int fd = open(exprt, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open export file");
        exit(1);
    }

    if (write(fd, pin, 2) != 2) {
        perror("Error writing to export file");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpioXX/direction

    fd = open(direction, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open direction file");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to direction file");
        exit(1);
    }

    close(fd);

    fd = open(value, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open value file");
        exit(1);
    }

    // Toggle LED 50 ms on, 50ms off, 100 times (10 seconds)

    for (int i = 0; i < 100; i++) {
        if (write(fd, "1", 1) != 1) {
            perror("Error writing to value file");
            exit(1);
        }
        usleep(50000);

        if (write(fd, "0", 1) != 1) {
            perror("Error writing to value file");
            exit(1);
        }
        usleep(50000);
    }

    close(fd);

    // Unexport the pin by writing to /sys/class/gpio/unexport

    fd = open(unexport, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open unexport file");
        exit(1);
    }

    if (write(fd, pin, 2) != 2) {
        perror("Error writing to unexport file");
        exit(1);
    }

    close(fd);

    // And exit
    return 0;
}
