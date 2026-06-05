#include "widget.h"
#include "ui_widget.h"
#include "nivel1.h"



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
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//fondo
    QPixmap portada(":/Imagenes/Imagenes/inicio.png");
    bgInicio = new QGraphicsPixmapItem(portada);
    bgInicio->setPos(0, 0);
    bgInicio->setScale(0.7);
    sceneInicio->addItem(bgInicio);

//bton inicio
    btnPlay = new QPushButton("", this);
    btnPlay->setGeometry(370, 510, 168, 55);
    connect(btnPlay, &QPushButton::clicked, this, &Widget::iniciarNivel1);

//musica
    musicaInicio = new QMediaPlayer(this);
    QAudioOutput *sonido = new QAudioOutput(this);
    musicaInicio->setAudioOutput(sonido);
    musicaInicio->setSource(QUrl("qrc:/sonidos/Sonidos/Start1.mp3"));
    sonido->setVolume(0.3);
    musicaInicio->play();
}

void Widget::iniciarNivel1()
{
    btnPlay->hide();
    musicaInicio->stop();
    ui->graphicsView->hide();


    nivel1 = new Nivel1(this);
    nivel1->setGeometry(0, 0, 800, 600);
    nivel1->iniciar();
    nivel1->show();
    setFixedSize(800, 600);

    connect(nivel1, &Nivel1::pasarNivel2, this, &Widget::iniciarNivel2);

}

void Widget::iniciarNivel2()
{
    nivel1->hide();
    nivel2 = new Nivel2(this);
    nivel2->setGeometry(0, 0, 800, 600);
    nivel2->iniciar();
    nivel2->show();
}
