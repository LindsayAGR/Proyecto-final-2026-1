#include "obstaculo.h"

Obstaculo::Obstaculo(Jugador *jugador, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    this->jugador = jugador;

    srand(time(NULL));
    int randObs = rand() % 3 + 1;
    QPixmap img;

    switch (randObs) {
    case 1:
        img = QPixmap(":/Imagenes/Imagenes/obstaculo1.png");
        break;
    case 2:
        img = QPixmap(":/Imagenes/Imagenes/obstaculo2.png");
        break;
    case 3:
        img = QPixmap(":/Imagenes/Imagenes/obstaculo3.png");
        break;
    }

    img = img.transformed(QTransform().rotate(90));
    setPixmap(img.scaled(70, 90, Qt::KeepAspectRatio));

    setPos(800, 490);
    velocidad = 3.5;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Obstaculo::mover);
    timer->start(16);
}

void Obstaculo::mover()
{
    int newX = x() - velocidad;
    setPos(newX, y());

    if (collidesWithItem(jugador))
    {
        timer->stop();
        emit colision();

        if(scene())
            scene()->removeItem(this);

        deleteLater();
        return;
    }

    if (newX + pixmap().width() <= 0)
    {
        emit eliminado(this);
        if(scene())
            scene()->removeItem(this);

        emit eliminado(this);
        deleteLater();
    }
}

void Obstaculo::detenerTimer()
{
    timer->stop();
}

bool Obstaculo::detectarColision(QGraphicsPixmapItem *jugador)
{
    return collidesWithItem(jugador);
}
