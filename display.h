#ifndef DISPLAY_H
#define DISPLAY_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include "images.h"
#include "Font4x7Fixed.h"

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

void CurrentTrack(const String &track)
{
  display.setFont(&Font4x7Fixed); 
  display.setTextColor(GC9_ORANGE);
  display.setTextSize(12);
  drawCentreString(track, center_x, 110);
}

void TrackCarousel(const String &prevTrack, const String &selTrack,const String &nextTrack)
{
  display.setFont(&Font4x7Fixed); 
  display.setTextColor(GC9_PURPLE);
  display.setTextSize(8);
  drawCentreString(selTrack, center_x, 230);
  display.setTextSize(4);
  drawCentreString(prevTrack, 55, 200);
  drawCentreString(nextTrack, 185, 200);
}

void SelectedPatchBank(const String &patch)
{
  display.setFont(&Font4x7Fixed); 
  display.setTextColor(GC9A01A_WHITE);
  display.setTextSize(3);
  drawCentreString(patch, center_x + 15, 154);
}

void MainScreen()
{
  // Main
  display.fillScreen(GC9_DARKGRAY);
  // Tracks 
  display.fillRect(0, 146, 240, 90, GC9_BEIGE);
  //Bank Container
  display.fillRoundRect(4, 125, 230, 33, 25, GC9_SAGE);

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
    delay(4000); // must set to one second and add more 2 sec on setup
    MainScreen();

    SelectedPatchBank("Hillsonguiar");
    TrackCarousel("G#", "G", "A");
    CurrentTrack("A#");
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

