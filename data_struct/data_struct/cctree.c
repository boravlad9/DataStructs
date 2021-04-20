#include "cctree.h"
#include "common.h"

NODE* CreateNode(int Value, int Key)
{
    NODE* node = NULL;
    node = (NODE*)malloc(sizeof(NODE));
    if (NULL == node)
    {
        return NULL;
    }
    node->Left = NULL;
    node->Right = NULL;
    node->Height = 1;
    node->Key = Key;
    node->Value = Value;
    return node;
}

int TreeCreate(CC_TREE **Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }

    *Tree = NULL;
    *Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
    if (NULL == *Tree)
    {
        return -1;
    }
    (*Tree)->Node = NULL;
    (*Tree)->ElementCount = 0;
    return 0;
}

void TreeKill(NODE** Tree)
{
    if ((*Tree) == NULL)
    {
        return;
    }
    TreeKill(&(*Tree)->Right);
    TreeKill(&(*Tree)->Left);
    free(*Tree);
    (*Tree) = NULL;
}


int TreeDestroy(CC_TREE **Tree)
{
    if (Tree == NULL)
    {
        return -1;
    }
    if (*Tree == NULL)
    {
        return -1;
    }
    TreeKill(&(*Tree)->Node);
    free(*Tree);
    (*Tree) = NULL;
    return 0;
}

int Max(int First, int Second)
{
    if (First > Second)
        return First;
    return Second;
}

int GetHeight(NODE* Current)
{
    if (NULL == Current)
    {
        return 0;
    }
    return Current->Height;
}

NODE* RightRotate(NODE* Current)
{
    NODE* first = Current->Left;
    NODE* second = Current->Right;
    first->Right = Current;
    Current->Left = second;
    Current->Height = Max(GetHeight(Current->Left), GetHeight(Current->Right)) + 1;
    Current->Height = Max(GetHeight(first->Left), GetHeight(first->Right)) + 1;
    return first;
}

NODE* LeftRotate(NODE* Current)
{
    NODE* first = Current->Right;
    NODE* second = Current->Left;
    first->Left = Current;
    Current->Right = second;
    Current->Height = Max(GetHeight(Current->Left), GetHeight(Current->Right)) + 1;
    first->Height = Max(GetHeight(first->Left), GetHeight(first->Right)) + 1;
    return first;
}

int GetBalance(NODE* Current)
{
    if (NULL == Current)
        return 0;
    return GetHeight(Current->Left) - GetHeight(Current->Right);
}

NODE* RecursiveInsert(NODE* Node, int Value, int Key)
{
    if (NULL == Node)
    {
        return CreateNode(Value, Key);
    }
    if (Key < Node->Key)
        Node->Left = RecursiveInsert(Node->Left, Value, Key);
    else if (Key > Node->Key)
        Node->Right = RecursiveInsert(Node->Right, Value, Key);
    else
        return Node;
    
    Node->Height = 1 + Max(GetHeight(Node->Left), GetHeight(Node->Right));

    int balance = GetBalance(Node);

    if (1 < balance && Key > Node->Left->Key)
        return RightRotate(Node);

    if (-1 > balance && Key > Node->Right->Key)
        return LeftRotate(Node);

    if (1 < balance && Key > Node->Left->Key)
    {
        Node->Left = LeftRotate(Node->Left);
        return RightRotate(Node);
    }

    if (-1 > balance && Key < Node->Right->Key)
    {
        Node->Right = RightRotate(Node->Right);
        return LeftRotate(Node);
    }

    return Node;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    if (NULL == Tree)
    {
        return -1;
    }
    return TreeInsertGeneral(Tree, Value, Value);
}

int TreeInsertGeneral(CC_TREE* Tree, int Value, int Key)
{
    if (NULL == Tree)
    {
        return -1;
    }
    Tree->Node = RecursiveInsert(Tree->Node, Value, Key);
    Tree->ElementCount++;
    return 0;
}

NODE* GetMinValueNode(NODE* Current)
{
    while (NULL != Current)
    {
        Current = Current->Left;
    }
    return Current;
}

