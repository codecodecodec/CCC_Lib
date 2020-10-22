#ifndef CCC
#define CCC

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>

#include <TM1637Display.h>  // CHRONOMETRE

/****                    - - - - CHRONOMETRE - - - -                    ****/

#define DIGIT_OFF     0b00000000
#define DIGIT_ZERO    0b00111111    // 0
#define DIGIT_ONE     0b00000110    // 1
#define DIGIT_TWO     0b01011011    // 2
#define DIGIT_THREE   0b01001111    // 3
#define DIGIT_FOUR    0b01100110    // 4
#define DIGIT_FIVE    0b01101101    // 5
#define DIGIT_SIX     0b01111101    // 6
#define DIGIT_SEVEN   0b00000111    // 7
#define DIGIT_EIGHT   0b01111111    // 8
#define DIGIT_NINE    0b01101111    // 9

const uint32_t liste[] = {3600000, 600000, 60000, 10000, 1000, 100, 10, 1, 0};

const uint8_t chiffres[] = {DIGIT_ZERO, DIGIT_ONE, DIGIT_TWO, DIGIT_THREE, DIGIT_FOUR, DIGIT_FIVE,
                            DIGIT_SIX, DIGIT_SEVEN, DIGIT_EIGHT, DIGIT_NINE, DIGIT_OFF};

const uint8_t SEG_1[] = {
  SEG_A,     
  0,
  0,
  0,         
};


const uint8_t SEG_2[] = {
  0,     
  SEG_A,
  0,
  0,         
};

const uint8_t SEG_3[] = {
  0,
  0,     
  SEG_A,
  0,         
};

const uint8_t SEG_4[] = {
  0,  
  0,
  0,   
  SEG_A,         
};

const uint8_t SEG_5[] = {
  0,     
  0,
  0,  
  SEG_B,       
};

const uint8_t SEG_6[] = {
  0,     
  0,
  0,  
  SEG_C,       
};

const uint8_t SEG_7[] = {
  0,     
  0,
  0,  
  SEG_D,       
};

const uint8_t SEG_8[] = {
  0,     
  0,
  SEG_D,  
  0,     
};

const uint8_t SEG_9[] = {
  0,     
  SEG_D,    
  0,
  0,   
};

const uint8_t SEG_10[] = {
  SEG_D,   
  0,     
  0,
  0,
};

const uint8_t SEG_11[] = {
  SEG_E,
  0,
  0,
  0,
};

const uint8_t SEG_12[] = {
  SEG_F,
  0,
  0,
  0,
};

uint32_t *chrono(int etat = 0);
void afficher_chiffres(TM1637Display display, uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void animation(TM1637Display display);

/****                  - - - - END CHRONOMETRE - - - -                  ****/

/****                    - - - - MACHINE A BLAGUE - - - -                    ****/

#define ARDUINO_TX 4
#define ARDUINO_RX 3

/*********      All Commands      *************/
#define         PLAY              0X01        //
#define         NEXT_SONG         0X03        //
#define         STOP              0X0E        //
#define         SET_VOLUME        0X31        //
#define         SEL_DEV           0X35        //
  #define         DEV_TF            0X01      //
#define         PLAY_COMBINE      0X45        //
/**********************************************/

SoftwareSerial myMP3(ARDUINO_RX, ARDUINO_TX);
int8_t Send_buf[6] = {0};

void open_smart_initialisation(void);
int temps_appuye(int bttn);
int temps_relache(int bttn);

void mp3Basic(int8_t command);
void mp3_5bytes(int8_t command, uint8_t dat);
void envoie_commande(int8_t command, int16_t dat = 0);
void sendBytes(uint8_t nbytes);
void change_volume(int8_t vol);

/****                  - - - - END MACHINE A BLAGUE - - - -                  ****/

/****                  - - - - CAPTEUR DE DISTANCE - - - -                  ****/

int ultrason(int pinTrig, int pinEcho);

/****                  - - - - END CAPTEUR DE DISTANCE - - - -                  ****/

/****                  - - - - RADAR A BUZZER - - - -                  ****/

void buzz_buzz(int buzzer, int temps, int volume = 0);

/****                  - - - - END RADAR A BUZZER - - - -                  ****/

#endif /* CCC */
