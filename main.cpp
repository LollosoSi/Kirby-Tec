#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // istanzio applicazione Qt
    QApplication a(argc, argv);

    MainWindow *mw = new MainWindow();

	// hello world
    QPushButton* button = new QPushButton("Hello world!", mw);
    button->show();

    // eseguo applicazione Qt
    return a.exec();
}
