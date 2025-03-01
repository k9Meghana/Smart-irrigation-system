// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;

Adafruit_LiquidCrystal lcd(0);

#define SOIL_MOISTURE_PIN A1
#define LIGHT_SENSOR_PIN A3  // Using a Potentiometer as a Light Sensor
#define TEMP_SENSOR_PIN A2  // LM35 Temperature Sensor
int PUMP_PIN=5;
int RED_LED=2;
int GREEN_LED=4;


unsigned long lastIrrigationTime = 0;
const long irrigationInterval = 30;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
    
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(TEMP_SENSOR_PIN, INPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
  
    lcd.setBacklight(0);
}

void loop()
{
  
   int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
    int lightLevel = analogRead(LIGHT_SENSOR_PIN);
    int tempValue = analogRead(TEMP_SENSOR_PIN);
    float temperature = tempValue * (5.0 / 1023.0) * 100.0; // Convert LM35 output to °C
    unsigned long currentMillis = millis();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.setBacklight(1);
    lcd.print("Soil: ");
    lcd.print(soilMoisture);

    lcd.setCursor(0, 1);
    lcd.setBacklight(1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    
    lcd.setBacklight(1);
    Serial.print("Soil Moisture: "); 
    Serial.println(soilMoisture);
    lcd.setBacklight(1);
    Serial.print("Temp: "); 
    Serial.println(temperature);
    lcd.clear();
    lcd.setBacklight(1);
    Serial.print("Light: "); 
    Serial.println(lightLevel);
    lcd.clear();
    
    Serial.print(currentMillis);

    // LED Indicator Logic
    if (soilMoisture < 400) {
        digitalWrite(RED_LED, HIGH);  // Soil is dry → Red LED ON
        digitalWrite(GREEN_LED, LOW);
        lcd.print("Soil is dry..!"); // Green LED OFF
    } 
    else {
        digitalWrite(RED_LED, LOW);   // Soil is wet → Red LED OFF
        digitalWrite(GREEN_LED, HIGH); // Green LED ON
        lcd.print("soil is wet..!");
    }

    // Simulated Irrigation Every 30 Seconds
    if (currentMillis - lastIrrigationTime >= irrigationInterval) {
        lastIrrigationTime = currentMillis;

        if (soilMoisture < 400 && lightLevel > 200 && temperature > 20) { // Conditions
            digitalWrite(PUMP_PIN, HIGH);
            lcd.setCursor(0, 1);
            lcd.setBacklight(1);
            lcd.print("Irrigating...");
            Serial.print("Irrigating..");
            delay(5000); // Simulated watering time
            digitalWrite(PUMP_PIN, LOW);
        }
    }

    delay(2000);
}