NODE* DeleteRecursive(NODE* Node, int Key, int *Number)
{
    if (NULL == Node)
    {
        return NULL;
    }

    if (Key < Node->Key)
        Node->Left = DeleteRecursive(Node->Left, Key, Number);
    else if (Key > Node->Key)
        Node->Right = DeleteRecursive(Node->Right, Key, Number);
    else
    {
        if ((NULL == Node->Left) || (NULL == Node->Right))
        {
            NODE* temp = NULL;
            if (Node->Left)
            {
                temp = Node->Left;
            }
            else
            {
                temp = Node->Right;
            }

            if (NULL == temp)
            {
                temp = Node;
                Node = NULL;
            }
            else
            {
                *Node = *temp;
            }
            (*Number)++;
            free(temp);
        }
        else
        {
            NODE* temp = GetMinValueNode(Node->Right);
            Node->Key = temp->Key;
            Node->Value = temp->Value;
            Node->Right = DeleteRecursive(Node->Right, Key, Number);
        }
        DeleteRecursive(Node, Key, Number);
    }

    if (NULL == Node)
        return NULL;

    Node->Height = 1 + Max(GetHeight(Node->Right), GetHeight(Node->Left));
    int balance = GetBalance(Node);
    if (1 < balance && GetBalance(Node->Left) >= 0)
        return RightRotate(Node);
    
    if (1 < balance && GetBalance(Node->Left) < 0)
    {
        Node->Left = LeftRotate(Node->Left);
        return RightRotate(Node);
    }

    if (-1 > balance && GetBalance(Node->Right) <= 0)
    {
        return LeftRotate(Node);
    }

    if (-1 > balance && GetBalance(Node->Right) > 0)
    {
        Node->Right = RightRotate(Node->Right);
        return LeftRotate(Node);
    }
    return Node;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
    if (NULL == Tree)
    {
        return -1;
    }
    return TreeRemoveGeneral(Tree, Value);
}

int TreeRemoveGeneral(CC_TREE* Tree, int Key)
{
    if (NULL == Tree)
    {
        return -1;
    }
    int number = 0;
    Tree->Node = DeleteRecursive(Tree->Node, Key, &number);
    if (0 == number)
    {
        return -1;
    }
    Tree->ElementCount -= number;
    return 0;
}

int TreeGetValueByKey(CC_TREE* Tree, int Key, int* Value)
{
    if (NULL == Tree)
    {
        return -1;
    }

    if (NULL == Value)
    {
        return -1;
    }
    NODE* current = Tree->Node;
    while (current)
    {
        if (Key == current->Key)
        {
            *Value = current->Value;
            return 0;
        }
        else
        {
            if (Key > current->Key)
            {
                current = current->Right;
            }
            else
            {
                current = current->Left;
            }
        }
    
    }
    return -1;
}

int TreeContains(CC_TREE *Tree, int Value)
{
    if (NULL == Tree)
    {
        return -1;
    }
    NODE* current = Tree->Node;
    while (current)
    {
        if (current->Key == Value)
        {
            return 1;
        }
        if (current->Key < Value)
        {
            current = current->Right;
        }
        else
        {
            current = current->Left;
        }
    }
    return 0;
}

int TreeGetCount(CC_TREE *Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }
    return Tree->ElementCount;
}

int TreeGetHeight(CC_TREE *Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }
    return GetHeight(Tree->Node);
}

int TreeClear(CC_TREE *Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }
    Tree->ElementCount = 0;
    TreeKill(&Tree->Node);
    return 0;
}

void NthPreorderNode(NODE* Node, int Index, int* Value, int* Counter)
{
    if (NULL == Node)
    {
        return;
    }
    if (*Counter == Index)
        *Value = Node->Key;
    (*Counter)++;
    NthPreorderNode(Node->Left, Index, Value, Counter);
    NthPreorderNode(Node->Right, Index, Value, Counter);

}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    if (NULL == Tree)
    {
        return -1;
    }
    if (NULL == Value)
    {
        return -1;
    }
    if (Index < 0 || Index >= TreeGetCount(Tree))
    {
        return -1;
    }
    int counter = 0;
    NthPreorderNode(Tree->Node, Index, Value, &counter);
    return 0;
}

void NthInorderNode(NODE* Node, int Index, int* Value, int* Counter)
{
    if (NULL == Node)
    {
        return;
    }
    NthInorderNode(Node->Left, Index, Value, Counter);
    if (*Counter == Index)
        *Value = Node->Key;
    (*Counter)++;
    NthInorderNode(Node->Right, Index, Value, Counter);

}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    if (NULL == Tree)
    {
        return -1;
    }
    if (NULL == Value)
    {
        return -1;
    }
    if (Index < 0 || Index >= TreeGetCount(Tree))
    {
        return -1;
    }
    int counter = 0;
    NthInorderNode(Tree->Node, Index, Value, &counter);
    return 0;
}

void NthPostorderNode(NODE* Node, int Index, int* Value, int *Counter)
{
    if (NULL == Node)
    {
        return;
    }
    NthPostorderNode(Node->Left, Index, Value, Counter);
    NthPostorderNode(Node->Right, Index, Value, Counter);
    if (*Counter == Index)
        *Value = Node->Key;
    (*Counter)++;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    if (Tree == NULL)
    {
        return -1;
    }
    if (Value == NULL)
    {
        return -1;
    }
    if (Index < 0 || Index >= TreeGetCount(Tree))
    {
        return -1;
    }
    int counter = 0;
    NthPostorderNode(Tree->Node, Index, Value, &counter);
    return 0;
}

