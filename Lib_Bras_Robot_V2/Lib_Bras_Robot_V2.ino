#include "bras_robot.h"
#include <Wire.h>
#include "rgb_lcd.h" 

// VARIABLE POSITION
int mixed_X = 14;
int mixed_rZ = 90;
int mixed_Y[6] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5};
int mixed_height = 6;

int blue_X = 14;
int blue_rZ = 45;
int blue_Y[6] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5};
int blue_height = 0;

int orange_X = 14;
int orange_rZ = 135;
int orange_Y[6] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5};
int orange_height = 0;


// SERVOMOTEUR
bras bras(3,5,6,9,10);


// CAPTEUR DE COULEUR
int S2 = 8;
int S3 = 7;
int sensorOut = 2;

int rouge = 0;
int vert = 0;
int bleu = 0;

String couleur = "none";

//CONTROLE
int X_pin = A0;
int Y_pin = A1;
int Z_pin = A2;

int up = 0;
int down = 0;

int manual = 12;
int Go = 11;
int mode = 1;

int pince_open = 0;
int pince_close = 90;

//LCD
rgb_lcd lcd;

//BRAS
int X = 0;
int Y = 0;
int R = 0;

int step = 0;
int cibleX = 10;
int cibleY = 10;
int cibleR = 90;

void setup(){
 
 //SERVOMOTEUR
  bras.Begin(9600);
  bras.SetManuel(90, 0, 0, 90, 90);

 //CAPTEUR DE COULEUR
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

 //CONTROLE
  pinMode(manual, INPUT_PULLUP);
  pinMode(Go, INPUT_PULLUP);
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  pinMode(Z_pin, INPUT);

 //LCD
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setRGB(70, 70, 70);
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 0);  
  lcd.print("ROBOTIC ARM 2000");
  lcd.setCursor(0, 1);
  lcd.print("init");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  lcd.display();
}

void loop(){
  
  // for (int t=0; t<9; t++){
  //  bras.SetXY(13, t+10);
  //  delay(1000);
  // }
  
  // Serial.println(couleur);
  get_color();
  screen();
  Manual();
  LaunchMenu();
  Auto();
  bras.SetManuel(90, 0, 0, 90, 90);

}

int get_color(){
  // ===== ROUGE =====
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  rouge = pulseIn(sensorOut, LOW);

  // ===== BLEU =====
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  bleu = pulseIn(sensorOut, LOW);

  // ===== VERT =====
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  vert = pulseIn(sensorOut, LOW);

  // affichage
  // Serial.print("R = ");
  // Serial.print(rouge);

  // Serial.print(" V = ");
  // Serial.print(vert);

  // Serial.print(" B = ");
  // Serial.print(bleu);

  // Serial.print(" C = ");
  // Serial.println(couleur);


  // ===== DETECTION =====

  // BLEU
  if (bleu < 15 && rouge < 15 && vert < 30) {
    lcd.setRGB(0, 0, 255);
    couleur = "BLEU";
  }

  // ORANGE
  else if (rouge < 22 && vert < 22 && bleu < 22) {
    lcd.setRGB(255, 45, 0);
    couleur = "ORANGE";
  }

  else{
    lcd.setRGB(70, 70, 70);
    couleur = "none";
  }
  
  // return couleur;
}

void screen(){
  if(digitalRead(manual) == 0){
    mode = 2;
    lcd.setCursor(0, 0);
    lcd.print("Manual Mode     ");
    lcd.setCursor(0, 1);
    lcd.print("R:");
    lcd.print(R);
    lcd.print(" X:");
    lcd.print(X);
    lcd.print(" Y:");
    lcd.print(Y);
    lcd.print("       ");
  }

  if(digitalRead(manual) == 1 && digitalRead(Go) == 1){
    if(mode == 2){
      mode = 1;
    }

    if(mode == 1){
      lcd.setCursor(0, 0);
      lcd.print("Press to start    ");
      lcd.setCursor(0, 1);
      lcd.print("mix:");
      lcd.print(mixed_height);
      lcd.print(" O:");
      lcd.print(0);
      lcd.print(" B:");
      lcd.print(0);
      lcd.print("       ");
    }

    if(mode == 0){
      lcd.setCursor(0, 0);
      lcd.print("Press to stop    ");
      lcd.setCursor(0, 1);
      lcd.print("mix:");
      lcd.print(mixed_height);
      lcd.print(" O:");
      lcd.print(0);
      lcd.print(" B:");
      lcd.print(0);
      lcd.print("       ");
    }
  }

  if(digitalRead(Go) == 0){
    if(mode == 0){
      mode = 1;
      delay(500);
    }
    else if(mode == 1){
      mode = 0;
      delay(500);
    }
  }
}

void Manual(){
  if(mode == 2){
    int Z_pos = analogRead(Z_pin);
    // Serial.println(Z_pos);
    if(Z_pos < 492){
      R += -1;
      delay(200);
    }
    if(Z_pos > 522){
      R += 1;
      delay(200);
    }
    if(R < 0){R = 0;}
    if(R > 180){R = 180;}

    int X_pos = analogRead(X_pin);
    // Serial.println(X_pos);
    if(X_pos < 492){
      X += -1;
      delay(200);
    }
    if(X_pos > 522){
      X += 1;
      delay(200);
    }
    if(X < 0){X = 0;}
    if(X > 180){X = 180;}

    int Y_pos = analogRead(Y_pin);
    // Serial.println(Y_pos);
    if(Y_pos < 492){
      Y += -1;
      delay(200);
    }
    if(Y_pos > 522){
      Y += 1;
      delay(200);
    }
    if(Y < 0){Y = 0;}
    if(Y > 180){Y = 180;}

    bras.SetPos(X, Y, R);
  }
}

void LaunchMenu(){
  if(mode == 1){
    int X_pos = analogRead(X_pin);
    // Serial.println(X_pos);
    if(X_pos < 492 && down == 0){
      down = 1;
    }
    if(X_pos > 522 && up == 0){
      up = 1;
    }

    if(X_pos < 522 && X_pos > 492 && up == 1){
      mixed_height += 1;
      up = 0;
      delay(200);
    }

    if(X_pos < 522 && X_pos > 492 && down == 1){
      mixed_height += -1;
      down = 0;
      delay(200);
    }

    if(mixed_height < 0){mixed_height = 0;}
    if(mixed_height > 7){mixed_height = 7;}
    int orange_height = 0;
    int blue_height = 0;
  }
}

void Auto(){
  if(mode == 0){
    if(step == 0){
      cibleX = 10;
      cibleY = 10;
      cibleR = 90;
      if(deplacement() == 0){step = 1;}
    }
    if(step == 0){
      cibleX = 10;
      cibleY = 10;
      cibleR = 90;
      if(deplacement() == 0){step = 1;}
    }

  }
}

int deplacement(){
  
  for (int t=0; t<90; t++){
   bras.SetManuel(90, t, 90, 90, 90);
   delay(20);
  }
  delay(500);
  for (int t=0; t<90; t++){
   bras.SetManuel(90, 90-t, 90, 90, 90);
   delay(20);
  }
  delay(500);

  return false;
}