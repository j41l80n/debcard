#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 


void setup() {
  // inicia a serial
  Serial.begin(9600);
  //inicia comunicacao do barramento SPI
  SPI.begin();
  //escreve na tela
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() {
  // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  // testa se o cartao1 foi lido
  if (conteudo.substring(1) == "D8 4B 12 22")
  {
    Serial.println("Cartao1 - Acesso liberado !");
    Serial.println();
    delay(3000);
  }

  // testa se o cartao2 foi lido
  if (conteudo.substring(1) == "87 4B DC 8A")
  {
    Serial.println("Cartao2 - Acesso negado !!");
    Serial.println();
  }
  delay(1000);

  // dump debug info about the card. PICC_HaltA() is automatically called.
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
