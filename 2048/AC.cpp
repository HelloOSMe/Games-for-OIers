#include<bits/stdc++.h>
#include<unistd.h>
int winnum=2048;
#if defined(_WIN32)||defined(_WIN64)
#include<conio.h>
#include<windows.h>
#define cls system("cls")
#define syspau() system("pause")
void goto00() {
    COORD coord = {0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else
#define cls cout<<"\033c"
char getch(void){
    char ch;
    system("stty -icanon");//关闭终端缓冲区
    system("stty -echo");
    ch=getchar();
    system("stty icanon");//打开终端缓冲区
    system("stty echo");
    return ch;
}
void Sleep(int a){
    usleep(a*1000);
}
void syspau(){
    std::cout<<"请按enter键继续...";
    system("read anykey");
}
#endif
using namespace std;
//2048插件-AC
//把这个东西放到using namespace std;后，改一下显示函数printscreen就行！
#if defined(_WIN32)||defined(_WIN64)
void pri(int n){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    switch(n){
        case 2:
            SetConsoleTextAttribute(handle,111);
            cout<<" CE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 4:
            SetConsoleTextAttribute(handle,176);
            cout<<"???";
            SetConsoleTextAttribute(handle,7);
            break;
        case 8:
            SetConsoleTextAttribute(handle,95);
            cout<<" RE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 16:
            SetConsoleTextAttribute(handle,159);
            cout<<"TLE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 32:
            SetConsoleTextAttribute(handle,159);
            cout<<"MLE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 64:
            SetConsoleTextAttribute(handle,158);
            cout<<"ILE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 128:
            SetConsoleTextAttribute(handle,159);
            cout<<"OLE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 256:
            SetConsoleTextAttribute(handle,31);
            cout<<"UKE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 512:
            SetConsoleTextAttribute(handle,207);
            cout<<" WA";
            SetConsoleTextAttribute(handle,7);
            break;
        case 1024:
            SetConsoleTextAttribute(handle,224);
            cout<<" PE";
            SetConsoleTextAttribute(handle,7);
            break;
        case 2048:
            SetConsoleTextAttribute(handle,47);
            cout<<" AC";
            SetConsoleTextAttribute(handle,7);
            break;
    }
}
#else
void pri(int n){
    switch(n){
        case 2:
            cout<<"\033[43;1m";
            cout<<" CE";
            cout<<"\033[000m";
            break;
        case 4:
            cout<<"\033[46;1m";
            cout<<"???";
            cout<<"\033[000m";
            break;
        case 8:
            cout<<"\033[45;1m";
            cout<<" RE";
            cout<<"\033[000m";
            break;
        case 16:
            cout<<"\033[44;1m";
            cout<<"TLE";
            cout<<"\033[000m";
            break;
        case 32:
            cout<<"\033[44;1m";
            cout<<"MLE";
            cout<<"\033[000m";
            break;
        case 64:
            cout<<"\033[44;1m";
            cout<<"ILE";
            cout<<"\033[000m";
            break;
        case 128:
            cout<<"\033[44;1m";
            cout<<"OLE";
            cout<<"\033[000m";
            break;
        case 256:
            cout<<"\033[40;1m";
            cout<<"UKE";
            cout<<"\033[000m";
            break;
        case 512:
            cout<<"\033[41;1m";
            cout<<" WA";
            cout<<"\033[000m";
            break;
        case 1024:
            cout<<"\033[43;30m";
            cout<<" PE";
            cout<<"\033[000m";
            break;
        case 2048:
            cout<<"\033[42;1m";
            cout<<" AC";
            cout<<"\033[000m";
            break;
    }
}
#endif
const int n=4;
int m[n+1][n+1]={0};
int ax,ay;
bool init(int x,int y){
    return x>=0&&x<n&&y>=0&&y<n;
}
bool have_space(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[i][j]==0){
                return 1;
            }
        }
    }
    return 0;
}
void printscreen(){
    cout<<"|";
    for(int j=0;j<4;++j){
        cout<<"---|";
    }
    cout<<endl;
    for(int i=0;i<n;++i){
        cout<<'|';
        for(int j=0;j<n;++j){
            if(m[i][j]==0){
                cout<<"   |";
            }else{
                pri(m[i][j]);
                cout<<'|'; 
            }
        }
        cout<<endl<<"|";
        for(int j=0;j<4;++j){
            cout<<"---|";
        }
        cout<<endl;
    }
}
void makenum(){
    if(!have_space()){
        return;
    }
    srand(time(NULL));
    int b=rand()%10;
    if(b==4){
        b=2;
    }else{
        b=1;
    }
    int x,y,num=rand()%10;
    while(b>0&&have_space()){
        x=rand()%4;
        y=rand()%4;
        if(m[x][y]==0&&have_space()){
            m[x][y]=(num==0?4:2);
            ax=x;
            ay=y;
            b--;
        }
    }
}
void move_up(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[i][j]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x-1,y)&&m[x-1][y]==0){
                    m[x-1][y]=m[x][y];
                    m[x][y]=0;
                    x--;
                }
            }
        }
    }//抹空格
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(init(i+1,j)&&init(i,j)&&m[i][j]!=0){
                if(m[i][j]==m[i+1][j]){
                    m[i][j]=m[i][j]*2;
                    m[i+1][j]=0;
                }
            }
        }
    }//加法
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[i][j]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x-1,y)&&m[x-1][y]==0){
                    m[x-1][y]=m[x][y];
                    m[x][y]=0;
                    x--;
                }
            }
        }
    }//抹空格
}
void move_down(){
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[i][j]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x+1,y)&&m[x+1][y]==0){
                    m[x+1][y]=m[x][y];
                    m[x][y]=0;
                    x++;
                }
            }
        }
    }//抹空格
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(init(i-1,j)&&init(i,j)&&m[i][j]!=0){
                if(m[i][j]==m[i-1][j]){
                    m[i][j]=m[i][j]*2;
                    m[i-1][j]=0;
                }
            }
        }
    }//加法
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[i][j]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x+1,y)&&m[x+1][y]==0){
                    m[x+1][y]=m[x][y];
                    m[x][y]=0;
                    x++;
                }
            }
        }
    }//抹空格
}
void move_left(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[j][i]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x-1,y)&&m[y][x-1]==0){
                    m[y][x-1]=m[y][x];
                    m[y][x]=0;
                    x--;
                }
            }
        }
    }//抹空格
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(init(i+1,j)&&init(i,j)&&m[j][i]!=0){
                if(m[j][i]==m[j][i+1]){
                    m[j][i]=m[j][i]*2;
                    m[j][i+1]=0;
                }
            }
        }
    }//加法
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[j][i]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x-1,y)&&m[y][x-1]==0){
                    m[y][x-1]=m[y][x];
                    m[y][x]=0;
                    x--;
                }
            }
        }
    }//抹空格
}
void move_right(){
    bool f=0;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[j][i]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x+1,y)&&m[y][x+1]==0){
                    m[y][x+1]=m[y][x];
                    m[y][x]=0;
                    x++;
                }
            }
        }
    }//抹空格
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(init(i-1,j)&&init(i,j)&&m[j][i]!=0){
                if(m[j][i]==m[j][i-1]){
                    m[j][i]=m[j][i]*2;
                    m[j][i-1]=0;
                }
            }
        }
    }//加法
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[j][i]!=0){
                int x=i,y=j;
                while(init(x,y)&&init(x+1,y)&&m[y][x+1]==0){
                    m[y][x+1]=m[y][x];
                    m[y][x]=0;
                    x++;
                }
            }
        }
    }//抹空格
}
bool can_move_up(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[i][j]==0){
                return 1;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(init(i+1,j)&&init(i,j)&&m[i][j]!=0){
                if(m[i][j]==m[i+1][j]){
                    return 1;
                }
            }
        }
    }
    return 0;
}
bool can_move_down(){
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[i][j]==0){
                return 1;
            }
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(init(i-1,j)&&init(i,j)&&m[i][j]!=0){
                if(m[i][j]==m[i-1][j]){
                    return 1;
                }
            }
        }
    }
    return 0;
}
bool can_move_left(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[j][i]==0){
                return 1;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(init(i+1,j)&&init(i,j)&&m[j][i]!=0){
                if(m[j][i]==m[j][i+1]){
                    return 1;
                }
            }
        }
    }
    return 0;
}
bool can_move_right(){
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(m[j][i]==0){
                return 1;
            }
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(init(i-1,j)&&init(i,j)&&m[j][i]!=0){
                if(m[j][i]==m[j][i-1]){
                    return 1;
                }
            }
        }
    }
    return 0;
}
void warning(){
    cout<<"============================="<<endl;
    cout<<"|         2048 Game         |"<<endl;
    cout<<"|                           |"<<endl;
    cout<<"|请用WASD/方向键控制加法方向|"<<endl;
    cout<<"|                           |"<<endl;
    cout<<"|Copyright (c) 2022 HelloOS |"<<endl;
    cout<<"============================="<<endl;
}
bool win(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(m[i][j]==winnum){
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    #ifdef WIN
    system("mode con cols=30 lines=10");
    #endif
    warning();
    Sleep(2000);
    cls;
    #ifdef WIN
    system("mode con cols=18 lines=8");
    #endif
    char ch;
    while(true){
        goto00();
        //cls;
        printscreen();
       if(can_move_up()||can_move_down()||can_move_left()||can_move_right()){
            if(win()){
                cout<<"Winner!"<<endl;
                syspau();
                exit(0);
            }
        }else{
            cout<<"Failed!"<<endl;
            syspau();
            exit(0);
        }
        ch=getch();
        switch(ch){
            case 72:case 'w':case 'W':
                if(can_move_up()){
                    move_up();
                    makenum();
                }
                break;
            case 80:case 's':case 'S':
                if(can_move_down()){
                    move_down();
                    makenum();
                }
                break;
            case 75:case 'a':case 'A':
                if(can_move_left()){
                    move_left();
                    makenum();
                }
                break;
            case 77:case 'd':case 'D':
                if(can_move_right()){
                    move_right();
                    makenum();
                }
                break;
        }
    }
    return 0;
}

