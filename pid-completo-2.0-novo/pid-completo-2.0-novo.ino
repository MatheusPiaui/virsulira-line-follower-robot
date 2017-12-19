//setando portas do motor
//vetor onde:
//posição 1 = porta digital
//posição 2 = porta analógica(velocidade)
int motorEsq[2] = {7,6};
int motorDir[2] = {4,5};
int velocidade = 70;
//setando portas dos sensores
const int SENSOR0 = A0, SENSOR1 = A1, SENSOR2 = A2, SENSOR3 = A3, SENSOR4 = A4, SENSOR5 = A5, SENSOR6 = A6, SENSOR7 = A7;
int esq = 0, esqP = 0, esqT = 0;
int dir = 0, dirP = 0;
//// sensores de partida/chegada
int par1 = 0, par2 = 0, par3 = 0;
int leituraParChe[3] = {0,0,0};
////

// Definição
int corte = 100;
int cont = 0;



////
//int kp = 20; // constrante proporcional

int leitura[4] = {0,0,0,0};
// Possibilidades
//[0,1,1,1]1 //  4
//[0,0,0,1]2 //  3
//[0,0,1,1]3 //  2
//[0,0,1,0]4 //  1
//[0,1,1,0]5 //  0  centro
//[0,1,0,0]6 // -1
//[1,1,0,0]7 // -2
//[1,0,0,0]8 // -3
//[1,1,1,0]9 // -4

//pid
float erro = 0;
float P = 0,I = 0,D = 0;
float kp = 20, ki = 0.00001 , kd = 15;
float PIDvalue = 0;
int previousError = 0;

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
       dirPLi += dirP;lerSensores();
       par1Li += par1;
       par2Li += par2;
       par3Li += par3;
       delay(100);
   }  
   delay(3000);

   //ACENDE LED
   digitalWrite(3,HIGH);
   
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
   digitalWrite(3,LOW);
}

int esqTLi = 0;

//5 segundos no banco e 5 no preto
void calibrarEsq(){

   int cont=0;
   delay(1000);
   for(cont=0; cont < 10; cont++){
       esqT = analogRead(SENSOR0);

       esqTLi += esqT;
       delay(100);
   }  
   delay(3000);

   //ACENDE LED
   digitalWrite(3,HIGH);
   
   delay(1000);
   for(cont=0; cont < 10; cont++){
       esqT = analogRead(SENSOR0);
       
       esqTLi += esqT;
       delay(100);
   }
   delay(3000);
   esqTLi /= 20;
   digitalWrite(3,LOW);
}

void setup() {
//    esqP = analogRead(SENSOR2);
//    esq = analogRead(SENSOR3);
//    dir = analogRead(SENSOR4);
//    dirP = analogRead(SENSOR5);
    //Define os pinos como saida
    //motorEsq
    pinMode(motorEsq[0], OUTPUT);
    pinMode(motorEsq[1], OUTPUT);
    //motorDir
    pinMode(motorDir[0], OUTPUT);
    pinMode(motorDir[1], OUTPUT);
    //led
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);

    calibrar();
    delay(5000);
//    calibrarEsq();
//    delay(7000);
//    calibraParChe();
//    delay(5000);
    
}


