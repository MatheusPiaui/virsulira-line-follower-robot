//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6} ;
int motorDir[2] = {4,5};

//setando portas dos sensores
const int SENSOR1 = 7, SENSOR2 = 6, SENSOR3 = 5, SENSOR4 = 4, SENSOR5 = 3, SENSOR6 = 2;
int esq, esqP;
int dir, dirP;
//variaveis para reconhecer linha
//abaixo desses valores está fora da linha
int esqPLi = 0, esqLi = 0, dirLi = 0, dirPLi = 0;
int corte = 200;


// Parametros do robo
const int velocidade = 150;


//deixar o robo em com todos os sensores em cima da linha por 5 segundos;
void calibrar(){
   esqP = analogRead(SENSOR2);
   esq = analogRead(SENSOR3);
   dir = analogRead(SENSOR4);
   dirP = analogRead(SENSOR5);

   int cont=0;
   delay(1000);
   
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR2);
       esq = analogRead(SENSOR3);
       dir = analogRead(SENSOR4);
       dirP = analogRead(SENSOR5);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       delay(100);
   }
   
   delay(2000);
   
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR2);
       esq = analogRead(SENSOR3);
       dir = analogRead(SENSOR4);
       dirP = analogRead(SENSOR5);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       delay(100);
   }   
   
   delay(3000);
   
   esqPLi /= 20;
   esqLi /= 20;
   dirLi /= 20;
   dirPLi /= 20; 
   
}

void setup() {
//    calibrar();

    //Define os pinos como saida
    //motorEsq
    pinMode(motorEsq[0], OUTPUT);
    pinMode(motorEsq[1], OUTPUT);
    //motorDir
    pinMode(motorDir[0], OUTPUT);
    pinMode(motorDir[1], OUTPUT);
    
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

    // 5 segundos para calibrar e mais 5 segundos para colocar no ponto de partida!
    delay(5000);
    
}

void loop() {
    esqP = analogRead(SENSOR2);
    esq = analogRead(SENSOR3);
    dir = analogRead(SENSOR4);
    dirP = analogRead(SENSOR5);
    
//    teste
//        direita(velocidade);
//        delay(2000);
//        para();
//        delay(2000);   
//        esquerda(velocidade); 
//        delay(2000); 
//        para();
//        delay(2000);

//    // Se "Esq Plus" estiver na linha
//    if(esqP > esqPLi){
//        //  Vira para a esquerda
////        esquerda(velocidade); 
//          direita(velocidade); 
//     
//    }else{
//        //  Se "Dir Plus" estiver na linha
//        if(dirP > dirPLi){
//            //  Vira para a direita
////            direita(velocidade);
//              esquerda(velocidade); 
//        }else{
//            //  Se "Esq Plus" e "Dir Plus" estiverem fora da linha
//            //  Avança
//            avanca(velocidade);
//        }
//    }
//  if((esq > esqLi)&&(dir > dirLi)){
//      avanca(velocidade);
//  }else{
//    if((esq < esqLi)&&(dir > dirLi)){
////        esquerda(velocidade);
//        direita(velocidade);
//    }else{
//      if((esq > esqLi)&&(dir < dirLi)){
//            esquerda(velocidade);
////            direita(velocidade);
//      }
//    }
//  }
    if((esq > corte) && (dir > corte)){
        avanca(velocidade);
    }
 
    if((esq < corte)&&(dir > corte)){
//      esquerda(velocidade);
        direita(velocidade+50);
    }
    
    if((esq > corte)&&(dir < corte)){
          esquerda(velocidade+50);
//        direita(velocidade);
    }
//
//    if((esqP < corte) && (dirP > corte)){
//      direita(velocidade);      
//    }
//    
//    if((esqP > corte) && (dirP < corte)){
//      esquerda(velocidade);
//    }
      
  
  
  
  

}

// FUNÇÕES DO ROBO
//
void avanca(int vel){
  //ir para frente
  motor(vel,motorEsq[0],motorEsq[1],false);
  motor(vel,motorDir[0],motorDir[1],true);
}
void volta(int vel){
  //ir para traz
  motor(vel,motorEsq[0],motorEsq[1],true);
  motor(vel,motorDir[0],motorDir[1],false);
}
void para(){
  //para
  pararMotor(motorEsq[0],motorEsq[1]);
  pararMotor(motorDir[0],motorDir[1]);
}
void direita(int vel){  
//  motor(vel,motorEsq[0],motorEsq[1],false);  
//  motor(vel,motorDir[0],motorDir[1],false);
  motor(vel,motorEsq[0],motorEsq[1],false);
  pararMotor(motorDir[0],motorDir[1]);
}
void esquerda(int vel){  
//  motor(vel,motorEsq[0],motorEsq[1],true);   
//  motor(vel,motorDir[0],motorDir[1],true);
  pararMotor(motorEsq[0],motorEsq[1]);   
  motor(vel,motorDir[0],motorDir[1],true);
}


//FUNÇÕES DO MOTOR
///
// sentido = 1 // horario
// sentido = 2 // anti-horario
void motor(int vel, int in1,int inp,bool sentido){
  if(sentido){
      //Gira o Motor no sentido horario
      digitalWrite(in1, HIGH);
      analogWrite(inp, vel);
  }else{
      //Gira o Motor no sentido anti-horario
      digitalWrite(in1, LOW);
      analogWrite(inp, -vel);
      
  }   
}

void pararMotor(int in1,int in2){
   //Para o motor
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
}
