#ifndef TOKEN_ITR_H
#define TOKEN_ITR_H

#include <stdbool.h>

#include "CharItr.h"
#include "Token.h"

typedef struct Scanner {
    CharItr char_itr;
    char next; // In a real scanner, this would be a Token
} Scanner;

Scanner Scanner_value(CharItr char_itr);

bool Scanner_has_Next(const Scanner *self);

Token Scanner_peek(const Scanner *self);

Token Scanner_next(Scanner *self);

#endif