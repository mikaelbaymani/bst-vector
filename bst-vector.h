#ifndef BSTVECTOR_H
#define BSTVECTOR_H
#define PRIVATE static
#include <stdbool.h>

typedef struct BSTVector BSTVector;
typedef void (*Iterator)(double value, void * token);

BSTVector * bSTVectorCreate(unsigned dim);
void bSTVectorFree(BSTVector ** obj);
bool bSTVectorPut(BSTVector * obj, unsigned index, double value);
double bSTVectorGet(BSTVector * obj, unsigned index);
bool bSTVectorCopy(BSTVector ** this, BSTVector * other);
double bSTVectorNorm2(BSTVector * obj);
unsigned bSTVectorSize(BSTVector * obj);
void bSTVectorIterator(BSTVector * obj, Iterator iterator, void * token);

#endif//BSTVECTOR_H
