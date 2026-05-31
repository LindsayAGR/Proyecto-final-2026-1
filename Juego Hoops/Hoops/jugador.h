#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QtMath>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Jugador(QObject *parent = nullptr);

    void mover();
    void saltar();
    void lanzar();
    void aplicarGravedad();
    void driblar();
    void soltarBalon();
    void actualizarDrible();

private:
    float velocidadY;
    int x, y;
    int velocidadX;
    bool tieneBalon;
    bool esIA;
    bool saltando;
    bool balonCayendo;
    float balonVelY;
    float anguloBalon;


    // animacion
    QTimer *timerAnimacion;
    int frameActual;
    QPixmap frames[4];

    QGraphicsPixmapItem *balon;
    bool driblando;

private slots:
    void actualizarFrame();
};

#endif // JUGADOR_H
