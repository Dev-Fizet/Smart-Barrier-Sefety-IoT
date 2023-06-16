/*
Programación de Arduino para el Modulo de Detección de Vibracion (MPU6050) y Distancia (HC-SR04)

Para compilar el codigo es necesario las siguientes librerias
Creador/Nombre de la libreria @ Versión Utilizada
adafruit/Adafruit MPU6050 @ ^2.0.3
adafruit/Adafruit Unified Sensor @ ^1.1.4
dfrobot/DFRobotDFPlayerMini@^1.0.5
knolleary/PubSubClient@^2.8
bblanchon/ArduinoJson@^6.21.2

Creado por Carlos Fizet 
Proyecto Final del Curso IoT por Código IoT
Junio 2023
*/

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DFRobotDFPlayerMini.h"

// Configuración de WiFi

#define BUILTIN_LED 2
const char *ssid = "Fizet IoT";
const char *password = "carloscarlos";
const char *mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
char datos[200];
//
void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
    digitalWrite(BUILTIN_LED, LOW);
    // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  }
  else
  {
    digitalWrite(BUILTIN_LED, HIGH);
    // Turn the LED off by making the voltage HIGH
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Fizet-Dev-Out", "Fizet Dev ESP32 Online");
      // ... and resubscribe
      client.subscribe("Fizet-Dev-In");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//
HardwareSerial mySoftwareSerial(1);
DFRobotDFPlayerMini myDFPlayer;

// Configuración de Sensor Ultrasónico

const int trigPin = 5;
const int echoPin = 18;

// define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

// Configuracion mpu6050
Adafruit_MPU6050 mpu;

//

void setup()
{

  mySoftwareSerial.begin(9600, SERIAL_8N1, 16, 17); // speed, type, RX, TX
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  // Inicio de WiFi y
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output

  Serial.println();
  Serial.println(F("Smart Security for Industry IoT by Fizet"));
  Serial.println(F("Initializing DFPlayer"));

  if (!myDFPlayer.begin(mySoftwareSerial))
  { // Use softwareSerial to communicate with mp3.

    Serial.println(myDFPlayer.readType(), HEX);
    Serial.println(F("Unable to begin:"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); // Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(30); // Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  // Inicio de mpu6050

  //
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!

  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 OK!");
  //

  // setup motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println(F("Mensaje de Inicio"));
  myDFPlayer.play(1); // Play the first mp3
  delay(4000);        // Duración del mensaje

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println(F("Mensaje de WiFi OK"));
  myDFPlayer.play(2); // Play the first mp3
  delay(6000);        // Duración del mensaje
}

void loop()
{

  // MQTT
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  if (mpu.getMotionInterruptStatus())
  {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    Serial.print("AccelX:");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print("AccelY:");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print("AccelZ:");
    Serial.print(a.acceleration.z);
    Serial.print(", ");
    Serial.print("GyroX:");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print("GyroY:");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.print("GyroZ:");
    Serial.print(g.gyro.z);
    Serial.println("");
    //
    // Crear el objeto JSON
    DynamicJsonDocument jsonDoc(200);
    jsonDoc["nombre"] = "ESP32 Fizet Dev";
    jsonDoc["AccelX"] = a.acceleration.x;
    jsonDoc["AccelY"] = a.acceleration.y;
    jsonDoc["AccelZ"] = a.acceleration.z;
    jsonDoc["GyroX"] = g.gyro.x;
    jsonDoc["GyroY"] = g.gyro.y;
    jsonDoc["GyroZ"] = g.gyro.z;

    // Serializar el JSON a una cadena
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    jsonString.toCharArray(datos, 200);

    client.publish("Fizet-Dev-Out/Movimiento", datos);

    Serial.println(F("Mensaje de Alerta Detección de Movimiento"));
    myDFPlayer.play(3); // Loop the first mp3
    delay(6000);
  }
  else
  {
    myDFPlayer.pause(); // pause the mp3
  }

  // Programación Sensor Ultrasónico
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if (distanceCm <= 20)
  {

    // Crear el objeto JSON
    DynamicJsonDocument jsonDoc(200);
    jsonDoc["nombre"] = "ESP32 Fizet Dev";
    jsonDoc["datos"] = distanceCm;

    // Serializar el JSON a una cadena
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    jsonString.toCharArray(datos, 200);

    client.publish("Fizet-Dev-Out/Distancia", datos);

    Serial.println(F("Mensaje de Alerta de Alto Riesgo"));
    myDFPlayer.play(4); // Loop the first mp3
    delay(6000);
  }
  else
  {
    myDFPlayer.pause(); // pause the mp3
  }
}