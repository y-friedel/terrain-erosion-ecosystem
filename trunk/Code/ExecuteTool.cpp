#include "qte.h"
#include "Terrain.h"
#include "Foret.h"
#include "Perlin_d.h"

/*! 
\brief TODO 
*/
void MainWindow::ExecuteToolVoid0()
{
  MaterialObject mo={ ShaderNormal, None, AColor(0.3,0.3,0.3,1.0), AColor(0.5,0.4,0.2,1.0), AColor(0.1,0.1,0.1,1.0), 50.,QString("")};

  MayaGeometry mg=MayaGeometry::CreateBox(Vector(-2),Vector(2));
  mg.setMaterialObject(mo);
  MayaGeometry mg2=MayaGeometry::CreateSphere(Vector(0,0,0),3.,24);
  mg2.setMaterialObject(mo);
  MayaGeometryAll mga(MayaGeometrySet(mg,MayaFrame::Id));
  mayaglWidget->clearWorld();
  mayaglWidget->setWorld(mga);
}

/*! 
\brief TODO 
*/
void MainWindow::ExecuteToolVoid1(){
  MayaGeometryStack mgs;
  mgs.Push();
  mgs.CreateBox(Vector(-2),Vector(2));
  mgs.Translate(Vector(2));
  mgs.CreateBox(Vector(-2),Vector(2));
  mgs.Pop();
  mgs.Push();
  mgs.Rotate(Vector(0,0,Math::Pi/4.0));
  mgs.CreateBox(Vector(-3,-3,4),Vector(3,3,5));
  mgs.Pop();

  MayaGeometryAll mga(MayaGeometrySet(mgs.Get(),MayaFrame::Id));
  mayaglWidget->clearWorld();
  mayaglWidget->setWorld(mga);
}

void MainWindow::GenTerrainPerlin()
{
	int size = 512;

	if(terrain == NULL)
	{
		terrain = new Terrain(size);

/** PERLIN V2 ********************************************************************************/

		Perlin_d per_d = Perlin_d(size,16);
		double* per_ter = per_d.generate();
		gaussian2D(per_ter, size, 2);
		
		terrain->setAllLayer(per_ter, LAYERTYPE_ROCK);

		for(int j = 0; j<size; j++)
		{
			for(int i = 0; i<size; i++)
			{
				//terrain->setLayerHeight(i,j,LAYERTYPE_WATER,10);
				//terrain->setLayerHeight(i,j,LAYERTYPE_SAND,1-(i+j)/*/(size/4.)*/);
				//terrain->setLayerHeight(i,j,LAYERTYPE_SAND, 5);
				/*
				double gauss = gauss_terrain(i, j, size)/3;
				if(gauss > 1)
				{
					terrain->setLayerHeight(i-size/4,j,LAYERTYPE_WATER,gauss);
					terrain->setLayerHeight(i+size/4,j,LAYERTYPE_WATER,gauss);
				}*/
			}
		}
		/*
		for(int j = 3*size/8; j<(size/2)+3; j++)
		{
			for(int i = 3*size/8; i<(size/2)+3; i++)
			{
				//terrain->setLayerHeight(i,j,LAYERTYPE_WATER,1-(i+j));
				terrain->setLayerHeight(i,j,LAYERTYPE_WATER,3);
			}
		}
		*/
	}
}

void MainWindow::GenTerrainGaussian()
{
	int size = 64;

	if(terrain == NULL)
	{
		terrain = new Terrain(size);

		for(int j = 0; j<size; j++)
		{
			
			//initBruit2D(512, 512, 1, 10);
			for(int i = 0; i<size; i++)
			{
				double gauss = gauss_terrain(i, j, size);
				terrain->setLayerHeight(i, j, LAYERTYPE_ROCK, 128+gauss/4);
				if(abs(i-size/2) < 15 && abs(j-size/2) < 15)
				{
					//terrain->setLayerHeight(i,j,LAYERTYPE_WATER,3);
				}
			}
		}
	}
}

void MainWindow::GenTerrainFlat()
{
	int size = 32;

	if(terrain == NULL)
	{
		terrain = new Terrain(size);

		for(int j = 0; j<size; j++)
		{
			for(int i = 0; i<size; i++)
			{
				terrain->setLayerHeight(i, j, LAYERTYPE_ROCK, 1);
			}
		}

		terrain->setLayerHeight(size/2, size/2, LAYERTYPE_WATER, 1);
	}

}

void MainWindow::RenderTerrain()
{
	if(terrain != NULL)
	{
		MaterialObject mo={ ShaderPhongVertexColor, VertexColor, AColor(1,0,0,1), AColor(0.6,0.6,0.6,0.6), AColor(1,1,1,0), 50.,QString("")};


		MayaGeometry mg_terrain = terrain->toMG();
		MayaGeometry mg_water = terrain->waterToMG();
		MayaGeometryAll mga = MayaGeometrySet(mg_terrain,MayaFrame::Id);
		mga.Append(mg_water);

		mayaglWidget->clearWorld();
		mayaglWidget->setWorld(mga);
	}
}

