#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Str.h"
#include "../include/Scanner.h"
#include "../include/Parser.h"
#include "../include/Exec.h"

#define BUFF_SIZE 80

size_t read(Str *line, FILE *stream);
Node* eval(Str *input);
void print(Node *node, size_t indention);

int main()
{
    Str line = Str_value(BUFF_SIZE);
    while (read(&line, stdin))
    {
        Node *parse_tree = eval(&line);
        exec(parse_tree);
        Node_drop(parse_tree);
    }
    Str_drop(&line);
    return EXIT_SUCCESS;
}

size_t read(Str *line, FILE *stream)
{
    printf("thsh> ");

    Str_splice(line, 0, Str_length(line), NULL, 0);
    size_t length = 0;
    char *buffer = Str_ref(line, 0);
    if (fgets(buffer, BUFF_SIZE, stream) != NULL)
    {
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
        {
            buffer[length - 1] = '\0';
            length -= 1;
        }
    }
    return length;
}