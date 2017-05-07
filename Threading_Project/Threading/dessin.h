#ifndef DESSIN_H
#define DESSIN_H

#include <QtCore>
#include <QtWidgets>
#include <QtPrintSupport>
class Dessin : public QWidget
{
      Q_OBJECT
      public:
        Dessin(QWidget *parent = 0);
      
      protected:
        void paintEvent(QPaintEvent *);

      private:
        int mode, taille, xs1, xs2, xsf, sendWay;
        bool isStarted, sendStep1,sendStep2, sendDone;
        QColor penCol, brushCol;
        QSlider *regle;
        QLabel *val;

      public slots:
        void dessiner(int);
        void setBrushCol();
        void setPenCol();
        void setFigure(int);
        void start();
        void changementVal(int);
};

#endif
