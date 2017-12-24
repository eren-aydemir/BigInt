//
//  main.cpp
//  bigInt
//
//  Created by Eren on 14.12.2017.
//  Copyright © 2017 Eren Aydemir. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <math.h>
#include "bigInt.h"
#include "statemachine.hpp"
using namespace std;

BigInt addBigInt(BigInt &a, BigInt &b);
BigInt multiplyBigInt(BigInt &a, BigInt &b);

void parser(const string& filename){

   stateMachine_t stateMachine;
  
   BigInt sayi;
   BigInt sayi1;
   BigInt sayi2;
   BigInt result;

   IntSLLNode *ptr;
   IntSLLNode *ptr_tmp;
   string math_operator;
   string math_operator_top;
  
   StateMachine_Init(&stateMachine);
   
   string line;
   string el;
   ifstream infile;
   infile.open (filename);
  
   while(!infile.eof())
   {
     getline(infile,line);
     if (line != "") {
       el = line;
     }
   }
   infile.close();
   
   const char *txt = el.c_str();
   
   for(int i=0; i<el.length(); i++){
   
     printf("incoming char is %c:\r\n", txt[i]);
     // Run first iteration
     stateMachine.el = txt[i];
     StateMachine_RunIteration(&stateMachine);
     if (stateMachine.currState == NUMBER) {
       sayi.update(txt[i]);
       //cout << txt[i] << endl;
     }else if (stateMachine.currState == MATHOPERATOR && stateMachine.operators.size() == 1){
       
       ptr = sayi.bigNumber.head;
       for (int i = 0; (i<sayi.len_of_number); i++) {
         sayi1.pushHead('a');
       }
       ptr_tmp = sayi1.bigNumber.head;
       
       while (ptr != NULL) {
         ptr_tmp->info = ptr->info;
         ptr = ptr->next;
         ptr_tmp = ptr_tmp->next;
       }
       sayi1.len_of_number = sayi.len_of_number;
       sayi.clear();
       while (!stateMachine.numbers.empty()) {
         stateMachine.numbers.pop();
       }
     }else if (stateMachine.currState == MATHOPERATOR && stateMachine.operators.size() > 1){

       sayi2.copy_content(sayi);
       sayi.clear();
       while (!stateMachine.numbers.empty()) {
         stateMachine.numbers.pop();
       }
         
       math_operator_top = stateMachine.operators.top();
       stateMachine.operators.pop();
       math_operator = stateMachine.operators.top();
       
       if(math_operator == "/"){
         stateMachine.operators.pop();
       }else if(math_operator == "*"){
         result.clear();
         result = multiplyBigInt(sayi1, sayi2);
         sayi1.copy_content(result);
         sayi2.clear();
         stateMachine.operators.pop();
       }else if(math_operator == "+"){
         result.clear();
         result = addBigInt(sayi1, sayi2);
         sayi1.copy_content(result);
         sayi2.clear();
         stateMachine.operators.pop();
       stateMachine.operators.push(math_operator_top);
     }
   }
}

   result.read();
}


BigInt addBigInt(BigInt &a, BigInt &b){

  BigInt result;
  int carry = 0;
  int sum = 0;
  int digit = 0;
  int len = 0;
  int equalize = 0;
  
  std::stack<int> stacka;
  std::stack<int> stackb;
  
  IntSLLNode *tmpa = a.bigNumber.head;
  IntSLLNode *tmpb = b.bigNumber.head;
  
  while(a.len_of_number != b.len_of_number){ //basamak sayilarini esitle
    
    equalize = int(a.len_of_number) - int(b.len_of_number);
    
    if(equalize>0){
      stackb.push(0);
      b.len_of_number = b.len_of_number + 1;
    }else if(equalize<0){
      stacka.push(0);
      a.len_of_number = a.len_of_number + 1;
    }
  }
  
  while(tmpa != NULL && tmpa->info < 10){
  
    stacka.push(tmpa->info);
    tmpa = tmpa->next;
  
  }

  while(tmpb != NULL && tmpb->info < 10){
    
    stackb.push(tmpb->info);
    tmpb = tmpb->next;
    
  }
  
  while (!stacka.empty() || !stackb.empty()){
    
    len = len + 1;
    
    sum = stacka.top() + stackb.top() + carry;
    
    digit = sum % 10;
    carry = ((sum-digit) / 10);
    result.pushHead(digit);
    
    stacka.pop();
    stackb.pop();
  
  }

  result.len_of_number = len;
  
  return result;
  
}

BigInt multiplyBigInt(BigInt &a, BigInt &b){
  
  BigInt returningInt;
  vector<int> result(a.len_of_number + b.len_of_number, 0);
  int carry = 0;
  int sum = 0;
  int digit = 0;
  int len = 0;
  
  int index_a;
  int index_b;
  
  std::vector<int> vectora;
  std::vector<int> vectorb;
  
  IntSLLNode *tmpa = a.bigNumber.head;
  IntSLLNode *tmpb = b.bigNumber.head;
  
  while(tmpa != NULL && tmpa->info < 10){
    vectora.push_back(tmpa->info);
    tmpa = tmpa->next;
    
  }
  index_a = 0;
  index_b = 0;
  
  while(tmpb != NULL && tmpb->info < 10){
    
    vectorb.push_back(tmpb->info);
    tmpb = tmpb->next;
    
  }
  
  for (int i = vectora.size()-1; i>=0; i--) {
    carry = 0;
    index_b = 0;
    
    for (int j = vectorb.size()-1; j>=0; j--) {
      
      sum = vectora[i] * vectorb[j] + result[index_a + index_b] + carry;
      carry = sum/10;
      result[index_a + index_b] = sum % 10;
      
      index_b++;
    }
    
    if (carry > 0){
      result[index_a + index_b] += carry;
    }
    
    index_a++;
  }
  
  for (int i = 0; i<result.size(); i++) {
    returningInt.pushHead(result[i]);
  }
  returningInt.len_of_number = int(result.size());
  
  return returningInt;
  
}

int main(int argc, const char * argv[])
{
/*
  BigInt sayi;
  sayi.create("12");

  BigInt sayi2;
  sayi2.create("12");
  
  //sayi.printAll();
  //sayi.read();
 */
 /*
  BigInt sayi4;
  sayi4.updateFromAFile("/Users/eren/Desktop/Yeditepe CSE/CSE211/Project/bigInt/bigInt/sayi.txt");
  sayi4.read();

  BigInt sayi3;
  
  sayi3 = multiplyBigInt(sayi4, sayi4);
  sayi3.read();
  sayi3.update('1');
  sayi3.read();
  sayi3.update("12346789");
  sayi3.read();
  */
  
  parser("/Users/eren/Desktop/bigInt/bigInt/islem.txt");
  
  return 0;
  
}
