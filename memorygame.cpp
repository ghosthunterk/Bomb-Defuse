#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

vector<int> dButton(6);
vector<int> button(6);
vector<int> buttonStage(6);
vector<int> labelStage(6);

int position(int a){
    for (int i=1;i<=4;i++){
        if (button[i]==a)return i;
    }
}

void initButton(){
    dButton.clear();
    dButton.assign(6,0);
    button.clear();
    for (int i=1;i<=4;i++){
        int t=1+(rand()%4);
        if (dButton[t]==0){
            button[i]=t;
            dButton[t]++;
        }
        else {
            while(dButton[t]==1){
                t=1+(rand()%4);
            }
            button[i]=t;
            dButton[t]++;
        }
    }
    cout<<"The four buttons are: "<<endl<<endl;
    for (int i=1;i<=4;i++)cout<<button[i]<<"   ";
    cout<<endl<<endl;
}


bool stage1(){

    /*init for each stage*/
    cout<<endl;
    cout<<"Stage 1: "<<endl;
    initButton();
    int lcd=1+(rand()%4);
    cout<<"LCD: "<<lcd<<endl;
    int buttonPressed;
    cout<<"Button Pressed: ";
    cin>>buttonPressed;
    cout<<endl;
    buttonStage[1]=position(buttonPressed);
    labelStage[1]=buttonPressed;

    /*init for each stage*/

    if (
        (lcd==1 && buttonPressed==button[2])
        ||(lcd==2 && buttonPressed==button[2])
        || (lcd==3) && (buttonPressed==button[3])
        || (lcd==4) && (buttonPressed==button[4])
        )
        {
            return true;
        }
    else {
        cout<<"WRONG!!!"<<endl;
        return false;
    }
}
void stage5(){

    /*init for each stage*/

    cout<<"Stage 5: "<<endl;
    initButton();
    int lcd=1+(rand()%4);
    cout<<"LCD: "<<lcd<<endl;
    int buttonPressed;
    cout<<"Button Pressed: ";
    cin>>buttonPressed;
    cout<<endl;

    /*init for each stage*/

    if (
        (lcd==1 && buttonPressed==labelStage[1])
        ||(lcd==2 && buttonPressed==labelStage[2])
        || (lcd==3 && buttonPressed==labelStage[4])
        || (lcd==4 && buttonPressed==labelStage[3])
        )
        {
            cout<<"CONGRATULATE ON WINNING";
            exit(0);
        }
    else {
        cout<<"WRONG!!!"<<endl;
        stage1();
    }
}
void stage4(){

    /*init for each stage*/

    cout<<"Stage 4: "<<endl;
    initButton();
    int lcd=1+(rand()%4);
    cout<<"LCD: "<<lcd<<endl;
    int buttonPressed;
    cout<<"Button Pressed: ";
    cin>>buttonPressed;
    cout<<endl;
    buttonStage[4]=position(buttonPressed);
    labelStage[4]=buttonPressed;

    /*init for each stage*/

    if (
        (lcd==1 && position(buttonPressed)==buttonStage[1])
        ||(lcd==2 && buttonPressed==button[1])
        || (lcd==3 && position(buttonPressed)==buttonStage[2])
        || (lcd==4 && position(buttonPressed)==buttonStage[2])
        )
        {
            stage5();
        }
    else {
        cout<<"WRONG!!!"<<endl;
        stage1();
    }
}
void stage3(){

    /*init for each stage*/

    cout<<"Stage 3: "<<endl;
    initButton();
    int lcd=1+(rand()%4);
    cout<<"LCD: "<<lcd<<endl;
    int buttonPressed;
    cout<<"Button Pressed: ";
    cin>>buttonPressed;
    cout<<endl;
    buttonStage[3]=position(buttonPressed);
    labelStage[3]=buttonPressed;

    /*init for each stage*/

    if (
        (lcd==1 && buttonPressed==labelStage[2])
        ||(lcd==2 && buttonPressed==labelStage[1])
        || (lcd==3 && buttonPressed==button[3])
        || (lcd==4 && buttonPressed==4)
        )
        {
            stage4();
        }
    else {
        cout<<"WRONG!!!"<<endl;
        stage1();
    }
}
void stage2(){

    /*init for each stage*/

    cout<<"Stage 2: "<<endl;
    initButton();
    int lcd=1+(rand()%4);
    cout<<"LCD: "<<lcd<<endl;
    int buttonPressed;
    cout<<"Button Pressed: ";
    cin>>buttonPressed;
    cout<<endl;
    buttonStage[2]=position(buttonPressed);
    labelStage[2]=buttonPressed;

    /*init for each stage*/

    if (
        (lcd==1 && buttonPressed==4)
        ||(lcd==2 && position(buttonPressed)==buttonStage[1])
        || (lcd==3 && buttonPressed==button[1])
        || (lcd==4 && position(buttonPressed)==buttonStage[1])
        )
        {
            stage3();
        }
    else {
        cout<<"WRONG!!!"<<endl;
        stage1();
    }
}


int main()
{
    srand(time(0)); //use this and rand() won't go bullsh*t
    while (true){
        if (stage1()){
            stage2();
        }
    }
}
