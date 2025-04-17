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

