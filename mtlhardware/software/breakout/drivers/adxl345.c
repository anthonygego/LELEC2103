#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <system.h>
#include <altera_avalon_spi.h>
#include <alt_types.h>

#include "adxl345.h"

/*
 * Writes data to accelerometer
 * - address : Address of register to modify
 * - data : Data to be written to register
 */
void adxl345_write(adxl345_info * p, alt_u8 address, alt_u8 data)
{
	alt_u8 txdata[2];
	txdata[0] = address;
	txdata[1] = data;
	alt_avalon_spi_command(p->ADXL_BASE, 0, 2, txdata, 0, NULL, 0);
}

/*
 * Reads data from accelerometer
 * - address : Address of register to read
 * - data : Pointer to data buffer
 * - length : Number of bytes to sequentially read from accelerometer
 */
int adxl345_read(adxl345_info * p, alt_u8 address, alt_u8 * data, alt_u32 length)
{
	alt_u8 txdata[2];
	txdata[0] = length == 1 ? address | 0x80 : address | 0xC0;
	return alt_avalon_spi_command(p->ADXL_BASE, 0, 1, txdata, length, data, 0);
}

/*
 * Initializes the adxl345 for the required usage
 */
adxl345_info * adxl345_init(alt_u32 BASE)
{
	adxl345_info * p = malloc(sizeof(adxl345_info));
	p->ADXL_BASE = BASE;

	adxl345_write(p, ADXL345_DATA_FORMAT, 0x4B);   // Activate 3-wire SPI + Full res + 16g range
	adxl345_write(p, ADXL345_BW_RATE, 0x09);		// Activate 25 Hz bandwidth
	adxl345_write(p, ADXL345_POWER_CONTROL, 0x08);	// Activate measure

	return p;
}

void adxl345_uninit(adxl345_info * p)
{
	if(p)
		free(p);
}
