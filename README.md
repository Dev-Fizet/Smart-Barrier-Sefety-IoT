# Smart Security for Industry IoT

Smart Security for Industry IoT es un proyecto que busca crear un entorno seguro dentro de la industria para permitir la seguridad de quienes trabajan en ella. 
Debido a que la seguridad en la industria es muy amplia el proyecto se enfoca en variables de seguridad específicas.
Una de las variables de seguridad en las que se trabaja en este proyecto es en niveles de CO2, para ello se colocan sensores  que determinen el nivel de CO2 presente en la zona durante un tiempo determinado, y de esta forma mandar una señales constantes para ser graficadas y que el usuario pueda monitorear los niveles de CO2.
También se presta atención en aquellas zonas donde el trabajador tiene prohibido el acceso, como lo son aquellas zonas donde el robot o máquina trabajan a altas velocidades, o zonas de alto voltaje, en resumen, zonas que signifiquen un riesgo significativo para el operador. Para esta parte del proyecto se utiliza un sensor de proximidad que alerte al trabajador cuando se encuentre en una zona de alto riesgo.
Otra variable importante, y muy común dentro del ámbito de seguridad es el uso de un detector de vibraciones.
Finalmente, el proyecto queda completo con un detector de cascos de seguridad que permite el acceso a los trabajadores únicamente si cuentan con su equipo de seguridad.

## Objetivos

+ Haciendo uso de un sensor de proximidad realizar un dispositivo de seguridad que indique al usuario cuando se encuentrte en una zona de alto riesgo, en donde su acceso está prohibido.
+ Construir un prototipo que sense los niveles de CO2 y con los datos obtenidos se grafique para monitoreo del usuario.
+ Programar un código que identifique si una persona lleva puesto casco de seguridad para permitir su acceso.
+ Realizar un dashboard en Node Red donde se puedan visualizar todos los datos obtenidos de las diferentes variables de seguridad que se establecieron al inicio del proyecto, como lo son los niveles de CO2, acceso a zonas determinadas y verificación del casco de seguridad.

## Justificación

Dentro de la industria, se pueden encontrar máquinas que facilitan diversos procesos, como el envasado o la fabricación de productos. Estas máquinas a menudo operan a altas velocidades o ejercen una fuerza considerable, lo que representa un riesgo para quienes se encuentren cerca de ellas. Las máquinas son solo uno de los múltiples ejemplos de los riesgos existentes en el entorno industrial. Por tanto, la seguridad desempeña un papel fundamental en la protección de los trabajadores y en la prevención de accidentes en este ámbito.

Sin embargo, en ocasiones, los propios trabajadores pueden ser la causa de los accidentes debido a descuidos, como no utilizar el equipo de seguridad adecuado o ingresar a zonas no seguras. Con la elaboración de este proyecto, se busca reducir las distracciones que puedan afectar a los trabajadores mediante la implementación de alertas que les indiquen cuando se encuentren en una zona peligrosa o les recuerden la necesidad de utilizar su equipo de seguridad.

El objetivo principal de este proyecto es mejorar la seguridad laboral y minimizar los riesgos en el entorno industrial. Al establecer un sistema de alertas efectivo, se pretende crear un ambiente de trabajo más seguro y consciente, donde los trabajadores estén constantemente recordados de la importancia de cumplir con las medidas de seguridad establecidas. De esta manera, se espera prevenir accidentes y garantizar la integridad y bienestar de todos los empleados en el entorno industrial

## Requisitos Generales

Componentes a utilizar

+ 3 ESP32 
+ ESP32 CAM OV2640
+ FTDI TTL USB Serial Converter FT232RL
+ LED
+ Resistencia de 330Ω
+ Resistencia de 1KΩ
+ Resistencia de 100KΩ
+ Transistor 2N2222
+ DFPLayer 
+ Bocina de 3W
+ Sensor Ultrasónico HC-SR04 
+ Sensor Acelerómetro y Giroscopio MPU6050
+ Sensor MQ-135 
+ Raspberry Pi 
+ SD 32GB 
+ Fuente para Raspberry 
+ Red WiFi Inalambrica de tipo 2.4 Ghz


Además se necesitará tener instalado en el PC:

