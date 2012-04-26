#ifndef __Qte__
#define __Qte__

#include "maya.h"

#include "mainWindowProjetQT.h" 
#include "camera.h" 
#include "plane.h"
#include "Terrain.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  // Interface
  Ui::Assets interfaceMainWindow;
  MayaGLWidget *mayaglWidget;
  MayaInstanceAll world;

  int currentIndex;                     // Outil selectionne
  QButtonGroup* buttonGroupEditorMode;  // Interface des boutons outils

  // Creation des actions du menu
  void createActions();

  // Export
  void exportMayaElement(QString &file);
  MayaInstanceAll testGeometry(int);

  //PROJECT TERRAIN
  Terrain* terrain;

protected:
	void GenTerrainFlat();
	void GenTerrainGaussian();
	void GenTerrainPerlin();
	void RenderTerrain();


  public slots:
    void New_Scene();
    void ExportObj();
    void ExportMaya();

    void ExecuteToolVoid0();
    void ExecuteToolVoid1();
    void ExecuteToolTerGenFlat();
    void ExecuteToolTerGenGaussian();
    void ExecuteToolTerGenPerlin();
	void ExecuteToolTerRender();
	void ExecuteToolTerWater();

	/*
    void ExecuteTool01();
    void ExecuteTool02();
    void ExecuteTool03();
    void ExecuteTool04();
    void ExecuteTool05();
    void ExecuteTool06();
    void ExecuteTool07();
    void ExecuteTool08();
    void ExecuteTool09();
    void ExecuteTool10();
    void ExecuteTool11();
    void ExecuteTool12();
    void ExecuteTool13();
    void ExecuteTool14();
    void ExecuteTool15();
    void ExecuteTool16();
    void ExecuteTool17();
    void ExecuteTool18();
    void ExecuteTool19();
    void ExecuteTool20();
    void ExecuteTool21();
    void ExecuteTool22();
    void ExecuteTool23();
    void ExecuteTool24();
    void ExecuteTool25();
    void ExecuteTool26();
    void ExecuteTool27();
    void ExecuteTool28();
    void ExecuteTool29();
    void ExecuteTool30();
    void ExecuteTool31();
    void ExecuteTool32();
    void ExecuteTool33();
    void ExecuteTool34();
    void ExecuteTool35();
	*/

    void modifySelectedButton(int);       // Modification de la selection de l'outil
    void editingSceneLeft(const Vector&); // Action de l'outil (Clic Gauche)
    void editingSceneRight(const Vector&);// Action de l'outil (Clic Droit)
    void selectCell(const Vector&);       // Selection d'une cellule

    void editingHeight(const Vector&,int);// Modification de l'épaisseur d'une cellule
};

#endif

