    #ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "controls.h"
class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    ~Player();






private:
    QMediaPlayer* player;
    QAbstractSlider*      slider;
    QVideoWidget* video;
    QVBoxLayout*  vertlayout;
    Controls*     controlpanel;
signals:
    
public slots:
    void detener();
    void pausar();
    void reanudar();
    void changeVol(int vol);
    void abrir();
    void seek(int ticks);
    void durationChanged(qint64 duration);
};

#endif // PLAYER_H
