#include <stdlib.h>

#include "../include/Node.h"
#include "../include/Guards.h"

Node* CommandNode_new(char *command)
{
    Node* node = malloc(sizeof(Node));
    node->type = COMMAND_NODE;
    node->data.command = command;
    return node;
};

Node* PipeNode_new(Node *left, Node *right)
{
    Node* node = malloc(sizeof(Node));
    node->type = PIPE_NODE;
    node->data.pipe.left = left;
    node->data.pipe.right = right;
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
    if(self->type == PIPE_NODE){
        Node_drop(self->data.pipe.left);
        Node_drop(self->data.pipe.right);
    }
    free(self);
    return NULL;
}
