/*
 * Aguilar Licona Marco Antonio
 * 02/05/18
 * Robots Móviles y agentes inteligentes
 * FI UNAM
*/

#define sensorIzquierdoCentral   A3
#define sensorIzquierdoCercano     A4
#define sensorIzquierdoLejano      A5
#define sensorDerechoCentral  A2
#define sensorDerechoCercano    A1
#define sensorDerechoLejano     A0

int lecturaIzquierdoCentral;
int lecturaIzquierdoCercano;
int lecturaIzquierdoLejano;
int lecturaDerechoCentral;
int lecturaDerechoCercano;
int lecturaDerechoLejano;

int etapaRepeticion;

#define tiempoEspera 600

#define motorIzquierdo1  6
#define motorIzquierdo2  7

#define motorDerecho1 4
#define motorDerecho2 5

#define motorDerechoPWM 9
#define motorIzquierdoPWM 10

#define led 13

#define colorNegro 600

char ruta[30] = {};
int tamanioRuta;
int tamanioLectura;

void setup(){  
  pinMode(sensorIzquierdoCentral, INPUT);
  pinMode(sensorIzquierdoCercano, INPUT);
  pinMode(sensorIzquierdoLejano, INPUT);
  pinMode(sensorDerechoCentral, INPUT);
  pinMode(sensorDerechoCercano, INPUT);
  pinMode(sensorDerechoLejano, INPUT);
    
  pinMode(motorIzquierdo1, OUTPUT);
  pinMode(motorIzquierdo2, OUTPUT);
  pinMode(motorDerecho1, OUTPUT);
  pinMode(motorDerecho2, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  Serial.begin(9600);
}


void loop(){
 leerSensores();                                                                                     
 /*Serial.print("lecturaIzquierdoCentral: ");
 Serial.println(lecturaIzquierdoCentral);
 Serial.print("lecturaDerechoCentral: ");
 Serial.println(lecturaDerechoCentral);*/
 if(lecturaIzquierdoLejano<colorNegro && lecturaDerechoLejano<colorNegro && (lecturaIzquierdoCentral>colorNegro || lecturaDerechoCentral>colorNegro) ){ 
    recto();                                                                                      
  }
  
  else{                                                                                              
    paredIzquierda();                                                                                   
  }
}

void leerSensores(){  
  lecturaIzquierdoCentral  = analogRead(sensorIzquierdoCentral);
  lecturaIzquierdoCercano    = analogRead(sensorIzquierdoCercano);
  lecturaIzquierdoLejano     = analogRead(sensorIzquierdoLejano);
  lecturaDerechoCentral = analogRead(sensorDerechoCentral);
  lecturaDerechoCercano   = analogRead(sensorDerechoCercano);
  lecturaDerechoLejano    = analogRead(sensorDerechoLejano);  

 //Serial.print("lecturaIzquierdoCentral: ");
 //Serial.println(lecturaIzquierdoCentral);
 /*Serial.print("lecturaIzquierdoCercano: ");
 Serial.println(lecturaIzquierdoCercano);
 Serial.print("lecturaIzquierdoLejano: ");
 Serial.println(lecturaIzquierdoLejano);*/
 
 //Serial.print("lecturaDerechoCentral: ");
 //Serial.println(lecturaDerechoCentral);
 /*Serial.print("lecturaDerechoCercano: ");
 Serial.println(lecturaDerechoCercano);
 Serial.print("lecturaDerechoLejano: ");
 Serial.println(lecturaDerechoLejano);*/
}

void recto(){
  if(analogRead(sensorIzquierdoCentral)<colorNegro){
    //Serial.println("SI en blanco");
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
    return;
  }
  if(analogRead(sensorDerechoCentral)<colorNegro){
    //Serial.println("SD en blanco");
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
    return;
  }  
    //Serial.println("SI y SD en color negro");
    Serial.println("Recto...");
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
    return;
}

void paredIzquierda(){
  //Se llego a meta o a un cruce
  if(lecturaIzquierdoLejano>colorNegro && lecturaDerechoLejano>colorNegro){
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(tiempoEspera);
    
    leerSensores();
    
    if(lecturaIzquierdoLejano>colorNegro || lecturaDerechoLejano>colorNegro){
      Serial.println("Se detectó meta");
      terminado();
    }
    if(lecturaIzquierdoLejano<colorNegro && lecturaDerechoLejano<colorNegro){
      Serial.println("Se detectó cruce y se comenzará vuelta a la izquierda");
      vueltaIzquierda();
    }    
  }  
  if(lecturaIzquierdoLejano>colorNegro){
   Serial.println("Se detecto eje izquierdo");
   digitalWrite(motorIzquierdo1, HIGH);
   digitalWrite(motorIzquierdo2, LOW);
   digitalWrite(motorDerecho1, HIGH);
   digitalWrite(motorDerecho2, LOW);
   moverMotor();   

   delay(tiempoEspera);
   leerSensores();
      
    if(lecturaIzquierdoLejano<colorNegro && lecturaDerechoLejano<colorNegro){
        Serial.println("Dando vuelta a la izquierda...");
        vueltaIzquierda();
    }
    else{
        Serial.println("Se detectó meta");
        terminado();
    }
  }
  
  if(lecturaDerechoLejano>colorNegro){
    Serial.println("Se detecto eje derecho");
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(tiempoEspera);
    leerSensores();
    
    if(lecturaIzquierdoLejano>colorNegro){
      Serial.println("Se detecto eje izquierdo");
      delay(tiempoEspera-30);
      leerSensores();
      
      if(lecturaDerechoLejano>colorNegro && lecturaIzquierdoLejano>colorNegro){
        Serial.println("Se detectó meta");
        terminado();
      }
      else{
        Serial.println("Dando vuelta a la izquierda...");
        vueltaIzquierda();
        return;
      }
    }
    delay(tiempoEspera-30);
    leerSensores();
    if(lecturaIzquierdoLejano<colorNegro && lecturaIzquierdoCentral<colorNegro && lecturaDerechoCentral<colorNegro && lecturaDerechoLejano<colorNegro){
      Serial.println("Dando vuelta a la derecha...");
      vueltaDerecha();
      return;
    }
    ruta[tamanioRuta]='R';
    tamanioRuta++;
    if(ruta[tamanioRuta-2]=='V'){
      acortarRuta();
    }
    recto();
  }
  leerSensores();
  if(lecturaIzquierdoLejano<colorNegro && lecturaIzquierdoCentral<colorNegro && lecturaDerechoCentral<colorNegro && lecturaDerechoLejano<colorNegro && lecturaIzquierdoCercano<colorNegro && lecturaDerechoCercano<colorNegro){
    Serial.println("No se detectaron ejes, dando vuelta de regreso...");
    vuelta();
  }
}

void terminado(){
  digitalWrite(motorIzquierdo1, LOW);
  digitalWrite(motorIzquierdo2, LOW);
  digitalWrite(motorDerecho1, LOW);
  digitalWrite(motorDerecho2, LOW);
  moverMotor();
  delay(5);
  etapaRepeticion=1;
  ruta[tamanioRuta]='M';
  tamanioRuta++;
  imprimirRuta();
 while(analogRead(sensorIzquierdoLejano)>colorNegro){
   digitalWrite(led, LOW);
   delay(150);
   digitalWrite(led, HIGH);
   delay(150);
 }
 delay(1000);
 repetir();
}

void vueltaIzquierda(){
    /*digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();  
    delay(1200);*/

   
  while(analogRead(sensorDerechoCentral)>colorNegro||analogRead(sensorIzquierdoCentral)>colorNegro){
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, HIGH);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotorVueltas();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
    
  while(analogRead(sensorDerechoCentral)<colorNegro){
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, HIGH);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotorVueltas();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
 
  if(etapaRepeticion==0){
    ruta[tamanioRuta]='I';
    //Serial.println("l");
    tamanioRuta++;
    //Serial.print("ruta length: ");
    //Serial.println(tamanioRuta);
    if(ruta[tamanioRuta-2]=='V'){
      //Serial.println("shortening ruta");
      acortarRuta();
    }
  }
}

void vueltaDerecha(){   
  /*digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();  
    delay(1200);*/
  while(analogRead(sensorDerechoCentral)>colorNegro){
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, HIGH);
    moverMotorVueltasD();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
   while(analogRead(sensorDerechoCentral)<colorNegro){
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, HIGH);
    moverMotorVueltasD();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
   while(analogRead(sensorIzquierdoCentral)<colorNegro){
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, HIGH);
    moverMotorVueltasD();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
  
  if(etapaRepeticion==0){
    ruta[tamanioRuta]='D';
    Serial.println("r");
    tamanioRuta++;
    Serial.print("Taman ruta: ");
    Serial.println(tamanioRuta);
    if(ruta[tamanioRuta-2]=='V'){
      Serial.println("acortando ruta...");
      acortarRuta();
    }
  }
}

void vuelta(){
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
   while(analogRead(sensorIzquierdoCentral)<colorNegro){
    /*digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, HIGH);
    digitalWrite(motorDerecho1, HIGH);
    digitalWrite(motorDerecho2, LOW);
    moverMotorVueltas();*/
    digitalWrite(motorIzquierdo1, HIGH);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, HIGH);
    moverMotorVueltasD();
    delay(5);
    digitalWrite(motorIzquierdo1, LOW);
    digitalWrite(motorIzquierdo2, LOW);
    digitalWrite(motorDerecho1, LOW);
    digitalWrite(motorDerecho2, LOW);
    moverMotor();
    delay(5);
  }
  ruta[tamanioRuta]='V';
  tamanioRuta++;
  recto();
}

