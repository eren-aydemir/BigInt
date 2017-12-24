//
//  bigInt.h
//  bigInt
//
//  Created by Eren on 14.12.2017.
//  Copyright © 2017 Eren Aydemir. All rights reserved.
//

#ifndef bigInt_h
#define bigInt_h

#include "intSLList.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

class BigInt{

  public:
    IntSLList bigNumber;
    int len_of_number;
  
    void update(const string& el); //create from string
    void updateFromAFile(const string& el); //create from a file
  
    void read();
    void update(const char& el); //extend with a char
  
    void printAll(){
      this->bigNumber.printAll();
    }
    void copy_content(BigInt&);
  
    void pushTail(const char& el){
      this->bigNumber.addToTail(el);
    }
    void pushHead(const char& el){
      this->bigNumber.addToHead(el);
    }
    void clear(){
      this->bigNumber.clear();
      this->bigNumber.tail = NULL;
      this->len_of_number = 0;
    }
    BigInt(); //default constructor
    BigInt(const BigInt &obj);  //copy constructor

};

BigInt::BigInt(){
  this->len_of_number = 0;
};

BigInt::BigInt(const BigInt &obj){
  this->bigNumber = obj.bigNumber ;
  this->len_of_number = obj.len_of_number;
};


void BigInt::update(const string& el){
  
  this->clear();
  
  const char *txt = el.c_str();
  
  for(int i=0; i<el.length(); i++){
    
    //cout << txt[i] << endl;
    
    this->pushTail(txt[i] - '0');
  }
  this->len_of_number = int(el.length());
}

//extend BigInt with a char
void BigInt::update(const char& el){
  
  while(el != 'a'){
    if(this->bigNumber.head == NULL){
      this->pushHead(el - '0');
    }else{
      this->pushTail(el - '0');
    }
    this->len_of_number = this->len_of_number + 1;
    break;
  }

}


void BigInt::updateFromAFile(const string& filename){
  
  this->clear();
  
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
    //cout << el << endl;
  }
  infile.close();
  
  const char *txt = el.c_str();
  
  for(int i=0; i<el.length(); i++){
    
    //cout << txt[i] << endl;
    
    this->pushTail(txt[i] - '0');
  }
  this->len_of_number = int(el.length());
}

void BigInt::read(){

  double number = 0;
  int count = 0;
  
  IntSLLNode *tmp = this->bigNumber.head;
  
  count = this->len_of_number;
  
  while (tmp != 0 && tmp->info < 10) {
    
    count = count - 1;

    number = number + int(tmp->info)*pow(10,count);
    tmp = tmp->next;
  }
  cout.precision(1);
  cout << fixed << number << endl;

}

void BigInt::copy_content(BigInt &obj){

  this->clear();
  
  for (int i = 0; (i<obj.len_of_number); i++) {
    this->pushHead('a');
  }
  
  IntSLLNode *tmp_this = this->bigNumber.head;
  IntSLLNode *tmp_obj = obj.bigNumber.head;

  while(tmp_obj != NULL){
  
    tmp_this->info = tmp_obj->info;
    tmp_this = tmp_this->next;
    tmp_obj = tmp_obj->next;
    
  }
  this->len_of_number = obj.len_of_number;
};


#endif /* bigInt_h */
