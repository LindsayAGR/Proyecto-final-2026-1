#include "nivel1.h"

Nivel1::Nivel1(QWidget *parent)
    : QGraphicsView(parent), Nivel()
{
    jugador = nullptr;
    aro = nullptr;
    lanzando = false;
    juegoTerminado = false;
    cantObstaculos = 0;
    faseLanzamiento = false;

    for (int i = 0; i < 20; i++)
        obstaculos[i] = nullptr;
}

void Nivel1::iniciar()
{
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 800, 600);
    setScene(escena);

    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // fondo
    QPixmap fondoImg(":/Imagenes/Imagenes/fondo_nivel1.png");
    fondoImg = fondoImg.scaled(fondoImg.width(), 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bgImageFon1 = new QGraphicsPixmapItem(fondoImg);
    bgImageFon2= new QGraphicsPixmapItem(fondoImg);
    bgImageFon1->setPos(0, 0);
    QPixmap fondoEspejo = fondoImg.transformed(QTransform().scale(-1, 1));
    bgImageFon2 = new QGraphicsPixmapItem(fondoEspejo);
    bgImageFon2->setPos(fondoImg.width(), 0);
    escena->addItem(bgImageFon2);
    escena->addItem(bgImageFon1);

    //timer para mover fondo
    bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, this, &Nivel1::moverFondo);
    bgTimer->start(16);

    // jugador
    jugador = new Jugador(this);
    jugador->setPos(100, 450);
    escena->addItem(jugador);

    connect(jugador, &Jugador::balonCayo, this, &Nivel1::restarVidaBalon);

    // timer juego
    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Nivel1::gameLoop);
    timerJuego->start(16);

    contadorSpawn = 0;
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &Nivel1::spawnObstaculo);
    spawnTimer->start(2000);



    // cronometro
    tiempoRestante = 20;
    textoTiempo = new QGraphicsTextItem();
    textoTiempo->setDefaultTextColor(Qt::white);
    textoTiempo->setFont(QFont("Arial", 20, QFont::Bold));
    textoTiempo->setPos(350, 10);
    textoTiempo->setZValue(50);
    textoTiempo->setPlainText("0:20");
    escena->addItem(textoTiempo);

    timerCronometro = new QTimer(this);
    connect(timerCronometro, &QTimer::timeout, this, &Nivel1::actualizarCronometro);
    timerCronometro->start(1000);

    // vidas
    vidas = 3;
    vida1 = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/vidas1.png").scaled(120, 80, Qt::KeepAspectRatio));
    vida2 = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/vidas2.png").scaled(120, 80, Qt::KeepAspectRatio));
    vida3 = new QGraphicsPixmapItem(QPixmap(":/Imagenes/Imagenes/vidas3.png").scaled(120, 80, Qt::KeepAspectRatio));
    vida1->setPos(10, 10);
    vida2->setPos(10, 10);
    vida3->setPos(10, 10);
    vida1->setZValue(50);
    vida2->setZValue(50);
    vida3->setZValue(50);
    escena->addItem(vida1);
    escena->addItem(vida2);
    escena->addItem(vida3);
    actualizarVidas();

    setFocus();
}

void Nivel1::actualizar()
{

    //gravedad

    jugador->aplicarGravedad();
    jugador->actualizarDrible();


}

void Nivel1::controlarJugador(QKeyEvent *evento)
{
    qDebug() << "Tecla detectada:" << evento->key();

    if (evento->key() == Qt::Key_Space)
        jugador->saltar();

    if (evento->key() == Qt::Key_Control)
        jugador->driblar();

    if (evento->key() == Qt::Key_Return && faseLanzamiento)
    {
        qDebug() << "ENTER PRESIONADO";
        jugador->lanzar();
    }

    if (evento->key() == Qt::Key_O && faseLanzamiento)
        jugador->subirAngulo();

    if (evento->key() == Qt::Key_L && faseLanzamiento)
        jugador->bajarAngulo();

    if (evento->key() == Qt::Key_Return)
    {
        qDebug()<<"fase lanzamiento ="<<faseLanzamiento;
    }
}


