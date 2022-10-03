/**
 * Este codigo funciona en un Arduino Nano.
 * Los pines en esta version son suficientes para
 * que este funcione.
 * 
 * Hecho y escrito por
 * ===========================
 * ||     Leandro Nieto     ||
 * ===========================
 */
 
static const int pinOuts[]={4,5,6,7,8,9,10,11}; //canales de salida
static const int pinIn=2;                       //pulsador cambia efectos
const int pinStandBy=3;                         //pin pausa
const int totalEffects = 11;                     //Efectos totales
int effectSelec=0;                              //numero que define el efecto a usar
int newEffect=0;                                //numero del nuevo efecto a usar
int tiempo;                                     //almacena el valor en mSeg de retraso en las transiciones
bool isPaused = false;                          //la secuencia esta en pausa?

namespace efectos {
  /*
   * Aqui se declaran las funciones que van a hacer secuencias.
   * Debe tener un bombre que explique qué va a hacer, y no es necesario
   * el uso de atributos.
   */
  void barrido();
  void barridoR();
  void puntos();
  void llenado();
  void dedo();
  void dedoR();
  void barra();
  void navidad();
  void circo();
  void circoR();
  void basico();
}

namespace luces {
  /*
   * Funciones que se encargan de encender los leds y apagarlos,
   * ademas de controlar el tiempo de encendido. Son solo declaraciones.
   * Se recomienda no tocar
   */
  void iluminar(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7);
  void iluminarSinRet(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7);
  void iluminarSolo(int sal, bool d);
  void retardo();
}

void setup() {
  // Funcion setup
  
  for(byte i=0; i<8; i++) {
    pinMode(pinOuts[i],OUTPUT);
    digitalWrite(pinOuts[i],LOW);
  }
  // Declara que los pines siguientes (2 y 3) seran receptores de
  // interrupciones. En arduino Nano, solo estos pines son los capaces
  // de hacer esta funcion.
  // Cuando estos pines detectan un cambio de estado LOW a HIGH (RISING),
  // ejecuta una rutina. Se explica mejor en documento adjunto
  attachInterrupt(digitalPinToInterrupt(pinStandBy), togglePausa, RISING);
  attachInterrupt(digitalPinToInterrupt(pinIn), cambioEfecto, RISING);
  // TODO: Para cambiar de estados mediante el PC sin necesidad de los pulsadores.
  Serial.begin(9600);
}

void loop() {
  // Funcion loop

  // Por cada efecto, se debe agregar un "case" y cambiar su respectivo numero.
  switch (newEffect) {
    case 0:
      effectSelec=0;
      efectos::barrido();
      break;
    case 1:
      effectSelec=1;
      efectos::barridoR();
      break;
    case 2:
      effectSelec=2;
      efectos::puntos();
      break;
    case 3:
      effectSelec=3;
      efectos::llenado();
      break;
    case 4:
      effectSelec=4;
      efectos::dedo();
      break;
    case 5:
      effectSelec=5;
      efectos::dedoR();
      break;
    case 6:
      effectSelec=6;
      efectos::barra();
      break;
    case 7:
      effectSelec=7;
      efectos::navidad();
      break;
    case 8:
      effectSelec=8;
      efectos::circo();
      break;
    case 9:
      effectSelec=9;
      efectos::circoR();
      break;
    case 10:
      effectSelec=10;
      efectos::basico();
      break;
  }
}

/* Funciones de interrupcion */
void cambioEfecto() {
  newEffect++;
  isPaused = false;
  if (newEffect==totalEffects)
    newEffect=0;
}

void togglePausa() {
  isPaused = !isPaused;
}

/* CONF LUCES */

/* Funcion que se encarga de encender los leds */
void luces::iluminar(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7) {
  luces::iluminarSinRet(d0, d1, d2, d3, d4, d5, d6, d7);
  
  // Retardo del efecto
  retardo();
}

void luces::iluminarSinRet(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7) {
  // Las luces no cambian si el efecto cambio
  if(effectSelec!=newEffect) 
    return;

  // Encendido/Apagado de leds
  digitalWrite(pinOuts[0], d0);
  digitalWrite(pinOuts[1], d1);
  digitalWrite(pinOuts[2], d2);
  digitalWrite(pinOuts[3], d3);
  digitalWrite(pinOuts[4], d4);
  digitalWrite(pinOuts[5], d5);
  digitalWrite(pinOuts[6], d6);
  digitalWrite(pinOuts[7], d7);
}

