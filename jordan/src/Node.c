#include <stdlib.h>

#include "../include/Node.h"
#include "../include/Guards.h"

Node* CharNode_new(char c)
{
    Node* node = malloc(sizeof(Node));
    node->type = CHAR_NODE;
    node->data.value = c;
    return node;
};

Node* PairNode_new(Node *left, Node *right)
{
    Node* node = malloc(sizeof(Node));
    node->type = PAIR_NODE;
    node->data.pair.left = left;
    node->data.pair.right = right;
    return node;
}

Node* ErrorNode_new(const char *msg)
{
    Node* node = malloc(sizeof(Node));
    node->type = ERROR_NODE;
    node->data.error = msg;
    return node;
}
//ai
void* Node_drop(Node *self)
{
    if(self->type == PAIR_NODE){
        Node_drop(self->data.pair.left);
        Node_drop(self->data.pair.right);
    }
    free(self);
    return NULL;
}
