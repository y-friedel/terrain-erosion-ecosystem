#include "maya.h"
#include <fstream>

#include "mainWindowProjetQT.h"
#include "qte.h"


void MainWindow::ExportObj()
{
	QString filename=QFileDialog::getSaveFileName(NULL,
		"Choose a filename to save",
		"",
		"OBJ file (*.obj)");

	if( !filename.isNull() )
	{
		MayaGeometry mg=world.Collapse();
		mg.Save(filename);
	}
}

/*!
\brief Export a maya 2011 scene.
*/
void MainWindow::ExportMaya()
{

	QString filename=QFileDialog::getSaveFileName(NULL,
		"Choose a filename to save",
		"",
		"Maya ASCII file (*.ma)");

	if( !filename.isNull() )
	{
		ofstream fichier (filename.toAscii().data(),ios::trunc);
		if(fichier)
		{
			QString file;

			// Generate Meshs
			file.append(world.ExportMaya());

			// Write file
			fichier.write(file.toAscii().data(),file.size());

			fichier.close();
		}
	}
}

