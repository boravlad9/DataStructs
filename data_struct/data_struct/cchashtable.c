#include "cchashtable.h"
#include "common.h"

unsigned int hashFunction(char* Index, int MaxSize)
{
    return ((unsigned int)Index * 13) % MaxSize;
}

int HtCreate(CC_HASH_TABLE **HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    *HashTable = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));
    if (NULL == *HashTable)
    {
        return -1;
    }
    (*HashTable)->MaxSize = 10007;
    (*HashTable)->ElementCount = 0;
    for (int i = 0; i < (*HashTable)->MaxSize; i++)
    {
        (*HashTable)->Vect[i] = NULL;
        int value = TreeCreate(&(*HashTable)->Vect[i]);
        if (-1 == value)
        {
            for (int j = 0; j < i; j++)
            {
                TreeDestroy(&(*HashTable)->Vect[j]);
                free(*HashTable);
            }
            return -1;
        }
    }
    return 0;
}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    for (int i = 0; i < (*HashTable)->MaxSize; i++)
    {
        TreeDestroy(&(*HashTable)->Vect[i]);
    }
    free(*HashTable);
    *HashTable = NULL;
    return 0;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    
    int place = hashFunction(Key, HashTable->MaxSize);
    if (1 == TreeContains(HashTable->Vect[place], (int)Key))
    {
        return -1;
    }
    HashTable->ElementCount++;
    TreeInsertGeneral(HashTable->Vect[place], Value, (int)Key);
    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    if (NULL == Value)
    {
        return -1;
    }
    
    int place = hashFunction(Key, HashTable->MaxSize);
    if (TreeGetValueByKey(HashTable->Vect[place], (int)Key, Value) == -1)
    {
        return -1;
    }
    return 0;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    int place = hashFunction(Key, HashTable->MaxSize);
    if (-1 == TreeRemoveGeneral(HashTable->Vect[place], (int)Key))
    {
        return -1;
    }

    HashTable->ElementCount--;
    return 0;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    int place = hashFunction(Key, HashTable->MaxSize);
    if (TreeContains(HashTable->Vect[place], (int)Key) == 1)
    {
        return 1;
    }
    return 0;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = NULL;


    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    iterator->CurrentTree = 0;
    iterator->CurrentElement = 0;
    
    *Iterator = iterator;

    // FIND THE FIRST KEY AND SET Key
    int value = HtGetNextKey(*Iterator, Key);
    return value;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    if (NULL == Iterator)
    {
        return -1;
    }

    if (NULL == Key)
    {
        return -1;
    }

    while (TreeGetCount(Iterator->HashTable->Vect[Iterator->CurrentTree]) <= Iterator->CurrentElement)
    {
        Iterator->CurrentElement = 0;
        Iterator->CurrentTree++;
        if (Iterator->CurrentTree > Iterator->HashTable->MaxSize)
        {
            return -2;
        }
    }

    int value = 0;
    TreeGetNthInorder(Iterator->HashTable->Vect[Iterator->CurrentTree], Iterator->CurrentElement, &value);
    Iterator->CurrentElement++;
    *Key = (char*)value;
    return 0;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
    if (NULL == Iterator)
    {
        return -1;
    }
    free(*Iterator);
    *Iterator = NULL;
    return 0;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }
    HashTable->ElementCount = 0;
    for (int i = 0; i < HashTable->MaxSize; i++)
    {
        TreeClear(HashTable->Vect[i]);
    }
    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    return HashTable->ElementCount;
}
