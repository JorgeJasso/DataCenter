//--------------------------------------------------------------------LIBRERIAS A UTILIZAR.

#include <Keypad.h> //Se incluye la libreria Keypad para poder uilizar el teclado matricial.
#include <DHT.h> //Incluye librería de control del sensor.
#include <Servo.h> // Incluimos la biblioteca para poder utilizar el Servo.


//-------------------------------------------------------------------DECLARACIÓN DE VARIABLES.

//----------CONSTANTES Y VARIABLES PARA EL TECLADO MATRICIAL

const byte REDSWITCH = 20; //Se guarda el valor del pin que tendra el red switch.
const byte BOCINA = 21; //Indica el valor del pin que tendra la bocina.
const byte NUMFILAS = 4; //Determina el numero de filas con las que trabajara nuestro teclado matrial.
const byte NUMCOLUMNAS = 4; //Determina el numero de columnas con las que trabajara nuestro teclado matrial.
const String CLAVE =  "7"; //Guarda la clave que se utilizara para verificar el ingreso a la propiedad.
boolean estadoAlarma = HIGH; //Determina si la alarma esta encendida (sonara la bocina en caso de que se abra la puerta) o apagada (se podra abrir la puerta y no sonara la bocina).
byte pinsFilas[NUMFILAS] = {38, 40, 42, 44}; //Se declara un arreglo que determinara los pines que utiliza el teclado matricial para las filas.
byte pinsColumnas[NUMCOLUMNAS] = {46, 48, 50, 52}; //Se declara un arreglo que determinara los pines que utiliza el teclado matricial para las columnas.
char tecla; //Almacena el valor de la tecla presionada
char tecladoMatricial[NUMFILAS][NUMCOLUMNAS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
}; //Arreglo que especifica los caracteres del teclado matrial.
String claveIngresada = ""; //Variable utilizada para ir almacenando los caracteres que ingrese el usuario.
Keypad teclado = Keypad(makeKeymap(tecladoMatricial), pinsFilas, pinsColumnas, NUMFILAS, NUMCOLUMNAS); //Declara una instancia de Keypad indicando los parametros (tecladoMatricial, pinsFilas, pinsColumnas, NUMFILAS, NUMCOLUMNAS).


//----------VARIABLES PARA EL SENSOR Y FOTORESISTENCIA

#define DHTPIN 2 //Defiene el pin al que se conectará el sensor.
#define LDR_pin A0 //Define la entrada analogica para la fotorresistencia.
#define DHTTYPE DHT11 //Seleciona el tipo de sensor a utilizar.
DHT dht(DHTPIN, DHTTYPE); //Configura la librería pasando como parametros el pin y tipo de sensor.
float temperatura = 0; //Declara la variable que almacenara la temperatura.
float humedad = 0; //Declara la variable que almacenara la humedad.
float luminosidad = 0; //Declara la variable que almacenara la luminosidad.


//----------VARIABLES PARA CONTROLAR EL NÚMERO DE VECES QUE SE MANDARÁ EL MENSAJE

int contAlarma = 0; //controla el numero de veces que se manda el mensaje de la alarma.
int contLuminosidad = 0; //controla el numero de veces que se manda el mensaje de luminosidad.
int contTemperatura = 0; //controla el numero de veces que se manda el mensaje de temperatura.


//----------CONSTANTES Y VARIABLES PARA LOS SERVOMOTORES.
const int PIN_SERVO = 13; //Indica el pin que usará la pinza.
const int TIEMPO = 200; // definimos el tiempo entre pasos del servo (velocidad).
boolean estadoPuerta = true; //Sirve para ver si la puerta esta abierta o cerrada.
Servo servo; // Definimos el servo que utilizaremos.


//-------------------------------------------------------------------SETUP

void setup() {
  pinMode(REDSWITCH, INPUT); //Asigna el pin 20 al red switch pero con un valor INPUT.
  pinMode(BOCINA, OUTPUT); //Asigna el pin 21 a la bocina.
  Serial.begin(9600); //Define 9600 como la velocidad del Serial.
  dht.begin();//Inicializa la libreria DHT.
  pinMode(LDR_pin, INPUT); //Establece que el LDR sera de entrada.
  servo.attach(PIN_SERVO);//Se indica el pin que utiliza el servo.
  servo.write(0); //Lleva el servo a su posicion inicial.
}


