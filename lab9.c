/*
Mariam Befekadu
COP 3502
Lab Assignment 9
*/

#include <stdio.h>
#include <stdlib.h>

struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

//Combined a structure for Node and HashType
struct HashNode {
    struct RecordType record;
    struct HashNode* next;
};

// Compute the hash function
int hash(int x)
{
    return x % 10; //Adjusts 10 as needed based on the size of the array
}

void insertRecord(struct HashNode* hashArray[], struct RecordType record)
{
    int index = hash(record.id);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->record = record;
    newNode->next = hashArray[index];
    hashArray[index] = newNode;
}

void displayRecordsInHash(struct HashNode* hashArray[], int hashSz)
{
    printf("\nRecords in Hash Structure:\n");
    for (int i = 0; i < hashSz; ++i) {
        printf("Index %d: ", i);
        struct HashNode* current = hashArray[i];
        while (current != NULL) {
            printf("(%d, %c, %d) -> ", current->record.id, current->record.name, current->record.order);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

// parses input file to an array of records
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    const int HASH_SIZE = 10;

    struct HashNode* hashTable[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; ++i) {
        hashTable[i] = NULL;
    }
    
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(hashTable, pRecords[i]);
    }

    displayRecordsInHash(hashTable, HASH_SIZE);

    free(pRecords);

    return 0;
}
