//Declaración de variables para el sensor HC-SR04
const int Trigger = 3;   //Pin digital 2 para el Trigger del sensor
const int Echo = 2;   //Pin digital 3 para el Echo del sensor

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

//Declaración de variables para el uso del Driver Motor  L298N,


int EnableM1 = 6;
int Dir1M1    = 7;
int Dir2M1    = 8;

int EnableM2 =11;
int Dir1M2    =10;
int Dir2M2    =9;

int contador = 0;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación

  // Pines para el Modulo Sensor HC-SR04
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  // Pines para el driver Motor L298N
  pinMode(EnableM1,OUTPUT);
  pinMode(Dir1M1,OUTPUT);
  pinMode(Dir2M1,OUTPUT);
  pinMode(EnableM2,OUTPUT);
  pinMode(Dir1M2,OUTPUT);
  pinMode(Dir2M2,OUTPUT);
  
}

void loop()
{

 control();
 
 contador=contador+1; //Establecer un contador

   if (contador = 100){//Intervalo de tiempo para el envío de la distancia, 
                        // si la App se bloquea, elimine o aumente este tiempo.
  
    distancia();
   }
 
 }

void M1back(){ // Motor Izquierdo atras

  digitalWrite(EnableM1,HIGH);
  digitalWrite(Dir1M1,HIGH);
  digitalWrite(Dir2M1,LOW);}

void M1forward(){ // Motor Izquierdo adelante

  digitalWrite(EnableM1,HIGH);
  digitalWrite(Dir1M1,LOW);
  digitalWrite(Dir2M1,HIGH);}

void M2forward(){ // Motor Derecho adelante

  digitalWrite(EnableM2,HIGH);
  digitalWrite(Dir1M2,LOW);
  digitalWrite(Dir2M2,HIGH);}

void M2back(){ // Motor Derecho atras

  digitalWrite(EnableM2,HIGH);
  digitalWrite(Dir1M2,HIGH);
  digitalWrite(Dir2M2,LOW);}

void Freno(){ // Freno de los motores

  digitalWrite(EnableM2,LOW);
  digitalWrite(Dir1M2,LOW);
  digitalWrite(Dir2M2,LOW);
  digitalWrite(EnableM1,LOW);
  digitalWrite(Dir1M1,LOW);
  digitalWrite(Dir2M1,LOW);
  }
void control(){

 if (Serial.available() > 0) {
    int App = Serial.read();  // declaramos el dato que recibimos de la APP o del Puerto Serial

    switch (App) {
      case 's':
        M1forward(); // SOLO UN MOTOR ADELANTE
        break;
      case 'w':
        M1back();  // SOLO UN MOTOR ATRAS
        break;
      case 'd':
        M2forward(); // SOLO UN MOTOR ADELANTE
        break;
      case 'a':
        M2back(); // SOLO UN MOTOR ATRAS
        break;
      case 'f':
        Freno();
        break;
      case 'q': // ADELANTE COMBINANDO MORORES
        M1forward();
        M2forward();
        break;  
      case 'b': // ATRAS COMBINANDO MOTORES
        M1back();
        M2back();
        break; 
      case 't': // GIRO COMPLETO DERECHO
        M1forward();
        M2back();
        break;
      case 'y': // GIRO COMPLETO DERECHO
        M1back();
        M2forward();
        break;           
      
    }
  }
}

void distancia(){

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;                //escalamos el tiempo a una distancia en cm

  Serial.println(d);      //Enviamos serialmente el valor de la distancia
  //delay(100);             //Hacemos una pausa de 100ms
    
}