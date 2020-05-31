#ifndef COURSE_H_INCLUDE
#define COURSE_H_INCLUDE

#include<cassert>
#include<cstring>
#include<iostream>

#include "Generic.h"

/// ���� "Course", ����� ���� ������� �� ����� ����������
class Course {
    public:
		//�������� ����-����� �� ��������� �� �����.
		const static int MAX_NAME_LEN = 60;
		///����������� � ���������.
		///��������� ���� ����� �� ������������ � � ������������ �������.
		Course(const char* name, const bool isRequired) : isRequred(isRequired), id(getNextId())
		{
			assert(name_course && strlen(name_course) <= MAX_NAME_LEN);
			strcpy_s(this->name_course, name_course);
		}
		///����������� �� ��������� � ������� ����.
		Course(std::istream& in) : id(getNextIntNumber(in))
		{
			assert(in);

			std::cin.getline(this->name_course, MAX_NAME_LEN);
			in >> isRequred;

		}
		///��������� ���� ���� ��� ���������� � ������� id
		bool operator== (const Course& c2) const { return c2.id == this->id; }
		///��������� ���� ���������� ���������� � ������������
		bool getIsRequired() const { return this->isRequred; }

		/// ���������, �����  �����  ���������� �� name_course
		const char* getNameCourse() const { return this->name_course; }
		/// ���������, �����  �����  ���������� �� id
		unsigned int getId() const { return this->id; }

		///���������, ����� �������� ���������� �� ����� ����������
		void print(std::ostream& out) const
		{
			out << COURSE << '\n';
			out << this->id << '\n';
			out << this->name_course << '\n' << this->isRequred << '\n';
		}
		

    private:
		///����������� �� ����-�������.
		static unsigned int idCourse;

		const unsigned int id;
		char name_course[MAX_NAME_LEN+1];
		 bool isRequred;
		 /// ���������, ����� ����� id-�� �� ���������� ����������
		unsigned int getNextId() {return idCourse++;}

};
#endif // !COURSE_H_INCLUDE