#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Obstaculo(QObject *parent = nullptr);

    bool detectarColision(QGraphicsPixmapItem *jugador);
    void mover();

private:
    float velocidad;
    QTimer *timer;
};

#endif // OBSTACULO_H