/* Funcion que solo enciende o apaga un LED. El retardo NO esta incluido aqui */
void luces::iluminarSolo(int sal, bool d) {
  // Las luces no cambian si el efecto cambio
  if(effectSelec!=newEffect) 
    return;

  // Encendido/Apagado de leds
  digitalWrite(pinOuts[sal], d);
}

/* Funcion que se encarga del tiempo de retardo.
   Es el tiempo en el que demora el paso de un 
   "frame" del efecrto al otro.*/
void luces::retardo() {
  // No hay retardo si el efecto cambio
  if(effectSelec!=newEffect) 
    return;

  // Valor obtenido [0 ; 1023]
  if (analogRead(A0) < 50)
    // Si el tiempo obtenido es menor a 50, el tiempo es de 50ms
    tiempo = 50;
  else
    tiempo = analogRead(A0);    
  
  // Retardo
  delay(tiempo);

  // El efecto esta en pausa si se pulso el boton de pausa
  while (isPaused) {
    Serial.print("pausa");
  }
}

/* EFECTOS */
void efectos::barrido() {
  /*  1
   *  11000011
   *  11100001
   *  11110000
   *  01111000
   *  00111100
   *  00011110
   *  00001111
   *  10000111
   */
   luces::iluminar(1,1,0,0,0,0,1,1);
   luces::iluminar(1,1,1,0,0,0,0,1);
   luces::iluminar(1,1,1,1,0,0,0,0);
   luces::iluminar(0,1,1,1,1,0,0,0);
   luces::iluminar(0,0,1,1,1,1,0,0);
   luces::iluminar(0,0,0,1,1,1,1,0);
   luces::iluminar(0,0,0,0,1,1,1,1);
   luces::iluminar(1,0,0,0,0,1,1,1);
}

void efectos::barridoR() {
  /*  2
   *  11000011
   *  10000111
   *  00001111
   *  00011110
   *  00111100
   *  01111000
   *  11110000
   *  11100001
   */
   luces::iluminar(1,1,0,0,0,0,1,1);
   luces::iluminar(1,0,0,0,0,1,1,1);
   luces::iluminar(0,0,0,0,1,1,1,1);
   luces::iluminar(0,0,0,1,1,1,1,0);
   luces::iluminar(0,0,1,1,1,1,0,0);
   luces::iluminar(0,1,1,1,1,0,0,0);
   luces::iluminar(1,1,1,1,0,0,0,0);
   luces::iluminar(1,1,1,0,0,0,0,1);
}

void efectos::puntos() {
  /*  3
   *  10000001
   *  01000010
   *  00100100
   *  00011000
   *  00100100
   *  01000010
   *  10000001
   *  00000000
   *  10000001
   *  11000011
   *  11100111
   *  11111111
   *  01111110
   *  00111100
   *  00011000
   *  00000000
   */

  luces::iluminarSinRet(1, 0, 0, 0, 0, 0, 0, 1);
  for(int i=7;i>=0;i--) {
    luces::iluminarSolo(i, HIGH);
    luces::iluminarSolo(7-i, HIGH);
    luces::retardo();
    luces::iluminarSolo(i, LOW);
    luces::iluminarSolo(7-i, LOW);
    luces::retardo();
  }
  for(int i=0;i<4;i++){
    luces::iluminarSolo(i, HIGH);
    luces::iluminarSolo(7-i, HIGH);
    luces::retardo();
  }
  for(int i=0;i<4;i++){
    luces::iluminarSolo(i, LOW);
    luces::iluminarSolo(7-i, LOW);
    luces::retardo();
  }
}

