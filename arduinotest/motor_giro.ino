//Pines para motor de la derecha
int enB = 10;//Habilita entrada PWM 
int IN3 = 5;
int IN4 = 4;

//Pines para motor de la izquierda
int enA = 11;//Habilita entrada PWM
int IN1 = 3;
int IN2 = 2;

//Inicializar valores digitales de sensores
int valorInfra1= 0;
int valorInfra2=0;

//Pines para sensores Tracker son inicializadas
int infraPin1= 12;
int infraPin2=6;

int lectura=0;
/********************PROGRAM**********************/
//FALTA VER COMO AVANZAR DE NUEVO
void setup()
{
  //Definición de pines de salida y entrada
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5

  pinMode (IN1, OUTPUT);    // Input4 conectada al pin 4
  pinMode (IN2, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(infraPin1,INPUT);
  pinMode(infraPin2,INPUT);

  Serial.begin(9600);
}

void loop()
{
AVANZAR: 
  //Lectura de sensores infrarrojos
  valorInfra1=digitalRead(infraPin1);
  valorInfra2=digitalRead(infraPin2);
  
  //ValorInfra1-->sensor derecha
  //ValorInfra2-->sensor izquierda
  
  //Sensores "leen" negro 
  if (valorInfra2 == LOW && valorInfra1==LOW)
  { //Avanza directo 
    // Motor de la derecha(D)
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    analogWrite(enA, 110);//110

   //Motor de la izquierda
    digitalWrite (IN1, LOW);//
    digitalWrite (IN2, HIGH);
    analogWrite(enB, 145);//200
    delay(200);
  }
  else
  if (valorInfra2==LOW && valorInfra1==HIGH)
  {/*Se MUEVE  motor de la izquierda y sigue girando el motor
    de la derecha*/
    digitalWrite(IN2,LOW);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
    analogWrite(enA, 110);
    delay(200);
  }
  else
  if(valorInfra2==HIGH && valorInfra1==LOW) //AVANZA MOTOR DERECHA
  {
    digitalWrite(IN3,LOW);
    digitalWrite (IN1, LOW);//ahora derecha
    digitalWrite (IN2, HIGH);
    analogWrite(enB, 145);
  }
  else
  if(valorInfra2==HIGH && valorInfra1==HIGH)  //LEE BLANCO ,AMBOS SENSORES
  {
    digitalWrite (IN4, LOW);
    digitalWrite (IN2, LOW);
    digitalWrite (IN3, LOW);
    digitalWrite (IN1, LOW);
   int lectura;
    while(true)
    {
    if(Serial.available()>0)
    {
      lectura=Serial.read();
      if (lectura=='a')//RETROCEDE
      {/*retrocede por un momento sin sensar para "entrar" en 
        la línea negra.*/
        digitalWrite(IN4,HIGH);
        digitalWrite(IN3,LOW);
        analogWrite(enA,130);

        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        analogWrite(enB,175);
        delay(1000);
       //EMPIENZA A SENSAR
        while(true)
        {
          valorInfra1=digitalRead(infraPin1);
          valorInfra2=digitalRead(infraPin2);

          if(valorInfra2==LOW && valorInfra1==LOW)
          {
            //ahora motor izquierda
            digitalWrite(IN4,HIGH);
            digitalWrite(IN3,LOW);
            analogWrite(enA,160);//

            //ahora motor derecha
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
            analogWrite(enB,175);
          }
          else
          if(valorInfra2==LOW && valorInfra1==HIGH)
          {
            digitalWrite(IN4,LOW); 
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
            analogWrite(enB,175);
          }
          else
          if(valorInfra2==HIGH && valorInfra1==LOW)
          {
            digitalWrite(IN1,LOW);
            digitalWrite(IN4,HIGH);
            digitalWrite(IN3,LOW);
            analogWrite(enA,160);

          }
          else
          if(valorInfra2==HIGH && valorInfra1==HIGH)
          {
            digitalWrite(IN1,LOW);
            digitalWrite(IN4,LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN1, LOW);
            goto hola;
          }          
        }        
      }
      else 
      hola:
      if(lectura=='b')//SIGUE AVANZANDO
      {/*avanza por un momento sin sensar,luego debe llegar a
       línea negra.idiota.*/
        //Motor de la derecha
        digitalWrite (IN4, LOW);
        digitalWrite (IN3, HIGH);
        analogWrite(enA, 130);

        //Motor de la izquierda
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, HIGH);
        analogWrite(enB, 175);
        delay(1000);
        goto AVANZAR;
       }  
    }
   }//llave primer while
  }
 
}
