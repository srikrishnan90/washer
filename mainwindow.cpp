#include "mainwindow.h"
#include "ui_mainwindow.h"

static int optn=0;
static int strip[12]={0,0,0,0,0,0,0,0,0,0,0,0};
static int wash_method=0;
static int wash_option=0;
static int wash_volume=0;
static int wash_times=0;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_toolButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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
    if(wash_method==0)
    {
        for(int i=0;i<wash_times+1;i++)
        {
            //send home command and wait for acknowledgement
            //current position = 0
            for(int j=0;j<12;j++)
            {
                if(strip[j]==1)
                {
                    //current position=current pos-j+1
                    //i2c send current position(total move position) with wash volume and cross wash and wait for acknowledgement
                }
            }
        }
        //send home command and wait for acknowledgement
    }
    else
    {
        //send home command and wait for acknowledgement
        //current position = 0
        for(int j=0;j<12;j++)
        {
            if(strip[j]==1)
            {
                //current position=current pos-j+1
                for(int i=0;i<wash_times+1;i++)
                {
                    if(i==0)
                    {
                        //i2c send move position and wait for acknowledgement
                    }
                    //i2c send wash volume and cross wash and wait for acknowledgement
                }

            }
        }
        //send home command and wait for acknowledgement
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
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
