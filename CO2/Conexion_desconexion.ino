#include <WiFi.h>
#include <PubSubClient.h>

// Configuración de red
const char* ssid = "Totalplay-559F";
const char* password = "559FF198UfvsqdDs";

// Configuración del servidor MQTT
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "testeo/sensormq135-Tzec/estado"; // Tema MQTT al que te suscribes

// Configuración del pin del LED
const int ledPin = 13;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(ledPin, OUTPUT);
  
  // Conexión a la red WiFi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a la red WiFi");
  
  // Configuración del cliente MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado al servidor MQTT");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Error de conexión al servidor MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying...");
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Mensaje recibido desde el tema: ");
  Serial.println(topic);
  Serial.print("Contenido del mensaje: ");
  Serial.println(message);
  
  if (message.equals("TRUE")) {
    digitalWrite(ledPin, HIGH);
  } else if (message.equals("FALSE")) {
    digitalWrite(ledPin, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión al servidor MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Falló, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando nuevamente en 5 segundos");
      delay(5000);
    }
  }
} /// msg.payload = '{"mensajero": "node-red", "estado": "' + global.get("estado") + '" }';
