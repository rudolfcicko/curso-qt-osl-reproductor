#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDir>
#include <QSlider>
#include <QFileDialog>
#include <QToolButton>
#include <QDialog>
#include <QLayout>
#include <QLabel>

#include <QMenu>
#include <QMenuBar>

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:

    QGridLayout*        lytMain_;
    QWidget*            wgtMain_;
    QMediaPlayer*       mediaPlayer_;
    QSlider*            playerSlider_;
    QVideoWidget*       videoWidget_;
    QSlider*            volumeSlider_;
    QToolButton*        btnOpen_;
    QToolButton*        btnPlay_;
    QToolButton*        btnPause_;
    QToolButton*        btnStop_;
    QMenuBar*           mainMenu_;
    QMenu*              mnuArchivo_;
    QMenu*              mnuVer_;
    QMenu*              mnuAyuda_;
    QAction*            actArchivoAbrir_;
    QAction*            actVerFullScreen_;
    QAction*            actAyudaAcerca_;
    QAction*            actArchivoRecientes_;
    QDialog*            acercaDeDialog_;
    QWidget*            acercaDeWidget_ ; //new al widget .. que use ese layout
    QLayout*            acercaDeLayout_; // new al layout
    QLabel*             logoAcercaDe_; // new  logo del programa
    QLabel*             textoAcercaDe_;//  new  texto que diga y estos dos labels los metemos en el layout.
    //////
    QAction*            actRecientes_[5];
    QJsonArray*         recientesArray;

private slots:
    void onOpen();
    void onSeek();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void setFullScreen();
    void CargarRecientes();
    void GuardarRecientes(QString filename);
};

#endif // MAINWINDOW_H
