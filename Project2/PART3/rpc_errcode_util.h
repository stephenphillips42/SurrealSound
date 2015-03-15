#include "rpc_server.h"
#include <string>

std::string RPCErrCodeToString(RPCErrCode ec) {
  switch(ec) {
    case RPC_OK:
      return "OK";
    case RPC_TRUEVALUE:
      return "TRUEVALUE";
    case RPC_NEW:
      return "NEW";
    case RPC_EXISTS:
      return "EXISTS";
    case RPC_ERROR:
      return "ERROR";
    case RPC_FALSEVALUE:
      return "FALSEVALUE";
    case RPC_NOTAVOTER:
      return "NOTAVOTER";
    case RPC_NOTACANDIDATE:
      return "NOTACANDIDATE";
    case RPC_ALREADYVOTED:
      return "ALREADYVOTED";
    default:
      return "UNKNOWN";
  }
}

int isError(RPCErrCode ec) {
  return ec > 4;
}
