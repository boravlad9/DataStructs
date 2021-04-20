#include "ccvector.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int ReallocVector(int **Vector, int *Size)
{
    int* myArray = NULL;
    myArray = (int*)realloc((*Vector), (*Size) * 2 * sizeof(int));
    
    if (myArray == NULL)
    {
        return -1;

    } // ce sa fac in cazul asta ca mna practic eu pot sa inserez elementul in cazul in care imi face realloc la memorie

    (*Size) *= 2;
    *Vector = myArray;

    return 0;
}

int VecCreate(CC_VECTOR **Vector)
{

    if (NULL == Vector)
    {
        return -1;
    }
    CC_VECTOR*vec = NULL;
    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        if (ReallocVector(&Vector->Array, &Vector->Size) == -1)
            return -1;
    }

    Vector->Array[Vector->Count] = Value;

    Vector->Count++;
    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        if (ReallocVector(&Vector->Array, &Vector->Size) == -1)
            return -1;
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0)
    {
        return -1;
    }

    if (Vector->Count <= Index)
    {
        return -1;
    }
    if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        if (ReallocVector(&Vector->Array, &Vector->Size) == -1)
            return -1;
    }

    for (int i = Vector->Count - 1; i > Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index + 1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0)
    {
        return -1;
    }

    if (Vector->Count <= Index)
    {
        return -1;
    }

    for (int i = Index; i < Vector->Count - 1; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }
    Vector->Count--;
    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    
    if (NULL == Vector)
    {
        return -1;
    }

    if (NULL == Value)
    {
        return -1;
    }

    if (Vector->Count <= Index)
    {
        return -1;
    }
    
    if (Index < 0)
    {
        return -1;
    }

    *Value = Vector->Array[Index];

    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }
    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }
    Vector->Count = 0;
    return 0;
}

void Swap(int* First, int* Second)
{
    int temp = *First;
    *First = *Second;
    *Second = temp;
}


int Partition(int* Vect, int Low, int High)
{
    int location = Low - 1;
    for (int i = Low; i < High; i++)
    {
        if (Vect[i] > Vect[High])
        {
            location++;
            Swap(&(Vect[i]), &(Vect[location]));
        }
    }
    location++;
    Swap(&(Vect[location]), &(Vect[High]));
    return location;
}

void QuickSort(int *Vect, int Low, int High)
{
    if (Low >= High)
        return;

    int mid = Partition(Vect, Low, High);
    QuickSort(Vect, Low, mid - 1);
    QuickSort(Vect, mid + 1, High);
}

int VecSort(CC_VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    QuickSort(Vector->Array, 0, Vector->Count - 1);
    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    if (NULL == DestVector)
    {
        return -1;
    }
    
    if (NULL == SrcVector)
    {
        return -1;
    }

    for (int i = 0; i < DestVector->Count; i++)
    {
        int value = VecInsertTail(SrcVector, DestVector->Array[i]);
        if (-1 == value)
        {
            // scade count-ul cu i
            return -1;
        }
    }

    return 0;
}
