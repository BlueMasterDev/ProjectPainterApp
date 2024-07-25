#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsview.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>
#include "graphics_save_load.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Pen Properties
    void onColorButtonClicked();
    void on_penWidthSpinBox_valueChanged(int arg1);
    void on_penWidthSpinBox_textChanged(const QString &arg1);
    void on_colorButton_1_clicked();
    void on_colorButton_2_clicked();
    void on_colorButton_3_clicked();
    void on_colorButton_4_clicked();
    void on_colorButton_5_clicked();
    void on_colorButton_6_clicked();
    void on_colorButton_7_clicked();
    void on_penStyleComboBox_currentIndexChanged(int index);

    void on_actionQuit_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionAdd_image_triggered();
    void on_actionAbout_this_app_triggered();
    void on_actionUndo_triggered();
    // void on_actionRedo_triggered();
    // void onColorButton_2Clicked();

private:
    Ui::MainWindow *ui;
    CustomGraphicsView *customView;
    QGraphicsScene *scene;
    QColor selectedColor;
    Graphics_Save_Load *graphics_Save_Load;
    CustomGraphicsView *customView ;

};

#endif // MAINWINDOW_H
