/**
 * Este codigo es la version hecha en 2017 y con pequeñas correcciones
 * de bugs en el 2018. Como en ese tiempo lo que aprendi de C++
 * era muy basico y no programaba correctamente, el codigo es dificil
 * de entender, mantener y ocupa un hardware muy potente para lo que
 * realmente necesita.
 * 
 * Subo esta version para que quede guardada y vean como funcionaba.
 */

bool high=0;
bool low=1;
const byte led[]={14,15,16,17,18,19,20,21};
const byte sal[]={2,3,4,5,6,7,8,9};   //canales de salida
const byte ent=10;                    //pulsador cambia efectos
bool num[5];                          //valores utiles para seleccionar efecto
int efecto=0;                         //numero que define el efecto a usar
int tiempo;                           //almacena el valor en mSeg de retraso en las transiciones
const byte pinMan=11;                 //define el pin donde se recibe el dato si sera automatico o manual
const byte standBy=12;                //pin pausa

void setup() {
  for(byte i=0;i<8;i++) {
    pinMode(sal[i],OUTPUT);
    pinMode(led[i],OUTPUT);
    digitalWrite(sal[i],low);
  } //fin para
  pinMode(pinMan,INPUT);
  pinMode(ent,INPUT);
  Serial.begin(9600);
} //fin setup()

void loop() {
  tiempo=retardo();
  //condicional que define automatizacion
  if(digitalRead(pinMan)==HIGH) {
    randomSeed(millis());
    efecto=random(17);
  }
  else{
    numero();
  }
  
  Serial.println(efecto);
  for(byte i=0;i<8;i++) {
    digitalWrite(sal[i],low);
  } //fin para
  
  switch (efecto) {
    case 0:
      barrido();
      break;
    case 1:
      barridoR();
      break;
    case 2:
      llenado();
      break;
    case 3:
      dedo();
      break;
    case 4:
      dedoR();
      break;
    case 5:
      puntos();
      break;
    case 6:
      barra();
      break;
    case 7:
      navidad();
      break;
    case 8:
      circo();
      break;
    case 9:
      circoR();
      break;
    case 10:
      basico();
      break;
    case 11:
      policia();
      break;
    case 12:
      punto2();
      break;
    case 13:
      punto2R();
      break;
    case 14:
      dedo2();
      break;
    case 15:
      dedo2R();
      break;
    case 16:
      puntoM();
      break;
    case 17:
      dosPuntos();
      break;
  }
}

void numero() {
  if(digitalRead(ent)==HIGH) {
    while(digitalRead(ent)==HIGH) { }
    efecto++;
    if(efecto>17) {
      efecto=0;;
    }
  }

  /*
   * La variable efecto definirá que efecto
   * hacer.
   */

}

void retraso(byte effect) {
  int y;
  bool cont=0;
  numero();
  byte n_effect=efecto;
  for(int d=0;d<8;d++) {
    if(digitalRead(sal[d])==HIGH) {
      digitalWrite(led[d],HIGH);
    }
    else{
    digitalWrite(led[d],LOW);
    }
  }
  if(n_effect==effect) {
    tiempo=retardo();
    for(int c=0;c<=(tiempo/20);c++) {
      tiempo=retardo();
      numero();
      n_effect=efecto;
      if(n_effect!=effect) {
        c=(tiempo/20);
      }
      delay(10);
    }
  }
  if(digitalRead(standBy)==HIGH) {
    while(digitalRead(standBy)==HIGH) {}
    while(cont==0) {
      if(digitalRead(standBy)==HIGH) {
        cont=1;
        while(digitalRead(standBy)==HIGH) {} 
      }
    }
  }
}

int retardo() {
  int t=analogRead(A0);
  if(t<40) {
    t=40;
  }
  //Serial.println(t);
  return t;
}

