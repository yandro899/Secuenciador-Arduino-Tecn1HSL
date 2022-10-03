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
const int totalEffects = 4;                     //Efectos totales
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
}

namespace luces {
  /*
   * Funciones que se encargan de encender los leds y apagarlos,
   * ademas de controlar el tiempo de encendido. Son solo declaraciones.
   * Se recomienda no tocar
   */
  void iluminar(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7);
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

  // Retardo del efecto
  retardo();
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

  // Lectura del potenciometro
  if (analogRead(A0)!=tiempo) {
    // Valor obtenido [0 ; 1023]
    if (analogRead(A0) < 50)
      // Si el tiempo obtenido es menor a 50, el tiempo es de 50ms
      tiempo = 50;
    else
      tiempo = analogRead(A0);    
  }
  // Retardo
  delay(tiempo);

  // El efecto esta en pausa si se pulso el boton de pausa
  while (isPaused) {
    Serial.print("pausa");
  }
}

/* EFECTOS */
void efectos::barrido() {
  /*
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
  /*
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
  /*
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
  /*
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
