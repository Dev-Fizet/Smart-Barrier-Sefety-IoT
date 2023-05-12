
var client = mqtt.connect("wss://test.mosquitto.org:8081/mqtts");
//Si lo usas en hosting para usar encriptado https
// var client = mqtt.connect("wss://test.mosquitto.org:8081/mqtts")

function EventoConectar() {
  console.log("Conectado a MQTT");
  client.subscribe('CloudCo2/datos_mq135', { qos: 1, clientId: 'Tzec-' + Math.random().toString(16).substr(2, 8) })
}

const generateRandomColor = () => {
  const r = Math.floor(Math.random() * 256);
  const g = Math.floor(Math.random() * 256);
  const b = Math.floor(Math.random() * 256);

  const rbgColor = `rgb(${r},${g},${b})`;
  return rbgColor;
};

function EventoMensaje(topic, message) {
  console.log(topic + " - " + message.toString());
  document.getElementById("valorA").textContent = message.toString();
  const newColor = generateRandomColor();
  console.log(newColor);
  document.getElementById("valorA").style.color= newColor; 
}


client.on("connect", EventoConectar);
client.on("message", EventoMensaje);

console.log("Empezando a conectar");
