// NetSock winsock helper class
// code by gynvael.coldwind//vx
// http://gynvael.vexillium.org
// http://vexillium.org
//
// Version: 2007-11-01
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
#pragma once
#ifdef __unix__
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/un.h>
#else
#  include <windows.h>
#  include <winsock.h>
#endif
#include <cstdio>

using namespace std;

class NetSock
{
private:
  unsigned int    ip;
  unsigned short  port;

  unsigned int    bindip;
  unsigned int    bindport;

  int   mode;
  int   socket;
  char  str_ip[16], str_bindip[16];

  bool  isUDP;

public:
  NetSock();
  ~NetSock();

  static const int SYNCHRONIC;
  static const int ASYNCHRONIC;

  bool ListenUDP(unsigned short bindport, const char *bindhost);
  bool ListenAllUDP(unsigned short bindport);

  bool Connect(const char* host, unsigned short port);
  bool Connect(unsigned int ip, unsigned short port);
  bool SetMode(int mode);
  bool Disconnect();
  bool Listen(unsigned short port, const char *bindip);
  bool ListenAll(unsigned short port);
  NetSock *Accept();
  int Read(unsigned char *Buffer, int Size);
  int Write(unsigned char *Buffer, int Size);
  
  int WriteUDP(const char* host, unsigned short port, void *buffer, int size);
  int ReadUDP(void *buffer, int size, char *srchost, unsigned short *srcport);

  unsigned short GetPort() const;
  unsigned int GetIP() const;
  const char *GetStrIP();

  unsigned short GetBindPort() const;
  unsigned int GetBindIP() const;
  const char *GetStrBindIP();


};

