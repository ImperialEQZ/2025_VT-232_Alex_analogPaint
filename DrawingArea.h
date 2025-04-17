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
    void resizeImage(QImage *image, QSize &newSize);//изменить размер содержимого
    bool modified;//Изменено ли состояние
    bool area;//Рисует ли пользователь на поверхности или нет
    QColor PenColor;//цвет пера
    QImage image;//картина, которую пользователь нарисовал
    QPoint endPoint;//последняя позиция мыши
public:
    PaintArea(QWidget *ancestor = 0);//создание виджета с холстом для рисования
    //Обработка различных событий в этом виджете
    bool openImage(const QString &fileName);
    bool saveFile(const QString &fileName, const char &fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    //произошли ли изменения?
    bool isModified() const {
        return modified;
    }
    //возврат ширины
    int penWidth() {
        return selectedPenWidth;
    }
    //возврат цвета
    QColor penColor() {
        return selectedPenColor;
    }

protected:
    //отслеживание действий мыши
    void mouseMoveEvent(QMouseEvent *event) override;//движение
    void mousePressEvent(QMouseEvent *event) override;//нажатие
    void mouseReleaseEvent(QMouseEvent *event) override;//отпустили кнопку мыши

    void paintEvent(QPaintEvent *event) override;//событие риосоваение в области холста
    void resizeEvent(QResizeEvent *event) override;//изменить размер

public slots:
    //очистить содержимое
    void clearImage();
    //вывести содержимое
    void output();

};


#endif // DRAWINGAREA_H
