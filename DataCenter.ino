#include <Keypad.h>
 const byte REDSWITCH = 4; //Se guarda el valor del pin que tendra el red switch.
const byte BOCINA = 5; //Indica el valor del pin que tendra la bocina.
const byte NUMFILAS = 4; //Determina el numero de filas con las que trabajara nuestro teclado matrial.
const byte NUMCOLUMNAS = 4; //Determina el numero de columnas con las que trabajara nuestro teclado matrial.
 byte pinsFilas[NUMFILAS] = {13,12,11,10}; //Se declara un arreglo que determinara los pines que utiliza el teclado matricial para las filas.
byte pinsColumnas[NUMCOLUMNAS] = {9,8,7,6}; //Se declara un arreglo que determinara los pines que utiliza el teclado matricial para las columnas.
char tecla; //Almacena el valor de la tecla presionada
char tecladoMatricial[NUMFILAS][NUMCOLUMNAS]=
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'},
}; //Arreglo que especifica los caracteres del teclado matrial.
 Keypad teclado = Keypad(makeKeymap(tecladoMatricial),pinsFilas,pinsColumnas,NUMFILAS,NUMCOLUMNAS); //Declara una instancia de Keypad indicando los parametros (tecladoMatricial, pinsFilas, pinsColumnas, NUMFILAS, NUMCOLUMNAS).
 void setup() {
  pinMode(REDSWITCH,INPUT); //Asigna el pin 4 al red switch pero con un valor INPUT.
  pinMode(BOCINA,OUTPUT); //Asigna el pin 5 a la bocina.
  Serial.begin(9600); 
}
 void loop() {
  if(digitalRead(REDSWITCH)==HIGH){
  //Comprueba si el iman se ha alejado del red switch, si es asi empezara a sonar la bocina.
  tecla=teclado.getKey();
  if(tecla!=NO_KEY){
    Serial.println(tecla);
  }
  if(digitalRead(REDSWITCH)==HIGH){
    tone(BOCINA,587);
    delay(500);
    noTone(BOCINA);
    delay(500);
  }else{
    noTone(BOCINA); //Si el iman esta cerca del red switch entonces debe dejar de sonar la alarma.
    noTone(BOCINA);
  }
}
 }

