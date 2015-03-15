/* The RPC implementation of the voting server */
/* The RPC version of the error codes */
enum RPCErrCode {
      RPC_OK,
      RPC_TRUEVALUE,
      RPC_NEW,
      RPC_EXISTS,
      RPC_ERROR,
      RPC_FALSEVALUE,
      RPC_NOTAVOTER,
      RPC_NOTACANDIDATE,
      RPC_ALREADYVOTED
};

/* Generic return value for all the RPC functions */
struct RetVal {
    RPCErrCode errcode;
    string data<>;
};

/* Argument for votefor method */
struct NameIdPair {
    int voterid;
    string name<>;
};

program VOTESERVER {
    version VOTESERVER_V1 {
        RetVal rpc_zeroize() = 1;
        RetVal rpc_addvoter(int) = 2;
        RetVal rpc_votefor(NameIdPair) = 3;
        RetVal rpc_listcandidates() = 4;
        RetVal rpc_votecount(string) = 5;
    } = 1;
} = 0x2100ffff;

