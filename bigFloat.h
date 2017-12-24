//
//  bigFloat.h
//  bigInt
//
//  Created by Eren on 17.12.2017.
//  Copyright © 2017 Eren Aydemir. All rights reserved.
//

#ifndef bigFloat_h
#define bigFloat_h
#include "intSLList.h"
#include "bigInt.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

class BigFloat{
  
  public:
  
    BigInt bigNumber;
    int index_of_decimal;

}

void BigFloat::clear{
  this->bigNumber.bigNumber.clear();
}


#endif /* bigFloat_h */
