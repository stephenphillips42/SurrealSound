#ifndef ERRORCODES
#define ERRORCODES value

// Error code of function
enum ErrCode {
  OK            =  0,
  TRUEVALUE     =  1,
  NEW           =  2,
  EXISTS        =  3,
  ERROR         = -1,
  FALSEVALUE    = -2,
  NOTAVOTER     = -3,
  NOTACANDIDATE = -4,
  ALREADYVOTED  = -5
};

#endif
