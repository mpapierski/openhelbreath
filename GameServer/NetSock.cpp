// NetSock winsock helper class
// code by gynvael.coldwind//vx
// http://gynvael.vexillium.org
// http://vexillium.org
//
// Version: 2008-08-01
//
// LICENSE
// Permission is hereby granted to use, copy, modify, and distribute this
// source code, or portions hereof, for any purpose, without fee, subject
// to the following restrictions:
// 
// 1. The origin of this source code must not be misrepresented.
// 
// 2. Altered versions must be plainly marked as such and must not
//    be misrepresented as being the original source.
// 
// 3. This Copyright notice may not be removed or altered from any
//    source or altered source distribution. 
// 
// This software is provided AS IS. The author does not guarantee that 
// this program works, is bugfree, etc. The author does not take any
// responsibility for eventual damage caused by this program.
// Use at own risk.
//
#if defined(_WIN32) && !defined(WIN32)
#  define WIN32
#endif

#if defined(WIN32)
#  include <windows.h>
#  include <winsock.h>
#elif defined(__unix__)
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/un.h>
#  include <resolv.h>
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <unistd.h>
#  include <fcntl.h>
#  define closesocket(a) close(a)
#endif

#include <cstdlib>
#include "NetSock.h"

#ifdef _WIN32
typedef int socklen_t;
#endif

const int NetSock::SYNCHRONIC  = 1;
const int NetSock::ASYNCHRONIC = 2;

NetSock::NetSock()
{
  this->socket = -1;
  this->ip     = 0x00000000;
  this->mode   = 0;
  this->port   = 0;
  this->isUDP  = false;

  this->bindip   = 0;
  this->bindport = 0;

  this->str_ip[0] = '\0';
  this->str_bindip[0] = '\0';  
}

NetSock::~NetSock()
{
  this->Disconnect();
}

bool
NetSock::ListenUDP(unsigned short bindport, const char *bindhost)
{
  int ret;
  sockaddr_in desc;

  desc.sin_family = AF_INET;
  desc.sin_addr.s_addr = inet_addr(bindhost); // TODO: fix this
  desc.sin_port = htons(bindport);
  memset(desc.sin_zero, 0, sizeof(desc.sin_zero));

  ret = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(ret == -1)
    return false;

  this->socket = ret;
  this->bindport = bindport;
  this->bindip = htonl(desc.sin_addr.s_addr);

  this->isUDP = true;

  // bind ip it!
  if(bind(this->socket, (sockaddr*)&desc, sizeof(sockaddr)) == -1)
    return false;

  return true;
}

bool
NetSock::ListenAllUDP(unsigned short bindport)
{
  return this->ListenUDP(bindport, "0.0.0.0");
}

bool
NetSock::Listen(unsigned short port, const char *bindip)
{
  sockaddr_in desc;
  int ret;

  desc.sin_family = AF_INET;
  desc.sin_addr.s_addr = inet_addr(bindip);
  desc.sin_port = htons(port);

  ret = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(ret == -1)
    return false;

  this->socket = ret;

  if(bind(this->socket, (sockaddr*)&desc, sizeof(sockaddr)) == -1)
    return false;

  if(listen(this->socket, SOMAXCONN) == -1)
    return false;

  return true;
}

bool
NetSock::ListenAll(unsigned short port)
{
  sockaddr_in desc;
  int ret;

  desc.sin_family = AF_INET;
  desc.sin_addr.s_addr = inet_addr("0.0.0.0");
  desc.sin_port = htons(port);

  ret = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(ret == -1)
    return false;

  if(bind(this->socket, (sockaddr*)&desc, sizeof(sockaddr)) == -1)
    return false;

  if(listen(this->socket, SOMAXCONN) == -1)
    return false;

  return true;
}

NetSock *
NetSock::Accept()
{
 sockaddr_in desc;
  int remote;
#if defined(WIN32)
  int size;
#elif defined(__unix__)
  socklen_t size;
#endif

  size = sizeof(sockaddr);
  remote = accept(this->socket, (sockaddr*)&desc, &size);
  if(remote == -1)
    return NULL;

  NetSock *NewSock = new NetSock;

  NewSock->socket = remote;
  NewSock->port   = htons(desc.sin_port);
  memcpy(&NewSock->ip, &desc.sin_addr.s_addr, 4);

  return NewSock;
}

bool
NetSock::Connect(const char* host, unsigned short port)
{
  unsigned int ip;

  ip = (unsigned int)inet_addr(host);
  if(ip == INADDR_NONE)
  {
    struct hostent *hostip;

    // resolve
    hostip = gethostbyname(host);
    if(!hostip)
      return false;

    memcpy(&ip, hostip->h_addr_list[0], 4);
  }

  return this->Connect(htonl(ip), port);
}

