/// Esp32 version
#include <ezButton.h>

#include "commons.h"
#include "display.h"

ezButton buttons[] = {PITCH_DOWN, ACTION, PITCH_UP};

void onButtonPressed(int idxBtn)
{
  int currTrck = -1;

  if (idxBtn == BTN_PLAY) {
    if (currentNotePlaying > -1) { 
      if (currentNotePlaying == selectedNote) {
        // stop
        Serial.println("stop");
        currentNotePlaying = -1;
        // stopAudio();
      } else {
        // play
        Serial.println("play");
        onChangeTrack(currentNote, selectedNote);
        currentNotePlaying = selectedNote;
        currentNote = selectedNote;
        // playAudio(currentPad + 1, currentNotePlaying + 1);
      }
    } else {
      // play
      Serial.println("play");
      onChangeTrack(currentNote, selectedNote);
      currentNotePlaying = selectedNote;
      currentNote = selectedNote;
      // playAudio(currentPad + 1, currentNotePlaying + 1);
    }
  }

  if (idxBtn == BTN_DOWN) {
    currTrck = selectedNote;
    selectedNote = trackDown(selectedNote);
    onChangeTrackCarousel(currTrck, selectedNote);
    Serial.print(NOTES[selectedNote]);
    Serial.println(" is Current Note ");
    Serial.print(selectedNote);
    Serial.println("");
  }

  if (idxBtn == BTN_UP) {
    currTrck = selectedNote;
    selectedNote = trackUp(selectedNote);
    onChangeTrackCarousel(currTrck, selectedNote);
    Serial.print(NOTES[selectedNote]);
    Serial.println(" is Current Note ");
    Serial.print(selectedNote);
    Serial.println("");
  }
}

void footSetup()
{

  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].setDebounceTime(DEBOUNCE_TIME);
  }
}

void footEvent()
{
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].loop();

    if (buttons[i].isPressed()) {
      Serial.print(i);
      Serial.println(" Btn is pressed");
      onButtonPressed(i);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Booting.."));

  displayInit();
  footSetup();
  onChangeTrackCarousel(0, 0);
}

void loop()
{
  footEvent();
}
