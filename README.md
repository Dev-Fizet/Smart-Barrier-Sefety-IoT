# Smart Security for Industry IoT

Smart Security for Industry IoT es un proyecto que busca crear un entorno seguro dentro de la industria para permitir la seguridad de quienes trabajan en ella. 
Debido a que la seguridad en la industria es muy amplia el proyecto se enfoca en variables de seguridad específicas.
Una de las variables de seguridad en las que se trabaja en este proyecto es en niveles de CO2, para ello se colocan sensores  que determinen el nivel de CO2 presente en la zona durante un tiempo determinado, y de esta forma mandar una señales constantes para ser graficadas y que el usuario pueda monitorear los niveles de CO2.
También se presta atención en aquellas zonas donde el trabajador tiene prohibido el acceso, como lo son aquellas zonas donde el robot o máquina trabajan a altas velocidades, o zonas de alto voltaje, en resumen, zonas que signifiquen un riesgo significativo para el operador. Para esta parte del proyecto se utiliza un sensor de proximidad que alerte al trabajador cuando se encuentre en una zona de alto riesgo.
Otra variable importante, y muy común dentro del ámbito de seguridad es el uso de un detector de vibraciones.
Finalmente, el proyecto queda completo con un detector de cascos de seguridad que permite el acceso a los trabajadores únicamente si cuentan con su equipo de seguridad.

## Objetivos

+ efekfdkfdklfdf

## Justificación


## Requisitos

## Detector CO2
<p> En este apartado encontras un breve resumen de la codigos de la carpeta llamada: CO2 y su conexion con node-red. Tambien encontraras un diagrama de conexiones para que puedas ver el codigo en funcionamiento. </p>

Antes de comenzar necesitaras instalar algunas librerias: 

Para poder llegar al archivo ==> [CO2_con_MQTT.ino] (https://github.com/Dev-Fizet/Smart-Security-for-Industry-IoT/blob/main/CO2/CO2_con_MQTT.ino) se tuvo que realizar una calibracion previa, esta calibracion y toda al explicacion a fondo del programa la puedes encontrar en: [Calibracion sensor MQ-135] (https://edu.codigoiot.com/mod/lesson/edit.php?id=3914&mode=full) en donde se trata de emitar la curva que tiene el sensor MQ-135 al momento de medir solamente CO2. 

Recomiendo que el sensor de caliente o se mantenga encendido durante 24 horas para eliminar alguna humedad que contenga. Una vez calibrado, el codigo toma en cuenta las diferentes variables calculadas, para despues realizar la lectura de PPM. 

Cuando se han calculado las partes 
  
 
## Detector de cascos


## Elaborado por
