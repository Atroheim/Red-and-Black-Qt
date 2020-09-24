#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <player.h>
#include <QKeyEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QTime>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *button;
    QPushButton *button1;
    bool state;//游戏状态
    int chart[4][4];
    void paintEvent(QPaintEvent*);
    Player *b;
    int num;
    int t;
public slots:
    void slotStart();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
