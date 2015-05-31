#include <Servo.h>

// -- VARIABLES --
const int pwPin = 9;
long pulse, inches, cm;
Servo myservo;
Servo myservo2;
int pos;

// -- SETUP --
void setup() {

  //results send back to PC console
  Serial.begin(9600);
  myservo.attach(5);
  myservo2.attach(6);
}

// -- LOOP --
void loop() {
  distanceBehaviour();
  servoBehaviour(); 
}


void distanceBehaviour(){ //Meet de afstand via de Max Sonar
  
  pinMode(pwPin, INPUT);
  pulse = pulseIn(pwPin, HIGH);
  inches = pulse/147; //Berekening van gemeten afstand naar inches
  cm = inches * 2.54; //Berekening inches naar centimeter
  // Serial Print output
  Serial.print(cm); //Laat de afstand zien in de serial monitor
  Serial.println("cm");
  Serial.println();
  delay(50);
}


void servoBehaviour() { //Stelt de servo's in aan de hand van de afstand

  if(cm>150 && cm<999) { //Als de afstand groter is dan 150cm
      myservo.write(170); //Kijk naar voren
      myservo2.write(40);
  }
  
  if(cm>80 && cm<150) { //Als de afstand tussen de 80cm en 150cm is
    myservo.write(155); //Kijk naar beneden
    myservo2.write(150);
    slow(random(2,5), 600); // Random snelheid waarin hij stieken naar boven kijkt
    myservo.write(155); //Kijk omhoog
    myservo2.write(150);
    delay(1000);    
  }
  
  if(cm>12 && cm<80) { //Als de afstand tussen de 12cm en 80cm is
    myservo.write(170); //Kijk naar beneden
    myservo2.write(150);
  }
  
}

void slow(int speed, int pos){ //Slow functie om de servo smooth te laten bewegen ipv stotterig
  for (int i = 0; i < pos; i++) {
    myservo2.writeMicroseconds(2000-i);
    delay(speed);
    }
}



