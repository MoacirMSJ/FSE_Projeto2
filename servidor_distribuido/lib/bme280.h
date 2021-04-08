#ifndef __BME280__
#define __BME280__
//
// BME280 temperature/pressure/humidity sensor
// prototyping code to read and calculate calibrated values
// from the I2C bus
//
// Written by Larry Bank - 2/1/2017
// Copyright (c) 2017 BitBank Software, Inc.
// bitbank@pobox.com
//
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define BME280_ADRESS 0x76

static int file_i2c = 0;
// Sensor calibration data
static int calT1,calT2,calT3;
static int calP1, calP2, calP3, calP4, calP5, calP6, calP7, calP8, calP9;
static int calH1, calH2, calH3, calH4, calH5, calH6;
//
// Opens a file system handle to the I2C device
// reads the calibration data and sets the device
// into auto sensing mode
//
void fecharArquivoI2C();
float bmeTempExterna();
int bme280Init(int iChannel, int iAddr);
int bme280ReadValues(int *T, int *P, int *H);
float tempExterna();

#endif // __BME280__