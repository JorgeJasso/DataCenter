# Data Center
## Presentación 
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/Presentacion.jpg">

## Introducción
El siguiente proyecto consiste en un sistema de control de seguridad para un Data Center, simulando las funciones de alarma, notificaciónes y cerrado automático de puertas. 
El sistema de control cumple los siguientes requisitos:
*  Incluye 3 sensores y un actuador.
*  El sistema de control muestra estadísticas de los sensores y tomar acciones en consecuencia.

Estas son algunas de las características  principales del sistema:
* El proyecto se usa para controlar un sistema de seguridad mediante sensores.
* El sistema es automatizado de manera que toma desiciones confome los resultados de las estadisticas.
* La información para el usuario se proporciona a traves del monitor serial.
* Contiene un teclado matricial para proporcionar las contraseñas y permitir el acceso al data center.
* Si la puerta principal es forzada se activa una alarma de seguridad y se cierran las puertas a servidores.

## Materiales
De Hardware
* Protoboard
* Arduino Mega 2560
* 1 servo motor sg90
* 1 Push-Button
* Sensor de temperatura y humedad dht11
* Fotoresistencia (LDR)
* Reed Switch
* Teclado matricial
* Bocina
* Iman
* Led
* Resistencias 330 ohms
* una bateria de 5V
* Cables Dupont(Jumpers) macho macho
* Cables de corriente
* Cable USB para arduino
* Computadora

De Software
* Arduino IDE
* OpenJDK
* OpenJRE
* Netbeans IDE
* Librería Keypad
* Librería DHT
* Librería Servo
* Librería RXTX

## Instalación de herramientas

### Instalación de Arduino IDE
Arduino IDE no se encuentra en los repositorios oficiales de Ubuntu, al menos la última versión, por lo que tenemos que utilizar la web oficial del Proyecto para conseguir este IDE. 
 https://www.arduino.cc/en/Main/OldSoftwareReleases 
 El archivo está comprimido y hay que extraerlo en una carpeta adecuada, recordando que se ejecutará desde allí.
 Una vez que tengamos esto, en la terminal escribimos lo siguiente:
```sh
$ sudo chmod +x install.sh 
```
Esta orden hará que el archivo de instalación pueda ejecutarse sin tener que ser root. Ahora ejecutamos en la terminal lo siguiente:
``` sh
$ ./install.sh 
```
Esto hará que comience la instalación de Arduino IDE en nuestro Ubuntu. Tras obedecer las órdenes del asistente y esperar varios segundos (o minutos, dependiendo del ordenador). Y ya está, ya tendremos Arduino IDE instalado en nuestro Ubuntu y un acceso directo en nuestro escritorio.

```sh
$ npm install --production
$ NODE_ENV=production node app
```

### Instalación de OpenJDK y OpenJRE

Abrimos la terminal y ejecutamos las siguientes instrucciones:
``` sh 
$ sudo apt-get install openjdk-8-jre openjdk-8-jdk
```
Al finalizar ejecutamos la siguiente instruccion para verificar la version instalada.
```sh
$ java -version
```
En caso de presentar el siguiente error:
No se pudo bloquear /var/lib/dpkg/lock – open (11: Recurso no disponible temporalmente). EJECUTAR los siguientes comandos: y volver a intentar la instalación.
``` sh
$ sudo fuser -vki  /var/lib/dpkg/lock
$ sudo rm -f /var/lib/dpkg/lock
$ sudo dpkg --configure -a
```

### Instalación de Netbeans IDE
Ir a la página oficial y descargar la última version de netbeans en  https://netbeans.org/downloads/start.html?platform=linux&lang=es&option=all.
Se extrae el archivo de la carpeta y se ejecuta en la terminal
```sh
$ sudo chmod +x netbeans-8.2-linux.sh
$ sudo ./netbeans-8.2-linux.sh
```
Ya iniciado el instalador nos permite realizar en un entorno gráfico, se recomienda quitar las opciones para instalar Apache Tomcat y GlassFish por el momento. y dar clic en “Next” hasta terminar el proceso de instalación.
Por ultimo Ya en nuestras aplicaciones buscamos “NetBeans IDE 8.2”, esperamos que inicie.

### Instalación de librería RXTX
Ejecutamos en la terminal los siguientes comandos.
```sh
$ sudo apt-get install librxtx-java
$ sudo cp -r /usr/lib/jni/librxtxSerial.so /usr/lib/x86_64-linux-gnu
$ sudo cp -r /usr/lib/jni/librxtxSerial.so /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64
```
### Instalación de la librería  keypad
Descarga la libreria <keypad.h>, extrae los archivos de la carpeta comprimida y posterirormente pega toda la carpeta en las librerias de arduino.
https://playground.arduino.cc/code/keypad

### Instalación de la librería  DHT
Descarga la libreria <DHT.h>, extrae los archivos de la carpeta comprimida y posterirormente pega toda la carpeta en las librerias de arduino.
https://www.arduinolibraries.info/libraries/dht-sensor-library

### Instalación de la librería  Servo
Descarga la libreria <servo.h>, extrae los archivos de la carpeta comprimida y posterirormente pega toda la carpeta en las librerias de arduino.
http://playground.arduino.cc/ComponentLib/servo

## Montaje del circuito
### Push-Button
* Conectamos el push-button al protoboard y con cables de corriente puenteamos su pata izquierda con tierra y la pata derecha la conectaos en serie con una resitencia y despues a voltaje.
* Realizamos la conexión de la pata derecha del push-button con un cable jumper al pin PWM 8 del arduino.

### Sensor DHT11
* Conectamos con cables de corriente la pata izquierda((GND) del sensor DHT11 a tierra y la pata derecha (VCC) al voltaje.
* Conectamos una resistencia entre la pata central (Data) y la pata derecha(VCC).
* Con un cable jumper conectamos la pata central (Data) al pin PWM 13  del arduino.
### Fotoresistencia LDR
* Conectamos con cables de corriente la pata izquierda de la resistencia con voltaje.
* Conectamos en serie la pata izquierda de la fotoresistencia  junto con la pata derecha de la resistencia.
* Conectamos la pata derecha de la fotoresistencia con cables de corriente a tierra.
* Conectamos con con cables jumper la pata izquiera de la fotoresistencia  al pin analógico A0 del arduino.

## Imagenes del montaje 

## Servo motoy y Sensor de temperatura
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/ImgServoTemp.jpg" width="400" height="400">

## Boton y Fotoresistencia
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/ImgBotonFotores.jpg" width="400" height="400">

## Bocina y Reed Switch
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/ImgBocinaReed.jpg" width="400" height="400">

## Teclado matricial
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/ImgTeclado.jpg" width="400" height="400">

## Imagenes del proyecto
<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG1.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG2.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG3.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG4.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG5.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG6.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG7.JPG" width="400" height="400">

<img src="https://github.com/JorgeJasso/DataCenter/blob/master/Imagenes/IMG8.JPG" width="400" height="400">



