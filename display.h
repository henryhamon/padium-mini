#ifndef DISPLAY_H
#define DISPLAY_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include "images.h"

#define TFT_SCK 22
#define TFT_MOSI 21 // default ESP32 SDA pin
#define TFT_DC 12 // Data/command
#define TFT_RST 14
#define TFT_CS 27 // Chip select
#define TFT_BL 13 // Backlight control

#define TFT_MISO -1

Adafruit_GC9A01A display(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST, -1);

// Theme Palette: #605678, #8ABFA3, #FFBF61, #FFE6A5
#define GC9_DARKGRAY ((55 & 0xf8) << 8) | ((62 & 0xfc) << 3) | (78 >> 3)
#define GC9_PURPLE ((96 & 0xf8) << 8) | ((86 & 0xfc) << 3) | (120 >> 3)
#define GC9_SAGE ((138 & 0xf8) << 8) | ((191 & 0xfc) << 3) | (163 >> 3)
#define GC9_ORANGE ((255 & 0xf8) << 8) | ((191 & 0xfc) << 3) | (97 >> 3)
#define GC9_BEIGE ((255 & 0xf8) << 8) | ((230 & 0xfc) << 3) | (165 >> 3)

const int center_x = 120;// center x of dial on 240*240 TFT display
const int center_y = 120;// center y of dial on 240*240 TFT display
int x_pos;
int y_pos; 

void drawCentreString(const String &buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
   // display.setTextWrap(true,true);
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void MainTitle(const String &buf)
{
  display.setTextSize(10);
  drawCentreString(buf, center_x, 30);
}

void SelectionTitle()
{

}

void SelectedPad()
{

}

void MainScreen()
{
  display.fillScreen(GC9_DARKGRAY);
  display.setTextColor(GC9_ORANGE);
  display.setTextSize(10);
  drawCentreString("A#", center_x, 30);

  display.fillRect(0, 146, 240, 90, GC9_BEIGE);
  display.fillRoundRect(4, 125, 230, 33, 25, GC9_SAGE);

  display.setTextColor(GC9A01A_WHITE);
  display.setTextSize(2);
  drawCentreString("Hillsong Pad", center_x + 15, 134);

  display.setTextColor(GC9_PURPLE);
  display.setTextSize(7);
  drawCentreString("A#", center_x, 170);

  display.setTextSize(3);
  drawCentreString("A", 50, 180);
  drawCentreString("B", 190, 180);
}

void displayRefresh()
{
    display.fillScreen(GC9_DARKGRAY);
    if (currentNotePlaying > -1) { // it's playing
        display.setTextColor(GC9A01A_YELLOW);
        display.setTextSize(10);
        drawCentreString(NOTES[currentNotePlaying], center_x, 30);
    }
    display.setTextColor(GC9A01A_WHITE);
    display.setTextSize(2);
    drawCentreString(PADS[currentPad], center_x + 10, center_y);
    display.setTextColor(GC9A01A_RED);
    display.setTextSize(7);
    drawCentreString(">_" + NOTES[selectedNote] + "_<", center_x, center_y + 30);
}

void displayBoot() {
    display.fillScreen(GC9A01A_WHITE);
    display.drawBitmap(0,0, epd_logo_hamOn, 240, 240, GC9A01A_BLUE);
    display.setTextSize(5);
    delay(500);
    display.fillScreen(GC9A01A_WHITE);
    display.drawBitmap(0,0, epd_padium_logo, 240, 240, GC9A01A_BLUE);   
    delay(4000);
    //displayRefresh();
    MainScreen();
}

void displayInit() {
  Serial.println("GC9A01A initialization!");
  display.begin();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  display.begin(40000000);
  display.setRotation(0);
  
  displayBoot();
}

#endif

