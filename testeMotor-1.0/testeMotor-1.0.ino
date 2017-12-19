//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6} ;
int motorDir[2] = {4,5};



void setup() {
  // put your setup code here, to run once:
  //Define os pinos como saida
  //motorEsq
  pinMode(motorEsq[0], OUTPUT);
  pinMode(motorEsq[1], OUTPUT);
  //motorDir
  pinMode(motorDir[0], OUTPUT);
  pinMode(motorDir[1], OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   motor(50,motorEsq[0], motorEsq[1]);
   motor(50,motorDir[0], motorDir[1]);

}


// FUNÇÕES DO ROBO
//
//void avanca(int vel){
//  //ir para frente
//  motor(vel,motorEsq[0],motorEsq[1],false);
//  motor(vel,motorDir[0],motorDir[1],true);
// 
//}
//void volta(int vel){
//  //ir para traz
//  motor(vel,motorEsq[0],motorEsq[1],true);
//  motor(vel,motorDir[0],motorDir[1],false);
//}
//void para(){
//  //para
//  pararMotor(motorEsq[0],motorEsq[1]);
//  pararMotor(motorDir[0],motorDir[1]);
//}
//void avancaDireita(int vel){  
//  motor(vel,motorEsq[0],motorEsq[1],false);  
//  pararMotor(motorDir[0],motorDir[1]);
//}
//void avancaEsquerda(int vel){  
//  motor(vel,motorDir[0],motorDir[1],true);  
//  pararMotor(motorEsq[0],motorEsq[1]);
//}
//void voltaDireita(int vel){  
//  motor(vel,motorEsq[0],motorEsq[1],true);  
//  pararMotor(motorDir[0],motorDir[1]);
//}
//void voltaEsquerda(int vel){  
//  motor(vel,motorDir[0],motorDir[1],false);  
//  pararMotor(motorEsq[0],motorEsq[1]);
//}



//FUNÇÕES DO MOTOR
///
// sentido = 1 // horario
// sentido = 2 // anti-horario
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

