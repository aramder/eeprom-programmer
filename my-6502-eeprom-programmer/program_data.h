/*
 * ROM: $8000-FFFF
 * RAM: $0000-3FFF
 * VIA1: $6000-600F
 * VIA2L $5000-500F
 * 
 * RST, NMI, and IRQ vectors are at $FFFA-$FFFF
 * which correlate to $7FFA-7FFF in the ROM
 * 
 * All vectors will point to start of ROM
 * 
 * See: http://wilsonminesco.com/6502primer/MemMapReqs.html for memory mapping information
 */

// Breadboard6502 - My first test reading the ADC and dislaying the value
//byte data[] = {
//  0xA9, 0x00, 0x8D, 0x03, 0x60, 0x8D, 0x02, 0x50, 0xA9, 0xDF, 0x8D, 0x02, 0x60, 0xA9, 0xFF, 0x8D,
//  0x03, 0x50, 0xA9, 0x08, 0x8D, 0x00, 0x60, 0xA9, 0x00, 0x8D, 0x00, 0x60, 0xA9, 0x00, 0xCD, 0x00,
//  0x60, 0xD0, 0xF9, 0xA9, 0x20, 0xCD, 0x00, 0x60, 0xD0, 0xF9, 0xA9, 0x10, 0x8D, 0x00, 0x60, 0xAD,
//  0x01, 0x60, 0x85, 0x00, 0xA9, 0x00, 0x8D, 0x00, 0x60, 0xA5, 0x00, 0x8D, 0x01, 0x50, 0x4C, 0x12,
//  0x80
//};

// ADC_subroutine - Reads data from ADC input 0 to RAM, then displays on VIA2 port A
//byte data[] = {
//  0xA9, 0x00, 0x8D, 0x03, 0x60, 0x8D, 0x02, 0x50, 0xA9, 0xDF, 0x8D, 0x02, 0x60, 0xA9, 0xFF, 0x8D,
//  0x03, 0x50, 0xA9, 0x00, 0x8D, 0x08, 0x02, 0x20, 0x23, 0x80, 0xAD, 0x00, 0x02, 0x8D, 0x01, 0x50,
//  0x4C, 0x17, 0x80, 0xA9, 0x08, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAD, 0x08, 0x02, 0x8D, 0x00,
//  0x60, 0xAD, 0x08, 0x02, 0xCD, 0x00, 0x60, 0xD0, 0xF8, 0xA9, 0x20, 0x0D, 0x08, 0x02, 0xCD, 0x00,
//  0x60, 0xD0, 0xFB, 0xA9, 0x10, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAE, 0x08, 0x02, 0xAD, 0x01,
//  0x60, 0x9D, 0x00, 0x02, 0xAD, 0x08, 0x02, 0x8D, 0x00, 0x60, 0x60
//};

// Scrolling_LED - Reads ADC input 0, uses that data to set VIA1 timer1 in oneshot, scrolls LED on VIA2 port A
//byte data[] = {
//  0xA9, 0x00, 0x8D, 0x03, 0x60, 0x8D, 0x02, 0x50, 0xA9, 0xDF, 0x8D, 0x02, 0x60, 0xA9, 0xFF, 0x8D, 
//  0x03, 0x50, 0xA9, 0x00, 0x8D, 0x08, 0x02, 0xA9, 0x01, 0x8D, 0x01, 0x50, 0x2E, 0x01, 0x50, 0x20, 
//  0x73, 0x80, 0x2E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x2E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x2E, 0x01, 
//  0x50, 0x20, 0x73, 0x80, 0x2E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x2E, 0x01, 0x50, 0x20, 0x73, 0x80, 
//  0x2E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 
//  0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 
//  0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 0x73, 0x80, 0x6E, 0x01, 0x50, 0x20, 0x73, 0x80, 
//  0x4C, 0x1C, 0x80, 0x20, 0x93, 0x80, 0x20, 0x7A, 0x80, 0x60, 0xA9, 0x00, 0x8D, 0x0B, 0x60, 0x8D, 
//  0x06, 0x60, 0xAD, 0x00, 0x02, 0x8D, 0x05, 0x60, 0xA9, 0x40, 0x2C, 0x0D, 0x60, 0xF0, 0xFB, 0xAD, 
//  0x06, 0x60, 0x60, 0xA9, 0x08, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAD, 0x08, 0x02, 0x8D, 0x00, 
//  0x60, 0xAD, 0x08, 0x02, 0xCD, 0x00, 0x60, 0xD0, 0xF8, 0xA9, 0x20, 0x0D, 0x08, 0x02, 0xCD, 0x00, 
//  0x60, 0xD0, 0xFB, 0xA9, 0x10, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAE, 0x08, 0x02, 0xAD, 0x01, 
//  0x60, 0x9D, 0x00, 0x02, 0xAD, 0x08, 0x02, 0x8D, 0x00, 0x60, 0x18, 0x60
//};