void MainWindow::GenVeget()
{
	std::cout << "Gen Veget" << std::endl;
	if(terrain != NULL && foret != NULL)
	{
		MaterialObject mo={ ShaderPhongVertexColor, VertexColor, AColor(1,0,0,1), AColor(0.6,0.6,0.6,0.6), AColor(1,1,1,0), 50.,QString("")};


		MayaGeometry mg_terrain = terrain->toMG();
		MayaGeometry mg_water = terrain->waterToMG();
		MayaGeometryAll mga = MayaGeometrySet(mg_terrain,MayaFrame::Id);
		mga.Append(mg_water);

		//Creation de la couche foret
		foret = new Foret();
		foret->fillTerrain(terrain, 10000, 0);

		QVector<MayaGeometrySet> vec_mgs;
		foret->foretToMGS(terrain, vec_mgs);
		
		for(int i=0; i< vec_mgs.size(); i++)
		{
			mga.Append(vec_mgs[i]);
		}

		mayaglWidget->clearWorld();
		mayaglWidget->setWorld(mga);
	}
}

void MainWindow::GrowVeget()
{
	if(terrain != NULL && foret != NULL)
	{
		MayaGeometry mg_terrain = terrain->toMG();
		MayaGeometry mg_water = terrain->waterToMG();
		MayaGeometryAll mga = MayaGeometrySet(mg_terrain,MayaFrame::Id);
		mga.Append(mg_water);
		
		for(int i = 0; i<1; i++)
		{
			foret->allGrow();
			std::cout << i << "/1" << std::endl; 
		}

		QVector<MayaGeometrySet> vec_mgs;
		foret->foretToMGS(terrain, vec_mgs);
		for(int i=0; i< vec_mgs.size(); i++)
		{
			mga.Append(vec_mgs[i]);
		}

		mayaglWidget->clearWorld();
		mayaglWidget->setWorld(mga);
	}
}

void MainWindow::ExecuteToolTerGenFlat()
{
	GenTerrainFlat();
	RenderTerrain();
}

void MainWindow::ExecuteToolTerGenGaussian()
{
	GenTerrainGaussian();
	RenderTerrain();
}

void MainWindow::ExecuteToolTerGenPerlin()
{
	GenTerrainPerlin();
	RenderTerrain();
}

void MainWindow::ExecuteToolTerRender()
{
	RenderTerrain();
}

void MainWindow::ExecuteToolGenVeget()
{
	GenVeget();
}

void MainWindow::ExecuteToolGrowVeget()
{
	GrowVeget();
}

bool rendu = false;
void MainWindow::ExecuteToolTerWater()
{
	if(terrain != NULL)
	{
		const int nbIter = 500;

		for(int i=0; i<nbIter; i++)
		{
			//terrain->fhsRain(9e-5);
			terrain->fhsRain(2e-4);
			//terrain->fhsRain(0.009);
			terrain->fhsIterationWater();
			terrain->fhsIterationErosion();
			terrain->fhsEvaporation(8e-5);

			terrain->thermalErosion(0.001, 0.01);

			if(i%50==0 || i == nbIter-1)
			{
				MayaGeometry mg_terrain = terrain->toMG();
				MayaGeometryAll mga = MayaGeometrySet(mg_terrain,MayaFrame::Id);
				mayaglWidget->clearWorld();
				mayaglWidget->setWorld(mga);
			}

			std::cout << i << "/" << nbIter << std::endl;
		}

		terrain->fhsEvaporation(0.1);
		terrain->setGrowLayer();
	}

}


/*
void MainWindow::ExecuteTool03(){}
void MainWindow::ExecuteTool05(){}
void MainWindow::ExecuteTool06(){}
void MainWindow::ExecuteTool07(){}
void MainWindow::ExecuteTool08(){}
void MainWindow::ExecuteTool09(){}
void MainWindow::ExecuteTool10(){}
void MainWindow::ExecuteTool11(){}
void MainWindow::ExecuteTool12(){}
void MainWindow::ExecuteTool13(){}
void MainWindow::ExecuteTool14(){}
void MainWindow::ExecuteTool15(){}
void MainWindow::ExecuteTool16(){}
void MainWindow::ExecuteTool17(){}
void MainWindow::ExecuteTool18(){}
void MainWindow::ExecuteTool19(){}
void MainWindow::ExecuteTool20(){}
void MainWindow::ExecuteTool21(){}
void MainWindow::ExecuteTool22(){}
void MainWindow::ExecuteTool23(){}
void MainWindow::ExecuteTool24(){}
void MainWindow::ExecuteTool25(){}
void MainWindow::ExecuteTool26(){}
void MainWindow::ExecuteTool27(){}
void MainWindow::ExecuteTool28(){}
void MainWindow::ExecuteTool29(){}
void MainWindow::ExecuteTool30(){}
void MainWindow::ExecuteTool31(){}
void MainWindow::ExecuteTool32(){}
void MainWindow::ExecuteTool33(){}
void MainWindow::ExecuteTool34(){}
void MainWindow::ExecuteTool35(){}
*/