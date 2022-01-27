#ifndef TEST_H
#define TEST_H

#include <QtGui>
#include <QMessageBox>
#include <QLabel>

class RasterWindow : public QWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = nullptr);

    virtual void render(QPainter *painter);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private:
    QBackingStore *m_backingStore;
};


struct Point//代替QPoint
{
    int x,y;
    Point(int X=0,int Y=0)
    {
        x=X;
        y=Y;
    }
};

class Snake
{
private:
    int length=3;
    Point *p=new Point[length];
    int v=10;
    //tail就是p[length-1]->x或者y
    //head也不直接写出来
    bool alive=true;
public:
    Snake()//初始化的位置
    {
        p[0].x=0;p[0].y=0;
        for(int i=1;i<length;i++)
        {
            p[i].x=p[i-1].x-10;
        }
    }
    int getX(int k)
    {
        return p[k].x;
    }
    int getY(int k)
    {
        return p[k].y;
    }
    int getlength()
    {
        return length;
    }
    Point* gethead()
    {
        return p;
    }
    void moveup()
    {

        for(int i=length-1;i>0;i--)
        {
            p[i]=p[i-1];
        }
        p[0].y-=v;
    }
    void movedown()
    {
        for(int i=length-1;i>0;i--)
        {
            p[i]=p[i-1];
        }
        p[0].y+=v;

    }
    void moveleft()
    {
        for(int i=length-1;i>0;i--)
        {
            p[i]=p[i-1];
        }
        p[0].x-=v;

    }
    void moveright()
    {
        for(int i=length-1;i>0;i--)
        {
            p[i]=p[i-1];
        }
        p[0].x+=v;

    }
    void grow(int x,int y)
    {

        Point *tmp=p;
        p=new Point[length+1];
        for(int i=0;i<length;i++)
        {
            p[i]=tmp[i];
        }
        length++;
        Point *Tmp=new Point(x,y);
        *(p+length-1)=*Tmp;
        delete tmp;
        delete Tmp;
    }
    void setTrue()
    {
       alive=true;
    }
    void setFalse()
    {
        alive=false;
    }
    bool getBool()
    {return alive;}
    void resetposition(int x,int y)
    {
        p[0].y=y;
        for(int i=1;i<length;i++)
        {
            p[i].x=p[i-1].x-10;
            p[i].y=p[i-1].y;
        }

    }
    void reset()
    {
        length=3;
        delete[]p;
        p=new Point[length];
        p[0].x=0;p[0].y=0;
        for(int i=1;i<length;i++)
        {
            p[i].x=p[i-1].x-10;
        }
        setTrue();
    }
};

class Food
{
private:
    QColor foodColor[4]={QColor (139,134,130,191),
                         QColor (28,134,238,191),
                         QColor (139,0,0,191),
                         QColor (255,0,0,255)
                     };
    int x;
    int y;
    bool FOOD=false;
public:
    Food(int X=9999,int Y=9999)
   {
     x=X;
     y=Y;
   }//构造函数

   QColor f1(){return foodColor[0];}
   QColor f2(){return foodColor[1];}
   QColor f3(){return foodColor[2];}
   QColor f4(){return foodColor[3];}
    void changeposition(int w,int h)//这里应该还是需要把变量写进去——要求刚好是五倍
    {
    int MIN_VALUE_x= -w/10/10+1;
    int MAX_VALUE_x =w/10/10-1 ;
    x = 10*(MIN_VALUE_x + (int)MAX_VALUE_x * rand() / (RAND_MAX + 1));
    int MIN_VALUE_y = -h/10/10+1;
    int MAX_VALUE_y = h/10/10-1;
    y= 10*(MIN_VALUE_y + (int)MAX_VALUE_y * rand() / (RAND_MAX + 1));
    }

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    bool getBool()
    {
        return FOOD;
    }
    void setTrue()
    {
        FOOD=true;
    }
    void setFalse()
    {
        FOOD=false;
    }
};

class Bricks{
private:
    int length=0;
    Point *p=new Point[length];
    QColor foodColor=QColor (255, 218, 185) ;
    int x;
    int y;
public:
    Bricks(int X=9999,int Y=9999)
   {
     x=X;
     y=Y;
   }//构造函数
    void reset()
    {
        length=0;
        delete [] p;
        p=new Point[length];
        x=9999;
        y=9999;
    }
   QColor brickColor(){return foodColor;}
   int getlength()
   {
       return length;
   }