void loop() {
  lerSensores();
  
  // logica partida/chegada
  if((leitura[0] == 1)&&(leitura[1] == 1)&&(leitura[2] == 1)&&(leitura[3] == 1))
    erro = 0;
  else{
    //condição de parada
//     if((leituraParChe[0] == 0) && (leituraParChe[1] == 1) && (leituraParChe[2] == 1) 
//      && (leitura[0] == 0) && (leitura[1] == 1) && (leitura[2] == 1) && (leitura[3] == 0) 
//      && esqT < esqTLi){
      if(leituraParChe[2] == 1){
        delay(500);
       
        if(cont == 11){
          
          motor(velocidade,motorEsq[0],motorEsq[1]);
          motor(velocidade,motorDir[0],motorDir[1]);
          delay(500);
          

          pararMotor(motorEsq[0],motorEsq[1]);
          pararMotor(motorDir[0],motorDir[1]);
          
          delay(15000);
          cont = 0;
        }else{
          cont++;
        }      
         
    
    }else{
        // logica para gerar os erros
        if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 0)&&(leitura[3] == 1))//1
          erro = 3;
        else{
          if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 1)&&(leitura[3] == 1))//2
            erro = 2;
          else{
            if((leitura[0] == 0)&&(leitura[1] == 0)&&(leitura[2] == 1)&&(leitura[3] == 0))//3
              erro = 1;
            else{
              if((leitura[0] == 0)&&(leitura[1] == 1)&&(leitura[2] == 1)&&(leitura[3] == 0))//4
                erro = 0;
              else{
                if((leitura[0] == 0)&&(leitura[1] == 1)&&(leitura[2] == 0)&&(leitura[3] == 0))//5
                  erro = -1;
                else{
                  if((leitura[0] == 1)&&(leitura[1] == 1)&&(leitura[2] == 0)&&(leitura[3] == 0))//6
                    erro = -2;
                  else{
                    if((leitura[0] == 1)&&(leitura[1] == 0)&&(leitura[2] == 0)&&(leitura[3] == 0))//7
                      erro = -3;
                    else{
                       if((leitura[0] == 0)&&(leitura[1] == 1)&&(leitura[2] == 1)&&(leitura[3] == 1))//8 //curva 90 graus
                          erro = 3;
                       else{
                          if((leitura[0] == 1)&&(leitura[1] == 1)&&(leitura[2] == 1)&&(leitura[3] == 0))//9 //curva 90 graus
                            erro = -3;
                          else{
                            
                          }
                       }
                    }
                  }
                }
              }
            }
          }
        }
      }
  }
 
  
  
  

  //velocidade dos motores (kp * erro)

  //pid
  calculatePID();
  //ir para frente
  if(erro == 3.05 || erro == -3.05){
    motor(velocidade + PIDvalue,motorEsq[0],motorEsq[1]);
    motor(velocidade - PIDvalue,motorDir[0],motorDir[1]);
    delay(100);
  }else{
    motor(velocidade + PIDvalue,motorEsq[0],motorEsq[1]);
    motor(velocidade - PIDvalue,motorDir[0],motorDir[1]);
  }

  
}

void lerSensores(){
   // leitura
   esqP = analogRead(SENSOR1);
   esq = analogRead(SENSOR2);
   dir = analogRead(SENSOR3);
   dirP = analogRead(SENSOR4);

   par1 = analogRead(SENSOR5);
   par2 = analogRead(SENSOR6);
   par3 = analogRead(SENSOR7);

   esqT = analogRead(SENSOR0);
   

  
  // Definir leitura
  
  
  if(esqP < esqPLi + corte){
    leitura[0] = 0;
  }else{
    leitura[0] = 1;
  }
  
  if(esq < esqLi + corte){
    leitura[1] = 0;
  }else{
    leitura[1] = 1;
  }
  
  if(dir < dirLi + corte){
    leitura[2] = 0;
  }else{
    leitura[2] = 1;
  }
  
  if(dirP < dirPLi + corte){
    leitura[3] = 0;
  }else{
    leitura[3] = 1;
  }

  // partida e Chegada
  if(par1 < par1Li + corte){
    leituraParChe[0] = 0;
  }else{
    leituraParChe[0] = 1;
  }
  if(par2 < par2Li + corte){
    leituraParChe[1] = 0;
  }else{
    leituraParChe[1] = 1;
  }
  if(par3 < par3Li + corte){
    leituraParChe[2] = 0;
  }else{
    leituraParChe[2] = 1;
  }
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
   digitalWrite(in2, 0);
}
