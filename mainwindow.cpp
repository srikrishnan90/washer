#include "mainwindow.h"
#include "ui_mainwindow.h"

static int optn=0;
static int strip[12]={0,0,0,0,0,0,0,0,0,0,0,0};
static int wash_method=0;
static int wash_option=0;
static int wash_volume=0;
static int wash_times=0;
static int soak_times=0;
static int pump_speed=0;
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
    setWindowFlags(Qt::FramelessWindowHint);

    timer = new QTimer(this);
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    temptimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(update()));
    connect(timer1, SIGNAL(timeout()), this,SLOT(timer1update()));
    connect(timer2, SIGNAL(timeout()), this,SLOT(timer2update()));
    connect(temptimer, SIGNAL(timeout()), this,SLOT(read_heater()));
    temptimer->start(1000);
    ui->stackedWidget->setCurrentIndex(0);
    init_load_set();
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
    ui->lineEdit_13->setText("0");

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
    ui->toolButton_17->hide();

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
    pump_speed=ui->lineEdit_10->text().toInt();
    soak_times=ui->lineEdit_13->text().toInt();

    processing();

}

void MainWindow::processing()
{
    write_heater("was");
    QString data, text;
    if(wash_method==0)
    {
        for(int i=0;i<wash_times+2;i++)//2 is for final aspiration cycle
        {
            if(stop_stat==1)
            {
                break;
            }
            else
            {
                data="ini";
                ui->label_13->setText("Homing...");
                write_motor(data);
                current_pos=0;
                if(i!=0)
                {
                    ui->label_13->setText("Soaking for "+QString::number(soak_times)+" sec.");
                    data="sok "+QString::number(soak_times);
                    write_motor(data);
                }
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
                                data="mof "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_option)+" "+QString::number(pump_speed);
                                text="Final Aspiration of strip "+QString::number(j+1);
                            }
                            else
                            {
                                data="mov "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_option)+" "+QString::number(pump_speed);
                                text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                            }
                            ui->label_13->setText(text);
                            //write_heater("ONN");
                            write_motor(data);
                            //write_heater("OFF");
                        }
                    }
                }
            }
        }
        if(stop_stat==1)
        {
            stop_stat=0;
            ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
            data="ini";
            ui->label_13->setText("Homing...");
            write_motor(data);
            ui->stackedWidget->setCurrentIndex(0);
        }
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
                                data="mov "+QString::number(move_pos)+" "+QString::number(wash_volume)+" "+QString::number(wash_option)+" "+QString::number(pump_speed);
                                text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                            }
                            else
                            {
                                ui->label_13->setText("Soaking for "+QString::number(soak_times)+" sec.");
                                data="sok "+QString::number(soak_times);
                                write_motor(data);
                                if(i==wash_times+1)
                                {
                                    data="mof 0 "+QString::number(wash_volume)+" "+QString::number(wash_option)+" "+QString::number(pump_speed);
                                    text="Final Aspiration of strip  "+QString::number(j+1);
                                }
                                else
                                {
                                    data="mov 0 "+QString::number(wash_volume)+" "+QString::number(wash_option)+" "+QString::number(pump_speed);
                                    text="Washing strip "+QString::number(j+1)+" of "+QString::number(i+1)+"/"+QString::number(wash_times+1)+" times";
                                }
                            }
                            ui->label_13->setText(text);
                            //write_heater("ONN");
                            write_motor(data);
                            //write_heater("OFF");
                        }
                    }
                }
            }
        }
        if(stop_stat==1)
        {
            stop_stat=0;
            ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
            data="ini";
            ui->label_13->setText("Homing...");
            write_motor(data);
            ui->stackedWidget->setCurrentIndex(0);
        }

    }
    write_heater("waf");
    ui->toolButton_4->setVisible(true);
    ui->toolButton_17->setVisible(true);
}