void barrido() {
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
  digitalWrite(sal[0],high);
  digitalWrite(sal[1],high);
  digitalWrite(sal[6],high);
  digitalWrite(sal[7],high);
  digitalWrite(sal[5],low);
  retraso(0);
  digitalWrite(sal[2],high);
  digitalWrite(sal[6],low);
  retraso(0);
  digitalWrite(sal[3],high);
  digitalWrite(sal[7],low);
  retraso(0);
  for(int i=4;i<8;i++) {
    digitalWrite(sal[i],high);
    digitalWrite(sal[i-4],low);
    retraso(0);
  }
  digitalWrite(sal[0],high);
  digitalWrite(sal[4],low);
  retraso(0);
}

void barridoR() {
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
  digitalWrite(sal[0],high);
  digitalWrite(sal[1],high);
  digitalWrite(sal[6],high);
  digitalWrite(sal[7],high);
  digitalWrite(sal[2],low);
  retraso(1);
  digitalWrite(sal[5],high);
  digitalWrite(sal[1],low);
  retraso(1);
  digitalWrite(sal[4],high);
  digitalWrite(sal[0],low);
  retraso(1);
  for(int i=3;i>=0;i--) {
    digitalWrite(sal[i],high);
    digitalWrite(sal[i+4],low);
    retraso(1);
  }
  digitalWrite(sal[7],high);
  digitalWrite(sal[3],low);
  retraso(1);
}

void puntos() {
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
    digitalWrite(sal[i],high);
    digitalWrite(sal[7-i],high);
    retraso(5);
    digitalWrite(sal[i],low);
    digitalWrite(sal[7-i],low);
    retraso(5);
  }
  /*for(int i=7;i>=0;i--) {
    if(i>3) {
      digitalWrite(sal[i+4],low);
      digitalWrite(sal[3-i],low);
    }
    else {
      digitalWrite(sal[i],high);
      digitalWrite(sal[7-i],high);
    }
    retraso(5);
    */
  for(int i=0;i<4;i++){
    digitalWrite(sal[i],high);
    digitalWrite(sal[7-i],high);
    retraso(5);
  }
  for(int i=0;i<4;i++){
    digitalWrite(sal[i],low);
    digitalWrite(sal[7-i],low);
    retraso(5);
  }
  
}

void llenado() {
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
  digitalWrite(sal[0],high);
  retraso(2);
  for(int i=1;i<7;i++) {
    digitalWrite(sal[i],high);
    retraso(2);
    digitalWrite(sal[i],low);
  }
  digitalWrite(sal[7],high);
  retraso(2);
  for(int i=6;i>1;i--) {
    digitalWrite(sal[i],high);
    retraso(2);
    digitalWrite(sal[i],low);
  }
  digitalWrite(sal[1],high);
  retraso(2);
  for(int i=2;i<6;i++) {
    digitalWrite(sal[i],high);
    retraso(2);
    digitalWrite(sal[i],low);
  }
  digitalWrite(sal[6],high);
  retraso(2);
  for(int i=5;i>2;i--) {
    digitalWrite(sal[i],high);
    retraso(2);
    digitalWrite(sal[i],low);
  }
  digitalWrite(sal[2],high);
  retraso(2);
  for(int i=3;i<5;i++) {
    digitalWrite(sal[i],high);
    retraso(2);
    digitalWrite(sal[i],low);
  }
  digitalWrite(sal[5],high);
  retraso(2);
  digitalWrite(sal[4],high);
  retraso(2);
  digitalWrite(sal[4],low);
  digitalWrite(sal[3],high);
  retraso(2);
  digitalWrite(sal[4],high);
  retraso(2);
  for(int i=0;i<7;i++) {
    digitalWrite(sal[i],low);
  }
  retraso(2);
  for(int i=0;i<7;i++) {
    digitalWrite(sal[i],high);
  }
  retraso(2);
  for(int i=0;i<7;i++) {
    digitalWrite(sal[i],low);
  }
}

