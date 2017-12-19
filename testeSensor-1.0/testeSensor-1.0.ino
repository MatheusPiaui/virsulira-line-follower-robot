
const int SENSOR1 = A1, SENSOR2 = A2, SENSOR3 = A3, SENSOR4 = A4, SENSOR5 = A5, SENSOR6 = A6;

int esq, esqP, esqT;
int dir, dirP, dirT;

//variaveis para reconhecer linha
//abaixo desses valores está fora da linha
int esqPLi = 0, esqLi = 0, dirLi = 0, dirPLi = 0;

//deixar o robo em com todos os sensores em cima da linha por 5 segundos;
void calibrar(){
  
   esqP = analogRead(SENSOR2);
   esq = analogRead(SENSOR3);
   dir = analogRead(SENSOR4);
   dirP = analogRead(SENSOR5);

   int cont=0;
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR2);
       esq = analogRead(SENSOR3);
       dir = analogRead(SENSOR4);
       dirP = analogRead(SENSOR5);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       delay(1000);
   }   
   esqPLi /= 10;
   esqLi /= 10;
   dirLi /= 10;
   dirPLi /= 10; 
   
}

void setup() {
//    calibrar();
    
    Serial.begin(9600); //Inicia a comunicação serial
  
    // put your setup code here, to run once:
    Serial.print("Esquerda Plus Linha: ");
    Serial.println(esqPLi);
    
    Serial.print("Esquerda Linha:        ");
    Serial.println(esqLi);
    
    Serial.print("Direita Linha :        ");
    Serial.println(dirLi);
    
    Serial.print("Direita Plus Linha : ");
    Serial.println(dirPLi);

    
}

void loop() {
  
  
  // put your main code here, to run repeatedly:  
  esqT = analogRead(SENSOR1);
  esqP = analogRead(SENSOR2);
  esq = analogRead(SENSOR3);
  dir = analogRead(SENSOR4);
  dirP = analogRead(SENSOR5);
  dirT = analogRead(SENSOR6);
  
  delay(1000);
//   
  Serial.print("Esquerda traz : ");
  Serial.println(esqT);

  Serial.print("Esquerda Plus : ");
  Serial.println(esqP);
  
  Serial.print("Esquerda :        ");
  Serial.println(esq);
  
  Serial.print("Direita  :        ");
  Serial.println(dir);
  
  Serial.print("Direita Plus  : ");
  Serial.println(dirP);

  Serial.print("Direita traz  : ");
  Serial.println(dirT);
  
  
  Serial.println("  ...  ");
  Serial.println("  PAUSA  ");
  Serial.println("  ...  ");
  delay(1000);
  

}
