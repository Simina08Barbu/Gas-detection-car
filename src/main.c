#define IN1 7 //setare implicită a pinilor pentru directia motoarelor
#define IN2 6
#define IN3 5
#define IN4 4
#define LED 9 

//initializare variabile pe pini programabili
int BUZZER = 8;
int MQ6=A4;//senzor gaz
int dataSensor;//date primite de la senzor gaz
char state;//date venite de la bluetooth
//control turație motoare
int ENB=A1;
int ENA=A0;

void setup() {
  Serial.begin(9600);//baudrate

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(BUZZER,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(MQ6,INPUT);//trimite datele citite

  digitalWrite(IN1,LOW);//initializare motoare-oprite
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  tone(BUZZER, 2000, 500);
    

}

void loop() {
  
  digitalWrite(ENA,255);//turatie motoare
  digitalWrite(ENB,255);
  digitalWrite(LED,LOW);

  if(Serial.available()>0){//verificare daca exista date valabile de la bluetooth
      state=Serial.read();//stocare date citite intr-o variabila char pentru a
				 //oferi comenzi motoarelor
  }
        
  dataSensor=analogRead(MQ6);//citire date
  Serial.println(dataSensor);//afisare serial monitor datele citite de la MQ6

  //MOTOR CONTROL
  if(state=='F'){//forward
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }else if(state=='B'){//back
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }else if(state=='L'){//left
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }else if(state=='R'){//right
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }else if(state=='S'){//stop
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }else if (state=='V'){
    tone(BUZZER, 2000, 500);
    digitalWrite(BUZZER, HIGH);
  }

//SENZOR+BUZZER-pentru valori >=400 led-ul luminează și buzzer-ul emite semnal
		   audio
  if(dataSensor>=400){
    tone(BUZZER, 2000, 500);
    digitalWrite(BUZZER, HIGH);

    digitalWrite(LED, HIGH);
  }

}
