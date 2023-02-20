#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<ctime>
using namespace std;


class Human
{
	std::string last_name;
	std::string first_name;
	tm birth_date; // tm - timepoint
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	tm get_birth_date()const
	{
		return birth_date;
	}
	unsigned int get_age()const
	{
		time_t t_today = time(NULL); 
		//cout << t_today << endl;
		tm* tm_today = localtime(&t_today);
		unsigned int age = tm_today->tm_year - birth_date.tm_year;
		if (tm_today->tm_mon < birth_date.tm_mon)age--;
		if (tm_today->tm_mon == birth_date.tm_mon && tm_today->tm_mday < birth_date.tm_mday)age--;
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_birth_date(int year, int month, int day)
	{
		birth_date.tm_year = year - 1900;
		birth_date.tm_mon = month - 1;
		birth_date.tm_mday = day;
	}

	//        Constructors:
	Human(const std::string& last_name, const std::string& first_name, int year, int month, int day)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_birth_date(year, month, day);
		cout << "HConstructors:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructors:\t" << endl;
	}

	//      Methods:
	virtual std::ostream& info(std::ostream& os)const
	{
		return os << last_name << " " << first_name << "\t" << get_age();
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}

class Student : public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//						Constructors:
	Student
	(
		const std::string& last_name, const std::string& first_name, int year, int month, int day,
		const std::string& speciality, const std::string& group, double rating, double attendance
	) :Human(last_name, first_name, year, month, day)//Вызов конструктора базового класса
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	Student(const Human& human, const std::string& speciality, const std::string& group, double rating, double attendance)
		:Human(human)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const
	{
		return Human::info(os)<< " " << speciality << " " << group << " " << rating << " " << attendance;
	}
};

//#define TIME_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef TIME_CHECK
	time_t t_today = time(NULL);	//Получаем текущее время в формате Timestamp
	cout << t_today << endl;
	tm* tm_today = localtime(&t_today);
	cout << tm_today->tm_year + 1900 << "\t";
	cout << tm_today->tm_mon + 1 << "\t";
	cout << tm_today->tm_mday << "\n";
	cout << asctime(tm_today) << endl;
#endif // TIME_CHECK

	//Human human("Тупенко", "Василий", 1990, 04, 01);
	//human.info();

	////Student student("Тупенко", "Василий", 1990, 04, 01, "IT", "start", 60, 30);
	//Student student(human, "IT", "start", 60, 30);
	//student.info();

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 1990, 03,04, "Chemistry", "WW_220", 90, 95),
		//new Teacher("White", "Walter", 1960, 9, 20, "Chemistry", 25),
		//new Graduate("Schrader", "Hank", 1970, 06,07, "Criminalistic", "WW_220", 75, 80, "How to catch Heizenberg"),
		new Student("Vercetty", "Tomas", 1970, 05, 25, "Criminalistic", "Vice", 90, 95),
		//new Teacher("Diaz", "Ricardo", 1960, 03,03, "Weapons distribution", 20)
	};

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//group[i]->info();
		cout << typeid(*group[i]).name() << ":\t";
		//cout << *group[i] << endl;
	}
}