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
  R_Actual = set_rZ;
  rZ.write(set_rZ);
  Epaule.write(set_Epaule);
  Coude.write(set_Coude);
  Poignet.write(set_Poignet);
  Pince_actual = set_Pince;
  Pince.write(set_Pince);
}

// void bras::SetXY(int set_X, int set_Y){
//   float taille_Bras = 15.0;
//   float R = 65.0;
//   float theta = 90.0;

//   float X = set_X;
//   float Y = set_Y - 13.0;

//   // Angle de la cible
//   float alpha = atan2(Y, X) * 180.0 / PI;

//   // Distance base -> cible
//   float BP = sqrt((X * X) + (Y * Y));

//   // Demi triangle
//   float HP = BP / 2.0;

//   // Angle du triangle
//   float beta = acos(HP / taille_Bras) * 180.0 / PI;

//   // Épaule
//   float E = beta + alpha;

//   float D = 90.0 - alpha;

//   // Angle interne du coude
//   float W = 180.0 - (2.0 * beta);

//   // Coude
//   float Z = W - R;

//   float rho = (beta + D) - 90.0;

//   // Poignet
//   float Q = rho + theta;

//   // Inversion servo coude
//   Z = map(Z, 0, 180, 180, 0);

//   // Serial.print("E=");
//   // Serial.print(E);

//   // Serial.print(" Z=");
//   // Serial.print(Z);

//   // Serial.print(" Q=");
//   // Serial.println(Q);

//   SetManuel(R_Actual, E, Z, Q, Pince_actual);
// }

void bras::SetXY(float set_X, float set_Y){

  // ==============================
  // PARAMETRES DU BRAS
  // ==============================

  float taille_Bras = 15.0;   // Longueur des 2 segments
  float theta = 90.0;         // Orientation voulue de la pince

  // ==============================
  // POSITION CIBLE
  // ==============================

  float X = set_X;
  float Y = set_Y - 13.0;     // Offset vertical de la base

  // ==============================
  // DISTANCE BASE -> POINT
  // ==============================

  float BP = sqrt((X * X) + (Y * Y));

  // Sécurité portée max
  float BPmax = (taille_Bras * 2.0) - 0.01;

  if(BP > BPmax){
    BP = BPmax;
  }

  // ==============================
  // ANGLE ALPHA
  // ==============================

  // Angle de la ligne BP par rapport au sol
  float alpha = atan2(Y, X);

  // Conversion en degrés
  alpha = alpha * 180.0 / PI;

  // ==============================
  // TRIANGLE ISOCELE
  // ==============================

  float HP = BP / 2.0;

  float ratio = HP / taille_Bras;

  // Sécurité acos
  ratio = constrain(ratio, -1.0, 1.0);

  float beta = acos(ratio);

  // Conversion degrés
  beta = beta * 180.0 / PI;

  // ==============================
  // EPAULE
  // ==============================

  float E = beta + alpha;

  // ==============================
  // COUDE
  // ==============================

  float W = 180.0 - (2.0 * beta);

  // Inversion mécanique servo
  float Z = 180.0 - W;

  // ==============================
  // POIGNET
  // ==============================

  float D = 90.0 - alpha;

  float rho = (beta + D) - 90.0;

  float Q = rho + theta;

  // ==============================
  // LIMITES SERVOS
  // ==============================

  E = constrain(E, 0, 180);
  Z = constrain(Z, 0, 180);
  Q = constrain(Q, 0, 180);

  // ==============================
  // DEBUG
  // ==============================

  // Serial.println("==========");

  // Serial.print("X = ");
  // Serial.println(X);

  // Serial.print("Y = ");
  // Serial.println(Y);

  // Serial.print("BP = ");
  // Serial.println(BP);

  // Serial.print("alpha = ");
  // Serial.println(alpha);

  // Serial.print("beta = ");
  // Serial.println(beta);

  // Serial.print("E = ");
  // Serial.println(E);

  // Serial.print("Z = ");
  // Serial.println(Z);

  // Serial.print("Q = ");
  // Serial.println(Q);

  // ==============================
  // ENVOI AUX SERVOS
  // ==============================

  SetManuel(
    R_Actual,
    E,
    Z,
    Q,
    Pince_actual
  );
}

void bras::SetRotation(int set_rZ){
  R_Actual = set_rZ;
  rZ.write(set_rZ);
}

void bras::SetPince(int set_Pince){
  Pince_actual = set_Pince;
  Pince.write(set_Pince);
}

void bras::SetPos(float set_X, float set_Y, int set_rZ){
  R_Actual = set_rZ;
  SetRotation(set_rZ);
  SetXY(set_X, set_Y);
}

void bras::Go(int set_X, int set_Y, int set_Z){
  Serial.println("Fonction .Go non fonctionelle pour le moment");
}
