#include<windows.h> 
#include<iostream>
#include<string>
#include <fstream>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

class Customer {

public:
	string name;
	string username;
	string password;
	double phoneno;
	string email;
	string address;
	string filename;

public:
	void getcustomer() {
		cin.ignore();
		cout << "Enter username: ";
		getline(cin, username);
		filename = username + ".txt";

		fstream customer(filename, ios::out);
		if (customer.is_open()) {
			cout << "Enter password: ";
			getline(cin, password);
			cout << "Enter full name: ";
			getline(cin, name);
			cout << "Enter phone number: ";
			cin >> phoneno;
			cin.ignore();
			cout << "Enter email: ";
			getline(cin, email);
			cout << "Enter address: ";
			getline(cin, address);

			customer << username << endl;
			customer << password << endl;
			customer << name << endl;
			customer << phoneno << endl;
			customer << email << endl;
			customer << address << endl;

			customer.close();
			cout << "Customer data saved successfully!\n";
		}
		else {
			cout << "Error opening file!\n";
		}
	}
	void showcustomer() {
		cout << "name is" << name << endl;
		cout << "username is " << username << endl;
		cout << "Contact details" << "   \n" << "phone no" << phoneno << "\n" << "email is" << email << endl;
		cout << "your address is" << endl;
		cout << address;
		cout << endl;
	}
};
class login {
private:
	Customer C;
	int loginselect;
	string enterusername;
	string enterpassword;
public:
	void select() {
		cout << "press 1 for log in and press 2 for sign up";
		cin >> loginselect;
		cin.ignore();
		if (loginselect == 1) {
			cout << "Enter the username" << endl;
			getline(cin, enterusername);
			cout << "Enter the password" << endl;
			getline(cin, enterpassword);

			string filename = enterusername + ".txt";
			fstream customer(filename, ios::in);
			if (customer.is_open()) {

				getline(customer, C.username);
				getline(customer, C.password);
				customer.close();

				if (C.password == enterpassword && C.username == enterusername) {
					cout << "Login successful" << endl;


				}



			}
			else {
				cout << "The file does not open" << endl;
			}
			//read from file if username and password matches show the info 
		}
		else if (loginselect == 2) {
			C.getcustomer();
			C.showcustomer();
		}
		else {
			cout << "invalid number entered";
		}
	}
};
class Product {
private:
	int id;
	string name;
	float price;
	int stockquantity;
public:
	Product() {
		id = 0;
		name = " ";
		price = 0.0;
		stockquantity = 0;
	}
	Product(int ID, string n, float p, int sq) {
		id = ID;
		name = n;
		price = p;
		stockquantity = sq;
	}
	void show() {

		cout << id << "-" << name << "price= " << "(" << price << ")" << endl;
	}
	void stock() {

		stockquantity--;



	}float getprice() {
		return price;
	}friend class Cart;
	friend class reciept;
};
class sationary :public Product {
private:
	string type;

public:
	sationary(int ID, string n, string t, int p, int sq) :Product(ID, n, p, sq) {
		type = t;
	}
	void show() {

		Product::show();

		cout << type << endl;
		Product::stock();
	}
};
class clothing :public Product {
	string size;
	string color;
public:
	clothing(int ID, string n, int p, string s, string c, int sq) :Product(ID, n, p, sq) {
		size = s;
		color = c;
	}
	void show() {
		Product::show();
		cout << "size=" << size << " " << "color" << color;
		Product::stock();
	}
};
class electronics :public Product {
private:

	string model;
public:
	electronics(int ID, string n, int p, int sq, string m) :Product(ID, n, p, sq) {
		model = m;
	}
	void show() {
		Product::show();
		cout << "The model is " << model << endl;
		Product::stock();
	}


};

class food :public Product {
private:
	string type;
	

public:
	food(int ID, string n, int p, int sq, string t) :Product(ID, n, p, sq) {
		type = t;
	}
	void show() {
		Product::show();
		cout << "the category is" << type;
		Product::stock();
	}
};

class Cart {
private:
	int match;
	int count;
	float total;

public:
	Product p[50];          // All available products
	Product cartItems[50];  // Products added to cart
	Product p6;
	Cart() {
		total = 0;
		count = 0;
	}

	void input() {
		cout << "Enter the ID of the items you want to buy (0 to finish): " << endl;
		while (true) {
			cin >> match;
			if (match == 0) break;

			bool found = false;
			for (int j = 0; j < 50; j++) {
				if (p[j].id == match && p[j].id != 0) {

					if (p[j].stockquantity <= 0) {
						cout << "Sorry! Product is out of stock.\n";
						found = true;
						break;
					}

					// Product is available
					found = true;

					p[j].stock();                  // reduce stock
					cartItems[count] = p[j];       // add to cart
					total += p[j].getprice();
					count++;

					cout << "Product successfully added to cart.\n";
					cout << "Remaining stock: " << p[j].stockquantity << endl;

					break;
				}

			}
			if (!found) {
				cout << "Invalid product ID. Try again." << endl;
			}
		}

	}
	void showcart() {
		for (int i = 0;i < 50;i++) {
			cout << cartItems[i].name;
		}
	}
	float Total() {

		return total;
	}

	friend class reciept;
};


class reciept {
	Cart c1;

public:

