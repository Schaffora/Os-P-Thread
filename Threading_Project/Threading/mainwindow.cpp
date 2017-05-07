#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Voir les threads"));
    dessinW = new Dessin(this);
    setCentralWidget(dessinW);
    resize(800,400);
    this->setMinimumHeight(200);
    this->setMinimumWidth(300);
    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    actDemarrer= new QAction(tr("&Démarrer"),this);
    actQuitter = new QAction(tr("&Quitter"),this);
    actAPropos = new QAction(tr("&A Propos"),this);
    actTrace= new QAction(tr("&Couleur tracé"),this);
    actRemp= new QAction(tr("&Couleur remplissage"),this);
    groupForme = new QActionGroup(this);
    actSequentiel= new QAction(tr("&Sequentiel"),groupForme);
    actParallel= new QAction(tr("&Avec Thread"),groupForme);

    connect(actQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(actAPropos, SIGNAL(triggered()), this, SLOT(about()));
    connect(actTrace, &QAction::triggered, dessinW, &Dessin::setPenCol);
    connect(actRemp, &QAction::triggered, dessinW, &Dessin::setBrushCol);
    connect(actDemarrer, &QAction::triggered, this, &MainWindow::start);
    connect(actSequentiel, SIGNAL(triggered()), this, SLOT(mode()));
    connect(actParallel, SIGNAL(triggered()), this, SLOT(mode()));
    actSequentiel->setCheckable(true);
    actSequentiel->setChecked(true);
    actParallel->setCheckable(true);
}

void MainWindow::createMenus()
{
    menuApplication = menuBar()->addMenu(tr("&Application"));
    menuApplication->addAction(actDemarrer);
    menuApplication->addAction(actQuitter);
    menuDessin=menuBar()->addMenu(tr("&Dessin"));
    menuDessin->addAction(actTrace);
    menuDessin->addAction(actRemp);


    menuDessin->addAction(actSequentiel);
    menuDessin->addAction(actParallel);
    menuAide = menuBar()->addMenu(tr("&?"));
    menuAide->addAction(actAPropos);
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("A Propos"), tr("Qt explication visuel d'un Thread"));
}

void MainWindow::start()
{
    dessinW->start();
}
void MainWindow::mode()
{
    if(actSequentiel->isChecked()==true)
    {
        dessinW->setFigure(1);
    }
    else
    {
         dessinW->setFigure(2);
    }

}
