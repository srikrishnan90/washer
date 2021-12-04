#include "mainwindow.h"
#include "ui_mainwindow.h"

static int optn=0;
static int strip[12]={0,0,0,0,0,0,0,0,0,0,0,0};
static int wash_method=0;
static int wash_option=0;
static int wash_volume=0;
static int wash_times=0;
static int current_pos=0;
static int previous_pos=0;
static int move_pos=0;
//static int done_stat=0;
static int stop_stat=0;
static int wplg_stat=0;
static int wsen_stat=0;
static int sen_war=0;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(update()));
    connect(timer1, SIGNAL(timeout()), this,SLOT(timer1update()));
    connect(timer2, SIGNAL(timeout()), this,SLOT(timer2update()));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->listWidget->setCurrentRow(0);
    ui->listWidget_2->setCurrentRow(1);
    ui->listWidget_3->setCurrentRow(6);
    ui->listWidget_4->setCurrentRow(4);

}

void MainWindow::on_toolButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_toolButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::changepage()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_toolButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->toolButton_9->setVisible(true);
    ui->toolButton_4->hide();
    QApplication::processEvents();
    //QTimer::singleShot(100, this, SLOT(processing()));
    for(int i=0;i<12;i++)
    {
        strip[i]=0;
    }

    if(ui->checkBox_112->isChecked())
        strip[0]=1;
    if(ui->checkBox_113->isChecked())
        strip[1]=1;
    if(ui->checkBox_114->isChecked())
        strip[2]=1;
    if(ui->checkBox_115->isChecked())
        strip[3]=1;
    if(ui->checkBox_116->isChecked())
        strip[4]=1;
    if(ui->checkBox_117->isChecked())
        strip[5]=1;
    if(ui->checkBox_118->isChecked())
        strip[6]=1;
    if(ui->checkBox_119->isChecked())
        strip[7]=1;
    if(ui->checkBox_120->isChecked())
        strip[8]=1;
    if(ui->checkBox_121->isChecked())
        strip[9]=1;
    if(ui->checkBox_122->isChecked())
        strip[10]=1;
    if(ui->checkBox_123->isChecked())
        strip[11]=1;

    wash_method=ui->listWidget->currentRow();
    wash_option=ui->listWidget_2->currentRow();
    wash_volume=ui->listWidget_3->currentRow();
    wash_times=ui->listWidget_4->currentRow();
    processing();

}

void MainWindow::processing()
{

    QString data, text;
    if(wash_method==0)
    {
        for(int i=0;i<wash_times+2;i++)//2 is for final aspiration cycle
        {
            if(stop_stat==1)
            {
                stop_stat=0;
                ui->stackedWidget->setCurrentIndex(0);
                break;
            }
            else
            {
                data="ini";
                ui->label_13->setText("Homing...");
                write_motor(data);
                current_pos=0;
                for(int j=0;j<12;j++)
                {
                    if(strip[j]==1)
                    {
                        if(stop_stat==1)
                        {
                            break;
                        }
                        else
                        {
                            previous_pos=current_pos;
                            current_pos=j+1;
                            move_pos=current_pos-previous_pos;
                            if(i==wash_times+1)
                            {
                                data="mof "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_method);
                                text="Final Aspiration of strip "+QString::number(j+1);
                            }
                            else
                            {
                                data="mov "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_method);
                                text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                            }
                            ui->label_13->setText(text);
                            write_motor(data);
                        }
                    }
                }
            }
        }
        data="ini";
        ui->label_13->setText("Homing...");
        write_motor(data);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        data="ini";
        ui->label_13->setText("Homing...");
        write_motor(data);
        current_pos=0;
        for(int j=0;j<12;j++)
        {
            if(stop_stat==1)
            {
                stop_stat=0;
                ui->stackedWidget->setCurrentIndex(0);
                break;
            }
            else
            {
                if(strip[j]==1)
                {
                    previous_pos=current_pos;
                    current_pos=j+1;
                    move_pos=current_pos-previous_pos;
                    for(int i=0;i<wash_times+2;i++)
                    {
                        if(stop_stat==1)
                        {
                            break;
                        }
                        else
                        {
                            if(i==0)
                            {
                                data="mov "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_method);
                                text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                            }
                            else
                            {
                                if(i==wash_times+1)
                                {
                                    data="mof 0 "+QString::number(wash_volume)+" "+QString::number(wash_method);
                                    text="Final Aspiration of strip  "+QString::number(j+1);
                                }
                                else
                                {
                                    data="mov 0 "+QString::number(wash_volume)+" "+QString::number(wash_method);
                                    text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                                }
                            }
                            ui->label_13->setText(text);
                            write_motor(data);
                        }
                    }
                }
            }
        }
        data="ini";
        ui->label_13->setText("Homing...");
        write_motor(data);
        ui->stackedWidget->setCurrentIndex(0);
    }
    ui->toolButton_4->setVisible(true);
}


