#include<iostream>
#include<pqxx/pqxx>
#include <string>
#include "VariadicTable.h"



using namespace std;
using namespace pqxx;

class hotel {
public:
	string sql, category, input, room, floor, type, price, user_name, ps_word, email_id, name, ph_num, hotel_id, hotel_name, is_available, psw;
	string connectionC = "dbname = HOTEL user = postgres password = admin@123 hostaddr = 127.0.0.1 port = 5432";
	void display();
	void displaytable();
	void search();
	void bookroom();
	void update();
	void add();
	int login();
	int signup();
	void addperson();
	void deleteroom();
	void deleteuser();
	void userdetails();
	void updateusers();
};

int hotel::login()
{
	pqxx::connection C(connectionC.c_str());
	char option;
	int sign_up;
	cout << "a) sign in as a guest:-\t\nb) sign up as new member:-\t\nc) sign in as authorizes person:-";
	cin >> option;

	switch (option) {
	case 'a':
	case 'A':
	{

		cout << "enter the user name  :" << endl;
		cin >> user_name;
		cout << "enter the password  :" << endl;
		cin >> ps_word;
		cout << "    ";
		sql = "SELECT password FROM users WHERE username = '" + user_name + "'";
		work W(C);
		pqxx::result R = W.exec(sql);

		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			psw = c[0].as<string>();

		}
		
		W.commit();
		if (psw == ps_word)
		{
			return 0;
		}
		else
			return 1;
		break;
	}
	case'b':
	case 'B':
	{
		sign_up = signup();
		return sign_up;
		break;
	}

	case'c':
	case 'C':
	{
		cout << "enter authorized id : ";
		cin >> user_name;
		cout << "enter password : ";
		cin >> ps_word;
		sql = "SELECT password FROM users WHERE username = 'jenny.2'";
		work W(C);
		pqxx::result R = W.exec(sql);

		for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
			psw = c[0].as<string>();
		}
		W.commit();
		if (psw == ps_word)
		{
			return 2;
		}
		else
		{
			return 1;
		}
		break;
	}
	default: 
		cout << "invalid option ";
		break;
	}
}



int hotel::signup()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the name  :" << endl;
	cin >> name;
	cout << "enter the email id  :" << endl;
	cin >> email_id;
	cout << "enter the user name  :" << endl;
	cin >> user_name;
	cout << "enter the phone number  :" << endl;
	cin >> ph_num;
	cout << "enter the password  :" << endl;
	cin >> ps_word;
	sql = "INSERT INTO users (name,email_address,phone_number,username,password) "
		"VALUES ('"+name+"','"+email_id+"','"+ph_num+"','"+user_name+"','"+ps_word+"'); ";

	/* Create a transactional object. */
	work W(C);

	/* Execute SQL query */

	W.exec(sql);
	W.commit();
	return 0;
}


void hotel::display()
{
	pqxx::connection C(connectionC.c_str());
	sql = "SELECT * from AVAILABLE_HOTELS ";

	/* Create a non-transactional object. */
	nontransaction N(C);
	/* Execute SQL query */
	result R(N.exec(sql));

	VariadicTable<string, string, string, string> vt({ "hotel_id", "hotel_name", "no_of_rooms", "type" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>());
	}


	vt.print(cout);
	cout << " ";
	cout << " ";



}


void hotel::displaytable()
{
	pqxx::connection C(connectionC.c_str());
	sql = "SELECT * from ROOM";

	/* Create a non-transactional object. */
	nontransaction N(C);
	/* Execute SQL query */
	result R(N.exec(sql));
	VariadicTable<string, string, string, string, string, string> vt({ "hotel_id", "hotel_name", "room_number", "price", "floor","is_available" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>(), c[5].as<string>());
	}


	vt.print(cout);

	cout << " ";


}

void hotel::search()
{
	pqxx::connection C(connectionC.c_str());
	cout << "category to search: ";
	cin >> category;
	cout << " your choice: ";
	cin >> input;
	cout << "     ";
	cout << "    ";


	sql = "SELECT * from  ROOM where " + category + " = '" + input + "' ";
	/* Create a non-transactional object. */
	nontransaction N(C);

	/* Execute SQL query */
	result R(N.exec(sql));

	VariadicTable<string, string, string, string, string, string> vt({ "hotel_id", "hotel_name", "room_number", "price", "floor", "is_available" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>(), c[5].as<string>());
	}

	vt.print(cout);




}

