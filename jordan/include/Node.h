#ifndef NODE_H
#define NODE_H

#include "Str.h"
#include "StrVec.h"

typedef enum NodeType {
    ERROR_NODE = -1,
    COMMAND_NODE = 0,
    PIPE_NODE = 1,
} NodeType;

typedef struct Node Node; // forward declaration
typedef const char* ErrorValue;

typedef struct PipeValue {
    Node *left;
    Node *right;
} PipeValue;

typedef char* CommandValue;


typedef union {
    PipeValue pipe;
    CommandValue command;
    ErrorValue error;
} NodeValue;

struct Node {
    NodeType type;
    NodeValue data;
};

Node* CommandNode_new(char *command);
Node* PipeNode_new(Node *left, Node *right);
Node* ErrorNode_new(const char *msg);
void* Node_drop(Node *self);

#endif