#pragma once

#include "..\Include\CQuadTree.h"

class CQuadTreeNode
{
private:

	CQuadTreeNode *topLeftChild;
	CQuadTreeNode *topRightChild;
	CQuadTreeNode *botLeftChild;
	CQuadTreeNode *botRightChild;

	CVector3 data;
	//CVector3 verticesNode;
	CVector3 centerLeaf;

public:

	CQuadTreeNode(CVector3* verticesNode, CHexGrid* myHex);
	~CQuadTreeNode();

	void Subdivide(CHexGrid* myHex);
};

