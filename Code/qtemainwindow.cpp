
#include "mainWindowProjetQT.h"
#include "qte.h"

MainWindow::MainWindow()
{
  // Chargement de l'interface
  interfaceMainWindow.setupUi(this);

  // Chargement du GLWidget
  mayaglWidget=new MayaGLWidget;
  QGridLayout* GLlayout=new QGridLayout;
  GLlayout->addWidget(mayaglWidget,0,0);
  GLlayout->setContentsMargins(0,0,0,0);
  interfaceMainWindow.widget_GL->setLayout(GLlayout);
  
  // Creation des connect
  createActions();

  terrain = NULL;
}

MainWindow::~MainWindow()
{
	if(terrain != NULL) delete terrain;
}

void MainWindow::createActions()
{
	//File
	connect(interfaceMainWindow.actionNew_Scene , SIGNAL(triggered()), this, SLOT(New_Scene()));
	connect(interfaceMainWindow.actionExport_obj, SIGNAL(triggered()), this, SLOT(ExportObj()));
	connect(interfaceMainWindow.actionExport_ma , SIGNAL(triggered()), this, SLOT(ExportMaya()));
	connect(interfaceMainWindow.actionExit      , SIGNAL(triggered()), this, SLOT(close()));

	connect(interfaceMainWindow.Objects_pushButton_void0, SIGNAL( clicked() ), this, SLOT(ExecuteToolVoid0()));
	connect(interfaceMainWindow.Objects_pushButton_void1, SIGNAL( clicked() ), this, SLOT(ExecuteToolVoid1()));
	connect(interfaceMainWindow.Objects_pushButton_terGenFlat, SIGNAL( clicked() ), this, SLOT(ExecuteToolTerGenFlat()));
	connect(interfaceMainWindow.Objects_pushButton_terGenGaussian, SIGNAL( clicked() ), this, SLOT(ExecuteToolTerGenGaussian()));
	connect(interfaceMainWindow.Objects_pushButton_terGenPerlin, SIGNAL( clicked() ), this, SLOT(ExecuteToolTerGenPerlin()));
	connect(interfaceMainWindow.Objects_pushButton_terRender, SIGNAL( clicked() ), this, SLOT(ExecuteToolTerRender()));
	connect(interfaceMainWindow.Objects_pushButton_terWater, SIGNAL( clicked() ), this, SLOT(ExecuteToolTerWater()));

	//Veget
	connect(interfaceMainWindow.Objects_pushButton_genVeget, SIGNAL( clicked() ), this, SLOT(ExecuteToolGenVeget()));
	connect(interfaceMainWindow.Objects_pushButton_growVeget, SIGNAL( clicked() ), this, SLOT(ExecuteToolGrowVeget()));

	// Connection des boutons
	/*
	connect(interfaceMainWindow.Objects_o03_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool03()));
	connect(interfaceMainWindow.Objects_o05_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool05()));
	connect(interfaceMainWindow.Objects_o06_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool06()));
	connect(interfaceMainWindow.Objects_o07_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool07()));
	connect(interfaceMainWindow.Objects_o08_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool08()));
	connect(interfaceMainWindow.Objects_o09_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool09()));
	connect(interfaceMainWindow.Objects_o10_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool10()));
	connect(interfaceMainWindow.Objects_o11_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool11()));
	connect(interfaceMainWindow.Objects_o12_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool12()));
	connect(interfaceMainWindow.Objects_o13_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool13()));
	connect(interfaceMainWindow.Objects_o14_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool14()));
	connect(interfaceMainWindow.Objects_o15_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool15()));
	connect(interfaceMainWindow.Objects_o16_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool16()));
	connect(interfaceMainWindow.Objects_o17_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool17()));
	connect(interfaceMainWindow.Objects_o18_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool18()));
	connect(interfaceMainWindow.Objects_o19_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool19()));
	connect(interfaceMainWindow.Objects_o20_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool20()));
	connect(interfaceMainWindow.Objects_o21_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool21()));
	connect(interfaceMainWindow.Objects_o22_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool22()));
	connect(interfaceMainWindow.Objects_o23_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool23()));
	connect(interfaceMainWindow.Objects_o24_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool24()));
	connect(interfaceMainWindow.Objects_o25_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool25()));
	connect(interfaceMainWindow.Objects_o26_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool26()));
	connect(interfaceMainWindow.Objects_o27_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool27()));
	connect(interfaceMainWindow.Objects_o28_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool28()));
	connect(interfaceMainWindow.Objects_o29_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool29()));
	connect(interfaceMainWindow.Objects_o30_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool30()));
	connect(interfaceMainWindow.Objects_o31_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool31()));
	connect(interfaceMainWindow.Objects_o32_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool32()));
	connect(interfaceMainWindow.Objects_o33_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool33()));
	connect(interfaceMainWindow.Objects_o34_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool34()));
	connect(interfaceMainWindow.Objects_o35_pushButton, SIGNAL( clicked() ), this, SLOT(ExecuteTool35()));
	*/
	connect(mayaglWidget, SIGNAL( _signalEditHeight(const Vector&,int)), this, SLOT(editingHeight(const Vector&,int)));

	connect(mayaglWidget, SIGNAL( _signalEditSceneLeft (const Vector&) ), this, SLOT(editingSceneLeft (const Vector&)));
	connect(mayaglWidget, SIGNAL( _signalEditSceneRight(const Vector&) ), this, SLOT(editingSceneRight(const Vector&)));

	/*interfaceMainWindow.Objects_o01_pushButton->setText("Cube");
	interfaceMainWindow.Objects_o02_pushButton->setText("Cube");*/
}

void MainWindow::New_Scene()
{
	cout<<"New Scene"<<endl;
}

/*!
\brief Modify the current selected button.
*/
void MainWindow::modifySelectedButton(int num)
{
}

/*!
\brief Action done when the left mouse button is pushed.
*/
void MainWindow::editingSceneLeft(const Vector& p)
{

}

/*!
\brief Action done when the right mouse button is pushed.
*/
void MainWindow::editingSceneRight(const Vector& p)
{

}

/*!
\brief Action done when the right mouse button is pushed.
*/
void MainWindow::selectCell(const Vector& p)
{

}

void MainWindow::editingHeight(const Vector& p,int steps)
{

}
