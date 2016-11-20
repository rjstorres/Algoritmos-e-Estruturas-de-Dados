/**
* @file person.h
* @author AEDA T3GE
* @title Class Person and Subclasses Stundent and Tutor
* @brief Classes used to store information of a Student or a Tutor
*/
#pragma once


#include <vector>
#include <string>
#include "exceptions.h"
#include "course.h"
#include "Date.h"

using namespace std;

typedef unsigned int uint;

class Person;
class Tutor;
class Student;
class Course;
class Date;

class Person {
protected:
	string code, name;
public:
	/**
	*@brief Constructor of pure virtual class Person
	*@param code of the person related to the department
	*@param name of the person
	*/
	Person(string code, string name);
	/**
	*@brief virtual fuction that returns the name of a Person
	*@return string with the name
	*/
	virtual string get_name() const = 0;

	/**
	*@brief virtual fuction that returns the code of a Person
	*@return string with the code
	*/
	virtual string get_code() const = 0;
};

class Tutor : public Person {
private:

public:
	//se der tempo mudar isto para privado
	vector<Student *> students;
	/**
	*@brief Constructor of the class Tutor
	*@param code of the tutor generated by the program itself or read from textfile
	*@param name of the tutor
	*/
	Tutor(string code, string name);
	/**
	*@brief virtual fuction that returns the name of a Tutor
	*@return string with the name
	*/
	string get_name() const;
	/**
	*@brief virtual fuction that returns the code of a Tutor
	*@return string with the code
	*/
	string get_code() const;
	/**
	*@brief Tutor has a vector of students mentored by him, adds a student to this vector
	*@param x Pointer to the student to add
	*/
	void add_student(Student* x);
	/**
	*@brief Operator < to see who's the tutor who has less students to mentor
	*@param t Tutor to compare with
	*/
	bool operator< (const Tutor &t) const;
};

class Student : public Person {
private:
	string email, status, tutor;
	double approved_credits, credits;
	vector<Course *> enrolled_courses;
	vector<Course *> approved_courses;
	vector<Date *> enrolled_dates;
	vector<Date *> approved_dates;
public:
	/**
	*@brief Constructor of the class Student
	*@param code of the student generated by the program itself or read from textfile
	*@param name of the student
	*@param email of the student
	*@param status of the student (if it's "Trabalhador Estudante", "Ordinário" etc.)
	*@param code of the mentor (tutor) if already assigned
	*/
	Student(string code, string name, string email, string status, string tutor);

	/**
	*@brief Constructor of the class Student
	*@param code of the student generated by the program itself or read from textfile
	*@param name of the student
	*@param email of the student
	*@param status of the student (if it's "Trabalhador Estudante", "Ordinário" etc.)
	*/
	Student(string code, string name, string email, string status);

	/**
	*@brief virtual fuction that returns the name of a Student
	*@return string with the name
	*/
	string get_name() const;

	/**
	*@brief virtual fuction that returns the code of a Student
	*@return string with the code
	*/
	string get_code() const;

	/**
	*@brief virtual fuction that returns the email of a Student
	*@return string with the email
	*/
	string get_email() const;

	/**
	*@brief virtual fuction that returns the status of a Student
	*@return string with the status
	*/
	string get_status() const;

	/**
	*@brief virtual fuction that returns the code of the tutor of a respective student
	*@return string with the code of a tutor
	*/
	string get_tutor() const;

	/**
	*@brief Function that returns a vector with the courses the student is enrolled
	*@return Returns vector<Course *> with student enrolled courses
	*/
	vector<Course *> get_enrol_courses() const;

	//TODO - Docs.
	vector<Course *> get_approv_courses() const;

	//TODO - Docs.
	vector<Date *> get_enrol_dates() const;

	//TODO - Docs.
	vector<Date *> get_approv_dates() const;

	/**
	*@brief returns the number of approved credits
	*/
	double get_appcredits() const;

	/**
	*@brief returns the number of credits assigned
	*/
	double get_credits() const;

	/**
	*@brief If a course is complered add credits of the respective course to approved credits of the student
	*@param x number of credits to add
	*/
	void add_approved_credits(double x);

	/**
	*@brief If a course is enrolled add credits of the respective course to credits of the student
	*@param x number of credits to add
	*/
	void add_credits(double x);

	/**
	*@brief Assigns a mentor for the stundent
	*@param x pointer to the Tutor to assign
	*/
	void assign_tutor(Tutor * x);
	/**
	*@brief Assigns a student to a course
	*@param c course to assign
	*/
	void enroll_course(Course *course, Date *date);

	/**
	*@brief If student passed the course removes it from the enrolled courses and goes to approved courses
	*@param c course to assign
	*/
	void approve_course(Course *course, Date *date);

	/**
	@brief Operator << for Student
	@param os ostream&
	@param s Student object to use the operator
	*/
	friend ostream& operator<<(ostream& os, const Student & s);
};