void MainWindow::write_motor(QString val)
{
    QMovie *movie = new QMovie("/home/pi/git/washer/loader.gif");
    ui->label_19->setMovie(movie);
    ui->label_19->setVisible(true);
    movie->start();
    qDebug()<<val;
    QMessageBox msgBox;
    //if(!(strncmp(val,"ini",3)==0 || strncmp(val,"buz",3)==0 || strncmp(val,"stp",3)==0 ||strncmp(val,"shk",3)==0)) //if(val!="ini")
    if(!(val.left(3)=="ini"||val.left(3)=="buz"||val.left(3)=="stp"||val.left(3)=="shk"))
    {
        while(true)
        {
            QApplication::processEvents();
            QThread::msleep(100);
            read_sensor();
            //qDebug()<<wplg_stat<<" "<<wsen_stat;
            if(wplg_stat==1 || wsen_stat==1)
            {
                write_heater("buz 2");
                msgBox.setWindowTitle("Warning...");
                if(wplg_stat==1)
                    msgBox.setText("Connect Waste Senor Plug Status and Click Yes to Resume. Click Cancel to Stop Washing.");
                if(wsen_stat==1)
                    msgBox.setText("Empty Waste Bottle and Click Yes to Resume. Click Cancel to Stop Washing.");
                msgBox.setStandardButtons(msgBox.Yes);
                msgBox.addButton(msgBox.Cancel);
                msgBox.setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:200px; height:50px; font-size: 18px; }");
                if(msgBox.exec() == msgBox.Yes)
                {
                    sen_war=1;
                }
                else
                {
                    qDebug()<<"in else";
                    stop_stat=1;
                    break;
                }

            }
            else if(sen_war==1)
            {
                sen_war=0;
                break;
            }
            else
            {
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
            QThread::msleep(100);
            if(read_motor())
            {
                break;
            }
            else if(stop_stat==1)
            {
                msgBox.setWindowTitle("Warning...");
                msgBox.setText("Are you sure to Stop Washing.");
                msgBox.setStandardButtons(msgBox.Yes);
                msgBox.addButton(msgBox.Cancel);
                msgBox.setStyleSheet("QLabel{min-width:500 px; font-size: 24px;} QPushButton{ width:200px; height:50px; font-size: 18px; }");
                if(msgBox.exec() == msgBox.Yes)
                {
                    stop_stat=1;
                    QString data="stp";
                    char* ch;
                    QByteArray ba=data.toLatin1();
                    ch=ba.data();
                    QThread::msleep(100);
                    arduino.i2cWrite(ch,30);
                    QThread::msleep(100);
                    qDebug()<<ch;
                    break;
                }
                else
                {
                    stop_stat=0;
                    ui->toolButton_9->setVisible(true);
                    ui->toolButton_4->hide();
                    ui->toolButton_17->hide();
                }
            }
        }
    }
    movie->stop();
    ui->label_19->hide();
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
    qDebug()<<val;
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
    wplg_stat=str.mid(6,1).toInt();
    wsen_stat=str.mid(9,1).toInt();
//       qDebug()<<"plug:"<<wplg_stat<<"sensor:"<<wsen_stat<<"str:"<<str;
//       for(int i=0;i<13;i++)
//       {
//           qDebug()<<str.mid(i,1);
//       }
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
    else if(optn==4)
    {
        ui->lineEdit_5->setText(ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(8);
    }
    else if(optn==5)
    {
        ui->lineEdit_7->setText(ui->lineEdit_4->text());
        save(0,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(9);
    }
    else if(optn==6)
    {
        ui->lineEdit_8->setText(ui->lineEdit_4->text());
        save(1,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(9);
    }
    else if(optn==7)
    {
        ui->lineEdit_10->setText(ui->lineEdit_4->text());
        save(2,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(9);
    }
    else if(optn==8)
    {
        ui->lineEdit_9->setText(ui->lineEdit_4->text());
        save(3,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(9);
    }

    else if(optn==9)
    {
        ui->lineEdit_12->setText(ui->lineEdit_4->text());
        save(4,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(10);
    }
    else if(optn==10)
    {
        ui->lineEdit_11->setText(ui->lineEdit_4->text());
        save(5,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(10);
    }
    else if(optn==11)
    {
        ui->lineEdit_13->setText(ui->lineEdit_4->text());
        //save(6,ui->lineEdit_4->text());
        ui->stackedWidget->setCurrentIndex(1);
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
    ui->toolButton_17->setVisible(true);

}

void MainWindow::on_toolButton_11_clicked()
{
    int speed=ui->listWidget_5->currentRow()+1;
    int dur=ui->lineEdit->text().toInt();
    QString data="shk "+QString::number(speed)+" "+QString::number(dur);
    ui->toolButton_11->hide();
    ui->toolButton_10->setVisible(true);
    QApplication::processEvents();
    //timer->start(1000);
    QTimer::singleShot(1000, this, SLOT(timerstart()));
    write_motor(data);
}

void MainWindow::timerstart()
{
    timer->start(1000);
}

void MainWindow::on_toolButton_10_clicked()
{
    ui->toolButton_10->setVisible(false);
    ui->toolButton_11->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
    QApplication::processEvents();
    write_motor("ini");
    ui->lineEdit->clear();
    timer->stop();

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

void MainWindow::on_toolButton_8_clicked()
{
    stop_stat=0;
    QString spd=ui->lineEdit_7->text();
    QString sec=ui->lineEdit_12->text();
    QString str="rns "+spd+" "+sec;
    write_motor(str);

}

void MainWindow::on_toolButton_16_clicked()
{
    stop_stat=0;
    QString spd=ui->lineEdit_10->text();
    QString sec=ui->lineEdit_11->text();
    QString str="prm "+spd+" "+sec;
    write_motor(str);
}

void MainWindow::on_toolButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_5_clicked()
{
    qApp->exit();
}

void MainWindow::on_toolButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->label_32->setVisible(true);
    qApp->processEvents();
    QStringList list2;
    QProcess process1;
    process1.start("sh",QStringList()<<"-c"<<"sudo iwlist wlan0 scan | grep ESSID");//scan list of wifi networks
    process1.waitForFinished();
    //ui->page_12->setVisible(true);
    ui->label_32->hide();
    QString data = process1.readAllStandardOutput();
    QString Error= process1.readAllStandardError();
    ui->comboBox->clear();
    list2 = (QStringList()<<"------Select-------");//append to dropdownlist
    ui->comboBox->addItems(list2);
    QStringList list = data.split("\n");//split data
    for(int i=0;i<list.count()-1;i++)
    {
        QStringList list1 = list.at(i).split("ESSID:");
        QString data1 = list1.at(1);
        list2 = (QStringList()<<data1);
        ui->comboBox->addItems(list2);//adding wifi names to dropdownlist
    }
    process1.start("sh",QStringList()<<"-c"<<"hostname -I");//scan list of wifi networks
    process1.waitForFinished();
    data = process1.readAllStandardOutput();
    ui->lineEdit_6->setText(data);

}

void MainWindow::on_toolButton_25_clicked()
{

    QFile file("/etc/wpa_supplicant/wpa_supplicant.conf");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<"ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev\n";
        stream<<"update_config=1\n";
        stream<<"country=IN\n";
        stream<<"\n";
        stream<<"network={\n";
        stream<<"\tssid=";
        stream<<ui->comboBox->currentText()+"\n";
        stream<<"\tpsk=\"";
        stream<<ui->lineEdit_5->text()+"\"\n";
        stream<<"\tkey_mgmt=WPA-PSK\n";
        stream<<"}";

        file.close();
        QProcess process2;
        process2.start("sh",QStringList()<<"-c"<<"sudo wpa_cli -i wlan0 reconfigure");
        process2.waitForFinished();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    optn=4;
    ui->lineEdit_4->clear();
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_94_clicked()
{
    on_pushButton_136_clicked();
}

void MainWindow::on_pushButton_50_clicked()
{
    on_pushButton_136_clicked();
}

void MainWindow::on_toolButton_26_clicked()
{
    QProcess process1;
    process1.start("sh",QStringList()<<"-c"<<"hostname -I");//scan list of wifi networks
    process1.waitForFinished();
    QString data = process1.readAllStandardOutput();
    ui->lineEdit_6->setText(data);
}

void MainWindow::on_pushButton_139_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_72_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);

}

void MainWindow::on_pushButton_110_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);

}

void MainWindow::on_pushButton_101_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}

void MainWindow::on_pushButton_105_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);

}

void MainWindow::on_pushButton_57_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_pushButton_61_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_9->text());
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_10->text());
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_36->text());
}

