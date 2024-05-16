#include<iostream>

using namespace std;

typedef struct{
    int tp;     // 0:空地 1:墙 2:出口 3:入口
    int state;  // 0:未探索 1:已探索
} Node;

int goOutTheMaze(Node* map,int weight,int height,int startX,int startY);

int main(){
    int width, height;
    int startX, startY;
    int endX, endY;
    
    //获取迷宫大小信息
    cout<<"Let's go out the maze!"<<endl;
    cout<<"Please input the size of the maze:"<<endl;
    cin>>width>>height;
    Node map[width][height];

    //获取迷宫地形信息
    cout<<"Please input the maze's terrain:"<<endl;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            cin>>map[i][j].tp;          //设置迷宫地形
            map[i][j].state=0;         //初始化状态为未探索
            switch(map[i][j].tp){       //单独记录一下出入口的坐标
                case 2:
                    endX=i;
                    endY=j;
                    break;
                case 3:
                    startX=i;
                    startY=j;
                    break;
                default:
                    break;
            }
        }
    }

    cout<<"Successfully input the maze's terrain!"<<endl;
    cout<<"Exploring the maze..."<<endl;

    //走出迷宫
    int result=goOutTheMaze(&map[startX][startY],width,height,startX,startY);
    cout<<"Exploration complete!"<<endl;
    //返回走出结果，是否成功走出（有无出去的路）
    if(result)cout<<"We have found the exit!"<<endl;
    else cout<<"We have not found the exit!"<<endl;
    
    return 0;
}

int goOutTheMaze(Node* now,int weight,int height,int startX,int startY){
    //初始化起点坐标，显示当前位置
    int nowX=startX;
    int nowY=startY;
    cout<<"Now at ("<<nowX<<","<<nowY<<")"<<endl;
    //如果已经探索过该地方
    if(now->state==1){
        cout<<"This place has been explored."<<endl;
        return 0;
    }
    //如果撞墙（当下所在地就是墙）
    if(nowX<0 || nowX>=weight || nowY<0 || nowY>=height || now->tp==1){
        cout<<"This place is a wall."<<endl;
        return 0;
    }
    //如果已经到达出口
    if(now->tp==2){
        cout<<"This is the exit."<<endl;
        return 1;   
    }
    //标记当前坐标已探索
    now->state=1;
    cout<<"This place is legal. I've marked it as explored."<<endl;
    //尝试四个方向
    cout<<"Going to the right..."<<endl;
    if(goOutTheMaze(now+1,weight,height,nowX+1,nowY))return 1;
    cout<<"Going to the left..."<<endl;
    if(goOutTheMaze(now-1,weight,height,nowX-1,nowY))return 1;
    cout<<"Going up..."<<endl;
    if(goOutTheMaze(now+weight,weight,height,nowX,nowY+1))return 1;
    cout<<"Going down..."<<endl;
    if(goOutTheMaze(now-weight,weight,height,nowX,nowY-1))return 1;
    //否则返回0
    cout<<"There is no way."<<endl;
    return 0;
}