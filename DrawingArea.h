#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class PaintArea : public QWidget {
    Q_OBJECT
private:
    void drawTo(const QPoint &endPoint);
    void resizeImage(QImage *image, QSize &newSize);
    bool modified;
    bool area;
    QColor OenColor;
    QImage image;
    QPoint endPoint;
public:
    PaintArea(QWidget *ancestor = 0);
    bool openImage(const QString &fileName);
    bool saveFile(const QString &fileName, const char &fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    bool isModified() const {
        return modified;
    }
    int penWidth() {
        return selectedPenWidth;
    }
    QColor penColor() {
        return selectedPenColor;
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};



#endif // DRAWINGAREA_H
