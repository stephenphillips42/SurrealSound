// Standard headers
#include <string>
#include <stdlib.h>
#include <iostream>
// For networking things
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
// My headers
#include "packetmaker.h"
#include "server.h"
#include "errorcode.h"

// Thank you Stack Overflow! For stringifying objects
#include <sstream>
#define SSTR( x ) ((dynamic_cast< std::ostringstream & > \
        ( std::ostringstream() << std::dec << x )).str()) 

#define DELIM ":"

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
    case TRUEVALUE:
      return "TRUE";
    case NEW:
      return "NEW";
    case EXISTS:
      return "EXISTS";
    case ERROR:
      return "ERROR";
    case FALSEVALUE:
      return "FALSE";
    case NOTAVOTER:
      return "NOTAVOTER";
    case NOTACANDIDATE:
      return "NOTACANDIDATE";
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
  packet.append(DELIM);
  return packet;
}

string ClientPacketMaker::addvoter() {
  string packet;
  PacketType type = ADDVOTER;
  packet.append(SSTR(type));
  packet.append(DELIM);
  packet.append(SSTR(id));
  return packet;
}

string ClientPacketMaker::votefor(std::string name) {
  string packet;
  PacketType type = VOTEFOR;
  packet.append(SSTR(type));
  packet.append(DELIM);
  packet.append(SSTR(id));
  packet.append(DELIM);
  packet.append(name);
  return packet;
}

string ClientPacketMaker::listcandidates() {
  string packet;
  PacketType type = LIST;
  packet.append(SSTR(type));
  packet.append(DELIM);
  return packet;
}

string ClientPacketMaker::votecount(std::string name) {
  string packet;
  PacketType type = VOTECOUNT;
  packet.append(SSTR(type));
  packet.append(DELIM);
  packet.append(name);
  return packet;
}

