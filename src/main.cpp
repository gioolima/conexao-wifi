#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>




// Protótipo das funções
void conexaoWifi();
void reconexaoWifi();

const char *SSID = "SENAI EDUCACIONAL";
const char *SENHA = "info@134";


const unsigned long tempoConexao = 10000;
const unsigned long tempoReconexao = 5000;

Timezone sp;

void setup() {
  Serial.begin(115200);

  conexaoWifi();
 
  waitForSync();

  sp.setLocation("America/Sao_Paulo");

  String mes;
  String diaSemana;
  int diasFaltam = 365 - sp.dayOfYear();

  Serial.println(sp.dateTime());

  if (sp.month() == 11){
    mes = "Novembro";
  }
  
  if(sp.weekday() == 6){
    diaSemana = "sexta-feira";
  }

  //Serial.println(sp.dateTime("d/m/Y H:i:s"));
  //Serial.println(sp.dateTime("\\Ho\\j\\e \\e l"));
  //Serial.printf("Hoje é %s e faltam %d dias para o ano novo\n", sp.dateTime("d \\d\\e F \\d\\e Y, l,").c_str(), diasFaltam);
  Serial.printf("Hoje é %s de %s de %s, %s, e faltam %d dias para o ano novo\n", sp.dateTime("d").c_str(), mes, sp.dateTime("Y").c_str(), diaSemana, diasFaltam);

  //Serial.println(sp.minute());
  //Serial.println(sp.second());
  //Serial.println(sp.hour());
  //Serial.println(sp.hourFormat12());
  //Serial.println(sp.day());
  //Serial.println(sp.dayOfYear());
  //Serial.println(sp.month());
  //Serial.println(sp.year());
  //Serial.println(sp.isAM());
  //Serial.println(sp.isPM());
}

void loop() {
  reconexaoWifi();
}

void conexaoWifi() {
  
  // Conexao WiFi
  Serial.printf("Conectando ao WiFi: %s", SSID);

  WiFi.begin(SSID, SENHA);

  unsigned long tempoWifi = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - tempoWifi < tempoConexao)
  {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi conectado com sucesso!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Falha ao se conectar");
  }
 
}

void reconexaoWifi() {
  unsigned long tempoAtual = millis();
  unsigned long tempoUltimaConexao = 0;

  if (tempoAtual - tempoUltimaConexao > tempoReconexao)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Conexao WiFi perdida");
      conexaoWifi();
    }

    tempoUltimaConexao = tempoAtual;
    
  }
  
}