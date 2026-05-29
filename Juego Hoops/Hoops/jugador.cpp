#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    // atributos
    velocidadY = 0;
    velocidadX = 5;
    tieneBalon = false;
    esIA       = false;
    saltando   = false;
    frameActual = 0;

    // cargar frames
    frames[0] = QPixmap(":/Imagenes/Imagenes/juga1.1.png");
    frames[1] = QPixmap(":/Imagenes/Imagenes/juga1.2.png");
    frames[2] = QPixmap(":/Imagenes/Imagenes/juga1.3.png");
    frames[3] = QPixmap(":/Imagenes/Imagenes/juga1.4.png");

    setPixmap(frames[0]);

    // timer animacion
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Jugador::actualizarFrame);
    timerAnimacion->start(150);
}

void Jugador::actualizarFrame()
{
    frameActual = (frameActual + 1) % 4;
    setPixmap(frames[frameActual]);
}

void Jugador::mover()
{
    setPos(x, y);
}

void Jugador::saltar()
{
    if (!saltando) {
        saltando   = true;
        velocidadY = -15;
    }
}

void Jugador::lanzar()
{
    // aquí irá el lanzamiento del balón
}
