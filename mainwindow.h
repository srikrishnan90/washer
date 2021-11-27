#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