byte data[] = {
  0xA9, 0x00, 0x8D, 0x03, 0x60, 0x8D, 0x02, 0x50, 0xA9, 0x9F, 0x8D, 0x02, 0x60, 0xA9, 0xFF, 0x8D, 0x03, 0x50, 0xA9, 0x00, 0x8D, 0x08, 0x02, 0xA9, 0x01, 0x8D, 0x01, 0x50, 0xA9, 0xFF, 0x8D, 0x03, 0x60, 0x8D, 0x01, 0x60, 0xA9, 0xFE, 0x8D, 0x01, 0x60, 0x8D, 0x09, 0x02, 0xA9, 0x01, 0x2C, 0x09, 0x02, 0xD0, 0x2D, 0xA9, 0xFD, 0x8D, 0x01, 0x60, 0x8D, 0x09, 0x02, 0xA9, 0x02, 0x2C, 0x09, 0x02, 0xD0, 0x26, 0xA9, 0xFB, 0x8D, 0x01, 0x60, 0x8D, 0x09, 0x02, 0xA9, 0x04, 0x2C, 0x09, 0x02, 0xD0, 0x1F, 0xA9, 0xF7, 0x8D, 0x01, 0x60, 0x8D, 0x09, 0x02, 0xA9, 0x08, 0x2C, 0x09, 0x02, 0xD0, 0x18, 0xA9, 0xCC, 0x8D, 0x0A, 0x20, 0x4C, 0x85, 0x80, 0xA9, 0x99, 0x8D, 0x0A, 0x20, 0x4C, 0x85, 0x80, 0xA9, 0x66, 0x8D, 0x0A, 0x20, 0x4C, 0x85, 0x80, 0xA9, 0x33, 0x8D, 0x0A, 0x20, 0x4C, 0x85, 0x80, 0xA9, 0xFF, 0x8D, 0x0A, 0x20, 0xA9, 0xFF, 0x8D, 0x03, 0x60, 0x8D, 0x01, 0x60, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x2E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x6E, 0x01, 0x50, 0x20, 0xE4, 0x80, 0x4C, 0x1C, 0x80, 0x20, 0xE8, 0x80, 0x60, 0xA9, 0x00, 0x8D, 0x0B, 0x60, 0x8D, 0x06, 0x60, 0xAD, 0x0A, 0x20, 0x8D, 0x05, 0x60, 0xA9, 0x40, 0x2C, 0x0D, 0x60, 0xF0, 0xFB, 0xAD, 0x06, 0x60, 0x60, 0xA9, 0x08, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAD, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAD, 0x08, 0x02, 0xCD, 0x00, 0x60, 0xD0, 0xF8, 0xA9, 0x20, 0x0D, 0x08, 0x02, 0xCD, 0x00, 0x60, 0xD0, 0xFB, 0xA9, 0x10, 0x0D, 0x08, 0x02, 0x8D, 0x00, 0x60, 0xAE, 0x08, 0x02, 0xAD, 0x01, 0x60, 0x9D, 0x00, 0x02, 0xAD, 0x08, 0x02, 0x8D, 0x00, 0x60, 0x18, 0x60  
};

// All vectors point to $8000, the start of the ROM
byte vector_data[] = {
  0x00, 0x80, 0x00, 0x80, 0x00, 0x80
};
