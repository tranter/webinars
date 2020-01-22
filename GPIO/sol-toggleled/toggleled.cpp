/*

Example of programming GPIO from C++ using the sysfs interface on
a Raspberry Pi or Toradex Colibri.

Will toggle a GPIO pin at a 100 millisecond rate for 10 seconds and
then exit.

This version is C++ only.

Jeff Tranter <jtranter@ics.com>

*/

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <string>
#include <unistd.h>

int main()
{
    // Uncomment the appropriate line below for the hardware it is runnning on.
    //std::string pin = "24"; // Pin 24 on Raspberry Pi
    std::string pin = "52"; // Pin 52 on Toradex Colibri

    // Paths for GPIO sysfs access.

    std::string exprt = "/sys/class/gpio/export";
    std::string unexport = "/sys/class/gpio/unexport";
    std::string direction = "/sys/class/gpio/gpio" + pin + "/direction";
    std::string value = "/sys/class/gpio/gpio" + pin + "/value";

    // Export the desired pin by writing to /sys/class/gpio/export

    int fd = open(exprt.c_str(), O_WRONLY, 0);
    if (fd == -1) {
        perror("Unable to open export file");
        exit(1);
    }

    if (write(fd, pin.c_str(), 2) != 2) {
        perror("Error writing to export file");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpioXX/direction

    fd = open(direction.c_str(), O_WRONLY, 0);
    if (fd == -1) {
        perror("Unable to open direction file");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to direction file");
        exit(1);
    }

    close(fd);

    fd = open(value.c_str(), O_WRONLY, 0);
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

    fd = open(unexport.c_str(), O_WRONLY, 0);
    if (fd == -1) {
        perror("Unable to open unexport file");
        exit(1);
    }

    if (write(fd, pin.c_str(), 2) != 2) {
        perror("Error writing to unexport file");
        exit(1);
    }

    close(fd);

    // And exit
    return 0;
}
