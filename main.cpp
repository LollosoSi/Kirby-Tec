#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    // istanzio applicazione Qt
    QApplication a(argc, argv);

	// hello world
    QPushButton* button = new QPushButton("Hello world!");
    button->show();

    // eseguo applicazione Qt
    return a.exec();
}