void MainWindow::on_pushButton_35_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_35->text());
}

void MainWindow::on_pushButton_40_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_40->text());
}

void MainWindow::on_pushButton_38_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_38->text());
}

void MainWindow::on_pushButton_39_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_39->text());
}

void MainWindow::on_pushButton_37_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_37->text());
}

void MainWindow::on_pushButton_43_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_43->text());
}

void MainWindow::on_pushButton_42_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_42->text());
}

void MainWindow::on_pushButton_85_clicked()
{
    ui->lineEdit_4->backspace();
}

void MainWindow::on_pushButton_41_clicked()
{
    ui->lineEdit_4->backspace();
}

void MainWindow::on_pushButton_51_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_51->text());
}

void MainWindow::on_pushButton_45_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_45->text());
}

void MainWindow::on_pushButton_46_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_46->text());
}

void MainWindow::on_pushButton_44_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_44->text());
}

void MainWindow::on_pushButton_52_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_52->text());
}

void MainWindow::on_pushButton_49_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_49->text());
}

void MainWindow::on_pushButton_47_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_47->text());
}

void MainWindow::on_pushButton_48_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_48->text());
}

void MainWindow::on_pushButton_53_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_53->text());
}

void MainWindow::on_pushButton_63_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_63->text());
}

void MainWindow::on_pushButton_60_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_60->text());
}

