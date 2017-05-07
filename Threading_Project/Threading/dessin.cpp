#include "dessin.h"

#include <QtWidgets>
#include <QtCore>
#include <QLayout>
#include <QtPrintSupport>
#include <QDebug>
Dessin::Dessin(QWidget *parent) : QWidget(parent)
{
    /* Mode Sequential or multiThread */
    mode=1;
    taille=25;

    /* Exchange tools */
    isStarted=false;
    sendStep1=false;
    sendStep2=false;
    sendDone=false;
    sendWay=150;

    /* Form and line color */
    penCol = Qt::green;
    brushCol = Qt::yellow;

    /* Windows parametring */
    setMinimumSize(QSize(100,100));
    this->resize(200,200);
    int x = this->height()/2;

    /* Time label */
    val= new QLabel("Temps=0.00(s)",this);
    val->move(x,20);
    val->setStyleSheet("QLabel { color : red; }");

    /* Time line */
    regle= new QSlider(Qt::Horizontal,this);
    regle->setTickInterval(1);
    regle->setMinimum(0);
    regle->setMaximum(100);
    regle->setGeometry(0,10,300,20);
    regle->setTickPosition(QSlider::TicksLeft);
    regle->setEnabled(true);

    /* Connection */
    connect(regle, SIGNAL(valueChanged(int)), this, SLOT(changementVal(int)));
    connect(regle,SIGNAL(valueChanged(int)),this,SLOT(dessiner(int)));

}

void Dessin::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setPen(penCol);
    paint.setBrush(brushCol);


    regle->setGeometry(0,10,this->width(),40);
    val->move(this->width()/2,0);

    int w=width(), h=height(), x, y;
    float r=1.*h/w;

    if (width()<height())
    {
        paint.setWindow(0,0,100,100*r);
        x=(100-taille)/2;
        y=(100*r-taille)/2;
    }
    else
    {
        paint.setWindow(0,0,100./r,100);
        x=(100./r-taille)/2;
        y=(100-taille)/2;
    }

    switch (mode)
    {
        case 1 :
                if(isStarted==false)
                {
                    xs1=48;
                    xs2=0;
                    xsf=2;
                    paint.drawEllipse(QRect(x*1.5,y,xs1,xs1));
                    paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                    sendStep1=true;
                }
                else
                {
                    if(sendStep1==true)
                    {
                        xs1--;
                        paint.drawEllipse(QRect(x*1.5,y,xs1,xs1));
                        paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                        sendStep1=false;
                        sendStep2=true;
                        sendWay=150;
                        Sleep(10);
                        update();
                    }
                    if(sendStep2==true)
                    {
                        if(sendWay>100)
                        {
                            paint.drawEllipse(QRect(x*1.5,y,xs1,xs1));
                            paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                            paint.drawEllipse(QRect(x*(sendWay/100),y,1,1));
                            sendWay=sendWay-3;
                            Sleep(1);
                            update();
                        }
                        else
                        {
                            sendWay=150;
                            sendStep2=false;
                            sendDone=true;
                            paint.drawEllipse(QRect(x*1.5,y,xs1,xs1));
                            paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                            update();
                        }
                    }

                    if(sendDone==true)
                    {
                        Sleep(10);
                        xsf++;
                        sendDone=false;
                        paint.drawEllipse(QRect(x*1.5,y,xs1,xs1));
                        paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                        if(xsf<50)
                        {
                            sendStep1=true;
                            regle->setValue(regle->value()+1);
                            changementVal(regle->value());
                            update();
                        }
                        else
                        {
                            regle->setValue(0);
                            changementVal(regle->value());
                            isStarted=false;
                            QMessageBox::information(this, tr("Sans thread"), tr("En mode séquentiel (une incrémentation à la fois), il faut 48 secondes"
                                                                                 " pour que le cercle atteigne sa taille final de 50. L'utilisation de thread "
                                                                                 "peut réduire grandement le temps nécessaire pour cette même action. Voilà un"
                                                                                 " grand avantage des threads."
                                                                                ));
                            update();

                        }
                    }



                }

            break;
        case 2 :
        if(isStarted==false)
        {
            xs1=24;
            xs2=24;
            xsf=2;
            paint.drawEllipse(QRect(x*1.5,y/2,xs1,xs1));
            paint.drawEllipse(QRect(x*1.5,y*1.5,xs2,xs2));
            paint.drawEllipse(QRect(x/10,y,xsf,xsf));
            sendStep1=true;
        }
        else
        {
            if(sendStep1==true)
            {
                xs1--;
                xs2--;
                paint.drawEllipse(QRect(x*1.5,y/2,xs1,xs1));
                paint.drawEllipse(QRect(x*1.5,y*1.5,xs2,xs2));
                paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                sendStep1=false;
                sendStep2=true;
                sendWay=150;
                Sleep(10);
                update();
            }
            if(sendStep2==true)
            {
                if(sendWay>100)
                {
                    paint.drawEllipse(QRect(x*1.5,y/2,xs1,xs1));
                    paint.drawEllipse(QRect(x*1.5,y*1.5,xs2,xs2));
                    paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                    paint.drawEllipse(QRect(x*(sendWay/100),y*1.25,1,1));
                    paint.drawEllipse(QRect(x*(sendWay/100),y*0.75,1,1));
                    sendWay=sendWay-3;
                    Sleep(1);
                    update();
                }
                else
                {
                    sendWay=150;
                    sendStep2=false;
                    sendDone=true;
                    paint.drawEllipse(QRect(x*1.5,y/2,xs1,xs1));
                    paint.drawEllipse(QRect(x*1.5,y*1.5,xs2,xs2));
                    paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                    update();
                }
            }

            if(sendDone==true)
            {
                Sleep(10);
                xsf=xsf+2;
                sendDone=false;
                paint.drawEllipse(QRect(x*1.5,y/2,xs1,xs1));
                paint.drawEllipse(QRect(x*1.5,y*1.5,xs2,xs2));
                paint.drawEllipse(QRect(x/10,y,xsf,xsf));
                if(xsf<50)
                {
                    sendStep1=true;
                    regle->setValue(regle->value()+1);
                    changementVal(regle->value());
                    update();

                }
                else
                {
                    regle->setValue(0);
                    changementVal(0);
                    isStarted=false;
                    QMessageBox::information(this, tr("Avec thread"), tr("Avec deux thread, pour incrémenter le cercle de départ jusqu'à"
                                                                         " une taille de 50, il faut 24 secondes. Deux fois plus de temps qu'en"
                                                                         " séquentiel, comme l'incrémentation se fait un par un. "
                                                                         " Cette exemple ne prend pas en compte la notion de protection de l'accés d'une variable"
                                                                         " par un seul thread."));
                    update();
                }
            }

        }

            break;
    }
}

//SLOTS
void Dessin::dessiner(int t)
{
    update();
}

void Dessin::setBrushCol()
{   brushCol = QColorDialog::getColor(brushCol, this); update(); }

void Dessin::setPenCol()
{   penCol = QColorDialog::getColor(penCol, this); update(); }

void Dessin::setFigure(int f)
{   mode=f; update();  }

void Dessin::start()
{
    isStarted=true;
}

void Dessin::changementVal(int v)
{
    QString valeur=QString::number(v);
    val->setText("temps="+valeur+"(s)");
}
