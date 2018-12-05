const byte REDSWITCH = 4; //Se guarda el valor del pin que tendra el red switch.
const byte BOCINA = 5; //Indica el valor del pin que tendra la bocina.
 void setup() {
  pinMode(REDSWITCH,INPUT); //Asigna el pin 4 al red switch pero con un valor INPUT.
  pinMode(BOCINA,OUTPUT); //Asigna el pin 5 a la bocina.
 }
 void loop() {
  if(digitalRead(REDSWITCH)==HIGH){ //Comprueba si el iman se ha alejado del red switch, si es asi empezara a sonar la bocina.
    tone(BOCINA,587);
    delay(500);
    noTone(BOCINA);
    delay(500);
  }else{
    noTone(BOCINA); //Si el iman esta cerca del red switch entonces debe dejar de sonar la alarma.
  }
 }
