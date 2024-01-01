#ifndef CHAR_ITR_H
#define CHAR_ITR_H

#include <stdbool.h>
#include <stdlib.h>

#include "Str.h"

typedef struct CharItr {
    const char *cursor;
    const char *sentinel;
} CharItr;



CharItr CharItr_value(const char *start, size_t length);
//Returns a pointer to the current character location of the iterator's cursor.
const char *CharItr_cursor(const CharItr *self);
//Returns true when there are additional characters to consume in the iteratable range.
bool CharItr_has_next(const CharItr *self);
//peek and return the next character. Do nut advance the iterator's cursor.
//will crash with out of bounds error if no more characters to consume.

char CharItr_peek(const CharItr *self);

//Read next character and advance iterator's cursor.
//Will crash with out of bounds error if no more characters to consume.

char CharItr_next(CharItr *self);

#endif