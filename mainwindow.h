#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <pi2c.h>
#include <QThread>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_117_clicked();

    void on_pushButton_115_clicked();

    void on_pushButton_116_clicked();

    void on_pushButton_128_clicked();

    void on_pushButton_125_clicked();

    void on_pushButton_123_clicked();

    void on_pushButton_138_clicked();

    void on_pushButton_140_clicked();

    void on_pushButton_134_clicked();

    void on_pushButton_141_clicked();

    void on_pushButton_118_clicked();

    void on_pushButton_136_clicked();

    void on_toolButton_7_clicked();

    void processing();

    void write_motor(QString);

    int read_motor();

    void write_heater(QString);

    int read_heater();
    void changepage();
    int read_sensor();

    void on_toolButton_9_clicked();

    void on_toolButton_11_clicked();

    void on_toolButton_10_clicked();
    void update();
    void timer1update();
    void timer2update();

    void on_toolButton_12_clicked();

    void on_toolButton_13_clicked();

    void on_toolButton_14_clicked();

    void on_toolButton_15_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_16_clicked();

    void on_toolButton_17_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer1, *timer2;
};

#endif // MAINWINDOW_H
