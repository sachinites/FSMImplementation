#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"
#include "std_fsm.h"

int
main(int argc, char **arg) {

    /* Let us build and test the composite NFA for reg ex (a|b)*c
        Algorithm :
        1. Build NFA for a
            fsm_a = q0a(i)-----a---->q1a(f)
        2. Build NFA for b
            fsm_b = q0b(i)-----b---->q1b(f)
        3. fsm_a_or_b = fsm_union(fsm_a, fsm_b);
            Accepts : a | b
        4. fsm_a_or_b_star = fsm_closure(fsm_a_or_b);
            Accepts : (a | b)*
        5. Build NFA for c
            fsm_c = q0c(i)-----c---->q1c(f)
        6. fsm_a_or_b_star_concat   =   fsm_concat(fsm_a_or_b_star, fsm_c)
             Accepts : (a | b)*.c
             Let's go
    */
   char state_name[MAX_STATE_NAME_SIZE];
   
   fsm_t *fsm_a = create_new_fsm("a");
   /*
    1. Build NFA for a
            fsm_a = q0a(i)-----a---->q1a(f)
    */
   sprintf(state_name, "q.%s.q0", fsm_a->fsm_name);
   state_t *q0a = create_new_state(state_name, FSM_FALSE);
   sprintf(state_name, "q.%s.q1", fsm_a->fsm_name);
   state_t *q1a = create_new_state(state_name, FSM_TRUE);
   set_fsm_initial_state(fsm_a, q0a);
   set_fsm_final_state(fsm_a, q1a);
    /*
    2. Build NFA for b
            fsm_b = q0b(i)-----b---->q1b(f)
    */
   fsm_t *fsm_b = create_new_fsm("b");
   sprintf(state_name, "q.%s.q0", fsm_b->fsm_name);
   state_t *q0b = create_new_state(state_name, FSM_FALSE);
   sprintf(state_name, "q.%s.q1", fsm_b->fsm_name);
   state_t *q1b = create_new_state(state_name, FSM_TRUE);
   set_fsm_initial_state(fsm_b, q0b);
   set_fsm_final_state(fsm_b, q1b);

   /*
    3. fsm_a_or_b = fsm_union(fsm_a, fsm_b);
            Accepts : a | b
   */
  fsm_t *fsm_a_or_b = fsm_union(fsm_a, fsm_b);
  
  /*
  4. fsm_a_or_b_star = fsm_closure(fsm_a_or_b);
            Accepts : (a | b)*
*/
fsm_t *fsm_a_or_b_star = fsm_closure(fsm_a_or_b);

/*
5. Build NFA for c
            fsm_c = q0c(i)-----c---->q1c(f)
*/
   fsm_t *fsm_c = create_new_fsm("c");
   sprintf(state_name, "q.%s.q0", fsm_c->fsm_name);
   state_t *q0c = create_new_state(state_name, FSM_FALSE);
   sprintf(state_name, "q.%s.q1", fsm_c->fsm_name);
   state_t *q1c = create_new_state(state_name, FSM_TRUE);
   set_fsm_initial_state(fsm_c, q0c);
   set_fsm_final_state(fsm_c, q1c);

    /*
    fsm_a_or_b_star_concat   =   fsm_concat(fsm_a_or_b_star, fsm_c)
             Accepts : (a | b)*.c
    */

   fsm_t *fsm_a_or_b_star_concat   =   fsm_concat(fsm_a_or_b_star, fsm_c);

   fsm_print(fsm_a_or_b_star_concat);
   return 0;
}