#include "controls.h"

Controls::Controls(QWidget *parent) :
    QWidget(parent)
{
    play  = new QPushButton(QString("play"));
    connect(play,SIGNAL(clicked()),this,SLOT(onClickPlay()));

    pause = new QPushButton(QString("pause"));
    connect(pause,SIGNAL(clicked()),this,SLOT(onClickPause()));

    stop  = new QPushButton(QString("stop"));
    connect(stop,SIGNAL(clicked()),this,SLOT(onClickStop()));
    volume = new QSlider(Qt::Vertical);
    connect(volume,SIGNAL(valueChanged(int)),this,SLOT(onVolChanged(int)));
    volume->setValue(50);
    open = new QPushButton("open");
    connect(open,SIGNAL(clicked()),this,SLOT(onClickOpen()));
    panel = new QGridLayout;
    panel->addWidget(open,0,0);
    panel->addWidget(play,0,1);
    panel->addWidget(pause,0,2);
    panel->addWidget(stop,0,3);
    panel->addWidget(volume,0,4,2,1);


    setLayout(panel);
}

void Controls::onClickPlay()
{
    emit splay();
}


void Controls::onClickPause()
{
    emit spause();
}


void Controls::onClickStop()
{
    emit sstop();
}

void Controls::onVolChanged(int vol)
{
    emit volchanged(vol);
}

void Controls::onClickOpen()
{
    emit sopen();
}