void Nivel1::keyPressEvent(QKeyEvent *evento)
{
    qDebug() << "tecla presionada:" << evento->key();
    controlarJugador(evento);
}

void Nivel1::keyReleaseEvent(QKeyEvent *evento)
{
    if (evento->key() == Qt::Key_Control) {
        jugador->soltarBalon();
    }
}

void Nivel1::gameLoop()
{
    actualizar();
}

void Nivel1::moverFondo()
{
    bgImageFon1->setPos(bgImageFon1->x() - 4, 0);
    bgImageFon2->setPos(bgImageFon2->x() - 4, 0);

    if (bgImageFon1->x() <= -bgImageFon1->pixmap().width())
        bgImageFon1->setPos(bgImageFon2->x() + bgImageFon2->pixmap().width(), 0);

    if (bgImageFon2->x() <= -bgImageFon2->pixmap().width())
        bgImageFon2->setPos(bgImageFon1->x() + bgImageFon1->pixmap().width(), 0);
}

void Nivel1::spawnObstaculo()
{
    Obstaculo *obs = new Obstaculo(jugador, this);

    connect(obs, &Obstaculo::colision, this, &Nivel1::mostrarGameOver);
    connect(obs, &Obstaculo::eliminado, this, &Nivel1::eliminarObstaculo);


    escena->addItem(obs);

    if(cantObstaculos < 20)
    {
        obstaculos[cantObstaculos] = obs;
        cantObstaculos++;
    }
}
void Nivel1::mostrarGameOver()
{
    if (juegoTerminado) return;

    vidas--;
    actualizarVidas();

    if (vidas > 0) return;

    juegoTerminado = true;
    timerJuego->stop();
    bgTimer->stop();
    spawnTimer->stop();
    timerCronometro->stop();
    jugador->detenerAnimacion();

    for (int i = 0; i < cantObstaculos; i++)
        if (obstaculos[i]) obstaculos[i]->detenerTimer();

    QPixmap imgGameOver(":/Imagenes/Imagenes/gameOver.png");
    imgGameOver = imgGameOver.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *pantallaGameOver = new QGraphicsPixmapItem(imgGameOver);
    pantallaGameOver->setPos(0, 0);
    pantallaGameOver->setZValue(100);
    escena->addItem(pantallaGameOver);

    btnReiniciar = new QPushButton("REINICIAR", this);
    btnReiniciar->setGeometry(300, 400, 200, 50);
    btnReiniciar->show();
    connect(btnReiniciar, &QPushButton::clicked, this, &Nivel1::reiniciar);
}

void Nivel1::reiniciar()
{
    btnReiniciar->hide();
    escena->clear();
    jugador = nullptr;
    aro = nullptr;
    cantObstaculos = 0;
    tiempoRestante = 30;
    juegoTerminado = false;
    iniciar();
}

void Nivel1::actualizarVidas()
{
    vida1->setVisible(vidas == 1);
    vida2->setVisible(vidas == 2);
    vida3->setVisible(vidas == 3);
}

void Nivel1::eliminarObstaculo(Obstaculo *obs)
{
    for(int i=0; i<cantObstaculos; i++)
    {
        if(obstaculos[i] == obs)
        {
            obstaculos[i] = nullptr;
            break;
        }
    }
}
void Nivel1::actualizarCronometro()
{
    tiempoRestante--;

    int mins = tiempoRestante / 60;
    int segs = tiempoRestante % 60;
    QString texto = QString::number(mins) + ":" +
                    (segs < 10 ? "0" : "") + QString::number(segs);
    textoTiempo->setPlainText(texto);

    if (tiempoRestante <= 0)
    {
        timerCronometro->stop();
        tiempoAgotado();
    }
}