void dedo() {
  /*
   *  01111111
   *  10111111
   *  11011111
   *  11101111
   *  11110111
   *  11111011
   *  11111110
   */
  for(int i=0;i<8;i++) {
    //nos aseguramos que todos los ledes esten en HIGH
    digitalWrite(sal[i],high);
  }
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
    retraso(3);
    digitalWrite(sal[i],high);
  }
}

void dedoR() {
  /*
   *  11111110
   *  11111101
   *  11111011
   *  11110111
   *  11101111
   *  11011111
   *  10111111
   *  01111111
   */
  for(int i=0;i<8;i++) {
    //nos aseguramos que todos los ledes esten en HIGH
    digitalWrite(sal[i],high);
  }
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],low);
    retraso(4);
    digitalWrite(sal[i],high);
  }
}

void barra() {

  /*
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
  
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
    retraso(6);
  }
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],low);
    retraso(6);
  }
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],high);
    retraso(6);
  }
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
    retraso(6);
  }
}

void navidad() {
  /*
   *  01010101
   *  10101010
   */
  for(int i=0;i<8;i++) {
    if((i%2)==0) {
      digitalWrite(sal[i],low);
    }
    else{
      digitalWrite(sal[i],high);
    }
    retraso(7);
    if((i%2)==0) {
      digitalWrite(sal[i],high);
    }
    else{
      digitalWrite(sal[i],low);
    }
    retraso(7);
  }
}

void circo() {
  /*
   *  10000000
   *  01000000
   *  00100000
   *  00010000
   *  00001000
   *  00000100
   *  00000010  
   *  00000001  
   */
   
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
    retraso(8);
    digitalWrite(sal[i],low);
  }
}

void circoR() {
  /*
   *  00000001
   *  00000010
   *  00000100
   *  00001000
   *  00010000
   *  00100000
   *  01000000
   *  10000000
   */
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],high);
    retraso(9);
    digitalWrite(sal[i],low);
  }
}

void basico() {
  /*
   *  11111111
   *  00000000
   */
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
  }
  retraso(10);
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
  }
  retraso(10);
}

void policia() {
  /*
   *  11110000
   *  11110000
   *  00001111
   *  00001111
   *  11110000
   *  00001111
   *  11110000
   *  00001111
   *  11110000 (6 veces en
   *  00001111  tiempo x 3)
   *  11111111
   *  00000000
   *  11111111
   *  00000000
   */
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],high);
    }
    else {
      digitalWrite(sal[i],low);
    }
  }
  retraso(11);
  retraso(11);
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],low);
    }
    else {
      digitalWrite(sal[i],high);
    }
  }
  retraso(11);
  retraso(11);
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],high);
    }
    else {
      digitalWrite(sal[i],low);
    }
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],low);
    }
    else {
      digitalWrite(sal[i],high);
    }
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],high);
    }
    else {
      digitalWrite(sal[i],low);
    }
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    if(i<4) {
      digitalWrite(sal[i],low);
    }
    else {
      digitalWrite(sal[i],high);
    }
  }
  retraso(11);
  for(int j=0;j<3;j++) {
    for(int i=0;i<8;i++) {
      if(i<4) {
        digitalWrite(sal[i],high);
      }
      else {
        digitalWrite(sal[i],low);
      }
    }
    retraso(11);
    for(int i=0;i<8;i++) {
      if(i<4) {
        digitalWrite(sal[i],low);
      }
      else {
        digitalWrite(sal[i],high);
      }
    }
    retraso(11);
  }
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
  }
  retraso(11);
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
  }
  retraso(11);
}

void punto2() {
  /*
   *  10001000
   *  01000100
   *  00100010
   *  00010001
   *  10001000
   *  01000100
   *  00100010
   *  00010001
   */
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
    if(i>=4) {
      digitalWrite(sal[i-4],high);
    }
    else {
      digitalWrite(sal[i+4],high);
    }
    retraso(12);
     digitalWrite(sal[i],low);
    if(i>=4) {
      digitalWrite(sal[i-4],low);
    }
    else {
      digitalWrite(sal[i+4],low);
    }
  }
}

