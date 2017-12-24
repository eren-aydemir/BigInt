//
//  statemachine.cpp
//  bigInt
//
//  Created by Eren on 19.12.2017.
//  Copyright © 2017 Eren Aydemir. All rights reserved.
//

#include "statemachine.hpp"

stack<string> numbers_stack;
stack<string> operators_stack;

void start(string el){
  //do nothing
  printf("start.\r\n");
};

void number(string el){
  
  //do nothing
  printf("number.\r\n");
  numbers_stack.push(el);
};

void mathoperator(string el){
  
  //do nothing
  printf("mathoperator.\r\n");
  operators_stack.push(el);
};

void StateMachine_Init(stateMachine_t *stateMachine){
  
  static int count = 0;
  count += 1;
  
  if (count == 1){
    printf("Initialising state machine.\r\n");
    stateMachine->currState = START;
  }
  
};

EventType StateMachine_GetEvent(stateMachine_t *stateMachine){
  
  //buraya eventler tanimlanacak
  //return EV0;
  static int count = 0;
  count += 1;
  string input_class;
  string el = stateMachine->el;
  
  EventType event = NONEV; //degisti!!!
  StateType currState = stateMachine->currState;
  if (el == "0" || el == "1" || el == "2" || el == "3" || el == "4" || el == "5" ||\
      el == "6" || el == "7" || el == "8" || el == "9") {
    input_class = "isNUMBER";
  }else if (el == "+" || el == "*" || el == "/"){
    input_class = "isOPERATOR";
  }else{
    input_class = "NONE";
  }
  
  if(count == 1){ //START
    cout << "EV0" << endl;
    event = EV0; //NUMBER
  }else if(currState == NUMBER && input_class == "isNUMBER"){
    cout << "EV0" << endl;
    event = EV0; //NUMBER
  }else if(currState == NUMBER && input_class == "isOPERATOR"){
    cout << "EV1" << endl;
    event = EV1; //MATHOPERATOR
  }else if(currState == MATHOPERATOR && input_class == "isNUMBER"){
    cout << "EV0" << endl;
    event = EV0; //NUMBER
  }
  
  return event;
};

void StateMachine_RunIteration(stateMachine_t *stateMachine){
  
  EventType event;
  event = StateMachine_GetEvent(stateMachine);
  
  // Iterate through the state transition matrix, checking if there is both a match with the current state
  // and the event
  
  for(int i = 0; i < sizeof(stateTransitionMatrix)/sizeof(stateTransitionMatrix[0]); i++) {
    
    if(stateTransitionMatrix[i].currState == stateMachine->currState) {
      
      if(stateTransitionMatrix[i].event == event) {
        
        // Transition to the next state
        stateMachine->currState =  stateTransitionMatrix[i].nextState;
        
        // Call the function associated with transition
        if (stateMachine->currState == NUMBER){
          (stateFunctionBehavior[stateMachine->currState].func)(stateMachine->el);
          stateMachine->numbers = numbers_stack;
        }
        if (stateMachine->currState == MATHOPERATOR){
          (stateFunctionBehavior[stateMachine->currState].func(stateMachine->el));
          stateMachine->operators = operators_stack;
          while(!numbers_stack.empty()){
            numbers_stack.pop();
          }
        }
        break;
      }
    }
  }
};

const char *StateMachine_GetStateName(StateType state){
  return stateFunctionBehavior[state].name;
};


stateMachine_t::stateMachine_t(){
  this->el = 'o';
};
