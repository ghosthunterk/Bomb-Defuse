#include <Vector.h>
#include <TM1637Display.h>
#include "LedControl.h"
#include <time.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int button1=2,button2=3,button3=4,button4=5;
LiquidCrystal_I2C lcd(0x27,16,2); 
LedControl lc=LedControl(12,10,11,1); // Pins: DIN,CLK,CS,number of displays
TM1637Display display = TM1637Display(8,9); // CLK,DIO
int dButton[5]= {-1,0,0,0,0};
int button[5];
int posButtonStage[5];
int labelButtonStage[5];




void initButton(){
    memset(dButton, 0, sizeof(dButton));
    for (int i=1;i<=4;i++){
        int t=random(1,5);
        Serial.println(t);
        if (dButton[t]==0){
            button[i]=t;
            dButton[t]++;
        }
        else {
            while(dButton[t]==1){
                t=random(1,5);
            }
            button[i]=t;
            dButton[t]++;
        }
    }
  display.clear();
  for (int i=0;i<4;i++)display.showNumberDec(button[i+1],false,1,i);
}

//Base Data

byte number1[] =
{
   B00001000,  // number 1's frame
   B00011000,
   B00001000,
   B00001000,
   B00001000,
   B00001000,
   B00011100,
   B00000000
};

byte number2[] =
{
   B00011100,  // number 2's frame
   B00100010,
   B00000010,
   B00000100,
   B00001000,
   B00010000,
   B00111110,
   B00000000
};

byte number3[] =
{
   B00111110,  // number 2's frame
   B00000010,
   B00000100,
   B00001100,
   B00000010,
   B00100010,
   B00011100,
   B00000000
};

byte number4[] =
{
   B00000100,  // number 2's frame
   B00001100,
   B00010100,
   B00100100,
   B00111110,
   B00000100,
   B00000100,
   B00000000
};

void setNumberOne()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,number1[i]);
  }
}

void setNumberTwo()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,number2[i]);
  }
}

void setNumberThree()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,number3[i]);
  }
}

void setNumberFour()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,number4[i]);
  }
}

//Base Data

void initMatrixLed() {
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays
}

void initGroveDisplay(){
  display.setBrightness(7);
  display.clear();
}

void initLCD(){
  lcd.init();                    
  lcd.backlight();
  lcd.clear();
}

void pushOnScreen(int x){
  if (x==1)setNumberOne();
  else if (x==2)setNumberTwo();
  else if (x==3)setNumberThree();
  else setNumberFour();
}

int checkPressed(){
  while (true){
    if (digitalRead(button1)==HIGH){
      return 1;
    }
    else if (digitalRead(button2)==HIGH){
      return 2;
    }
    else if (digitalRead(button3)==HIGH){
      return 3;
    }
    else if (digitalRead(button4)==HIGH){
      return 4;
    }
  }
}

bool stage1(){

    /*init for each stage*/
 
    initLCD();
    initButton();
    lcd.setCursor(5,0);
    lcd.print("Stage 1");
    int onScreen=random(1,5);
    pushOnScreen(onScreen);
    int buttonPressed=checkPressed();
    posButtonStage[1]=buttonPressed;
    labelButtonStage[1]=button[buttonPressed];

    /*init for each stage*/

    if (
        (onScreen==1 && buttonPressed==2)
        ||(onScreen==2 && buttonPressed==2)
        || (onScreen==3 && buttonPressed==3)
        || (onScreen==4 && buttonPressed==4)
        )
        {
            return true;
        }
    else {
        lcd.setCursor(5,1);
        lcd.print("WRONG!");
        return false;
    }
}

void stage2(){
    /*init for each stage*/
    initLCD();
    initButton();
    lcd.setCursor(5,0);
    lcd.print("Stage 2");
    int onScreen=random(1,5);
    pushOnScreen(onScreen);
    int buttonPressed=checkPressed();
    posButtonStage[2]=buttonPressed;
    labelButtonStage[2]=button[buttonPressed];
    if (
        (onScreen==1 && button[buttonPressed]==4)
        ||(onScreen==2 && buttonPressed==posButtonStage[1])
        || (onScreen==3 && buttonPressed==1)
        || (onScreen==4 && buttonPressed==posButtonStage[1])
        )
        {
            stage3();
        }
    else {
        lcd.setCursor(5,1);
        lcd.print("WRONG!");
    } 
}

void stage3(){
    /*init for each stage*/
 
    initLCD();
    initButton();
    lcd.setCursor(5,0);
    lcd.print("Stage 3");
    int onScreen=random(1,5);
    pushOnScreen(onScreen);
    int buttonPressed=checkPressed();
    posButtonStage[3]=buttonPressed;
    labelButtonStage[3]=button[buttonPressed];
    
    /*init for each stage*/
    if (
        (onScreen==1 && button[buttonPressed]==labelButtonStage[2])
        ||(onScreen==2 && button[buttonPressed]==labelButtonStage[1])
        || (onScreen==3 && buttonPressed==3)
        || (onScreen==4 && button[buttonPressed]==4)
        )
        {
            stage4();
        }
    else {
        lcd.setCursor(5,1);
        lcd.print("WRONG!");
    } 
}

void stage4(){
    /*init for each stage*/
 
    initLCD();
    initButton();
    lcd.setCursor(5,0);
    lcd.print("Stage 4");
    int onScreen=random(1,5);
    pushOnScreen(onScreen);
    int buttonPressed=checkPressed();
    posButtonStage[4]=buttonPressed;
    labelButtonStage[4]=button[buttonPressed];
    
    /*init for each stage*/
    if (
        (onScreen==1 && buttonPressed==posButtonStage[1])
        ||(onScreen==2 && buttonPressed==1)
        || (onScreen==3 && buttonPressed==posButtonStage[2])
        || (onScreen==4 && buttonPressed==posButtonStage[2])
        )
        {
            stage5();
        }
    else {
        lcd.setCursor(5,1);
        lcd.print("WRONG!");
    } 
}
void stage5(){
    /*init for each stage*/
 
    initLCD();
    initButton();
    lcd.setCursor(5,0);
    lcd.print("Stage 5");
    int onScreen=random(1,5);
    pushOnScreen(onScreen);
    int buttonPressed=checkPressed();
    posButtonStage[4]=buttonPressed;
    labelButtonStage[4]=button[buttonPressed];
    
    /*init for each stage*/
    if (
        (onScreen==1 && button[buttonPressed]==labelButtonStage[1])
        ||(onScreen==2 && button[buttonPressed]==labelButtonStage[2])
        || (onScreen==3 && button[buttonPressed]==labelButtonStage[4])
        || (onScreen==4 && button[buttonPressed]==labelButtonStage[3])
        )
        {
            initLCD();
            lcd.setCursor(3,0);
            lcd.print("You've won");
        }
    else {
        lcd.setCursor(5,1);
        lcd.print("WRONG!");
    } 
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  initMatrixLed();
  initGroveDisplay();
  initLCD();
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
}


void loop() {
  if (stage1()==true)stage2();
}
