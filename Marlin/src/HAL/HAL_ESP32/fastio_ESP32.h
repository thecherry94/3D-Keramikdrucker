/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 Marlin Firmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter an grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef	_FASTIO_ESP32_H
#define	_FASTIO_ESP32_H

/**
  utility functions
*/

// SX1509 registers

#define IODIRA    0x0E // sx1509 RegDirB
#define IODIRB    0x0F // sx1509 RegDirA
#define IPOLA     0x0C // sx1509 RegPolarityB
#define IPOLB     0x0D // sx1509 RegPolarityA
#define GPINTENA  0x12 // sx1509 RegInterruptMaskB
#define GPINTENB  0x13 // sx1509 RegInterruptMaskA
#define RegSenseHighA   0x16 // sx1509 RegSenseHighB
#define RegSenseLowA   0x17 // sx1509 RegSenseLowB

//#define DEFVALA   0x06 
//#define DEFVALB   0x07
#define INTCONA   0x18 // sx1509 RegInterruptSourceB
#define INTCONB   0x19 // sx1509 RegInterruptSourceA
//#define IOCON     0x0A
#define GPPUA     0x06 // sx1509 RegPullUpB
#define GPPUB     0x07 // sx1509 RegPullUpA
//#define INTFA     0x0E
//#define INTFB     0x0F
//#define INTCAPA   0x10
//#define INTCAPB   0x11
#define GPIOA     0x10 // sx1509 RegDataB
#define GPIOB     0x11 // sx1509 RegDataA
//#define OLATA     0x14
//#define OLATB     0x15


#define GPIOX_I2C_ADDR 0x3E

#define GET_REGISTER(IO, reg) ((IO & 0x7F) < 8 ? reg : reg+1)
#define GET_PIN(IO) ((IO & 0x7F) < 8 ? (IO&0x7F) : (IO&0x7F)-8)

uint8_t get_i2c_register(uint8_t reg);
void set_i2c_register(uint8_t reg, uint8_t val);
void set_i2c_pin_mode(uint8_t pin, uint8_t mode);
void set_i2c_pin_pullup(uint8_t pin, bool pullup);
uint8_t get_i2c_pin(uint8_t pin);
void set_i2c_pin(uint8_t pin, uint8_t val);

//
#define _SET_INPUT(IO)      (IO) & 0x80 ? set_i2c_pin_mode((IO)&0x7f, INPUT) : pinMode(IO, INPUT)

// set pin as output
#define _SET_OUTPUT(IO)     (IO) & 0x80 ? set_i2c_pin_mode((IO)&0x7f, OUTPUT) : pinMode(IO, OUTPUT)

// set pin as input with pullup mode
#define _PULLUP(IO, v)      (IO) & 0x80 ? set_i2c_pin_pullup((IO)&0x7f, v) : pinMode(IO, v ? INPUT_PULLUP : INPUT)

// Read a pin wrapper
#define _READ(IO)            (IO) & 0x80 ? get_i2c_pin((IO)&0x7f) : digitalRead(IO)
#define READ(IO)             (_READ(IO) ? HIGH : LOW)

// Write to a pin wrapper
#define WRITE(IO, v)        (IO) & 0x80 ? set_i2c_pin((IO)&0x7f, v) : digitalWrite(IO, v)

// set pin as input wrapper
#define SET_INPUT(IO)  _SET_INPUT(IO)

// set pin as input with pullup wrapper
#define SET_INPUT_PULLUP(IO) do{ _SET_INPUT(IO); _PULLUP(IO, HIGH); }while(0)

// set pin as output wrapper
#define SET_OUTPUT(IO)  do{ _SET_OUTPUT(IO); WRITE(IO, LOW); }while(0)

#define OUT_WRITE(IO,V) do{ SET_OUTPUT(IO); WRITE(IO,V); }while(0)

/**
  ports and functions

  added as necessary or if I feel like it- not a comprehensive list!
*/

// UART
#define RXD        3
#define TXD        1

// TWI (I2C)
#define SCL        5
#define SDA        4

/**
pins
*/


#endif	/* _FASTIO_ESP32_H */