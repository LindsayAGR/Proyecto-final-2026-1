#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Jugador(QObject *parent = nullptr);

    void mover();
    void saltar();
    void lanzar();

private:
    float velocidadY;
    int x, y;
    int velocidadX;
    bool tieneBalon;
    bool esIA;
    bool saltando;

    // animacion
    QTimer *timerAnimacion;
    int frameActual;
    QPixmap frames[4];

private slots:
    void actualizarFrame();
};

#endif // JUGADOR_H
