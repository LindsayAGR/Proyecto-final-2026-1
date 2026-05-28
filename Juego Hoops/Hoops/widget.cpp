#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mostrarInicio();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mostrarInicio()
{
    sceneInicio = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setScene(sceneInicio);

    QPixmap portada(":/Imagenes/Imagenes/inicio.png");
    bgInicio = new QGraphicsPixmapItem(portada);
    bgInicio->setPos(0, 0);
    sceneInicio->addItem(bgInicio);

    btnPlay = new QPushButton("", this);
    btnPlay->setGeometry(290, 510, 220, 55);
    connect(btnPlay, &QPushButton::clicked, this, &Widget::iniciarNivel1);

    musicaInicio = new QMediaPlayer(this);
    QAudioOutput *sonido = new QAudioOutput(this);
    musicaInicio->setAudioOutput(sonido);
    musicaInicio->setSource(QUrl("qrc:/sonidos/Sonidos/Start1.mp3"));
    sonido->setVolume(0.3);
    musicaInicio->play();
}

void Widget::iniciarNivel1()
{
    // aquí irá el nivel 1
}
