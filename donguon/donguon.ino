#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219; // địa chỉ mặc định 0x40

// Tùy chọn: nếu module của bạn có địa chỉ khác (A0/A1 hàn):
// Adafruit_INA219 ina219(0x41); // ví dụ

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }

  if (!ina219.begin()) {
    Serial.println(F("Không tìm thấy INA219. Kiểm tra dây/I2C địa chỉ!"));
    while (1) delay(10);
  }

  // Hiệu chuẩn cho dải 0–32V, ~2A (mặc định shunt 0.1Ω, gain phù hợp nhiều module)
  ina219.setCalibration_32V_2A();
  // Nếu cần dải thấp hơn, độ phân giải tốt hơn:
  // ina219.setCalibration_16V_400mA();

  Serial.println(F("time_ms,bus_V,shunt_mV,current_mA,power_mW"));
}

void loop() {
  float busVoltage_V   = ina219.getBusVoltage_V();    // điện áp sau shunt (V nguồn)
  float shuntVoltage_mV= ina219.getShuntVoltage_mV(); // sụt áp trên shunt
  float current_mA     = ina219.getCurrent_mA();      // dòng ước tính
  float power_mW       = ina219.getPower_mW();        // công suất ước tính

  // In dạng CSV cho dễ log/plot
  Serial.print(millis());
  Serial.print(',');
  Serial.print(busVoltage_V, 3);
  Serial.print(',');
  Serial.print(shuntVoltage_mV, 2);
  Serial.print(',');
  Serial.print(current_mA, 1);
  Serial.print(',');
  Serial.println(power_mW, 1);

  delay(500);
}
