#include "bras_robot.h"
#include "Servo.h"

  // rZ
  // Epaule
  // Coude
  // Poignet
  // Pince

bras::bras(int input_rZ, int input_Epaule, int input_Coude, int input_Poignet, int input_Pince) {
  rZ_pin        = input_rZ;
  Epaule_pin    = input_Epaule;
  Coude_pin     = input_Coude;
  Poignet_pin   = input_Poignet;
  Pince_pin    = input_Pince;
}

void bras::Begin(int Bauds) {
  Serial.begin(Bauds);
  Serial.println("*****************************");
  Serial.println("demarage bras");
  Serial.println("*****************************");
  Serial.println("");

  rZ.attach(rZ_pin);
  Serial.print("le servo 'axe Z' est sur le pin ");
  Serial.println(rZ_pin);

  Epaule.attach(Epaule_pin);
  Serial.print("le servo 'Epaule' est sur le pin ");
  Serial.println(Epaule_pin);

  Coude.attach(Coude_pin);
  Serial.print("le servo 'Coude' est sur le pin ");
  Serial.println(Coude_pin);
  
  Poignet.attach(Poignet_pin);
  Serial.print("le servo 'Poignet' est sur le pin ");
  Serial.println(Poignet_pin);

  Pince.attach(Pince_pin);
  Serial.print("le servo 'Pince' est sur le pin ");
  Serial.println(Pince_pin);
}

void bras::SetManuel(int set_rZ, int set_Epaule, int set_Coude, int set_Poignet, int set_Pince){
  rZ.write(set_rZ);
  Epaule.write(set_Epaule);
  Coude.write(set_Coude);
  Poignet.write(set_Poignet);
  Pince.write(set_Pince);
}

void bras::SetXY(int set_X, int set_Y){
  int taille_Bras = 15;//----------------------------------- taille bras -----------------------------------
  int R = 17;//--------------------------------------------- angle minimum coude -------------------------------
  int theta = 90;

  int X = set_X;
  int Y = set_Y - 10; //------------------------------------ offset Y ----------------------------------------

  int alpha = atan(Y / X);

  int BP = sqrt( (X*X) + (Y*Y) );
  int HP = BP / 2;

  int beta = acos(HP / taille_Bras);
  int E = beta + alpha;//---------------------------------- angle Epaule --------------------------------------

  int D = 90 - alpha;

  int W = 180 - (2 * beta);

  int Z = W - R;//----------------------------------------- angle Coude ---------------------------------------

  int rho = (beta + D) - 90;

  int Q = rho + theta ; //--------------------------------- angle Poignet -------------------------------------

}

void bras::SetRotation(int set_rZ){
  rZ.write(set_rZ);
}

void bras::SetPos(int set_X, int set_Y, int set_rZ){
  SetRotation(set_rZ);
  SetXY(set_X, set_Y);
}

void bras::Go(int set_X, int set_Y, int set_Z){
  Serial.println("Fonction .Go non fonctionelle pour le moment");
}
