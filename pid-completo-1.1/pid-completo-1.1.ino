//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6};
int motorDir[2] = {4,5};
int velocidade = 60;
//setando portas dos sensores
const int SENSOR1 = 1, SENSOR2 = 2, SENSOR3 = 3, SENSOR4 = 4, SENSOR5 = 5, SENSOR6 = 6;
int esq, esqP;
int dir, dirP;
////

// Definição
int corte = 150;



////
//int kp = 20; // constrante proporcional
int erro = 0;
int leitura[4] = {0,0,0,0};
// Possibilidades
//[0,0,0,1]1 //  3
//[0,0,1,1]2 //  2
//[0,0,1,0]3 //  1
//[0,1,1,0]4 //  0  centro
//[0,1,0,0]5 // -1
//[1,1,0,0]6 // -2
//[1,0,0,0]7 // -3

//pid
float P = 0,I = 0,D = 0;
float kp = 20, ki = 0, kd = 0;
float PIDvalue = 0;
int previousError;

void calculatePID ()
{
   P = erro;
   I = I + erro;
   D = erro - previousError;
   PIDvalue = (kp * P) + (ki * I) + (kd * D);
   previousError = erro;
}

//variaveis para reconhecer linha
//abaixo desses valores está fora da linha
int esqPLi = 0, esqLi = 0, dirLi = 0, dirPLi = 0;

//5 segundos no banco e 5 no preto
void calibrar(){

   esqP = analogRead(SENSOR1);
   esq = analogRead(SENSOR2);
   dir = analogRead(SENSOR3);
   dirP = analogRead(SENSOR4);

   int cont=0;
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR1);
       esq = analogRead(SENSOR2);
       dir = analogRead(SENSOR3);
       dirP = analogRead(SENSOR4);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       delay(100);
   }  
   delay(7000);
   for(cont=0; cont < 10; cont++){
       esqP = analogRead(SENSOR1);
       esq = analogRead(SENSOR2);
       dir = analogRead(SENSOR3);
       dirP = analogRead(SENSOR4);
       
       esqPLi += esqP;
       esqLi += esq;
       dirLi += dir;
       dirPLi += dirP;
       delay(100);
   } 
   esqPLi /= 20;
   esqLi /= 20;
   dirLi /= 20;
   dirPLi /= 20; 
   delay(2000);
}

void setup() {
    esqP = analogRead(SENSOR1);
    esq = analogRead(SENSOR2);
    dir = analogRead(SENSOR3);
    dirP = analogRead(SENSOR4);
    //Define os pinos como saida
    //motorEsq
    pinMode(motorEsq[0], OUTPUT);
    pinMode(motorEsq[1], OUTPUT);
    //motorDir
    pinMode(motorDir[0], OUTPUT);
    pinMode(motorDir[1], OUTPUT);

    calibrar();
    delay(2000);
}

void loop() {
  // leitura 
    esqP = analogRead(SENSOR1);
    esq = analogRead(SENSOR2);
    dir = analogRead(SENSOR3);
    dirP = analogRead(SENSOR4);

  
  // Definir leitura
  if(esqP < esqPLi){
    leitura[0] = 0;
  }else{
    leitura[0] = 1;
  }
  
  if(esq < esqLi){
    leitura[1] = 0;
  }else{
    leitura[1] = 1;
  }
  
  if(dir < dirLi){
    leitura[2] = 0;
  }else{
    leitura[2] = 1;
  }
  
  if(dirP < dirPLi){
    leitura[3] = 0;
  }else{
    leitura[3] = 1;
  }   


  
  // logica para gerar os erros
  if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 0)&&(leitura[3] == 1))//1
    erro = 3;
  if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 1)&&(leitura[3] == 1))//2
    erro = 2;
  if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 1)&&(leitura[3] == 0))//3
    erro = 1;
  if((leitura[0] == 0)&&(leitura[1] == 1)&&(leitura[2] == 1)&&(leitura[3] == 0))//4
    erro = 0;
  if((leitura[0] == 0)&&(leitura[1] == 1)&&(leitura[2] == 0)&&(leitura[3] == 0))//5
    erro = -1;
  if((leitura[0] == 1)&&(leitura[1] == 1)&&(leitura[2] == 0)&&(leitura[3] == 0))//6
    erro = -2;
  if((leitura[0] == 1)&&(leitura[1] == 0)&&(leitura[2] == 0)&&(leitura[3] == 0))//7
    erro = -3;

  //velocidade dos motores (kp * erro)

  //pid
  calculatePID();
  //ir para frente
  motor(velocidade + PIDvalue,motorEsq[0],motorEsq[1]);
  motor(velocidade - PIDvalue,motorDir[0],motorDir[1]);

}






//FUNÇÕES DO MOTOR
///
void motor(int vel, int in1,int inp){
    //Gira o Motor no sentido horario
    digitalWrite(in1, LOW);
    analogWrite(inp, vel);
}

void pararMotor(int in1,int in2){
   //Para o motor
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
}
