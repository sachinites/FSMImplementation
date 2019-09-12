/*
 * =====================================================================================
 *
 *       Filename:  app.c
 *
 *    Description:   This file is a test demo for making use of fsm project
 *
 *        Version:  1.0
 *        Created:  Sunday 08 September 2019 04:22:30  IST
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

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

void
bit_flipper_output_fn_gen(state_t *from, state_t *to,
        char *input_buff,
        unsigned int input_buff_size,
        fsm_output_buff_t *fsm_output_buff){

    char out;
    out = (*input_buff == '1') ? '0' : '1';
    fsm_output_buff->curr_pos += snprintf(fsm_output_buff->output_buffer +
            fsm_output_buff->curr_pos,
            (MAX_FSM_OUTPUT_BUFFER - fsm_output_buff->curr_pos - 1),
            "%s-->%c|%c-->%s\n",
            from->state_name, *input_buff, out,
            to->state_name);
}


int
main(int argc, char **argv){

    /*Create a FSM*/
    char transition_key_0 = '0',
         transition_key_1 = '1';

    unsigned int transition_keysize = 1;

    fsm_t *fsm = create_new_fsm("FSM Alternate");
    
    /*Create FSM States*/

    state_t *state_q0, *state_q1, *state_q2, *D;
    state_q0 = create_new_state("q0", FSM_FALSE);
    set_fsm_initial_state(fsm, state_q0);
    
    state_q1 = create_new_state("q1", FSM_TRUE);
    state_q2 = create_new_state("q2", FSM_TRUE);
    D = create_new_state("D", FSM_FALSE);

/*Transition Table of State q0*/
    create_and_insert_new_tt_entry(&state_q0->state_trans_table,
                                    &transition_key_1, transition_keysize, state_q1, bit_flipper_output_fn_gen);
    create_and_insert_new_tt_entry(&state_q0->state_trans_table,
                                    &transition_key_0, transition_keysize, state_q2, bit_flipper_output_fn_gen);

/*Transition Table of State q1*/
    create_and_insert_new_tt_entry(&state_q1->state_trans_table,
                                    &transition_key_1, transition_keysize, D, bit_flipper_output_fn_gen);
    create_and_insert_new_tt_entry(&state_q1->state_trans_table,
                                    &transition_key_0, transition_keysize, state_q2, bit_flipper_output_fn_gen);

/*Transition Table of State q2*/
    create_and_insert_new_tt_entry(&state_q2->state_trans_table,
                                    &transition_key_1, transition_keysize, state_q1, bit_flipper_output_fn_gen);
    create_and_insert_new_tt_entry(&state_q2->state_trans_table,
                                    &transition_key_0, transition_keysize, D, bit_flipper_output_fn_gen);

/*Transition Table of Dead State D*/
    create_and_insert_new_tt_entry(&D->state_trans_table,
                                    &transition_key_1, transition_keysize, D, bit_flipper_output_fn_gen);
    create_and_insert_new_tt_entry(&D->state_trans_table,
                                    &transition_key_0, transition_keysize, D, bit_flipper_output_fn_gen);
                                    
/*FSM Creation Complete*/


/*Using the Above Created FSM*/

    fsm_bool_t fsm_result;
    fsm_error_t fsm_error;
    fsm_output_buff_t fsm_output_buff;
    init_fsm_output_buffer(&fsm_output_buff);

    fsm_error = execute_fsm(fsm,
                    "0101010101\0",         /*Input String to process*/
                    strlen("0101010101\0"), /*Length of the Input String*/
                    &fsm_output_buff,
                    &fsm_result);

    if(fsm_error == FSM_NO_ERROR){
        if(fsm_result == FSM_TRUE){
            printf("Input String is Validated\n");
            printf("FSM Output string : \n%s\n", fsm_output_buff.output_buffer);
        }
        else{
            printf("Input String is Validated\n");
        }
    }
    return 0;
}
