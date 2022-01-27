#ifndef AI_H
#define AI_H
#include"test.h"
class AIWindow:public RasterWindow
{
public:
    AIWindow();//构造函数
    void SetInterval(int inter);
    //void endGame();
    //在内部实现一个自动寻路的函数
    /*void automove(int x,int y)
    {
        if(x!=snake.getX(0)&&y!=snake.getY(0))
        {
            if(direction=='u'||direction=='d')
            {
                if(x>snake.getX(0))
                {
                    direction='r';
                }
                if(x<snake.getX(0))
                {
                    direction='l';
                }
            }
            if(direction=='l'||direction=='r')
            {
                if(y>snake.getY(0))
                {
                    direction='d';
                }
                if((y<snake.getY(0)))
                {
                    direction='u';
                }
            }
        }
        if(x==snake.getX(0))
        {
            if(direction=='r'||direction=='l')
            {
                if(y>snake.getY(0))
                    direction='d';
                else {
                    direction='u';
                }
            }
            if(direction=='u')
            {
                if(y<snake.getY(0))
                    direction='u';
                else {
                    //direction='d';
                    //需要左右移动，但是也需要判断死亡与否
                }
            }
            if(direction=='d')
            {
                if(y>snake.getY(0))
                    direction='d';
                else {
                    //direction='u';
                    //需要左右移动，但是也需要判断死亡与否
                }
            }
        }
        if(y==snake.getY(0))
        {
            if(direction=='u'||direction=='d')
            {
                if(x>snake.getX(0))
                    direction='r';
                else {
                    direction='l';
                }
            }
            if(direction=='l')
            {
                if(x<snake.getX(0))
                    direction='l';
                else {
                    //direction='r';
                    //需要上下移动，但是也需要判断死亡与否
                }
            }
            if(direction=='r')
            {
                if(x>snake.getX(0))
                    direction='r';
                else {
                    //direction='l';
                    //需要上下移动，但是也需要判断死亡与否
                }
            }
        }

    }*/

    void restart()
    {
        //先把蛇给初始化
        snake.reset();
        queue.reset();

        interval=500;
        m_timerId = startTimer(interval);
        predirection='r';
        direction='r';
        i=0;
        N=0;
         overpassfai=false;//food和spefood
         overpassai=false;//food和蛇
         specoverpassai=false;//specfood和蛇
          blink=0;
          nai=0;//prelength

          delete[] preai;

          preai=new Point[nai];
          begin=0;
          C=0;
    }

protected:              //protected
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
    void keyPressEvent(QKeyEvent *e) override;
    //override和父子继承有关，在子类中重写父类

private:
    int m_timerId;
    int x;
    int y;
    char direction='r';
    char predirection='r';
    Point start;
    Snake snake;//这里已经实例化出来了单人模式的蛇
    Food food;//以及一般的食物？那么特殊食物需要单独考虑啊。再建一个，直接在cpp里面调整
    Queue queue;
    Food spefood;
    int interval=500;
    Bricks bricks;
    int begin;
    int blink=0;
     int nai=0;//prelength
     Point *preai=new Point[nai];
     int i=0;//food的计数循环
     int N=0;//弹窗的判断
     //static bool FOOD=false;
      bool overpassfai=false;//food和spefood
      bool overpassai=false;//food和蛇
      bool specoverpassai=false;//specfood和蛇
       int X,Y;
       int C=0;

};

#endif // AI_H