void punto2R() {
  /*
   *  00010001
   *  00100010
   *  01000100
   *  10001000
   *  00010001
   *  00100010
   *  01000100
   *  10001000
   */
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],high);
    if(i<=3) {
      digitalWrite(sal[i+4],high);
    }
    else {
      digitalWrite(sal[i-4],high);
    }
    retraso(13);
     digitalWrite(sal[i],low);
    if(i<=3) {
      digitalWrite(sal[i+4],low);
    }
    else {
      digitalWrite(sal[i-4],low);
    }
  }
}

void dedo2() {
  /*
   *  10001000
   *  01000100
   *  00100010
   *  00010001
   *  10001000
   *  01000100
   *  00100010
   *  00010001
   */
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
  }
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],low);
    if(i>=4) {
      digitalWrite(sal[i-4],low);
    }
    else {
      digitalWrite(sal[i+4],low);
    }
    retraso(14);
     digitalWrite(sal[i],high);
    if(i>=4) {
      digitalWrite(sal[i-4],high);
    }
    else {
      digitalWrite(sal[i+4],high);
    }
  }
}

void dedo2R() {
  /*
   *  00010001
   *  00100010
   *  01000100
   *  10001000
   *  00010001
   *  00100010
   *  01000100
   *  10001000
   */
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
  }
  for(int i=7;i>=0;i--) {
    digitalWrite(sal[i],low);
    if(i<=3) {
      digitalWrite(sal[i+4],low);
    }
    else {
      digitalWrite(sal[i-4],low);
    }
    retraso(15);
     digitalWrite(sal[i],high);
    if(i<=3) {
      digitalWrite(sal[i+4],high);
    }
    else {
      digitalWrite(sal[i-4],high);
    }
  }
}

void puntoM() {
  /*
   *  10000000
   *  01000000
   *  00100000
   *  00010000
   *  00001000
   *  00000100
   *  00000010
   *  00000001
   *  00000010
   *  00000100
   *  00001000
   *  00010000
   *  00100000
   *  01000000
   */
  for(int i=0;i<8;i++) {
    digitalWrite(sal[i],high);
    retraso(16);
    digitalWrite(sal[i],low);
  }
  for(int i=6;i>=1;i--) {
    digitalWrite(sal[i],high);
    retraso(16);
    digitalWrite(sal[i],low);
  }
}

void dosPuntos() {
  /*
   *  10001000
   *  01000100
   *  00100010
   *  00010001
   *  00001010
   *  00000100
   *  00001010
   *  00010001
   *  00100010
   *  01000100
   *  10001000
   *  01010000
   *  00100000
   *  01010000
   */
  for(int i=0;i<4;i++) {
    digitalWrite(sal[i],high);
    digitalWrite(sal[i+4],high);
    retraso(17);
    digitalWrite(sal[i],low);
    digitalWrite(sal[i+4],low);
  }
  digitalWrite(sal[4],high);
  digitalWrite(sal[6],high);
  retraso(17);
  digitalWrite(sal[4],low);
  digitalWrite(sal[6],low);
  digitalWrite(sal[5],high);
  retraso(17);
  digitalWrite(sal[4],high);
  digitalWrite(sal[6],high);
  digitalWrite(sal[5],low);
  retraso(17);
  digitalWrite(sal[4],low);
  digitalWrite(sal[6],low);
  for(int i=7;i>3;i--) {
    digitalWrite(sal[i],high);
    digitalWrite(sal[i-4],high);
    retraso(17);
    digitalWrite(sal[i],low);
    digitalWrite(sal[i-4],low);
  }
  digitalWrite(sal[1],high);
  digitalWrite(sal[3],high);
  retraso(17);
  digitalWrite(sal[1],low);
  digitalWrite(sal[3],low);
  digitalWrite(sal[2],high);
  retraso(17);
  digitalWrite(sal[1],high);
  digitalWrite(sal[3],high);
  digitalWrite(sal[2],low);
  retraso(17);
}
