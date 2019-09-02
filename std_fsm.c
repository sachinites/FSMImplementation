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
                         char *data2){      /*Data from User Input*/

    assert(size == 1 && !data1);
    
    /*We are bothered only about user data 'data2'*/

      if(*data2 >= 48 && 
          *data2 <= 57){

        return FSM_TRUE;
      }
      return FSM_FALSE;
}

fsm_bool_t
match_any_a_z_match_fn(char *data1,       /*Transition entry key, which will be empty buffer*/
                       unsigned int size, /*size shall be zero*/
                       char *data2){      /*Data from User Input*/

    assert(size == 1 && !data1);
    
    /*We are bothered only about user data 'data2'*/

      if(*data2 >= 97 && 
          *data2 <= 122){

        return FSM_TRUE;
      }
      return FSM_FALSE;
}

fsm_bool_t
match_any_A_Z_match_fn(char *data1,       /*Transition entry key, which will be empty buffer*/
                       unsigned int size, /*size shall be zero*/
                       char *data2){      /*Data from User Input*/

    assert(size == 1 && !data1);
    
    /*We are bothered only about user data 'data2'*/

      if(*data2 >= 65 && 
          *data2 <= 90){

        return FSM_TRUE;
      }
      return FSM_FALSE;
}


fsm_bool_t
match_any_0_9_or_a_z_or_A_Z_match_fn(char *data1, unsigned int size,
                                     char *data2){

    return (match_any_0_9_match_fn(data1, size, data2) || 
            match_any_a_z_match_fn(data1, size, data2) ||
            match_any_A_Z_match_fn(data1, size, data2));    
}

fsm_t *email_validator_fsm(){

    fsm_t *fsm = create_new_fsm("Email Validator");
    fsm_register_generic_transition_output_fn(fsm, 0);
    
    return fsm; 
}
