String MensajeEnviado;
String MensajeRecibido;
String Modo;
bool inicio = true;
bool fin = true;
int i = 1;


void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);                 //Velocidad de comunicacion con el modulo SIM800L
  Serial2.begin(19200);                 //Velocidad de comunicacion con la Pantalla NEXTION
  Serial.println("Inicializando...");
  delay(1000);
  Serial1.println("AT"); //Handshake con el modulo SIM800L para comprobar su conectividad .
  HandShake();
  Serial1.println("AT+CMGF=1");         // Configurar el módulo en modo de texto .  
  HandShake();                        
  Serial1.println("AT+CNMI=2,2,0,0,0"); //Configuracion de la forma como recibir mensajes.
  HandShake();
  MensajeRecibido.reserve(250);
}

void loop() {                        
  if (Serial2.available())   //Comprobamos disponibilidad de datos provenientes de la pantalla Nextion.
  {
    Modo = Serial2.readStringUntil("\n");
      if(Modo.indexOf ("enviar") >= 0) //Comando para el envio de mensaje
      {
        EnviarSMS();       
        Modo = "";      
      }
    else if(Modo.indexOf ("borrar") >= 0) //Comando de limpieza de bandeja de entrada
    {
      i = 1;
      Modo = "";
    }
   }
   else {
    RecepcionSMS ();
   }
  inicio = true;
  fin = true;
}

void HandShake(){   // Funcion para la lectura de comandos del SIM800L luego de relizar un handshake
    delay(500);
    while (Serial1.available())
    {
      String lectura=Serial1.readStringUntil("\n");
      Serial.println(lectura);        
    }  
}

void RecepcionSMS ()  //Funcion para la recepcion de SMS
{          
    if (Serial1.available())
    {      
      MensajeRecibido = Serial1.readStringUntil("\n");
      int Size = MensajeRecibido.length();
      String a = MensajeRecibido.substring(9, 21);
      String b = MensajeRecibido.substring(50, Size); 
      Serial.println(MensajeRecibido);        
      Serial2.print("Slot");      
      Serial2.print(i);
      Serial2.print(".txt=\"Mensaje de: ");
      Serial2.println(a);
      Serial2.print(b);           
      Serial2.print("\"");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);              
      i++;       
    }     
    if (i > 3){
    i = 1;        
    }     
}

void SerialFlush () // Limpieza del buffer para omitir datos denominados basura o inservible.
{
  while (Serial1.available())
  {
    Serial1.read();
  }
}

void EnviarSMS() //Funcion para el envio de SMS
{  
  Serial1.println("AT+CMGF=1");
  delay(200);

  while (inicio)
  {
    if (Serial2.available()) 
    {  
      String Numero = Serial2.readStringUntil("\n");            
      Serial1.println("AT+CMGS=\"+503" + Numero + "\""); //"+503" es el codigo de area que se asigna previo al numero de telefono en El Salvador. Este codigo cambia segun tu pais.
      delay(200);                                         
      while (fin) 
      {
        if (Serial2.available())
        {
          String MensajeEnviado = Serial2.readStringUntil("\n");
          int MensajeLength = MensajeEnviado.length();
          if (MensajeLength <= 120) //Mensaje con un maximo de 120 caracteres
          {
            Serial1.println(MensajeEnviado);      
            delay(200);
            Serial1.print((char)26);       
            delay(5000);       
            SerialFlush();    
            inicio = false;
            fin = false; 
          }  
         }                       
        }                   
      }
   }
}  