void hotel::bookroom()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to book: ";
	cin >> room;
	cout << "    ";
	cout << "    ";

	sql = "SELECT is_available FROM ROOM WHERE ROOM_NUMBER = '" + room + "'";
	work W(C);
	pqxx::result R = W.exec(sql);

	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		psw = c[0].as<string>();
	}
	W.commit();

	if (psw == "yes")
	{
		sql = "UPDATE ROOM set  is_available   = 'no' where room_number ='"+room+"'";

		/* Execute SQL query */
		work W(C);
		W.exec(sql);
		W.commit();
		cout << "YOUR ROOM HAS BEEN BOOKED SUCCESSFULLY\n\n";
		cout << "    ";
	}
	else
	{
		cout << "ROOM IS UNAVAILABLE\n\n";
	}

}

void hotel::deleteroom()
{
	
	pqxx::connection C(connectionC.c_str());
	cout << "which room number to remove : " << endl;
	cin >> room;
	cout << "   " << endl;
	
	/* Create  SQL DELETE statement */
	sql = "DELETE from  ROOM where ROOM_NUMBER = '" + room + "' ";
	/* Execute SQL query */
	work W(C);
	W.exec(sql);
	W.commit();
	cout << "   " << endl;
	cout << "room number :"<<room<<" removed successfully" << endl;
	cout << "   " << endl;
}

void hotel::deleteuser()
{
	
	pqxx::connection C(connectionC.c_str());
	cout << "which username to remove : " << endl;
	cin >>user_name;
	cout << "   " << endl;

	/* Create  SQL DELETE statement */
	sql = "DELETE from USERS where USERNAME ='"+user_name+"'";
	/* Execute SQL query */
	work W(C);
	W.exec(sql);
	W.commit();
	cout << "   " << endl;
	cout << "user :" << user_name<< " removed successfully" << endl;
	cout << "   " << endl;
}
void hotel::userdetails()
{
	pqxx::connection C(connectionC.c_str());
	sql = "SELECT * from USERS";

	/* Create a non-transactional object. */
	nontransaction N(C);
	/* Execute SQL query */
	result R(N.exec(sql));
	VariadicTable<string, string, string, string, string> vt({ "name", "email-address", "phone_number", "username", "password" });
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		vt.addRow(c[0].as<string>(), c[1].as<string>(), c[2].as<string>(), c[3].as<string>(), c[4].as<string>() );
	}


	vt.print(cout);

	cout << " ";

}

void hotel::update()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to update: ";
	cin >> room;
	cout << "enter the category to update: ";
	cin >> category;
	cout << "enter the new value to update: ";
	cin >> input;
	cout << "    ";

	/* Create a transactional object. */

	sql = "UPDATE ROOM set  "+category+"  = '"+input+"' where room_number = '"+room+"' ";

	/* Execute SQL query */
	work W(C);
	W.exec(sql);
	W.commit();


}

     
void hotel::updateusers()
{
	pqxx::connection C(connectionC.c_str());
	cout << "enter the username to update: ";
	cin >> user_name;
	cout << "enter the category to update: ";
	cin >> category;
	cout << "enter the new value to update: ";
	cin >> input;
	cout << "    ";

	/* Create a transactional object. */

	sql = "UPDATE users set  "+category+"  = '"+input+ "' where username = '"+user_name+"' ";

	/* Execute SQL query */
	work W(C);
	W.exec(sql);
	W.commit();

}
      

void hotel::add()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the room number to add: ";
	cin >> room;
	cout << "enter the hotel id: ";
	cin >> hotel_id;
	cout << "enter the hotel name : ";
	cin >> hotel_name;
	cout << "enter the floor: ";
	cin >> floor;
	cout << "enter the price: ";
	cin >>price;
	cout << "    ";
	cout << "enter the availability status: ";
	cin >> is_available;
	cout << "    ";
	sql = "INSERT INTO room (hotel_id, hotel_name, room_number, price, floor, is_available) "
		"VALUES ('"+hotel_id+"','"+hotel_name+"', '"+room+"', '"+price+"','"+floor+"','"+is_available+"');";

	/* Create a transactional object. */
	work W(C);

	/* Execute SQL query */
	W.exec(sql);
	W.commit();
}

