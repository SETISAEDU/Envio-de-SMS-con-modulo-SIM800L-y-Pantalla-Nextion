# Envio-de-SMS-con-modulo-SIM8000-y-Pantalla-Nextion
Repositorio de archivos utilizados en el proyecto envio de SMS con el modulo SIM800L combinado con la pantalla Nextion y Arduino

# Diagrama de conexión
![Diagrama](https://raw.githubusercontent.com/SETISAEDU/Envio-de-SMS-con-modulo-SIM800L-y-Pantalla-Nextion/master/SIM800L_SMS_NEXTION_DIAGRAMA.png)


**Antes de iniciar, considere insertar una tarjeta SIM con saldo al módulo SIM800L para poder realizar el tutorial presentado acontinuacion**

Haciendo uso de la interfaz de edicion `Nextion Editor` creamos una aplicion para la pantalla Nextion  que nos permita enviar SMS  hasta un dispositivo celular. De igual manera poder recibir SMS de respuesta en nuestra pantalla. La comunicación del modulo `SIM800L` y nuestra patalla es gracias al variedad de puertos seriales que pose nuestro Arduino Mega, ya que este es el bridge de comunicacion entre ambos dispositivos bajo la base del protocolo UART.

La interfaz esta diseñada para poder enviar SMS hasta un dispostivo celular , permitiendo colocar el nuemero de telefono y el mensaje deseado, haciendo uso de un teclado tipo QWERTY desplegado en nuestra pantalla NEXTION. En la bandeja de entrada nos permite alojar hasta 3 mensajes de respuesta provenientes de cualquier dispositivo movil. Agregando la funcion de poder desplegar cada mensaje de manera independiente en una nueva pagina de vizualizacion. Y un boton de borrar para poder limpiar nuestra bandeja de entrada.


