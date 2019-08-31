/*
 * =====================================================================================
 *
 *       Filename:  std_fsm.h
 *
 *    Description:  This file contains standard Finite state machines and Common Reader Functions Declarations
 *
 *        Version:  1.0
 *        Created:  Saturday 31 August 2019 09:03:35  IST
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

#ifndef __STD_FSM__
#define __STD_FSM__

#include "fsm.h"

/*Standard FSM Input Reader Function*/

/*Reading 1 characted at a time*/
unsigned int
std_input_reader_fn_read_1_char(char *input_buff, 
                                unsigned int size,
                                unsigned int start_pos,
                                char *read_out_buff,   /*Already zeroed out*/
                                unsigned int *read_out_buff_len,
                                unsigned int read_out_buff_max_size);




/*Standard Example FSMs*/
fsm_t *email_validator_fsm();
fsm_t *phone_number_validator_fsm();

/*https://www.geeksforgeeks.org/mealy-and-moore-machines*/
fsm_t *mealy_machine_fsm();
fsm_t *moore_machine_fsm();

#endif /* __STD_FSM__ */