void hotel::addperson()
{
	pqxx::connection C(connectionC.c_str());

	cout << "enter the name  :" << endl;
	cin >> name;
	cout << "enter the email id  :" << endl;
	cin >> email_id;
	cout << "enter the user name  :" << endl;
	cin >>user_name;
	cout << "enter the phone number  :" << endl;
	cin >> ph_num;
	cout << "enter the password  :" << endl;
	cin >> ps_word;
	sql = "INSERT INTO users (name, email_address, phone_number, username, password) "
		"VALUES ('"+name+"','"+email_id+"','"+ph_num+"','"+user_name+"','"+ps_word+"'); ";

	/* Create a transactional object. */
	work W(C);

	/* Execute SQL query */

	W.exec(sql);
	W.commit();
}






int main()
{
	hotel p;
	
	string  choice;
	int LoginVariable;
	LoginVariable = p.login();
	if (LoginVariable == 0)
	{

		cout << " opened database successfully " << endl;
		cout << " ";
		cout << " ";
		cout << "--------------------------------------------------------" << endl;
		cout << "    HOTELS AVAILABLE" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << " ";

		p.display();
		p.displaytable();

		do {

			cout << " ";
			cout << " ";
			cout << "--------------------------------------------------------" << endl;
			cout << "OPERATIONS :- " << endl;
			cout << "--------------------------------------------------------" << endl;
			
			cout << "a).book a room :\nb).search a room\nc).display list " << endl;
			cout << " ";
			cin >> choice;
			if ((choice == "a") || (choice == "A"))
			{
				p.bookroom();
				cout << " ";
				cout << " ";
				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;

			}

			else if ((choice == "b") || (choice == "B"))
			{
				p.search();
				cout << " ";
				cout << " ";
				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
			}

		
			else if ((choice == "c") || (choice == "C"))
			{
				p.display();
				p.displaytable();
				cout << " ";
				cout << " ";
				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}
			else {

				cout << "wrong choice" << endl;
				cout << " ";
				cout << " ";
				cout << "do you want to continue the function:- (yes/no)" << endl;
				cin >> choice;
				cout << "   " << endl;
				cout << "   " << endl;
				cout << "   " << endl;
			}

		} while ((choice.compare("yes") == 0) || (choice.compare("YES") == 0));

	}
	else if (LoginVariable == 2)   //receptionist
{
cout << " opened database successfully " << endl;
p.display();

p.displaytable();

    do {

	cout << " ";
	cout << " ";
	cout << "--------------------------------------------------------" << endl;
	cout << "OPERATIONS :- " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "a).book a room :\nb).search a room\nc).update\nd).add a room\ne).display the hotel list\nf).add a person\ng).remove a room\nh).remove a person\ni).userdetails\nj).update user details " << endl;
	cout << " ";
	cin >> choice;
	if ((choice == "a") || (choice == "A"))
	{
		p.bookroom();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;

	}

	else if ((choice == "b") || (choice == "B"))
	{
		p.search();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}

	else if ((choice == "c") || (choice == "C"))
	{
		p.update();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
		cout << "   " << endl;
		cout << "   " << endl;
	}

	else if ((choice == "d") || (choice == "D"))
	{
		p.add();
		
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
		cout << "   " << endl;

	}
	else if ((choice == "e") || (choice == "E"))
	{
		p.display();
		p.displaytable();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
		cout << "   " << endl;
		cout << "   " << endl;
	}
	else if ((choice == "f") || (choice == "F"))
	{
		p.addperson();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}
	else if ((choice == "g") || (choice == "G"))
	{   
		p.displaytable();
		p.deleteroom();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}
	else if ((choice == "h") || (choice == "H"))
	{
		p.userdetails();
		p.deleteuser();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}
	else if ((choice == "i") || (choice == "I"))
	{
		p.userdetails();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}
	else if ((choice == "j") || (choice == "J"))
	{
		p.userdetails();
		p.updateusers();
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
	}

	else {

		cout << "wrong choice" << endl;
		cout << " ";
		cout << " ";
		cout << "do you want to continue the function:- (yes/no)" << endl;
		cin >> choice;
		cout << "   " << endl;
		cout << "   " << endl;
		cout << "   " << endl;
	}

} while ((choice.compare("yes") == 0) || (choice.compare("YES") == 0));
	}



	else {
		cout << "Can't open database" << endl;

	}
	return 0;
}