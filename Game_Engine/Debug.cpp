#include "Debug.h"
#include <chrono>
using namespace std::chrono;

std::string Debug::logFileName = "";

void Debug::DebugInit(const std::string& logFileName_) {
	logFileName = logFileName_;
	std::ofstream out;
	out.open(logFileName, std::ios::out);

	char str[26]; /// get the time and date
	system_clock::time_point p = system_clock::now();
	std::time_t result = system_clock::to_time_t(p);
    ctime_s(str,sizeof str,&result); /// Since C11
	out << str;

	out.close();
}

void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_) {
	std::ofstream out;
	std::string msg;
	out.open(logFileName, std::ios::out | std::ios::app);
	if (type_ == MessageType::TYPE_INFO) {
		msg = message_;
	} else {
		msg = message_ + " in file: " + fileName_ + " on line: " + std::to_string(line_);
	}
#ifdef _DEBUG
	std::cout << msg << std::endl;
#endif
	out << msg << std::endl;
	out.flush();
	out.close();
}

void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, fileName_, line_);
}