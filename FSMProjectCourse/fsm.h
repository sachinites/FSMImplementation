/*
 * =====================================================================================
 *
 *       Filename:  fsm.h
 *
 *    Description:  This file contans the Data structure definitions for Generic FSM Project
 *
 *        Version:  1.0
 *        Created:  Tuesday 03 September 2019 07:18:53  IST
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

/* Visit my website for free courses and discounts : 
 * https://csepracticals.wixsite.com/csepracticals */

#ifndef __FSM__
#define __FSM__

#define MAX_INP_BUFFER_LEN  128
#define MAX_TRANSITION_TABLE_SIZE   128
#define MAX_STATE_NAME_SIZE 32
#define MAX_FSM_NAME_SIZE 32
#define MAX_TRANSITION_KEY_SIZE 64
#define MAX_FSM_OUTPUT_BUFFER 1024

typedef enum {

    FSM_FALSE,
    FSM_TRUE
} fsm_bool_t;


typedef struct state_ state_t;
typedef struct fsm_ fsm_t;

typedef struct fsm_output_buff_{
    char output_buffer[MAX_FSM_OUTPUT_BUFFER];
    unsigned int curr_pos;
} fsm_output_buff_t;

typedef void (*output_fn)(state_t *, state_t *,
        char *, unsigned int,   /*Input buff, size of Inputputbuff*/
        fsm_output_buff_t *);   /*Output Buff*/

void
init_fsm_output_buffer (fsm_output_buff_t *
                    fsm_output_buff);

typedef struct tt_entry_ {

    char transition_key[MAX_TRANSITION_KEY_SIZE];
    unsigned int transition_key_size;
    state_t *next_state;
    output_fn outp_fn;
} tt_entry_t;

typedef struct tt_{

    tt_entry_t
        tt_entry[MAX_TRANSITION_TABLE_SIZE];
} tt_t;

struct state_ {

    /*Name of the state, must be unique within FSM*/
    char state_name[MAX_STATE_NAME_SIZE];
    /*Transition Table of the state*/
    tt_t state_trans_table;
    /*Boolean if the state is final or not*/
    fsm_bool_t is_final;
};

struct fsm_{

    /*Intitial state of FSM to start with*/
    state_t *initial_state;
    /*Name of FSM*/
    char fsm_name[MAX_FSM_NAME_SIZE];
    /* Application provided input data to parse
     * by FSM*/
    char input_buffer[MAX_INP_BUFFER_LEN];
    /* Length of above data*/
    unsigned int input_buffer_size;
    /*Cursor to read the above input_buffer in coninuation*/
    unsigned int input_buffer_cursor;
};

state_t *
create_new_state(char *state_name, fsm_bool_t is_final);

tt_entry_t * create_and_insert_new_tt_entry(tt_t *trans_table,
        char *transition_key,
        unsigned int sizeof_key,
        state_t *next_state,
        output_fn outp_fn);

fsm_t *create_new_fsm(const char *fsm_name);

#define FSM_ITERATE_TRANS_TABLE_BEGIN(tr_table_ptr, tt_entry_ptr)   \
    do{                                                             \
        unsigned int index = 0;                                     \
        for(; index < MAX_TRANSITION_TABLE_SIZE; index++){          \
            tt_entry_ptr = &(tr_table_ptr->tt_entry[index]);        \
            if(is_tt_entry_empty(tt_entry_ptr) == FSM_TRUE)         \
            break;                                                  \


#define FSM_ITERATE_TRANS_TABLE_END(tr_table_ptr, tt_entry_ptr)     \
        }}while(0);

typedef enum {

        FSM_NO_TRANSITION,
        FSM_NO_ERROR
} fsm_error_t;

fsm_error_t
execute_fsm(fsm_t *fsm,
        char *input_buffer,
        unsigned int size,
        fsm_output_buff_t *output_buffer,
        fsm_bool_t *fsm_result);


#endif
