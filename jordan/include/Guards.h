#ifndef CHAR_ITR_H
#define CHAR_ITR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct CharItr {
    const char *cursor;
    const char *sentinel;
} CharItr;

CharItr CharItr_value(const char *start, size_t length);

const char *CharItr_cursor(const CharItr *self);

bool CharItr_has_Next(const CharItr *self);

char CharItr_peek(const CharItr *self);

char CharItr_next(CharItr *self);

#endif 