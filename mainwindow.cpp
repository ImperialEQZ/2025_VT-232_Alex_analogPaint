#include "mainwindow.h"
//#include "./ui_mainwindow.h"
#include "DrawingArea.h"
#include <QtWidgets>


MainWindow::MainWindow()
{
    drawningArea = new PaintArea;
    setCentralWidget(drawningArea);
    createActions();
    createMenu();
    setWindowTitle(tr("Draw"));
    resize(600, 600);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(abilitySave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open() {
    if(abilitySave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
        if (!fileName.isEmpty()) {
            drawningArea->openImage(fileName);
        }
    }
}

void MainWindow::abilitySave() {
    QAction *act = qobject_cast<QAction *> (sender());
    QByte fileFormat = act->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor() {
    QColor newColor = QColorDialog::getColor(drawningArea->penColor());
    if(newColor.isValid()) {
        drawningArea->setPenColor(newColor);
    }
}

void MainWindow::penWidth() {
    bool flag;
    int newWidth = QInputDialog::getInt(this, tr("Draw"), tr("Выберите толщину пера:"),
                                        drawningArea->penWidth(), 1, 60, 1, &flag);
}

void MainWindow::about() {
    QMessageBox::about(this, tr("О приложении"), tr("Вышло прикольно"));
}

void MainWindow::createActions() {
    openActions = new QAction(tr("&Open"), this);
    openActions->setShortcut(QKeySequence::Open);
    connect(openActions, SIGNAL(triggered()), this, SLOT(open()));
    foreach (QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActions.append(action);
    }
    printActions = newQAction(tr("&Print..."), this);
    connect(printActions, SIGNAL(triggered()), drawningArea, SLOT(print()));
    exitActions = new QAction(tr("&Exit"), this);
    exitActions->setShortcuts(QKeySequence::Quit);
    connect(exitActions, SIGNAL(triggered()), this, SLOT(close()));

    penColorActions = new QAction(tr("&Pen Color..."), this);
    connect(penColorActions, SIGNAL(triggered()), drawningArea, SLOT(changePenColor()));

    penWidthActions = new QAction(tr("&Pen Width..."), this);
    connect(penWidthActions, SIGNAL(triggered()), drawningArea, SLOT(changePenWidth()));

    clearAreaActions = new QAction(tr("&Clear Screen..."), this);
    clearAreaActions->setShortcut(tr("Cntr+L"));
    connect(penColorActions, SIGNAL(triggered()), drawningArea, SLOT(clearImage()));

    aboutActions = new QAction(tr("&About..."), this);
    connect(aboutActions, SIGNAL(triggered()), SLOT(about()));
}

void MainWindow::createMenu(){
    saveAs = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsActions)
        saveAs->addAction(action);
    menuFile = new QMenu(tr("&File"), this);
    menuFile->addAction(open);
    menuFile->addAction(saveAs);
    menuFile->addAction(printActions);
    menuFile->addSeparator();
    menuFile->addAction(exitActions);

    menuOption = new QMenu(tr("&Options"), this);
    menuOption->addAction(penColorActions);
    menuOption->addAction(penWidthActions);

    menuHelp = new QMenu(tr("&Help"), this);
    menuHelp->addAction(aboutActions);

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuOption);
    menuBar()->addMenu(menuHelp);
}

