#include <string>
#include <stdlib.h>
#include <iostream>
#include "packetmaker.h"
#include "server.h"
#include "errorcode.h"

// Thank you Stack Overflow! For stringifying objects
#include <sstream>
#define SSTR( x ) ((dynamic_cast< std::ostringstream & > \
        ( std::ostringstream() << std::dec << x )).str()) 

using namespace std;

string PacketTypeToString(PacketType type) {
  switch(type) {
    case ZEROIZE:
      return "ZEROIZE";
    case ADDVOTER:
      return "ADDVOTER";
    case VOTEFOR:
      return "VOTEFOR";
    case LIST:
      return "LIST";
    case VOTECOUNT:
      return "VOTECOUNT";
    case RESPONSE_ZEROIZE:
      return "RESPONSE_ZEROIZE";
    case RESPONSE_ADDVOTER:
      return "RESPONSE_ADDVOTER";
    case RESPONSE_VOTEFOR:
      return "RESPONSE_VOTEFOR";
    case RESPONSE_LIST:
      return "RESPONSE_LIST";
    case RESPONSE_VOTECOUNT:
      return "RESPONSE_VOTECOUNT";
    case RESPONSE_UNKNOWN:
      return "RESPONSE_UNKNOWN";
    default:
      return "UNKNOWN";
  }
}
// Useful here
string ErrCodeToString(ErrCode code) {
  switch(code) {
    case OK:
      return "OK";
    case NEW:
      return "NEW";
    case EXISTS:
      return "EXISTS";
    case ERROR:
      return "ERROR";
    case NOTAVOTER:
      return "NOTAVOTER";
    case ALREADYVOTED:
      return "ALREADYVOTED";
    default:
      return "UNKNOWN";    
  }
}


// Client functions
ClientPacketMaker::ClientPacketMaker(int voterid) {
  id = voterid;
}

string ClientPacketMaker::zeroize() {
  string packet;
  PacketType type = ZEROIZE;
  packet.append(SSTR(type));
  packet.append("-");
  return packet;
}

string ClientPacketMaker::addvoter() {
  string packet;
  PacketType type = ADDVOTER;
  packet.append(SSTR(type));
  packet.append("-");
  packet.append(SSTR(id));
  return packet;
}

string ClientPacketMaker::votefor(std::string name) {
  string packet;
  PacketType type = VOTEFOR;
  packet.append(SSTR(type));
  packet.append("-");
  packet.append(SSTR(id));
  packet.append("-");
  packet.append(name);
  return packet;
}

string ClientPacketMaker::listcandidates() {
  string packet;
  PacketType type = LIST;
  packet.append(SSTR(type));
  packet.append("-");
  return packet;
}

string ClientPacketMaker::votecount(std::string name) {
  string packet;
  PacketType type = VOTECOUNT;
  packet.append(SSTR(type));
  packet.append("-");
  packet.append(name);
  return packet;
}

string ClientPacketMaker::parseresponse(string response) {
  string parsedresponse;
  unsigned int divide1 = response.find("-");
  unsigned int divide2 = response.find("-",divide1+1);
  
  // Finding the type
  string typeStr = response.substr(0,divide1);
  if(!isInteger(typeStr)) {
    return "Wrong formatted message type: " + typeStr;
  }
  PacketType type = (PacketType)atoi(typeStr.c_str());
  string typeFormat = PacketTypeToString(type);

  // Finding the error code
  string codeStr;
  if (divide2 == string::npos) {
    codeStr = response.substr(divide1+1);
  }
  else {
    codeStr = response.substr(divide1+1,divide2-divide1-1);
  }
  if(!isInteger(codeStr)) {
    return "Wrong formatted error code: " + codeStr;
  }
  ErrCode errcode = (ErrCode)atoi(codeStr.c_str());
  string errcodeFormat = ErrCodeToString(errcode);

  // Check if it was good or not
  if (errcode < 0) {
    parsedresponse.append(typeFormat);
    parsedresponse.append(": Error of type ");
    parsedresponse.append(errcodeFormat);
  }
  else {
    parsedresponse.append(typeFormat);
    parsedresponse.append(": Success of type ");
    parsedresponse.append(errcodeFormat);
    parsedresponse.append("\nReturn:\n");
    if (divide2 == string::npos || response.size() >= divide2+1) {
      parsedresponse.append(""); // Add nothing
    }
    else {
      parsedresponse.append(response.substr(divide2+1));
    }
  }

  return parsedresponse;
}


