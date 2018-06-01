#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include <string>

using namespace std;

class I2C {
public:
I2C(uint8_t address);
I2C(string interface_name, uint8_t address);

int init();

int read(uint8_t reg, uint8_t length, uint8_t *data);
int write(uint8_t reg, uint8_t length, uint8_t *data);

private:
int interface_;
uint8_t address_;
};

#endif
