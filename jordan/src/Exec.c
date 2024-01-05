#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/Exec.h"


#define FORKED_CHILD 0

static void exec_command(Node *node)
{
    printf("Todo");
}

void exec(Node *node)
{
    switch (node->type)
    {
        case COMMAND_NODE:
            exec_command(node);
            break;
        default:
            printf("Todo");
            break;
    }
}

static void exec_command(Node *node)
{
    if (fork() == FORKED_CHILD)
    {
      StrVec *words = &node->data.command;
      size_t argc = StrVec_length(words);
      char *argv[argc + 1];
      argv[argc] = NULL;
      for (size_t i = 0; i < argc; i++)
      {
        Str *word = StrVec_ref(words, i);
        argv[i] = Str_ref(word, 0);
        }
      execvp(argv[0], argv);
    }
    wait(NULL);

}