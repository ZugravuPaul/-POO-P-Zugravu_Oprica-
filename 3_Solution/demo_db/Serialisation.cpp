#include "Serialisation.h"



string Serialisation::find_request(const std::string& data_received)
{
	json j;
	
	try {
		j = json::parse(data_received);
		this->request = j["request"];
	}
	catch (const std::exception& e) {
		string msg1 = "Failed to deserialize object: ";
		string msg2=e.what();
		return msg1+msg2+"\n";
	}
	
	if(this->request == "POST_USER") {
		
		User* user = new User(j["nume"], j["prenume"], j["username"], j["password"], j["email"]);
		return DAL::getInstance().ProcessPOST_Request(*user); //can return a string message
	}
	if (this->request == "LOGIN_USER") {

		User* user = new User(j["username"],j["password"]);
		return DAL::getInstance().ProcessLOGIN_Request(*user);
	}
	if (this->request == "POST_BOOK") {
		Book* book = new Book(j["Titlu"], j["Autor"], j["An_publicare"]);
		string buff = j["IdUser"];
		if (DAL::getInstance().createBook(*book, buff.c_str()) == true)
			return "Carte adaugata!";
		return "Eroare!";
		
	}
}

std::string Serialisation::Serialize(User& user)
{
	/*json j;
	j["id"] = user.id;
	j["username"] = user.username;
	j["password"] = user.password;
	j["email"] = user.email;
	return j.dump();*/
	return string();
}
