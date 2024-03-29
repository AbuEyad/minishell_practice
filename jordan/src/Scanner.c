#include <ctype.h>
#include <stdio.h>
#include "../include/Scanner.h"
#include "../include/Str.h"
#include "../include/CharItr.h"

char nullChar = '\0';
CharItr nextChar;

static Token token_parser(CharItr *char_itr);

Scanner Scanner_value(CharItr char_itr)
{
    Token FirstTok = token_parser(&char_itr);
    Token next = {
        FirstTok.type, 
        FirstTok.lexeme
    };
    Scanner itr = {
        char_itr,
        next
    };
    return itr;
}

bool Scanner_has_next(const Scanner *self)
{   
    return self->next.type != END_TOKEN;   //if (self->next.lexeme.buffer != '\0') {

}

Token Scanner_peek(const Scanner *self)
{
    return self->next; 
}

static Token token_parser(CharItr *char_itr) 
{
    char peekVal;    
     
    if (CharItr_has_next(char_itr)) {
        peekVal = CharItr_peek(char_itr);
        // printf(" \n peekVal: %d", peekVal);
        while (CharItr_has_next(char_itr) && (peekVal == ' ' | peekVal == '\t')) {
            CharItr_next(char_itr); 
            if (CharItr_has_next(char_itr)) {
                
                peekVal = CharItr_peek(char_itr); 
            }
       }
        if (peekVal == '|') {     
           Token nextTok = {PIPE_TOKEN, Str_from("|")}; 
           CharItr_next(char_itr); 
           while(CharItr_has_next(char_itr) && ((CharItr_peek(char_itr) == ' ') || (CharItr_peek(char_itr) == '\t'))) {
                CharItr_next(char_itr);
           } 
           return nextTok; 
        } else if(peekVal == (nullChar | EOF)){ 
            Token nextTok = {END_TOKEN, Str_from("")};
            return nextTok;
        } else { 
           char c; 
           size_t count = 0; 
           Str s = Str_value(sizeof(char));// Str_from(char_itr->cursor);
          // printf(" \n before while"); 
           while(CharItr_has_next(char_itr) && (CharItr_peek(char_itr) != ' ')){ 
                   c = CharItr_next(char_itr);
                    Str_set(&s, count, c);    
                    count++;     
           }
           while(CharItr_has_next(char_itr) && ((CharItr_peek(char_itr) == ' ') || (CharItr_peek(char_itr) == '\t'))) {
                CharItr_next(char_itr);
           } 
           // printf("\n past while");
            Token nextTok = {COMMAND_TOKEN, s};
            return nextTok;
        }
    } else { 
            Token nextTok = {END_TOKEN, Str_from("")};
            Str_drop(&nextTok.lexeme);
            return nextTok;
    }
 } 


Token Scanner_next(Scanner *self) 
{ 
    Token t = self->next;
    self->next = token_parser(&self->char_itr);     
    //Str_drop(&self->next.lexeme);
    return t;               
}