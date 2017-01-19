//
//
//


#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "TreePath.h"
#include "Position.h"
#include "findAllPossiblePaths.h"

pathTree findAllPossiblePaths(Board board, Position *startingPosition) {
	pathTree* pt      = createNewPathTree();
	Position pa[SIZE] = { NULL };
	int arrSize		  = 0;
	pt->root	      = createTreeNode(startingPosition);
	connectAllBoardTreeNodes(pt->root, pa, arrSize, board);

	return *pt;

}
BOOL isPositionInArray(Position *position, Position* positions, int arrSize) {
	for (int i = 0; i < arrSize; i++) {
		if (isEqualPos(positions[i], *position))
			return TRUE;
	}
	return FALSE;
}



void connectAllBoardTreeNodes(treeNode* tn, Position* positions, int arrSize, Board board) {
	int x = coordinateToInt( tn->position[0]), y = coordinateToInt( tn->position[1] );


	positions[arrSize][0] = tn->position[0];
	positions[arrSize][1] = tn->position[1];
	++arrSize;
	
	if (tn->up == NULL) {
		connectTreeNodeWithCoordinates(x, y - 1, 'u', tn, positions, arrSize, board);
	}
	if (tn->down == NULL) {
		connectTreeNodeWithCoordinates(x, y + 1, 'd', tn, positions, arrSize, board);
	}
	if (tn->right == NULL) {
		connectTreeNodeWithCoordinates(x + 1, y, 'r', tn, positions, arrSize, board);
	}
	if (tn->right == NULL) {
		connectTreeNodeWithCoordinates(x - 1, y, 'l', tn, positions, arrSize, board);
	}
}
	
void connectTreeNodeWithCoordinates(int x, int y, char direction, treeNode* source, Position* positions, int arrSize, Board board) {
	if (inboard(x) && inboard(y)) {
		Position* pos = createPos(x, y);
		if (!isPositionInArray(pos, positions, arrSize) && getPosValue(*pos, board) != 0) {
			treeNode* target = createTreeNode(pos);
			connectTreeNodeWith(direction, source, target);
			connectAllBoardTreeNodes(target, positions, arrSize, board);
		}
	}
}
void connectTreeNodeWith(char direction, treeNode* base, treeNode* next) {
	switch (direction)
	{
	case 'u': // UP
		base->up = next;
		next->down = base;
		break;
	case 'd': // DOWN
		base->down = next;
		next->up = base;
		break;
	case 'r': // RIGHT
		base->right = next;
		next->left = base;
		break;
	case 'l': // LEFT
		base->left = next;
		next->right = base;
		break;
		
	}

}