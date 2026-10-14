#include <Arduino.h>

void leituraBloqueante();
void leituraNaoBloqueante();
void processaFrase(const char* texto);

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(2000); 
  //* readStringUntil espera no máximo por caractere esse tempo em (ms) pelo '\n'
  //* O padrão é 1000ms

  Serial.println();
  Serial.println("Digite o seu nome e pressione ENTER: ");
}

void loop() 
{
  leituraNaoBloqueante();
}

void leituraNaoBloqueante()
{
  const int tamanhoMaximo = 50; //* Tamanho do vetor (incluir '/0')
  static char frase[tamanhoMaximo];
  static int position = 0;

  while(Serial.available() > 0)
  {
    char c = Serial.read();

    if(c == '\r') continue;
    //* o continue pula o restante do while naquela volta e passa pra leitura
    //* do próximo caractere. O '/r' é lido e simplesmente descartado, sem entrar
    //* no vetor 

    if(c == '\n')
    {
      frase[position] = '\0';
      
      if(position > 0) processaFrase(frase);
      
      position = 0;
    }
    else if (position < tamanhoMaximo - 1)
    {
      frase[position] = c;
      position++;
    }
  }
}

void processaFrase(const char* texto)
{
  Serial.printf("Recebido: [%s]\n\r", texto);

  if(strcmp(texto, "ola") == 0)
    Serial.println("Olá para você também!");
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
