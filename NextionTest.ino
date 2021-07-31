/*Este ejemplo muestra en el display NEXTION 4.3" datos enviados desde ESP32
Los pines se definieron por SoftwareSerial (Libreria EspSoftwareSerial)
Se pasan los datos en formato string por facilidad de mostrar así los flotantes en nextion.

En nextion editor se agregan textos con etiquetas como "t0 ,t1, etc" pero tenemos la libertad
de nombrar las etiquetas a gusto.

Cuando enviamos datos simplemente accedemos a las etiqutas y su contenido mediante "t0.txt="*/

#include <SoftwareSerial.h>
#define RXD2 19
#define TXD2 23

float V_bateria_chica = 8.26;
float V_bateria_grande = 64.10;
float T_bateria_grande = 33.5;
float Distancia_encoder = 1200;


SoftwareSerial SerialNextion(RXD2, TXD2);//Configarión de los pines serial por software


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialNextion.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  SerialNextion.print("t0.txt=\"");
  SerialNextion.print(V_bateria_chica, 2);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t1.txt=\"");
  SerialNextion.print(V_bateria_grande, 2);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t2.txt=\"");
  SerialNextion.print(T_bateria_grande, 1);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t3.txt=\"");
  SerialNextion.print(Distancia_encoder, 0);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  delay(5000);

  SerialNextion.print("t0.txt=\"");
  SerialNextion.print(V_bateria_chica - 2, 2);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t1.txt=\"");
  SerialNextion.print(V_bateria_grande - 4, 2);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t2.txt=\"");
  SerialNextion.print(T_bateria_grande - 10, 1);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  SerialNextion.print("t3.txt=\"");
  SerialNextion.print(Distancia_encoder + 1000, 0);
  SerialNextion.print("\"");
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);
  SerialNextion.write(0xff);

  delay(5000);
}
