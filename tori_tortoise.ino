#include <NewPing.h>
NewPing sonar(A0, A1, 10);//trigger pin, echo pin, max distance in centimetres

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(13, 12, 11, 10); // SCK = 13, MOSI = 12, CS = 11, A0 = 10

String action;
float progress;
String dir;

void intro(String description, String leg, String action) {
 
 u8g.drawStr( 0, 10, "Tori Tortoise");
 u8g.drawFilledEllipse(23, 35, 15, 15);
 u8g.setColorIndex(0);
 u8g.drawBox(3, 35, 40, 20);
 u8g.setColorIndex(1);
 u8g.drawFilledEllipse(6, 31, 4, 4);
 u8g.drawBox(12, 35, 4, 7);
 u8g.drawBox(30, 35, 4, 7);
 leg += description;
 u8g.drawStr(0, 60, leg.c_str());
 u8g.drawStr(50, 30, action.c_str());
 u8g.drawFrame(49, 39, 50, 5);
 u8g.drawBox(50, 40, 48*progress, 3);
 if (dir == "f" or dir == "b") {
  u8g.drawBox(115, 33, 3, 10);}
 if (dir == "f") {
  u8g.drawTriangle(112, 33, 121, 33, 116, 28);}
 if (dir == "b") {
  u8g.drawTriangle(112, 43, 121, 43, 116, 48);}
 if (dir == "l" or dir == "r"){
  u8g.drawBox(111, 37, 10, 3);}
 if (dir == "l") {
  u8g.drawTriangle(111, 33, 111, 43, 107, 38);}
 if (dir == "r") {
  u8g.drawTriangle(121, 33, 121, 43, 125, 38);}
 }
 
 
void run_intro(String description, String leg, String action){
  u8g.firstPage();
  do {
    intro(description, leg, action);} while( u8g.nextPage() );}


#include <Servo.h>
Servo uppers[4];
Servo lowers[4];

//front left, front right, back left, back right
int upperPins[4] = {9, 7, 5, 3};
int lowerPins[4] = {8, 6, 4, 2};

//forward and back angles of each upper servo, in above order(assuming 70 degrees of rotation for all legs)
int upperAngles[8] = {0, 70, 180, 110, 0, 70, 180, 110};

//up and down angles of each lower servo, in above order (90 degrees of rotation)(may change)
int lowerAngles[8] = {90, 180, 90, 0, 90, 0, 90, 180};

//names of legs by index
String names[4] = {"f_l: ", "f_r: ", "b_l: ", "b_r: "};

//order of legs when walking (back left, front left, back right, front right)
int order[4] = {2, 0, 3, 1};

void lift_leg(int index, String action) {
  String name = names[index];
  /*int upperForward = upperAngles[index*2];
  int upperBack = upperAngles[index*2 + 1];*/
  int lowerUp = lowerAngles[index*2];
  int lowerDown = lowerAngles[index*2 + 1];
  
  //lift leg
  progress += 0.0625;
  run_intro("lift", name, action);
  if (lowerUp > lowerDown){
    for (int lowerAngle = lowerDown; lowerAngle < lowerUp; lowerAngle++){
      lowers[index].write(lowerAngle);
      delay(15);}}
  else {
    for (int lowerAngle = lowerDown; lowerAngle > lowerUp; lowerAngle--){
      lowers[index].write(lowerAngle);
      delay(15);}}
  delay(1000);}

void forward_leg(int index, String action) {
  String name = names[index];
  int upperForward = upperAngles[index*2];
  int upperBack = upperAngles[index*2 + 1];
  /*int lowerUp = lowerAngles[index*2];
  int lowerDown = lowerAngles[index*2 + 1];*/
  
  //leg forward
  progress += 0.0625;
  run_intro("forward", name, action);
  if (upperForward > upperBack){
    for (int upperAngle = upperBack; upperAngle < upperForward; upperAngle++){
      uppers[index].write(upperAngle);
      delay(15);}}
  else {
    for (int upperAngle = upperBack; upperAngle > upperForward; upperAngle--){
      uppers[index].write(upperAngle);
      delay(15);}}
  delay(1000);}

void lower_leg(int index, String action) {
  String name = names[index];
  /*int upperForward = upperAngles[index*2];
  int upperBack = upperAngles[index*2 + 1];*/
  int lowerUp = lowerAngles[index*2];
  int lowerDown = lowerAngles[index*2 + 1];
  
  //lower leg
  progress += 0.0625;
  run_intro("lower", name, action);
  if (lowerUp < lowerDown){
    for (int lowerAngle = lowerUp; lowerAngle < lowerDown; lowerAngle++){
      lowers[index].write(lowerAngle);
      delay(15);}}
  else {
    for (int lowerAngle = lowerUp; lowerAngle > lowerDown; lowerAngle--){
      lowers[index].write(lowerAngle);
      delay(15);}}
  delay(1000);}
  
void back_leg(int index, String action) {
  String name = names[index];
  int upperForward = upperAngles[index*2];
  int upperBack = upperAngles[index*2 + 1];
  /*int lowerUp = lowerAngles[index*2];
  int lowerDown = lowerAngles[index*2 + 1];*/
  
  //leg forward
  progress += 0.0625;
  run_intro("back", name, action);
  if (upperForward < upperBack){
    for (int upperAngle = upperForward; upperAngle < upperBack; upperAngle++){
      uppers[index].write(upperAngle);
      delay(15);}}
  else {
    for (int upperAngle = upperForward; upperAngle > upperBack; upperAngle--){
      uppers[index].write(upperAngle);
      delay(15);}}
  delay(1000);}

void step_leg(int index, String action) {
  lift_leg(index, action);
  forward_leg(index, action);
  lower_leg(index, action);
  back_leg(index, action);
}

void backwards_step(int index, String action) {
  lift_leg(index, action);
  back_leg(index, action);
  lower_leg(index, action);
  forward_leg(index, action);
}

int walk_forward(){
  progress = 0;
  action = "walking";
  dir = "f";
  int dist;
  bool cont = true;
  for (int index = 0; index < 4; index++){
    if (cont == true) {
      int leg = order[index];
      String name = names[leg];
      run_intro("scanning", name, action);
      delay(500);
      dist = sonar.ping_cm();
      if (dist != 0) {
        cont = false;}
      if (cont == true) {
        step_leg(leg, action);}
  }}
  return cont;}


void turn_left(){
  progress = 0;
  action = "turning";
  dir = "l";
  
  step_leg(3, action);
  step_leg(1, action);
  backwards_step(2, action);
  backwards_step(0, action);
  }

void turn_right(){
  progress = 0;
  action = "turning";
  dir = "r";
  
  step_leg(2, action);
  step_leg(0, action);
  backwards_step(3, action);
  backwards_step(1, action);
  }

void setup() {
  for(int i=0;i<4;i++){
    uppers[i].attach(upperPins[i]);
    lowers[i].attach(lowerPins[i]);}

  u8g.setColorIndex(1); // pixel on
  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_8x13r);
}

bool cont = true;
int choice;
int dist;
void loop() {
  if (cont == true) {
    cont = walk_forward();}
  else {
    choice = random(2);
    if (choice < 1) {
      turn_left();}
    else {
      turn_right();}
    dist = sonar.ping_cm();  
    if (dist == 0) {
      cont = true;}
    }
}