void MainWindow::on_pushButton_55_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_55->text());
}

void MainWindow::on_pushButton_62_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_62->text());
}

void MainWindow::on_pushButton_64_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_64->text());
}

void MainWindow::on_pushButton_58_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_58->text());
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_59->text());
}

void MainWindow::on_pushButton_54_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_54->text());
}

void MainWindow::on_pushButton_56_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_56->text());
}

void MainWindow::on_pushButton_75_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_75->text());
}

void MainWindow::on_pushButton_73_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_73->text());
}

void MainWindow::on_pushButton_71_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_71->text());
}

void MainWindow::on_pushButton_76_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_76->text());
}

void MainWindow::on_pushButton_100_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+"&");
}

void MainWindow::on_pushButton_77_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_77->text());
}

void MainWindow::on_pushButton_78_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_78->text());
}

void MainWindow::on_pushButton_80_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_80->text());
}

void MainWindow::on_pushButton_79_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_79->text());
}

void MainWindow::on_pushButton_84_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_84->text());
}

void MainWindow::on_pushButton_82_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_82->text());
}

void MainWindow::on_pushButton_83_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_83->text());
}

void MainWindow::on_pushButton_81_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_81->text());
}

void MainWindow::on_pushButton_87_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_87->text());
}

void MainWindow::on_pushButton_86_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_86->text());
}

void MainWindow::on_pushButton_95_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_95->text());
}

void MainWindow::on_pushButton_89_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_89->text());
}

void MainWindow::on_pushButton_90_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_90->text());
}

void MainWindow::on_pushButton_88_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_88->text());
}

void MainWindow::on_pushButton_96_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_96->text());
}

void MainWindow::on_pushButton_93_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_93->text());
}

void MainWindow::on_pushButton_91_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_91->text());
}

void MainWindow::on_pushButton_92_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_92->text());
}

void MainWindow::on_pushButton_97_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_97->text());
}

void MainWindow::on_pushButton_107_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_107->text());
}

void MainWindow::on_pushButton_104_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_104->text());
}

void MainWindow::on_pushButton_99_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_99->text());
}

void MainWindow::on_pushButton_106_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_106->text());
}

void MainWindow::on_pushButton_108_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_108->text());
}

void MainWindow::on_pushButton_102_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_102->text());
}

void MainWindow::on_pushButton_103_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_103->text());
}

void MainWindow::on_pushButton_98_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_98->text());
}

void MainWindow::on_pushButton_113_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_113->text());
}

void MainWindow::on_pushButton_111_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_111->text());
}

void MainWindow::on_pushButton_109_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_109->text());
}

void MainWindow::on_pushButton_114_clicked()
{
    ui->lineEdit_4->setText(ui->lineEdit_4->text()+ui->pushButton_114->text());
}

