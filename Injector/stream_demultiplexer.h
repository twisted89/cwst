#pragma once
#include <vector>
#include <ostream>
class stream_demultiplexer
{
private:
	typedef std::vector<std::ostream*> str_cont;
	str_cont d;
public:
	stream_demultiplexer& put(std::ostream::char_type ch)
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
		{
			(*it)->put(ch);
		}
		return *this;
	}

	stream_demultiplexer& write(const std::ostream::char_type* s, std::streamsize count)
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
		{
			(*it)->write(s, count);
		}
		return *this;
	}

	stream_demultiplexer& flush()
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
			(*it)->flush();
		return *this;
	}


	template<typename T>
	stream_demultiplexer& operator<<( const T& obj )
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
			(**it) << obj;
		return *this;
	}

	stream_demultiplexer& operator<<(std::ios_base& (*func)(std::ios_base&))
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
			(**it)<< func;
		return *this;
	}

	template<typename CharT, typename Traits>
	stream_demultiplexer& operator<<(std::basic_ios<CharT,Traits>& (*func)(std::basic_ios<CharT,Traits>&) )
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
			(**it) << getPrependTime() << func;
		return *this;
	}

	stream_demultiplexer& operator<<(std::ostream& (*func)(std::ostream&) )
	{
		for(str_cont::iterator it = d.begin(); it != d.end(); ++it)
			(**it) << func;
		return *this;
	}

	void add_stream(std::ostream& ss)
	{
		d.push_back(&ss);
	}

	std::string getPrependTime(void)
	{
		time_t now;
		char the_date[12];

		the_date[0] = '\0';

		now = time(NULL);

		if (now != -1)
		{
			strftime(the_date, 12, "%H:%M ", gmtime(&now));
		}

		return std::string(the_date);
	}
};

