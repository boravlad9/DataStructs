#pragma once

typedef struct _NODE
{
    int Value;
    struct _NODE* Left;
    struct _NODE* Right;
    int Height;
    int Key;
}NODE;

typedef struct _CC_TREE 
{
    NODE* Node;
    int ElementCount;
} CC_TREE;

int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree);

// Duplicates are allowed
int TreeInsert(CC_TREE *Tree, int Value);
int TreeInsertGeneral(CC_TREE* Tree, int Value, int Key);

// Removes all elements equal to Value
int TreeRemove(CC_TREE *Tree, int Value);
int TreeRemoveGeneral(CC_TREE* Tree, int Key);

int TreeGetValueByKey(CC_TREE* Tree, int Key, int* Value);


//  Returns:
//       1  - Tree contains Value
//       0  - Tree does not contain Value
//      -1  - Error or invalid parameter
int TreeContains(CC_TREE *Tree, int Value);

// Returns the number of elements in Tree or -1 in case of error or invalid parameter
int TreeGetCount(CC_TREE *Tree);

// Returns the height of Tree or -1 in case of error or invalid parameter
int TreeGetHeight(CC_TREE *Tree);

// Removes every element of the tree
int TreeClear(CC_TREE *Tree);

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);
