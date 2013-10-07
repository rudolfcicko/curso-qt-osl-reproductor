#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QDebug>
class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QWidget *parent = 0);




private:
    QPushButton *play;
    QPushButton *pause;
    QPushButton *stop;
    QPushButton *open;
    QGridLayout *panel;
    QSlider     *volume;
signals:
    void splay();
    void spause();
    void sstop();
    void volchanged(int);
    void sopen();
public slots:
    void onClickPlay();
    void onClickPause();
    void onClickStop();
    void onVolChanged(int vol);
    void onClickOpen();
};

#endif // CONTROLS_H
