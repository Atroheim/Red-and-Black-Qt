#ifndef PLAYER_H
#define PLAYER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QtGlobal>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
class Player : public QObject
{
    Q_OBJECT
    int a[16];
    struct game_player {
        int ran;
        QString card;
        bool lord;
        double tic;
        bool live;
        bool vote_right;
        int k1;
        int k2;
    }person[16],W[16];
public:
    explicit Player(QObject *parent = nullptr);
    void id(QWidget *point,int num,int *a);
    void v1(QWidget *point,int num,int t,int chart[4][4]);
    void v2(QWidget *point,int num,int chart[4][4]);
    void night(QWidget *point,int num,int t);
    bool victory(QWidget *point,int num);
    void announcement(QWidget *point, int FLAG,int num);
    int islord(int num);
    bool isvictory(int num);
signals:

public slots:
};

#endif // PLAYER_H
