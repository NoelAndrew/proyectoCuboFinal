
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>

//pines del cubo
int levels[4] = {26, 25, 33, 32};                                               //niveles del cubo
int columnas[16] = {22, 1, 3, 21, 19, 18, 5, 17, 16, 4, 2, 15, 27, 14, 12, 13}; //columnas verticales del cubo
int tim = 250;

//Parámetros de conexión a internet
const char *ssid = "INFINITUM9D3D_2.4";
const char *password = "banderasluis3026";

//Datos del broker (Luis)
const char *mqtt_server = "driver.cloudmqtt.com";
const int mqtt_port = 18625;
const char *mqtt_user = "bmtqnhmu";
const char *mqtt_pass = "KHw4Itds6hTj";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;
long espera = 0;

//Conexión al wifi
void setup_wifi()
{
  Serial.println();
  Serial.println("Conectando a...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("Conexion exitosa");
  Serial.println("Mi dirección ip es -> ");
  Serial.println(WiFi.localIP());
}

void encenderTodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], 1);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(levels[i], 0);
  }
}

void apagarTodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columnas[i], 0);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(levels[i], 1);
  }
}

void parpadeartodo()
{
  int x = 60;
  for (int i = 0; i < 300; i += 5)
  {
    encenderTodo();
    delay(x);
    apagarTodo();
    delay(x);
  }
}

void parpadeoRandom()
{
  apagarTodo();
  int x = 150;
  for (int i = 0; i < 100; i += 5)
  {
    int nivelRandom = random(0, 4);
    int columnaRandom = random(0, 16);

    digitalWrite(levels[nivelRandom], 1);
    digitalWrite(columnas[columnaRandom], 0);
    delay(x);
    digitalWrite(levels[nivelRandom], 0);
    digitalWrite(columnas[columnaRandom], 1);
    delay(x);
  }
}

void lluviaRandom()
{
  apagarTodo();
  int x = 100;
  for (int i = 0; i < 100; i += 2)
  {
    int columnaRandom = random(0, 16);
    digitalWrite(columnas[columnaRandom], 0);
    digitalWrite(levels[3], 1);
    delay(x + 50);
    digitalWrite(levels[3], 0);
    digitalWrite(levels[2], 1);
    delay(x);
    digitalWrite(levels[2], 0);
    digitalWrite(levels[1], 1);
    delay(x);
    digitalWrite(levels[1], 0);
    digitalWrite(levels[0], 1);
    delay(x + 50);
    digitalWrite(levels[0], 0);
    digitalWrite(columnas[columnaRandom], 1);
  }
}

