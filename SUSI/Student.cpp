#include<cassert>
#include<cstring>

#include<iostream>

#include "Student.h"
#include "University.h"
#include "Generic.h"

///����������� � ����������
///��������� ���� ����� � � ����������� ������� � ���� ������������ ����� � � ������� �� 6 �������.
Student::Student(const char* name_student, const int fn, Status status) : 
	id(getNextId()), status(status)
{
	assert(name_student && strlen(name_student) <= MAX_STNAME_LEN);
	strcpy_s(this->name_student, name_student);

	assert(fn == MAX_FN_LEN);
	this->fn = fn;
	
}

///����������� �� ��������� � ������� ����.
Student::Student(std::istream& in) : id(getNextIntNumber(in))
{
	assert(in);

	std::cin.getline(this->name_student, MAX_STNAME_LEN);
	in >> this->fn;
	this->status = Status(getNextIntNumber(in));
	
}
/// ��������� ���� ���� ����� �������� � ������� ���������� ������
bool Student::operator== (const Student& s2) const
{
	return s2.fn == this->fn;
}

/// ���������, �����  �����  ���������� �� name_student
const char* Student::getNameStudent() const
{
	return this->name_student;
}
/// ���������, �����  �����  ���������� �� fn
const int Student::getFN() const
{
	return this->fn;
}
/// ���������, �����  �����  ���������� �� status
Status Student::getStatus() const
{
	return this->status;
}
/// ���������, �����  �����  ���������� �� id
unsigned int Student::getId() const
{
	return this->id;
}

/// ���������, ����� ���� ���������� �� name_student
void Student::setNameStudent(const char* name_student)
{
	assert(name_student && strlen(name_student) <= MAX_STNAME_LEN);
	strcpy_s(this->name_student, name_student);
}
/// ���������, �����  ���� ���������� �� fn
void Student::setFN(const int fn)
{
	this->fn = fn;
}
/// ���������, �����  ���� ���������� �� status
void Student::setStatus(Status status) 
{
	this->status = status;
}

///���������, ����� �������� ���������� �� ����� �������
void Student::print(std::ostream& out) const
{
	out << STUDENT << '\n';
	out << this->id << '\n';
	out << this->name_student << '\n' << this->fn << '\n' << this->status << '\n';
}