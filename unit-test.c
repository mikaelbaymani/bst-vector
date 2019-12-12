#include <stdio.h>
#include <assert.h>
#include "bst-vector.h"

void test_nullptr();
void test_create_vector();
void test_insert();
void test_contains();
void test_length();
void test_norm2();
void test_zero_size();
void test_copy();

int main(int argc, char * argv[]) {
  printf("Starting tests!\n");

  test_nullptr();
  test_create_vector();
  test_insert();
  test_contains();
  test_length();
  test_norm2();
  test_zero_size();
  test_copy();

  printf("Tests complete.\n");
  return 0;
}

void print_list(double value, void * _) {
  printf("%.0f, ", value);
}

void test_nullptr() {
  bool isOK;

  printf("Testing nullptr...\n");
  isOK = bSTVectorPut(NULL, 0, 1);
  assert(isOK != true);
}

void test_create_vector() {
  BSTVector * vector = NULL;

  printf("Testing create()...\n");
  vector = bSTVectorCreate(1);
  assert(vector != NULL);
  bSTVectorFree(&vector);
  assert(vector == NULL);
}

void test_insert() {
  bool isOK;
  BSTVector * vector = bSTVectorCreate(100);

  printf("Testing insert()...\n");
  isOK = bSTVectorPut(vector, 0, 1);
  assert(isOK != false);
  isOK = bSTVectorPut(vector, 50, 2);
  assert(isOK != false);
  isOK = bSTVectorPut(vector, 99, 3);
  assert(isOK != false);
  isOK = bSTVectorPut(vector, 99, 0);
  assert(isOK != false);
  isOK = bSTVectorPut(vector, 100, 4);
  assert(isOK != true);
  bSTVectorIterator(vector, print_list, NULL);
  printf("\n");
  bSTVectorFree(&vector);
  isOK = bSTVectorPut(vector, 0, 9);
  assert(isOK != true);
}

void test_contains() {
  BSTVector * vector = bSTVectorCreate(4);

  printf("Testing constains()...\n");
  (void)bSTVectorPut(vector, 0, 99);
  (void)bSTVectorPut(vector, 1, 98);
  (void)bSTVectorPut(vector, 2, 97);
  (void)bSTVectorPut(vector, 3, 96);
  assert(bSTVectorGet(vector, 0) == 99 &&
         bSTVectorGet(vector, 1) == 98 &&
         bSTVectorGet(vector, 2) == 97 &&
         bSTVectorGet(vector, 3) == 96 &&
         bSTVectorGet(vector, 4) == 0);
  bSTVectorIterator(vector, print_list, NULL);
  printf("\n");
  bSTVectorFree(&vector);
}

void test_length() {
  BSTVector * vector = bSTVectorCreate(42);

  printf("Testing size()...\n");
  assert(bSTVectorSize(vector) == 42);
  bSTVectorFree(&vector);
}

void test_norm2() {
  double norm2;
  BSTVector * vector = bSTVectorCreate(4);

  printf("Testing norm2()...\n");
  (void)bSTVectorPut(vector, 0, 0);
  (void)bSTVectorPut(vector, 1, 0);
  (void)bSTVectorPut(vector, 2, 3);
  (void)bSTVectorPut(vector, 3, 4);
  norm2 = bSTVectorNorm2(vector);
  assert(norm2 == 25);
  (void)bSTVectorPut(vector, 0, 1);
  norm2 = bSTVectorNorm2(vector);
  assert(norm2 == 26);
  bSTVectorIterator(vector, print_list, NULL);
  printf("\n");
  bSTVectorFree(&vector);
}

void test_zero_size() {
  bool isOK;
  BSTVector * vector = bSTVectorCreate(0);

  printf("Testing size zero...\n");
  isOK = bSTVectorPut(vector, 0, 1);
  assert(isOK != false);
  isOK = bSTVectorPut(vector, 1, 2);
  assert(isOK != true);
  bSTVectorIterator(vector, print_list, NULL);
  printf("\n");
  bSTVectorFree(&vector);
}

void test_copy() {
  bool isOK;
  BSTVector * vector = bSTVectorCreate(10);
  BSTVector * copy_of_vector = NULL;

  printf("Testing copy()...\n");
  isOK = bSTVectorPut(vector, 0, 1);
  isOK = bSTVectorPut(vector, 1, 2);
  isOK = bSTVectorPut(vector, 2, 3);
  isOK = bSTVectorPut(vector, 3, 4);
  isOK = bSTVectorPut(vector, 4, 5);
  isOK = bSTVectorPut(vector, 5, 6);
  isOK = bSTVectorPut(vector, 6, 7);
  isOK = bSTVectorPut(vector, 7, 8);
  isOK = bSTVectorPut(vector, 8, 9);
  isOK = bSTVectorPut(vector, 9, 10);
  isOK = bSTVectorCopy(NULL, vector);
  assert(isOK != true);
  isOK = bSTVectorCopy(&copy_of_vector, NULL);
  assert(isOK != true);
  isOK = bSTVectorCopy(&vector, vector);
  assert(isOK != true);
  isOK = bSTVectorCopy(&copy_of_vector, vector);
  assert(isOK != false && bSTVectorSize(copy_of_vector) == 10);
  isOK = bSTVectorPut(vector, 9, 11);
  isOK = bSTVectorCopy(&copy_of_vector, vector);
  assert(isOK != false && bSTVectorSize(copy_of_vector) == 10);
  bSTVectorIterator(vector, print_list, NULL);
  printf("\n");
  bSTVectorIterator(copy_of_vector, print_list, NULL);
  printf("\n");
  bSTVectorFree(&vector);
  bSTVectorFree(&copy_of_vector);
  assert(vector == NULL);
  assert(copy_of_vector == NULL);
}
