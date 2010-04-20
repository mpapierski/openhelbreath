/*
 This file is part of OpenHelbreath.
 OpenHelbreath is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenHelbreath is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenHelbreath.  If not, see <http://www.gnu.org/licenses/>.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUFFERS_H
#define BUFFERS_H

#include "NetSock.h"

class Buffer
{
	private:
		char * _data; //
		int _size; //
		int _pos; //
	public:
		Buffer(int iSize)
		{
			_data = new char[iSize];
			_size = iSize;
			clear();
			_pos = 0;
		}
		~Buffer()
		{
			delete[] _data;
		}

		inline void clear()
		{
			memset(_data, 0, _size);
			_pos = 0;
		}
		inline int const pos()
		{
			return _pos;
		}
		inline void pop(char*dest, int size)
		{
			memmove(dest, _data, size);
			memmove(_data, (char*) (_data + size), _size - size);
			_pos -= size;
		}
		inline int const size()
		{
			return _pos;
		}
		inline bool empty() const
		{
			return _pos == 0;
		}

		char* data() const
		{
			return _data;
		}

		char* writeptr() const
		{
			return _data + _pos;
		}

		inline unsigned int spaceAvailable() const
		{
			return _size - _pos;
		}

		void _written(unsigned int k)
		{
			_pos += k;
		}

		inline void seek(int where)
		{
			if (where < _pos)
				memmove(_data, _data + where, _size - where);
			_pos -= where;
		}

		template <typename T>
		inline T next()
		{
			T x;
			memcpy(&x, _data, sizeof(T));
			seek(sizeof(T));
			return x;
		}
		template <typename T>
		inline T* next(int len)
		{
			T* x = new T[len];
			memcpy(x, _data, len * sizeof(T));
			seek(len * sizeof(T));
			return x;
		}

		template <typename TS>
		inline void push(const TS* x, int len)
		{
			memcpy(_data + _pos, x, len * sizeof(TS));
			_pos += len * sizeof(TS);
		}
		template <typename TS>
		inline void push(const TS& x)
		{
			memcpy(_data + _pos, &x, sizeof(TS));
			_pos += sizeof(TS);
		}
		template <typename TS>
		inline void insert(const TS& x, int offset)
		{
			memcpy(_data + offset, &x, sizeof(TS));
		}
		inline void send(NetSock * sock)
		{
			if (!sock)
				return;
			sock->Write((unsigned char*) data(), size());
		}
		bool receive(NetSock * sock)
		{
			if (!sock)
				return false;
			int bytes = sock->Read((unsigned char*) writeptr(), spaceAvailable());
			if (bytes > 0)
				_written(bytes);
			return bytes > -1;
		}
};

class Packet: public Buffer
{
	private:
		unsigned short dwSize;
		inline void _setsize()
		{
			Buffer::insert<unsigned short>(dwSize, 1);
		}
	public:
		Packet(unsigned int MsgID, unsigned short MsgType) :
			Buffer(1024)
		{
			Buffer::push<unsigned char>(0);
			Buffer::push<unsigned short>(0);
			Buffer::push<unsigned int>(MsgID);
			Buffer::push<unsigned short>(MsgType);
			dwSize = 3 + 4 + 2;
			_setsize();
		}

		template <typename TS>

		void push(const TS* x, int len)
		{
			Buffer::push<TS>(x, len);
			dwSize += len;
			_setsize();
		}
		template <typename TS>
		void push(const TS& x)
		{
			Buffer::push<TS>(x);
			dwSize += sizeof(TS);
			_setsize();
		}
		inline int const size()
		{
			return dwSize;
		}
};
#endif
