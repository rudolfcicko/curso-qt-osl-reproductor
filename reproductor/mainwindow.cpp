#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //***Rudy PART
    for(int i = 0; i < 5; i++)
    {
        actRecientes_[i] = new QAction(this) ;
    }
     mainMenu_ = new QMenuBar(this);

     mnuArchivo_ = new QMenu(tr("&Archivo"), this); // El & es para permitir un acceso más rápido desde el teclado , por ejemplo ALT + A ( Abrir )
     mainMenu_->addMenu(mnuArchivo_);

     actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
     actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
     mnuArchivo_->addAction(actArchivoAbrir_);

     mnuVer_ = new QMenu(tr("&Ver"), this);
     mainMenu_->addMenu(mnuVer_);

     actVerFullScreen_ = new QAction(tr("&Pantalla Completa"), this);
     actVerFullScreen_->setShortcut(Qt::Key_Escape);
     mnuVer_->addAction(actVerFullScreen_);

     mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
     mainMenu_->addMenu(mnuVer_);

     actAyudaAcerca_ = new QAction(tr("&Acerca"), this);
     mnuAyuda_->addAction(actAyudaAcerca_);

     actArchivoRecientes_ = new QAction(tr("&Recientes"), this);
     mnuArchivo_->addAction(actArchivoRecientes_);

     setMenuBar(mainMenu_);

    //*** END RUDY PART
    //Create central widget and set main layout
    wgtMain_ = new QWidget(this);
    lytMain_ = new QGridLayout(wgtMain_);
    wgtMain_->setLayout(lytMain_);
    setCentralWidget(wgtMain_);

    //Initialize widgets
    mediaPlayer_  = new QMediaPlayer(this);
    playerSlider_ = new QSlider(Qt::Horizontal, this);
    videoWidget_  = new QVideoWidget(this);
    volumeSlider_ = new QSlider(Qt::Horizontal, this);
    btnOpen_      = new QToolButton(this);
    btnPlay_      = new QToolButton(this);
    btnPause_     = new QToolButton(this);
    btnStop_      = new QToolButton(this);

    //Setup widwgets
    videoWidget_->setMinimumSize(400, 400);
    mediaPlayer_->setVideoOutput(videoWidget_);
    mediaPlayer_->setVolume(100);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Populate grid layout
    lytMain_->addWidget(videoWidget_,  0, 0, 1, 5);
    lytMain_->addWidget(playerSlider_, 1, 0, 1, 5);
    lytMain_->addWidget(btnOpen_,      2, 0, 1, 1);
    lytMain_->addWidget(btnPlay_,      2, 1, 1, 1);
    lytMain_->addWidget(btnPause_,     2, 2, 1, 1);
    lytMain_->addWidget(btnStop_,      2, 3, 1, 1);
    lytMain_->addWidget(volumeSlider_, 2, 4, 1, 1);

    //Buttons icons
    btnOpen_->setIcon(QIcon(QPixmap(":/icons/resources/eject.png")));
    btnPause_->setIcon(QIcon(QPixmap(":/icons/resources/pause.png")));
    btnPlay_->setIcon(QIcon(QPixmap(":/icons/resources/play.png")));
    btnStop_->setIcon(QIcon(QPixmap(":/icons/resources/stop.png")));

    //Connections
    connect(actArchivoRecientes_,  SIGNAL (triggered()),     this,   SLOT(CargarRecientes()));
    connect(actArchivoAbrir_,   SIGNAL(triggered()),        this,          SLOT(onOpen()));
    connect(actVerFullScreen_,   SIGNAL(triggered()),        this,         SLOT(setFullScreen()));
    //connect(volumeSlider_,   SIGNAL(sliderMoved(int)),        videoWidget_,SLOT(setBrightness(int)));
    connect(btnOpen_,      SIGNAL(pressed()),               this,          SLOT(onOpen()));
    connect(btnPlay_,      SIGNAL(pressed()),               mediaPlayer_,  SLOT(play()));
    connect(btnPause_,     SIGNAL(pressed()),               mediaPlayer_,  SLOT(pause()));
    connect(btnStop_,      SIGNAL(pressed()),               mediaPlayer_,  SLOT(stop()));
    connect(playerSlider_, SIGNAL(sliderReleased()),        this,          SLOT(onSeek()));
    connect(mediaPlayer_,  SIGNAL(durationChanged(qint64)), this,          SLOT(onDurationChanged(qint64)));
    connect(mediaPlayer_,  SIGNAL(positionChanged(qint64)), this,          SLOT(onPositionChanged(qint64)));
    connect(volumeSlider_, SIGNAL(sliderMoved(int)),        this,          SLOT(onVolumeChanged(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setFullScreen()
{
    videoWidget_->setFullScreen(!videoWidget_->isFullScreen());
}


void MainWindow::onOpen()
{
    //Show file open dialog
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo"));

    //QFile archivaso("C:\\Users\\rudolf\\Desktop\\recientes.txt");

    GuardarRecientes(fileName);

         if (fileName != "")
        {
            mediaPlayer_->setMedia(QUrl::fromLocalFile(fileName));
        }
}

void MainWindow::GuardarRecientes(QString filename)
{
    QString         dir_fichero(QUrl::fromLocalFile(filename).toEncoded());
    QFile           recent_file("jsonRecientes.txt");
    QJsonDocument   jsonDocument_;
    QJsonObject     recientes_nuevos;
    QJsonObject     recientes_viejos;
    QJsonArray      recent_array;

    if(!recent_file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning() << "NO se pudo abrir el archivo Json" ;
    else
    {
        jsonDocument_ = QJsonDocument::fromJson(recent_file.readAll()); // fromJson es una función estática.
        recientes_viejos = jsonDocument_.object();

        recent_array = recientes_viejos["recientes"].toArray();

        recent_array.prepend(dir_fichero);

        recientes_nuevos.insert("recientes",recent_array);

        jsonDocument_ = QJsonDocument(recientes_nuevos);

        recent_file.close();

        if(!recent_file.open(QIODevice::WriteOnly | QIODevice::Text ))
            qWarning() << "NO se pudo abrir el archivo Json" ;
        else
        {
            recent_file.write(jsonDocument_.toJson());
            recent_file.close();
        }
        qWarning() << "Todo bien" ;
    }
}

void MainWindow::onSeek()
{
    mediaPlayer_->setPosition(playerSlider_->sliderPosition());
}

void MainWindow::onDurationChanged(qint64 duration)
{
    playerSlider_->setRange(0, duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    playerSlider_->setSliderPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    mediaPlayer_->setVolume(volume);
}

void MainWindow::CargarRecientes()
{
    qDebug() << "Entramos en recientes" ;
    QFile archivo;
    archivo.setFileName(":/recientes.txt");
    if (archivo.open(QFile::ReadOnly))
    {
         qDebug() << archivo.readLine();
         mediaPlayer_->setMedia(QUrl::fromLocalFile("Cancion"));
    }
}

