#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

#include "utils.h"
#include "exceptions.h"
#include "faculdade.h"
#include "course.h"
#undef max

using namespace std;
Department newDepartment(string name);
bool Menu_department();
void mainMenu(Department &dept);