void efectos::llenado() {
  /*  4
   *  10000000
   *  11000000
   *  10100000
   *  10010000
   *  10001000
   *  10000100
   *  10000010
   *  10000001
   *  10000011
   *  10000101
   *  10001001
   *  10010001
   *  10100001
   *  11000001
   *  11100001
   *  11010001
   *  11001001
   *  11000101
   *  11000011
   *  11000111
   *  11001011
   *  11010011
   *  11100011
   *  11110011
   *  11101011
   *  11100111
   *  11101111
   *  11111111
   *  00000000
   *  11111111
   *  00000000
   */

  luces::iluminarSinRet(1, 0, 0, 0, 0, 0, 0, 0);
  for (int j=0; j<3; j++) {
    luces::iluminarSolo(j, HIGH);
    luces::retardo();
    for(int i=1+j; i<7-j; i++) {
      luces::iluminarSolo(i, HIGH);
      luces::retardo();
      luces::iluminarSolo(i, LOW);
    }
    luces::iluminarSolo(7-j, HIGH);
    luces::retardo();
    for(int i=6-j; i>1+j; i--) {
      luces::iluminarSolo(i, HIGH);
      luces::retardo();
      luces::iluminarSolo(i, LOW);
    }
  }

  luces::iluminar(1, 1, 1, 1, 0, 1, 1, 1);
  luces::iluminar(1, 1, 1, 1, 1, 1, 1, 1);
  luces::iluminar(0, 0, 0, 0, 0, 0, 0, 0);
  luces::iluminar(1, 1, 1, 1, 1, 1, 1, 1);
  luces::iluminar(0, 0, 0, 0, 0, 0, 0, 0);
}

void efectos::dedo() {
  /*  5
   *  01111111
   *  10111111
   *  11011111
   *  11101111
   *  11110111
   *  11111011
   *  11111110
   */
  luces::iluminarSinRet(0, 1, 1, 1, 1, 1, 1, 1);
  for(int i=0;i<8;i++) {
    luces::iluminarSolo(i, LOW);
    luces::retardo();
    luces::iluminarSolo(i, HIGH);
  }
}

void efectos::dedoR() {
  /*  6
   *  11111110
   *  11111101
   *  11111011
   *  11110111
   *  11101111
   *  11011111
   *  10111111
   *  01111111
   */
  luces::iluminarSinRet(1, 1, 1, 1, 1, 1, 1, 0);
  for(int i=7;i>=0;i--) {
    luces::iluminarSolo(i, LOW);
    luces::retardo();
    luces::iluminarSolo(i, HIGH);
  }
}

void efectos::barra() {

  /*  7
   *  10000000
   *  11000000
   *  11100000
   *  11110000
   *  11111000
   *  11111100
   *  11111110
   *  11111111
   *  11111110
   *  11111100
   *  11111000
   *  11110000
   *  11100000
   *  11000000
   *  10000000
   *  00000000
   *  00000001
   *  00000011
   *  00000111
   *  00001111
   *  00011111
   *  00111111
   *  01111111
   *  11111111
   *  01111111
   *  00111111
   *  00011111
   *  00001111
   *  00000111
   *  00000011
   *  00000001
   *  00000000
   */

  luces::iluminarSinRet(1, 0, 0, 0, 0, 0, 0, 0);
  for(int i=0;i<8;i++) {
    luces::iluminarSolo(i, HIGH);
    luces::retardo();
  }
  for(int i=7;i>=0;i--) {
    luces::iluminarSolo(i, LOW);
    luces::retardo();
  }
  for(int i=7;i>=0;i--) {
    luces::iluminarSolo(i, HIGH);
    luces::retardo();
  }
  for(int i=0;i<8;i++) {
    luces::iluminarSolo(i, LOW);
    luces::retardo();
  }
}

void efectos::navidad() {
  /*  8
   *  01010101
   *  10101010
   */
  luces::iluminar(0, 1, 0, 1, 0, 1, 0, 1);
  luces::iluminar(1, 0, 1, 0, 1, 0, 1, 0);
}

void efectos::circo() {
  /*  9
   *  10000000
   *  01000000
   *  00100000
   *  00010000
   *  00001000
   *  00000100
   *  00000010  
   *  00000001  
   */

  luces::iluminarSinRet(1, 0, 0, 0, 0, 0, 0, 0);
  for(int i=0;i<8;i++) {
    luces::iluminarSolo(i, HIGH);
    luces::retardo();
    luces::iluminarSolo(i, LOW);
  }
}

void efectos::circoR() {
  /*  10
   *  00000001
   *  00000010
   *  00000100
   *  00001000
   *  00010000
   *  00100000
   *  01000000
   *  10000000
   */
  
  luces::iluminarSinRet(0, 0, 0, 0, 0, 0, 0, 1);
  for(int i=7;i>=0;i--) {
    luces::iluminarSolo(i, HIGH);
    luces::retardo();
    luces::iluminarSolo(i, LOW);
  }
}

void efectos::basico() {
  /*  11
   *  11111111
   *  00000000
   */
  luces::iluminar(1, 1, 1, 1, 1, 1, 1, 1);
  luces::iluminar(0, 0, 0, 0, 0, 0, 0, 0);
}
