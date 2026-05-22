#ifndef bras_robot_h
#define bras_robot_h

#include <Arduino.h>
#include "Servo.h"

class bras {
  public:
    bras(int input_rZ, int input_Epaule, int input_Coude, int input_Poignet, int input_Pince);
    void Begin(int Bauds);
    void SetManuel(int set_rZ, int set_Epaule, int set_Coude, int set_Poignet, int set_Pince);
    void SetXY(float set_X, float set_Y);
    void SetRotation(int set_rZ);
    void SetPos(float set_X, float set_Y, int set_rZ);
    void SetPince(int set_Pince);
    void Go(int set_X, int set_Y, int set_rZ);

    Servo rZ;
    Servo Epaule;
    Servo Coude;
    Servo Poignet;
    Servo Pince;
  private:
    int rZ_pin;
    int Epaule_pin;
    int Coude_pin;
    int Poignet_pin;
    int Pince_pin;

    int R_Actual = 90;
    int Pince_actual = 90;
    
    // int pos_rZ;
    // int pos_Epaule;
    // int pos_Coude;
    // int pos_Poignet;
    // int pos_Pince;
    // int X;
    // int Y; 
};

#endif
