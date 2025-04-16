#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class DrawingArea;//"холст" программы

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void endEvent(QCloseEvent *event) override;//функция, завершающая события


private slots://Возможные события, список "слотов"
    void open();
    void save();
    void changePenColor();
    void changePenWidth();
    void aboutPaintAnalog();

private://Действия пользователя
    void createActions();//создать действие
    void createMenu();//меню с разными событиями
    bool saveFile(const QByteArray &formatFile);//сохранить в выбранном формате
    bool abilitySave();//Возможность сохранить файл

    DrawingArea *DrawingArea;
//Список виджетов-меню
    QMenu *saveAs;//сохранить файл как
    QMenu *menuFile;//
    QMenu *menuOption;//меню параметров (пример, смена цвета)
    QMenu *menuHelp;//меню о программе PaintAnalog

    QAction *openActions;//Доступные действия

    QList<QAction *> saveAsActions;//список действий
    QAction *penColorActions;//изменить цвет пера
    QAction *printActions;//печать
    QAction *penWidthActions;//изменить ширину пера
    QAction *clearAreaActions;//очистить холст
    QAction *aboutActions;//открытие диалогового окна

};
#endif // MAINWINDOW_H
