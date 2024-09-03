#include "ShipsExceptions.h"


ShipsException::ShipsException(const std::string& message)
	: message(message) { }


const char* ShipsException::what() const noexcept
{
	return message.c_str();
}
