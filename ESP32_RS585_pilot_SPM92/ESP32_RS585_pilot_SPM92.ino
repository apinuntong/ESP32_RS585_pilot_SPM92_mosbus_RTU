#include "Crc16.h"
Crc16 crc;
uint16_t Modbus_read_ID1byte(uint8_t id, uint8_t function_code, uint16_t r_register) {
  byte data[8];
  data[0] = id;
  data[1] = function_code;
  data[2] = highByte(r_register);
  data[3] = lowByte(r_register);
  data[4] = highByte(0);
  data[5] = lowByte(1);
  crc.clearCrc();
  unsigned short value = crc.Modbus(data, 0, 6);
  data[6] = lowByte(value);
  data[7] = highByte(value);
  Serial1.write(data, 8);
  byte buffer[7];
  while (!Serial1.available());
  int size = Serial1.readBytes(buffer, 7);
  uint16_t ccnn = (uint16_t)word(buffer[6], buffer[5]);
  crc.clearCrc();
  value = crc.Modbus(buffer, 0, 5);
  if (ccnn == value) {
    return int(word(buffer[3], buffer[4]));
  } else {
    return 0;
  }
}
void Modbus_confi_ID1byte(uint8_t id, uint8_t function_code, uint16_t r_register, uint16_t datas) {
  byte data[8];
  data[0] = id;
  data[1] = function_code;
  data[2] = highByte(r_register);
  data[3] = lowByte(r_register);
  data[4] = highByte(datas);
  data[5] = lowByte(datas);
  crc.clearCrc();
  unsigned short value = crc.Modbus(data, 0, 6);
  data[6] = lowByte(value);
  data[7] = highByte(value);
  Serial1.write(data, 8);
}
void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 17, 4);
  Serial1.setTimeout(100);

}
float kWh = 0;
float V = 0;
float A = 0;
float W = 0;
float Hz = 0;

void loop() {

  uint16_t datas = Modbus_read_ID1byte(0x01, 0x03, 11);
  Serial.println(datas);
  delay(1000);

}
