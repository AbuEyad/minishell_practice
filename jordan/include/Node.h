#ifndef NODE_H
#define NODE_H

#include "Str.h"
#include "StrVec.h"

typedef enum NodeType {
    ERROR_NODE = -1,
    COMMAND_NODE = 0,
    PAIR_NODE = 1,
} NodeType;

typedef struct Node Node; // forward declaration
typedef const char* ErrorValue;

typedef struct PairValue {
    Node *left;
    Node *right;
} PairValue;

typedef char CharValue;


typedef union {
    PairValue pair;
    CharValue command;
    ErrorValue error;
} NodeValue;

struct Node {
    NodeType type;
    NodeValue data;
};

Node* CharNode_new(char c);
Node* PairNode_new(Node *left, Node *right);
Node* ErrorNode_new(const char *msg);
void* Node_drop(Node *self);

#endif