/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPC_SERVER_H_RPCGEN
#define _RPC_SERVER_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


enum RPCErrCode {
	RPC_OK = 0,
	RPC_TRUEVALUE = 1,
	RPC_NEW = 2,
	RPC_EXISTS = 3,
	RPC_ERROR = 4,
	RPC_FALSEVALUE = 5,
	RPC_NOTAVOTER = 6,
	RPC_NOTACANDIDATE = 7,
	RPC_ALREADYVOTED = 8,
};
typedef enum RPCErrCode RPCErrCode;

struct RetVal {
	RPCErrCode errcode;
	char *data;
};
typedef struct RetVal RetVal;

struct NameIdPair {
	int voterid;
	char *name;
};
typedef struct NameIdPair NameIdPair;

#define VOTESERVER 0x2100ffff
#define VOTESERVER_V1 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpc_zeroize 1
extern  RetVal * rpc_zeroize_1(void *, CLIENT *);
extern  RetVal * rpc_zeroize_1_svc(void *, struct svc_req *);
#define rpc_addvoter 2
extern  RetVal * rpc_addvoter_1(int *, CLIENT *);
extern  RetVal * rpc_addvoter_1_svc(int *, struct svc_req *);
#define rpc_votefor 3
extern  RetVal * rpc_votefor_1(NameIdPair *, CLIENT *);
extern  RetVal * rpc_votefor_1_svc(NameIdPair *, struct svc_req *);
#define rpc_listcandidates 4
extern  RetVal * rpc_listcandidates_1(void *, CLIENT *);
extern  RetVal * rpc_listcandidates_1_svc(void *, struct svc_req *);
#define rpc_votecount 5
extern  RetVal * rpc_votecount_1(char **, CLIENT *);
extern  RetVal * rpc_votecount_1_svc(char **, struct svc_req *);
extern int voteserver_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpc_zeroize 1
extern  RetVal * rpc_zeroize_1();
extern  RetVal * rpc_zeroize_1_svc();
#define rpc_addvoter 2
extern  RetVal * rpc_addvoter_1();
extern  RetVal * rpc_addvoter_1_svc();
#define rpc_votefor 3
extern  RetVal * rpc_votefor_1();
extern  RetVal * rpc_votefor_1_svc();
#define rpc_listcandidates 4
extern  RetVal * rpc_listcandidates_1();
extern  RetVal * rpc_listcandidates_1_svc();
#define rpc_votecount 5
extern  RetVal * rpc_votecount_1();
extern  RetVal * rpc_votecount_1_svc();
extern int voteserver_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_RPCErrCode (XDR *, RPCErrCode*);
extern  bool_t xdr_RetVal (XDR *, RetVal*);
extern  bool_t xdr_NameIdPair (XDR *, NameIdPair*);

#else /* K&R C */
extern bool_t xdr_RPCErrCode ();
extern bool_t xdr_RetVal ();
extern bool_t xdr_NameIdPair ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPC_SERVER_H_RPCGEN */