void espiral()
{
  int x = 60;
  for(int i = 0; i<6; i++)
  {
    //Espiral hacia afuera, sentido del reloj
    digitalWrite(columnas[0], 1);
    delay(x);
    digitalWrite(columnas[1], 1);
    delay(x);
    digitalWrite(columnas[2], 1);
    delay(x);
    digitalWrite(columnas[3], 1);
    delay(x);
    digitalWrite(columnas[7], 1);
    delay(x);
    digitalWrite(columnas[11], 1);
    delay(x);
    digitalWrite(columnas[15], 1);
    delay(x);
    digitalWrite(columnas[14], 1);
    delay(x);
    digitalWrite(columnas[13], 1);
    delay(x);
    digitalWrite(columnas[12], 1);
    delay(x);
    digitalWrite(columnas[8], 1);
    delay(x);
    digitalWrite(columnas[4], 1);
    delay(x);
    digitalWrite(columnas[5], 1);
    delay(x);
    digitalWrite(columnas[6], 1);
    delay(x);
    digitalWrite(columnas[10], 1);
    delay(x);
    digitalWrite(columnas[9], 1);
    delay(x);
    //Espiral en sentido contrario
    digitalWrite(columnas[9], 0);
    delay(x);
    digitalWrite(columnas[10], 0);
    delay(x);
    digitalWrite(columnas[6], 0);
    delay(x);
    digitalWrite(columnas[5], 0);
    delay(x);
    digitalWrite(columnas[4], 0);
    delay(x);
    digitalWrite(columnas[8], 0);
    delay(x);
    digitalWrite(columnas[12], 0);
    delay(x);
    digitalWrite(columnas[13], 0);
    delay(x);
    digitalWrite(columnas[14], 0);
    delay(x);
    digitalWrite(columnas[15], 0);
    delay(x);
    digitalWrite(columnas[11], 0);
    delay(x);
    digitalWrite(columnas[7], 0);
    delay(x);
    digitalWrite(columnas[3], 0);
    delay(x);
    digitalWrite(columnas[2], 0);
    delay(x);
    digitalWrite(columnas[1], 0);
    delay(x);
    digitalWrite(columnas[0], 0);
    delay(x);
    //Espiral hacia afuera sentido contrario
    digitalWrite(columnas[0], 1);
    delay(x);
    digitalWrite(columnas[4], 1);
    delay(x);
    digitalWrite(columnas[8], 1);
    delay(x);
    digitalWrite(columnas[12], 1);
    delay(x);
    digitalWrite(columnas[13], 1);
    delay(x);
    digitalWrite(columnas[14], 1);
    delay(x);
    digitalWrite(columnas[15], 1);
    delay(x);
    digitalWrite(columnas[11], 1);
    delay(x);
    digitalWrite(columnas[7], 1);
    delay(x);
    digitalWrite(columnas[3], 1);
    delay(x);
    digitalWrite(columnas[2], 1);
    delay(x);
    digitalWrite(columnas[1], 1);
    delay(x);
    digitalWrite(columnas[5], 1);
    delay(x);
    digitalWrite(columnas[9], 1);
    delay(x);
    digitalWrite(columnas[10], 1);
    delay(x);
    digitalWrite(columnas[6], 1);
    delay(x);
    //Espiral hacia adentro sentido contrario
    digitalWrite(columnas[6], 0);
    delay(x);
    digitalWrite(columnas[10], 0);
    delay(x);
    digitalWrite(columnas[9], 0);
    delay(x);
    digitalWrite(columnas[5], 0);
    delay(x);
    digitalWrite(columnas[1], 0);
    delay(x);
    digitalWrite(columnas[2], 0);
    delay(x);
    digitalWrite(columnas[3], 0);
    delay(x);
    digitalWrite(columnas[7], 0);
    delay(x);
    digitalWrite(columnas[11], 0);
    delay(x);
    digitalWrite(columnas[15], 0);
    delay(x);
    digitalWrite(columnas[14], 0);
    delay(x);
    digitalWrite(columnas[13], 0);
    delay(x);
    digitalWrite(columnas[12], 0);
    delay(x);
    digitalWrite(columnas[8], 0);
    delay(x);
    digitalWrite(columnas[4], 0);
    delay(x);
    digitalWrite(columnas[0], 0);
    delay(x);
  }
  encenderTodo();
}

void pisos(){
  int dlay = 60;
  for(int k = 0; k<5; k++){
    for (int i=0; i<4; i++){
      apagarTodo();
      for (int j = 0; j < 16; j++)
      {
        digitalWrite(columnas[j], 1);
      }
      digitalWrite(levels[i],0);  
      delay(dlay);
    }
    dlay += 60;
    encenderTodo();
  }
}
//Mensajes recibidos
void callback(char *topic, byte *payload, unsigned int lenght)
{
  Serial.print("Mensaje recibido bajo el topico -> ");
  Serial.print(topic);
  Serial.print("\n");

  for (int i = 0; i < lenght; i++)
  {
    Serial.print((char)payload[i]);
  }

  //Apagamos todo
  if ((char)payload[0] == '0')
  {
    apagarTodo();
  }

  //Encendemos todos
  else if ((char)payload[0] == '1')
  {
    encenderTodo();
  }

  //Parpadeo
  else if ((char)payload[0] == '2')
  {
    parpadeartodo();
  }

  //Parpadeo Random
  else if ((char)payload[0] == '3')
  {
    parpadeoRandom();
  }

  //Lluvia de leds
  else if ((char)payload[0] == '4')
  {
    lluviaRandom();
  }

  //Espiral
  else if ((char)payload[0] == '5')
  {
    espiral();
  }

  //Pisos
   else if ((char)payload[0] == '6')
  {
    pisos();
  }
  Serial.println();
}

//Reconexión del broker
void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando Conexión MQTT");
    String clientId = "";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conexion a MQTT exitosa!!!");
      client.publish("salida_luis", "primer mensaje");
      client.subscribe("entrada_luis");
    }
    else
    {
      Serial.println("Fallo Conexion");
      Serial.print(client.state());
      Serial.print("Se intentara de nuevo en 5 segundos");
      delay(5000);
    }
  }
}
void setup()
{

  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  for (int i = 0; i < 16; i++)
  {
    pinMode(columnas[i], OUTPUT); //Definimos las columnas como salida
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(levels[i], OUTPUT); //Definimos los niveles como salida
  }
}

void loop()
{

  //VERIFICAMOS SI SIGUE CONECTADO EL BROKER
  if (client.connected() == false)
  {
    reconnect();
  }

  client.loop();

  if (millis() - lastMsg > 2000)
  {
    lastMsg = millis();
    value++;
    String mes = "Valor ->" + String(value);
    mes.toCharArray(msg, 50);
    client.publish("Salida", msg);
    Serial.println("Mensaje enviado ->" + String(value));
  }
}