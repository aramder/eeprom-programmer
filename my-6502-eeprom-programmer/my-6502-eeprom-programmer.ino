/*
   Programmer for EEPROM for use in my breadboard 6502

   Heavily based on Ben Eater's eeprom programmer

*/

#include "program_data.h"

#define ERASE_LENGTH 0x7FFF
#define PRINT_LENGTH 0x7FFF

// IO defines
#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13

void setup() {
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  digitalWrite(WRITE_EN, HIGH);
  pinMode(WRITE_EN, OUTPUT);
  Serial.begin(115200);
  Serial.print("\r\n\r\n");

  printContents();

  eraseEEPROM();

  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, OUTPUT);
  }

  // Program data bytes
  Serial.print("Programming EEPROM");
  for (int address = 0; address < sizeof(data); address += 1) {
    writeEEPROM(address, data[address]);

    if (address % 128 == 0) {
      Serial.print(".");
    }
  }
  Serial.println(" done");

  Serial.print("Programming vector data");
  for (int address = 0x7FFC; address < 0x7FFF; address += 1) {
    writeEEPROM(address, vector_data[address]);
  }

  printContents();
}

void loop() {
  // Nothing in loop
}

/*
   Output the address bits and outputEnable signal using shift registers.
*/
void setAddress(uint16_t address, bool outputEnable) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

/*
   Read a byte from the EEPROM at the specified address.
*/
byte readEEPROM(int address) {
  setAddress(address, /*outputEnable*/ true);

  byte data = 0;
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

/*
   Write a byte to the EEPROM at the specified address.
*/
void writeEEPROM(uint16_t address, byte data) {
  setAddress(address, /*outputEnable*/ false);
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }
  digitalWrite(WRITE_EN, LOW);
  __asm__("nop\n\t");
  __asm__("nop\n\t");
  digitalWrite(WRITE_EN, HIGH);
  delay(5); // Datasheet specifies 5ms write cycle
}

/*
   Erase contents of EEPROM
*/
void eraseEEPROM(void) {
  Serial.print("Erasing EEPROM");
  for (uint16_t address = 0; address <= ERASE_LENGTH; address += 1) {
    writeEEPROM(address, 0xFF);

    if (address % 128 == 0) {
      Serial.print(".");
    }
  }
  Serial.println(" done");
}

/*
   Read the contents of the EEPROM and print them to the serial monitor.
*/
void printContents() {
  Serial.println("Reading EEPROM");
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, INPUT);
  }

  for (uint16_t base = 0; base <= PRINT_LENGTH; base += 16) {
    byte data[16];
    for (uint16_t offset = 0; offset <= 15; offset += 1) {
      data[offset] = readEEPROM(base + offset);
    }

    char buf[80];
    sprintf(buf, "0x%04x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);

    Serial.println(buf);
  }
}
