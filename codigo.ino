#include <IRremote.h> // Inclui a biblioteca que permite a decodificação dos dados em infravermelho
#include <Servo.h> // Inclui a biblioteca para a manipulação do servo motor


Servo nossoServo;
int pinoSinal = 1; // Define o pino que estará relacionado ao sensor de infravermelho
int pinoServo = 5; // Define o pino que estará relacionado ao servo motor
IRrecv irrecv(pinoSinal); // Instancia um objeto para manipularmos as funções da biblioteca 
decode_results results;
float teclaPressionada = 0; 
float teclaLigaDesliga = 0; 
int grau = 23; // Quantos graus o servo deve virar. Inicialmente serão 5min. Como o servo gira até 180 graus, e a fritadeira tem 8 marcações de 5min nesse período, 180/8 = 22,5 
int contaGrau = 1; // Quantas vezes o botão já foi pressionado, para saber quantos graus o servo deve girar

void setup() {
  Serial.begin(9600); // Inicia o monitor serial, que será onde os "códigos" ou "pulsos" em binário de cada tecla do controle serão exibidos
  irrecv.enableIRIn(); // Inicia o processo de recebimento de dados
  nossoServo.attach(pinoServo); 

}

void loop() {
  // PARTE 1: DESCOBRIR QUAL O VALOR CORRESPONDENTE A UMA CERTA TECLA (LIGA/DESLIGA)
  
  if (irrecv.decode(&results)) { // Caso algum valor tenha sido passado ao sensor
    Serial.print("A tecla pressionada corresponde a: ");
    Serial.print(results.value); // Imprime na tela o valor em binário correspondente ao pulso que representa a tecla pressionada. 
    teclaPressionada = results.value; // Armazena o "número" que representa a tecla pressionada 
  }
  
  // Já sabendo qual o valor que corresponde à tecla de liga/desliga, executar:
  // PARTE 2: ACIONAR O SERVO MOTOR E LIGAR A FRITADEIRA
  if(teclaPressionada == teclaLigaDesliga){
    nossoServo.write(grau*contaGrau); // Passa ao servo quantos graus ele deve girar
    contaGrau++; 
    delay(30); // um tempinho para o servo se ajustar
  }
  if(contaGrau==8){
    contaGrau = 1;
  }
  irrecv.resume(); // Permite a leitura de um novo valor

}
