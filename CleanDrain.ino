#include <HX711.h>
#include <WiFi.h>
#include <PubSubClient.h>


//defines:
//defines de id mqtt e tópicos para publicação e subscribe denominado TEF(Telemetria e Monitoramento de Equipamentos)
#define TOPICO_SUBSCRIBE    "/TEF/DreamClean8/cmd"        //tópico MQTT de escuta
#define TOPICO_PUBLISH      "/TEF/DreamClean8/attrs"      //tópico MQTT de envio de informações para Broker
#define TOPICO_PUBLISH_2    "/TEF/DreamClean8/attrs/w"    //tópico MQTT de envio de informações para 
#define TOPICO_PUBLISH_3    "/TEF/DreamClean8/attrs/d"

#define ID_MQTT  "fiware_0904" //id mqtt (para identificação de sessão)
const int PINO_DT = 26;
const int PINO_SCK = 25;
#define TRIG_PIN 12
#define ECHO_PIN 14
HX711 escala; //declaracao do objeto ESCALA na classe HX711 da biblioteca
const int FATOR_CALIBRACAO = -45000; //esse valor deve ser alterado para o valor de calibracao obtido com o outro codigo
int D4 = 2;

// WIFI
const char* SSID = "Wokwi-GUEST"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = ""; // Senha da rede WI-FI que deseja se conectar

// MQTT
const char* BROKER_MQTT = "46.17.108.113"; // URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char EstadoSaida = '0'; //variável que armazena o estado atual da saída
char msgBuffer[10]; // Declara a variável msgBuffer para formatação da mensagem MQTT

//Prototypes
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);

void setup()
{
  //inicializações:
  InitOutput();
  initSerial();
  initWiFi();
  initMQTT();
  delay(5000);
  MQTT.publish(TOPICO_PUBLISH, "s|on");
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  escala.begin (PINO_DT, PINO_SCK); //inicializacao e definicao dos pinos DT e SCK dentro do objeto ESCALA
  
  escala.tare(); //zera a escala

  escala.set_scale(FATOR_CALIBRACAO); //ajusta a escala para o fator de calibracao
}

void initSerial()
{
  Serial.begin(115200);
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
  MQTT.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String msg;

  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.print("- Mensagem recebida: ");
  Serial.println(msg);

  if (msg.equals("lamp001@on|"))
  {
    digitalWrite(D4, HIGH);
    EstadoSaida = '1';
  }

  if (msg.equals("lamp001@off|"))
  {
    digitalWrite(D4, LOW);
    EstadoSaida = '0';
  }
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
      Serial.println("Havera nova tentativa de conexao em 2s");
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
  {
    MQTT.publish(TOPICO_PUBLISH, "s|on");
    Serial.println("- Led Ligado");
  }
  if (EstadoSaida == '0')
  {
    MQTT.publish(TOPICO_PUBLISH, "s|off");
    Serial.println("- Led Desligado");
  }
  Serial.println("- Estado do LED onboard enviado ao broker!");
  delay(1000);
}

void InitOutput(void)
{
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  boolean toggle = false;

  for (int i = 0; i <= 10; i++)
  {
    toggle = !toggle;
    digitalWrite(D4, toggle);
    delay(200);
  }
}

void loop()
{
  float duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) * 0.0343;

  // Lê o valor da célula de carga
  float weight = escala.get_units(10); // 10 leituras para suavizar

  snprintf(msgBuffer, sizeof(msgBuffer), "%.2f", distance);
  MQTT.publish(TOPICO_PUBLISH_3, msgBuffer);

  // Publica o valor da célula de carga
  snprintf(msgBuffer, sizeof(msgBuffer), "%.2f", weight);
  MQTT.publish(TOPICO_PUBLISH_2, msgBuffer);

  // Imprime os valores no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Valor da célula de carga: ");
  Serial.print(weight);
  Serial.println(" unidades");

  VerificaConexoesWiFIEMQTT();
  EnviaEstadoOutputMQTT();

  MQTT.loop();
}
