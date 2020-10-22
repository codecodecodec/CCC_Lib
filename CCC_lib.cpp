/****                    - - - - CHRONOMETRE - - - -                    ****/

uint32_t *chrono(int etat = 0)                              // Cette fonction permet toutes les interactions avec le temps
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
  return digits;
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void afficher_chiffres(TM1637Display display, uint8_t a, uint8_t b, uint8_t c, uint8_t d)  // Cette fonction affiche 4 chiffres
{                                                                                          // sur un écran 4 digits
  uint8_t affiche[] = {chiffres[a], chiffres[b], chiffres[c], chiffres[d]};

  display.setSegments(affiche);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void animation(TM1637Display display)                   // Cette fonction fait une petite animation sur l'écran 4 digits
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

void open_smart_initialisation(void)          // Cette fonction initialise l'Open-Smart mp3 player et d'autres parametres
{
  myMP3.begin(9600);                 // Initialisation de l'Open-Smart mp3 player
  delay(500);                        // On attend que l'initialisation soit fini
  sendCommand(SEL_DEV, DEV_TF);      // Selection de la carte TF
}

/*---------------------------------------------------------------------------------------------------------------------------*/

int temps_appuye(int bttn)
{
    int etat_bouton = digitalRead(bttn);    // Cette variable va lire si le bouton est appuyé ou non
    int m_seconds = 0;                      // Cette variable va compter les millisecondes appuyé

    while (etat_bouton == HIGH) {           // Cette boucle va se répéter tant que le bouton est appuyé (HIGH)
        delay(100);                         // On attend 100 ms
        m_seconds += 100;                   // On ajoute 100 à la variable m_seconds
        etat_bouton = digitalRead(bttn);    // On lit si le bouton est appuyé ou non
    }
    Serial.print("Le temps appuye est de ");// On affiche le temps appuyé sur le moniteur série
    Serial.print(m_seconds);
    Serial.println(" millisecondes");
    return m_seconds;                       // On renvoit le temps appuyé
}

/*---------------------------------------------------------------------------------------------------------------------------*/

int temps_relache(int bttn)
{
  int etat_bouton = digitalRead(bttn);      // Cette variable va lire si le bouton est appuyé ou non
  int m_seconds = 0;                        // Cette variable va compter les millisecondes relaché

  while (etat_bouton == LOW) {              // Cette boucle va se répéter tant que le bouton est relaché (LOW)
    delay(100);                             // On attend 100 ms
    m_seconds += 100;                       // On ajoute 100 à la variable m_seconds
    etat_bouton = digitalRead(bttn);        // On lit si le bouton est appuyé ou non
  }
  Serial.print("Le temps relache est de "); // On affiche le temps relaché sur le moniteur série
  Serial.print(m_seconds);
  Serial.println(" millisecondes");
  return m_seconds;                         // On renvoit le temps relaché
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void mp3Basic(int8_t command)
{
  Send_buf[0] = 0x7e;       //starting byte
  Send_buf[1] = 0x02;       //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = 0xef;
  sendBytes(4);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void mp3_5bytes(int8_t command, uint8_t dat)
{
  Send_buf[0] = 0x7e;       //starting byte
  Send_buf[1] = 0x03;       //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command;
  Send_buf[3] = dat;
  Send_buf[4] = 0xef;
  sendBytes(5);
}

/*---------------------------------------------------------------------------------------------------------------------------*/

void envoie_commande(int8_t command, int16_t dat = 0)
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

void change_volume(int8_t vol)
{
  mp3_5bytes(SET_VOLUME, vol);
}

/****                  - - - - END MACHINE A BLAGUE - - - -                  ****/

/****                  - - - - CAPTEUR DE DISTANCE - - - -                  ****/

int ultrason(int pinTrig, int pinEcho)
{
    int temps = 0;                          // Cette variable va récuperer le temps du signal

    digitalWrite(pinTrig, HIGH);            // On lance un signal
    delayMicroseconds(10);                  // Pendant 10 microsecondes
    digitalWrite(pinTrig, LOW);             // Puis on le stop

    temps = pulseIn(pinEcho, HIGH);         // On récupère le signal envoyé
    return temps;                           // On renvoie le temps récupéré
}

/****                  - - - - END CAPTEUR DE DISTANCE - - - -                  ****/

/****                  - - - - RADAR A BUZZER - - - -                  ****/

void buzz_buzz(int buzzer, int temps, int volume = 0)
{
    digitalWrite(buzzer, HIGH);                     // On allume le buzzer,
    tone(buzzer, 500, volume);                      // On le fait biper au volume indiqué
    delay(temps);                                   // Pendant le temps indiqué
    digitalWrite(buzzer, LOW);                      // Et on eteind le buzzer
}

/****                  - - - - END RADAR A BUZZER - - - -                  ****/