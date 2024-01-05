#include "../include/Parser.h"
#include "../include/Token.h"
#include "../include/Scanner.h"

// Grammar
// NODE         ::= CHAR_NODE | PAIR_NODE
// CHAR_NODE    ::= CHAR_TOKEN
// PAIR_NODE    ::= LPAREN_TOKEN NODE SPACE_TOKEN NODE RPAREN_TOKEN

static Node* parse_pair(Scanner *scanner);
static Node* parse_char(Scanner *scanner);

// NODE         ::= CHAR_NODE | PAIR_NODE
Node* parse(Scanner *scanner){
    Token token = Scanner_peek(scanner);
    switch (token.type){
        case CHAR_TOKEN:
            return parse_char(scanner);
        case LPAREN_TOKEN:
            return parse_pair(scanner);
        default:
            return ErrorNode_new("Expected ( or a Char");
    }
}


// CHAR_NODE    ::= CHAR_TOKEN
static Node* parse_char(Scanner *scanner){
    Token next = Scanner_next(scanner);
    return CharNode_new(next.lexeme);
}

// PAIR_NODE    ::= LPAREN_TOKEN NODE SPACE_TOKEN NODE RPAREN_TOKEN
static Node* parse_pair(Scanner *scanner){
    Token next = Scanner_next(scanner);
    Node *left = parse(scanner);
    next = Scanner_next(scanner);// consume SPACE_TOKEN, trust no error check
    Node *right = parse(scanner);
    next = Scanner_next(scanner);// consume RPAREN_TOKEN, trust no error check here
    return PairNode_new(left, right);
}