#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <pi2c.h>
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include <QMovie>
#include <QProcess>
#include <QFile>

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
    void timerstart();

    void on_toolButton_12_clicked();

    void on_toolButton_13_clicked();

    void on_toolButton_14_clicked();

    void on_toolButton_15_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_16_clicked();

    void on_toolButton_17_clicked();

    void on_pushButton_5_clicked();

    void on_toolButton_18_clicked();

    void on_toolButton_25_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_94_clicked();

    void on_pushButton_50_clicked();

    void on_toolButton_26_clicked();

    void on_pushButton_139_clicked();

    void on_pushButton_72_clicked();

    void on_pushButton_110_clicked();

    void on_pushButton_101_clicked();

    void on_pushButton_105_clicked();

    void on_pushButton_57_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_85_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_62_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_56_clicked();

    void on_pushButton_75_clicked();

    void on_pushButton_73_clicked();

    void on_pushButton_71_clicked();

    void on_pushButton_76_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_77_clicked();

    void on_pushButton_78_clicked();

    void on_pushButton_80_clicked();

    void on_pushButton_79_clicked();

    void on_pushButton_84_clicked();

    void on_pushButton_82_clicked();

    void on_pushButton_83_clicked();

    void on_pushButton_81_clicked();

    void on_pushButton_87_clicked();

    void on_pushButton_86_clicked();

    void on_pushButton_95_clicked();

    void on_pushButton_89_clicked();

    void on_pushButton_90_clicked();

    void on_pushButton_88_clicked();

    void on_pushButton_96_clicked();

    void on_pushButton_93_clicked();

    void on_pushButton_91_clicked();

    void on_pushButton_92_clicked();

    void on_pushButton_97_clicked();

    void on_pushButton_107_clicked();

    void on_pushButton_104_clicked();

    void on_pushButton_99_clicked();

    void on_pushButton_106_clicked();

    void on_pushButton_108_clicked();

    void on_pushButton_102_clicked();

    void on_pushButton_103_clicked();

    void on_pushButton_98_clicked();

    void on_pushButton_113_clicked();

    void on_pushButton_111_clicked();

    void on_pushButton_109_clicked();

    void on_pushButton_114_clicked();

    void on_pushButton_74_clicked();

    void on_pushButton_112_clicked();

    void on_toolButton_19_clicked();

    void on_toolButton_20_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void save(int, QString);
    void init_load_set();

    void on_toolButton_21_clicked();

    void on_toolButton_22_clicked();

    void on_toolButton_24_clicked();

    void on_toolButton_23_clicked();

    void on_pushButton_6_clicked();

    void on_toolButton_27_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer1, *timer2, *temptimer;
};

#endif // MAINWINDOW_H
