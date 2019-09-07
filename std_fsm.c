/*
 * =====================================================================================
 *
 *       Filename:  std_fsm.c
 *
 *    Description:  This file contains standard Finite state machines and Common Reader Functions Definitions
 *
 *        Version:  1.0
 *        Created:  Saturday 31 August 2019 09:02:13  IST
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  Er. Abhishek Sagar, Networking Developer (AS), sachinites@gmail.com
 *        Company:  Brocade Communications(Jul 2012- Mar 2016), Current : Juniper Networks(Apr 2017 - Present)
 *        
 *        This file is part of the FSMProject distribution (https://github.com/sachinites).
 *        Copyright (c) 2017 Abhishek Sagar.
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by  
 *        the Free Software Foundation, version 3.
 *
 *        This program is distributed in the hope that it will be useful, but 
 *        WITHOUT ANY WARRANTY; without even the implied warranty of 
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 *        General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License 
 *        along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * =====================================================================================
 */

#include "std_fsm.h"
#include <memory.h>
#include <assert.h>

fsm_bool_t
match_any_0_9_match_fn(char *data1,         /*Transition entry key, which will be empty buffer*/
                         unsigned int size, /*size shall be zero*/
                         char *data2,       /*Data from User Input*/
                         unsigned int *length_read){

    /*We are bothered only about user data 'data2'*/

    if(*data2 >= 48 && 
            *data2 <= 57){

        *length_read = 1;
        return FSM_TRUE;
    }

    return FSM_FALSE;
}

fsm_bool_t
match_any_a_z_match_fn(char *data1,       /*Transition entry key, which will be empty buffer*/
                       unsigned int size, /*size shall be zero*/
                       char *data2,       /*Data from User Input*/
                       unsigned int *length_read){

    /*We are bothered only about user data 'data2'*/

    if(*data2 >= 97 && 
            *data2 <= 122){

        *length_read = 1;
        return FSM_TRUE;
    }

    return FSM_FALSE;
}

fsm_bool_t
match_any_A_Z_match_fn(char *data1,       /*Transition entry key, which will be empty buffer*/
                       unsigned int size, /*size shall be zero*/
                       char *data2,       /*Data from User Input*/
                       unsigned int *length_read){

    /*We are bothered only about user data 'data2'*/

    if(*data2 >= 65 && 
            *data2 <= 90){

        *length_read = 1;
        return FSM_TRUE;
    }

    return FSM_FALSE;
}


fsm_bool_t
match_any_0_9_or_a_z_or_A_Z_match_fn(char *data1, unsigned int size,
                                     char *data2, unsigned int *length_read){

    return (match_any_0_9_match_fn(data1, size, data2, length_read) || 
            match_any_a_z_match_fn(data1, size, data2, length_read) ||
            match_any_A_Z_match_fn(data1, size, data2, length_read));

    /**length_read shall be set to 1 by callees*/
}

fsm_t *email_validator_fsm(){

    tt_entry_t *tt_entry = NULL;
    char transition_key[MAX_TRANSITION_KEY_SIZE];
    unsigned int transition_keysize = 0;

    fsm_t *fsm = create_new_fsm("Email Validator");

    /*No output required*/
    fsm_register_generic_transition_output_fn(fsm, 0);

/*DEAD_STATE*/
    state_t *DEAD_STATE = create_new_state(fsm, "D", FSM_FALSE);
    create_and_insert_new_tt_entry_wild_card(DEAD_STATE, DEAD_STATE, 0);

/*state_F*/
    state_t *state_F = create_new_state(fsm, "F", FSM_TRUE);
    create_and_insert_new_tt_entry_wild_card(state_F, DEAD_STATE, 0);

/*q6*/
    state_t *state_q6 = create_new_state(fsm, "q6", FSM_FALSE);

    transition_keysize = strlen("gmail.com");
    strncpy(transition_key, "gmail.com", transition_keysize);
    create_and_insert_new_tt_entry(&state_q6->state_trans_table,
                                   transition_key, transition_keysize, 0,
                                   state_F);

    transition_keysize = strlen("hotmail.com");
    strncpy(transition_key, "hotmail.com", transition_keysize);
    create_and_insert_new_tt_entry(&state_q6->state_trans_table,
                                   transition_key, transition_keysize, 0,
                                   state_F);
            
    create_and_insert_new_tt_entry_wild_card(state_q6, DEAD_STATE, 0);

/*q5*/
    state_t *state_q5 = create_new_state(fsm, "q5", FSM_FALSE);
    tt_entry = create_and_insert_new_tt_entry(&state_q5->state_trans_table,
                                   0, 0, 0,
                                   state_q5);

    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);

    transition_keysize = 1;
    transition_key[0] = '@';
    create_and_insert_new_tt_entry(&state_q5->state_trans_table,
                                    transition_key, transition_keysize , 0,
                                    state_q6);          
    create_and_insert_new_tt_entry_wild_card(state_q5, DEAD_STATE, 0);
    
/*q4*/
    state_t *state_q4 = create_new_state(fsm, "q4", FSM_FALSE);
    tt_entry = create_and_insert_new_tt_entry(&state_q4->state_trans_table,
                                   0, 0, 0,
                                   state_q5);
    
    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);
    create_and_insert_new_tt_entry_wild_card(state_q4, DEAD_STATE, 0);

/*q3*/
    state_t *state_q3 = create_new_state(fsm, "q3", FSM_FALSE);
    tt_entry = create_and_insert_new_tt_entry(&state_q3->state_trans_table,
                                   0, 0, 0,
                                   state_q4);
    
    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);
    create_and_insert_new_tt_entry_wild_card(state_q3, DEAD_STATE, 0); 

/*q2*/
    state_t *state_q2 = create_new_state(fsm, "q2", FSM_FALSE);
    tt_entry = create_and_insert_new_tt_entry(&state_q2->state_trans_table,
                                   0, 0, 0,
                                   state_q3);

    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);
    create_and_insert_new_tt_entry_wild_card(state_q2, DEAD_STATE, 0); 

/*q1*/
    state_t *state_q1 = create_new_state(fsm, "q1", FSM_FALSE);
    tt_entry = create_and_insert_new_tt_entry(&state_q1->state_trans_table,
                                   0, 0, 0,
                                   state_q2);

    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);
    create_and_insert_new_tt_entry_wild_card(state_q1, DEAD_STATE, 0); 

/*q0*/
    state_t *state_q0 = create_new_state(fsm, "q0", FSM_FALSE);
    set_fsm_initial_state(fsm, state_q0);

    tt_entry = create_and_insert_new_tt_entry(&state_q0->state_trans_table,
                                   0, 0, 0,
                                   state_q1);

    register_input_matching_tt_entry_cb(tt_entry, match_any_0_9_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_a_z_match_fn);
    register_input_matching_tt_entry_cb(tt_entry, match_any_A_Z_match_fn);
    create_and_insert_new_tt_entry_wild_card(state_q0, DEAD_STATE, 0); 

    return fsm; 
}
