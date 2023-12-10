#pragma once

#include "../bsa.h"

typedef struct bsaNode {
    int index;
    int data;
    struct bsaNode* next;
} bsaNode;

struct bsa{
    bsaNode* head;
};
