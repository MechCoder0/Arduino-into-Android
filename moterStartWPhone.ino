#include <Servo.h>
//Try using different pins because it may not need PWM
Servo esc3, esc5, esc6, esc9;
int motorSpeed =0;
int flag = 0;
String data;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  instructions();
  esc9.attach(9);
  esc6.attach(6);
  esc5.attach(5);
  esc3.attach(3);
}

void loop() {

  if(Serial.available() > 0){
      data = Serial.readStringUntil('*');
      flag=0;
  }
  if(data.equalsIgnoreCase("U")){
    motorSpeed = up();
  }
  if(motorSpeed >180){
    motorSpeed = 180;
  }
  if(data.equalsIgnoreCase("D")){
      for(int i=motorSpeed; i>=0; i--){
        setLevel(i);
        delay(100);
        if(i <= 20){
          setLevel(0);
          motorSpeed=0;
          break;
        }
    }
    flag = 1;
  }
  if(data.equalsIgnoreCase("S")){
    motorSpeed = 0;
  }
  if(flag==0){
    setLevel(motorSpeed);
    Serial.println("Speed:" + motorSpeed);
    instructions();
    flag = 1;
  }
}

int up(){
  int upAmount=0;
  Serial.println("How much up?, end with a *");
  data = Serial.readStringUntil('*');
  upAmount = data.toInt();
  return upAmount; 
}

/*void down(){
  for(int i=100; i>=0; i--){
    setLevel(i);
    delay(100);
  }
  motorSpeed=0;
}*/

void setLevel(int level){
    esc3.write(level);
    esc5.write(level);
    esc6.write(level);
    esc9.write(level);
    /*
    if(level >currentSpeed){
      for(int i = currentSpeed; i< level; i++){
        esc3.write(i);
        esc5.write(i);
        esc6.write(i);
        esc9.write(i);
        delay(5);
      }
    }
    else if (level < currentSpeed){
      for(int i = currentSpeed; i> level; i--){
        esc3.write(i);
        esc5.write(i);
        esc6.write(i);
        esc9.write(i);
        delay(5);
      }
    }
    currentSpeed = level;*/
}

void instructions(){
  Serial.println("Always end your line with a *");
  Serial.println("Type U for up\n");
  Serial.println("Type S for stop\n");
  Serial.println("Type D for a gradual down");
}

