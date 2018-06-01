/*!
 * \file I2C.cc
 *
 * \author YYen Gallup
 *
 * Core logic for implementation of I2C device on linux.
 */

#include "i2c.h"

#include <linux/i2c-dev.h>
#include <errno.h>

#define DEFAULT_INTERFACE "/dev/I2C-0"

I2C::I2C(uint8_t address) {
	I2C(DEFAULT_INTERFACE, address);
}

I2C::I2C(string interface_name, uint8_t address) {
	interface_ = open(interface_name, O_RDRW);
	address_ = address;
}

int I2C::init() {
	if(interface_ < 0) {
		log.err("I2C init failed to bind interface.", errno);
		return -1;
	}

	if(ioctl(interface_, I2C_SLAVE, address_) < 0) {
		log.err("I2C init failed to bind address " + address_, errno);
		return -1;
	}

	return 0;
}

int I2C::read(uint8_t reg, uint8_t length, uint8_t *data) {
	int read_length = 0;

	if(write(interface_, &reg, 1) < 0) {
		log.err("I2C read transaction failed on register transmit.", errno);
		return -1;
	}

	read_length = read(interface_, &data, length);
	if(read_length < 0) {
		log.err("I2C read transaction failed on readback.", errno);
		return -1;
	}

	return read_length;
}

int I2C::write(uint8_t reg, uint8_t length, uint8_t *data) {
	int write_length = 0;

	if(write(interface_, &reg, 1) < 0) {
		log.err("I2C write transaction failed on register transmit.", errno);
		return -1;
	}

	write_length = write(interface_, &data, length);
	if(write_length < 0) {
		log.err("I2C write transaction failed on data transmit.", errno);
		return -1;
	}

	return write_length;
}