void Nivel1::tiempoAgotado()
{

   // timerJuego->stop();
    faseLanzamiento = true;
    juegoTerminado = true;
    bgTimer->stop();
    spawnTimer->stop();
    jugador->detenerAnimacion();

    for (int i = 0; i < cantObstaculos; i++) {
        if (obstaculos[i]) {
            disconnect(obstaculos[i], &Obstaculo::colision, this, &Nivel1::mostrarGameOver);
            obstaculos[i]->detenerTimer();
        }
    }

    QGraphicsTextItem *txtVictoria = new QGraphicsTextItem("NIVEL COMPLETADO\nPresiona Enter para lanzar");
    txtVictoria->setDefaultTextColor(Qt::yellow);
    txtVictoria->setFont(QFont("Arial", 28, QFont::Bold));
    txtVictoria->setPos(130, 220);
    txtVictoria->setZValue(100);
    escena->addItem(txtVictoria);

    // mostrar aro
    QPixmap imgAro(":/Imagenes/Imagenes/aro.png");
    aro = new QGraphicsPixmapItem(imgAro.scaled(100, 120, Qt::KeepAspectRatio));
    aro->setPos(600, 250);
    aro->setZValue(10);
    escena->addItem(aro);

    connect(jugador, &Jugador::encesto, this, &Nivel1::nivelCompletado);
    connect(jugador, &Jugador::fallo,   this, &Nivel1::lanzamientoFallido);

    timerLanzamiento = new QTimer(this);
    connect(timerLanzamiento, &QTimer::timeout, this, &Nivel1::actualizarLanzamiento);
    timerLanzamiento->start(16);

    timerTexto = new QTimer(this);
    connect(timerTexto, &QTimer::timeout, this, [=](){
        escena->removeItem(txtVictoria);
        timerTexto->stop();
    });
    timerTexto->start(3000);

}

void Nivel1::nivelCompletado()
{
    timerLanzamiento->stop();
   jugador->getBalon()->setPos(aro->x() + 35, aro->y() + 60);

    QGraphicsTextItem *txt = new QGraphicsTextItem("¡ENCESTADO! Nivel 1 completado");
    txt->setDefaultTextColor(Qt::yellow);
    txt->setFont(QFont("Arial", 24, QFont::Bold));
    txt->setPos(100, 250);
    txt->setZValue(100);
    escena->addItem(txt);



    btnNivel2 = new QPushButton("IR AL NIVEL 2", this);
    btnNivel2->setGeometry(300, 400, 200, 50);
    btnNivel2->show();
    connect(btnNivel2, &QPushButton::clicked, this, &Nivel1::irNivel2);
}

void Nivel1::irNivel2()
{
    emit pasarNivel2();
}

void Nivel1::lanzamientoFallido()
{
    QGraphicsTextItem *txt = new QGraphicsTextItem("¡Fallaste! Intenta de nuevo");
    txt->setDefaultTextColor(Qt::red);
    txt->setFont(QFont("Arial", 24, QFont::Bold));
    txt->setPos(150, 250);
    txt->setZValue(100);
    escena->addItem(txt);
}

void Nivel1::actualizarLanzamiento()
{
    if (aro != nullptr)
        jugador->actualizarLanzamiento(aro->x() + 50, aro->y() + 30);
}

void Nivel1::restarVidaBalon()
{
    if (juegoTerminado) return;
    vidas--;
    actualizarVidas();

    QGraphicsTextItem *txt = new QGraphicsTextItem("¡Soltaste el balón! -1 vida");
    txt->setDefaultTextColor(Qt::red);
    txt->setFont(QFont("Arial", 24, QFont::Bold));
    txt->setPos(200, 200);
    txt->setZValue(100);
    escena->addItem(txt);

    QTimer::singleShot(2000, this, [=](){
        escena->removeItem(txt);
        delete txt;
    });

    if (vidas <= 0)
        mostrarGameOver();
}
