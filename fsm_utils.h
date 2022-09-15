#ifndef __FSM_UTILS__
#define __FSM_UTILS__

int 
string_insert_dots(char *str, int str_len, char *out_str);

char *
infix_to_postfix(char *string, int str_len, int *new_len);

#endif /* __FSM_UTILS__ */