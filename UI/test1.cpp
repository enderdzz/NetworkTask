#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc , char *argv[])
{
	QApplication app(argc, argv);
	QPushButton *button = new QPushButton("Quit");
	QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
	button->show();

	QLabel *label = new QLabel("Hello Qt!");
	label->show();

	return app.exec();
}
