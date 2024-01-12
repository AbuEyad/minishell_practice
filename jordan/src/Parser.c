#include "../include/Parser.h"
#include "../include/Token.h"
#include "../include/Scanner.h"
#include <string.h>

// Grammar
// NODE          ::= COMMAND_NODE | PIPE_NODE
// COMMAND_NODE  ::= CHAR*_TOKEN
// PIPE_NODE     ::= CHAR * PIPE CHAR *

static Node* parse_pipe(Scanner *scanner);
static Node* parse_command(Scanner *scanner);

// NODE         ::= COMMAND_NODE | PIPE_NODE
Node* parse(Scanner *scanner){
    Token token = Scanner_peek(scanner);
    switch (token.type){
        case COMMAND_TOKEN:
            return parse_command(scanner);
        case PIPE_TOKEN:
            return parse_pipe(scanner);
        default:
            return ErrorNode_new("Expected ( or a Char");
    }
}

static Node* parse_pipe(Scanner *scanner){
    Token next = Scanner_next(scanner);
    Node *left = parse_command(scanner);
    next = Scanner_next(scanner);// consume SPACE_TOKEN, trust no error check
    Node *right = parse_command(scanner);
    return PipeNode_new(left, right);
}

static Node* parse_command(Scanner *scanner){
    Token next = Scanner_next(scanner);
    if (next.type == COMMAND_TOKEN){
        char* command = strdup(next.lexeme.buffer); // Convert Str to const char*
        return CommandNode_new(command);
    } else {
        return ErrorNode_new("Expected a Command");
    }
}

// // CHAR_NODE    ::= CHAR_TOKEN
// static Node* parse_char(Scanner *scanner){
//     Token next = Scanner_next(scanner);
//     return CharNode_new(next.lexeme);
// }

// PAIR_NODE    ::= LPAREN_TOKEN NODE SPACE_TOKEN NODE RPAREN_TOKEN
// static Node* parse_pair(Scanner *scanner){
//     Token next = Scanner_next(scanner);
//     Node *left = parse(scanner);
//     next = Scanner_next(scanner);// consume SPACE_TOKEN, trust no error check
//     Node *right = parse(scanner);
//     next = Scanner_next(scanner);// consume RPAREN_TOKEN, trust no error check here
//     return PairNode_new(left, right);
// }