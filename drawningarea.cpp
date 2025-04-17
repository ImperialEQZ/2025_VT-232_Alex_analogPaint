#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrinter>
#include <QtPrinterDialog>
#endif
#endif
#include "DrawningArea.h"

DrawningArea::DrawningArea(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    selectedPenWidth = 1;
    selectedPPenColor = Qt::blue
}

bool DrawningArea::openImage(const QString &fileName) {
    QImage loadedImg;
    if(!loadedImg.load(fileName)) {
        return false;
    }
    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImg, newSize);
    image = loadedImg;
    modified = false;
    update();
    return true;
}

bool DrawningArea::saveImage(const QString &fileName, const char *formatFile) {
    QImage visImg = image;
    resize(&visImg, size());
    if(visImg.save(fileName, formatFile)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void DrawningArea::setPenColor(const QColor &newColor) {
    selectedPenColor = newColor;
}

void DrawningArea::setPenWidth(int newWidth) {
    selectedPenWidth = newWidth;
}

void DrawningArea::clearImage() {
    image.fill(qRgb(255,255,255));
    modified = true;
    update();
}

void DrawningArea::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        drawning = true;
    }
}

void DrawningArea::mouseMoveEvent(QMouseEvent *event) {
    if((event->button() & Qt::LeftButton) && drawning) {
        drawTo(event->pos());
    }
}

void DrawningArea::mouseReleaseEvent(QMouseEvent *event) {
    if((event->button() == Qt::LeftButton) && drawning) {
        drawTo(event->pos());
        drawning = false;
    }
}



