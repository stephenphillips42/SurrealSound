/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rpc_server.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

RetVal *
rpc_zeroize_1(void *argp, CLIENT *clnt)
{
	static RetVal clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpc_zeroize,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_RetVal, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

RetVal *
rpc_addvoter_1(int *argp, CLIENT *clnt)
{
	static RetVal clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpc_addvoter,
		(xdrproc_t) xdr_int, (caddr_t) argp,
		(xdrproc_t) xdr_RetVal, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

RetVal *
rpc_votefor_1(NameIdPair *argp, CLIENT *clnt)
{
	static RetVal clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpc_votefor,
		(xdrproc_t) xdr_NameIdPair, (caddr_t) argp,
		(xdrproc_t) xdr_RetVal, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

RetVal *
rpc_listcandidates_1(void *argp, CLIENT *clnt)
{
	static RetVal clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpc_listcandidates,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_RetVal, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

RetVal *
rpc_votecount_1(char **argp, CLIENT *clnt)
{
	static RetVal clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpc_votecount,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_RetVal, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
