#ifndef STUDENTTOCOURSE_H_INCLUDE
#define STUDENTTOCOURSE_H_INCLUDE

#include "Student.h"
#include "Course.h"
#include "Grade.h"

#include<iostream>
#include<list>

/// ���� "StudentToCourse", ����� ���� ������� �� ����� ������� � ��� ���������� � � ������.
class StudentToCourse
{
	public:
		///����������� � ���������.
		StudentToCourse(const Student& s, const Course& c) : student(s), course(c) {}
		
		///������ �� ���� ������ ��� ����� � ������.
		void addGrade(Grade grade) { grades.push_back(grade); }

		/// ���������, �����  �����  ���������� �� student.
		const Student& getStudent() const { return this->student; }
		/// ���������, �����  �����  ���������� �� course.
		const Course& getCourse() const { return this->course; }
		///����� ��������� ������� �� �����, �.� ���������� �������� ������ �� ��������.
		const Grade getLastGrade() const { return grades.back(); }
		///��������� ���� ��� �������� ������ �� ������������.
		bool hasGrade() const { return grades.size() > 0; }

		///���������, ����� �������� ���������� �� ����� �������, ���������� � ������.
		/**
		*��������� �������� ��������� � ������������ �� id,
		* �������� � ��������, ���� ����� ����� ������ ������,
		* ���� ���� � ����� ������� ������ ������.
		*/
		void print(std::ostream& out) const
		{
			out << STUDENT_TO_COURSE << '\n'
				<< this->student.getId() << '\n'
				<< this->course.getId() << '\n'
				<< this->grades.size() << '\n';
			for (std::list<Grade>::const_iterator i = this->grades.begin();
				i != this->grades.end(); ++i)
			{
				(*i).print(out);
			}
		}

	private:
		///���������� ��� ������� � ����������.
		const Student& student;
		const Course& course;
		///���� � ������.
		std::list<Grade> grades;
};
#endif // !STUDENTTOCOURSE_H_INCLUDE
