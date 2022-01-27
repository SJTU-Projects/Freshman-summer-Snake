#ifndef DOUBLEMODE_H
#define DOUBLEMODE_H
#include "test.h"
class DoubleSnakeWindow : public RasterWindow
   {
   public:
       DoubleSnakeWindow();//构造函数
       void SetInterval(int inter);
       //void endGame();

   protected:              //protected
       void timerEvent(QTimerEvent *) override;
       void render(QPainter *p) override;
       void keyPressEvent(QKeyEvent *e) override;
       //override和父子继承有关，在子类中重写父类
   private:
       int m_timerId;
       int x;
       int y;
       char direction1;
       char predirection1='r';
       char direction2;
       char predirection2='r';
       Point start;
       Snake snake1;
       Snake snake2;
       Food food;//以及一般的食物？那么特殊食物需要单独考虑啊。再建一个，直接在cpp里面调整
       Queue queue1;
       Queue queue2;
       Food spefood;
       int interval=500;
       Bricks bricks;
   };



#endif // DOUBLEMODE_H
