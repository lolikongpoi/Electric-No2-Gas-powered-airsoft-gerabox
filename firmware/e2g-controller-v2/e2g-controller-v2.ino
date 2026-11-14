#include <EEPROM.h>



int SEMI[] = {1,0};    //shoots when trigger push and release
int AUTO[] = {-1,0};    //-1 means full auto


int fireRate = 20;  //fire rate
int pushTime = 13;  //valve open time, shall less than 1000/firerate
int minGap = 5;     //valve close time


const int VALVE = 6;
const int EXT = 5;
const int MAG = 3;
const int TRIGGER = A3;
const int SELECTOR = A2;
const int BAT = A1;

int gap;
int firingMode;
int needToShoot = 0;
int triggerStatus=HIGH;
int lastTriggerStatus = LOW;

void blink(int time, int intervel);

String inputString = "";
boolean stringComplete = false;
void singleVar(int mode);
void dualVar(int mode);
void(* resetFunc) (void) = 0;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGER,INPUT_PULLUP);
  pinMode(SELECTOR,INPUT_PULLUP);
  pinMode(BAT,INPUT);
  pinMode(MAG, OUTPUT);
  pinMode(VALVE, OUTPUT);
  digitalWrite(MAG,LOW);
  digitalWrite(VALVE,LOW);
  inputString.reserve(200);

  if(float(analogRead(BAT))*5/1024 < 3.3){
    while(1){
      blink(1,100);
    }
  } 
  int tmp;
  /**
  EEPROM.get(8,tmp);
  if(tmp!=0){
    EEPROM.get(0,SEMI[0]);
    EEPROM.get(2,SEMI[1]);
    EEPROM.get(4,AUTO[0]);
    EEPROM.get(6,AUTO[1]);
    EEPROM.get(8,fireRate);
    EEPROM.get(10,pushTime);
  }
  **/

  EEPROM.get(12,tmp);
  if(tmp!=233){
    EEPROM.put(0,SEMI[0]);
    EEPROM.put(2,SEMI[1]);
    EEPROM.put(4,AUTO[0]);
    EEPROM.put(6,AUTO[1]);
    EEPROM.put(8,fireRate);
    EEPROM.put(10,pushTime);  
    EEPROM.put(12,233);  
  }else{
    EEPROM.get(0,SEMI[0]);
    EEPROM.get(2,SEMI[1]);
    EEPROM.get(4,AUTO[0]);
    EEPROM.get(6,AUTO[1]);
    EEPROM.get(8,fireRate);
    EEPROM.get(10,pushTime);
  }



  gap = 1000/fireRate - pushTime;


  blink(3,300);

  Serial.begin(9600);
  serialHello();

}
void loop(){
  triggerStatus = digitalRead(TRIGGER);
  if(lastTriggerStatus!=triggerStatus){
    lastTriggerStatus = triggerStatus;
    firingMode = digitalRead(SELECTOR);
    if(firingMode == LOW){
      if(triggerStatus == LOW){
        needToShoot = AUTO[0];
      }else{
        needToShoot = AUTO[1];
      }
    }else{
      if(triggerStatus == LOW){
        needToShoot = SEMI[0];
      }else{
        needToShoot = SEMI[1];
      }
    }
  }


  shoot();


  if (stringComplete) {
    Serial.println(inputString);
    serialSettings();
    inputString = "";
    stringComplete = false;
  }


}

void shoot(){
  if(needToShoot==0){return;}
  digitalWrite(MAG,HIGH);
  digitalWrite(VALVE,HIGH);
  delay(pushTime);
  digitalWrite(VALVE,LOW);
  delay(gap);
  digitalWrite(MAG,LOW);
  needToShoot--;
  // Serial.println(1);
}

