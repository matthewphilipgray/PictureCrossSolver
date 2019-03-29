#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QPoint m_mousePos;
    Board *m_puzzle;
    bool draw = true;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);





private slots:

    void on_pushButton_clicked();

    void on_crossesButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
