#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Khởi tạo
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;

const int rainSensorPin = 34;
const int ta195Pin = 35; // Giả sử chân ADC cho cảm biến dòng

void setup() {
  Serial.begin(115200);
  Wire.begin();

  lcd.init();
  lcd.backlight();

  if (!mpu.begin()) {
    lcd.print("MPU6050 Error!");
    while (1);
  }

  pinMode(rainSensorPin, INPUT);
  pinMode(ta195Pin, INPUT);

  lcd.print("System Initialized");
  delay(1000);
  lcd.clear();
}

void loop() {
  // 1. Đọc cảm biến mưa
  int rainValue = analogRead(rainSensorPin);

  // 2. Đọc cảm biến dòng TA195
  int currentRaw = analogRead(ta195Pin);

  // 3. Đọc MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Hiển thị luân phiên trên LCD để không bị quá tải ký tự
  // Trang 1: Mưa và Dòng điện
  lcd.setCursor(0, 0);
  lcd.print("Rain:"); lcd.print(rainValue);
  lcd.setCursor(0, 1);
  lcd.print("Amp:"); lcd.print(currentRaw);
  delay(2000);

  // Trang 2: Góc nghiêng MPU
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MPU X:"); lcd.print(a.acceleration.x, 1);
  lcd.setCursor(0, 1);
  lcd.print("MPU Y:"); lcd.print(a.acceleration.y, 1);
  delay(2000);
  lcd.clear();
}