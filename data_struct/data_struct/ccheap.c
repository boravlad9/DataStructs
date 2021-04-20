#include "ccheap.h"
#include "common.h"


#define myFunction(myHeap)  (myHeap->Type == 0) ? Higher : Lower

int Parent(int Location)
{
    return Location / 2;
}

int Left(int Location)
{
    return 2 * Location + 1;
}

int Right(int Location)
{
    return 2 * Location + 2;
}

int Higher(int A, int B)
{
    return A > B;
}


int Lower(int A, int B)
{
    return A < B;
}

void Heapify(CC_HEAP* Heap, int Place, int Function(int, int))
{
    int left = Left(Place);
    int right = Right(Place);
    int largest;
    if (left < Heap->Vect->Count && Function(Heap->Vect->Array[left], Heap->Vect->Array[Place]))
    {
        largest = left;
    }
    else
    {
        largest = Place;
    }
    if (right < Heap->Vect->Count && Function(Heap->Vect->Array[right], Heap->Vect->Array[largest]))
    {
        largest = right;
    }
    if (largest != Place)
    {

        Swap(&Heap->Vect->Array[Place], &Heap->Vect->Array[largest]);
        Heapify(Heap, largest, Function);
    }
}

int CreateHeap(CC_HEAP** Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }
    *Heap = NULL;
    *Heap = (CC_HEAP*)malloc(sizeof(CC_HEAP));
    if (NULL == *Heap)
    {
        return -1;
    }

    if (VecCreate(&(*Heap)->Vect) == -1)
    {
        free(*Heap);
        return -1;
    }


    return 0;
}

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    int value = CreateHeap(MaxHeap);
    if (-1 == value)
    {
        return -1;
    }
    (*MaxHeap)->Type = 0;
    if (NULL != InitialElements)
    {
        VecAppend(InitialElements, (*MaxHeap)->Vect);
        for (int i = (*MaxHeap)->Vect->Count / 2; i >= 0; i--)
        {
            Heapify(*MaxHeap, i, myFunction((*MaxHeap)));
        }
    }
    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    int value = CreateHeap(MinHeap);
    if (-1 == value)
    {
        return -1;
    }
    (*MinHeap)->Type = 1;
    if (NULL != InitialElements)
    {
        VecAppend(InitialElements, (*MinHeap)->Vect);
        for (int i = (*MinHeap)->Vect->Count / 2; i >= 0; i--)
        {
            Heapify(*MinHeap, i, myFunction((*MinHeap)));
        }
    }
    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }
    VecDestroy(&(*Heap)->Vect);
    free(*Heap);
    *Heap = NULL;
    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    if (NULL == Heap)
    {
        return -1;
    }    

    int value = VecInsertTail(Heap->Vect, Value);

    if (-1 == value)
    {
        return -1;
    }
    Heapify(Heap, Parent(Heap->Vect->Count - 1), myFunction(Heap));

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    if (NULL == Heap)
    {
        return -1;
    }
    for (int i = 0; i < Heap->Vect->Count; i++)
    {
        if (Heap->Vect->Array[i] == Value)
        {
            Swap(&Heap->Vect->Array[i], &Heap->Vect->Array[Heap->Vect->Count - 1]);
            Heap->Vect->Count--;
            Heapify(Heap, Parent(i), myFunction(Heap));
            Heapify(Heap, Left(i), myFunction(Heap));
            Heapify(Heap, Right(i), myFunction(Heap));
            Heapify(Heap, i, myFunction(Heap));
            i--; 
        }
    }
    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    if (NULL == Heap)
    {
        return -1;
    }

    if (NULL == ExtremeValue)
    {
        return -1;
    }
    *ExtremeValue = Heap->Vect->Array[0];
    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    if (NULL == Heap)
    {
        return -1;
    }

    if (NULL == ExtremeValue)
    {
        return -1;
    }
    *ExtremeValue = Heap->Vect->Array[0];
    HpRemove(Heap, Heap->Vect->Array[0]);
    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    return Heap->Vect->Count;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    if (NULL == Heap)
    {
        return -1;
    }

    if (NULL == Heap)
    {
        return -1;
    }
    while (Heap->Vect->Count)
    {
        int value;
        HpPopExtreme(Heap, &value);
        if (Heap->Type == 0)
        {
            VecInsertHead(SortedVector, value);
        }
        else
        {
            VecInsertTail(SortedVector, value);
        }
    }
    return 0;
}