void blink(int time, int intervel){
  for (int i = 0; i < time; ++i){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(intervel);
    digitalWrite(LED_BUILTIN, LOW);
    delay(intervel); 
  }
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void serialHello(){
  Serial.println("Welcome using E2G V2.02");
  Serial.println("Function list");
  Serial.println("READ  : Read all constants");
  Serial.println("SAVE  : Save the constants");
  Serial.println("HELP  : Show help massage");
  Serial.println("AUTO <INT> <INT> : Shoots when trigger pushed or released in Full mode, -1 means full auto, the second constant shall not be -1");
  Serial.println("SEMI <INT> <INT> : Shoots when trigger pushed or released in Semi mode, -1 means full auto, the second constant shall not be -1");
  Serial.println("RATE <INT> : Shooting rate, between 5 to 50");
  Serial.println("PUSH <INT> : Valve open time in ms, shall less than 1000/rate");
  Serial.println("MAGG <INT> : Preloading time in s");
  Serial.println("SHOT <INT> : Remote fire, shall less than 100 rounds");
  Serial.println("RESET  : Reset to manufactory setting");
  Serial.println("To get user manual and more info, you can go to Youtube channel: gelhpa");
}

void serialSettings(){
  inputString.trim();
  if(inputString.startsWith("READ")){
    Serial.println("Current state：");
    Serial.print("Full ");
    Serial.print(AUTO[0]);
    Serial.print(" , ");
    Serial.println(AUTO[1]);
    Serial.print("Semi ");
    Serial.print(SEMI[0]);
    Serial.print(" , ");
    Serial.println(SEMI[1]);
    Serial.print("Rate ");
    Serial.print(fireRate);
    Serial.println(" r/s");
    Serial.print("valve open time ");
    Serial.print(pushTime);
    Serial.println(" ms");
    Serial.print("Battery voltage ");
    Serial.print(float(analogRead(BAT))*5/1024);
    Serial.print(" V");
  }else if(inputString.startsWith("SAVE")){
    EEPROM.put(0,SEMI[0]);
    EEPROM.put(2,SEMI[1]);
    EEPROM.put(4,AUTO[0]);
    EEPROM.put(6,AUTO[1]);
    EEPROM.put(8,fireRate);
    EEPROM.put(10,pushTime);
  }else if(inputString.startsWith("AUTO ")){
    dualVar(1);
  }else if(inputString.startsWith("SEMI ")){
    dualVar(2);    
  }else if(inputString.startsWith("RATE ")){
    singleVar(1);
  }else if(inputString.startsWith("PUSH ")){
    singleVar(2);
  }else if(inputString.startsWith("MAGG ")){
    singleVar(3);
  }else if(inputString.startsWith("SHOT ")){
    singleVar(4);
  }else if(inputString.startsWith("HELP")){
    serialHello();
  }else if(inputString.startsWith("RESET")){
    EEPROM.put(0,1);
    EEPROM.put(2,0);
    EEPROM.put(4,-1);
    EEPROM.put(6,0);
    EEPROM.put(8,20);
    EEPROM.put(10,13);
    EEPROM.get(0,SEMI[0]);
    EEPROM.get(2,SEMI[1]);
    EEPROM.get(4,AUTO[0]);
    EEPROM.get(6,AUTO[1]);
    EEPROM.get(8,fireRate);
    EEPROM.get(10,pushTime);

  }
}

void dualVar(int mode){
  String buf;
  String vars1 = "";
  String vars2 = "";
  int var1,var2;
  bool switchflag = false;  
  buf = inputString.substring(4);
  buf.trim();
  int len = buf.length();
  char charbuf[len] = {};
  buf.toCharArray(charbuf,len+1);
  for(int i=0;i<len;i++){
    if(charbuf[i] != ' '){
      if(switchflag){
        vars2 += charbuf[i];
      }else{
        vars1 += charbuf[i];
      }
    }else{
      switchflag = true;
    }
  }
  var1 = vars1.toInt();
  var2 = vars2.toInt();

  if(var1<=0||var1>5 || var2<0||var2>5){
      Serial.print("Input value ");
      Serial.print(var1);
      Serial.print(" , ");
      Serial.print(var2);
      Serial.println(" is illegal");
    return;
  }

  if(mode == 1){
    AUTO[0] = var1;
    AUTO[1] = var2;
  }else{
    SEMI[0] = var1;
    SEMI[1] = var2;
  }
  Serial.println("Successed");
}

void singleVar(int mode){
  String buf;
  String vars1 = inputString.substring(4);
  vars1.trim();

  int var = vars1.toInt();

  if(mode == 1){
    if(var<5||var>50){
      Serial.print("Input value ");
      Serial.print(var);
      Serial.println(" is illegal");
      return;
    }

    if(1000/var-pushTime<minGap){
      pushTime = 1000/var-minGap;
      Serial.print("Valave opens time too long, reduced to ");
      Serial.print(pushTime);
      Serial.println(" ms");
    }
    fireRate = var;
    gap = 1000/fireRate - pushTime;
  }else if(mode == 2){
    if(var<5){
      Serial.print("Input value ");
      Serial.print(var);
      Serial.println(" is illegal");
      return; 
    }

    if(1000/fireRate-var<minGap){
      pushTime = 1000/fireRate-minGap;
      Serial.print("Valave opens time too long, setting to maximum ");
      Serial.print(pushTime);
      Serial.println(" ms");
    }else{
      pushTime = var;
    }
    gap = 1000/fireRate - pushTime;
  }else if(mode == 3){
    if(var<0||var>15){
      Serial.print("Input value ");
      Serial.print(var);
      Serial.println(" is illegal"); 
      return;
    }
    digitalWrite(MAG,HIGH);
    delay(var*1000);
    digitalWrite(MAG,LOW);
  }else if(mode == 4){
    if(var<0||var>100){
      Serial.print("Input value ");
      Serial.print(var);
      Serial.println(" is illegal"); 
      return;
    }
    while(var>0){
      var--;
      needToShoot++;
      shoot();
    }
  }
  Serial.println("Successed");

}
