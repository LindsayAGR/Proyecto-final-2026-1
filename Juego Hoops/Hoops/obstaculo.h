#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>
#include "jugador.h"

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Obstaculo(Jugador *jugador, QObject *parent = nullptr);

    bool detectarColision(QGraphicsPixmapItem *jugador);
    void mover();
    void detenerTimer();

signals:
    void colision();
    void eliminado(Obstaculo *obs);

private:
    float velocidad;
    QTimer *timer;
    Jugador *jugador;
};

#endif // OBSTACULO_H
