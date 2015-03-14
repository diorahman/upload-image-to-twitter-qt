#include <QtGui/QApplication>
#include <QFile>
#include <QFileInfo>

#include "twitter.h"

Q_DECL_EXPORT int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	Twitter t;
	t.testUploadImage();
	return app.exec();
}
