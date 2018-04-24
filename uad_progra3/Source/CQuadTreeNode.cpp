#include "..\Include\CQuadTreeNode.h"


CQuadTreeNode::CQuadTreeNode(CVector3* verticesNode, CHexGrid* myHex):
	topLeftChild(nullptr),
	topRightChild(nullptr),
	botLeftChild(nullptr),
	botRightChild(nullptr)
{
	Log << "Constructor: CQuadTreeNode()" << std::endl;

	centerLeaf.setValues((verticesNode[0].getX() + verticesNode[1].getX()) / 2,
		0,
		(verticesNode[0].getZ() + verticesNode[1].getZ()) / 2);
}

CQuadTreeNode::~CQuadTreeNode()
{
}

void CQuadTreeNode::Subdivide(CHexGrid* myHex)
{
	for (size_t i = 0; i < SIZE_OF_HEXGRID; i++) {
		for (size_t j = 0;  j < SIZE_OF_HEXGRID;  j++) {
		}
	}
	return;
}
