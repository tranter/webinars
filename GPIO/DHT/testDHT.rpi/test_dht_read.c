#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pi_2_dht_read.h"
#include "pi_2_mmio.h"

// Call dht_read and return result code, humidity, and temperature.

int main(int argc, char **argv)
{
    int pin = 26;
    float humidity = 0;
    float temperature = 0;
    int result = 0;
    int type = DHT22;

    // Check for optional sensor type (DHT22 or DHT11) on the command line.
    if (argc == 2) {
        if (!strcmp(argv[1], "11") || !strcmp(argv[1], "dht11") || !strcmp(argv[1], "DHT11")) {
            type = DHT11;
        } else if (!strcmp(argv[1], "22") || !strcmp(argv[1], "dht22")
                   || !strcmp(argv[1], "DHT22")) {
            type = DHT22;
        }
    }

    if (type == DHT11)
        printf("Start test DHT11. GPIO pin is %d\n", pin);
    else if (type == DHT22)
        printf("Start test DHT22. GPIO pin is %d\n", pin);

    result = pi_2_dht_read(type, pin, &humidity, &temperature);

    printf("result = %d humidity = %f  temperature = %f \n", result, humidity, temperature);

    return 0;
}
