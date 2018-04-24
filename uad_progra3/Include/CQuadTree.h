#pragma once

#include <iostream>
#include "../Include/CVector3.h"
#include "../Include/CHexGrid.h"
#include "../Include/CQuadTreeNode.h"

class CQuadTree
{
private:
	CHexGrid *myHex;
	CVector3 verticesRoot [2];
	
	//CQuadTreeNode *root;

public:
	CQuadTree(CHexGrid *myhex);
	~CQuadTree();
	
	CVector3* getVerticesRoot();
	bool Inicialize();
};

