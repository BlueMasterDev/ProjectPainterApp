/**
 * @file mainwindow.cpp
 * @brief Fichier pour la classe MainWindow
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QPen>
#include <QIcon>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>


/**
 * @brief Constructeur de base de MainWindow
 * @param parent : widget parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , actionHandler(new ActionHandler(this))
    , selectedColor(Qt::black)
    // , selectedColor_2(Qt::yellow)
{
    ui->setupUi(this);

    customView = new CustomGraphicsView(selectedColor,ui->penWidthSpinBox->value(), ui->penStyleComboBox->currentIndex(), this);

    // création de la scene et définition de sa taille à partir d'un rectangle
    scene = new QGraphicsScene(this);
    const int sceneMaxSize = 1000;
    scene->setSceneRect(0, 0, sceneMaxSize, sceneMaxSize);

    // ajout de la scene à la graphicsview et centrage par défaut sur le centre de la scene
    customView->setScene(scene);
    customView->centerOn(QPointF(sceneMaxSize/2, sceneMaxSize/2));

    ui->mainLayout->replaceWidget(ui->graphicsView, customView);
    delete ui->graphicsView;
    ui->graphicsView = nullptr;

    graphics_Save_Load = new Graphics_Save_Load(customView);

    connect(ui->penColorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);


    //les actions et les icônes
    setupActions();

    //maj curseur lié aux actions
    connect(actionHandler, &ActionHandler::cursorChanged, this, &MainWindow::updateCursor);


    // connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::onColorButton_2Clicked);

}

/**
 * @brief Destructeur de base de MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete graphics_Save_Load;
}

// -----------------------------------------------------------------------------------------------------------------
// Pen Properties

/**
 * @brief Action qui se déclenche lorsque l'on clique sur la zone de couleur du crayon, permet à l'utilisateur de choisir une couleur.
 */
void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(selectedColor, this, "Choose Color");

    if (color.isValid()) {
        selectedColor = color;
        ui->penColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
        customView->setPenColor(color);
    }
}

/**
 * @brief Action qui se déclenche lorsque l'on incrémente ou décrémente le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_valueChanged(int arg1)
{
    customView->setPenWidth(arg1);
}

/**
 * @brief Action qui se déclenche lorsque l'on change numériquement au clavier le champs contenant la largeur du crayon.
 */
void MainWindow::on_penWidthSpinBox_textChanged(const QString &arg1)
{
    customView->setPenWidth(arg1.toInt());
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la première couleur par défaut (violet)
 */
void MainWindow::on_colorButton_1_clicked()
{
    customView->setPenColor(QColor(85, 0, 127));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(85).arg(0).arg(127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la deuxième couleur par défaut (violet-bleu)
 */
void MainWindow::on_colorButton_2_clicked()
{
    customView->setPenColor(QColor(50, 14, 127));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(50).arg(14).arg(127));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la troisuème couleur par défaut (bleu)
 */
void MainWindow::on_colorButton_3_clicked()
{
    customView->setPenColor(QColor(0, 0, 255));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(0).arg(0).arg(255));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la quatrième couleur par défaut (vert)
 */
void MainWindow::on_colorButton_4_clicked()
{
    customView->setPenColor(QColor(0, 255, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(0).arg(255).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la cinquième couleur par défaut (jaune)
 */
void MainWindow::on_colorButton_5_clicked()
{
    customView->setPenColor(QColor(255, 255, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(255).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la sixième couleur par défaut (orange)
 */
void MainWindow::on_colorButton_6_clicked()
{
    customView->setPenColor(QColor(255, 85, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(85).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on clique sur la septième couleur par défaut (rouge)
 */
void MainWindow::on_colorButton_7_clicked()
{
    customView->setPenColor(QColor(255, 0, 0));
    ui->penColorButton->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(255).arg(0).arg(0));
}

/**
 * @brief Action qui se déclenche lorque l'on change la combo box contenant le style du crayon [Solid, Dashed, Dotted, Dot Dashed]
 */
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
