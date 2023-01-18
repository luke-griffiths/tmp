#include "i2c.h"
#include "bldc_display.h"

//create code for CAN handler and functions in a separate file
//do control loop stuff here
float Ki_vel;
float Kp_vel;
float Ki_current;
float Kp_current;
float Kp_pos;


float pos_feedback; //this is the encoder reading
float pos_prev; //previous position of the encoder, updates every step
float current_integral;
float voltage_integral;
float current_feedback; //this is calculated from Nivant's current read ADC stuff

//MAKE EVERYTHING NECESSARY VOLATILE

float tmp(bool cmd_type, float cmd_arg) {
  float vel_cmd;
  float vel_feedback = (pos_feedback - pos_prev) * 3.14159272; //some scaling based on how fast the control loop interrupt is run
  if (cmd_type) {
    //cmd_type of true is a position write 
    float pos_error = cmd_arg - pos_feedback; //pos_feedback is the position given from the encoder, cmd_arg is the position sent by CS
    vel_cmd = pos_error * Kp_pos;
  }
  else {
    //cmd_type of false is a velocity write
    vel_cmd = cmd_arg;
  }
  //POSITION LOOP FINISHED
  //VEL LOOP START
  float vel_error = vel_cmd - vel_feedback;
  current_integral += vel_error * Ki_vel;
  float current_cmd = vel_error * Kp_vel + current_integral;
  //VEL LOOP FINISHED
  //CURRENT LOOP START
  float current_error = current_cmd - current_feedback;
  voltage_integral += current_error * Ki_current;
  float voltage_cmd = current_error * Kp_current + voltage_integral;

  return voltage_cmd;
}