	void printReceipt(Cart& cart, Customer& s) {
		cout << "\n======= RECEIPT =======\n";
		cout << "Customer: " << s.username << endl;

		for (int i = 0; i < cart.count; i++) {
			cout << "Product: " << cart.cartItems[i].name
				<< " | Price: " << cart.cartItems[i].getprice() << endl;
		}

		cout << "Total Price: Rs." << cart.Total() << endl;
		cout << "=======================\n";
		string filename = "receipt_" + s.username + ".txt";
		ofstream receiptFile(filename, ios::app);

		if (receiptFile.is_open()) {
			receiptFile << "======= RECEIPT =======\n";
			receiptFile << "Customer Username: " << s.username << endl;
			receiptFile << "Name: " << s.name << endl;
			receiptFile << "Phone: " << s.phoneno << endl;
			receiptFile << "Email: " << s.email << endl;
			receiptFile << "Address: " << s.address << endl;
			receiptFile << "------------------------\n";

			for (int i = 0; i < cart.count; i++) {
				receiptFile << "Product: " << cart.cartItems[i].name
					<< " | Price: Rs." << cart.cartItems[i].getprice() << endl;
			}

			receiptFile << "------------------------\n";
			receiptFile << "Total Price: Rs." << cart.Total() << endl;
			receiptFile << "========================\n";

			receiptFile.close();
			cout << "\nReceipt saved in file: " << filename << endl;
		}
		else {
			cout << "Error creating receipt file!" << endl;
		}
	}
};

class payment {
	int fingerprintstandard=1018;
	int fingerprint;
public:
	void pay() {
		cout << "cashier can give her fingerprint if payment is done";
		cin >> fingerprint;
		if (fingerprintstandard == fingerprint) {
			cout << "payment recieved! Thankyou for shopping";
		}
		else {
			cout << "payment not recieved";
		}
}
};
int main() {
	Cart c;
	int person;
	Customer C;
	login L;
	Product p3;
	SetConsoleTextAttribute(h, 2);
	cout << "If you want to register/subscribe press 1 / press any other number if you want to do shopping?" << endl;
	cin >> person;
	if (person != 1) {
		cout << "Shopping without subscribing" << endl;
	}


	system("pause");
	system("CLS");
	if (person == 1) {
		C.getcustomer();
		C.showcustomer();

		L.select();
	}

	system("CLS");
	SetConsoleTextAttribute(h, 11);


	cout << "Enter the department from which you would like to purchase" << endl;
	cout << "These are the departments" << endl;
	cout << "-----------------------------------";
	cout << "Electronics" << endl;
	cout << "-----------------------------------";
	cout << "Clothing" << endl;
	cout << "-----------------------------------";
	cout << "Stationary" << endl;
	cout << "-----------------------------------";
	cout << "FOOD" << endl;
	cout << "-----------------------------------";
	cout << endl;
	SetConsoleTextAttribute(h, 4);
	int department;
	do {
		cout << "Enter 1 for Electronics,2 for clothing, 3 for stationary and 4 for food" << endl;

		cin >> department;
		if (department == 0) { break; }

		if (department == 1) {
			c.p[0] = electronics(2, "laptop", 10000.9, 9, "windows 11");

			c.p[1] = electronics(1, "mobile", 1089.9, 8, "14 pro max");
			c.p[2] = electronics(3, "mobile case", 65.9, 5, "15 pro");
			c.p[3] = electronics(4, "power bank", 889.9, 8, "samsung");
			c.p[4] = electronics(5, "charger", 189.9, 2, "wireless charger");
			c.p[5] = electronics(6, "batteries", 1089.9, 8, "80 volts");

			for (int i = 1; i <= 5; i++) {
				c.p[i].show();
			}

		}

		else if (department == 2) {
			c.p[6] = clothing(7, "Shirt", 2500, "small", "blue", 10);
			c.p[7] = clothing(8, "Trousers", 1500, "small", "black", 12);
			c.p[8] = clothing(9, "Undergarments", 1240, " ", " ", 22);
			c.p[9] = clothing(10, "Shoes", 2500, "6 size", "black", 25);

			for (int i = 6; i <= 9; i++) {
				c.p[i].show();
			}

		}
		else if (department == 3) {

			c.p[10] = sationary(11, "Notebooks", "Narrow lines", 250, 33);
			c.p[11] = sationary(12, "pencils and markers", "ORO", 750, 55);
			c.p[12] = sationary(13, "Files and Plastic covers", "simple", 30.5, 77);
			c.p[13] = sationary(14, "Schoolbags", "for girls", 1340, 33);

			for (int i = 10; i <= 13; i++) {
				c.p[i].show();
			}

		}
		else
		{
			c.p[14] = food(15, "Apple", 240, 12, "Fruit");
			c.p[15] = food(16, "Mango", 120, 33, "Fruit");

			c.p[16] = food(17, "Tomato", 340, 22, "Vegetable");
			c.p[17] = food(18, "Onion", 330, 33, "Vegetable");

			c.p[18] = food(19, "Yogurt", 125, 12, "Dairy");
			c.p[19] = food(20, "Milk", 450, 45, "Dairy");

			c.p[20] = food(21, "Chips", 222, 45, "Junk");
			c.p[21] = food(22, "Cold Drink", 126, 33, "Junk");


			for (int i = 14; i <= 21; i++) {
				c.p[i].show();
			}
		}


		c.input();
	} while (department != 0);
	SetConsoleTextAttribute(h, 6);
	system("pause");
	system("CLS");
	cout << "Your total is:" << endl;
	cout << c.Total()<<endl;
	system("pause");
	system("CLS");
	SetConsoleTextAttribute(h, 7);
	reciept r;
	r.printReceipt(c, C);
	SetConsoleTextAttribute(h, 12);
	payment p;
	p.pay();
}