void acortarRuta(){
  /*Sintaxis ruta
   * Derecha -> D
   * Izquierda -> I
   * Recto -> R
   * Volver -> V
   * Meta -> M  
  */
 int corteTerminado=0;
  if(ruta[tamanioRuta-3]=='I' && ruta[tamanioRuta-1]=='D'){
    tamanioRuta-=3;
    ruta[tamanioRuta]='V';
    corteTerminado=1;
  }
   
  if(ruta[tamanioRuta-3]=='I' && ruta[tamanioRuta-1]=='R' && corteTerminado==0){
    tamanioRuta-=3;
    ruta[tamanioRuta]='D';
    corteTerminado=1;
  }
   
  if(ruta[tamanioRuta-3]=='D' && ruta[tamanioRuta-1]=='I' && corteTerminado==0){
    tamanioRuta-=3;
    ruta[tamanioRuta]='V';
    corteTerminado=1;
  }
  
   
  if(ruta[tamanioRuta-3]=='R' && ruta[tamanioRuta-1]=='I' && corteTerminado==0){
    tamanioRuta-=3;
    ruta[tamanioRuta]='D';
    corteTerminado=1;
  }
     
  if(ruta[tamanioRuta-3]=='R' && ruta[tamanioRuta-1]=='R' && corteTerminado==0){
    tamanioRuta-=3;
    ruta[tamanioRuta]='V';
    corteTerminado=1;
  }
    if(ruta[tamanioRuta-3]=='I' && ruta[tamanioRuta-1]=='I' && corteTerminado==0){
    tamanioRuta-=3;
    ruta[tamanioRuta]='R';
    corteTerminado=1;
  }
  
  ruta[tamanioRuta+1]='M';
  ruta[tamanioRuta+2]='M';
  tamanioRuta++;
}


