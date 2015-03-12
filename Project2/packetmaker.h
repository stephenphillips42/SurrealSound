#ifndef PACKETMAKERH
#define PACKETMAKERH value

// Functions for UDP/TCP packages for voting protocol
#include <string>

class ServerWorker;

// We enforce that each message be at most 512 bytes long (a voter should not
// need more than that for specifiying its voter ID and its candidate). The
// first 4 bytes are the package type, the next bytes are determined by the
// type of message, descibed below
#define MAXLEN 512

// These are the types of packets the client and server can send
enum PacketType {
  ZEROIZE            = 0,
  ADDVOTER           = 1,
  VOTEFOR            = 2,
  LIST               = 3,
  VOTECOUNT          = 4,
  RESPONSE_ZEROIZE   = 5,
  RESPONSE_ADDVOTER  = 6,
  RESPONSE_VOTEFOR   = 7,
  RESPONSE_LIST      = 8,
  RESPONSE_VOTECOUNT = 9,
  RESPONSE_UNKNOWN   = 10
};
std::string PacketTypeToString(PacketType type);

// Client packets are of the form:
// <PACKET-TYPE> "-" (<ARGUEMENT1> "-" <ARGUEMENT2> "-" ...)

// These functions implement the network side of the server API, see server.h
// for details on the API
class ClientPacketMaker {
public:
  ClientPacketMaker(int voterid);
  std::string zeroize();
  std::string addvoter();
  std::string votefor(std::string name);
  std::string listcandidates();
  std::string votecount(std::string name);
  std::string parseresponse(std::string response);
private:
  int id;
};

// Server packets are of the form:
// <PACKET-TYPE> "-" <ERROR-CODE> ("-" <RETURN-VALUES>)

class ServerPacketMaker {
public:
  ServerPacketMaker();
  // This is the super-function: It just takes in the packet and responds
  // accordingly
  std::string processpacket(std::string packet);
  // The functions processpacket calls.
  std::string zeroize();
  std::string addvoter(std::string packet);
  std::string votefor(std::string packet);
  std::string listcandidates();
  std::string votecount(std::string packet);
private:
  ServerWorker *worker;
  // Helper functions
  std::string sendError(PacketType type);
};

// Helper function
bool isInteger(std::string s);

#endif

