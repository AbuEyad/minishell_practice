#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/Exec.h"


#define FORKED_CHILD 0

typedef struct Context
{
    int fd[2]; // for stdin and stdout
    int fd_close; // close and fd? -1 if not
} Context;

static int exec_node(Node *node, Context *ctx);
static int exec_command(Node *node, Context *ctx);
static int exec_pipe(Node *node, Context *ctx);


void exec(Node *node)
{
    Context ctx = {
        {
            STDIN_FILENO,
            STDOUT_FILENO
        },
        -1
    };
    int children = exec_node(node, &ctx);
    for (int i = 0; i < children; i++)
    {
        wait(NULL);
    }
}
static int exec_node(Node *node, Context *ctx)
{
    switch (node->type)
    {
        case COMMAND_NODE:
            return exec_command(node, ctx);
        case PIPE_NODE:
            return exec_pipe(node, ctx);
        default:
            return 0;
    }

}
static int exec_pipe(Node *node, Context *ctx)
{
    //todo establish pipe
    int p[2];
    pipe(p); // p_read  p[0]
    //          p_write p[1]
    int children = 0;

    Node *lhs = node->data.pipe.left;
    Context lhs_ctx = *ctx;
    lhs_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    lhs_ctx.fd_close = p[STDIN_FILENO];
    children += exec_node(lhs, &lhs_ctx);

    Node *rhs = node->data.pipe.right;
    Context rhs_ctx = *ctx;
    rhs_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    rhs_ctx.fd_close = p[STDOUT_FILENO];
    children += exec_node(rhs, &rhs_ctx);

    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return children;
}

static int exec_command(Node *node, Context *ctx)
{
    if (fork() == FORKED_CHILD)
    {
        dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
        dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
        if (ctx->fd_close != -1)
        {
            close(ctx->fd_close);
        }

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
    return 1;
}
