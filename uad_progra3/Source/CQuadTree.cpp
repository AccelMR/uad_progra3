#include "..\Include\CQuadTree.h"



CQuadTree::CQuadTree(CHexGrid *myhex):
	myHex(myhex)
	//root(nullptr)
{
}


CQuadTree::~CQuadTree()
{
}

CVector3* CQuadTree::getVerticesRoot()
{
	return verticesRoot;
}

bool CQuadTree::Inicialize()
{
	// Points that I need to build the QuadTree
	CVector3 fourthPoint_firstCell;
	CVector3 thirdPoint_firstCell;
	CVector3 firstPoint_lastCellRow;
	CVector3 zeroPoint_lastCell;

	fourthPoint_firstCell = myHex->getCellPointInfo(0, 0, 4);
	thirdPoint_firstCell = myHex->getCellPointInfo(0, 0, 3);
	firstPoint_lastCellRow = myHex->getCellPointInfo(SIZE_OF_HEXGRID - 1, 0, 1);
	zeroPoint_lastCell = myHex->getCellPointInfo(SIZE_OF_HEXGRID - 1, SIZE_OF_HEXGRID - 1, 0);

	verticesRoot[0].setValues(fourthPoint_firstCell.getX(), 0, thirdPoint_firstCell.getZ());
	//verticesRoot[1].setValues(firstPoint_lastCellRow.getX(), 0, thirdPoint_firstCell.getZ());
	verticesRoot[1].setValues(firstPoint_lastCellRow.getX(), 0, zeroPoint_lastCell.getZ());
	//verticesRoot[3].setValues(fourthPoint_firstCell.getX(), 0, zeroPoint_lastCell.getZ());

	for (size_t i = 0; i < 2; i++)
	{
		std::cout << verticesRoot[i].getX() << "   ";
		std::cout << verticesRoot[i].getZ();
		std::cout << std::endl;
	}

	//root = new CQuadTreeNode(verticesRoot, myHex);
	//root->Subdivide(myHex);

	return true;
}
