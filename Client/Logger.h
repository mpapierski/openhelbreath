#ifndef LOGGER_H_
#define LOGGER_H_
#include <string>
#include <fstream>
#include <sstream>
#include <dir.h>

class Log {
   public:
   explicit Log() :
          msg("", std::ios_base::out | std::ios_base::ate)
   {}

   ~Log();

   template<typename T>
   Log& operator<<(const T& t) {
      msg << t;
      return *this;
   }

   Log& operator<<(std::ostream& (*t)(std::ostream&)) {
      msg << t;
      return *this;
   }
   Log& operator<<(std::ios& (*t)(std::ios&)) {
      msg << t;
      return *this;
   }
   Log& operator<<(std::ios_base& (*t)(std::ios_base&)) {
      msg << t;
      return *this;
   }

   inline std::string getMsg() const { return msg.str(); }

   private:
		std::ostringstream msg;
};


class Debugger : public Log
{
	public:
		Debugger(std::string Func, std::string Src, int Line);
};

#define Debug() Debugger( __func__ , __FILE__ , __LINE__ )

#endif /* LOGGER_H_ */
