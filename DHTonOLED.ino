#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display connection:
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1  // Reset pin not used
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



// DHT sensor connection:
#define DHT_PIN 2
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  dht.begin();  // Initialize DHT sensor
}

void loop() {
  display.clearDisplay();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  if (isnan(humidity) || isnan(temperature)) {
    // If reading failed, display error message on OLED screen
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Error reading from DHT sensor!");
    display.display();
  } else {
    // If reading successful, display temperature and humidity on OLED screen
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.println(temperature);
    display.print("Humidity: ");
    display.println(humidity);
    display.print(" Love You <3 ");


    display.display();
  }
  // yield();
  delay(2000);  // Wait 2 seconds before taking another reading
}