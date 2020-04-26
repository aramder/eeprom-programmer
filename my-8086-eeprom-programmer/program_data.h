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

byte program_data[] = {
  0xB0, 0x90, 0xE6, 0x06, 0xE4, 0x00, 0xE6, 0x02, 0xEB, 0xFA
};

// Program at reset address to far JMP to F1000H
byte reset_program_data[] = {
  0xEA, 0x00, 0xF0, 0x00, 0x01
};
