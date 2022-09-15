#include <stdbool.h>
#include "fsm_utils.h"

/*
    if curr : symbol Or (
    if prev : symbol Or ) Or unary Operator [*, +, ?]
    then insert dot before curr
*/

static bool
is_symbol(char curr)
{
     if ( (curr >= 65 && curr <= 90) ||
           (curr >= 97 && curr <= 122) ||
           (curr >= 48 && curr <= 57) ) {
        return true;
    }
    return false;
}

char *
infix_to_postfix(char *string, int str_len, int *new_len) {

    *new_len = str_len;
    return string;
}

int 
string_insert_dots(char *str, int str_len, char *out_str) {

}