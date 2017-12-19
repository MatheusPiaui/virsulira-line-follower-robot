
const int SENSOR0 = A0, SENSOR1 = A1, SENSOR2 = A2, SENSOR3 = A3, SENSOR4 = A4, SENSOR5 = A5, SENSOR6 = A6, SENSOR7 = A7;

int esq, esqP, esqT;
int dir, dirP, dirT;
int par1, par2, par3;




void leitura(){
   esqP = analogRead(SENSOR1);
   esq = analogRead(SENSOR2);
   dir = analogRead(SENSOR3);
   dirP = analogRead(SENSOR4);
}

//variaveis para reconhecer linha
//abaixo desses valores está fora da linha
int esqPLi = 0, esqLi = 0, dirLi = 0, dirPLi = 0;
int par1Li = 0, par2Li = 0, par3Li = 0;

//5 segundos no banco e 5 no preto
void calibrar(){

   int cont=0;
   delay(1000);
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR1);
       esq = analogRead(SENSOR2);
       dir = analogRead(SENSOR3);
       dirP = analogRead(SENSOR4);
       par1 = analogRead(SENSOR5);
       par2 = analogRead(SENSOR6);
       par3 = analogRead(SENSOR7);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       par1Li += par1;
       par2Li += par2;
       par3Li += par3;
       delay(100);
   }  
   delay(3000);
   delay(1000);
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR1);
       esq = analogRead(SENSOR2);
       dir = analogRead(SENSOR3);
       dirP = analogRead(SENSOR4);
       par1 = analogRead(SENSOR5);
       par2 = analogRead(SENSOR6);
       par3 = analogRead(SENSOR7);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       par1Li += par1;
       par2Li += par2;
       par3Li += par3;
       delay(100);
   }
   delay(3000);
   esqPLi /= 20;
   esqLi /= 20;
   dirLi /= 20;
   dirPLi /= 20;
   par1Li /= 20;
   par2Li /= 20;
   par3Li /= 20;   
}

void setup() {
//    calibrar();

    delay(5000);
    
    Serial.begin(9600); //Inicia a comunicação serial
  
//    // put your setup code here, to run once:
//    Serial.print("Esquerda Plus Linha: ");
//    Serial.println(esqPLi);
//    
//    Serial.print("Esquerda Linha:        ");
//    Serial.println(esqLi);
//    
//    Serial.print("Direita Linha :        ");
//    Serial.println(dirLi);
//    
//    Serial.print("Direita Plus Linha : ");
//    Serial.println(dirPLi);
//
//    Serial.print("Partida 1 : ");
//    Serial.println(par1Li);
//
//    Serial.print("Partida 2 : ");
//    Serial.println(par2Li);
//
//    Serial.print("Partida 3 : ");
//    Serial.println(par3Li);
//    
}

void loop() {
  
  
  // put your main code here, to run repeatedly:  
//  esqT = analogRead(SENSOR1);
//  esqP = analogRead(SENSOR2);
//  esq = analogRead(SENSOR3);
//  dir = analogRead(SENSOR4);
//  dirP = analogRead(SENSOR5);
//  dirT = analogRead(SENSOR6);
//  
//  delay(1000);
//   
//  Serial.print("Esquerda traz : ");
//  Serial.println(esqT);
//
//  Serial.print("Esquerda Plus : ");
//  Serial.println(esqP);
//  
//  Serial.print("Esquerda :        ");
//  Serial.println(esq);
//  
//  Serial.print("Direita  :        ");
//  Serial.println(dir);
//  
//  Serial.print("Direita Plus  : ");
//  Serial.println(dirP);
//
//  Serial.print("Direita traz  : ");
//  Serial.println(dirT);
  Serial.print("sensor 0 : ");
  Serial.println(analogRead(SENSOR0));

  Serial.print("sensor 1 : ");
  Serial.println(analogRead(SENSOR1));

  Serial.print("sensor 2 : ");
  Serial.println(analogRead(SENSOR2));
  
  Serial.print("sensor 3 : ");
  Serial.println(analogRead(SENSOR3));
  
  Serial.print("sensor 4 : ");
  Serial.println(analogRead(SENSOR4));
  
  Serial.print("sensor 5 : ");
  Serial.println(analogRead(SENSOR5));

  Serial.print("sensor 6 : ");
  Serial.println(analogRead(SENSOR6));

  Serial.print("sensor 7 : ");
  Serial.println(analogRead(SENSOR7));
  
  Serial.println("  ...  ");
  Serial.println("  PAUSA  ");
  Serial.println("  ...  ");
  delay(1000);
  

}
