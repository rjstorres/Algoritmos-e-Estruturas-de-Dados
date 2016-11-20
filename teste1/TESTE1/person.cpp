#include "person.h"

/*********************************
*CLASS PERSON
*********************************/

Person::Person(string code, string name) : code(code), name(name) {
	if (name.size() < 3)
		throw exception_or_error("Nome que tentou atribuir a esta pessoa � demasiado pequeno (" +  name  + ")");
	if (code.length() != 11)
		throw exception_or_error("Codigo de aluno ou tutor invalido (" + code + ")");
}

/*********************************
*CLASS TUTOR
*********************************/
Tutor::Tutor(string code, string name) : Person(code, name) {
	if (code.at(0) != 't' || code.at(1) != 'u')
		throw exception_or_error("Codigo de tutor invalido(" + code + ")");
}

string Tutor::get_name() const { return name; }

string Tutor::get_code() const { return code; }

void Tutor::add_student(Student* x)
{
	students.push_back(x);
}

bool Tutor::operator< (const Tutor &t) const {
	return students.size() < t.students.size();
}

/*********************************
*CLASS Student
*********************************/

Student::Student(string code, string name, string email, string status, string tutor) : Person(code, name), email(email), status(status), tutor(tutor) {
	approved_credits = 0;
	credits = 0;
	if (code.at(0) != 's' || code.at(1) != 't')
		throw exception_or_error("Codigo de estudante invalido(" + code + ")");
}

Student::Student(string code, string name, string email, string status) : Person(code, name), email(email), status(status) {
	approved_credits = 0;
	credits = 0;
	if (code.at(0) != 's' || code.at(1) != 't')
		throw exception_or_error("Codigo de estudante invalido(" + code + ")");
}

string Student::get_name() const { return name; }
string Student::get_code() const { return code; }
string Student::get_email() const { return email; }
string Student::get_status() const { return status; }
string Student::get_tutor() const { return tutor; }

vector<Course *> Student::get_enrol_courses() const {
	return enrolled_courses;
}

vector<Course *> Student::get_approv_courses() const {
	return approved_courses;
}

double Student::get_appcredits() const { return approved_credits; }
double Student::get_credits() const { return credits; }
void Student::add_approved_credits(double x) {
	approved_credits += x;
	credits -= x; // right? se foi aprovado retiramos dos creditos que esta inscrito...
}
void Student::add_credits(double x) { credits += x; }
void Student::assign_tutor(Tutor * x) { tutor = x->get_code(); }

void Student::enroll_course(Course *course) {
	enrolled_courses.push_back(course);
	credits += course->get_credits();
}

void Student::approve_course(Course *course) {
	bool found = false;
	for (vector<Course *>::iterator it = enrolled_courses.begin(); it != enrolled_courses.end(); ++it) {
		if (*it == course) {
			enrolled_courses.erase(it);
			found = true;
			break;
		}
	}

	approved_courses.push_back(course);
	if (found) {
		credits -= course->get_credits();
	}
	approved_credits += course->get_credits();
}

ostream & operator<<(ostream &os, const Student &stud)
{
	os << stud.code << " || " << stud.name << " || " << stud.email << endl <<
		"Status: " << stud.status << endl <<
		"Tutor: " << stud.tutor << endl <<
		"Completed credits: " << stud.approved_credits << endl <<
		"Credits currently enrolled for: " << stud.credits;
	return os;
}