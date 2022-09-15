#include <string.h>
#include "fsm.h"

int
main(int argc, char **argv) {

    char str[32];
    memset(str, 0, sizeof(str));
    strncpy(str, "ab|*c.\0", strlen("ab|*c.\0") + 1);
    //strcpy(str, "ab|*c.\0");
    fsm_t *fsm = fsm_nfa_construction(str, strlen(str));
    return 0;
}