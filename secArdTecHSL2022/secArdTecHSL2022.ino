/**
 * Este codigo funciona en un Arduino Nano.
 * Los pines en esta version son suficientes para
 * que este funcione.
 */
 
static const int pinOuts[]={4,5,6,7,8,9,10,11}; //canales de salida
static const int pinIn=2;                       //pulsador cambia efectos
const int pinStandBy=3;                  //pin pausa
const int totalEffects = 2;             //Efectos totales
int effectSelec=0;                        //numero que define el efecto a usar
int newEffect=0;                          //numero del nuevo efecto a usar
int tiempo;                               //almacena el valor en mSeg de retraso en las transiciones
bool isPaused = false;                 //la secuencia esta en pausa?

namespace efectos {
  void barrido();
  void barridoR();
}

namespace luces {
  void iluminar(bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7);
  void retardo();
}

void setup() {
  for(byte i=0; i<8; i++) {
    pinMode(pinOuts[i],OUTPUT);
    digitalWrite(pinOuts[i],LOW);
  }
  //pinMode(pinIn,INPUT);
  attachInterrupt(digitalPinToInterrupt(pinStandBy), togglePausa, RISING);
  attachInterrupt(digitalPinToInterrupt(pinIn), cambioEfecto, RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (newEffect) {
    case 0:
      effectSelec=0;
      efectos::barrido();
      break;
    case 1:
      effectSelec=1;
      efectos::barridoR();
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
