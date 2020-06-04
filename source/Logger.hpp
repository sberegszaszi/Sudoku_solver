#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include "Timer.hpp"

class Logger
{
private:
	std::ofstream logFile;
public:
    Logger() = delete;
	Logger(std::string const file): logFile{file}
	{
		if (!logFile.is_open()){
			throw std::runtime_error(std::string{"Unable to open log file"});
		}
	}
	Logger(Logger const &) = delete;
    Logger & operator=(Logger const &) = delete;
	Logger(Logger &&) = default;
	Logger & operator=(Logger &&) = delete;
	~Logger(){ logFile.close();	}

    template<typename T>
	void writeWithTC(const T & data);

	template<typename T>
    friend Logger& operator<<(Logger & log, const T & data);
};

template<typename T>
void Logger::writeWithTC(const T & data)
{
	auto now = std::chrono::system_clock::now();
	auto now_t = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	logFile << std::put_time(std::localtime(& now_t), "[%X.");
	logFile << std::setw(3) << std::setfill('0') << ms.count() << "] ";
	logFile << data << std::endl;
}

template<typename T>
Logger& operator<<(Logger & log, const T & data)
{
		log.logFile << data;
		return log;
}

#endif // LOGGER_HPP