#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            chart[i][j]=0;
        }
    }//初始化
    button=new QPushButton("START!",this);
    button->setIcon(icon);
    button1=new QPushButton("QUIT.",this);
    button->setGeometry(60,370,200,50);
    button1->setGeometry(60,420,200,50);
    b=new Player;
    qsrand(uint(QTime(0,0,0).secsTo((QTime::currentTime()))));//随机种子
    //槽与信号
    connect(button,SIGNAL(clicked()),this,SLOT(slotStart()));
    connect(button1,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setBrush(Qt::white);
    p.setFont(QFont("微软雅黑",20,700,false));
    //格子的实现
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            p.setPen(Qt::transparent);
            if(chart[i][j]==0){
                p.setBrush(Qt::gray);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(i*4+(j+1)),QTextOption(Qt::AlignCenter));//编号居中实现
            }
            else if(chart[i][j]==1){
                p.setBrush(Qt::green);
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(i*4+(j+1)),QTextOption(Qt::AlignCenter));//编号居中实现
            }
            else if(chart[i][j]==-1){
                p.setBrush((Qt::red));
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(i*4+(j+1)),QTextOption(Qt::AlignCenter));//编号居中实现
            }
            else if(chart[i][j]==-2){
                p.setBrush((Qt::black));
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::white);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(i*4+(j+1)),QTextOption(Qt::AlignCenter));//编号居中实现
            }
            else if(chart[i][j]==2){
                p.setBrush((Qt::blue));
                p.drawRect(i*60+40,j*60+120,55,55);
                p.setPen(Qt::white);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(i*4+(j+1)),QTextOption(Qt::AlignCenter));//编号居中实现
            }
        }
    }
}

void MainWindow::slotStart(){
    //游戏开始或者游戏重新开始
    button->setText("RESTART!");
    QMessageBox::about(this,"Rules of the game.","Vote to exile all your enemies.");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            chart[i][j]=0;
        }
    }
    int a[16]={0};
    num=QInputDialog::getInt(this,"The game has started.","Now please input the total of players(no less than 5 and no more than 16)",5,5,16,1);
    t=num;
    int i=0,j=0;
    while(i*4+j+1<=num){
        chart[i][j]=1;
        j++;
        if(j==4)
        {
            j=0;
            i++;
        }
    }//全体格子置一，全部为绿色
    b->id(this,num,a);
    QMessageBox::information(this,"Red and Black Judges","Now please elect the lord.");
    int f=0;
    b->announcement(this,f,num);
    b->v2(this,num,chart);
    while(1){
        QMessageBox::information(this,"NIGHT","Night comes.");
        b->night(this,num,t);
        QMessageBox::information(this,"Red and Black Judges","Day comes. Now each living player has to make a statement.");
        f=b->islord(num);
        b->announcement(this,f,num);
        QMessageBox::information(this,"Red and Black Judges","Please vote against the player you distrust the most.");
        b->v1(this,num,t,chart);
        bool flag=b->victory(this,num);
        if(flag)
            break;
    }
}
