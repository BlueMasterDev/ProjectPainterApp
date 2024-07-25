#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QMouseEvent>
#include <QPen>
#include <QMessageBox>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), drawing(false), penColor(Qt::black), penWidth(5)
{
}

void CustomGraphicsView::setPenColor(const QColor &color)
{
    penColor = color;
}

void CustomGraphicsView::setPenWidth(int width)
{
    penWidth = width;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = mapToScene(event->pos());
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPointF currentPoint = mapToScene(event->pos());
        QPen pen(penColor, penWidth);
        scene()->addLine(lastPoint.x(), lastPoint.y(), currentPoint.x(), currentPoint.y(), pen);
        lastPoint = currentPoint;
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , selectedColor(Qt::yellow)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    auto *customView = new CustomGraphicsView(this);
    customView->setScene(scene);
    ui->horizontalLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = customView;

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->pushButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
    }
}

// void MainWindow::onColorButton_2Clicked()
// {
//     QColor color = QColorDialog::getColor(selectedColor_2, this, "Choose Color");

//     if (color.isValid()) {
//         selectedColor_2 = color;
//         ui->toolButton_2->setStyleSheet(QString("background-color: %1").arg(color.name()));
//         dynamic_cast<CustomGraphicsView*>(ui->graphicsView)->setPenColor(color);
//     }
// }


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Message", "Test");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
