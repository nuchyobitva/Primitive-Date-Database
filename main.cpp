#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <iomanip>
using namespace std;
class Date {
public:
	Date(const int& yy, const int& mm, const int& dd) {
		year = yy;
		month = mm;
		day = dd;
	}
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
	void printdate() const {
		cout << setfill('0');
		cout << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day;
	}

private:
	int year;
	int month;
	int day;
};

istream& operator>>(istream& chit1, Date& d) { //doesn't check for the -
	chit1.ignore();
	string whole;
	getline(chit1,whole,' ');
	istringstream chit(whole);	
	int yy, dd, mm,tmp=1;
	string ystr, dstr, mstr;
	if (chit.peek() == '-') { 
		chit.ignore(1);
		tmp = -1;
	}
	getline(chit, ystr, '-');
	getline(chit, mstr, '-');
	getline(chit, dstr, ' ');
	if (ystr.size()==0 || mstr.size()==0|| dstr.size()==0) {
		cout << "Wrong date format: " << whole << endl;
		return chit1;
	}
	istringstream dchit(dstr);
	istringstream ychit(ystr);
	istringstream mchit(mstr);
	
	if (ychit>>yy) { //reading year
		string chck;
		if (ychit >> chck) {
			cout << "Wrong date format: " << whole << endl;
			return chit1;
		}
		yy *= tmp;
	}
	if (mchit >> mm) { //reading month
		string chck;
		if (mchit >> chck) {
			cout << "Wrong date format: " << whole << endl;
			return chit1;
		}
		if (mm < 1 || mm>12) {
			cout << "Month value is invalid: " << mm << endl;
			return chit1;
		}
	}
	if (dchit >> dd) {
		string chck;
		if (dchit >> chck) {
			cout << "Wrong date format: " << whole << endl;
			return chit1;
		}
		if (dd < 1 || dd>31) {
			cout << "Day value is invalid: " << dd << endl;
			return chit1;
		}
	}
	else {
		cout << "Wrong date format: " << whole << endl;
		return chit1;
	}
	d = { yy,mm,dd };
	return chit1;

}
bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) return lhs.GetYear() < rhs.GetYear();
	if (lhs.GetMonth() != rhs.GetMonth()) return lhs.GetMonth() < rhs.GetMonth();
	return lhs.GetDay() < rhs.GetDay();
}
bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) return false;
	if (lhs.GetMonth() != rhs.GetMonth()) return false;
	return lhs.GetDay() == rhs.GetDay();
}
bool operator!=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) return true;
	else {
		if (lhs.GetMonth() != rhs.GetMonth()) return true;
		else {
			return lhs.GetDay() != rhs.GetDay();
		}
	}
}

class Database {
public:
	void AddEvent(const Date& date, const string& ev) {
		a[date].insert(ev);
	}
	bool DeleteEvent(const Date& date, const string& ev) {
		if (a.count(date) == 0) return false;
		else {
			if (a[date].erase(ev)) {
				return true;
			}
		}
		return false;
	}
	int  DeleteDate(const Date& date) {
		if (a.count(date) == 0) return 0;
		else {
			int n = a[date].size();
			a.erase(date);
			return n;
		}
	}
	void Find(const Date& date) const {
		for (const auto& item : a) {
			if (item.first == date) {
				for (const string& str : item.second) {
					cout << str << endl;
				}
				return;
			}
		}
	}
	void Print() const {
		for (const auto& item : a) {
			for (const string& str : item.second) {
				item.first.printdate();
				cout << " " << str << endl;
			}
		}
	}
private:
	map <Date, set<string>> a;
};
int main() {
	Database db;
	Date zero(0, 0, 0);
	string command, cmd;
	while (getline(cin, command)) {
		istringstream chit(command);
		chit >> cmd;
		if (command.size() == 0) {

		}
		else if (cmd == "Print") {
			db.Print();
		}
		else if (cmd == "Find") {
			Date d(0, 0, 0);
			chit >> d;
			if (d != zero) {
				db.Find(d);
			}
		}
		else if (cmd == "Add") {
			Date d(0, 0, 0);
			string s;
			chit >> d;
			if (d != zero) {
				chit >> s;
				if (s.size() != 0) {
					db.AddEvent(d, s);
				}
			}
		}
		else if (cmd == "Del") {
			Date d(0, 0, 0);
			string s;
			chit >> d;
			if (d != zero) {
				if (chit >> s) {
					if (db.DeleteEvent(d, s)) {
						cout << "Deleted successfully" << endl;
					}
					else cout << "Event not found" << endl;
				}
				else {
					cout << "Deleted " << db.DeleteDate(d) << " events" << endl;
				}
			}
		}
		else if (cmd.size() < 1) {

		}
		else {
			cout << "Unknown command: " << cmd << endl;
		}
	}
	return 0;
}
