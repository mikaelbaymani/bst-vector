#include <stdlib.h>
#include "bst-vector.h"

struct BSTVector {
  unsigned dim;
  bool is_leaf;
  double value;
  double norm2;
  struct BSTVector * left;
  struct BSTVector * right;
};

BSTVector * bSTVectorCreate(unsigned dim) {
  // assume malloc always succeeds
  BSTVector * obj = malloc(sizeof *obj);
  obj->dim = dim==0 ? 1 : dim;
  obj->is_leaf = dim <= 1;
  obj->value = obj->norm2 = 0.0;
  obj->left = obj->right = NULL;
  return obj;
}

PRIVATE BSTVector * makeEmpty(BSTVector * obj) {
  if (obj != NULL) {
    makeEmpty(obj->left);
    makeEmpty(obj->right);
    free(obj);
  }
  return NULL;
}

void bSTVectorFree(BSTVector ** obj) {
  *obj = makeEmpty(*obj);
}

PRIVATE void updateNorm2(BSTVector * obj) {
  obj->norm2 = obj->left ? obj->left->norm2 : 0.0;
  obj->norm2 += obj->right ? obj->right->norm2 : 0.0;
}

bool bSTVectorPut(BSTVector * obj, unsigned index, double value) {
  if (obj == NULL || index >= obj->dim) {
    return false;
  }

  if (obj->is_leaf) {
    obj->value = value;
    obj->norm2 = value * value;
    return true;
  }

  BSTVector ** child = NULL;
  unsigned child_size;
  unsigned child_index;
  unsigned cutoff = obj->dim / 2;

  if (index < cutoff) {
    child = &obj->left;
    child_size = cutoff;
    child_index = index;
  }
  else {
    child = &obj->right;
    child_size = obj->dim - cutoff;
    child_index = index - cutoff;
  }

  if (*child == NULL) {
    *child = bSTVectorCreate(child_size);
  }

  bool isOK = bSTVectorPut(*child, child_index, value);
  if ((*child)->norm2 == 0.0) {
    free(*child);
    *child = NULL;
  }

  updateNorm2(obj);
  return isOK;
}

double bSTVectorGet(BSTVector * obj, unsigned index) {
  if (obj == NULL || index >= obj->dim) {
    return 0.0;
  }

  if (obj->is_leaf) {
    return obj->value;
  }

  BSTVector ** child = NULL;
  unsigned child_index;
  unsigned cutoff = obj->dim / 2;

  if (index < cutoff) {
    child = &obj->left;
    child_index = index;
  }
  else {
    child = &obj->right;
    child_index = index - cutoff;
  }

  if (*child == NULL) {
    return 0.0;
  }

  return bSTVectorGet(*child, child_index);
}

PRIVATE BSTVector* copy(BSTVector * other) {
  if (other == NULL) {
    return NULL;
  }
  // assume malloc always succeeds
  BSTVector * this = malloc(sizeof *this);
  this->dim = other->dim;
  this->is_leaf = other->is_leaf;
  this->value = other->value;
  this->norm2 = other->norm2;

  this->left = copy(other->left);
  this->right = copy(other->right);

  return this;
}

bool bSTVectorCopy(BSTVector ** this, BSTVector * other) {
  if (!this || !other || *this == other) {
    return false;
  }

  *this = makeEmpty(*this);
  *this = copy(other);
  return true;
}

double bSTVectorNorm2(BSTVector * obj) {
  if (obj == NULL) {
    return 0.0;
  }
  return obj->norm2;
}

unsigned bSTVectorSize(BSTVector * obj) {
  if (obj == NULL) {
    return 0;
  }
  return obj->dim;
}

void bSTVectorIterator(BSTVector * obj, Iterator iterator, void * token) {
  if (obj == NULL)
    return;
  {
    bSTVectorIterator(obj->left, iterator, token);
    if (obj->is_leaf) {
      iterator(obj->value, token);
    }
    bSTVectorIterator(obj->right, iterator, token);
  }
}
