/****                    - - - - CHRONOMETRE - - - -                    ****/

uint32_t *chrono(TM1637Display display, int etat = 0)       // Cette fonction permet toutes les interactions avec le temps
{                                                           // du chronomètre sur un ecran 4 digits
  static uint32_t original = 0;
  static uint32_t milli_en_trop = 0;
  static uint32_t pause = 0;
  static int decimal = 0;
  uint32_t temps = 0;
  static uint32_t digits[] = {0, 0, 0, 0};                  // C'est une liste de 4 nombres

  if (etat >= 0)                                            // Si l'etat est superieur ou egal a 0,
  {                                                         // ca veut dire qu'on lance le chrono.
    decimal = etat;                                         // Le nombre correspond a l'ordre de grandeur du chrono
    if (decimal > 4)                                        // (heures, minutes, secondes, dixiemes, centieme, millieme)
      decimal = 4;
  }
  if (etat == -2)                                           // Si l'etat est egal a -2, il reinitialise tout le chrono
  {
    original = 0;
    milli_en_trop = 0;
    pause = 0;
    afficher_chiffres(display, 0, 0, 0, 0);
    return digits;
  }
  if (etat == -1)                                           // Si l'etat est egal a -1, on met le chrono en pause si il ne l'est pas,
  {
    pause = millis();
    return digits;
  }
  if (pause != 0)                                           // et le remet en route si il est deja en pause
  {
    milli_en_trop += millis() - pause;
    pause = 0;
  }
  else if (original == 0)
  {
    original = millis();
  }
  temps = millis() - original - milli_en_trop;
  digits[0] = temps / liste[decimal];
  temps %= liste[decimal];
  digits[1] = temps / liste[decimal + 1];
  temps %= liste[decimal + 1];
  digits[2] = temps / liste[decimal + 2];
  temps %= liste[decimal + 2];
  digits[3] = temps / liste[decimal + 3];
  afficher_chiffres(display, digits[0], digits[1], digits[2], digits[3]);
  return digits;
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void afficher_chiffres(TM1637Display display, uint8_t a, uint8_t b, uint8_t c, uint8_t d)  // Cette fonction affiche 4 chiffres
{                                                                                          // sur un ecran 4 digits
  uint8_t affiche[] = {chiffres[a], chiffres[b], chiffres[c], chiffres[d]};

  display.setSegments(affiche);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void ecran_gagnant(TM1637Display display)                   // Cette fonction fait une petite animation sur l'ecran 4 digits
{
  display.setSegments(SEG_1);
  delay(150);
  display.setSegments(SEG_2);
  delay(150);
  display.setSegments(SEG_3);
  delay(150);
  display.setSegments(SEG_4);
  delay(150);
  display.setSegments(SEG_5);
  delay(150);
  display.setSegments(SEG_6);
  delay(150);
  display.setSegments(SEG_7);
  delay(150);
  display.setSegments(SEG_8);
  delay(150);
  display.setSegments(SEG_9);
  delay(150);
  display.setSegments(SEG_10);
  delay(150);
  display.setSegments(SEG_11);
  delay(150);
  display.setSegments(SEG_12);
  delay(150);
}

/****                  - - - - END CHRONOMETRE - - - -                  ****/

/****                    - - - - MACHINE A BLAGUE - - - -                    ****/

void open_smart_setup(void)          // Cette fonction initialise l'Open-Smart mp3 player et d'autres parametres0
{
  myMP3.begin(9600);                 // Initialisation de l'Open-Smart mp3 player
  delay(500);                        // On attend que l'initialisation soit fini
  randomSeed(analogRead(0));         // Creation d'une "seed" pour l'aleatoire
  sendCommand(SEL_DEV, DEV_TF);      // Selection de la carte TF
}

/*---------------------------------------------------------------------------------------------------------------------------*/

int check_low_time(void)
{
  int bttnState = digitalRead(bttn);
  int m_seconds = 0;

  while (bttnState == LOW && m_seconds <= 2000) {
    delay(100);
    m_seconds += 100;
    bttnState = digitalRead(bttn);
  }
  Serial.print("LOW TIME IS ");
  Serial.println(m_seconds);
  return m_seconds;
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void mp3Basic(int8_t command)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x02; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = 0xef; //
  sendBytes(4);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void mp3_5bytes(int8_t command, uint8_t dat)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x03; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command;
  Send_buf[3] = dat;
  Send_buf[4] = 0xef;
  sendBytes(5);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  if(command < 0x10)
    mp3Basic(command);
  else if(command < 0x40)
    mp3_5bytes(command, dat);
  else
    return;
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void sendBytes(uint8_t nbytes)
{
  for(uint8_t i=0; i < nbytes; i++)
  {
    myMP3.write(Send_buf[i]) ;
  }
}

void setVolume(int8_t vol)
{
  mp3_5bytes(SET_VOLUME, vol);
}

/****                  - - - - END MACHINE A BLAGUE - - - -                  ****/
