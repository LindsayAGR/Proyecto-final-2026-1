#include "nivel2.h"

Nivel2::Nivel2(QWidget *parent)
    : QGraphicsView(parent), Nivel()
{
    actual = nullptr;
    puntaje = 0;
    gravedad = 0.3;

    for (int i = 0; i < 3; i++) {
        equipo[i] = nullptr;
        rival[i]  = nullptr;
    }
}

void Nivel2::iniciar()
{
    escenaN2 = new QGraphicsScene(this);
    escenaN2->setSceneRect(0,0,1600,1200);

    setScene(escenaN2);
    setFixedSize(800,600);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // fondo

    QPixmap fondoImg(":/Imagenes/Imagenes/fondo2.png");

    fondoN2 = new QGraphicsPixmapItem(
        fondoImg.scaled(
            1600,
            1200,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation));

    fondoN2->setPos(0,0);

    escenaN2->addItem(fondoN2);


    // EQUIPO AZUL

    equipo[0] = new Jugador(true,this);
    equipo[0]->setPixmapJugador(":/Imagenes/Imagenes/equipo1.1.png");
    equipo[0]->setPos(650,600);
    equipo[0]->setZValue(5);
    escenaN2->addItem(equipo[0]);

    equipo[1] = new Jugador(true,this);
    equipo[1]->setPixmapJugador(":/Imagenes/Imagenes/equipo1.2.png");
    equipo[1]->setPos(520,500);
    equipo[1]->setZValue(5);
    equipo[1]->getBalon()->hide();
    escenaN2->addItem(equipo[1]);

    equipo[2] = new Jugador(true,this);
    equipo[2]->setPixmapJugador(":/Imagenes/Imagenes/equipo1.3.png");
    equipo[2]->setPos(520,700);
    equipo[2]->setZValue(5);
    equipo[2]->getBalon()->hide();
    escenaN2->addItem(equipo[2]);


    // EQUIPO ROJO

    rival[0] = new Jugador(true,this);
    rival[0]->setPixmapJugador(":/Imagenes/Imagenes/equipo2.1.png");
    rival[0]->setPos(950,600);
    rival[0]->setZValue(5);
    rival[0]->getBalon()->hide();
    escenaN2->addItem(rival[0]);

    rival[1] = new Jugador(true,this);
    rival[1]->setPixmapJugador(":/Imagenes/Imagenes/equipo2.2.png");
    rival[1]->setPos(1100,400);
    rival[1]->setZValue(5);
    rival[1]->getBalon()->hide();
    escenaN2->addItem(rival[1]);

    rival[2] = new Jugador(true,this);
    rival[2]->setPixmapJugador(":/Imagenes/Imagenes/equipo2.3.png");
    rival[2]->setPos(1100,800);
    rival[2]->setZValue(5);
    rival[2]->getBalon()->hide();
    escenaN2->addItem(rival[2]);


    // jugador controlado

    actual = equipo[0];

    actual->getBalon()->setVisible(true);
    actual->getBalon()->setParentItem(actual);
    actual->getBalon()->setPos(20,20);




    // timers

    timerJuegoN2 = new QTimer(this);
    connect(timerJuegoN2,&QTimer::timeout,this,&Nivel2::gameLoop);
    timerJuegoN2->start(16);

    timerIA = new QTimer(this);
    connect(timerIA,&QTimer::timeout,this,&Nivel2::moverIASlot);
    timerIA->start(500);


    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Nivel2::actualizar()
{
    if(actual)
    {
        centerOn(actual);

        actual->actualizarLanzamiento(
            1400,
            600
            );
    }

    verificarPunto();


    for(int i=0;i<3;i++)
    {
        if(equipo[i]!=actual)
        {

            float dx =
                actual->scenePos().x()
                - equipo[i]->scenePos().x();

            float dy =
                actual->scenePos().y()
                - equipo[i]->scenePos().y();


            equipo[i]->setPos(

                    equipo[i]->scenePos().x()
                    + dx*0.002,

                equipo[i]->scenePos().y()
                    + dy*0.002

                );

        }
    }

}
void Nivel2::controlarJugador(QKeyEvent *evento)
{
    if (!actual) return;

    if (evento->key() == Qt::Key_W)
        actual->setPos(actual->pos().x(),
                       actual->pos().y()-5);

    if (evento->key() == Qt::Key_S)
        actual->setPos(actual->pos().x(),
                       actual->pos().y()+5);

    if (evento->key() == Qt::Key_A)
        actual->setPos(actual->pos().x()-5,
                       actual->pos().y());

    if (evento->key() == Qt::Key_D)
        actual->setPos(actual->pos().x()+5,
                       actual->pos().y());

    for(int i=0;i<3;i++)
    {
        if(actual->collidesWithItem(rival[i]))
        {
            rival[i]->getBalon()->setParentItem(actual);

            rival[i]->getBalon()->setPos(20,20);
        }
    }


    if (evento->key() == Qt::Key_Space) cambiarJugador();
    if (evento->key() == Qt::Key_R)     pasarBalon();
    if (evento->key() == Qt::Key_Return) lanzarBalon();
}

void Nivel2::cambiarJugador()
{
    actual->getBalon()->setVisible(false);

    for(int i=0;i<3;i++)
    {
        if(equipo[i]==actual)
        {
            actual = equipo[(i+1)%3];
            break;
        }
    }

    actual->getBalon()->setVisible(true);
}

void Nivel2::pasarBalon()
{
    Jugador *anterior=actual;

    for(int i=0;i<3;i++)
    {
        if(equipo[i]==actual)
        {
            actual=
                equipo[(i+1)%3];

            break;
        }
    }

    anterior->getBalon()->setVisible(false);

    anterior->getBalon()->setParentItem(nullptr);

    actual->getBalon()->setVisible(true);

    actual->getBalon()->setParentItem(actual);

    actual->getBalon()->setPos(20,20);
}

void Nivel2::lanzarBalon()
{
    if (actual) actual->lanzar();
}

void Nivel2::robarBalon()
{
    // colision con rival
    for (int i = 0; i < 3; i++) {
        if (rival[i] && actual && actual->collidesWithItem(rival[i])) {
            // robo exitoso
            break;
        }
    }
}

void Nivel2::moverIA()
{
    for(int i=0;i<3;i++)
    {
        if(rival[i] && actual)
        {

            float dx =
                actual->getBalon()->scenePos().x()
                - rival[i]->pos().x();

            float dy =
                actual->getBalon()->scenePos().y()
                - rival[i]->pos().y();


            if(dx > 0)
                rival[i]->setPos(
                    rival[i]->pos().x()+3,
                    rival[i]->pos().y()
                    );

            if(dx < 0)
                rival[i]->setPos(
                    rival[i]->pos().x()-3,
                    rival[i]->pos().y()
                    );


            if(dy > 0)
                rival[i]->setPos(
                    rival[i]->pos().x(),
                    rival[i]->pos().y()+3
                    );

            if(dy < 0)
                rival[i]->setPos(
                    rival[i]->pos().x(),
                    rival[i]->pos().y()-3
                    );



            // robo balón

            if(rival[i]->collidesWithItem(
                    actual->getBalon()))
            {
                actual->getBalon()->setParentItem(
                    rival[i]);

                actual->getBalon()->setPos(
                    20,
                    20
                    );
            }

        }
    }
}


void Nivel2::verificarPunto()
{
    // aquí irá la lógica de enceste
}

void Nivel2::keyPressEvent(QKeyEvent *evento)
{
    controlarJugador(evento);
}

void Nivel2::keyReleaseEvent(QKeyEvent *evento)
{
    Q_UNUSED(evento);
}

void Nivel2::gameLoop()
{
    actualizar();


}

void Nivel2::moverIASlot()
{
    moverIA();
}
