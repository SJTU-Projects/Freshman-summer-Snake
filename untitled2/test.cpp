/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "test.h"
#include <QtGui>
#include <cstdlib>
#include "window.h"
#include <QMessageBox>
#include <QFont>
#include <QLabel>


//! [1]
/*
RasterWindow::RasterWindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{
    setGeometry(100, 100, 300, 200);
}
//! [1]


//! [7]
bool RasterWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}
//! [7]

//! [6]
void RasterWindow::renderLater()
{
    requestUpdate();
}
//! [6]


//! [5]
void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
}
//! [5]

//! [2]
void RasterWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}
//! [2]


//! [3]
void RasterWindow::renderNow()//在这个函数里面它只画了一个背景——也就是设置背景函数
{
    if (!isExposed())//没打开就直接返回
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);//画图必用的

    painter.fillRect(0, 0, width(), height(), QGradient::CloudyKnoxville);//画背景。gradient就是渐变的意思
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}
//! [3]

//! [4]
void RasterWindow::render(QPainter *painter)
{
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));//这个是写text，但是我好像没发现有什么用，也就是说这个整个cpp和蛇没有关系，除了初始化
}
//! [4]
*/


void SnakeWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Up){
        //y-=4;//y的上下要反过来。
        if(predirection!='d')
        {
            direction='u';
            predirection='u';
        };
    }
    if(e->key()==Qt::Key_Down){
        //y+=4;
        if(predirection!='u')
        {
            direction='d';
            predirection='d';
        };

    }
    if(e->key()==Qt::Key_Right){
        //x+=4;
        if(predirection!='l')
        {
            direction='r';
            predirection='r';
        };

    }
    if(e->key()==Qt::Key_Left){
        //x-=4;
        if(predirection!='r')
        {
            direction='l';
            predirection='l';
        };
    }
    if(e->key()==Qt::Key_Space)
     {
        direction='n';//不动
    }

}
//! [6]
//!
void SnakeWindow:: SetInterval(int inter)//方便之后的特殊道具改变刷新时间（在多人游戏的时候应该还要再改改）（比如两个show函数啊之类的）
{
    interval=inter;
}
SnakeWindow::SnakeWindow()//建立窗口//构造函数的实现
{
    setTitle("SnakeWindow");//这个window的名字名为“SnakeWindow”
    resize(1000, 1000);  //设定大小（之后还有个函数可以自动调整）    //这两个应该是内置的函数，直接可以把框框给搞出来
    x=0;//初始位置
    y=0;
    m_timerId = startTimer(interval);//刷新interval//interval越大，刷新间隔时间越长（单位是ms）——直到killtime（）函数is called



}


void SnakeWindow::timerEvent(QTimerEvent *event)//每次刷新之后应该发生的事情
{
    if (event->timerId() == m_timerId)//判断当前事件是不是我想要的触发,可能有好多个startTimer但是名字不一样
    {
        if(direction=='u')
        {
            snake.moveup();
        }
        if(direction=='d')
        {
            snake.movedown();
        }
        if(direction=='r')
        {
            snake.moveright();
        }
        if(direction=='l')
        {
            snake.moveleft();
        }
        //x+=1;
        //y+=0;//先改数值，再画
        renderLater();//画——在rendr（）函数里面判定死亡
    }
}

