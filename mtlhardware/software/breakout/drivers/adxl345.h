#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <system.h>
#include <altera_avalon_spi.h>
#include <alt_types.h>

#ifndef ADXL345_H_
#define ADXL345_H_

// Definition of registers
#define ADXL345_DEVID            0x00
#define	ADXL345_BW_RATE	         0x2c
#define ADXL345_POWER_CONTROL    0x2d
#define ADXL345_DATA_FORMAT      0x31
#define	ADXL345_DATAX0           0x32

typedef struct {
	alt_16 x;
	alt_16 y;
	alt_16 z;
} adxl345_coordinates;

typedef struct {
	alt_u32 ADXL_BASE;
	alt_u32 ADXL_IRQ_NUM;
    alt_u32 ADXL_IRQ_CONTROLLER;
} adxl345_info;

adxl345_info *  adxl345_init(alt_u32 BASE);
void 			adxl345_uninit(adxl345_info * p);
void 			adxl345_write(adxl345_info * p, alt_u8 address, alt_u8 data);
int  			adxl345_read(adxl345_info * p, alt_u8 address, alt_u8 * data, alt_u32 length);

#endif /* ADXL345_H_ */
