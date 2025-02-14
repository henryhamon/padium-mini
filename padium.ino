/// Esp32 version

#include "commons.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  Serial.println(F("Booting.."));

  displayInit();
}

void loop() {
  // put your main code here, to run repeatedly:

}