void SnakeWindow::render(QPainter *p)
{


    /*static int Score=0;

    static int i=0;//food的计数循环
    static int N=0;//弹窗的判断
    //static bool FOOD=false;
    static bool overpassf=false;//food和spefood
    static bool overpass=false;//food和蛇
    static bool overpassb=false;//food和砖块
    static bool specoverpassb=false;//specfood与砖块
    static bool specoverpass=false;//specfood和蛇
    static bool over=false;//砖块和蛇*/
    for(int i=0;i<snake.getlength();i++)//检查overpass//其实一开始没必要，我已经初始值设置成一个很大的数 不可能overpass
    {
        if((snake.getX(i)!=food.getX()||snake.getY(i)!=food.getY()))
        {
            overpass=false;
        }
        else{overpass=true;i=snake.getlength()-1;}
    };
    for(int i=0;i<bricks.getlength();i++)//检查overpassb//其实一开始没必要，我已经初始值设置成一个很大的数 不可能overpass
    {
        if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY()))
        {
            overpassb=false;
        }
        else{overpassb=true;i=bricks.getlength()-1;}
    };
    for(int i=0;i<snake.getlength();i++)//检查specoverpass
    {
        if((snake.getX(i)!=spefood.getX()||snake.getY(i)!=spefood.getY()))
        {
            specoverpass=false;
        }
        else{specoverpass=true;i=snake.getlength()-1;}
    };
    for(int i=0;i<bricks.getlength();i++)//检查specoverpassb
    {
        if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
        {
            specoverpassb=false;
        }
        else{specoverpassb=true;i=bricks.getlength()-1;}
    };
    for(int i=0;i<snake.getlength();i++)//检查over
    {
        if(snake.getX(i)!=bricks.getX()||snake.getY(i)!=bricks.getY())
        {
            over=false;
        }
        else{over=true;i=snake.getlength()-1;}
    }
    //static bool alive=1;
    /*static int blink=0;
    static int n=0;//prelength
    static Point *pre=new Point[n];*/

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
        if(i==0)
        {
            Score+=10;
        }
        if(i==1)
        {
            Score+=20;
        }
        if(i==2)
        {
            Score+=30;
        }



    }
    if(snake.getX(0)==spefood.getX() && snake.getY(0)==spefood.getY())//吃到了
    {
        Score+=50;
        //FOOD=false;
        spefood.setFalse();
        Point tmp(spefood.getX(),spefood.getY());
        queue.enQueue(tmp);
        int count=rand()%2;
        if(count==1){
            if(interval<1000)
            this->SetInterval(interval*2);
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
    //撞到砖块
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
            else{specoverpassb=true;i=bricks.getlength()-1;}

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
                        overpass=false;
                    }
                    else{overpass=true;i=snake.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };
                for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY()))
                    {
                        overpassb=false;
                    }
                    else{overpassb=true;i=bricks.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };
                if(food.getX()!=spefood.getX()||food.getY()!=spefood.getY())
                {
                    overpassf=false;
                }
                else{overpassf=true;}
            }
            while(overpass||overpassb||overpassf);
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
                        specoverpass=false;
                    }
                    else{specoverpass=true;i=snake.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };
                for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
                    {
                        specoverpassb=false;
                    }
                    else{specoverpassb=true;i=bricks.getlength()-1;}//这里要是break退出了包括while在内全部循环的话，就这样，令i=length-1，就跳出嘛
                };
                if(food.getX()!=spefood.getX()||food.getY()!=spefood.getY())
                {
                    overpassf=false;
                }
                else{overpassf=true;}
            }
            while(specoverpass||specoverpassb||overpassf);
            //关于这个位置改变函数还有一个要求——————————————————不能够和蛇的位置重合！！！！！也就是要do while
            p->setPen(Qt::NoPen);
            p->setBrush(spefood.f4());

            p->save();
            p->translate(spefood.getX(),spefood.getY());
            p->drawConvexPolygon(specfood, 5);
            p->restore();
        }



            //snake.copy(pre);

            pre=new Point[snake.getlength()];
            for(int j=0;j<snake.getlength();j++)
            {
                Point *Tmp=new Point(snake.getX(j),snake.getY(j));
                *(pre+j)=*Tmp;
            }
            n=snake.getlength();


    }
    if(snake.getBool()==0)
    {
        direction='n';//不让他动
        N++;
        if(N==1)
        {
            QString result = "Your Score:";
              QString y ;
              y.setNum(Score);

              result.append(y);
            //std::string f_str = std::to_string(Score);
            //std::string f1="Your Score:";
            //std::string result=f1+f_str;
            QFont ft;
            ft.setPointSize(14);

            QLabel *label = new QLabel("this");
            label->setFont(ft);
             //设置大小.
             label->resize(300,200);
             //设置边框风格.凹陷下去.
             label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
             //设置文本内容.
             label->setText(result) ;
             //设置对齐方式.
             label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
             label->show();

                QMessageBox msgbox;
                msgbox.setText("Ooooooooops Game Over");
                msgbox.exec();
            //QMessageBox::information(this,"Ooooooooops Game Over", "Ooooooooops Game Over",QMessageBox::Ok);

        }
        //想做成一直闪（其实可以不用改interval，还是用一个staticint然后i=（i+1）%2——那就还是需要一个prexprey来存储上一次操作结束之后的位置
        if(blink==0)
        {
            //画出来——需要储存死亡的时候的情况，也就是需要在上面那个循环里面储存。
            p->setPen(headColor);
            p->setBrush(headColor);

            p->save();
            p->translate(pre->x,pre->y);
            p->drawEllipse(-5,-5,10,10);
            p->restore();

            QBrush bodybrush(bodyColor);
            QPen bodypen(liningColor,0.75);

            p->setPen(bodypen);
            p->setBrush(bodybrush);

            for(int j=1;j<snake.getlength();j++)
            {
                p->save();
                p->translate((pre+j)->x,(pre+j)->y);
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

};
