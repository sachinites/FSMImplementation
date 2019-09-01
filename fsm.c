/*
 * =====================================================================================
 *
 *       Filename:  fsm.c
 *
 *    Description:  This file contans the implementation of core functions of Generic FSM Project
 *
 *        Version:  1.0
 *        Created:  Saturday 31 August 2019 12:10:59  IST
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

fsm_t *create_new_fsm(const char *fsm_name){

    fsm_t * fsm = calloc(1, sizeof(fsm_t));
    strncpy(fsm->fsm_name, fsm_name, MAX_FSM_NAME_SIZE - 1);
    fsm->fsm_name[MAX_FSM_NAME_SIZE - 1] = '\0';
    return fsm;
}

void
set_fsm_initial_state(fsm_t *fsm, state_t *state){
    
    assert(!fsm->initial_state);
    fsm->initial_state = state;
}

void
set_fsm_input_buffer_size(fsm_t *fsm, unsigned int size){

    fsm->input_buffer[size] = '\0';
    fsm->input_buffer_size = size;
}


state_t *
create_new_state(fsm_t *fsm, char *state_name,
                 fsm_bool_t is_final,
                 state_input_matching_fn state_input_matching_fn_cb){

    assert(state_name);
    
    state_t *state = calloc(1, sizeof(state_t));
    
    strncpy(state->state_name, state_name, MAX_STATE_NAME_SIZE -1);
    state->state_name[MAX_STATE_NAME_SIZE -1] = '\0';

    state->is_final = is_final;
    state->state_input_matching_fn_cb = state_input_matching_fn_cb ? \
        state_input_matching_fn_cb : fsm->generic_state_input_matching_fn_cb;
    return state;
}

tt_entry_t *
get_next_empty_tt_entry(tt_t *trans_table){

    tt_entry_t *tt_entry_ptr = NULL;
    
    assert(trans_table);

    FSM_ITERATE_TRANS_TABLE_BEGIN(trans_table, tt_entry_ptr){
        /*No Op*/
    } FSM_ITERATE_TRANS_TABLE_END(trans_table, tt_entry_ptr);

    if(is_tt_entry_empty(tt_entry_ptr) == FSM_TRUE)
        return tt_entry_ptr;

    return NULL;
}


void create_and_insert_new_tt_entry(tt_t *trans_table,
        char *transition_key,
        unsigned int sizeof_key,
        output_fn outp_fn,
        state_t *next_state){

    assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);

    tt_entry_t *tt_entry_ptr = get_next_empty_tt_entry(trans_table);
    
    if(!tt_entry_ptr){
        printf("FATAL : Transition Table is Full\n");
        return;
    }

    memcpy(tt_entry_ptr->transition_key, transition_key, sizeof_key);
    tt_entry_ptr->transition_key[sizeof_key] = '\0';
    tt_entry_ptr->transition_key_size = sizeof_key;
    tt_entry_ptr->outp_fn = outp_fn;
    tt_entry_ptr->next_state = next_state;
}

static state_t *
fsm_apply_transition(fsm_t *fsm, state_t *state, 
                     char *input_buffer,        /*Input buffer to parse*/
                     unsigned int size,         /*Remaining length of the buffer*/
                     unsigned int *length_read, /* initialized to zero, returns the no of bytes read*/
                     fsm_output_buff_t *output_buffer){


   tt_entry_t *tt_entry = NULL;
   state_input_matching_fn match_cb = NULL;
   output_fn output_fn_cb = NULL;
   state_t *next_state = NULL;
    
   match_cb = state->state_input_matching_fn_cb ?  \
              state->state_input_matching_fn_cb :  \
              fsm->generic_state_input_matching_fn_cb;

   FSM_ITERATE_TRANS_TABLE_BEGIN((&state->state_trans_table),
                                 tt_entry){

        if((tt_entry->transition_key_size < size) &&
            match_cb(tt_entry->transition_key,
                    tt_entry->transition_key_size,
                    input_buffer)){

            output_fn_cb = tt_entry->outp_fn ? tt_entry->outp_fn : \
                            fsm->generic_transition_output_fn;
            
            next_state = tt_entry->next_state;
             
            if(output_fn_cb){
                output_fn_cb(state, next_state, 
                            input_buffer, 
                            tt_entry->transition_key_size,
                            output_buffer);
            }

            *length_read = tt_entry->transition_key_size;
            return next_state;
        }

   }FSM_ITERATE_TRANS_TABLE_END(&state->state_trans_table,
                                 tt_entry);
   return NULL;
}


fsm_error_t
execute_fsm(fsm_t *fsm, 
            char *input_buffer,         /*Input buffer containing user data*/
            unsigned int size,          /*Size of the data in the buffer*/
            fsm_output_buff_t *output_buffer,   /*output buffer to write data into*/
            fsm_bool_t *fsm_result){            /*A flag to track if data parsing ends in final state or not */


   state_t *initial_state = fsm->initial_state;
   assert(initial_state);

   state_t *current_state = initial_state;
   state_t *next_state = NULL;

   fsm->input_buffer_cursor = 0;
   unsigned int length_read = 0;
   unsigned int input_buffer_len = 0;
   char *buffer_to_parse;

   if(fsm_result){
       *fsm_result = FSM_FALSE;
   }

   /*Use Application Supplied Buffer*/
   if(input_buffer && size){
        buffer_to_parse = input_buffer;
        input_buffer_len = size;
   }
   else{
        /*Use FSM buffer set by the application*/
        buffer_to_parse = fsm->input_buffer;
        input_buffer_len = fsm->input_buffer_size;
   }

   /*If application has not supplied output buffer,
    * Use FSM's internal output buffer*/
   if(!output_buffer){
        output_buffer = &fsm->fsm_output_buff;
   }
   
   init_fsm_output_buffer(output_buffer);
   
   while(fsm->input_buffer_cursor < MAX_INP_BUFFER_LEN){
   
        length_read = 0;
         
        next_state = fsm_apply_transition(fsm, current_state, 
                        buffer_to_parse + fsm->input_buffer_cursor, 
                        (input_buffer_len - fsm->input_buffer_cursor),
                        &length_read, output_buffer);
        
        if(length_read){

            fsm->input_buffer_cursor += length_read;

            if(!next_state){
                return NO_TRANSITION;
            }

            current_state = next_state;
            continue;
        }
        break;
   }
 
   if(fsm_result){ 
       *fsm_result = current_state->is_final; 
   }
   return FSM_NO_ERROR;
}

void
fsm_register_input_reader_fn(fsm_t *fsm, input_fn fsm_input_reader_fn){

    fsm->fsm_input_reader_fn = fsm_input_reader_fn;
}

void
fsm_register_generic_state_input_matching_fn_cb(fsm_t *fsm, 
        state_input_matching_fn generic_state_input_matching_fn_cb){
    
    fsm->generic_state_input_matching_fn_cb = 
        generic_state_input_matching_fn_cb;
}

void
fsm_register_generic_transition_output_fn(fsm_t *fsm, output_fn output_fn_cb){

    fsm->generic_transition_output_fn = output_fn_cb;
}

void
init_fsm_output_buffer(fsm_output_buff_t *fsm_output_buff){
    
    memset(fsm_output_buff->output_buffer, 0, MAX_OUP_BUFFER_LEN);
    fsm_output_buff->curr_pos = 0;
}
