#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Nivel
{
public:
    Nivel();
    virtual ~Nivel();

    virtual void iniciar()    = 0;
    virtual void actualizar() = 0;
    void aplicarGravedad(float &velocidadY, float &y);

protected:
    int balonX;
    int balonY;
    float gravedad;

    QGraphicsPixmapItem *balon;
    QGraphicsScene      *escena;
    QTimer              *timerJuego;
};

#endif // NIVEL_H
