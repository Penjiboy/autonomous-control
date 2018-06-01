#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define NUMBER_TO_AMPS 0.00046

int address = 0x40;
int file;
char filename[] = "/dev/i2c-1";
char result[2];
int seconds = 25;

int main(int argc, char *argv[]) {
	//if(argc > 1) sscanf(argv[1], "%i", seconds);
file = open(filename, O_RDWR);
if(file < 0)
	printf("File not opened properly");

if(ioctl(file, I2C_SLAVE, address) < 0)
	printf("File couldnt open I2C");

result[0] = 0x0;

char reg = 0x1;

//printf("Test: %h\n", i2c_smbus_read_byte_data(file, 0x1));
for(int i = 0; (i < 10*seconds) | (seconds == -1); i++) {
	int avg = 0;
	for(int i = 0; i < 30; i++) {
		if(write(file, &reg, 1) < 0)
			printf("couldn't send register address.\n");

		if(read(file, result, 2) < 0)
			printf("Read failed\n");
		else {
			short number = (result[0] << 8)| result[1];
			//printf("%i, ", number);
			avg += number;
		}

		usleep(1000);
	}
	avg /= 30;

	printf("Amps: %f\n", avg*NUMBER_TO_AMPS);

	usleep(100000);
}

return 0;
}
