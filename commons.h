
#ifndef COMMONS_H
#define COMMONS_H

#define DEBOUNCE_TIME 25
#define PITCH_UP 33
#define PITCH_DOWN 25
#define ACTION 32

const int BTN_DOWN = 0;
const int BTN_PLAY = 1;
const int BTN_UP = 2;

const String MENU[] = {"Pad", "Volume", "Equalization", "Fader In/Out (ms)"};

const String NOTES[] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
/****
Folder structure

01 - WorshipPadz
02 - MPads Ambient
03 - MMQA Worship
04 - Hillsong
*****/
const String PADS[] = {"WorshipPadz", "MPads Ambient", "MMQA Worship",  "HillSong Pad"};

int currentPad = 3;
int currentNote = -1;
int selectedNote = 0;
int Fader = 50;
int currentVol = 20;
int currentNotePlaying = -1; // -1 is null
const int NUM_BUTTONS = 3;

int trackUp(int current){
    current += 1;
    current = current % 12;
    return current;
}

int trackDown(int current){
    current -= 1;
    if(current < 0){
        current = 11;
    }
    return current;
}
#endif