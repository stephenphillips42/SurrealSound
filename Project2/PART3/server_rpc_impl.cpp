#include "../server.h"
#include "../errorcode.h"
#include "rpc_server.h"

#include <vector>
#include <string>

// Good old 'to string' implementation
#include <sstream>
#define SSTR( x ) ((dynamic_cast< std::ostringstream & > \
         ( std::ostringstream() << std::dec << x )).str()) 


using namespace std;

RPCErrCode convertErrCode(ErrCode er);

ServerWorker worker;
// For being able to create a persistent pointer without memory leaks
RetVal g_retval;
char emptystring[] = "";
string resultstr;
char * resultcstr = NULL;

// RPC Wrappers to the server functions
RetVal *
rpc_zeroize_1_svc(void *arg, struct svc_req *sreq) {
	((void)(arg));
	ErrCode ec = worker.zeroize();
	g_retval.errcode = convertErrCode(ec);
	g_retval.data = emptystring;
	return &g_retval;
}

RetVal *
rpc_addvoter_1_svc(int *voterid, struct svc_req *sreq) {
	ErrCode ec = worker.addvoter(*voterid);
	g_retval.errcode = convertErrCode(ec);
	g_retval.data = emptystring;
	return &g_retval;
}

RetVal *
rpc_votefor_1_svc(NameIdPair *nameid, struct svc_req *sreq) {
	ErrCode ec = worker.votefor(nameid->voterid,nameid->name);
	g_retval.errcode = convertErrCode(ec);
	g_retval.data = emptystring;
	return &g_retval;
}

// Actually returns a value so we need some extra work
RetVal *
rpc_listcandidates_1_svc(void *arg, struct svc_req *sreq) {
	((void)(arg));
	vector<string> candidates = worker.listcandidates();
	resultstr.clear();
	// Wasteful memory allocation, I know, but easier programming
	for(unsigned int i = 0; i < candidates.size(); ++i) {
		resultstr.append(candidates[i]);
		resultstr.append("\n");
	}
	resultstr.append("\n");
	g_retval.errcode = RPC_OK;
	free(resultcstr);
	resultcstr = strdup(resultstr.c_str());
	g_retval.data = resultcstr;
	return &g_retval;
}

RetVal *
rpc_votecount_1_svc(char **name, struct svc_req *sreq) {
	int count = worker.votecount(*name);
	RPCErrCode ec = RPC_OK;
	if (count < 0) {
		ec = RPC_ERROR;
	}
	resultstr = SSTR(count);
	g_retval.errcode = ec;
	free(resultcstr);
	resultcstr = strdup(resultstr.c_str());
	g_retval.data = resultcstr;
	return &g_retval;
}

int voteserver_1_freeresult	(SVCXPRT *transp,
							 xdrproc_t xdr_result,
							 caddr_t result) {
	// We really don't do anything here.
	(void) xdr_free(xdr_result, result);
	return 0;
}

RPCErrCode convertErrCode(ErrCode er) {
	switch(er) {
		case OK:
			return RPC_OK;
		case TRUEVALUE:
			return RPC_TRUEVALUE;
		case NEW:
			return RPC_NEW;
		case EXISTS:
			return RPC_EXISTS;
		case ERROR:
			return RPC_ERROR;
		case FALSEVALUE:
			return RPC_FALSEVALUE;
		case NOTAVOTER:
			return RPC_NOTAVOTER;
		case NOTACANDIDATE:
			return RPC_NOTACANDIDATE;
		case ALREADYVOTED:
			return RPC_ALREADYVOTED;
		default: // Don't know what is happening
			return RPC_ERROR;
	}
}

