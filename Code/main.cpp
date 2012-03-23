#include "qte.h"
#include "Terrain.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setStyle(new QPlastiqueStyle);	

	MainWindow mainWin;	
	mainWin.show();

	return app.exec();
} 
