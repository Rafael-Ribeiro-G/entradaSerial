#include <Arduino.h>

void leituraBloqueante();
void leituraNaoBloqueante();
void processaFrase(char* texto);
int lerProximoNumero(char*& cursor);
void aplicarCor();

int vermelho = 0;
int verde = 0;
int azul = 0;
int branco = 0;
int brilho = 0;


void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(2000); 
  //* readStringUntil espera no máximo por caractere esse tempo em (ms) pelo '\n'
  //* O padrão é 1000ms

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

//* VERMELHO
//* VERDE
//* AZUL
//* BRANCO 
//* DESLIGA
//* RGB r g b (ex.: RGB 200 125 98)
//* BRILHO n (0 A 100%)
void processaFrase(char* texto)
{
  Serial.printf("Recebido: [%s]\n\r", texto);

  //* O ponteiro indica o endereço da variável
  char* comando = texto;
  char* parametro = NULL; //* NULL ---> '\0'

  char* espaco = strchr(texto, ' ');
  if(espaco != NULL) //* Se ele encontrou o espaço...
  {
    parametro = espaco + 1;
    *espaco = '\0';
  }

  //* strcmp ---> Compara a ordem léxica das palavras
  //* strcasecmp ---> Compara a ordem léxica das palavras mas ignora se foir maiúscula ou minúscula 
  if(strcasecmp(comando, "VERMELHO") == 0)
  {
    vermelho = 255;
    verde = 0;
    azul = 0;
    brilho = 100;
  }

  else if(strcasecmp(comando, "VERDE") == 0)
  {
    vermelho = 0;
    verde = 255;
    azul = 0;
    brilho = 100;
  }

  else if(strcasecmp(comando, "AZUL") == 0)
  {
    vermelho = 0;
    verde = 0;
    azul = 255;
    brilho = 100;
  }

  else if(strcasecmp(comando, "BRANCO") == 0)
  {
    vermelho = 255;
    verde = 255;
    azul = 255;
    brilho = 100;
  }

  else if(strcasecmp(comando, "DESLIGA") == 0)
  {
    vermelho = 0;
    verde = 0;
    azul = 0;
  }

  else if(strcasecmp(comando, "RGB") == 0)
  {
    if(parametro == NULL)
    {
      Serial.println("Você é burro? É pra usar o comando: RGB r g b (0 a 255)");
      return;
    }
  
    char* cursor = parametro;

    vermelho = constrain(lerProximoNumero(cursor), 0, 255); //* Limita o valor já convertido para int de 0 a 255
    verde = constrain(lerProximoNumero(cursor), 0, 255); //* Limita o valor já convertido para int de 0 a 255
    azul = constrain(lerProximoNumero(cursor), 0, 255); //* Limita o valor já convertido para int de 0 a 255
  }

  else if(strcasecmp(comando, "BRILHO") == 0)
  {
    if(parametro == NULL)
    {
      Serial.println("Use o comando: BRILHO n (0 a 100)");
      return;
    }

    brilho = constrain(atoi(parametro), 0, 100);
  }

  else
  {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Comando: [%s] não existe\n\r", comando);
    Serial.print(buffer);
    return;
  }
  //if(strcmp(texto, "ola") == 0)
    //Serial.println("Olá para você também!");
  aplicarCor();
}

void aplicarCor()
{
  int r = vermelho * brilho / 100;
  int g = verde * brilho / 100;
  int b = azul * brilho / 100;

  //* neopixelWrite ---> Controla o LED RGB
  neopixelWrite(PIN_RGB_LED, r, g, b);

  char bufferMensagem[80];

  snprintf(bufferMensagem, sizeof(bufferMensagem), "Cor: R = [%3d] | G = [%3d] | B = [%3d] | Brilho: [%3d %%] | HEX: [#%02X#%02X#%02X]", vermelho, verde, azul, brilho, r, g, b);
  Serial.println(bufferMensagem);
}

int lerProximoNumero(char*& cursor)
{
  int valor = atoi(cursor);
  char* espaco = strchr(cursor, ' ');
  cursor = (espaco != NULL) ? espaco + 1 : NULL;
  return valor;
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