void MainWindow::write_motor(QString val)
{
    QMessageBox msgBox;
    //if(!(strncmp(val,"ini",3)==0 || strncmp(val,"buz",3)==0 || strncmp(val,"stp",3)==0 ||strncmp(val,"shk",3)==0)) //if(val!="ini")
    if(!(val.left(3)=="ini"||val.left(3)=="buz"||val.left(3)=="stp"||val.left(3)=="shk"))
    {
        while(true)
        {
            QApplication::processEvents();
            QThread::msleep(100);
            read_sensor();
            if(wplg_stat==1 || wsen_stat==1)
            {
                msgBox.setWindowTitle("Warning...");
                msgBox.setText("check sensor status and click Yes to Resume and No to Stop");
                msgBox.setStandardButtons(msgBox.Yes);
                msgBox.addButton(msgBox.No);
                msgBox.setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:200px; height:50px; font-size: 18px; }");
                if(msgBox.exec() == msgBox.Yes)
                {
                    sen_war=1;
                }
                else
                {
                    stop_stat=1;
                    break;
                }

            }
            else if(sen_war==1)
            {
                sen_war=0;
                break;
            }
            if(stop_stat==1)
            {
                break;
            }
        }
    }
    if(stop_stat==0)
    {
        Pi2c arduino(7);
        QString data=val;
        char* ch;
        QByteArray ba=data.toLatin1();
        ch=ba.data();
        QThread::msleep(100);
        arduino.i2cWrite(ch,30);
        QThread::msleep(100);
        while(true)
        {
            QApplication::processEvents();
            QThread::msleep(500);
            if(!read_motor())
                break;
            else if(stop_stat==1)
            {
                break;
            }
        }
    }
}



int MainWindow::read_motor()
{
    Pi2c arduino(7);
    char receive[30];
    QThread::msleep(100);
    arduino.i2cRead(receive,30);
    QThread::msleep(100);
    if(strncmp(receive,"done",4)==0)
        return 1;
    else
        return 0;
}

void MainWindow::write_heater(QString val)
{
    Pi2c arduino(8);
    QString data=val;
    char* ch;
    QByteArray ba=data.toLatin1();
    ch=ba.data();
    QThread::msleep(100);
    arduino.i2cWrite(ch,30);
    QThread::msleep(100);
}

int MainWindow::read_heater()
{
    Pi2c arduino(8);
    char receive[30];
    QThread::msleep(100);
    arduino.i2cRead(receive,30);
    QThread::msleep(100);
    QString str=receive;
    //Print out what the Arduino is sending...
    //qDebug() << "Arduino Says: " << str.mid(0,2);
    ui->label_17->setText(str.mid(0,4));


}

int MainWindow::read_sensor()
{
    Pi2c arduino(8);
    char receive[30];
    QThread::msleep(100);
    arduino.i2cRead(receive,30);
    QThread::msleep(100);
    QString str=receive;
    //wplg_stat=str.mid(5,6).toInt();
    //wsen_stat=str.mid(7,8).toInt();
    wplg_stat=1;
    wsen_stat=1;

}

void MainWindow::on_toolButton_2_clicked()
{
    ui->listWidget_5->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(4);
    ui->toolButton_10->hide();
}

void MainWindow::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->toolButton_14->hide();
    ui->toolButton_15->hide();
}

void MainWindow::on_pushButton_clicked()
{
    optn=1;
    ui->lineEdit_4->clear();
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_2_clicked()
{
    optn=2;
    ui->lineEdit_4->clear();
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    optn=3;
    ui->lineEdit_4->clear();
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}


void MainWindow::on_pushButton_117_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_117->text());
}

void MainWindow::on_pushButton_115_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_115->text());
}

void MainWindow::on_pushButton_116_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_116->text());
}

void MainWindow::on_pushButton_128_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_128->text());
}

