#include "bras_robot.h"
#include <Wire.h>

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
// int S0 = 12;
// int S1 = 8;
// int S2 = 7;
// int S3 = 4;
// int sensorOut = 2;

// int rouge = 0;
// int vert = 0;
// int bleu = 0;

// String couleur = "none";

//CONTROLE
int X_pin = A0;
int Y_pin = A1;
int Z_pin = A2;

int manual = 12;
int Go = 11;
int mode = 0;

//LCD
#include "rgb_lcd.h"
rgb_lcd lcd;

//BRAS
int X = 0;
int Y = 0;
int R = 0;

void setup(){
 
 //SERVOMOTEUR
 bras.Begin(9600);
 bras.SetManuel(90, 80, 90, 90, 90);

 //CAPTEUR DE COULEUR
//  pinMode(S0, OUTPUT);
//   pinMode(S1, OUTPUT);
//   pinMode(S2, OUTPUT);
//   pinMode(S3, OUTPUT);
//   pinMode(sensorOut, INPUT);

// fréquence à 20%
// digitalWrite(S0, HIGH);
// digitalWrite(S1, LOW);

//CONTROLE
pinMode(manual, INPUT_PULLUP);
pinMode(Go, INPUT_PULLUP);
pinMode(X_pin, INPUT);
pinMode(Y_pin, INPUT);
pinMode(Z_pin, INPUT);
//LCD
Wire.begin();
lcd.begin(16, 2);
lcd.setRGB(55, 50, 200);
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
  // get_color();
  // Serial.println(couleur);
  // 
  // for (int t=0; t<90; t++){
  //  bras.SetManuel(90, t, 90, 90, 90);
  //  delay(20);
  // }
  // delay(500);
  // for (int t=0; t<90; t++){
  //  bras.SetManuel(90, 90-t, 90, 90, 90);
  //  delay(20);
  // }
  // delay(500);

screen();
Manual();

}

// void get_color(){
//   // ===== ROUGE =====
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, LOW);

//   rouge = pulseIn(sensorOut, LOW);

//   // ===== BLEU =====
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, HIGH);

//   bleu = pulseIn(sensorOut, LOW);

//   // ===== VERT =====
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, HIGH);

//   vert = pulseIn(sensorOut, LOW);

//   // affichage
//   // Serial.print("R = ");
//   // Serial.print(rouge);

//   // Serial.print(" V = ");
//   // Serial.print(vert);

//   // Serial.print(" B = ");
//   // Serial.println(bleu);

//   // ===== DETECTION =====

//   // BLEU
//   if (bleu < 150 && bleu < rouge && bleu < vert) {
//     couleur = "BLEU";
//   }

//   // ORANGE
//   else if (rouge < 75 && bleu > rouge) {
//     couleur = "ORANGE";
//   }

//   else{
//     couleur = "none";
//   }
  
//   return couleur;
// }

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
    Serial.println(Z_pos);
    if(Z_pos < 492){
      R += 1;
      delay(20);
    }
  }
}