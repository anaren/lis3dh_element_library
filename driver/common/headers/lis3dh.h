// Copyright (c) 2014, Anaren Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies, 
// either expressed or implied, of the FreeBSD Project.

#ifndef LIS3DH_H
#define LIS3DH_H

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */

#include "pin_mapping.h"
#include "lis3dh_config.h"
#include "../spi/spi.h"
#include <stdint.h>

#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */

#define LIS3DH_STATUS_REG_AUX_ADDR      0x07  // Auxiliary Status (read only)
#define LIS3DH_OUT_ADC1_L_REG_ADDR      0x08  // Data Output ADC1 LSB (read only)
#define LIS3DH_OUT_ADC1_H_REG_ADDR      0x09  // Data Output ADC1 MSB (read only)
#define LIS3DH_OUT_ADC2_L_REG_ADDR      0x0A  // Data Output ADC2 LSB (read only)
#define LIS3DH_OUT_ADC2_H_REG_ADDR      0x0B  // Data Output ADC2 MSB (read only)
#define LIS3DH_OUT_ADC3_L_REG_ADDR      0x0C  // Data Output ADC3 LSB (read only)
#define LIS3DH_OUT_ADC3_H_REG_ADDR      0x0D  // Data Output ADC3 MSB (read only)
#define LIS3DH_INT_COUNTER_REG_ADDR     0x0E  // Interrupt Counter (read only)
#define LIS3DH_WHO_AM_I_REG_ADDR        0x0F  // Device Identification (read only)
#define LIS3DH_TEMP_CFG_REG_ADDR        0x1F  // Temperature Sensor Configuration
#define LIS3DH_CTRL_REG1_ADDR           0x20  // Control 1
#define LIS3DH_CTRL_REG2_ADDR           0x21  // Control 2
#define LIS3DH_CTRL_REG3_ADDR           0x22  // Control 3
#define LIS3DH_CTRL_REG4_ADDR           0x23  // Control 4
#define LIS3DH_CTRL_REG5_ADDR           0x24  // Control 5
#define LIS3DH_CTRL_REG6_ADDR           0x25  // Control 6
#define LIS3DH_REFERENCE_REG_ADDR       0x26  // Reference / Data Capture
#define LIS3DH_STATUS_REG2_ADDR         0x27  // Status 2 (read only)
#define LIS3DH_OUT_X_L_REG_ADDR         0x28  // Data Output X LSB (read only)
#define LIS3DH_OUT_X_H_REG_ADDR         0x29  // Data Output X MSB (read only)
#define LIS3DH_OUT_Y_L_REG_ADDR         0x2A  // Data Output Y LSB (read only)
#define LIS3DH_OUT_Y_H_REG_ADDR         0x2B  // Data Output Y MSB (read only)
#define LIS3DH_OUT_Z_L_REG_ADDR         0x2C  // Data Output Z LSB (read only)
#define LIS3DH_OUT_Z_H_REG_ADDR         0x2D  // Data Output Z MSB (read only)
#define LIS3DH_FIFO_CTRL_REG_ADDR       0x2E  // FIFO Control
#define LIS3DH_FIFP_SRC_REG_ADDR        0x2F  // FIFO Source (read only)
#define LIS3DH_INT1_CFG_REG_ADDR        0x30  // Interrupt 1 Configuration
#define LIS3DH_INT1_SRC_REG_ADDR        0x31  // Interrupt 1 Source (read only)
#define LIS3DH_INT1_THS_REG_ADDR        0x32  // Interrupt 1 Threshold
#define LIS3DH_INT1_DURATION_REG_ADDR   0x33  // Interrupt 1 Duration
#define LIS3DH_CLICK_CFG_REG_ADDR       0x38  // Click Configuration
#define LIS3DH_CLICK_SRC_REG_ADDR       0x39  // Click Source (read only)
#define LIS3DH_CLICK_THS_REG_ADDR       0x3A  // Click Threshold
#define LIS3DH_TIME_LIMIT_REG_ADDR      0x3B  // Time Limit
#define LIS3DH_TIME_LATENCY_REG_ADDR    0x3C  // Time Latency
#define LIS3DH_TIME_WINDOW_REG_ADDR     0x3D  // Time Window
#define LIS3DH_SPI_MODE 0
#define LIS3DH_MSB_FIRST 1
/**
 *  eLIS3DHOperatingMode - type indicating the operating mode of the
 *  LIS3DH device.  The LIS3DH offers two modes; Normal and Low-power.  Refer
 *  to the LIS3DH datasheet for details regarding the different modes.
 */
enum eLIS3DHOperatingMode
{
  LIS3DH_LowPower              = 0x00,
  LIS3DH_Normal                = 0x01
};

/**
 *  eLIS3DHDataRate - type indicating the output data rate of the LIS3DH
 *  device, specified in Hz.
 */
enum eLIS3DHDataRate
{
  LIS3DH_Rate_PowerDown        = 0x00, // power down mode (default)
  LIS3DH_Rate_1Hz              = 0x01, // normal & low-power modes
  LIS3DH_Rate_10Hz             = 0x02, // normal & low-power modes
  LIS3DH_Rate_25Hz             = 0x03, // normal & low-power modes
  LIS3DH_Rate_50Hz             = 0x04, // normal & low-power modes
  LIS3DH_Rate_100Hz            = 0x05, // normal & low-power modes
  LIS3DH_Rate_200Hz            = 0x06, // normal & low-power modes
  LIS3DH_Rate_400Hz            = 0x07, // normal & low-power modes
  LIS3DH_Rate_1600Hz           = 0x08, // low-power mode only
  LIS3DH_Rate_1250Hz_5000Hz    = 0x09  // 1.25kHz normal mode, 5kHz low-power mode
};

void LIS3DH_Init();

/**
Write an 8-bit value to a device register.  All of the LIS3DH registers are
read only except for the configuration and control registers.  This function
does not do any form of error checking, so trying to write to one of the
read-only registers may result in undesireable behavior.
@param addr device register address
@param data data to be written to the specified register address
*/
void LIS3DH_WriteReg(uint8_t addr, uint8_t data);

/**
Read an 8-bit value from a device register.
@param addr device register address
@return data read from the specified register address
*/
uint8_t LIS3DH_ReadReg(uint8_t addr);

/**
Read WHO_AM_I identification register.
@return contents of WHO_AM_I register.  Value always = 0x33 (ascii '3').
*/
uint8_t LIS3DH_GetWhoAmIReg(void);


int16_t LIS3DH_GetXaxisRaw(void);
int16_t LIS3DH_GetYaxisRaw(void);
int16_t LIS3DH_GetZaxisRaw(void);

float LIS3DH_GetXaxis(void);
float LIS3DH_GetYaxis(void);
float LIS3DH_GetZaxis(void);


#endif  /* LIS3DH_H */
