#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QPen>
#include <QIcon>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , actionHandler(new ActionHandler(this))
    , selectedColor(Qt::black)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(selectedColor,ui->penWidthSpinBox->value(), ui->penStyleComboBox->currentIndex(), this);
    scene = new QGraphicsScene(this);

    customView->setScene(scene);

    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = nullptr;

    graphics_Save_Load = new Graphics_Save_Load(customView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);


    //les actions et les icônes
    setupActions();

    //maj curseur lié aux actions
    connect(actionHandler, &ActionHandler::cursorChanged, this, &MainWindow::updateCursor);

    // Initialisation de la ListWidget avec tous les items
    setListWidgetItems();
    customView->setAcceptDrops(true);
    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphics_Save_Load;
}

void MainWindow::setListWidgetItems()
{
    listWidget = ui->listWidgetShapeItems;

    // Mise en place des icônes pour les items
    QPixmap pixLearn(":/images/images/quick.png");
    QPixmap pixEllipse(":/images/images/circle.png");
    QPixmap pixRect(":/images/images/rectangle.png");
    QPixmap pixStar(":/images/images/star.png");

    // Création des items pour la listwidget
    QListWidgetItem *itemLearn = new QListWidgetItem;
    QListWidgetItem *itemEllipse = new QListWidgetItem;
    QListWidgetItem *itemRect = new QListWidgetItem;
    QListWidgetItem *itemStar = new QListWidgetItem;

    // Application des icônes pour tous les items
    itemLearn->setIcon(pixLearn);
    itemEllipse->setIcon(pixEllipse);
    itemRect->setIcon(pixRect);
    itemStar->setIcon(pixStar);

    // Application du texte pour tous les items
    itemLearn->setText("Learn");
    itemEllipse->setText("Ellipse");
    itemRect->setText("Rectangle");
    itemStar->setText("Star");

    // Ajout de tous les items dans la listwidget
    listWidget->addItem(itemLearn);
    listWidget->addItem(itemEllipse);
    listWidget->addItem(itemRect);
    listWidget->addItem(itemStar);

    // Activation du drag and drop
    listWidget->setDragEnabled(true);
}

// -----------------------------------------------------------------------------------------------------------------
// Pen Properties

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setPenColor(color);
    }
}


void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    customView->setPenWidth(arg1);
}

void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    customView->setPenWidth(arg1.toInt());
}

void MainWindow::on_colorButton_1_clicked()
{
    customView->setPenColor(QColor(85, 0, 127));
}

void MainWindow::on_colorButton_2_clicked()
{
    customView->setPenColor(QColor(50, 14, 127));
}

void MainWindow::on_colorButton_3_clicked()
{
    customView->setPenColor(QColor(0, 0, 255));
}

void MainWindow::on_colorButton_4_clicked()
{
    customView->setPenColor(QColor(0, 255, 0));
}

void MainWindow::on_colorButton_5_clicked()
{
    customView->setPenColor(QColor(255, 255, 0));
}

void MainWindow::on_colorButton_6_clicked()
{
    customView->setPenColor(QColor(255, 85, 0));
}

void MainWindow::on_colorButton_7_clicked()
{
    customView->setPenColor(QColor(255, 0, 0));
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(int index)
{
    customView->setPenStyle(index);
}

// -----------------------------------------------------------------------------------------------------------------
// File Properties - About

void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "NomImage", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->saveScene(filePath);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->loadScene(filePath);
    }
}

void MainWindow::on_actionAdd_image_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Add File", "", "Images (*.png *.jpg)");
    if (!filePath.isEmpty()) {
        graphics_Save_Load->addImage(filePath);
    }
}

void MainWindow::on_actionAbout_this_app_triggered()
{
    QMessageBox::about(this, "Message", "Membre du projet : \n\nMUKHTAR Masooma\nRENOU Noemie\nKITIHOUN Bryan\nJIN Laurent");
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

// -----------------------------------------------------------------------------------------------------------------

void MainWindow::setupActions() {
    // Liste des actions
    QList<QAction*> actions = { ui->actionEraser, ui->actionCursor, ui->actionPen, ui->actionEllipse, ui->actionStar, ui->actionRectangle };
    actionHandler->configureActions(actions);
}

void MainWindow::onActionTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        // Met à jour l'icône et le curseur dans ActionHandler
        actionHandler->onActionTriggered();
    }
}

void MainWindow::updateCursor(const QCursor& cursor) {
    // Mettre à jour le curseur de la vue graphique
    customView->setCursor(cursor);
}

// -----------------------------------------------------------------------
// void MainWindow::onColorButton_2Clicked()
// {
//     QColor color = QColorDialog::getColor(selectedColor_2, this, "Choose Color");

