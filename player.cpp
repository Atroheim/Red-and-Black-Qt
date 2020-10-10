#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

void Player::id(QWidget *point,int num,int *a)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int n=0,i,t;
    for(i=0;i<num;i++){
        t= qrand()%num+1;
        for(i=0;i<n;i++)
            if(t==a[i]) break;
        if(i==n) {
            a[n]=t;
            n++;
        }
        t=rand()%num+1;
    }
    for(i=0; i<num; i++) {
        person[i].live=true;
        person[i].ran=a[i];
        person[i].tic=1;
        if(person[i].ran%2)
            person[i].card="RED";
        else
            person[i].card="BLACK";
        QMessageBox::information(point,"CONFIRM YOUR IDENTITY","NO."+QString::number(i+1)+". Your identity is "+person[i].card);
    }
}
bool Player::victory(QWidget *point,int num)
{
    int i=0;
    bool flag1=false,flag2=false;
    for(;i<num;i++){
        if(person[i].live&&person[i].card=="RED")
            flag1=true;
        if(person[i].live&&person[i].card=="BLACK")
            flag2=true;
    }
    if(!flag1) {
        QMessageBox::information(point,"Game Over","BLACK wins！");
        return true;
    }
    else if(!flag2) {
        QMessageBox::information(point,"Game Over","RED wins！");
        return true;
    }
    return false;
}

void Player::announcement(QWidget *point, int FLAG,int num)
{
    int i;
    if(FLAG==0){
        for(i=0;i<num;i++){
            QMessageBox::information(point,"ANNOUNCEMENT","NO."+QString::number(i+1)+" is making an announcement.");
        }
        return;
    }
    if(QMessageBox::Yes==QMessageBox::question(point,"ANNOUNCEMENT","Now let the lord choose the order of statements.",QMessageBox::Yes|QMessageBox::No))
    {
        int i=FLAG;
        if(i>=num)
            i=0;
        for(int j=0;j<num;j++){
            if(!person[i].live){
                i++;
                continue;
            }
            QMessageBox::information(point,"ANNOUNCEMENT","NO."+QString::number(i+1)+" is making an announcement.");
            i++;
            if(i>=num)
                i=0;
        }
    }
    else {
        int i=FLAG-2;
        if(i<0)
            i=num-1;
        while(!person[i].live){
            i--;
            if(i<0)
                i=num-1;
        }

        for(int j=0;j<num;j++){
            if(!person[i].live){
                i++;
                continue;
            }
            QMessageBox::information(point,"ANNOUNCEMENT","NO."+QString::number(i+1)+" is making an announcement.");
            i++;
            if(i>=num)
                i=0;
        }
    }
}

int Player::islord(int num)
{
    int i;
    for(i=0;i<num;i++)
        if(person[i].live&&person[i].lord)
            break;
    return i+1;
}

bool Player::isvictory(int num)
{
    int i=0;
    bool flag1=false,flag2=false;
    for(;i<num;i++){
        if(person[i].live&&person[i].card=="RED")
            flag1=true;
        if(person[i].live&&person[i].card=="BLACK")
            flag2=true;
    }
    if(!flag1) {
        return true;
    }
    else if(!flag2) {
        return true;
    }
    return false;
}