// Server side packets
ServerPacketMaker::ServerPacketMaker() {
  worker = new ServerWorker();
}
// This is the super-function: It just takes in the packet and responds
// accordingly
string ServerPacketMaker::processpacket(string packet) {
  PacketType type = RESPONSE_UNKNOWN;

  // Find the first divide, which is always there in well formed packets
  unsigned int divide1 = packet.find("-");
  if (divide1 == string::npos) {
    return sendError(type);
  }

  // Parse out packet type
  string typeStr = packet.substr(0,divide1-1);
  if (!isInteger(typeStr)) {
    return sendError(type);
  }
  else {
    type = (PacketType)atoi(typeStr.c_str());
  }

  // We now give it off to the subfunctions since they know exactly how the
  // packet should be formatted
  switch(type) {
    case ZEROIZE:
      return zeroize();
    case ADDVOTER:
      return addvoter(packet);
    case VOTEFOR:
      return votefor(packet);
    case LIST:
      return listcandidates();
    case VOTECOUNT:
      return votecount(packet);
    default:
      return sendError(type);
  }
  return packet;
}

// The functions processpacket calls
// This code is used a lot, but so short it's not worth to put in a function
#define RESPSTART(response,type,errcode) \
  response.append(SSTR(type)); \
  response.append("-"); \
  response.append(SSTR(errcode));


string ServerPacketMaker::zeroize() {
  // First do it
  ErrCode errcode = worker->zeroize();
  string response;
  PacketType type = RESPONSE_ZEROIZE;
  RESPSTART(response,type,errcode);
  return response;
}

string ServerPacketMaker::addvoter(string packet) {
  static const unsigned int startPos = 2; // Know this beforehand
  PacketType type = RESPONSE_ADDVOTER;
  string response;

  // Tons and tons of error checking
  if (startPos >= packet.size())
    return sendError(type);
  string voteridStr = packet.substr(startPos+1);
  if (!isInteger(voteridStr))
    return sendError(type);

  // Finally get the id we need
  int voterid = atoi(voteridStr.c_str());

  // Do the actual calculation
  ErrCode errcode = worker->addvoter(voterid);
  RESPSTART(response,type,errcode);
  return response;
}

string ServerPacketMaker::votefor(string packet) {
  static const unsigned int startPos = 2; // Know this beforehand
  PacketType type = RESPONSE_VOTEFOR;
  string response;

  // So much error checking...
  unsigned int divide = packet.find("-",startPos);
  if (divide + 1 >= string::npos)
    return sendError(type);
  string voteridStr = packet.substr(startPos,divide-1);
  if (!isInteger(voteridStr))
    return sendError(type);

  // No errors!
  int voterid = atoi(voteridStr.c_str());
  string name = packet.substr(divide+1);

  // Do the actual work
  ErrCode errcode = worker->votefor(voterid,name);
  RESPSTART(response,type,errcode);
  return response;
}

string ServerPacketMaker::listcandidates() {
  vector<string> candidates = worker->listcandidates();
  PacketType type = RESPONSE_LIST;
  ErrCode errcode = OK;
  // Just get the candidates and send
  string response;
  RESPSTART(response,type,errcode);
  response.append("-");
  for(unsigned int i = 0; i < candidates.size(); ++i) {
    response.append(candidates[i]);
    response.append("\n");
  }
  response.append("\n");

  return response;
}

string ServerPacketMaker::votecount(string packet) {
  static const unsigned int startPos = 2; // Know this beforehand
  string response;
  PacketType type = RESPONSE_VOTECOUNT;
  ErrCode errcode = NOTACANDIDATE;

  // Simple error checking
  unsigned int divide = packet.find("-",startPos);
  if (divide + 1 >= string::npos)
    return sendError(type);
  string name = packet.substr(startPos,divide-1);


  int nvotes = worker->votecount(name);
  if (nvotes > 0)
    errcode = OK;
  RESPSTART(response,type,errcode);
  response.append("-");
  response.append(SSTR(nvotes));
  return response;
}

string ServerPacketMaker::sendError(PacketType type) {
  string response;
  response.append(PacketTypeToString(type));
  response.append("-");
  ErrCode errcode = ERROR;
  response.append(ErrCodeToString(errcode));
  return response;
}

// The C++ API uses exceptions to check for failure, which is just overkill, so
// this function just checks that it is an integer
bool isInteger(string s) {
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;
  char * p;
  strtol(s.c_str(), &p, 10);
  return (*p == 0);
}


