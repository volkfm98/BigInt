#include <iostream>

#include "BigInt.h"

//Begin of BigIntChunk part
int BigIntChunk::digitCount() {
    int count = 0;

    long long num = this->val;

    if (num == 0) {
      ++count;
    }

    while (num > 0) {
        ++count;
        num /= 10;
    }

    return count;
}

BigIntChunk::BigIntChunk(): next(NULL), prev(NULL) {}

BigIntChunk::BigIntChunk(const long long &b): val(b), next(NULL), prev(NULL) {}

BigIntChunk BigIntChunk::operator= (const BigIntChunk &b) {
    this->val = b.val;

    return *(this);
}

BigIntChunk BigIntChunk::operator= (const long long &b) {
    this->val = b;

    return *(this);
}

long long BigIntChunk::operator+ (const BigIntChunk &b) {
    long long retVal;

    this->val += b.val;
    retVal = this->val / MAX_CHUNK_VALUE;
    this->val %= MAX_CHUNK_VALUE;

    return retVal;
}

void BigIntChunk::addRemainder(const long long &b) {
    this->val += b;
}

long long BigIntChunk::operator* (const BigIntChunk &b) {
    long long retVal;

    this->val *= b.val;
    retVal = this->val / MAX_CHUNK_VALUE;
    this->val %= MAX_CHUNK_VALUE;

    return retVal;
}

void BigIntChunk::write() {
    std::cout << (this->val);
}
//End of BigIntChunk part
//Begin of BigInt part
void BigInt::extend() {
    BigIntChunk *newPart = new BigIntChunk();

    if (this->begin != NULL) {
        (this->begin)->prev = newPart;
        newPart->next = this->begin;
    }

    this->begin = newPart;

    if (this->end == NULL) {
        this->end = newPart;
    }
}

BigInt::BigInt(): begin(NULL), end(NULL) {
    extend();
}

BigInt::BigInt(const long long &a) {
    extend();

    *(this->end) = a;
    this->begin = this->end;
}

BigInt BigInt::operator= (const BigInt &b) {
    BigIntChunk *bPtr = b.end, *thisPtr = this->end;

    for (; bPtr != (b.begin)->prev; bPtr = bPtr->prev, thisPtr = thisPtr->prev) {
        if (thisPtr == NULL) {
            this->extend();
            thisPtr = this->begin;
        }

        *thisPtr = *bPtr;
    }

    if (thisPtr != NULL) {
        this->begin = thisPtr->next;
    }

    return *(this);
}

BigInt BigInt::operator= (const long long &b) {
    if (this->end == NULL) {
        this->extend();
    }

    *(this->end) = b;
    this->begin = this->end;

    return *(this);
}

BigInt BigInt::operator+ (const BigInt &b) {
    BigInt *res = new BigInt;
    *res = *this;
    BigIntChunk *resPtr = this->end, *bPtr = b.end;

    long long remainder = 0;

    for (; bPtr != (b.begin)->prev; resPtr = resPtr->prev, bPtr = bPtr->prev) {
        if (resPtr == NULL) {
            res->extend();
            resPtr = res->begin;
        }

        resPtr->addRemainder(remainder);
        remainder = *resPtr + *bPtr;
    }

    if (remainder != 0) {
        if (resPtr == NULL) {
            res->extend();
            resPtr = res->begin;
        }

        resPtr->addRemainder(remainder);
    }

    if (resPtr != NULL) {
        this->begin = resPtr->next;
    }

    return *res;
}

/*BigInt BigInt::operator* (const BigInt &b) {
  BigInt *res = new BigInt;
  *res = *this;
  BigIntChunk *resPtr = this->end, *bPtr = b.end;

  long long remainder = 0;

  for (; bPtr != (b.begin)->prev; resPtr = resPtr->prev, bPtr = bPtr->prev) {
      if (resPtr == NULL) {
          res->extend();
          resPtr = res.begin;
      }

      resPtr->addRemainder(remainder);
      remainder = (*resPtr) * (*bPtr);
  }

  if (resPtr != NULL) {
      this->begin = resPtr->next;
  }

  return *res;
}*/

void BigInt::write() {
    (this->begin)->write();

    int cnt;

    for (BigIntChunk *thisPtr = (this->begin)->next; thisPtr != NULL; thisPtr = thisPtr->next) {
        cnt = MAX_DIGIT_COUNT - thisPtr->digitCount();

        for (int i = 0; i < cnt; ++i) {
            std::cout << '0';
        }

        thisPtr->write();
    }
}

BigInt::~BigInt() {
    BigIntChunk *tmp;
    for (BigIntChunk *thisPtr = (this->end); thisPtr != NULL; thisPtr = tmp) {
        tmp = thisPtr->prev;
        delete (thisPtr);
    }
}
//End of BigInt