void imprimirRuta(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=tamanioRuta){
    Serial.println(ruta[x]);
    x++;
  }
  Serial.println("+++++++++++++++++");
}


void repetir(){
  leerSensores();
  if(lecturaIzquierdoLejano<colorNegro && lecturaDerechoLejano<colorNegro){
    recto();
  }
  else{
    if(ruta[tamanioLectura]=='M'){
      digitalWrite(motorIzquierdo1, HIGH);
      digitalWrite(motorIzquierdo2, LOW);
      digitalWrite(motorDerecho1, HIGH);
      digitalWrite(motorDerecho2, LOW);
      moverMotor();
      delay(100);
      digitalWrite(motorIzquierdo1, LOW);
      digitalWrite(motorIzquierdo2, LOW);
      digitalWrite(motorDerecho1, LOW);
      digitalWrite(motorDerecho2, LOW);
      moverMotor();
      movimientoFinal();
    }
    if(ruta[tamanioLectura]=='I'){
      digitalWrite(motorIzquierdo1, HIGH);
      digitalWrite(motorIzquierdo2, LOW);
      digitalWrite(motorDerecho1, HIGH);
      digitalWrite(motorDerecho2, LOW);
      moverMotor();
      delay(tiempoEspera);
      vueltaIzquierda();
    }
    if(ruta[tamanioLectura]=='D'){
      digitalWrite(motorIzquierdo1, HIGH);
      digitalWrite(motorIzquierdo2, LOW);
      digitalWrite(motorDerecho1, HIGH);
      digitalWrite(motorDerecho2, LOW);
      moverMotor();
      delay(tiempoEspera);
      vueltaDerecha();
    }
    if(ruta[tamanioLectura]=='R'){
      digitalWrite(motorIzquierdo1, HIGH);
      digitalWrite(motorIzquierdo2, LOW);
      digitalWrite(motorDerecho1, HIGH);
      digitalWrite(motorDerecho2, LOW);
      moverMotor();
      delay(tiempoEspera);
      recto();
    }    
    tamanioLectura++;
  }    
  repetir();
}

void movimientoFinal(){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(500);
    movimientoFinal();
}

void moverMotor(){
  int velocidad_derecha = 90;
  int velocidad_izquierda = velocidad_derecha + 5;
  analogWrite(motorIzquierdoPWM, velocidad_izquierda);
  analogWrite(motorDerechoPWM, velocidad_derecha);
}

void moverMotorVueltas(){
  int velocidad_derecha = 150;
  int velocidad_izquierda = 0;
  analogWrite(motorIzquierdoPWM, velocidad_izquierda);
  analogWrite(motorDerechoPWM, velocidad_derecha);
}

void moverMotorVueltasD(){
  int velocidad_derecha = 0;
  int velocidad_izquierda = 190;
  analogWrite(motorIzquierdoPWM, velocidad_izquierda);
  analogWrite(motorDerechoPWM, velocidad_derecha);
}
