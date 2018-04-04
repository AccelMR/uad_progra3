#include "..\Include\CQuadTree.h"



CQuadTree::CQuadTree(CHexGrid *myhex):
	myHex(myhex)
{

}


CQuadTree::~CQuadTree()
{
}

void CQuadTree::initialized()
{
	// Points that I need to build the QuadTree
	CVector3 point4ofFC;
	CVector3 point3ofFC;
	CVector3 point3ofLCR;
	CVector3 point3ofLSRC;

	point4ofFC = myHex->getCellPointInfo(0, 0, 4);
	point3ofFC = myHex->getCellPointInfo(0, 0, 3);
	point3ofLCR = myHex->getCellPointInfo(SIZE_OF_HEXGRID - 1, 0, 3);
	point3ofLSRC = myHex->getCellPointInfo(1, SIZE_OF_HEXGRID - 1, 3);

	// P0 of QuadTree
	firstFourPoints[0].setValues(point4ofFC.getX(),0,point3ofFC.getZ());

	// P1 of QuadTree
	firstFourPoints[1].setValues(point3ofLCR.getX(),0,point3ofFC.getZ());

	// P3 of QuadTree
	firstFourPoints[2].setValues(point4ofFC.getX(),0,point3ofLSRC.getZ());

	//P4 of QuadTree
	firstFourPoints[3].setValues(point3ofLCR.getX(),0,point3ofLSRC.getZ());

	for (size_t i = 0; i < 4; i++)
	{
		std::cout << firstFourPoints[i].getX() << "   ";
		std::cout << firstFourPoints[i].getZ();
		std::cout << std::endl;
	}
}
