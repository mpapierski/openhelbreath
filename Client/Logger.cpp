#include "Logger.h"
#include "Game.h"

Log::~Log()
{
	puts(msg.str().c_str());
}

Debugger::Debugger(std::string Func, std::string Src, int Line):
	Log()
{
	for (unsigned int i = 0; i < Src.length(); i++)
		if (Src[i] == '/')
			Src[i] = '\\';
	Src = Src.substr(Src.find_last_of('\\') + 1);
	(*this) << "[" << Func << "@" << Src << ":" << Line << "] ";
}
