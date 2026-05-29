#include "nivel1.h"

Nivel1::Nivel1(QWidget *parent)
    : QGraphicsView(parent), Nivel()
{
    jugador = nullptr;
}

void Nivel1::iniciar()
{
    escena = new QGraphicsScene(this);
    setScene(escena);
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // fondo
    QPixmap fondoImg(":/Imagenes/Imagenes/fondo_nivel1.png");
    fondoImg = fondoImg.scaled(fondoImg.width(), 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bgImageFon1 = new QGraphicsPixmapItem(fondoImg);
    bgImageFon2= new QGraphicsPixmapItem(fondoImg);
    bgImageFon1->setPos(0, 0);
    QPixmap fondoEspejo = fondoImg.transformed(QTransform().scale(-1, 1));
    bgImageFon2 = new QGraphicsPixmapItem(fondoEspejo);
    bgImageFon2->setPos(fondoImg.width(), 0);
    escena->addItem(bgImageFon2);
    escena->addItem(bgImageFon1);

    //timer para mover fondo
    bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, this, &Nivel1::moverFondo);
    bgTimer->start(16);

    // jugador
    jugador = new Jugador(this);
    jugador->setPos(100, 400);
    escena->addItem(jugador);

    // timer juego
    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Nivel1::gameLoop);
    timerJuego->start(16);
}

void Nivel1::actualizar()
{
    // mover jugador
    jugador->mover();
}

void Nivel1::controlarJugador(QKeyEvent *evento)
{
    if (evento->key() == Qt::Key_D)
        jugador->mover();
    if (evento->key() == Qt::Key_Space)
        jugador->saltar();
}

void Nivel1::keyPressEvent(QKeyEvent *evento)
{
    controlarJugador(evento);
}

void Nivel1::keyReleaseEvent(QKeyEvent *evento)
{
    Q_UNUSED(evento);
}

void Nivel1::gameLoop()
{
    actualizar();
}

void Nivel1::moverFondo()
{
    bgImageFon1->setPos(bgImageFon1->x() - 0.5, 0);
    bgImageFon2->setPos(bgImageFon2->x() - 0.5, 0);

    if (bgImageFon1->x() <= -bgImageFon1->pixmap().width())
        bgImageFon1->setPos(bgImageFon2->x() + bgImageFon2->pixmap().width(), 0);

    if (bgImageFon2->x() <= -bgImageFon2->pixmap().width())
        bgImageFon2->setPos(bgImageFon1->x() + bgImageFon1->pixmap().width(), 0);
}