bool 
NetSock::Connect(unsigned int ip, unsigned short port)
{
  struct sockaddr_in sock_info;
  int ret, sock = -1;

  if(this->socket != -1)
    throw "Socket already exists";

  ret = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(ret == -1)
    throw "Socket create failed";

  sock = ret;

  // sock info
  sock_info.sin_family = AF_INET;
  sock_info.sin_addr.s_addr = htonl(ip);
  sock_info.sin_port = htons(port);
  memset(sock_info.sin_zero, 0, sizeof(sock_info.sin_zero));

  // conn
  ret = connect(sock, (struct sockaddr*)&sock_info, sizeof( struct sockaddr ));
  if(ret == -1)
  {
    closesocket(sock);
    return false;
  }

  // ok
  this->ip = ip;
  this->port = port;
  this->mode = this->SYNCHRONIC;
  this->socket = sock;
  return true;
}
  
bool 
NetSock::SetMode(int mode)
{
  unsigned long mode_temp;
  if(this->socket == -1)
    return false;
  
  if(this->mode == mode)
    return true;

  switch(mode)
  {
    case NetSock::SYNCHRONIC:
      mode_temp = 0;
#if defined(WIN32)
      ioctlsocket(this->socket, FIONBIO, &mode_temp);
#else
      fcntl(this->socket, F_SETFL, 0);
#endif
      break;

    case NetSock::ASYNCHRONIC:
      mode_temp = 1;
#if defined(WIN32)
      ioctlsocket(this->socket, FIONBIO, &mode_temp);
#else
      fcntl(this->socket, F_SETFL, O_NONBLOCK);
#endif
      break;
  }

  this->mode = mode;
  return true;
}

bool 
NetSock::Disconnect()
{
  if(this->socket == -1)
    return false;

  closesocket(this->socket);
  this->socket = -1;
  this->ip     = 0x00000000;
  this->mode   = 0;
  this->port   = 0;
  return true;
}

int 
NetSock::Read(unsigned char *Buffer, int Size)
{
  if(this->socket == -1)
    return -1;

  return recv(this->socket, (char*)Buffer, Size, 0);
}

int 
NetSock::Write(unsigned char *Buffer, int Size)
{
  if(this->socket == -1)
    return -1;

  return send(this->socket, (char*)Buffer, Size, 0);
}

unsigned short 
NetSock::GetPort() const
{
  return this->port;
}

unsigned int
NetSock::GetIP() const
{
  return this->ip;
}

const char *
NetSock::GetStrIP()
{
  // cached ?
  if(this->str_ip[0])
    return this->str_ip;

  strncpy(this->str_ip, inet_ntoa(*(in_addr*)&this->ip), 16);
  this->str_ip[15] = '\0';
  return this->str_ip;
}

unsigned short 
NetSock::GetBindPort() const
{
  return this->bindport;
}

unsigned int 
NetSock::GetBindIP() const
{
  return this->bindip;
}

const char *
NetSock::GetStrBindIP()
{
  // cached ?
  if(this->str_bindip[0])
    return this->str_bindip;

  strncpy(this->str_bindip, inet_ntoa(*(in_addr*)&this->bindip), 16);
  this->str_bindip[15] = '\0';
  return this->str_bindip;
}

int
NetSock::WriteUDP(const char* host, unsigned short port, void *buffer, int size)
{
  // Sanity check
  if(this->socket == -1)
    return -1;

  // Address
  struct sockaddr_in sock_info;

  sock_info.sin_family = AF_INET;
  sock_info.sin_addr.s_addr = inet_addr(host); // Change this to 'host' later
  sock_info.sin_port = htons(port);

  memset(sock_info.sin_zero, 0, sizeof(sock_info.sin_zero));

#ifdef __unix__
  return sendto(socket, buffer, size, 0, (struct sockaddr*)&sock_info, sizeof(struct sockaddr));
#else
  return sendto(socket, (const char*)buffer, size, 0, (struct sockaddr*)&sock_info, sizeof(struct sockaddr));
#endif
}

int 
NetSock::ReadUDP(void *buffer, int size, char *srchost, unsigned short *srcport)
{
  // Sanity check
  if(this->socket == -1)
    return -1;

  // Recieve
  struct sockaddr_in srcaddr;
  socklen_t len = sizeof(srcaddr);
#ifdef __unix__
  int ret = recvfrom(socket, buffer, size, 0, (struct sockaddr*)&srcaddr, &len);
#else
  int ret = recvfrom(socket, (char*)buffer, size, 0, (struct sockaddr*)&srcaddr, &len);
#endif

  // Fill some info ?
  if(ret > 0)
  {
    if(srchost)
    {
      strncpy(srchost, inet_ntoa(srcaddr.sin_addr), 16); // htonl?
      srchost[15] = '\0';
    }

    if(srcport)
    {
      *srcport = htons(srcaddr.sin_port);
    }
  }

  // Done
  return ret;
}