void Player::v1(QWidget *point,int num,int t,int chart[4][4])
{
    QString c;
    for(int i=0; i<num; i++)
        person[i].k1=0;
    int x;
    for(int i=0; i<num; i++) {
        if(person[i].live)
            person[i].vote_right=true;
        else
            person[i].vote_right=false;
    }
    for(int i=0; i<num; i++) {
        if(person[i].live) {
            x=QInputDialog::getInt(point,"Exile your foe."+QString::number(i+1),"Vote against.",1,1,16);
            while(person[x-1].live==false&&x!=0) {
                QMessageBox::critical(point,"Exile your foe."+QString::number(i+1),"You must vote against whom still exists.");
                x=QInputDialog::getInt(point,"Exile your foe."+QString::number(i+1),"Vote against.",1,1,16);
            }
            if(x==0)
                QMessageBox::information(point,"Exile your foe."+QString::number(i+1),"You have abstained in the vote.");
            else {
                QMessageBox::information(point,"Exile your foe."+QString::number(i+1),"You have voted against NO."+QString::number(x));
                person[x-1].k1+=person[i].tic;
            }
        } else QMessageBox::critical(point,"Exile your foe."+QString::number(i+1),"You have been exiled and you can't vote.");
    }
    for(int i=0; i<=num; i++) {
        W[i]=person[i];
    }
    for(int i=0;i<num-1;i++){
        for(int j=0;j<num-1-i;j++){
            if(W[j].k1<W[j+1].k1){
                int temp=W[j].k1;
                W[j].k1=W[j+1].k1;
                W[j+1].k1=temp;
            }
        }
    }
    while(W[0].k1==W[1].k1) {
        for(int i=0; i<=num; i++) {
            if(W[0].k1!=person[i].k1)
                person[i].vote_right=false;
            if(person[i].k1==W[1].k1) {
                c=c+QString::number(i+1)+" ";
            }
        }
        QMessageBox::information(point,"LORD ELECTION",c+"are now in stalement. Now a new round of vote is to commence.");
        for(int i=0; i<num; i++) {
            if(person[i].live) {
                x=QInputDialog::getInt(point,"Exile your foe."+QString::number(i+1),"Vote against.",1,1,16,1);
                while(person[x-1].vote_right==false&&x!=0) {
                    QMessageBox::critical(point,"Exile your foe. NO."+QString::number(i+1),"You can't vote against this player.");
                    x=QInputDialog::getInt(point,"Exile your foe. NO."+QString::number(i+1),"Vote against.",1,1,16,1);
                }
                if(x==0) {
                    QMessageBox::information(point,"Exile your foe. NO."+QString::number(i+1),"You have abstained in the vote.");
                } else {
                    QMessageBox::information(point,"Exile your foe. NO."+QString::number(i+1),"You have voted against NO."+QString::number(x));
                    person[x-1].k1+=person[i].tic;
                }
            } else QMessageBox::critical(point,"Exile your foe. NO."+QString::number(i+1),"You have been exiled and you can't vote.");
        }
        for(int i=0; i<num; i++) {
            person[i].vote_right=true;
            W[i]=person[i];
        }
        for(int i=0;i<num-1;i++)
            for(int j=0;j<num-1-i;j++)
                if(W[j].k1<W[j+1].k1){
                    int temp=W[j].k1;
                    W[j].k1=W[j+1].k1;
                    W[j+1].k1=temp;
                }
    }
    int m=0;
    for(m=0;m<num;m++){
        if(W[0].k1==person[m].k1){
            person[m].live=false;
            break;//
        }
    }
    for(int p=0;p<4;p++){
        for(int q=0;q<4;q++){
            if(p*4+q==m){
                if(person[m].card=="RED")
                    chart[p][q]=-1;
                if(person[m].card=="BLACK")
                    chart[p][q]=-2;
            }
        }
    }
    QMessageBox::information(point,"Exile your foe.","NO."+QString::number(m+1)+" is exiled and the identity is "+person[m].card+".");
    t--;
    if(!isvictory(num))
        if(person[m].lord){
            QMessageBox::information(point,"LORD ELECTION","Vote for a new lord.");
            v2(point,num,chart);
        }
}
void Player::v2(QWidget *point,int num,int chart[4][4])
{
    QString c;
    for(int i=0; i<num; i++)
        person[i].k2=0;
    int x;
    for(int i=0; i<num; i++) {
        if(person[i].live) person[i].vote_right=true;
        else person[i].vote_right=false;
    }
    for(int i=0; i<num; i++) {
        if(person[i].live) {
            x=QInputDialog::getInt(point,"LORD ELECTION"+QString::number(i+1),"Vote for the lord.",1,1,20,1);
            while(person[x-1].live==false&&x!=0) {
                QMessageBox::critical(point,"LORD ELECTION"+QString::number(i+1),"You must vote for whom still exists.");
                x=QInputDialog::getInt(point,"LORD ELECTION"+QString::number(i+1),"Vote for the lord.",1,1,20,1);
            }
            if(x==0)
                QMessageBox::information(point,"LORD ELECTION"+QString::number(i+1),"You have abstained in the vote.");
            else {
                QMessageBox::information(point,"LORD ELECTION"+QString::number(i+1),"You have voted for NO."+QString::number(x));
                person[x-1].k2++;
            }
        } else QMessageBox::critical(point,"LORD ELECTION"+QString::number(i+1),"You have been exiled and you can't vote.");
    }
    for(int i=0; i<=num; i++) {
        W[i]=person[i];
    }
    for(int i=0;i<num-1;i++)
        for(int j=0;j<num-1-i;j++)
            if(W[j].k2<W[j+1].k2){
                int temp=W[j].k2;
                W[j].k2=W[j+1].k2;
                W[j+1].k2=temp;
            }
    while(W[0].k2==W[1].k2) {
        for(int i=0; i<num; i++) {
            if(W[0].k2!=person[i].k2)
                person[i].vote_right=false;
            if(person[i].k2==W[1].k2) {
                c=c+QString::number(i+1)+" ";
            }
        }
        QMessageBox::information(point,"LORD ELECTION",c+"are now in stalement. Now a new round of vote is to commence.");
        for(int i=0; i<num; i++) {
            if(person[i].live) {
                x=QInputDialog::getInt(point,"LORD ELECTION"+QString::number(i+1),"Vote for the lord.",1,1,16,1);
                while(person[x-1].vote_right==false&&x!=0) {
                    QMessageBox::critical(point,"LORD ELECTION"+QString::number(i+1),"You can't vote for this player.");
                    x=QInputDialog::getInt(point,"LORD ELECTION"+QString::number(i+1),"Vote for the lord.",1,1,16,1);
                }
                if(x==0) {
                    QMessageBox::information(point,"LORD ELECTION"+QString::number(i+1),"You have abstained in the vote.");
                } else {
                    QMessageBox::information(point,"LORD ELECTION"+QString::number(i+1),"You have voted for NO."+QString::number(x)+".");
                    person[x-1].k2++;
                }
            } else QMessageBox::critical(point,"LORD ELECTION"+QString::number(i+1),"You have been exiled and you can't vote.");
        }
        for(int i=0; i<num; i++) {
            person[i].vote_right=true;
            W[i]=person[i];
        }
        for(int i=0;i<num-1;i++)
            for(int j=0;j<num-1-i;j++)
                if(W[j].k2<W[j+1].k2){
                    int temp=W[j].k2;
                    W[j].k2=W[j+1].k2;
                    W[j+1].k2=temp;
                }

    }
    int m=0;
    for(m=0;m<num;m++)
        if(W[0].k2==person[m].k2){
            person[m].lord=true;
            for(int p=0;p<4;p++){
                for(int q=0;q<4;q++){
                    if(p*4+q==m){
                        chart[p][q]=2;
                    }
                }
            }
            break;
        }
    QMessageBox::information(point,"LORD ELECTION","NO."+QString::number(m+1)+" is elected as lord.");
}


