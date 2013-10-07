#include "mainwindow.h"
//Ejemplo de reproduccion de un archivo de música
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    player = new Player;
    setCentralWidget(player);
}

MainWindow::~MainWindow()
{
    delete player;
}
