#pragma once

#include "..\Include\CQuadTree.h"

class CQuadTreeNode
{
private:

	CQuadTreeNode *root;
	CQuadTreeNode *fChild;
	CQuadTreeNode *sChild;
	CQuadTreeNode *tChild;
	CQuadTreeNode *frthChild;

	CVector3 data[18];

public:

	CQuadTreeNode();
	~CQuadTreeNode();
};

