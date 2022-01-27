#include"ai.h"
#include <QtGui>
#include <cstdlib>
#include "window.h"
#include <QMessageBox>
void AIWindow:: SetInterval(int inter)//方便之后的特殊道具改变刷新时间（在多人游戏的时候应该还要再改改）（比如两个show函数啊之类的）
{
    interval=inter;
}
AIWindow::AIWindow()//建立窗口//构造函数的实现
{
    setTitle("AISnake");//这个window的名字名为“SnakeWindow”
    resize(1000, 1000);  //设定大小（之后还有个函数可以自动调整）    //这两个应该是内置的函数，直接可以把框框给搞出来
    x=0;//初始位置
    y=0;
    m_timerId = startTimer(interval);//刷新interval//interval越大，刷新间隔时间越长（单位是ms）——直到killtime（）函数is called
}
void AIWindow::keyPressEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_Space)
    {
        begin=1;
    }

}

void AIWindow::timerEvent(QTimerEvent *event)//每次刷新之后应该发生的事情
{

    if ((event->timerId() == m_timerId)&&begin==1)//判断当前事件是不是我想要的触发,可能有好多个startTimer但是名字不一样
    {



        if(((snake.getX(0)-food.getX())*(snake.getX(0)-food.getX())+(snake.getY(0)-food.getY())*(snake.getY(0)-food.getY()))>((snake.getX(0)-spefood.getX())*(snake.getX(0)-spefood.getX())+(snake.getY(0)-spefood.getY())*(snake.getY(0)-spefood.getY())))
        {
            X=spefood.getX();
            Y=spefood.getY();
        }
        else{
            X=food.getX();
            Y=food.getY();
        };//确定是吃最近的那个食物

        //automove
        if(X!=snake.getX(0)&&Y!=snake.getY(0))
        {
            if(direction=='u'||direction=='d')//需要左右走
            {
                if(X>snake.getX(0))
                {
                    //死亡判定
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)+10==snake.getX(i)&&snake.getY(0)==snake.getY(i)))//右走会吃到自己
                        {direction=predirection; i=snake.getlength()-1;}//方向不用变——应当是predirection//一旦会吃到自己就退出循环，保持原样
                        else{direction='r';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='r';
                            C=1;*/
                }
                if(X<snake.getX(0))
                {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)-10==snake.getX(i)&&snake.getY(0)==snake.getY(i)))//左走吃自己
                        {direction=predirection;i=snake.getlength()-1;}
                        else{direction='l';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='l';
                            C=1;*/
                }
            }
            if((direction=='l'||direction=='r')&&C==0)
            {
                if(Y>snake.getY(0))
                {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)+10==snake.getY(i)))//下走吃自己
                        {direction=predirection;i=snake.getlength()-1;}
                        else{direction='d';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='d';
                            C=1;*/
                }
                if((Y<snake.getY(0))&&C==0)
                {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)-10==snake.getY(i)))
                        {direction=predirection;i=snake.getlength()-1;}
                        else{direction='u';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='u';
                            C=1;*/
                }
            }
        }
        if(X==snake.getX(0)&&C==0)
        {
            if(direction=='r'||direction=='l')
            {
                if(Y>snake.getY(0))
                {
                    for(int i=2;i<snake.getlength();i++)
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)+10==snake.getY(i)))//下走吃到自己
                        {
                            direction=predirection;i=snake.getlength()-1;
                        }
                        else{direction='d';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='d';
                            C=1;*/
                }
                else {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)-10==snake.getY(i)))//上走吃到自己
                        {direction=predirection;i=snake.getlength()-1;}
                        else{direction='u';}
                    }
                    predirection=direction;
                    C=1;
                    /*direction='u';
                            C=1;*/
                }
            }
            if(direction=='u'&&C==0)
            {
                if(Y<snake.getY(0))
                {
                    for(int i=2;i<snake.getlength();i++)
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)-10==snake.getY(i)))//上走自己吃自己//需要左右走
                        {
                            direction=predirection;i=snake.getlength()-1;
                            if(snake.getX(0)+10>=width()/10)//右走超出墙，那就左或者原方向即u——只有着三个，要是出不去就没了
                            {
                                for(int j=2;j<snake.getlength();j++)//自己吃自己
                                {
                                    if((snake.getX(0)-10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//左吃自己
                                    {
                                        direction=predirection;j=snake.getlength()-1;
                                    }
                                    else{
                                        direction='l';
                                    }
                                }
                                predirection=direction;
                                C=1;

                            }
                            else{//右走不出墙，那就上左右三种嘛
                                for(int j=2;j<snake.getlength();j++)
                                {
                                    if((snake.getX(0)+10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//右走吃自己
                                    {//检查一下左走吃不吃就好了
                                        direction=predirection;j=snake.getlength()-1;
                                        for(int k=2;k<snake.getlength();k++)
                                        {
                                            if((snake.getX(0)-10==snake.getX(k)&&snake.getY(0)==snake.getY(k)))//左走吃自己
                                            {
                                                direction=predirection;k=snake.getlength()-1;
                                            }
                                            else{direction='l';}
                                        }

                                    }
                                    else{direction='r';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='d';C=1;
                            }

                        }
                        else{direction='u';}
                    }
                    predirection=direction;
                    C=1;
                    //direction='u';C=1;
                }
                else {

                    //需要左右移动，但是也需要判断死亡与否
                    if(snake.getX(0)+10>=width()/10)//右走超出墙，那就左或者原方向即u——只有着三个，要是出不去就没了
                    {
                        for(int j=2;j<snake.getlength();j++)//自己吃自己
                        {
                            if((snake.getX(0)-10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//左吃自己
                            {
                                direction=predirection;j=snake.getlength()-1;
                            }
                            else{
                                direction='l';
                            }
                        }
                        predirection=direction;
                        C=1;

                    }
                    else{//右走不出墙，那就上左右三种嘛
                        for(int j=2;j<snake.getlength();j++)
                        {
                            if((snake.getX(0)+10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//右走吃自己
                            {//检查一下左走吃不吃就好了
                                direction=predirection;j=snake.getlength()-1;
                                for(int k=2;k<snake.getlength();k++)
                                {
                                    if((snake.getX(0)-10==snake.getX(k)&&snake.getY(0)==snake.getY(k)))//左走吃自己
                                    {
                                        direction=predirection;k=snake.getlength()-1;
                                    }
                                    else{direction='l';}
                                }

                            }
                            else{direction='r';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='d';C=1;
                    }
                }
            }
            if(direction=='d'&&C==0)
            {
                if(Y>snake.getY(0))
                {
                    for(int i=2;i<snake.getlength();i++)
                    {
                        if((snake.getX(0)==snake.getX(i)&&snake.getY(0)+10==snake.getY(i)))//d走自己吃自己//需要左右走
                        {
                            direction=predirection;i=snake.getlength()-1;
                            if(snake.getX(0)+10>=width()/10)//右走超出墙，那就左或者原方向即d——只有着三个，要是出不去就没了
                            {
                                for(int j=2;j<snake.getlength();j++)//自己吃自己
                                {
                                    if((snake.getX(0)-10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//左吃自己
                                    {
                                        direction=predirection;j=snake.getlength()-1;
                                    }
                                    else{
                                        direction='l';
                                    }
                                }
                                predirection=direction;
                                C=1;

                            }
                            else{//右走不出墙，那就上左右三种嘛
                                for(int j=2;j<snake.getlength();j++)
                                {
                                    if((snake.getX(0)+10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//右走吃自己
                                    {//检查一下左走吃不吃就好了
                                        direction=predirection;j=snake.getlength()-1;
                                        for(int k=2;k<snake.getlength();k++)
                                        {
                                            if((snake.getX(0)-10==snake.getX(k)&&snake.getY(0)==snake.getY(k)))//左走吃自己
                                            {
                                                direction=predirection;k=snake.getlength()-1;
                                            }
                                            else{direction='l';}
                                        }

                                    }
                                    else{direction='r';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='d';C=1;
                            }

                        }
                        else{direction='d';}
                    }
                    predirection=direction;
                    C=1;
                    //direction='d';C=1;
                }
                else {

                    //需要左右移动，但是也需要判断死亡与否
                    if(snake.getX(0)+10>=width()/10)//右走超出墙，那就左或者原方向即d——只有着三个，要是出不去就没了
                    {
                        for(int j=2;j<snake.getlength();j++)//自己吃自己
                        {
                            if((snake.getX(0)-10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//左吃自己
                            {
                                direction=predirection;j=snake.getlength()-1;
                            }
                            else{
                                direction='l';
                            }
                        }
                        predirection=direction;
                        C=1;

                    }
                    else{//右走不出墙，那就d左右三种嘛
                        for(int j=2;j<snake.getlength();j++)
                        {
                            if((snake.getX(0)+10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//右走吃自己
                            {//检查一下左走吃不吃就好了
                                direction=predirection;j=snake.getlength()-1;
                                for(int k=2;k<snake.getlength();k++)
                                {
                                    if((snake.getX(0)-10==snake.getX(k)&&snake.getY(0)==snake.getY(k)))//左走吃自己
                                    {
                                        direction=predirection;k=snake.getlength()-1;
                                    }
                                    else{direction='l';}
                                }

                            }
                            else{direction='r';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='d';C=1;
                    }
                }
            }
        }
        if(Y==snake.getY(0)&&C==0)
        {
            if(direction=='u'||direction=='d')
            {
                if(X>snake.getX(0))
                {
                    for(int j=2;j<snake.getlength();j++)//自己吃自己
                    {
                        if((snake.getX(0)+10==snake.getX(j)&&snake.getY(0)==snake.getY(j)))//右走会吃到自己
                        {direction=predirection; j=snake.getlength()-1;}//方向不用变——应当是predirection//一旦会吃到自己就退出循环，保持原样
                        else{direction='r';}
                    }
                    predirection=direction;
                    C=1;
                    //direction='r';C=1;
                }
                else {

                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)-10==snake.getX(i)&&snake.getY(0)==snake.getY(i)))//左走吃自己
                        {direction=predirection;i=snake.getlength()-1;}
                        else{direction='l';}
                    }
                    predirection=direction;
                    C=1;
                    //direction='l';C=1;

                }
            }
            if(direction=='l'&&C==0)
            {
                if(X<snake.getX(0))
                {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)-10==snake.getX(i)&&snake.getY(0)==snake.getY(i)))//左走吃自己//需要上下走
                        {
                            direction=predirection;i=snake.getlength()-1;
                            if(snake.getY(0)+10>=height()/10)//下走超出墙，那就上或者原方向即左——只有着三个，要是出不去就没了
                            {
                                for(int j=2;j<snake.getlength();j++)//自己吃自己
                                {
                                    if((snake.getX(0)==snake.getX(j)&&snake.getY(0)-10==snake.getY(j)))
                                    {direction=predirection;j=snake.getlength()-1;}
                                    else{direction='u';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='u';C=1;
                            }
                            else{//下走不出墙，那就上下左三种嘛
                                for(int j=2;j<snake.getlength();j++)
                                {
                                    if((snake.getX(0)==snake.getX(j)&&snake.getY(0)+10==snake.getY(j)))//下走吃自己
                                    {//检查一下上走吃不吃就好了
                                        direction=predirection;j=snake.getlength()-1;
                                        for(int k=2;k<snake.getlength();k++)
                                        {
                                            if((snake.getX(0)==snake.getX(k)&&snake.getY(0)+10==snake.getY(k)))//上走吃自己
                                            {
                                                direction=predirection;k=snake.getlength()-1;//保持原方向
                                            }
                                            else{direction='u';}
                                        }

                                    }
                                    else{direction='d';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='d';C=1;
                            }

                        }
                        else{direction='l';}//不吃就好
                    }
                    predirection=direction;
                    C=1;
                    //direction='l';C=1;
                }
                else {//需要上下走掉头
                    if(snake.getY(0)+10>=height()/10)//下走超出墙，那就上或者原方向即左——只有着三个，要是出不去就没了
                    {
                        for(int j=2;j<snake.getlength();j++)//自己吃自己
                        {
                            if((snake.getX(0)==snake.getX(j)&&snake.getY(0)-10==snake.getY(j)))
                            {direction=predirection;j=snake.getlength()-1;}
                            else{direction='u';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='u';C=1;
                    }
                    else{//下走不出墙，那就上下左三种嘛
                        for(int j=2;j<snake.getlength();j++)
                        {
                            if((snake.getX(0)==snake.getX(j)&&snake.getY(0)+10==snake.getY(j)))//下走吃自己
                            {//检查一下上走吃不吃就好了
                                direction=predirection;j=snake.getlength()-1;
                                for(int k=2;k<snake.getlength();k++)
                                {
                                    if((snake.getX(0)==snake.getX(k)&&snake.getY(0)+10==snake.getY(k)))//上走吃自己
                                    {
                                        direction=predirection;k=snake.getlength()-1;
                                    }
                                    else{direction='u';}
                                }

                            }
                            else{direction='d';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='d';C=1;
                    }
                }
            }
            if(direction=='r'&&C==0)
            {
                if(X>snake.getX(0))
                {
                    for(int i=2;i<snake.getlength();i++)//自己吃自己
                    {
                        if((snake.getX(0)+10==snake.getX(i)&&snake.getY(0)==snake.getY(i)))//右走会吃到自己//需要上下走
                        {
                            direction=predirection; i=snake.getlength()-1;
                            if(snake.getY(0)+10>=height()/10)//下走超出墙，那就上或者原方向即右——只有着三个，要是出不去就没了
                            {
                                for(int j=2;j<snake.getlength();j++)//自己吃自己
                                {
                                    if((snake.getX(0)==snake.getX(j)&&snake.getY(0)-10==snake.getY(j)))
                                    {direction=predirection;j=snake.getlength()-1;}
                                    else{direction='u';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='u';C=1;
                            }
                            else{//下走不出墙，那就上下右三种嘛
                                for(int j=2;j<snake.getlength();j++)
                                {
                                    if((snake.getX(0)==snake.getX(j)&&snake.getY(0)+10==snake.getY(j)))//下走吃自己
                                    {//检查一下上走吃不吃就好了
                                        direction=predirection;j=snake.getlength()-1;
                                        for(int k=2;k<snake.getlength();k++)
                                        {
                                            if((snake.getX(0)==snake.getX(k)&&snake.getY(0)+10==snake.getY(k)))//上走吃自己
                                            {
                                                direction=predirection;k=snake.getlength()-1;
                                            }
                                            else{direction='u';}
                                        }

                                    }
                                    else{direction='d';}
                                }
                                predirection=direction;
                                C=1;
                                //direction='d';C=1;
                            }

                        }//方向不用变——应当是predirection//一旦会吃到自己就退出循环，保持原样
                        else{direction='r';}
                    }
                    predirection=direction;
                    C=1;
                    //direction='r';C=1;
                }
                else {

                    if(snake.getY(0)+10>=height()/10)//下走超出墙，那就上或者原方向即右——只有着三个，要是出不去就没了
                    {
                        for(int j=2;j<snake.getlength();j++)//自己吃自己
                        {
                            if((snake.getX(0)==snake.getX(j)&&snake.getY(0)-10==snake.getY(j)))
                            {direction=predirection;j=snake.getlength()-1;}
                            else{direction='u';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='u';C=1;
                    }
                    else{//下走不出墙，那就上下右三种嘛
                        for(int j=2;j<snake.getlength();j++)
                        {
                            if((snake.getX(0)==snake.getX(j)&&snake.getY(0)+10==snake.getY(j)))//下走吃自己
                            {//检查一下上走吃不吃就好了
                                direction=predirection;j=snake.getlength()-1;
                                for(int k=2;k<snake.getlength();k++)
                                {
                                    if((snake.getX(0)==snake.getX(k)&&snake.getY(0)+10==snake.getY(k)))//上走吃自己
                                    {
                                        direction=predirection;k=snake.getlength()-1;
                                    }
                                    else{direction='u';}
                                }

                            }
                            else{direction='d';}
                        }
                        predirection=direction;
                        C=1;
                        //direction='d';C=1;
                    }
                }
            }
        }
        C=0;

        if(direction=='u')
        {
            snake.moveup();
            predirection=direction;

        }
        if(direction=='d')
        {
            snake.movedown();
            predirection=direction;
        }
        if(direction=='r')
        {
            snake.moveright();
            predirection=direction;

        }
        if(direction=='l')
        {
            snake.moveleft();
            predirection=direction;

        }

        renderLater();//画——在rendr（）函数里面判定死亡

    }
}



void AIWindow::render(QPainter *p)
{
    if(begin==1)
    {
        for(int i=0;i<snake.getlength();i++)//检查overpass//其实一开始没必要，我已经初始值设置成一个很大的数 不可能overpass
        {
            if((snake.getX(i)!=food.getX()||snake.getY(i)!=food.getY()))
            {
                overpassai=false;
            }
            else{overpassai=true;i=snake.getlength()-1;}
        };
        /*for(int i=0;i<bricks.getlength();i++)//检查overpassb//其实一开始没必要，我已经初始值设置成一个很大的数 不可能overpass
    {
        if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY()))
        {
            overpassb=false;
        }
        else{overpassb=true;}
    };
    */
        for(int i=0;i<snake.getlength();i++)//检查specoverpass
        {
            if((snake.getX(i)!=spefood.getX()||snake.getY(i)!=spefood.getY()))
            {
                specoverpassai=false;
            }
            else{specoverpassai=true;i=snake.getlength()-1;}
        };
        /*for(int i=0;i<bricks.getlength();i++)//检查specoverpassb
    {
        if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
        {
            specoverpassb=false;
        }
        else{specoverpassb=true;}
    };
    */
        /*for(int i=0;i<snake.getlength();i++)//检查over
    {
        if(snake.getX(i)!=bricks.getX()||snake.getY(i)!=bricks.getY())
        {
            over=false;
        }
        else{over=true;}
    }
    */
        //static bool alive=1;

        QColor headColor(255,20,147);
        QColor bodyColor(205,133,63);
        QColor liningColor(255,215,0);
        QColor wallColor(255, 218, 185);

        static const QPoint food1[3] ={
            QPoint(5, 5),
            QPoint(-5, 5),
            QPoint(0, -5)
        };
        static const QPoint food2[3] = {
            QPoint(5, -5),
            QPoint(-5, -5),
            QPoint(0, 5)
        };
        static const QPoint food3[6] = {
            QPoint(2, -2),
            QPoint(-2, -2),
            QPoint(-4,0),
            QPoint(-2,2),
            QPoint(2,2),
            QPoint(4,0),
        };
        static const QPoint specfood[5]={
            QPoint(0,5),
            QPoint(4,2),
            QPoint(3,-4),
            QPoint(-3,-4),
            QPoint(-4,2)
        };


        if(snake.getX(0)==food.getX() && snake.getY(0)==food.getY())//吃到了
        {
            //FOOD=false;
            food.setFalse();
            Point tmp(food.getX(),food.getY());
            queue.enQueue(tmp);
        }
        if(snake.getX(0)==spefood.getX() && snake.getY(0)==spefood.getY())//吃到了
        {
            //FOOD=false;
            spefood.setFalse();
            Point tmp(spefood.getX(),spefood.getY());
            queue.enQueue(tmp);
            int count=rand()%2;
            if(count==1){//这里就不要减速了
                //if(interval<2000)
                //this->SetInterval(interval*2);
            }
            else {
                if(interval>200)
                    this->SetInterval(interval/2);
            }
            m_timerId = startTimer(interval);
        }
        if(!queue.isEmpty()&&snake.getX(snake.getlength()-1)==queue.getHead().x && snake.getY(snake.getlength()-1)==queue.getHead().y)//grow
        {
            snake.grow(queue.getHead().x ,queue.getHead().y);
            queue.deQueue();
        }




        //死亡判定
        for(int i=2;i<snake.getlength();i++)//自己吃自己
        {
            if(snake.getX(0)==snake.getX(i)&&snake.getY(0)==snake.getY(i))
                snake.setFalse();
        }
        if(snake.getX(0)>=width()/10||snake.getX(0)<=-width()/10||snake.getY(0)>=height()/10||snake.getY(0)<=-height()/10)//超出墙
            //alive=0;
            snake.setFalse();
        //撞到砖块（不要了）
        /*
    for(int i=0;i<bricks.getlength();i++)
    {
        if(snake.gethead()->x!=bricks.getX(i)||snake.gethead()->y!=bricks.getY(i))
        {

        }
        else
        {
            snake.setFalse();
        }
    }
*/

        //

        p->setRenderHint(QPainter::Antialiasing);//反锯齿现象，让斜线更加顺滑
        p->translate(width() / 2, height() / 2);//图像移到中间
        int side = qMin(width(), height());
        p->scale(side / 200.0, side / 200.0);//保证接下来画的图和窗口大小合适

        QBrush wallbrush(wallColor);
        //画墙
        p->setPen(Qt::NoPen);
        p->setBrush(wallbrush);
        p->save();
        p->translate(width()/10,0);
        p->drawRect(-5,-height()/10,5,height()/5);
        p->translate(-width()/5,0);
        p->drawRect(0,-height()/10,5,height()/5);
        p->restore();

        p->setPen(Qt::NoPen);
        p->setBrush(wallbrush);
        p->save();
        p->translate(0,height()/10);
        p->drawRect(-width()/10,-5,width()/5,5);
        p->translate(0,-height()/5);
        p->drawRect(-width()/10,0,width()/5,5);
        p->restore();

        /*
   //砖块
    if((snake.getX(0)==food.getX() && snake.getY(0)==food.getY())||(snake.getX(0)==spefood.getX() && snake.getY(0)==spefood.getY()))//吃到了就加一块
    {

        do
        {
        bricks.changeposition(width(),height());//变出当前需要画的那个（要是变到自身无所谓）
        for(int i=0;i<snake.getlength();i++)
        {
            if((snake.getX(i)!=bricks.getX()||snake.getY(i)!=bricks.getY()))
            {
                 over=false;
            }
            else{over=true;i=snake.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
        };
        for(int i=0;i<bricks.getlength();i++)
        {
            if((food.getX()!=bricks.getX(i)||food.getY()!=bricks.getY(i)))
            {
                overpassb=false;
            }
            else{overpassb=true;i=bricks.getlength()-1;}
            if(spefood.getX()!=bricks.getX(i)||spefood.getY()!=bricks.getY(i))
            {
                specoverpassb=false;
            }
            else{overpassb=true;i=bricks.getlength()-1;}

        }
        }
        while(over||overpassb||specoverpassb);
        bricks.addBricks();
    };
    for(int i=0;i<bricks.getlength();i++)
    {
    p->setPen(Qt::NoPen);
    p->setBrush(wallbrush);
    p->save();
    p->translate(bricks.getX(i),bricks.getY(i));
    p->drawRect(-5,-5,10,10);
    p->restore();
    }
//
*/

        //不画砖块了吧就

        //下面才是画蛇
        if(snake.getBool())
        {
            p->setPen(headColor);
            p->setBrush(headColor);

            p->save();
            p->translate(snake.getX(0),snake.getY(0));
            p->drawEllipse(-5,-5,10,10);
            p->restore();

            QBrush bodybrush(bodyColor);
            QPen bodypen(liningColor,0.75);

            p->setPen(bodypen);
            p->setBrush(bodybrush);

            for(int i=1;i<snake.getlength();i++)
            {
                p->save();
                p->translate(snake.getX(i),snake.getY(i));
                p->drawRect(-5,-5,10,10);
                p->restore();
            };


            if(food.getBool()==true)//true 存在
            {
                //Printfood（i%3）
                if(i==0)
                { p->setPen(Qt::NoPen);
                    p->setBrush(food.f1());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food1, 3);
                    p->restore();
                }
                if(i==1)
                {
                    p->setPen(Qt::NoPen);
                    p->setBrush(food.f2());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food2, 3);
                    p->restore();
                }
                if(i==2)
                {
                    p->setPen(Qt::NoPen);
                    p->setBrush(food.f3());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food3, 6);
                    p->restore();
                }
            }
            else
            {
                //FOOD=true;
                food.setTrue();
                i=(i+1)%3;
                do
                {
                    food.changeposition(width(),height());
                    for(int i=0;i<snake.getlength();i++)
                    {
                        if((snake.getX(i)!=food.getX()||snake.getY(i)!=food.getY()))
                        {
                            overpassai=false;
                        }
                        else{overpassai=true;i=snake.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                    };
                    /*for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY()))
                    {
                        overpassb=false;
                    }
                    else{overpassb=true;i=bricks.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };*/
                    if(food.getX()!=spefood.getX()||food.getY()!=spefood.getY())
                    {
                        overpassfai=false;
                    }
                    else{overpassfai=true;}
                }
                while(overpassai||overpassfai);
                //关于这个位置改变函数还有一个要求——————————————————不能够和蛇的位置重合！！！！！也就是要do while
                //food.Printfood(i%3);
                if(i==0)
                { p->setPen(Qt::NoPen);
                    p->setBrush(food.f1());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food1, 3);
                    p->restore();
                }
                if(i==1)
                {
                    p->setPen(Qt::NoPen);
                    p->setBrush(food.f2());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food2, 3);
                    p->restore();
                }
                if(i==2)
                {
                    p->setPen(Qt::NoPen);
                    p->setBrush(food.f3());

                    p->save();
                    p->translate(food.getX(),food.getY());
                    p->drawConvexPolygon(food3, 6);
                    p->restore();
                }
            }


            if(spefood.getBool()==true)//true 存在
            {
                //Printfood


                p->setPen(Qt::NoPen);
                p->setBrush(spefood.f4());

                p->save();
                p->translate(spefood.getX(),spefood.getY());
                p->drawConvexPolygon(specfood, 5);
                p->restore();

            }
            else
            {

                //FOOD=true;
                spefood.setTrue();
                do
                {
                    spefood.changeposition(width(),height());//???????是这个导致的吗？还是我的判据
                    for(int i=0;i<snake.getlength();i++)
                    {
                        if((snake.getX(i)!=spefood.getX()||snake.getY(i)!=spefood.getY()))
                        {
                            specoverpassai=false;
                        }
                        else{specoverpassai=true;i=snake.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                    };
                    /*for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
                    {
                        specoverpassb=false;
                    }
                    else{specoverpassb=true;i=bricks.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };*/
                    if(food.getX()!=spefood.getX()||food.getY()!=spefood.getY())
                    {
                        overpassfai=false;
                    }
                    else{overpassfai=true;}
                }
                while(specoverpassai||overpassfai);
                //关于这个位置改变函数还有一个要求——————————————————不能够和蛇的位置重合！！！！！也就是要do while
                p->setPen(Qt::NoPen);
                p->setBrush(spefood.f4());

                p->save();
                p->translate(spefood.getX(),spefood.getY());
                p->drawConvexPolygon(specfood, 5);
                p->restore();
            }



            //snake.copy(pre);

            preai=new Point[snake.getlength()];
            for(int j=0;j<snake.getlength();j++)
            {
                Point *Tmp=new Point(snake.getX(j),snake.getY(j));
                *(preai+j)=*Tmp;
            }
            nai=snake.getlength();


        }
        if(snake.getBool()==0)
        {
            direction='n';//不让他动
            N++;
            if(N==1)
            {

                QMessageBox msgboxai;
                msgboxai.setText("Ooooooooops Game Over");
                msgboxai.exec();
                //QMessageBox::information(this,"Ooooooooops Game Over", "Ooooooooops Game Over",QMessageBox::Ok);

            }
            //想做成一直闪（其实可以不用改interval，还是用一个staticint然后i=（i+1）%2——那就还是需要一个prexprey来存储上一次操作结束之后的位置
            if(blink==0)
            {
                //画出来——需要储存死亡的时候的情况，也就是需要在上面那个循环里面储存。
                p->setPen(headColor);
                p->setBrush(headColor);

                p->save();
                p->translate(preai->x,preai->y);
                p->drawEllipse(-5,-5,10,10);
                p->restore();

                QBrush bodybrush(bodyColor);
                QPen bodypen(liningColor,0.75);

                p->setPen(bodypen);
                p->setBrush(bodybrush);

                for(int j=1;j<snake.getlength();j++)
                {
                    p->save();
                    p->translate((preai+j)->x,(preai+j)->y);
                    p->drawRect(-5,-5,10,10);
                    p->restore();
                };

            }
            if(blink==1)
            {
                //什么都不做，空白的
                ;
            }
            blink=(blink+1)%2;
        }
    }
};
