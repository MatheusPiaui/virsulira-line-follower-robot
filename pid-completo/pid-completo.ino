//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6} ;
int motorDir[2] = {4,5};
int velocidade = 120;
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
float kp = 40, ki = 0, kd = 110;
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


void setup() {
    esqP = analogRead(SENSOR2);
    esq = analogRead(SENSOR3);
    dir = analogRead(SENSOR4);
    dirP = analogRead(SENSOR5);
    //Define os pinos como saida
    //motorEsq
    pinMode(motorEsq[0], OUTPUT);
    pinMode(motorEsq[1], OUTPUT);
    //motorDir
    pinMode(motorDir[0], OUTPUT);
    pinMode(motorDir[1], OUTPUT);

}

void loop() {
  // leitura 
    esqP = analogRead(SENSOR2);
    esq = analogRead(SENSOR3);
    dir = analogRead(SENSOR4);
    dirP = analogRead(SENSOR5);

  
  // Definir leitura
  if(esqP < 483.5){
    leitura[0] = 0;
  }else{
    leitura[0] = 1;
  }
  
  if(esq < 538){
    leitura[1] = 0;
  }else{
    leitura[1] = 1;
  }
  
  if(dir < 470.7){
    leitura[2] = 0;
  }else{
    leitura[2] = 1;
  }
  
  if(dirP < 599){
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
