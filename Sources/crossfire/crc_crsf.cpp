/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x 
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "crc_crsf.h"

static const unsigned short * crc16tab[] = {
  crc16tab_1021,
  crc16tab_1189
};

uint16_t crc16(uint8_t index, const uint8_t * buf, uint32_t len, uint16_t start)
{
  uint16_t crc = start;
  const unsigned short * tab = crc16tab[index];
  for (uint32_t i=0; i<len; i++) {
    crc = (crc<<8) ^ tab[((crc>>8) ^ *buf++) & 0x00FF];
  }
  return crc;
}

// CRC8 implementation with polynom = x^8+x^7+x^6+x^4+x^2+1 (0xD5)
const unsigned char crc8tab[256] = {
  0x00, 0xD5, 0x7F, 0xAA, 0xFE, 0x2B, 0x81, 0x54,
  0x29, 0xFC, 0x56, 0x83, 0xD7, 0x02, 0xA8, 0x7D,
  0x52, 0x87, 0x2D, 0xF8, 0xAC, 0x79, 0xD3, 0x06,
  0x7B, 0xAE, 0x04, 0xD1, 0x85, 0x50, 0xFA, 0x2F,
  0xA4, 0x71, 0xDB, 0x0E, 0x5A, 0x8F, 0x25, 0xF0,
  0x8D, 0x58, 0xF2, 0x27, 0x73, 0xA6, 0x0C, 0xD9,
  0xF6, 0x23, 0x89, 0x5C, 0x08, 0xDD, 0x77, 0xA2,
  0xDF, 0x0A, 0xA0, 0x75, 0x21, 0xF4, 0x5E, 0x8B,
  0x9D, 0x48, 0xE2, 0x37, 0x63, 0xB6, 0x1C, 0xC9,
  0xB4, 0x61, 0xCB, 0x1E, 0x4A, 0x9F, 0x35, 0xE0,
  0xCF, 0x1A, 0xB0, 0x65, 0x31, 0xE4, 0x4E, 0x9B,
  0xE6, 0x33, 0x99, 0x4C, 0x18, 0xCD, 0x67, 0xB2,
  0x39, 0xEC, 0x46, 0x93, 0xC7, 0x12, 0xB8, 0x6D,
  0x10, 0xC5, 0x6F, 0xBA, 0xEE, 0x3B, 0x91, 0x44,
  0x6B, 0xBE, 0x14, 0xC1, 0x95, 0x40, 0xEA, 0x3F,
  0x42, 0x97, 0x3D, 0xE8, 0xBC, 0x69, 0xC3, 0x16,
  0xEF, 0x3A, 0x90, 0x45, 0x11, 0xC4, 0x6E, 0xBB,
  0xC6, 0x13, 0xB9, 0x6C, 0x38, 0xED, 0x47, 0x92,
  0xBD, 0x68, 0xC2, 0x17, 0x43, 0x96, 0x3C, 0xE9,
  0x94, 0x41, 0xEB, 0x3E, 0x6A, 0xBF, 0x15, 0xC0,
  0x4B, 0x9E, 0x34, 0xE1, 0xB5, 0x60, 0xCA, 0x1F,
  0x62, 0xB7, 0x1D, 0xC8, 0x9C, 0x49, 0xE3, 0x36,
  0x19, 0xCC, 0x66, 0xB3, 0xE7, 0x32, 0x98, 0x4D,
  0x30, 0xE5, 0x4F, 0x9A, 0xCE, 0x1B, 0xB1, 0x64,
  0x72, 0xA7, 0x0D, 0xD8, 0x8C, 0x59, 0xF3, 0x26,
  0x5B, 0x8E, 0x24, 0xF1, 0xA5, 0x70, 0xDA, 0x0F,
  0x20, 0xF5, 0x5F, 0x8A, 0xDE, 0x0B, 0xA1, 0x74,
  0x09, 0xDC, 0x76, 0xA3, 0xF7, 0x22, 0x88, 0x5D,
  0xD6, 0x03, 0xA9, 0x7C, 0x28, 0xFD, 0x57, 0x82,
  0xFF, 0x2A, 0x80, 0x55, 0x01, 0xD4, 0x7E, 0xAB,
  0x84, 0x51, 0xFB, 0x2E, 0x7A, 0xAF, 0x05, 0xD0,
  0xAD, 0x78, 0xD2, 0x07, 0x53, 0x86, 0x2C, 0xF9
};

