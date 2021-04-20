#include "ccstack.h"
#include "common.h"

int StCreate(CC_STACK **Stack)
{
    if (NULL == Stack)
        return -1;

    *Stack = (CC_STACK*)malloc(sizeof(CC_STACK));

    if (NULL == *Stack)
    {
        return -1;
    }

    CC_VECTOR* vect = NULL;
    int value = VecCreate(&vect);
    
    if (-1 == value)
    {
        free(*Stack);
        return -1;
    }
    
    (*Stack)->Vect = vect;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    if (NULL == Stack)
        return -1;

    int value = VecDestroy(&(*Stack)->Vect);
    
    if (-1 == value)
    {
        return -1;
    }

    free(*Stack);
    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    if (NULL == Stack)
    {
        return -1;
    }

    int value = VecInsertTail(Stack->Vect, Value);
    
    return value;
}

int StPop(CC_STACK *Stack, int *Value)
{
    if (NULL == Stack)
        return -1;

    if (NULL == Value)
    {
        return -1;
    }

    int value = VecGetValueByIndex(Stack->Vect, VecGetCount(Stack->Vect) - 1, Value);
    if (-1 == value)
    {
        return -1;
    }
    value = VecRemoveByIndex(Stack->Vect, VecGetCount(Stack->Vect) - 1);
    return value;
}


int StPeek(CC_STACK *Stack, int *Value)
{
    if (NULL == Stack)
    {
        return -1;
    }

    if (NULL == Value)
    {
        return -1;
    }

    
    int value = VecGetValueByIndex(Stack->Vect, VecGetCount(Stack->Vect) - 1, Value);
    return value;
}

int StIsEmpty(CC_STACK *Stack)
{
    if (NULL == Stack)
        return -1;
    
    int value = VecGetCount(Stack->Vect);

    if (0 == value)
        return 1;
    return 0;
}

int StGetCount(CC_STACK *Stack)
{
    if (NULL == Stack)
        return -1;
    
    return VecGetCount(Stack->Vect);
}

int StClear(CC_STACK* Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    int value = VecClear(Stack->Vect);
    return value;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    if (NULL == Stack)
    {
        return -1;
    }
    
    if (NULL == StackToPush)
    {
        return -1;
    }

    while (!StIsEmpty(StackToPush))
    {
        int value = 0;
        StPop(StackToPush, &value);
        VecInsertHead(Stack->Vect, value);
    }
    return 0;
}