+ Arduino IDE
+ Libreria PubSubClient
+ Libreria AverageValue 
+ Libreria ArduinoJson 
+ Libreria MPU6050
+ Libreria DFPayer
+ Mediapipe, para instalarlo ejecuta 'pip install mediapipe'
+ Python (cualquier versión entre las 3.6 y 3.8, ya que las librerías que se utilizarán trabajan en estas versiones).
+ OpenCV, para instalar OpenCV  ejecuta 'pip install opencv-contrib-python' desde la terminal de Python.

Por otro lado para ejecutar el servidor en la Raspberry Pi se necesitará realizar los siguientes cursos;

+ [Instalación de Raspberry OS en Raspberry Pi 4](https://edu.codigoiot.com/course/view.php?id=823)
+ [Configurar WiFi y SSH en Raspberry Pi sin Monitor](https://edu.codigoiot.com/course/view.php?id=815)
  
Adicionalmente tambien se puede instalar el VNC para lograr ver el escritorio a distancia
+ [Comunicación VNC con la Raspberry Pi](https://edu.codigoiot.com/course/view.php?id=816)

Ademas via SSH o VNC sera necesario instalar y configurar los siguientes paquetes. 
+ Node Red ,[Instalar Node RED en Raspberry Pi](https://nodered.org/docs/getting-started/raspberrypi)
+ MySQL, [Instalar MySQL en Raspberry Pi](https://randomnerdtutorials.com/raspberry-pi-apache-mysql-php-lamp-server/
)
+ Grafana: [Instalar Grafana en Raspberry Pi](https://grafana.com/tutorials/install-grafana-on-raspberry-pi/)

EL proyecto esta compuesto por tres modulos y un servidor

+ Servidor en Raspberry
+ Módulo Detector CO2
+ Módulo Detector de Casctos
+ Módulo Detecctor de Vibración y Distancia

A lo largo de esta descripcción se detallan los modulos.

## Detector CO2
<p> En este apartado encontras un breve resumen de la codigos de la carpeta llamada: CO2 y su conexion con node-red. Tambien encontraras un diagrama de conexiones para que puedas ver el codigo en funcionamiento. </p>

Para poner en marcha este apartado, se utilizara el siguiente codigo en arduino: [CO2 con Node-Red](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/tree/main/CO2/Codigos%20para%20ESP32/CO2%20con%20Node-red). En donde encontrarás la calibracion del sensor MQ-135 para obtener solamente la lectura de CO2 (sensor que es utilizado en ste proyecto). Tambien en el codigo encontraras la conexion al broker hivemq, esta comonicacion nos permitira enviar las PPM (Partes por millón) del sensor a traves de internet y esta misma las recibira en node-red. 

A continuacion se muestra como node-red realiza el recebimiento de datos 

![Node-red](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/Media/Node-red%20receptro.png)

Como se puede observar en la imagen el escuchador se suscribe al tema para poder obtener el dato, este recibira un paquete json que contendra: 

  + El nombre del emisor 
  + El dato del emisor 
  
Despues pasara por un json para convertirlo a object y en las funciones se extraeran los datos para inyectarlos a la base datos, tambien se colocaron varios debug para revisar que todo este saliendo de la manera correcta. 

La siguiente parte del flow en node red es la siguiente: 

![Node-red conexion](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/Media/Node-red%20conexion.png)

Primero el usuario tendra que colocar el limite de partes por millon permitidas en el ambiente que este sensando, para posteriormente cuando se sobre pase el limite accionar algun ventilador. Esta parte del flow manda el mensaje a otra ESP32 que activara o desactivara algun dispositivo. 

Despues se necesitara el codigo de la ESP32 que prendera el dispositivo: [Conexion-ESP32](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/tree/main/CO2/Codigos%20para%20ESP32/Conexion_desconexion) 

Este programa realizara la activacion de un relevador para el encendido de un dispositivo cuando reciba un "TRUE" enviado por el mensajero de Node-red cuando las ppm sean mayores a las colocadas por el usuario. 

En esta imagen se muestran las conexiones del relavador *Verifica que las conexiones esten bien antes de conectarlo la clavija, ya que podria causar un cortocircuito*

![Conexion-esp32-relevador](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/Media/Esquema_ESP32-Foco.png)

Por ultimo se utilizo grafana para poder graficar los datos del sensor, teniendo el dashboard de la siguiente manera: 
![Dashboard-CO2](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/Media/Dashboard-CO2.png)

Si quieres saber como se realiza la calibracion de este sensor y toda la logica que hay en este apartado, preciona click [aquí](https://edu.codigoiot.com/course/view.php?id=993#section-0), ademas comparto el flow donde viene todo este partado. [Node-red-CO2](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/CO2_Node-red.json)
 
## Detector de cascos

En este repositorio encontrarás los archivos necesarios para poder realizar la parte de detección de cascos. Para este proyecto se hará uso de la ESP32CAM.

Esta sección consiste en detectar si una persona trae puesto un casco de seguridad, si se detecta que lo trae puesto mandará un mensaje por MQTT a Node Red en donde se activará un indicador que será visible en un dashboard como se ve en la siguiente imagen.

![Dashboard de en Node Red](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/Dashboard.png)

Una vez que se ha mandado el mensaje a Node Red, la ESP32CAM leerá ese mensaje y prenderá un LED indicando que se permite el acceso.

Deberás seguir los siguientes pasos para ejecutar esta parte del proyecto:


1. Crea una carpeta llamada Dataset y en ella descarga las dos carpetas que encontrarás dando clic [aquí](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/tree/main/Detector%20de%20cascos/Dataset)

2. Entrena el modelo con el código llamado  [Train.py](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/Detector%20de%20cascos/Train.py). Al ejecutar el código se creará un archivo llamado "modelo_cascos.xml".

3. Realiza la siguiente conexión:

![Conexión para configurar IP de la esp32](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/Esquema1.jpg)

En Arduino IDE abre el ejemplo de CameraWebServer dando dirigiéndote a File>Examples>ESP32>Camera>CameraWebServer

Coloca el nombre de tu Red WiFi y tu contraseña.

![Configuración de red](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/RED_y_contrase%C3%B1a.png)

Sube el programa a la ESP32, recuerda que para subir un código deberás conectar con el pin IO0 con GND, y retirar la conexión una vez completado el proceso. Para que se ejecute el código deberás presionar el botón de reset de la ESP32. 

En el monitor serial aparecerá una IP asignada para tu ESP32, será algo parecido a esto: http://192.168.100.26

Ahora ya puedes ejecutar el código Prueba_cascos.py. Solo cambia la IP que obtuviste en la siguiente línea del código.

![Línea a modificar](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/L%C3%ADnea%20a%20modificar.png)

4. Dirígete a Node Red y agrega el el flow [Detector_de_cascos.json](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/Detector_cascos.json)

5. Realiza la siguiente conexión:

![Conexión con led](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/Esquema2.jpg)

Una vez terminadas las conexiones descarga la carpeta donde se encuentra el código de la ESP32, puedes encontrarla dando clic  [aquí](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/tree/main/Detector%20de%20cascos/ESP32MQTT)

Habrá cuatro archivos diferentes, tres de ellos son necesarios para que la  ESP32 pueda conectarse a WiFi. Abre el archivo que se llama "ESP32MQTT.ino".

Al igual que en ejemplo CameraWebServer, deberás poner el nombre y contraseña de tu red WiFi.

Además deberás agregar los datos del broker al que se conectará, el broker utilizado es brokerhivemq.com

Debido a que se necesita una IP para poder conectarse usa el comando nslookup broker.hivemq.com desde tu terminal, de esta forma obtendrás la IP del broker público, esa IP es la que deberás colocar en la línea 41 del código. 

Una vez hecho esto carga el programa en la ESP32 y listo, ya tienes un programa que identifica si se lleva casco de seguridad. Si es así envía un mensaje por MQTT que es recibido por Node Red y activa un indicador. La ESP32 lee el mensaje que llega a Node Red y enciende un LED.

## Detector de Movimiento y Proximidad

En este repositorio encontrarás los archivos necesarios para poder realizar el modulo 


![Diagrama de Conección](https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/M%C3%B3dulo%20Detecci%C3%B3n%20de%20Movimiento%20y%20Proximidad/Circuito%20Modulo%20Deteccion%20Movimiento%20y%20Proximidad_bb.png)




## Elaborado por
+ Carlos Roberto Figueroa Zetina
+ Karen Yizel Rosas Trejo
+ Arath Tzec Vargas
