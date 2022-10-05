#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QObject>
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    // istanzio applicazione Qt
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();

	// hello world
    QPushButton* button = new QPushButton("Hello world!", mw);
    button->show();

    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

    // eseguo applicazione Qt
    return a.exec();
}