    void changeposition(int w,int h)//这里应该还是需要把变量写进去——要求刚好是五倍
    {
    int MIN_VALUE_x= -w/10/10+1;
    int MAX_VALUE_x =w/10/10-1 ;
    x = 10*(MIN_VALUE_x + (int)MAX_VALUE_x * rand() / (RAND_MAX + 1));
    int MIN_VALUE_y = -h/10/10+1;
    int MAX_VALUE_y = h/10/10-1;
    y= 10*(MIN_VALUE_y + (int)MAX_VALUE_y * rand() / (RAND_MAX + 1));
    }

    int getX(int k)
    {
        return p[k].x;
    }
    int getY(int k)
    {
        return p[k].y;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }

    void addBricks()
    {
        Point *tmp=p;
        p=new Point[length+1];
        for(int i=0;i<length;i++)
        {
            p[i]=tmp[i];
        }
        length++;
        Point *Tmp=new Point(x,y);//这里的xy就是直接它类里面的xy，我在外面调用changeposition（）检查然后直接add
        *(p+length-1)=*Tmp;
        delete tmp;
        delete Tmp;
    }

};


class Queue
{
    private:
    Point *elem;
    int maxSize;
    int front,rear;

    public:
    Queue(int size=10)
    {
        elem=new Point[size];
        maxSize=size;
        front=rear=0;
    }
    /*~Queue()
    {
        delete[]elem;
    }*/
    bool isEmpty()
    {
        return front==rear;
    }
    void enQueue(Point &x)
    {
        if((rear+1)%maxSize==front)doubleSpace();
        rear=(rear+1)%maxSize;
        elem[rear]=x;
    }
    void doubleSpace()
    {
        Point *tmp=elem;
        elem=new Point[2*maxSize];
        for(int i=1;i<=maxSize;i++)
        {
            elem[i]=tmp[(front+i)%maxSize];
        }
        front=0;rear=maxSize;
        maxSize*=2;
        delete tmp;
    }
    void deQueue()
    {
        front=(front+1)%maxSize;
    }
    Point getHead()
    {
        return elem[(front+1)%maxSize];
    }
    void reset()
    {
        front=rear=0;
    }
};


class SnakeWindow : public RasterWindow
{
public:
    SnakeWindow();//构造函数
    void SetInterval(int inter);
    //void endGame();
    void restart()
    {
        resize(1000, 1000);
        //先把蛇给初始化
        snake.reset();
        //食物也要清空
        queue.reset();
        //bricks
        bricks.reset();
        interval=500;
        m_timerId = startTimer(interval);
        predirection='r';
        direction='n';
        Score=0;
        i=0;
        N=0;
         overpassf=false;//food和spefood
         overpass=false;//food和蛇
         overpassb=false;//food和砖块
         specoverpassb=false;//specfood与砖块
         specoverpass=false;//specfood和蛇
         over=false;//砖块和蛇
          blink=0;
          n=0;//prelength
          delete[]pre;
          pre=new Point[n];
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
    char direction;
    char predirection='r';
    Point start;
    Snake snake;//这里已经实例化出来了单人模式的蛇
    Food food;//以及一般的食物？那么特殊食物需要单独考虑啊。再建一个，直接在cpp里面调整
    Queue queue;
    Food spefood;
    int interval=500;
    Bricks bricks;

     int Score=0;

     int i=0;//food的计数循环
     int N=0;//弹窗的判断
    //static bool FOOD=false;
     bool overpassf=false;//food和spefood
     bool overpass=false;//food和蛇
     bool overpassb=false;//food和砖块
     bool specoverpassb=false;//specfood与砖块
     bool specoverpass=false;//specfood和蛇
     bool over=false;//砖块和蛇
      int blink=0;
      int n=0;//prelength
      Point *pre=new Point[n];


        //clock.exec();
    //QLabel* label=new QLabel(0,Qt::SplashScreen|Qt::WindowStaysOnTopHint);
};


#endif // TEST_H
