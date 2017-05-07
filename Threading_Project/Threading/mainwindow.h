#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include "dessin.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    void createActions();
    void createMenus();
    Dessin *dessinW;
    QMenu *menuApplication,*menuDessin, *menuAide;
    QAction *actDemarrer, *actQuitter, *actTrace, *actRemp, *actSequentiel, *actParallel, *actAPropos;
    QActionGroup *groupForme;
    QVBoxLayout *vlayout;
private slots:
    void about();
    void start();
    void mode();

};

#endif // MAINWINDOW_H
