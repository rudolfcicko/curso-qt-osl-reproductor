#include "player.h"

Player::Player(QWidget *parent) :
    QWidget(parent)
{
    player       = new QMediaPlayer;
    video        = new QVideoWidget;
    vertlayout   = new QVBoxLayout;
    controlpanel = new Controls;

    slider       = new QSlider(Qt::Horizontal,this);
    setMinimumSize(400,400);

    player->setVideoOutput(video);
    player->setVolume(50);

    vertlayout->addWidget(video);
    vertlayout->addWidget(slider);
    vertlayout->addWidget(controlpanel);
    setLayout(vertlayout);

    connect(controlpanel,SIGNAL(splay()),this,SLOT(reanudar()));
    connect(controlpanel,SIGNAL(spause()),this,SLOT(pausar()));
    connect(controlpanel,SIGNAL(sstop()),this,SLOT(detener()));
    connect(controlpanel,SIGNAL(volchanged(int)),this,SLOT(changeVol(int)));
    connect(controlpanel,SIGNAL(sopen()),this,SLOT(abrir()));

    connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));
    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
}
Player::~Player()
{
    delete player;
    delete video;
}
void Player::reanudar()
{
    player->play();
}

void Player::pausar()
{
    player->pause();
}

void Player::detener()
{
    player->stop();
}

void Player::changeVol(int vol)
{
   player->setVolume(vol);
}

void Player::abrir()
{
    QString archivo = QFileDialog::getOpenFileNames(this, tr("Abrir archivo")).at(0);
    player->setMedia(QUrl::fromLocalFile(archivo));
}
void Player::seek(int ticks){
    player->setPosition(ticks);

}
void Player::durationChanged(qint64 duration)
{
    qDebug()<<"sdfsd"<<endl;
    slider->setRange(0,duration);

}
