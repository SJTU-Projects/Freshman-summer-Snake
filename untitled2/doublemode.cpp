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

#include "doublemode.h"
#include <QtGui>
#include <cstdlib>
#include "window.h"
#include <QMessageBox>
#include <QFont>
#include <QLabel>
//! [1]
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
void RasterWindow::renderNow()//??????????????????????????????????????????????????????????????????????????????
{
    if (!isExposed())//????????????????????????
        return;

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);//???????????????

    painter.fillRect(0, 0, width(), height(), QGradient::CloudyKnoxville);//????????????gradient?????????????????????
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}
//! [3]

//! [4]
void RasterWindow::render(QPainter *painter)
{
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow"));//????????????text??????????????????????????????????????????????????????????????????cpp????????????????????????????????????
}
//! [4]



void DoubleSnakeWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Up){
        //y-=4;//y????????????????????????
        if(predirection2!='d')
        {
            direction2='u';
            predirection2='u';
        };
    }
    if(e->key()==Qt::Key_Down){
        //y+=4;
        if(predirection2!='u')
        {
            direction2='d';
            predirection2='d';
        };

    }
    if(e->key()==Qt::Key_Right){
        //x+=4;
        if(predirection2!='l')
        {
            direction2='r';
            predirection2='r';
        };

    }
    if(e->key()==Qt::Key_Left){
        //x-=4;
        if(predirection2!='r')
        {
            direction2='l';
            predirection2='l';
        };
    }

    if(e->key()==Qt::Key_A){
            //x-=4;
         if(predirection1!='r')
         {
             direction1='l';
             predirection1='l';
         };

    }
    if(e->key()==Qt::Key_W){
        //y-=4;//y????????????????????????
        if(predirection1!='d')
        {
            direction1='u';
            predirection1='u';
        };
    }
    if(e->key()==Qt::Key_S){
        //y+=4;
        if(predirection1!='u')
        {
            direction1='d';
            predirection1='d';
        };

    }
    if(e->key()==Qt::Key_D){
        //x+=4;
        if(predirection1!='l')
        {
            direction1='r';
            predirection1='r';
        };
    }
}
//! [6]
//!
void DoubleSnakeWindow:: SetInterval(int inter)//???????????????????????????????????????????????????????????????????????????????????????????????????????????????show?????????????????????
{
    interval=inter;
}
DoubleSnakeWindow::DoubleSnakeWindow()//????????????//?????????????????????
{
    setTitle("DoubleMode");
    resize(1000, 1000);  //?????????????????????????????????????????????????????????    //?????????????????????????????????????????????????????????????????????
    x=0;//????????????
    y=0;
    m_timerId = startTimer(interval);//??????interval//interval?????????????????????????????????????????????ms???????????????killtime????????????is called
}


void DoubleSnakeWindow::timerEvent(QTimerEvent *event)//???????????????????????????????????????
{
    if (event->timerId() == m_timerId)//?????????????????????????????????????????????,??????????????????startTimer?????????????????????
    {
        if(direction2=='u')
        {
            snake2.moveup();
        }
        if(direction2=='d')
        {
            snake2.movedown();
        }
        if(direction2=='r')
        {
            snake2.moveright();
        }
        if(direction2=='l')
        {
            snake2.moveleft();
        }


        if(direction1=='u')
        {
            snake1.moveup();
        }
        if(direction1=='d')
        {
            snake1.movedown();
        }
        if(direction1=='r')
        {
            snake1.moveright();
        }
        if(direction1=='l')
        {
            snake1.moveleft();
        }
        //x+=1;
        //y+=0;//?????????????????????
        renderLater();//????????????rendr??????????????????????????????
    }
}

