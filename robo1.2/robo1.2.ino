//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6} ;
int motorDir[2] = {4,5};

int SENSOR1, SENSOR2, SENSOR3;
 
//deslocamentos de calibracao
int leftOffset = 0, rightOffset = 0, centre = 0;
//pinos para a velocidade e direcao do motor
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
//velocidade inicial e deslocamento de rotacao
int startSpeed = 200, rotate = 30;
//limiar do sensor
int threshold = 0;
//velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;
 
//Rotina de calibracao do sensor
void calibrate()
{
 for (int x=0; x<10; x++) //Executa 10 vezes para obter uma media
 {
   delay(100);
   SENSOR1 = analogRead(6);
   SENSOR2 = analogRead(5);
   SENSOR3 = analogRead(3);
   leftOffset = leftOffset + SENSOR1;
   centre = centre + SENSOR2;
   rightOffset = rightOffset + SENSOR3;
   delay(100);
 }
 //obtem a media para cada sensor
 leftOffset = leftOffset /10;
 rightOffset = rightOffset /10;
 centre = centre / 10;
 //calcula os deslocamentos para os sensores esquerdo e direito
 leftOffset = centre - leftOffset;
 rightOffset = centre - rightOffset;
}
 
void setup()
{
  calibrate();
  //Define os pinos como saida
  //motorEsq
  pinMode(motorEsq[0], OUTPUT);
  pinMode(motorEsq[1], OUTPUT);
  //motorDir
  pinMode(motorDir[0], OUTPUT);
  pinMode(motorDir[1], OUTPUT);
  delay(3000);
}
 
void loop()
{
  //utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;
 
  //le os sensores e adiciona os deslocamentos
  SENSOR1 = analogRead(6) + leftOffset;
  SENSOR2 = analogRead(5);
  SENSOR3 = analogRead(3) + rightOffset;
 
  //Se SENSOR1 for maior do que o sensor do centro + limiar,
// vire para a direita
  if (SENSOR1 > SENSOR2+threshold)
  {
    left = startSpeed + rotate;
    right = startSpeed - rotate;
//      direita(right);
    
  }
  //Se SENSOR3 for maior do que o sensor do centro + limiar,
    // vire para a esquerda
      if (SENSOR3 > (SENSOR2+threshold))
      {
        left = startSpeed - rotate;
        right = startSpeed + rotate;
//          esquerda(left);
      }
 direita(right);
 esquerda(left);
  
 
  //Envia os valores de velocidade para os motores
//  motor_esq.setSpeed(left);
//  motor_esq.run(FORWARD);
//  motor_dir.setSpeed(right);
//  motor_dir.run(FORWARD);
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
  motor(vel,motorEsq[0],motorEsq[1],false);  
  motor(vel,motorDir[0],motorDir[1],false);
}
void esquerda(int vel){  
  motor(vel,motorEsq[0],motorEsq[1],true);   
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
