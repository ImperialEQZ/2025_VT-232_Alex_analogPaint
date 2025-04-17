#include "mainwindow.h"
#include "DrawingArea.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), drawingArea(new DrawingArea(this))
{
    setCentralWidget(drawingArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Paint Analog"));
    resize(600, 600);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (abilitySave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::open()
{
    if (abilitySave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            drawingArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(drawingArea->penColor());
    if (newColor.isValid())
        drawingArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool flag;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        drawingArea->penWidth(),
                                        1, 50, 1, &flag);
    if (flag)
        drawingArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
                       tr(""));
}

void MainWindow::createActions()
{
    openActions = new QAction(tr("&Open..."), this);
    openActions->setShortcuts(QKeySequence::Open);
    connect(openActions, &QAction::triggered, this, &MainWindow::open);

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActions.append(action);
    }

    printActions = new QAction(tr("&Print..."), this);
    connect(printActions, &QAction::triggered, drawingArea, &DrawingArea::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    penColorActions = new QAction(tr("&Pen Color..."), this);
    connect(penColorActions, &QAction::triggered, this, &MainWindow::penColor);

    penWidthActions = new QAction(tr("Pen &Width..."), this);
    connect(penWidthActions, &QAction::triggered, this, &MainWindow::penWidth);

    clearAreaActions = new QAction(tr("&Clear Screen"), this);
    clearAreaActions->setShortcut(tr("Ctrl+L"));
    connect(clearAreaActions, &QAction::triggered,
            drawingArea, &DrawingArea::clearImage);

    aboutActions = new QAction(tr("&About"), this);
    connect(aboutActions, &QAction::triggered, this, &MainWindow::about);

}

void MainWindow::createMenus()
{
    saveAs = new QMenu(tr("&Save As"), this);
    for (QAction *action : qAsConst(saveAsActions))
        saveAs->addAction(action);

    menuFile = new QMenu(tr("&File"), this);
    menuFile->addAction(openActions);
    menuFile->addMenu(saveAs);
    menuFile->addAction(printActions);
    menuFile->addSeparator();
    menuFile->addAction(exitAct);

    menuOption = new QMenu(tr("&Options"), this);
    menuOption->addAction(penColorActions);
    menuOption->addAction(penWidthActions);
    menuOption->addSeparator();
    menuOption->addAction(clearAreaActions);

    menuHelp = new QMenu(tr("&Help"), this);
    menuHelp->addAction(aboutActions);

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuOption);
    menuBar()->addMenu(menuHelp);
}

bool MainWindow::abilitySave()
{
    if (drawingArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Paint Analog"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile("png");
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return drawingArea->saveImage(fileName, fileFormat.constData());
}