void MainWindow::on_pushButton_125_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_125->text());
}

void MainWindow::on_pushButton_123_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_123->text());
}

void MainWindow::on_pushButton_138_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_138->text());
}

void MainWindow::on_pushButton_140_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_140->text());
}

void MainWindow::on_pushButton_134_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_134->text());
}

void MainWindow::on_pushButton_141_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_141->text());
}

void MainWindow::on_pushButton_118_clicked()
{
    ui->lineEdit_4->backspace();
}

void MainWindow::on_pushButton_136_clicked()
{
    if(optn==1)
    {
        ui->lineEdit_2->setText(ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(5);
    }
    else if(optn==2)
    {
        ui->lineEdit_3->setText(ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(5);
    }
    else if(optn==3)
    {
        ui->lineEdit->setText(ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(4);
    }
}

void MainWindow::on_toolButton_7_clicked()
{
    ui->checkBox_112->setChecked(true);
    ui->checkBox_113->setChecked(true);
    ui->checkBox_114->setChecked(true);
    ui->checkBox_115->setChecked(true);
    ui->checkBox_116->setChecked(true);
    ui->checkBox_117->setChecked(true);
    ui->checkBox_118->setChecked(true);
    ui->checkBox_119->setChecked(true);
    ui->checkBox_120->setChecked(true);
    ui->checkBox_121->setChecked(true);
    ui->checkBox_122->setChecked(true);
    ui->checkBox_123->setChecked(true);
}

void MainWindow::on_toolButton_9_clicked()
{
    stop_stat=1;
    ui->toolButton_9->hide();
    ui->toolButton_4->setVisible(true);
}

void MainWindow::on_toolButton_11_clicked()
{
    int speed=ui->listWidget_5->currentRow()+1;
    int dur=ui->lineEdit->text().toInt();
    QString data="shk "+QString::number(speed)+" "+QString::number(dur);
    write_motor(data);
    timer->start(1000);
    ui->toolButton_11->hide();
    ui->toolButton_10->setVisible(true);


}

void MainWindow::on_toolButton_10_clicked()
{
    write_motor("ini");
    ui->lineEdit->clear();
    timer->stop();
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton_10->setVisible(false);
    ui->toolButton_11->setVisible(true);
}

void MainWindow::update()
{
    int num=ui->lineEdit->text().toInt();
    num=num-1;
    ui->lineEdit->setText(QString::number(num));
    ui->toolButton_10->setVisible(true);
    if(num<=0)
    {
        ui->lineEdit->clear();
        timer->stop();
        ui->stackedWidget->setCurrentIndex(0);
        ui->toolButton_11->setVisible(true);
    }
}

void MainWindow::on_toolButton_12_clicked()
{
    timer1->start(1000);
    ui->toolButton_12->hide();
    ui->toolButton_14->setVisible(true);
}

void MainWindow::on_toolButton_13_clicked()
{
    timer2->start(1000);
    ui->toolButton_13->hide();
    ui->toolButton_15->setVisible(true);
}

void MainWindow::timer1update()
{
    int num=ui->lineEdit_2->text().toInt();
    num=num-1;
    ui->lineEdit_2->setText(QString::number(num));
    ui->toolButton_14->setVisible(true);
    if(num<=0)
    {
        ui->lineEdit_2->clear();
        timer1->stop();
        write_heater("buz 2");
        ui->stackedWidget->setCurrentIndex(0);
        ui->toolButton_12->setVisible(true);
        ui->toolButton_14->hide();
    }
}

void MainWindow::timer2update()
{
    int num=ui->lineEdit_3->text().toInt();
    num=num-1;
    ui->lineEdit_3->setText(QString::number(num));
    ui->toolButton_15->setVisible(true);
    if(num<=0)
    {
        ui->lineEdit_3->clear();
        timer2->stop();
        write_heater("buz 2");
        ui->stackedWidget->setCurrentIndex(0);
        ui->toolButton_13->setVisible(true);
        ui->toolButton_15->hide();
    }
}

void MainWindow::on_toolButton_14_clicked()
{
    ui->lineEdit_2->clear();
    timer1->stop();
    ui->toolButton_12->setVisible(true);
    ui->toolButton_14->hide();
}

void MainWindow::on_toolButton_15_clicked()
{
    ui->lineEdit_3->clear();
    timer2->stop();
    ui->toolButton_13->setVisible(true);
    ui->toolButton_15->hide();
}
