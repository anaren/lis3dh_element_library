/**
 *  ----------------------------------------------------------------------------
 *  Copyright (c) 2014, Anaren Microwave, Inc.
 *
 *  For more information on licensing, please see Anaren Microwave, Inc's
 *  end user software licensing agreement: EULA.txt.
 *
 *  ----------------------------------------------------------------------------
 *
 *  lis3dh.c - driver interface for the ST Microelectronics LIS3DH 3-Axis MEMS
 *  accelerometer.
 *
 *  @version    1.0.00
 *  @date       30 Sep 2014
 *  @author     Anaren, air@anaren.com
 *
 *  assumptions
 *  ===========
 *  - The SPI driver provides the proper signaling sequences for read & write
 *    operations.
 *  - The SPI driver meets the timing requirements specified in the LIS3DH
 *    datasheet.
 *
 *  file dependency
 *  ===============
 *  spi.h : defines the SPI read & write interfaces.
 *
 *  revision history
 *  ================
 *  ver 1.0.00 : 30 Sep 2014
 *  - initial release
 */

#include "lis3dh.h"


// -----------------------------------------------------------------------------
/**
 *  Global data
 */

// -----------------------------------------------------------------------------
/**
 *  Private interface
 */

// -----------------------------------------------------------------------------
/**
 *  Public interface
 */

void LIS3DH_Init()
{
	AIR_SPI_SetCSPin(LIS3DH_CSPIN);
	LIS3DH_WriteReg(0x20, 0x77);
}

void LIS3DH_WriteReg(uint8 addr, uint8 data)
{
  uint8 writeBytes[2];

  writeBytes[0] = addr;
  writeBytes[1] = data;
  AIR_SPI_Write(LIS3DH_CSPIN, writeBytes, 2);
}

uint8 LIS3DH_ReadReg(uint8 addr)
{
  uint8 writeBytes[2];
  uint8 readBytes[2];

  writeBytes[0] = addr | 0x80;  // set msb high for read operations
  writeBytes[1] = 0xFF;         // dummy byte

  AIR_SPI_Exchange(LIS3DH_CSPIN, readBytes, writeBytes, 2);
  return readBytes[1];
}


uint8 LIS3DH_GetWhoAmIReg(void)
{
  return LIS3DH_ReadReg(LIS3DH_WHO_AM_I_REG_ADDR);
}

int16 LIS3DH_GetXaxisRaw(void)
{
  uint16 returnData = (uint16)LIS3DH_ReadReg(LIS3DH_OUT_X_H_REG_ADDR) << 8;
  
  returnData |= LIS3DH_ReadReg(LIS3DH_OUT_X_L_REG_ADDR);
  
  return (int16)returnData;
}

int16 LIS3DH_GetYaxisRaw(void)
{
  uint16 returnData = (uint16)LIS3DH_ReadReg(LIS3DH_OUT_Y_H_REG_ADDR) << 8;
  
  returnData |= LIS3DH_ReadReg(LIS3DH_OUT_Y_L_REG_ADDR);
  
  return (int16)returnData;
}

int16 LIS3DH_GetZaxisRaw(void)
{
  uint16 returnData = (uint16)LIS3DH_ReadReg(LIS3DH_OUT_Z_H_REG_ADDR) << 8;
  
  returnData |= LIS3DH_ReadReg(LIS3DH_OUT_Z_L_REG_ADDR);
  
  return (int16)returnData;
}

float LIS3DH_GetXaxis(void)
{
  return (float)LIS3DH_GetXaxisRaw() / 16384.0;
}

float LIS3DH_GetYaxis(void)
{
  return (float)LIS3DH_GetYaxisRaw() / 16384.0;
}

float LIS3DH_GetZaxis(void)
{
  return (float)LIS3DH_GetZaxisRaw() / 16384.0;
}
