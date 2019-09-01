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

/*Standard FSM Input Reader Function*/

/*Reading 1 characted at a time*/
unsigned int
std_input_reader_fn_read_1_char(char *input_buff,
        unsigned int size,
        unsigned int start_pos,
        char *read_out_buff,   /*Already zeroed out*/
        unsigned int *read_out_buff_len,
        unsigned int read_out_buff_max_size){


    if(start_pos > (size -1))
        return 0;

    memcpy(read_out_buff, input_buff + start_pos, 1);
    read_out_buff[1] = '\0';
    *read_out_buff_len = 1;
    return 1;
}

fsm_bool_t
std_key_match_fn_1_char(char *data1, unsigned int size1,
                         char *data2, unsigned int size2){


    if(*data1 == *data2)
        return FSM_TRUE;
    return FSM_FALSE;
}

static fsm_bool_t
match_any_digit_or_alphabet_key_match_fn(char *data1, unsigned int size,
                             char *data2){
    
    /* I am not bothered what is there in transition table key buffer (data1)
     * bevause i am using hard-coded values here. This way I would have
     * to create very minimal no of transition entries in transition 
     * tables of states*/

      if(size == 0){
        return FSM_FALSE;
      }

      if(*data2 == '0' || 
         *data2 == '1' ||
         *data2 == '2' ||
         *data2 == '3' ||
         *data2 == '4' ||
         *data2 == '5' ||
         *data2 == '6' ||
         *data2 == '7' ||
         *data2 == '8' ||
         *data2 == '9' ||
         
         *data2 == 'a' ||
         *data2 == 'b' ||
         *data2 == 'c' ||
         *data2 == 'd' ||
         *data2 == 'e' ||
         *data2 == 'f' ||
         *data2 == 'g' ||
         *data2 == 'h' ||
         *data2 == 'i' ||
         *data2 == 'j' ||
         *data2 == 'k' ||
         *data2 == 'l' ||
         *data2 == 'm' ||
         *data2 == 'n' ||
         *data2 == '0' ||
         *data2 == 'p' ||
         *data2 == 'q' ||
         *data2 == 'r' ||
         *data2 == 's' ||
         *data2 == 't' ||
         *data2 == 'u' ||
         *data2 == 'v' ||
         *data2 == 'w' ||
         *data2 == 'x' ||
         *data2 == 'y' ||
         *data2 == 'z' ||

         *data2 == 'A' ||
         *data2 == 'B' ||
         *data2 == 'C' ||
         *data2 == 'D' ||
         *data2 == 'E' ||
         *data2 == 'F' ||
         *data2 == 'G' ||
         *data2 == 'H' ||
         *data2 == 'I' ||
         *data2 == 'J' ||
         *data2 == 'K' ||
         *data2 == 'L' ||
         *data2 == 'M' ||
         *data2 == 'N' ||
         *data2 == 'O' ||
         *data2 == 'P' ||
         *data2 == 'Q' ||
         *data2 == 'R' ||
         *data2 == 'S' ||
         *data2 == 'T' ||
         *data2 == 'U' ||
         *data2 == 'V' ||
         *data2 == 'W' ||
         *data2 == 'X' ||
         *data2 == 'Y' ||
         *data2 == 'Z'
         ) {

        return FSM_TRUE;
      }
      return FSM_FALSE;
}

fsm_t *email_validator_fsm(){

    fsm_t *fsm = create_new_fsm("Email Validator");
    fsm_register_input_reader_fn(fsm, std_input_reader_fn_read_1_char);
    fsm_register_generic_state_input_matching_fn_cb(fsm, match_any_digit_or_alphabet_key_match_fn);
    fsm_register_generic_transition_output_fn(fsm, 0);
    
    char charact;

    state_t *dead_state =  create_new_state(fsm, "DEAD_STATE", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&dead_state->state_trans_table,
                                    0, 0,
                                    0,
                                    dead_state);
    
    state_t *state_S8_m =  create_new_state(fsm, "S8_m", FSM_FALSE, 0);
    set_fsm_initial_state(fsm, state_S8_m);
    create_and_insert_new_tt_entry(&state_S8_m->state_trans_table,
                                    0, 0,
                                    0,
                                    dead_state);

    state_t *state_S8_o =  create_new_state(fsm, "S8_o", FSM_FALSE, 0);
    charact = 'm';
    create_and_insert_new_tt_entry(&state_S8_o->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S8_m);

    state_t *state_S8_c =  create_new_state(fsm, "S8_c", FSM_FALSE, 0);
    charact = 'o';
    create_and_insert_new_tt_entry(&state_S8_c->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S8_o);

    state_t *state_S7_dot =  create_new_state(fsm, "S7_dot", FSM_FALSE, 0);
    charact = 'c';
    create_and_insert_new_tt_entry(&state_S7_dot->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S8_c);

    state_t *state_S6_l =  create_new_state(fsm, "S6_l", FSM_FALSE, 0);
    charact = '.';
    create_and_insert_new_tt_entry(&state_S6_l->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S7_dot);

    state_t *state_S6_i =  create_new_state(fsm, "S6_i", FSM_FALSE, 0);
    charact = 'l';
    create_and_insert_new_tt_entry(&state_S6_i->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6_l);

    state_t *state_S6_a =  create_new_state(fsm, "S6_a", FSM_FALSE, 0);
    charact = 'i';
    create_and_insert_new_tt_entry(&state_S6_a->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6_i);

    state_t *state_S6_m =  create_new_state(fsm, "S6_m", FSM_FALSE, 0);
    charact = 'a';
    create_and_insert_new_tt_entry(&state_S6_m->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6_a);

    state_t *state_S6_g =  create_new_state(fsm, "S6_g", FSM_FALSE, 0);
    charact = 'm';
    create_and_insert_new_tt_entry(&state_S6_g->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6_m);

    state_t *state_S6 =  create_new_state(fsm, "S6", FSM_FALSE, 0);
    charact = 'g';
    create_and_insert_new_tt_entry(&state_S6->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6_g);


    state_t *state_S5 = create_new_state(fsm, "S5", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&state_S5->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S5);
    
    charact = '@';
    create_and_insert_new_tt_entry(&state_S5->state_trans_table,
                                    &charact, 1,
                                    0,
                                    state_S6);
    create_and_insert_new_tt_entry(&state_S5->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S5);

    state_t *state_S4 = create_new_state(fsm, "S4", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&state_S4->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S5);

    state_t *state_S3 = create_new_state(fsm, "S3", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&state_S3->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S4);
    
    state_t *state_S2 = create_new_state(fsm, "S2", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&state_S2->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S3);
    
    state_t *state_S1 = create_new_state(fsm, "S1", FSM_FALSE, 0);
    create_and_insert_new_tt_entry(&state_S1->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S2);
    
    state_t *state_S0 = create_new_state(fsm, "S0", FSM_FALSE, 0);
    set_fsm_initial_state(fsm, state_S0);
    create_and_insert_new_tt_entry(&state_S0->state_trans_table,
                                    0, 0,
                                    0,
                                    state_S1);
    return fsm; 
}
