#include "utils.h"

void clrscr(void)
{
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}


Student* read_student(ifstream &f,uint &linenum)
{
	string code, name, email, status, tutor, line;
	double apcredits, credits;

	read_line(f,line,linenum);



	code = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	name = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	email = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	status = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	tutor = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	apcredits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));

	Student* s=new Student(code, name, email, status, tutor);
	s->add_approved_credits(apcredits);
	s->add_credits(credits);

	return s;
}

Student* read_student(string line)
{
	string code, name, email, status, tutor;
	double apcredits, credits;
	
	code = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	name = line.substr(0, line.find(';'));
	line.erase(0, line.find(';') + 1);

	email = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	status = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	tutor = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	apcredits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));

	Student* s= new Student(code, name, email, status, tutor);
	s->add_approved_credits(apcredits);
	s->add_credits(credits);

	return s;
}

Tutor* read_tutor(ifstream &f,uint &linenum) {
	string code, name, line;

	read_line(f, line, linenum);

	code = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	name = line.substr(0, line.find(';'));
	
	Tutor* t= new Tutor(code, name);

	return t;
}

Course* read_course(ifstream &f,uint &linenum) {
	string name, line;
	uint year, semestre;
	double credits;

	read_line(f, line, linenum);

	name = (line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	year = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	semestre = stoul(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	credits = stod(line.substr(0, line.find(';')));
	line.erase(0, line.find(';') + 1);

	Course* c= new Course(year, semestre, credits, name);

	read_line(f, line, linenum);
	
	for (; line != "approved_students";) {
		c->add_student(read_student(line));
		read_line(f, line, linenum);
	}

	read_line(f, line, linenum);
	for (;line!="end_course";){
		c->add_approved_student(read_student(line));
		read_line(f, line, linenum);
	}

	return c;
}

void read_line(ifstream & f, string & line, uint &linenum)
{
	getline(f, line);
	++linenum;
}


