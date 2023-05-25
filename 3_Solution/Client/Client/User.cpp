#include "User.h"

std::string User::SerializeUser()
{
    json j;
    j["id"] = this->id;
    j["username"] = this->username;
    j["password"] = this->password;
    j["email"] = this->email;
    return j.dump();
}

void User::Deserialize(const std::string& serializedUser)
{
	User user;
	try {
		json j = json::parse(serializedUser);
		user.id = j["id"];
		user.username = j["username"];
		user.password = j["password"];
		user.email = j["email"];
	}
	catch (const std::exception& e) {
		std::cout << "Failed to deserialize User object: " << e.what() << std::endl;
	}
	*this = user;
}