string ClientPacketMaker::parseresponse(string response) {
  string parsedresponse;
  unsigned int divide1 = response.find(DELIM);
  unsigned int divide2 = response.find(DELIM,divide1+1);
  
  // Finding the type
  string typeStr = response.substr(0,divide1);
  if(!isInteger(typeStr)) {
    return "Wrong formatted message type: " + typeStr;
  }
  PacketType type = (PacketType)atoi(typeStr.c_str());
  string typeFormat = PacketTypeToString(type);

  // Finding the error code
  string codeStr;
  if (divide2 > response.size()) {
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
    if (divide2 > response.size()) { //  || response.size() >= divide2+1) {
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
  unsigned int divide1 = packet.find(DELIM);
  if (divide1 > packet.size()) {
    cerr << "Can't find -" << endl;
    return sendError(type);
  }

  // Parse out packet type
  string typeStr = packet.substr(0,divide1);
  if (!isInteger(typeStr)) {
    cerr << "Invalid formated type: " << typeStr << endl;
    cerr << "Divide is " << divide1 << endl;

    return sendError(type);
  }
  else {
    type = (PacketType)atoi(typeStr.c_str());
  }

  // We now give it off to the subfunctions since they know exactly how the
  // packet should be formatted
  switch(type) {
    case ZEROIZE:
      cerr << "Working on zeroize" << endl;
      return zeroize();
    case ADDVOTER:
      cerr << "Working on addvoter" << endl;
      return addvoter(packet);
    case VOTEFOR:
      cerr << "Working on votefor" << endl;
      return votefor(packet);
    case LIST:
      cerr << "Working on listcandidates" << endl;
      return listcandidates();
    case VOTECOUNT:
      cerr << "Working on votecount" << endl;
      return votecount(packet);
    default:
      cerr << "Working on sendError" << endl;
      return sendError(type);
  }
  return packet; // So this should never get here...
}

// The functions processpacket calls
// This code is used a lot, but so short it's not worth to put in a function
#define RESPSTART(response,type,errcode) \
  response.append(SSTR(type)); \
  response.append(DELIM); \
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
  if (startPos >= packet.size()) {
    cerr << "Packet too small to parse" << endl;
    return sendError(type);
  }
  string voteridStr = packet.substr(startPos);
  if (!isInteger(voteridStr)) {
    cerr << "Voter ID is not a integer: " << voteridStr << endl;
    return sendError(type);
  }

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
  unsigned int divide = packet.find(DELIM,startPos);
  if (divide + 1 >= string::npos) {
    cerr << "Nothing in the second part of packet: " << packet << endl;
    return sendError(type);
  }
  string voteridStr = packet.substr(startPos,divide-startPos);
  if (!isInteger(voteridStr)) {
    cerr << "Voter ID is not a integer: " << voteridStr << endl;
    return sendError(type);
  }

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
  response.append(DELIM);
  for(unsigned int i = 0; i < candidates.size(); ++i) {
    response.append(candidates[i]);
    response.append("\n");
  }
  response.append("\n");
  cout << response << endl;

  return response;
}

string ServerPacketMaker::votecount(string packet) {
  static const unsigned int startPos = 2; // Know this beforehand
  string response;
  PacketType type = RESPONSE_VOTECOUNT;
  ErrCode errcode = NOTACANDIDATE;

  // Simple error checking
  unsigned int divide = packet.find(DELIM,startPos);
  if (divide + 1 >= string::npos) {
    cerr << "Nothing in the second part of packet: " << packet << endl;
    return sendError(type);
  }
  string name = packet.substr(startPos,divide-startPos);


  int nvotes = worker->votecount(name);
  if (nvotes >= 0)
    errcode = OK;
  RESPSTART(response,type,errcode);
  response.append(DELIM);
  response.append(SSTR(nvotes));
  return response;
}

string ServerPacketMaker::sendError(PacketType type) {
  string response;
  response.append(SSTR(type));
  response.append(DELIM);
  ErrCode errcode = ERROR;
  response.append(SSTR(errcode));
  return response;
}

// Helper functions

// The C++ API uses exceptions to check for failure, which is just overkill, so
// this function just checks that it is an integer
bool isInteger(string s) {
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;
  char * p;
  strtol(s.c_str(), &p, 10);
  return (*p == 0);
}


// Help for the clients - automatic packet sender
string sendPacket(char* dest_ip, char* dest_port, string packet, int socktype) {
  // Get address matching intput arguments
  addrinfo hints;
  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
  // Socket type - the only thing that changes between TCP and UDP
  hints.ai_socktype = socktype;
  hints.ai_flags = 0;
  hints.ai_protocol = 0; // Any protocol

  addrinfo *saddr;
  if (getaddrinfo(dest_ip, dest_port, &hints, &saddr) < 0) {
    cerr << "Error with getaddrinfo" << endl;
    exit(EXIT_FAILURE);
  }
  if (saddr == NULL) {               // No address succeeded
    cerr << "Could not connect" << endl;
    exit(EXIT_FAILURE);
  }

  // So while getaddrinfo returns multiple, I just ignore all the other ones
  // return the first one.
  int ssocket =
        socket(saddr->ai_family, saddr->ai_socktype, saddr->ai_protocol);
  if (ssocket < 0) {
    cerr << "Failed to create socket to server" << endl;
    exit(EXIT_FAILURE);
  }
  if (connect(ssocket, saddr->ai_addr, saddr->ai_addrlen) < 0) {
    cerr << "Could not connect to server" << endl;
    close(ssocket);
    exit(EXIT_FAILURE);
  }

  // Write and read are the same as send/sendto and recv/recvfrom with no
  cout << "Packet: " << packet << endl;
  if (write(ssocket, packet.c_str(), packet.size()+1)
        != (unsigned)(packet.size()+1)) {
    cerr << "Partial/failed write" << endl;
    close(ssocket);
    exit(EXIT_FAILURE);
  }

  char buf[MAXLEN];
  ssize_t nread = read(ssocket, buf, MAXLEN);
  if (nread < 0) {
    perror("read");
    close(ssocket);
    exit(EXIT_FAILURE);
  }
  close(ssocket);

  return string(buf);
}

string sendPacketUDP(char* dest_ip, char* dest_port, string packet) {
  return sendPacket(dest_ip, dest_port, packet, SOCK_DGRAM);
}

string sendPacketTCP(char* dest_ip, char* dest_port, string packet) {
  return sendPacket(dest_ip, dest_port, packet, SOCK_STREAM);
}
