#include <Arduino.h>

void leituraBloqueante();
void leituraNaoBloqueante();

void setup() 
{
  Serial.begin(115200);
  Serial.setTimeout(2000); 
  //* readStringUntil espera no máximo por caractere esse tempo em (ms) pelo '\n'
  //* O padrão é 1000ms

  Serial.println();
  Serial.println("Digite o seu nome e pressione ENTER: ");
}

void loop() 
{
  
}

void leituraNaoBloqueante()
{
  const int tamanhoMaximo = 50; //* Tamanho do vetor (incluir '/0')
  char linha[tamanhoMaximo];
  int position = 0;

  while(Serial.available() > 0)
  {
    char c = Serial.read();
  }
}

void leituraBloqueante()
{
  //* Vê se tem algo a ser recebido na Serial 
  //* available() diz quantos bytes já chegaram e estão esperando leitura
  if(Serial.available() > 0)
  {
    //* Serial.readStringUntil ---> Lê até achar o caracter
    String texto = Serial.readStringUntil('\n');

    //* trim() remove espaços, '\r', '\t', '\n' que alguns terminais enviam
    texto.trim();

    //* c_str ---> converte para String
    if(texto.length() == 0) return;
    Serial.printf("Seu nome é: %s\n\r", texto.c_str());
    Serial.printf("Quantidade de caracteres: %d\n\r", texto.length());

    Serial.printf("Primeira letra: %c\n\r", texto.charAt(0));
    Serial.printf("Última letra: %c\n\r", texto[texto.length() - 1]);

    String maiusculo = texto;
    maiusculo.toUpperCase();
    Serial.printf("Em maiúsculas: %s\n\r", maiusculo.c_str());

    if(maiusculo == "RAFAEL")
    {
      Serial.println("Este é o seu nome correto");
    }
  }
}
