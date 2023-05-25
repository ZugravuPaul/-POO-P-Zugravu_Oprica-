#include "DAL.h"






bool DAL::createUser(const User& user) {
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            INSERT INTO users (nume , prenume , username , password , email) VALUES (?, ?, ?, ?, ?);
        )");


	stmt.bind(0, user.nume.c_str());
	stmt.bind(1, user.prenume.c_str());
	stmt.bind(2, user.username.c_str());
	stmt.bind(3, user.password.c_str());
	stmt.bind(4, user.email.c_str());
	nanodbc::result rez = stmt.execute();

	return rez.has_affected_rows();
}

bool DAL::createBook(const Book& book, const char* userid) {
		
	if (this->verifyExistentbooks(book) == false) {
	    nanodbc::statement stmt(conn);
		nanodbc::prepare(stmt, R"(
            INSERT INTO Carti (Titlu , Autor , An_publicare) VALUES (?, ?, ?);
        )");


		stmt.bind(0, book.Titlu.c_str());
		stmt.bind(1, book.Autor.c_str());
		stmt.bind(2, book.An_publicare.c_str());

		nanodbc::result rez = stmt.execute();
	}
	nanodbc::statement stmt2(conn);
	nanodbc::prepare(stmt2, R"(
        INSERT INTO DetinatoriCarti (IdUser, IdCarte) VALUES (?, ?);
    )");

	stmt2.bind(0, userid);
	stmt2.bind(1, &book.id);
	nanodbc::result rez = stmt2.execute();
		
	return rez.has_affected_rows();
	
}

bool DAL::verifyExistentbooks(const Book& bookverif)
{
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            SELECT Id, Titlu, Autor FROM Carti;
        )");

	nanodbc::result result = stmt.execute();
	while (result.next()) {
		Book book;
		book.id = result.get<int>(0);
		book.Titlu = result.get<std::string>(1);
		book.Autor = result.get<std::string>(2);

		if (book.Titlu == bookverif.Titlu && book.Autor == bookverif.Autor)
			return true;
	}

	return false;
}

User DAL::getUserById(int id) {
	User user;
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
        SELECT id, username, email FROM users WHERE id = ?;
    )");
	stmt.bind(0, &id);

	nanodbc::result result = stmt.execute();

	const short columns = result.columns();
	//cout << "\nDisplaying " << result.rowset_size() << " rows "
	//    << "(" << result.rowset_size() << " fetched at a time):" << endl;

	//// show the column names
	//cout << "row\t";
	//for (short i = 0; i < columns; ++i)
	//    cout << result.column_name(i) << "\t";
	//cout << endl;

	if (result.next()) {
		user.id = result.get<int>(0);
		user.username = result.get<std::string>(1);
		user.email = result.get<std::string>(2);
	}

	return user;
}

bool DAL::updateUser(const User& user) {
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            UPDATE users SET username = ?, email = ? WHERE id = ?;
        )");

	stmt.bind(0, user.username.c_str());
	stmt.bind(1, user.email.c_str());
	stmt.bind(2, &user.id);

	nanodbc::result rez = stmt.execute();

	return rez.has_affected_rows();
}

bool DAL::deleteUser(int id) {
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            DELETE FROM users WHERE id = ?;
        )");

	stmt.bind(0, &id);

	nanodbc::result rez = stmt.execute();

	return rez.has_affected_rows();
}

bool DAL::verifyExistingUser(const User& userverif)
{
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            SELECT id, username, email FROM users;
        )");

	nanodbc::result result = stmt.execute();
	while (result.next()) {
		User user;
		user.id = result.get<int>(0);
		user.username = result.get<std::string>(1);
		user.email = result.get<std::string>(2);

		if (user.id == userverif.id || user.username == userverif.username || user.email == userverif.email)
			return true;
	}

	return false;
}

bool DAL::verifyRegisteredUser(const User& userverif)
{	
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            SELECT username, password FROM users WHERE username=? AND password=?;
        )");
	stmt.bind(0, userverif.username.c_str());
	stmt.bind(1, userverif.password.c_str());
	nanodbc::result result = stmt.execute();
	while (result.next()) {
		User user;
		user.username = result.get<std::string>(0);
		user.password = result.get<std::string>(1);
		
		if (user.username == userverif.username && user.password == userverif.password)
			return true;
	}
	return false;
}

vector<User> DAL::getUsersByEmail(const std::string& email)
{
	std::vector<User> users;
	nanodbc::statement stmt(conn);
	nanodbc::prepare(stmt, R"(
            SELECT id, username, email FROM users WHERE email LIKE ?;
        )");

	std::string email_pattern = "%" + email + "%";
	stmt.bind(0, email_pattern.c_str());

	nanodbc::result result = stmt.execute();

	while (result.next()) {
		User user;
		user.id = result.get<int>(0);
		user.username = result.get<std::string>(1);
		user.email = result.get<std::string>(2);
		users.push_back(user);
	}

	return users;
}
string DAL::ProcessPOST_Request(const User& newUser) {
	

	if (this->verifyExistingUser(newUser) == false) {
			if (this->createUser(newUser)) {
		        return "User created successfully.\n";
		    }
		     else {
		        return "Error creating user.\n";
	        }
	}
	return "Error! User already exists!.\n";
	
}

string DAL::ProcessLOGIN_Request(const User& user)
{
	if (this->verifyRegisteredUser(user) == false)
		return "false";
	return "true";
}


//void DAL::ProcessClientRequest(const std::string& request, const User& user)
//{
//    // Create a new user
//    User newUser{ "John Doeeee", "johndoeeee@example.com" };
//    if (this->verifyExistingUser(newUser) == false) {
//        if (this->createUser(newUser)) {
//            std::cout << "User created successfully.\n";
//        }
//        else {
//            std::cout << "Error creating user.\n";
//        }
//    }
//    else
//        std::cout << "Error! User already exists!.\n";
//
//    // Fetch user by ID
//    User fetchedUser = this->getUserById(4);
//    std::cout << "Fetched user: " << fetchedUser.id << ", " << fetchedUser.username << ", " << fetchedUser.email << '\n';
//
//    // Update user
//    fetchedUser.username = "Jake Doedel";
//    fetchedUser.email = "jakedoe@example.com";
//    if (this->updateUser(fetchedUser)) {
//        std::cout << "User updated successfully.\n";
//    }
//    else {
//        std::cout << "Error updating user.\n";
//    }
//
//    // Fetch users by email
//    std::vector<User> users = this->getUsersByEmail("jakedoe@example.com");
//    for (const auto& user : users) {
//        std::cout << "User found: " << user.id << ", " << user.username << ", " << user.email << '\n';
//    }
//
//    // Delete user
//    if (this->deleteUser(4)) {
//        std::cout << "User deleted successfully.\n";
//    }
//    else {
//        std::cout << "Error deleting user.\n";
//    }
//}




void DAL::disconnect() {
	if (conn.connected()) {
		conn.disconnect();
		conn.deallocate();
	}
}


