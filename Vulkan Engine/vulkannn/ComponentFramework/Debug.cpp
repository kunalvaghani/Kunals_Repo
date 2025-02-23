#include "Debug.h"
std::string Debug::fileName = "";

void Debug::DebugInit(const std::string& fileName_) {
	fileName = fileName_ + ".txt";
	std::ofstream out;
	out.open(fileName, std::ios::out);
	out << "";
	out.close();
}

void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_) {
	std::ofstream out;
	std::string msg;
	out.open(fileName, std::ios::out | std::ios::app);
	if (type_ == TYPE_INFO) {
		msg = message_;
	}
	else {
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