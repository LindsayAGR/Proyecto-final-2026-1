#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    lanzando = false;
    driblando = false;
    balonCayendo = false;
    balonVelY = 0;
    anguloLanzamiento = -20;
    anguloBalon = 0;
    x = 100; y = 450;
    velocidadX = 5;
    velocidadY = 0;
    saltando = false;
    tieneBalon = false;
    esIA = false;
    frameActual = 0;

    frames[0] = QPixmap(":/Imagenes/Imagenes/juga1.1.png").scaled(80, 100, Qt::KeepAspectRatio);
    frames[1] = QPixmap(":/Imagenes/Imagenes/juga1.2.png").scaled(80, 100, Qt::KeepAspectRatio);
    frames[2] = QPixmap(":/Imagenes/Imagenes/juga1.3.png").scaled(80, 100, Qt::KeepAspectRatio);
    frames[3] = QPixmap(":/Imagenes/Imagenes/juga1.4.png").scaled(80, 100, Qt::KeepAspectRatio);
    setPixmap(frames[0]);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Jugador::actualizarFrame);
    timerAnimacion->start(150);

    balon = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/balon.png").scaled(30, 30, Qt::KeepAspectRatio));
    balon->setParentItem(this);
    balon->setPos(40, 60);
}

Jugador::Jugador(bool esNivel2, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    lanzando = false;
    driblando = false;
    balonCayendo = false;
    balonVelY = 0;
    anguloLanzamiento = -20;
    anguloBalon = 0;
    x = 0; y = 0;
    velocidadX = 0;
    velocidadY = 0;
    saltando = false;
    tieneBalon = false;
    esIA = false;
    frameActual = 0;

    if (!esNivel2) {
        // cargar frames nivel 1
        frames[0] = QPixmap(":/Imagenes/Imagenes/juga1.1.png").scaled(80, 100, Qt::KeepAspectRatio);
        frames[1] = QPixmap(":/Imagenes/Imagenes/juga1.2.png").scaled(80, 100, Qt::KeepAspectRatio);
        frames[2] = QPixmap(":/Imagenes/Imagenes/juga1.3.png").scaled(80, 100, Qt::KeepAspectRatio);
        frames[3] = QPixmap(":/Imagenes/Imagenes/juga1.4.png").scaled(80, 100, Qt::KeepAspectRatio);
        setPixmap(frames[0]);
        timerAnimacion = new QTimer(this);
        connect(timerAnimacion, &QTimer::timeout, this, &Jugador::actualizarFrame);
        timerAnimacion->start(150);
    }

    balon = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/balon.png").scaled(30, 30, Qt::KeepAspectRatio));
    balon->setParentItem(this);
    balon->setPos(40, 60);
}

void Jugador::actualizarFrame()
{
    frameActual = (frameActual + 1) % 4;
    setPixmap(frames[frameActual]);

    if (balonCayendo) {
        balonVelY += 1;
        balon->setPos(balon->x() - 3, balon->y() + balonVelY);

        if (balon->y() > 600) {
            balonCayendo = false;
            emit balonCayo();
        }
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
    if (lanzando) return;
    lanzando = true;
    driblando = false;
    balonCayendo = false;
    balonVelY = anguloLanzamiento;
    balonVelX = 12;
    balon->setParentItem(nullptr);
    balon->setPos(scenePos().x() + 40, scenePos().y() + 30);
    balon->setZValue(20);
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

void Jugador::subirAngulo()
{
    if (anguloLanzamiento > -25) anguloLanzamiento -= 1;
}

void Jugador::bajarAngulo()
{
    if (anguloLanzamiento < -10) anguloLanzamiento += 1;
}

void Jugador::setPixmapJugador(QString ruta)
{
    // limpiar frames anteriores
    for (int i = 0; i < 4; i++)
        frames[i] = QPixmap();

    QPixmap img(ruta);
    setPixmap(img.scaled(50, 60, Qt::KeepAspectRatio));
}

QGraphicsPixmapItem* Jugador::getBalon()
{
    return balon;
}
