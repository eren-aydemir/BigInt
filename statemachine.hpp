//
//  statemachine.hpp
//  bigInt
//
//  Created by Eren on 19.12.2017.
//  Copyright © 2017 Eren Aydemir. All rights reserved.
//

#ifndef statemachine_hpp
#define statemachine_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <math.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

typedef enum{
  START,
  NUMBER,
  MATHOPERATOR,
}StateType;

typedef enum{
  EV0,
  EV1,
  NONEV
}EventType;

typedef struct{
  
  StateType currState;
  EventType event;
  StateType nextState;
  
}STMrow_t;


static STMrow_t stateTransitionMatrix[] = {
  
  //CURR STATE      //EVENT     //NEXT STATE
  {START,           EV0,        NUMBER},
  {NUMBER,          EV0,        NUMBER},
  {NUMBER,          EV1,        MATHOPERATOR},
  {MATHOPERATOR,    EV0,        NUMBER}
};

struct stateMachine_t{
  StateType currState;
  string el;
  stack<string> numbers;
  stack<string> operators;
  stateMachine_t();
};

typedef struct {
  const char *name;
  void (*func)(string);
} SFrow_t;

void start(string);

void number(string);

void mathoperator(string);

static SFrow_t stateFunctionBehavior[] = {
  {"START",         &start},
  {"NUMBER",        &number},
  {"MATHOPERATOR",  &mathoperator}
};

void StateMachine_Init(stateMachine_t *stateMachine);
void StateMachine_RunIteration(stateMachine_t *stateMachine);
const char *StateMachine_GetStateName(StateType state);

#endif /* statemachine_hpp */
