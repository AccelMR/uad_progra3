#pragma once

#include <iostream>
#include "../Include/CVector3.h"
#include "../Include/CHexGrid.h"

class CQuadTree
{
private:
	CVector3 firstFourPoints [4];
	CHexGrid *myHex;


public:
	CQuadTree(CHexGrid *myhex);
	~CQuadTree();

	void initialized();
};

