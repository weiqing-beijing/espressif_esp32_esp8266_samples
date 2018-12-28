#include <pitches.h>
#include <Tone32.h>

#ifdef M5Stack_Core_ESP32
#define BUZZER_PIN 25
#else
#ifdef ESP32_DEV
#define BUZZER_PIN 27
#endif
#define BUZZER_PIN 27
#endif

#define LEDCCHANNEL 1

#include "pitches.h"

// notes in the melody:
int melody[] = {
  A_SO,  A_LA, AH_DO,  AH_RE,  AH_SO,  AH_RE,  A_SO, A_LA, AH_DO,  AH_RE,  AH_SO,  AH_RE,  /*前奏*/A_LA, A_LA, A_SO, A_MI, A_RE, A_DO, A_MI, A_RE, A_DO, AL_LA,  AL_SO,  AL_SO,  /*沧海笑，滔滔两岸潮*/ AL_SO,  AL_LA,  AL_SO,  AL_LA,  A_DO,  A_RE,  A_MI, A_SO, A_LA,  A_SO,  A_MI, A_RE, A_DO, A_RE, /*浮沉随浪记今朝*/ A_LA, A_LA, A_SO, A_MI, A_RE, A_DO, A_MI, A_RE, A_DO, AL_LA,  AL_SO,  AL_SO,  /*苍天笑纷纷世上潮*/  AL_SO,  AL_LA,  AL_SO,  AL_LA,  A_DO,  A_RE,  A_MI, A_SO, A_LA,  A_SO,  A_MI, A_RE, A_DO, A_DO, /*豪情仍在痴痴笑笑*/A_LA, A_LA, A_SO, A_MI, A_RE, A_DO, A_MI, A_RE, A_DO, AL_LA,  AL_SO,  AL_SO,  AL_LA,  AL_SO,  AL_LA,  A_DO, A_RE, A_MI, A_SO, A_LA, A_SO, A_SO, A_SO, A_MI, A_RE, A_DO, A_RE  /*尾声*/
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8,  8,  8,  8,  4,  4,  8,  8,  8,  8,  4,  4,  /*前奏*/4,  8,  8,  4,  8,  1,  4,  8,  4,  8,  8,  1,  /*沧海笑，滔滔两岸潮*/ 4,  8,  4,  8,  4,  8,  4,  4,  4,  8,  8,  8,  4,  2,  /*浮沉随浪记今朝*/4, 8,  8,  4,  8,  1,  4,  8,  4,  8,  8,  1,  /*苍天笑纷纷世上潮*/  4,  8,  4,  8,  4,  8,  4,  4,  4,  8,  8,  8,  4,  1,  /*豪情仍在痴痴笑笑*/  4,  8,  8,  4,  8,  1,  4,  8,  4,  8,  1,  4,  8,  4,  8,  4,  8,  4,  8,  4,  8,  8,  8,  8,  8,  8,  1 /*尾声*/
};

void setup() {
  //  iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(melody)/sizeof(int)); thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 800 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration, LEDCCHANNEL);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN, LEDCCHANNEL);
  }

}

void loop() {
  // no need to repeat the melody.

  //  ledcAttachPin(27, 1);
  //
  //  ledcWriteTone(1, 440);
  //  delay(500);
  //  ledcDetachPin(27);
  //
  //  ledcWrite(1, 0);
  //  delay(100);
  //  ledcAttachPin(27, 1);
  //  ledcWriteTone(1, 880);
  //
  //  delay(500);
  //
  //  ledcDetachPin(27);
  //
  //  ledcWrite(1, 0);
  //  delay(300);
}