void MainWindow::on_pushButton_74_clicked()
{
    ui->lineEdit_4->setText(" ");
}

void MainWindow::on_pushButton_112_clicked()
{
    ui->lineEdit_4->setText(" ");

}

void MainWindow::on_toolButton_19_clicked()
{
    QString line;
    QString lines[6];
    int n=0;
    ui->stackedWidget->setCurrentIndex(9);
    QFile file("/home/pi/git/washer/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        QTextStream stream(&file);

        do {
            line = stream.readLine();
            lines[n]=line;
            n++;
        } while(!line.isNull());

        file.close();
        //qDebug() << "Reading finished";
    }
    ui->lineEdit_7->setText(lines[0]);
    ui->lineEdit_8->setText(lines[1]);
    ui->lineEdit_10->setText(lines[2]);
    ui->lineEdit_9->setText(lines[3]);
}

void MainWindow::on_toolButton_20_clicked()
{
    QString line;
    QString lines[6];
    int n=0;
    ui->stackedWidget->setCurrentIndex(10);
    QFile file("/home/pi/git/washer/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        QTextStream stream(&file);

        do {
            line = stream.readLine();
            lines[n]=line;
            n++;
        } while(!line.isNull());

        file.close();
        //qDebug() << "Reading finished";
    }
    ui->lineEdit_12->setText(lines[4]);
    ui->lineEdit_11->setText(lines[5]);

}

void MainWindow::on_pushButton_7_clicked()
{
    optn=5;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_7->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_8_clicked()
{
    optn=6;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_8->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_11_clicked()
{
    optn=7;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_10->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_12_clicked()
{
    optn=8;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_9->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_14_clicked()
{
    optn=9;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_12->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_13_clicked()
{
    optn=10;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_11->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::save(int num, QString val)
{
    QString line;
    QString lines[6];
    int n=0;
    ui->stackedWidget->setCurrentIndex(10);
    QFile file("/home/pi/git/washer/settings.txt");
    QTextStream stream(&file);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        do {
            line = stream.readLine();
            lines[n]=line;
            n++;
        } while(!line.isNull());
        file.close();
    }
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {

        for(int i=0;i<6;i++)
        {
            if(i==num)
                stream<<val+"\n";
            else {
                stream<<lines[i]+"\n";
            }
        }
        file.close();

    }
}

void MainWindow::init_load_set()
{
    QString line;
    QString lines[6];
    int n=0;
    QFile file("/home/pi/git/washer/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {

        QTextStream stream(&file);

        do {
            line = stream.readLine();
            lines[n]=line;
            n++;
        } while(!line.isNull());

        file.close();
        //qDebug() << "Reading finished";
    }
    ui->lineEdit_7->setText(lines[0]);
    ui->lineEdit_8->setText(lines[1]);
    ui->lineEdit_10->setText(lines[2]);
    ui->lineEdit_9->setText(lines[3]);
    ui->lineEdit_12->setText(lines[4]);
    ui->lineEdit_11->setText(lines[5]);
}

void MainWindow::on_toolButton_21_clicked()
{
    QString spd=ui->lineEdit_7->text();
    QString sec=ui->lineEdit_8->text();
    QString str="rns "+spd+" "+sec;
    write_motor(str);
}

void MainWindow::on_toolButton_22_clicked()
{
    QString spd=ui->lineEdit_10->text();
    QString sec=ui->lineEdit_9->text();
    QString str="prm "+spd+" "+sec;
    write_motor(str);
}

void MainWindow::on_toolButton_24_clicked()
{
    QString spd=ui->lineEdit_7->text();
    QString sec=ui->lineEdit_12->text();
    QString str="rns "+spd+" "+sec;
    write_motor(str);
}

void MainWindow::on_toolButton_23_clicked()
{
    QString spd=ui->lineEdit_10->text();
    QString sec=ui->lineEdit_11->text();
    QString str="prm "+spd+" "+sec;
    write_motor(str);
}

void MainWindow::on_pushButton_6_clicked()
{
    optn=11;
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setText(ui->lineEdit_13->text());
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_2->setCurrentIndex(2);
}
