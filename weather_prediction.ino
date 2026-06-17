#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Khởi tạo LCD 1602 I2C (Địa chỉ mặc định thường là 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;

// Chân đọc cảm biến mưa (Chọn chân ADC như GPIO 34)
const int rainSensorPin = 34;

void setup() {
  Serial.begin(115200);

  // Khởi động màn hình LCD
  lcd.init();
  lcd.backlight();

  // Khởi động cảm biến góc/gia tốc MPU6050
  if (!mpu.begin()) {
    lcd.print("MPU6050 Error!");
    while (1) delay(10);
  }

  pinMode(rainSensorPin, INPUT);
  lcd.print("Weather Project");
  lcd.setCursor(0, 1);
  lcd.print("System Ready...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Đọc giá trị từ cảm biến mưa
  int rainValue = analogRead(rainSensorPin);

  // Đọc dữ liệu từ MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Hiển thị dòng 1: Giá trị cảm biến mưa
  lcd.setCursor(0, 0);
  lcd.print("Rain Vol: ");
  lcd.print(rainValue);
  lcd.print("   "); // Xóa ký tự thừa phía sau nếu có

  // Hiển thị dòng 2: Trục X và Y của MPU6050 (để biết bo mạch có bị nghiêng do gió/mưa không)
  lcd.setCursor(0, 1);
  lcd.print("X:");
  lcd.print(a.acceleration.x, 1);
  lcd.print(" Y:");
  lcd.print(a.acceleration.y, 1);

  delay(500); // Cập nhật lại sau mỗi 0.5 giây
}