void DoubleSnakeWindow::render(QPainter *p)
{

    static int Score1=0;
    static int Score2=0;
    //???????????????????????????
static int renew=0;
if(renew==0)
{
    snake1.resetposition(10,-10);
    renew++;
}


    /*static bool overpass=false;//food??????
    //???????????????food???????????????specfood?????????
    static bool overpassb=false;
    static bool specoverpassb=false;
    static bool specoverpass=false;//specfood??????
    static bool over=false;//?????????static//?????????????????????....*/


    static int i=0;//food???????????????
    static int N=0;//???????????????
    //static bool FOOD=false;
    static bool overpass1=false;//food??????1
    static bool overpass2=false;//food??????2
    static bool overpass=false;//food???specfood
    static bool specoverpass1=false;//specfood??????1
    static bool specoverpass2=false;//specfood??????2
    //static bool specoverpass=false;
    static bool overpassb=false;//food?????????
    static bool specoverpassb=false;//specfood?????????
    static bool over1=false;//????????????1
    static bool over2=false;//????????????2
    for(int i=0;i<snake1.getlength();i++)
    {
        if((snake1.getX(i)!=food.getX()||snake1.getY(i)!=food.getY()))
        {
            overpass1=false;
        }
        else{overpass1=true;i=snake1.getlength()-1;}
    };
    for(int i=0;i<snake2.getlength();i++)
    {
        if((snake2.getX(i)!=food.getX()||snake2.getY(i)!=food.getY()))
        {
            overpass2=false;
        }
        else{overpass2=true;i=snake2.getlength()-1;}
    };
    ////?????????overpass??????????????????????????????????????
    for(int i=0;i<bricks.getlength();i++)//??????overpass
    {
        if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY())&&(bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
        {
        }
        else{overpass=true;i=bricks.getlength()-1;}
    };
    for(int i=0;i<snake1.getlength();i++)//??????specoverpass1
    {
        if((snake1.getX(i)!=spefood.getX()||snake1.getY(i)!=spefood.getY()))
        {
            specoverpass1=false;
        }
        else{specoverpass1=true;i=snake1.getlength()-1;}

        if((snake1.getX(i)!=bricks.getX()||snake1.getY(i)!=bricks.getY()))
        {
            over1=false;
        }
        else{over1=true;i=snake1.getlength()-1;}
    };
    for(int i=0;i<snake2.getlength();i++)//??????specoverpass2
    {
        if((snake2.getX(i)!=spefood.getX()||snake2.getY(i)!=spefood.getY()))
        {
            specoverpass2=false;
        }
        else{specoverpass2=true;i=snake2.getlength()-1;}

        if((snake2.getX(i)!=bricks.getX()||snake2.getY(i)!=bricks.getY()))
        {
            over2=false;
        }
        else{over2=true;i=snake2.getlength()-1;}
    };
    for(int i=0;i<bricks.getlength();i++)//??????specoverpassb
    {
        if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
        {
            specoverpassb=false;
        }
        else{specoverpassb=true;i=bricks.getlength()-1;}
    };

    //static bool alive=1;
    static int blink=0;
    static int n1=0;//prelength
    static Point *pre1=new Point[n1];
    static int n2=0;//prelength
    static Point *pre2=new Point[n2];


    QColor headColor1(255,20,147);
    QColor headColor2(70 ,130 ,180);
    QColor bodyColor1(205,133,63);
    QColor bodyColor2(255 ,192 ,203	);
    QColor liningColor(255,215,0);
    QColor liningColor2(238, 130, 238);
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


    if(snake1.getX(0)==food.getX() && snake1.getY(0)==food.getY())//?????????
    {
        //FOOD=false;
        food.setFalse();
        Point tmp(food.getX(),food.getY());
        queue1.enQueue(tmp);
        //????????????
        if(i==0)
        {
            Score1+=10;
        }
        if(i==1)
        {
            Score1+=20;
        }
        if(i==2)
        {
            Score1+=30;
        }
    }
    if(snake2.getX(0)==food.getX() && snake2.getY(0)==food.getY())//?????????
    {
        //FOOD=false;
        food.setFalse();
        Point tmp(food.getX(),food.getY());
        queue2.enQueue(tmp);
        //????????????
        if(i==0)
        {
            Score2+=10;
        }
        if(i==1)
        {
            Score2+=20;
        }
        if(i==2)
        {
            Score2+=30;
        }
    }
    if(snake1.getX(0)==spefood.getX() && snake1.getY(0)==spefood.getY())//?????????
    {
        Score1+=50;
        //FOOD=false;
        spefood.setFalse();
        Point tmp(spefood.getX(),spefood.getY());
        queue1.enQueue(tmp);
        int count=rand()%2;
        if(count==1){
            if(interval<1000)
            this->SetInterval(interval*2);
            Score1*=2;
        }
        else {
            if(interval>200)
                    this->SetInterval(interval/2);
            Score1-=100;
        }
        m_timerId = startTimer(interval);
    }
    if(snake2.getX(0)==spefood.getX() && snake2.getY(0)==spefood.getY())//?????????
    {
        Score2+=50;
        //FOOD=false;
        spefood.setFalse();
        Point tmp(spefood.getX(),spefood.getY());
        queue2.enQueue(tmp);
        int count=rand()%2;
        if(count==1){
            if(interval<1000)
            this->SetInterval(interval*2);//??????
            Score2*=2;
        }
        else {
            if(interval>=200)
                    this->SetInterval(interval/2);
            Score2-=100;

        }
        m_timerId = startTimer(interval);
    }
    if(!queue1.isEmpty()&&snake1.getX(snake1.getlength()-1)==queue1.getHead().x && snake1.getY(snake1.getlength()-1)==queue1.getHead().y)//grow
    {
        snake1.grow(queue1.getHead().x ,queue1.getHead().y);
        queue1.deQueue();
    }
    if(!queue2.isEmpty()&&snake2.getX(snake2.getlength()-1)==queue2.getHead().x && snake2.getY(snake2.getlength()-1)==queue2.getHead().y)//grow
    {
        snake2.grow(queue2.getHead().x ,queue2.getHead().y);
        queue2.deQueue();
    }



    //????????????
    for(int i=2;i<snake1.getlength();i++)//???????????????
    {
        if(snake1.getX(0)==snake1.getX(i)&&snake1.getY(0)==snake1.getY(i))
            snake1.setFalse();
    }
    for(int i=2;i<snake2.getlength();i++)//???????????????
    {
        if(snake2.getX(0)==snake2.getX(i)&&snake2.getY(0)==snake2.getY(i))
            snake2.setFalse();
    }
    if(snake1.getX(0)>=width()/10||snake1.getX(0)<=-width()/10||snake1.getY(0)>=height()/10||snake1.getY(0)<=-height()/10)//?????????
        //alive=0;
        snake1.setFalse();
    if(snake2.getX(0)>=width()/10||snake2.getX(0)<=-width()/10||snake2.getY(0)>=height()/10||snake2.getY(0)<=-height()/10)//?????????
        //alive=0;
        snake2.setFalse();

    //????????????
    for(int i=0;i<bricks.getlength();i++)//??????????????????????????????????????????test?????????????????????
    {
        if(snake1.gethead()->x!=bricks.getX(i)||snake1.gethead()->y!=bricks.getY(i))
        {

        }
        else
        {
            snake1.setFalse();
        }
    }
    for(int i=0;i<bricks.getlength();i++)//??????????????????????????????????????????test?????????????????????
    {
        if(snake2.gethead()->x!=bricks.getX(i)||snake2.gethead()->y!=bricks.getY(i))
        {

        }
        else
        {
            snake2.setFalse();
        }
    }

    //????????????
    for(int i=0;i<snake1.getlength();i++)
    {
        //2??????1
        if(snake2.gethead()->x!=snake1.getX(i)||snake2.gethead()->y!=snake1.getY(i))
        {

        }
        else
        {
            snake2.setFalse();
        }
    }
    for(int i=0;i<snake2.getlength();i++)
    {
        //1??????2
        if(snake1.gethead()->x!=snake2.getX(i)||snake1.gethead()->y!=snake2.getY(i))
        {

        }
        else
        {
            snake1.setFalse();
        }
    }



    p->setRenderHint(QPainter::Antialiasing);//???????????????????????????????????????
    p->translate(width() / 2, height() / 2);//??????????????????
    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);//?????????????????????????????????????????????

    QBrush wallbrush(wallColor);
    //??????
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

    //??????
    if((snake1.getX(0)==food.getX() && snake1.getY(0)==food.getY())||(snake1.getX(0)==spefood.getX() && snake1.getY(0)==spefood.getY())||(snake2.getX(0)==food.getX() && snake2.getY(0)==food.getY())||(snake2.getX(0)==spefood.getX() && snake2.getY(0)==spefood.getY()))//?????????????????????
    {

        do
        {
        bricks.changeposition(width(),height());//???????????????????????????????????????????????????????????????
        for(int i=0;i<snake1.getlength();i++)
        {
            if((snake1.getX(i)!=bricks.getX()||snake1.getY(i)!=bricks.getY()))
            {
                 over1=false;
            }
            else{over1=true;i=snake1.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
        };
        for(int i=0;i<snake2.getlength();i++)
        {
            if((snake2.getX(i)!=bricks.getX()||snake2.getY(i)!=bricks.getY()))//??????????????????????????????????????????????????????????????????????????????
            {
                 over2=false;
            }
            else{over2=true;i=snake2.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
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
        while(over1||over2||overpassb||specoverpassb);
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


    //??????????????????
    if(snake1.getBool()&&snake2.getBool())
    {
        p->setPen(headColor1);
        p->setBrush(headColor1);

        p->save();
        p->translate(snake1.getX(0),snake1.getY(0));
        p->drawEllipse(-5,-5,10,10);
        p->restore();

        p->setPen(headColor2);
        p->setBrush(headColor2);
        p->save();
        p->translate(snake2.getX(0),snake2.getY(0));
        p->drawEllipse(-5,-5,10,10);
        p->restore();


        QBrush bodybrush(bodyColor1);
        QPen bodypen(liningColor,0.75);

        p->setPen(bodypen);
        p->setBrush(bodybrush);

        for(int i=1;i<snake1.getlength();i++)
        {
            p->save();
            p->translate(snake1.getX(i),snake1.getY(i));
            p->drawRect(-5,-5,10,10);
            p->restore();
        };
        QBrush bodybrush2(bodyColor2);
        QPen bodypen2(liningColor2,0.75);

        p->setPen(bodypen2);
        p->setBrush(bodybrush2);
        for(int i=1;i<snake2.getlength();i++)
        {
            p->save();
            p->translate(snake2.getX(i),snake2.getY(i));
            p->drawRect(-5,-5,10,10);
            p->restore();
        };


        if(food.getBool()==true)//true ??????
        {
            //Printfood???i%3???
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
            do//???????????????food???????????????food?????????overpass
            {
                food.changeposition(width(),height());
                for(int i=0;i<snake1.getlength();i++)
                {
                    if((snake1.getX(i)!=food.getX()||snake1.getY(i)!=food.getY()))
                    {
                        overpass1=false;
                    }
                    else{overpass1=true;i=snake1.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
                };
                for(int i=0;i<snake2.getlength();i++)
                {
                    if((snake2.getX(i)!=food.getX()||snake2.getY(i)!=food.getY()))
                    {
                        overpass2=false;
                    }
                    else{overpass2=true;i=snake2.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
                };
                if(food.getX()!=spefood.getX()||food.getY()!=spefood.getX())
                {
                    overpass=false;
                }
                else overpass=true;
                for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=food.getX()||bricks.getY(i)!=food.getY()))
                    {
                        overpassb=false;
                    }
                    else{overpassb=true;i=bricks.getlength()-1;}
                }
            }
            while(overpass1||overpass2||overpassb||overpass);
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


        if(spefood.getBool()==true)//true ??????
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
            do//???????????????food???????????????food?????????overpass
            {
                spefood.changeposition(width(),height());
                for(int i=0;i<snake1.getlength();i++)
                {
                    if((snake1.getX(i)!=spefood.getX()||snake1.getY(i)!=spefood.getY()))
                    {
                        specoverpass1=false;
                    }
                    else{specoverpass1=true;i=snake1.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
                };
                for(int i=0;i<snake2.getlength();i++)
                {
                    if((snake2.getX(i)!=spefood.getX()||snake2.getY(i)!=spefood.getY()))
                    {
                        specoverpass2=false;
                    }
                    else{specoverpass2=true;i=snake2.getlength()-1;}//????????????break???????????????while??????????????????????????????????????????i=length-1???????????????
                };
                if(food.getX()!=spefood.getX()||food.getY()!=spefood.getX())
                {
                    overpass=false;
                }
                else overpass=true;
                for(int i=0;i<bricks.getlength();i++)
                {
                    if((bricks.getX(i)!=spefood.getX()||bricks.getY(i)!=spefood.getY()))
                    {
                        specoverpassb=false;
                    }
                    else{specoverpassb=true;i=bricks.getlength()-1;}
                }
            }
            while(specoverpass1||specoverpass2||specoverpassb||overpass);
            //???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????do while
            p->setPen(Qt::NoPen);
            p->setBrush(spefood.f4());

            p->save();
            p->translate(spefood.getX(),spefood.getY());
            p->drawConvexPolygon(specfood, 5);
            p->restore();
        }



            //snake.copy(pre);

            pre1=new Point[snake1.getlength()];
            for(int j=0;j<snake1.getlength();j++)
            {
                Point *Tmp=new Point(snake1.getX(j),snake1.getY(j));
                *(pre1+j)=*Tmp;
            }
            n1=snake1.getlength();

            pre2=new Point[snake2.getlength()];
            for(int j=0;j<snake2.getlength();j++)
            {
                Point *Tmp=new Point(snake2.getX(j),snake2.getY(j));
                *(pre2+j)=*Tmp;
            }
            n2=snake2.getlength();


    }
    if(snake1.getBool()==0||snake2.getBool()==0)//??????
    {
        direction1='n';//????????????
        direction2='n';//????????????

        N++;
        if(N==1)
        {

            QString result1 = "The Left Player's Score:";
              QString y1 ;
              y1.setNum(Score1);
              result1.append(y1);
            QString result2="The Right Player's Score:";
            QString y2;
            y2.setNum(Score2);
            QString y3="\n";
            result2.append(y2);
            result1.append(y3);
            result1.append(result2);
            QFont ft;
            ft.setPointSize(14);

            QLabel *label = new QLabel("this");
            label->setFont(ft);
             label->resize(500,300);

             label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
             //??????????????????.
             label->setText(result1) ;
             //??????????????????.
             label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
             label->show();
                QMessageBox msgbox;
                msgbox.setText("Ooooooooops Game Over");
                msgbox.exec();
            //QMessageBox::information(this,"Ooooooooops Game Over", "Ooooooooops Game Over",QMessageBox::Ok);

        }
        //??????????????????????????????????????????interval??????????????????staticint??????i=???i+1???%2??????????????????????????????prexprey?????????????????????????????????????????????
        if(blink==0)
        {
            //?????????????????????????????????????????????????????????????????????????????????????????????????????????
            p->setPen(headColor1);
            p->setBrush(headColor1);

            p->save();
            p->translate(pre1->x,pre1->y);
            p->drawEllipse(-5,-5,10,10);
            p->restore();

            QBrush bodybrush(bodyColor1);
            QPen bodypen(liningColor,0.75);
            p->setPen(bodypen);
            p->setBrush(bodybrush);
            for(int j=1;j<snake1.getlength();j++)
            {
                p->save();
                p->translate((pre1+j)->x,(pre1+j)->y);
                p->drawRect(-5,-5,10,10);
                p->restore();
            };

            p->setPen(headColor2);
            p->setBrush(headColor2);
            p->save();
            p->translate(pre2->x,pre2->y);
            p->drawEllipse(-5,-5,10,10);
            p->restore();

            QBrush bodybrush2(bodyColor2);
            QPen bodypen2(liningColor2,0.75);
            p->setPen(bodypen2);
            p->setBrush(bodybrush2);

            for(int j=1;j<snake2.getlength();j++)
            {
                p->save();
                p->translate((pre2+j)->x,(pre2+j)->y);
                p->drawRect(-5,-5,10,10);
                p->restore();
            };



        }
        if(blink==1)
        {
            //???????????????????????????
            ;
        }
        blink=(blink+1)%2;
    }
};
