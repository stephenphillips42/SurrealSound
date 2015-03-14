#ifndef ERRORCODES
#define ERRORCODES value

// Error code of function
enum ErrCode {
  OK            =  0,
  TRUEVALUE     =  0, // Repeated
  NEW           =  1,
  EXISTS        =  2,
  ERROR         = -1,
  FALSEVALUE    = -1, // Repeated
  NOTAVOTER     = -2,
  NOTACANDIDATE = -2, // Repeated
  ALREADYVOTED  = -3
};

#endif
