#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>

class DrawingArea : public QWidget
{
    Q_OBJECT

public:
    DrawingArea(QWidget *parent = nullptr);//создание виджета с холстом для рисования
    //Обработка различных событий в этом виджете
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    //произошли ли изменения?
    bool isModified() const {
        return modified;
    }
    //возврат цвета
    QColor penColor() const {
        return myPenColor;
    }
    //возврат ширины
    int penWidth() const {
        return myPenWidth;
    }

public slots:
    //очистить содержимое
    void clearImage();
    //вывести содержимое
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified = false;
    bool area = false;//Рисует ли пользователь на поверхности или нет
    QColor myPenColor = Qt::green;//цвет пера
    int myPenWidth = 1;//Начальная толщина пера
    QImage image;//картина, которую пользователь нарисовал
    QPoint lastPoint;//последняя позиция(точка)нахождения мыши
};
#endif // DRAWINGAREA_H
