#include<cassert>
#include<cstring>

#include<iostream>

#include "Student.h"
#include "University.h"
#include "Generic.h"

///Конструктор с променливи
///Проверява дали името е в допустимите дължини и дали факултетният номер е с дължина от 6 символа.
Student::Student(const char* name_student, const int fn, Status status) : 
	id(getNextId()), status(status)
{
	assert(name_student && strlen(name_student) <= MAX_STNAME_LEN);
	strcpy_s(this->name_student, name_student);

	assert(fn == MAX_FN_LEN);
	this->fn = fn;
	
}

///конструктор за записване в текстов файл.
Student::Student(std::istream& in) : id(getNextIntNumber(in))
{
	assert(in);

	std::cin.getline(this->name_student, MAX_STNAME_LEN);
	in >> this->fn;
	this->status = Status(getNextIntNumber(in));
	
}
/// Проверява дали няма двама студенти с еднакви факултетни номера
bool Student::operator== (const Student& s2) const
{
	return s2.fn == this->fn;
}

/// Фунцкията, която  връща  стойността на name_student
const char* Student::getNameStudent() const
{
	return this->name_student;
}
/// Фунцкията, която  връща  стойността на fn
const int Student::getFN() const
{
	return this->fn;
}
/// Фунцкията, която  връща  стойността на status
Status Student::getStatus() const
{
	return this->status;
}
/// Фунцкията, която  връща  стойността на id
unsigned int Student::getId() const
{
	return this->id;
}

/// Фунцкията, която дава стойността на name_student
void Student::setNameStudent(const char* name_student)
{
	assert(name_student && strlen(name_student) <= MAX_STNAME_LEN);
	strcpy_s(this->name_student, name_student);
}
/// Фунцкията, която  дава стойността на fn
void Student::setFN(const int fn)
{
	this->fn = fn;
}
/// Фунцкията, която  дава стойността на status
void Student::setStatus(Status status) 
{
	this->status = status;
}

///Функцията, която принтира информация за всеки студент
void Student::print(std::ostream& out) const
{
	out << STUDENT << '\n';
	out << this->id << '\n';
	out << this->name_student << '\n' << this->fn << '\n' << this->status << '\n';
}