#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include <QTimer>
#include <fileloader.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    std::vector<std::vector<unsigned int>> *settings  = new std::vector<std::vector<unsigned int>> [2];
    unpackSettings("../Boards/Medium/001.txt", settings);


    Board *puzzle = new Board(settings);

    ui->setupUi(this);
    m_puzzle = puzzle;

    //update();

    QTimer *timer = new QTimer(this); //a timer to draw the phrase as it changes
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);


}

MainWindow::~MainWindow()
{

    std::cout<<"Deleting"<<std::endl;
    //delete m_puzzle;
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    m_puzzle->draw(&painter, 100,100,500,500);

}

void MainWindow::on_pushButton_clicked()
{
    m_puzzle->iterate();
}

void MainWindow::on_crossesButton_clicked()
{
    //m_puzzle->addCrosses();
}