//-------------------------------------------------------------------LOOP

void loop() {
  tecla = teclado.getKey(); //Obtiene el caracter del teclado.
  humedad = dht.readHumidity();// Lee la humedad.
  temperatura = dht.readTemperature();//Lee la temperatura.
  luminosidad = analogRead(LDR_pin); //Lee la luminosidad.
  //Serial.println(String("T:") + temperatura + String("C H:") + humedad + String("% L:") + luminosidad); //Imprime la humedad, temperatura y luminosidad.
  if (tecla != NO_KEY) { //Si se presiono una tecla del teclado matricial entra en esta parte de codigo.
    if (tecla == '*') { //El asterisco sirve para ingresar todos los caracteres presionados antes de él.
      if (claveIngresada == CLAVE) { //Entra cuando claveIngresada es igual a CLAVE (271115).
        Serial.println("Bienvenido");
        estadoAlarma = LOW; //Desactiva la alarma para poder ingresar a la casa.
        if (!estadoPuerta) { //Si la puerta esta cerrada
          estadoPuerta = true; //Indica que se abrio la puerta 
          for (int i = 180; i >= 0; i = i - 10) {//For para ir moviendo el servo por pasos.
            servo.write(i); //Mueve el servo a la posicion i.
            delay(TIEMPO);//Espera el tiempo especificado.
          }
        }
      } else {
        Serial.println("Clave incorrecta");//Indica si la clave ingresada no es correcta.
      }
      claveIngresada = ""; //Limpia cualquier valor que haya estado contenido en CLAVEINGRESADA.
    } else {
      Serial.println(tecla); //Imprime la tecla presionada.
      claveIngresada = claveIngresada + tecla; //Si aun no se ha precionado asterisco ingresa el caracter a claveIngresada.
    }
  }
  if (digitalRead(REDSWITCH) == HIGH) { //Comprueba si el iman se ha alejado del red switch.
    if (estadoAlarma == HIGH) { //Si se alejo y la alarma estaba activada entonces tiene que sonar.
      if (contAlarma == 0) {
        Serial.println("ATENCIÓN: LA ALARMA FUE ACTIVADA"); //Imprime que la alarma esta encendida.
        if (estadoPuerta) { //Solo si la puerta esta abierta la cierra
          estadoPuerta = false;
          for (int i = (-10); i < 180; i = i + 10) { //Va moviendose entre el servo para cerrar la puerta.
            servo.write(i); //Mueve el servo en la posicion i.
            delay(TIEMPO);
          }
        }
        contAlarma = 1; //Indica que ya se mando el mensaje de la alarma.
      }
      tone(BOCINA, 587);//Suena la alarma.
      delay(500);
      noTone(BOCINA);//Y despues se apaga.
      delay(300);
    } else {
      delay(300);
      if (digitalRead(REDSWITCH) == LOW) { //Vuelve a comprobar, si el iman ya esta cerca del red switch.
        estadoAlarma = HIGH; //Si fue asi entonces la alarma se vuelve a activar.
      }
    }
  } else {
    noTone(BOCINA); //Si el iman esta cerca del red switch entonces debe dejar de sonar la alarma.
    contAlarma = 0; //Indica que si se vuelve a violar la alarma ya puede mandar otro mensaje.
  }
  if (luminosidad > 15 && digitalRead(REDSWITCH) == LOW) { //Solo entre si el foco esta prendido y la puerta cerrada.
    if (contLuminosidad == 0) {
      Serial.println("ATENCIÓN: LA LUCES ESTAN ENCENDIDAS");//Manda la alerta.
      contLuminosidad = 1;//Indica que ya se mando la alerta.
    }
  } else {
    contLuminosidad = 0;//Indica que ya se puede mandar otro mensaje en dado caso de que el foco este prendido.
  }
  if (temperatura > 21) { //Si la tempratura es mayor a 21 grados entra
    if (contTemperatura == 0) {
      Serial.println("ATENCION: LA TEMPERATURA DE LOS SERVIDORES ES MUY ALTA"); //Manda la alerta.
      contTemperatura = 1;//Señana que la alerta de temperatura ya se mando.
    }
  } else {
    contTemperatura = 0;//Indica que ya se puede mandar otra alerta.
  }
}

