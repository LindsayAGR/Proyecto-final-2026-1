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
    x = 100;
    y = 450;
    anguloBalon = 0;

    // cargar frames
    frames[0] = QPixmap(":/Imagenes/Imagenes/juga1.1.png");
    frames[1] = QPixmap(":/Imagenes/Imagenes/juga1.2.png");
    frames[2] = QPixmap(":/Imagenes/Imagenes/juga1.3.png");
    frames[3] = QPixmap(":/Imagenes/Imagenes/juga1.4.png");

    frames[0] = frames[0].scaled(80, 100, Qt::KeepAspectRatio);
    frames[1] = frames[1].scaled(80, 100, Qt::KeepAspectRatio);
    frames[2] = frames[2].scaled(80, 100, Qt::KeepAspectRatio);
    frames[3] = frames[3].scaled(80, 100, Qt::KeepAspectRatio);
    setPixmap(frames[0]);

    // timer animacion
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Jugador::actualizarFrame);
    timerAnimacion->start(150);

    // balon
    balon = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/balon.png").scaled(30, 30, Qt::KeepAspectRatio));
    balon->setParentItem(this);
    balon->setPos(40, 60);
    driblando = false;
    balonCayendo = false;
    balonVelY = 0;

}

void Jugador::actualizarFrame()
{
    frameActual = (frameActual + 1) % 4;
    setPixmap(frames[frameActual]);

    if (balonCayendo) {
        balonVelY += 1;
        balon->setPos(balon->x() - 3, balon->y() + balonVelY);
    }
}

void Jugador::mover()
{
    x += velocidadX;
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
    if (balonCayendo || lanzando) return;
    lanzando = true;
    driblando = false;
    balonVelY = -20;
    balonVelX = 12;
    balon->setParentItem(nullptr);
    balon->setPos(scenePos().x() + 40, scenePos().y() + 30);
}

void Jugador::aplicarGravedad()
{
    if (saltando) {
        velocidadY += 1;
        y += velocidadY;
        if (y >= 450) {
            y = 450;
            velocidadY = 0;
            saltando = false;
        }
        setPos(x, y);
    }
}


void Jugador::driblar()
{
    balon->setParentItem(this);

    driblando = true;

    balonCayendo = false;
}

void Jugador::soltarBalon()
{
    driblando = false;
    balonCayendo = true;
    balonVelY = 0;
    balon->setParentItem(nullptr);
    balon->setPos(scenePos().x() + 40, scenePos().y() + 60);
}

void Jugador::actualizarDrible()
{
    if(driblando)
    {
        anguloBalon += 0.1;

        if(anguloBalon > 6.28)
            anguloBalon = 0;

        float nuevaY = 50 + 20*qSin(anguloBalon);

        balon->setPos(40,nuevaY);
    }
}

void Jugador::detenerAnimacion()
{
    timerAnimacion->stop();
}


void Jugador::actualizarLanzamiento(float aroX, float aroY)
{
    if (!lanzando) return;

    balonVelY += 0.8;
    balon->setPos(balon->x() + balonVelX, balon->y() + balonVelY);

    if (qAbs(balon->x() - aroX) < 40 && qAbs(balon->y() - aroY) < 40) {
        lanzando = false;
        emit encesto();
    }

    if (balon->x() > 850 || balon->y() > 650) {
        lanzando = false;
        emit fallo();
    }
}
