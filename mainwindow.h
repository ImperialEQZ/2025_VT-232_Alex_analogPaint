#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "DrawingArea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;//функция, завершающая события

private slots://Возможные события, список "слотов"
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private://Действия пользователя
    void createActions();//создать действие
    void createMenus();//меню с разными событиями
    bool saveFile(const QByteArray &fileFormat);//сохранить в выбранном формате
    bool abilitySave();//Возможность сохранить файл


    DrawingArea *drawingArea;
//Список виджетов-меню
    QMenu *saveAs;//сохранить файл как
    QMenu *menuFile;//Открыть как, сохранить как, выйти
    QMenu *menuOption;//смена цвета, ширины пера, очистить холст
    QMenu *menuHelp;//О приложении PaintAnalog

    QAction *openActions;//Доступные действия

    QList<QAction *> saveAsActions;//список действий
    QAction *penColorActions;//изменить цвет пера
    QAction *printActions;//"печать"
    QAction *exitAct;//Добавил, действие выхода из программы
    QAction *penWidthActions;//изменить ширину пера
    QAction *clearAreaActions;//очистить холст
    QAction *aboutActions;//открытие диалогового окна "О программе"
};
#endif // MAINWINDOW_H