uint8_t crc8(const uint8_t * ptr, uint32_t len)
{
  uint8_t crc = 0;
  for (uint32_t i=0; i<len; i++) {
    crc = crc8tab[crc ^ *ptr++];
  }
  return crc;
}

// CRC8 implementation with polynom = 0xBA
const unsigned char crc8tab_BA[256] = {
  0x00, 0xBA, 0xCE, 0x74, 0x26, 0x9C, 0xE8, 0x52,
  0x4C, 0xF6, 0x82, 0x38, 0x6A, 0xD0, 0xA4, 0x1E,
  0x98, 0x22, 0x56, 0xEC, 0xBE, 0x04, 0x70, 0xCA,
  0xD4, 0x6E, 0x1A, 0xA0, 0xF2, 0x48, 0x3C, 0x86,
  0x8A, 0x30, 0x44, 0xFE, 0xAC, 0x16, 0x62, 0xD8,
  0xC6, 0x7C, 0x08, 0xB2, 0xE0, 0x5A, 0x2E, 0x94,
  0x12, 0xA8, 0xDC, 0x66, 0x34, 0x8E, 0xFA, 0x40,
  0x5E, 0xE4, 0x90, 0x2A, 0x78, 0xC2, 0xB6, 0x0C,
  0xAE, 0x14, 0x60, 0xDA, 0x88, 0x32, 0x46, 0xFC,
  0xE2, 0x58, 0x2C, 0x96, 0xC4, 0x7E, 0x0A, 0xB0,
  0x36, 0x8C, 0xF8, 0x42, 0x10, 0xAA, 0xDE, 0x64,
  0x7A, 0xC0, 0xB4, 0x0E, 0x5C, 0xE6, 0x92, 0x28,
  0x24, 0x9E, 0xEA, 0x50, 0x02, 0xB8, 0xCC, 0x76,
  0x68, 0xD2, 0xA6, 0x1C, 0x4E, 0xF4, 0x80, 0x3A,
  0xBC, 0x06, 0x72, 0xC8, 0x9A, 0x20, 0x54, 0xEE,
  0xF0, 0x4A, 0x3E, 0x84, 0xD6, 0x6C, 0x18, 0xA2,
  0xE6, 0x5C, 0x28, 0x92, 0xC0, 0x7A, 0x0E, 0xB4,
  0xAA, 0x10, 0x64, 0xDE, 0x8C, 0x36, 0x42, 0xF8,
  0x7E, 0xC4, 0xB0, 0x0A, 0x58, 0xE2, 0x96, 0x2C,
  0x32, 0x88, 0xFC, 0x46, 0x14, 0xAE, 0xDA, 0x60,
  0x6C, 0xD6, 0xA2, 0x18, 0x4A, 0xF0, 0x84, 0x3E,
  0x20, 0x9A, 0xEE, 0x54, 0x06, 0xBC, 0xC8, 0x72,
  0xF4, 0x4E, 0x3A, 0x80, 0xD2, 0x68, 0x1C, 0xA6,
  0xB8, 0x02, 0x76, 0xCC, 0x9E, 0x24, 0x50, 0xEA,
  0x48, 0xF2, 0x86, 0x3C, 0x6E, 0xD4, 0xA0, 0x1A,
  0x04, 0xBE, 0xCA, 0x70, 0x22, 0x98, 0xEC, 0x56,
  0xD0, 0x6A, 0x1E, 0xA4, 0xF6, 0x4C, 0x38, 0x82,
  0x9C, 0x26, 0x52, 0xE8, 0xBA, 0x00, 0x74, 0xCE,
  0xC2, 0x78, 0x0C, 0xB6, 0xE4, 0x5E, 0x2A, 0x90,
  0x8E, 0x34, 0x40, 0xFA, 0xA8, 0x12, 0x66, 0xDC,
  0x5A, 0xE0, 0x94, 0x2E, 0x7C, 0xC6, 0xB2, 0x08,
  0x16, 0xAC, 0xD8, 0x62, 0x30, 0x8A, 0xFE, 0x44
};

uint8_t crc8_BA(const uint8_t * ptr, uint32_t len)
{
  uint8_t crc = 0;
  for (uint32_t i=0; i<len; i++) {
    crc = crc8tab_BA[crc ^ *ptr++];
  }
  return crc;
}
