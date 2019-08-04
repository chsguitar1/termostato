#include <Thermistor.h>

//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>


//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(8,9,4,5,6,7);
//const int LM35 = A0; // Define o pino que lera a saída do LM35
const int porta_rele1 = 10;
int temperatura;
int tempFermentacao;
const int pinoBotaoConfig = 11;
const int pinoMais = 10;
const int pinoMenos = 12;
boolean medindo = true;
boolean liga = false;
boolean ligado = false;
int tempoLigado;

 
Thermistor temp(2);
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(pinoBotaoConfig, INPUT_PULLUP);
  pinMode(pinoMais, INPUT_PULLUP);
  pinMode(pinoMenos, INPUT_PULLUP);
 pinMode(porta_rele1, OUTPUT);
  Serial.begin(9600);
 // digitalWrite(porta_rele1,HIGH);

}

void loop()
{
  //Limpa a tela
  if(digitalRead(pinoBotaoConfig) == LOW && medindo == true){ 
    medindo = false;

  }
  else if(!medindo && digitalRead(pinoBotaoConfig) == LOW) {

    medindo = true;
  }

  if(!medindo){
    if(digitalRead(pinoMais) == LOW){
      tempFermentacao = tempFermentacao + 1;
    }
    if(digitalRead(pinoMenos) == LOW){
      tempFermentacao = tempFermentacao - 1;
    }
  }
  medeTemperatura();
  Serial.println(temperatura);

  if(temperatura  < tempFermentacao + 2){
    liga = false;
  }

  if(temperatura  > tempFermentacao +2 ){
    liga = true;
  }


  if(liga && !ligado){
    ligado = true;

    digitalWrite(porta_rele1,LOW);


  }
  else if(!liga && ligado && tempoLigado == 60000 ){
    ligado == false;
    digitalWrite(porta_rele1,HIGH);

  }
  if(ligado){
    tempoLigado = tempoLigado +1000;
  }


  delay(2000);
}

void medeTemperatura(){
  if(medindo){
    lcd.clear();
   // temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
   temperatura = temp.getTemp();

    if(ligado){
  //    temperatura = temperatura - 4;
 // Serial.println(temperatura);

    }else{
  //  temperatura = temperatura + 4;
    }
    lcd.setCursor(0,0);
    lcd.print("Temp.");
    lcd.setCursor(6,0);
    lcd.print(temperatura);
  //  lcd.print((char) 223);
    lcd.setCursor(0,1);
    lcd.print("T. Ferm.");
    lcd.setCursor(9,1);
    lcd.print(tempFermentacao);
    //lcd.print((char) 223);

  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T. Fermentacao");
    lcd.setCursor(0,1);
    lcd.print(tempFermentacao);
    //lcd.print((char) 223);


  }
}





