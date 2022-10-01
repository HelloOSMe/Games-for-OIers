/*
ClearMind
控制台扫雷游戏
支持Windows/Linux
By HelloOS
*/
/*
Clear Mind
扫雷游戏
版本：v1.0.1
上一版本：v1.0.0
*/
/**更新历史记录**
### 记号：
* (N)-normal 正常更新
* (S)-special 特别更新
* (W)-warning 紧急更新
### 记录
类型|时间    |内容
----|--------|---------------
(N) |20220818|UI更新
*/
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int bombs=0,AllBombs=0;
int flag=0;
int bx=-1,by=-1;
#if defined(_WIN32)||defined(_WIN64)
#include<windows.h>
#define ST SetConsoleTitle("扫雷")
#include<conio.h>
#define pause system("pause")
#define cls system("cls")
#define WIN
HANDLE handle;
void light(string str){
    SetConsoleTextAttribute(handle,240);
    cout<<str;
    SetConsoleTextAttribute(handle,7);
}
void red(string str){
    SetConsoleTextAttribute(handle,4*16+15);
    cout<<str;
    SetConsoleTextAttribute(handle,7);
}
void cyan(string str){
    SetConsoleTextAttribute(handle,11);
    cout<<str;
    SetConsoleTextAttribute(handle,7);
}
void green(string str){
    SetConsoleTextAttribute(handle,160);
    cout<<str;
    SetConsoleTextAttribute(handle,7);
}
void flagcolor(int flagnum){
    SetConsoleTextAttribute(handle,159);
    cout<<' ';
    if(flagnum<10){
        cout<<' ';
    }
    cout<<flagnum;
    SetConsoleTextAttribute(handle,7);
}
void flagcolor2(int flagnum){
    SetConsoleTextAttribute(handle,159);
    if(flagnum<10){
        cout<<' ';
    }
    cout<<flagnum;
    SetConsoleTextAttribute(handle,7);
}
void goto00(){
    COORD coord={0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
#else
void NULLS(){
    
}
#define ST NULLS()
void light(string str){
    cout<<"\033[47;1m"<<str<<"\033[000m";
}
void red(string str){
    cout<<"\033[41;1m"<<str<<"\033[000m";
}
void cyan(string str){
    cout<<"\033[36;1m"<<str<<"\033[000m";
}
void green(string str){
    cout<<"\033[42;1m"<<str<<"\033[000m";
}
void flagcolor(int flagnum){
    cout<<"\033[44;1m";
    cout<<' ';
    if(flagnum<10){
        cout<<' ';
    }
    cout<<flagnum<<"\033[000m";
}
void flagcolor2(int flagnum){
    cout<<"\033[44;1m";
    if(flagnum<10){
        cout<<' ';
    }
    cout<<flagnum<<"\033[000m";
}
void Sleep(int i){
    usleep(i*1000);
}
char getch(){
    char ch;
    system("stty -icanon");//关闭终端缓冲区
    system("stty -echo");
    scanf("%c",&ch);
    system("stty icanon");//打开终端缓冲区
    system("stty echo");
    return ch;
}
void LinuxPause(){
    cout<<"请按Enter键继续...";
    system("read anykey");
}
void goto00(){
	cout<<"\033[0,0H";
}
#define pause LinuxPause()
#define cls system("clear")
#endif
char map1[50][50];
char map2[50][50];
int x,y;
void InputXY(){
    char c,c2[2];
    while(true){
        cls;
        cout<<"Choose the size:"<<endl;
        cout<<"[1]10*10 [2]20*20 [3]50*50 [4]Other"<<endl;
        cout<<">>> ";
        cin>>c;
        if(c=='1'){
            x=10;
            y=10;
            #ifdef WIN
            system("mode con cols=43 lines=28");
            #endif
            return;
        }else if(c=='2'){
            x=20;
            y=20;
            #ifdef WIN
            system("mode con cols=83 lines=49");
            #endif
            return;
        }else if(c=='3'){
            x=50;
            y=50;
            #ifdef WIN
            system("mode con cols=203 lines=109");
            #endif
            return;
        }else{
            char cmd[1000]={'\0'};
            while(true){
                cls;
                cout<<"X>> ";
                cin>>c2;
                if(c2[1]=='\0'){
                    x=c2[0]-48;
                }else{
                    x=(c2[0]-48)*10+c2[1]-48;
                }
                cout<<"Y>> ";
                cin>>c2;
                if(c2[1]=='\0'){
                    y=c2[0]-48;
                }else{
                    y=(c2[0]-48)*10+c2[1]-48;
                }
                sprintf(cmd,"mode con cols=%d lines=%d",(y*4+3<36?36:y*4+3),x*2+9);
                if(x>50||y>50){
                    cout<<"Error:The number is too long.";
                }else if(x!=y){
                    cout<<"X≠Y!Do you want to use it?[y/n]"<<endl;
                    cin>>c;
                    if(c=='y'||c=='Y'){
                        #ifdef WIN
                        system(cmd);
                        #endif
                        return;
                    }
                }else{
                    #ifdef WIN
                    system(cmd);
                    #endif
                    return;
                }
            }
        }
    }
}
void MakeMap(){
    int z,num=0;
    srand(time(NULL));
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            z=rand()%7;
            //让雷变得稀疏
            if(z==0){
                map1[i][j]='*';
                bombs++;
                flag++;
                AllBombs++;
            }else{
                map1[i][j]=' ';
            }
            map2[i][j]='#';
        }
    }
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            num=0;
            if(map1[i][j]=='*'){
                continue;
            }
            if(map1[i+1][j]=='*'){
                num++;
            }if(map1[i-1][j]=='*'){
                num++;
            }if(map1[i][j+1]=='*'){
                num++;
            }if(map1[i][j-1]=='*'){
                num++;
            }if(map1[i-1][j-1]=='*'){
                num++;
            }if(map1[i+1][j-1]=='*'){
                num++;
            }if(map1[i-1][j+1]=='*'){
                num++;
            }if(map1[i+1][j+1]=='*'){
                num++;
            }
            map1[i][j]=(char)(num+'0');
            if(map1[i][j]=='0'){
                map1[i][j]=' ';
            }
        }
    }
}
void ShowMap(){
    cout<<"雷的数量:"<<AllBombs<<"   旗子数量:"<<flag<<endl;
    cout<<"  |";
    for(int j=0;j<y;j++){
        flagcolor(j+1);
        cout<<'|';
    }
    cout<<"\n--|";
    for(int j=0;j<y;j++){
        cout<<"---|";
    }
    cout<<endl;
    for(int i=0;i<x;i++){
        flagcolor2(i+1);
        cout<<"|";
        for(int j=0;j<y;j++){
            if(map2[i][j]==' '){
                cout<<' ';
                cout<<map1[i][j];
                cout<<' ';
            }else if(map2[i][j]=='+'){
                cyan(" + ");
            }else{
                light("   ");
            }
            cout<<"|";
        }
        cout<<endl<<"--|";
        for(int j=0;j<y;j++){
            cout<<"---|";
        }
        cout<<endl;
    }
}
void OverShowMap(){
    cout<<"  |";
    for(int j=0;j<y;j++){
        flagcolor(j+1);
        cout<<'|';
    }
    cout<<"\n--|";
    for(int j=0;j<y;j++){
        cout<<"---|";
    }
    cout<<endl;
    for(int i=0;i<x;i++){
        flagcolor2(i+1);
        cout<<"|";
        for(int j=0;j<y;j++){
            if(map2[i][j]==' '||map1[i][j]=='*'){
                if(i==bx&&j==by){
                    red(" * ");
                }else if(map2[i][j]=='+'){
                    green(" + ");
                }else{
                    cout<<' ';
                    cout<<map1[i][j];
                    cout<<' ';
                }
            }else if(map2[i][j]=='+'){
                cyan(" + ");
            }else{
                light("   ");
            }
            cout<<"|";
        }
        cout<<endl<<"--|";
        for(int j=0;j<y;j++){
            cout<<"---|";
        }
        cout<<endl;
    }
}
void hello(){
    cout<<"   +-----------------+"<<endl;
    cout<<"   |             -[]X|"<<endl;
    cout<<"   |-----------------|"<<endl;
    cout<<"   | C:\\>_           |"<<endl;
    cout<<"   |       扫雷      |"<<endl;
    cout<<"   |   Clear  Mind   |"<<endl;
    cout<<"   +-----------------+"<<endl;
    cout<<"Copyright (c) 2022 HelloOS"<<endl;
    Sleep(1800);
    cls;
}
void gz(){
    cout<<"========================="<<endl;
    cout<<"|        符号提示       |"<<endl;
    cout<<"|     *   雷            |"<<endl;
    cout<<"|     +   旗子          |"<<endl;
    cout<<"|     1-9 周围的雷数量  |"<<endl;
    cout<<"|                       |"<<endl;
    cout<<"========================="<<endl;
    pause;
}
void if_isspace(int xx,int yy){
    if(map1[xx][yy]==' '){
        //cout<<1<<endl;;
        for(int i=xx-1;i<=xx+1;i++){
            for(int j=yy-1;j<=yy+1;j++){
                if(map2[i][j]==' '){
                    continue;
                }
                map2[i][j]=' ';
                if(map1[i][j]==' '){
                    //cout<<2;
                    //getch();
                    if_isspace(i,j);
                }
                //cout<<3;
            }
            //cout<<endl;
        }
    }
}
int main(){
    #ifdef WIN
    system("mode con cols=36 lines=10");
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    ST;
    hello();
    gz();
    InputXY();
    MakeMap();
    int X,Y,b;
    while(true){
        //goto00();
        cls;
        ShowMap();
        if(bombs==0){
            #ifdef WIN
            MessageBox(GetForegroundWindow(),"你赢了!                    ","扫雷-赢",MB_OK);
            #else
            cout<<"WINNER!\n";
            pause;
            #endif
            exit(0);
        }
        cout<<"输入格子的行列以及翻开(0)还是标记(1)"<<endl;
        cout<<"例子：5 5 0    翻开格子(5,5)"<<endl;
        cout<<">>> ";
        cin>>X>>Y>>b;
        if(X<1||Y<1||X>50||Y>50){
            cout<<"Error";
            Sleep(1000);
            continue;
        }
        if(b==0){
        	if(map2[X-1][Y-1]=='+'){
        		flag++;
			} 
            map2[X-1][Y-1]=' ';
            if(map1[X-1][Y-1]==' ')
                if_isspace(X-1,Y-1);
        }else if(flag!=0){
            flag--;
            map2[X-1][Y-1]='+';
        }
        if(map1[X-1][Y-1]=='*'&&map2[X-1][Y-1]==' '){
            cls;
            bx=X-1;
            by=Y-1;
            cout<<"GameOver!"<<endl;
            OverShowMap();
            pause;
            exit(0);
        }
        if(map1[X-1][Y-1]=='*'&&map2[X-1][Y-1]=='+'){
            bombs--;
        }
        if(flag==0&&bombs!=0){
            cls;
            cout<<"GameOver!"<<endl;
            OverShowMap();
            pause;
            exit(0);
        }
        //cout<<map2[X-1][Y-1];
        //Sleep(3000);
    }
    return 0;
}

