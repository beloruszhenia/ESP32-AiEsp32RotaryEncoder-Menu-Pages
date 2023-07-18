//робить базове меню та енкодер
#include <Wire.h>
#include "AiEsp32RotaryEncoder.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Menu.h>

#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22

#define ROTARY_ENCODER_A_PIN 18
#define ROTARY_ENCODER_B_PIN 19
#define ROTARY_ENCODER_BUTTON_PIN 17
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

String options[] = {"Option 1", "Option 2", "Option 3", "Option 4", "Option 5", "Option 6", "Option 7", "Option 8", "Option 9", "Option 10"};
Menu menu(options, 10, 0, 0, 1); // create menu instance

void rotary_onButtonClick()
{
  if (rotaryEncoder.isEncoderButtonClicked()){
    static unsigned long lastTimePressed = 0; // Soft debouncing
    menu.selectButton();
    
    lastTimePressed = millis();
    Serial.print("button pressed ");
    Serial.print(millis());
    Serial.println(" milliseconds after restart");
  }
}

void rotary_loop()
{
    //dont print anything unless value changed
    long tt = rotaryEncoder.encoderChanged();
    if (tt)
    {
      Serial.print("Value: ");
      Serial.println(rotaryEncoder.readEncoder());
      menu.scroll(tt);
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
      rotary_onButtonClick(); 
    }
}

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

void setup() {
  Serial.begin(9600);

  //initialize rotary encoder
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);

  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 1000, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.disableAcceleration();

  //display inicialisation
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Menu Example");
  display.display();
  delay(1500);
}

void loop() {
  rotary_loop();
  rotary_onButtonClick();
  menu.drawMenu();
  int selected = menu.getSelected();  
}