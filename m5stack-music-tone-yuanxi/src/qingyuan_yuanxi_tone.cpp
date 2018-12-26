#include <Arduino.h>
#include <pitches.h>
#include <Tone32.h>
//#include <M5Stack.h>

#define BUZZER_PIN 25

#define LEDCCHANNEL 1

//Duration of one beat at 4/4: quarter note = BEAT = ((1/4) * 1000)
#define SIXTEENTH_NOTE 63 //((1/4/*quarter note*/) * 1000/*1 sec = 1000 ms*/ / 4 /* 1/16 note = quarter note /4 */)

#include "pitches.h"

portMUX_TYPE taskMux = portMUX_INITIALIZER_UNLOCKED;
static xSemaphoreHandle sem;

void playMusicTone(int number) {
  // notes in the melody:
  //for Qing-Yu-An-Yuan-Xi: C major, beat 4/4
  int melody[] = {
    CL_LA, CL_LA, CL_XI, C_DO, C_MI,    /*1*/
    C_FA, C_DO, CL_XI,                  /*2*/
    CH_FA, CH_DO, C_XI, C_XI, CH_DO,    /*3*/
    CH_RE, C_XI, C_LA,                  /*4*/
    C_LA,                               /*5*/
    //C_LA,                               /*6*/

    CH_MI, CH_DO, C_LA, 0, C_MI,        /*7*/
    CH_MI, CH_RE, C_XI, C_XI, 0, C_MI,  /*8*/
    CH_RE, C_XI, CH_FA, CH_MI,          /*9*/
    C_XI,  0,                             /*10*/
    C_MI, C_LA, CH_MI, C_LA,            /*11*/
    CH_SO, CH_FA, CH_MI, CH_RE, CH_RE, CH_MI, CH_FA, /*12*/
    CH_MI, C_MI, C_MI,                  /*13*/
    CH_FA, CH_MI, CH_RE, CH_FA,         /*14*/
    CH_MI, C_MI, C_MI, CH_DO, C_XI,     /*15*/
    C_LA,                               /*16*/
    //C_LA,                               /*17*/

    CH_MI, CH_DO, C_LA, C_MI,           /*18*/
    CH_RE, CH_MI, C_XI,                 /*19*/
    0, CH_RE, CH_MI, C_XI, C_MI, 0, C_MI,/*20*/
    CH_MI, C_XI, 0,                       /*21*/
    C_MI, C_LA, 0, CH_MI, C_LA,         /*22*/
    CH_SO, CH_FA, CH_MI, CH_RE, CH_RE, CH_MI, CH_FA, /*23*/
    CH_MI, C_MI, C_MI,                  /*24*/
    CH_FA, CH_MI, CH_RE, CH_FA,         /*25*/
    CH_MI, CH_MI, C_MI, C_XI, CH_MI,     /*26*/
    C_LA,        0,                       /*27*/
    //C_LA,                               /*28*/

    //    CH_MI, C_LA, CH_MI, C_LA,           /*29*/
    //    CH_FA, CH_FA_SHARP, CH_DO, CH_DO, C_XI,  /*30*/
    //    CH_FA, CH_FA_SHARP, CH_DO, CH_DO, C_XI,  /*31*/
    //    CH_RE, CH_RE, CH_DO, C_XI, C_LA,    /*32*/

  };

  int noteDurations[] = {
    4 + 2, 1, 1, 4, 4,      /*1*/
    4, 4, 4 + 4,            /*2*/
    4, 4, 4 + 2, 1, 1,      /*3*/
    4 + 2, 2, 4 + 4,          /*4*/
    4 + 4 + 4 + 4,          /*5*/
    //4 + 4 + 4 + 4,          /*6*/

    2 + 1, 1, 4 + 4, 2, 2,  /*7*/
    4, 2, 2, 4, 2, 2,       /*8*/
    4, 4, 4 + 2, 2,         /*9*/
    4 + 4 , 4 + 4,          /*10*/
    4, 4, 4, 4,             /*11*/
    2, 4, 2, 4, 1, 2, 1,    /*12*/
    4 + 4 + 4, 2, 2,        /*13*/
    2, 2, 4 + 4, 4,         /*14*/
    4, 2, 2, 4, 4,          /*15*/
    4 + 4 + 4 + 4,          /*16*/
    //4 + 4 + 4 + 4,          /*17*/

    2 + 1, 1, 4 + 4, 4,     /*18*/
    2 + 1, 1, 4 + 4 + 4,    /*19*/
    4, 2, 2, 2, 2, 2, 2,    /*20*/
    4 + 2 , 4, 4 + 2, /*21*/
    4, 4, 2, 2, 4,          /*22*/
    2, 4, 2, 4, 1, 2, 1,    /*23*/
    4 + 4 + 4, 2, 2,        /*24*/
    2, 2, 4 + 4, 4,         /*25*/
    4, 2, 2, 4, 4,          /*26*/
    4 + 4 , 4 + 4,          /*27*/
    //4 + 4 + 4 + 4,          /*28*/

    //    4 + 2, 2, 4 + 2, 2,     /*29*/
    //    2, 2, 2, 2, 4 + 4,      /*30*/
    //    2, 2, 2, 2, 4 + 4,      /*31*/
    //    2, 2, 2, 2, 4 + 4,      /*32*/
  };

  for (int i = 0; i < number; i++) {
    //  iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < (sizeof(melody) / sizeof(int)); thisNote++) {

      // to calculate the note duration, use the pre-defined beat configuration
      //e.g. one beat = BEAT = ((1/4) * 1000),quarter note = 1 * BEAT, eighth note = (1/2) * BEAT, etc.
      int noteDuration = SIXTEENTH_NOTE * noteDurations[thisNote];
      if (melody[thisNote] == 0) {
        delay(noteDuration);
      } else {
        tone(BUZZER_PIN, melody[thisNote], noteDuration, LEDCCHANNEL);
      }
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(BUZZER_PIN, LEDCCHANNEL);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start Play song of \'YuanXi\'");
  playMusicTone(1);
  Serial.println("Music Play Finished, Press Reset button to continue.");
}

void loop() {
  vTaskDelay(portMAX_DELAY);
}
