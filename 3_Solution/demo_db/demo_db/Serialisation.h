#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include "DAL.h"
#include <nlohmann/json.hpp>
#include "User.h"
#include "Book.h"

using json = nlohmann::json;

class Serialisation
{private:
	string request;

public:
	std::string find_request(const std::string& data_received);
	std::string Serialize(User& user);
};