void Player::night(QWidget *point,int num,int t)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int r=qrand()%2;
    if(r)
        QMessageBox::information(point,"NIGHT","It's red night.");
    else
        QMessageBox::information(point,"NIGHT","It's black night.");
    QMessageBox::question(point,"Do you want to open your eyes?","Decide whether you want to open your eyes.");
    int R=0, B=0;
    for(int i=0;i<num;i++){
        if(person[i].live){
            int x=QInputDialog::getInt(point,"Do you want to open your eyes?","0 for close and 1 for open",0,0,1,1);
            if(x==0){
                QMessageBox::information(point,"NO."+QString::number(i+1),"Your eyes are closed.");
            }
            if(x==1){
                QMessageBox::information(point,"NO."+QString::number(i+1),"Your eyes are open.");
                if(person[i].card=="RED")
                    R++;
                if(person[i].card=="BLACK")
                    B++;
            }
        }
        else{
            QMessageBox::critical(point,"NO."+QString::number(i+1),"You are exiled.");
        }
    }
    int i;
    for(i=0;i<num;i++)
        if(person[i].lord)
            break;
    if((r&&R%2==0&&R!=0)||(!r&&B%2==0&&B!=0)){
        QMessageBox::information(point,"Red and Black Judges","The vote of the lord is 1");
        person[i].tic=1;
    }
    else if(t%2==1){
        QMessageBox::information(point,"Red and Black Judges","The vote of the lord is 0.5");
        person[i].tic=0.5;
    }
    else if(t%2==0){
        QMessageBox::information(point,"Red and Black Judges","The vote of the lord is 1.5");
        person[i].tic=1.5;
    }
}
