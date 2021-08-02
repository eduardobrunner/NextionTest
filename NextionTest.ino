/*Este ejemplo muestra en el display NEXTION 4.3" datos enviados desde ESP32
  Los pines se definieron por SoftwareSerial (Libreria EspSoftwareSerial)
  Se pasan los datos en formato string por facilidad de mostrar así los flotantes en nextion.

  En nextion editor se agregan textos con etiquetas como "t0 ,t1, etc" pero tenemos la libertad
  de nombrar las etiquetas a gusto.

  Cuando enviamos datos simplemente accedemos a las etiqutas y su contenido mediante "t0.txt="*/

#include <SoftwareSerial.h>
#define RXD2 19
#define TXD2 23
#define N_BOTONES 2

#define BOT1_PIN 34
#define BOT2_PIN 13

float V_bateria_chica = 8.26;
float V_bateria_grande = 64.10;
float T_bateria_grande = 33.5;
float Distancia_encoder = 1200;


int botones[N_BOTONES] = {BOT1_PIN,
                          BOT2_PIN
                         };

volatile unsigned long millis_aux;
volatile unsigned long tiempo_pulso_boton[N_BOTONES];
volatile unsigned long tiempo_pulso_diff[N_BOTONES];

boolean Bandera = 0;

SoftwareSerial SerialNextion(RXD2, TXD2);//Configarión de los pines serial por software


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialNextion.begin(9600);

  /*for (int i = 0; i < N_BOTONES; i++)
    pinMode(botones[i], INPUT);*/
  pinMode(botones[0], INPUT);
  pinMode(botones[1], INPUT);

  for (int i = 0; i < N_BOTONES; i++)
    attachInterrupt(digitalPinToInterrupt(botones[i]), detectBotones, CHANGE);
  nextion();
}

void loop() {
  // put your main code here, to run repeatedly:




}

void detectBotones()
{
  Serial.println("interruption!!");

  millis_aux = millis();
  for (int i = 0; i < N_BOTONES; i++)
  {
    if (!digitalRead(botones[i]))
      tiempo_pulso_boton[i] = millis_aux;
    else
    {
      tiempo_pulso_diff[i] = millis_aux - tiempo_pulso_boton[i];

      if (tiempo_pulso_diff[i] > 100 && tiempo_pulso_diff[i] < 1000)
      {

        if (Bandera)
        {
          Serial.println("apagando en nextion");

          SerialNextion.print("sleep=1");
          SerialNextion.write(0xff);
          SerialNextion.write(0xff);
          SerialNextion.write(0xff);
          Bandera = 0;
        }
        else
        {
          Serial.println("encendiendo en nextion");

          SerialNextion.print("sleep=0");
          SerialNextion.write(0xff);
          SerialNextion.write(0xff);
          SerialNextion.write(0xff);
          Bandera = 1;
        }
      }
    }
    if (tiempo_pulso_diff[i] != 0)
      tiempo_pulso_diff[i] = 0;
  }
}

void nextion ()
{
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
}
