
#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 

#define TOPICO_SUBSCRIBE "MQTTLucasOBJINTEnvia"     
#define TOPICO_PUBLISH   "MQTTLucasOBJINTpRecebe"    
#define ID_MQTT  "lucasrossitrabson"
#define pinoAnalog A0 
#define pinoRele 4 
#define pino5V 5 
 
int ValAnalogIn; 

// WIFI
const char* SSID = "ssid"; 
const char* PASSWORD = "senha"; 
  
// MQTT
const char* BROKER_MQTT = "mqtt.eclipse.org"; 
int BROKER_PORT = 1883; 
 
 

WiFiClient espClient; 
PubSubClient MQTT(espClient); 
char EstadoSaida = '1'; 


void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void VerificaConexoesWiFIEMQTT(void);
 

void setup() {

pinMode(pinoRele, OUTPUT); 
pinMode(pino5V, OUTPUT); 
digitalWrite(pino5V, HIGH); 
initSerial();
initWiFi();
initMQTT();
}

void initSerial() 
{
    Serial.begin(9600);
}
 

void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}
  

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   

}
  

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}
  

void reconectWiFi() 
{

    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); 
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}
 

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); 
     
     reconectWiFi(); 
}
 

void EnviaEstadoOutputMQTT(void)
{
    if (EstadoSaida == '1')
      MQTT.publish(TOPICO_PUBLISH, "N");
 
    if (EstadoSaida == '2')
      MQTT.publish(TOPICO_PUBLISH, "I");

    if (EstadoSaida == '3')
      MQTT.publish(TOPICO_PUBLISH, "A");
      
    Serial.println("- Estado da planta enviado ao broker!");
    delay(1000);
}
 


void loop() {

    VerificaConexoesWiFIEMQTT();
 

    EnviaEstadoOutputMQTT();
 
 
    MQTT.loop();
ValAnalogIn = analogRead(pinoAnalog); 
int Porcento = map(ValAnalogIn, 1023, 0, 0, 100); 
 
Serial.print(Porcento); 
Serial.println("%"); 
 
if (Porcento <= 30) { 
EstadoSaida = '2';
Serial.println("estadp saida == 2 ...");
Serial.println("Irrigando a planta ..."); 
digitalWrite(pinoRele, LOW); 

}
 
else { // Se não ...
digitalWrite(pinoRele, HIGH); 
if (EstadoSaida == '2'){
  EstadoSaida = '3';
}
}

delay (1000); 

}
