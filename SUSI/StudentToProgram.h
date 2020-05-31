#ifndef STUDENTTOPROGRAM_H_INCLUDE
#define STUDENTTOPROGRAM_H_INCLUDE

#include "Student.h"
#include "Program.h"
#include "Year.h"

#include<iostream>

/// ���� "StudentToProgram", ����� ���� ������� �� ����� ������� � ��� �����������, ����� � ������ �.
class StudentToProgram 
{
	public:
		///����������� � ���������
		///������� ������� �� ����������� � ����� ����.
		StudentToProgram(const Student& s, const Program& p, int group) : student(s), program(p), group(group)
		{
			addYear(Year::FIRST);
		}

		///������ ������ ��� ��������.
		void addYear(Year year) { years.push_back(year); }

		/// ���������, �����  �����  ���������� �� student.
		const Student& getStudent() const { return this->student; }
		/// ���������, �����  �����  ���������� �� program.
		const Program& getProgram() const { return this->program; }
		/// ���������, �����  �����  ���������� �� group.
		int getGroup() const { return this->group; }

		///����� ��������� ������� �� �����, �.� �������� ��������� ���� �� ��������.
		const Year getCurrentYear() const { return years.back(); }
		///����� ���� �� � �������� ����.
		bool isPreviousYear() const { return getCurrentYear() - 1; }
		/// ���������, �����  ���� ���������� �� group.
		void setGroup(int group) const { this->group == group; }

		///���������, ����� �������� ���������� �� ����� �������, �����������, ����� � ������.
		/**
		*��������� �������� ��������� � ������������� �� id,
		*�������� � ��������, ���� ����� ����� ������ ������, 
		*���� ���� � ����� ������� ������ ������.
		*/
		void print(std::ostream& out) const
		{
			out << STUDENT_TO_PROGRAM << '\n'
				<< this->student.getId() << '\n'
				<< this->program.getId() << '\n'
				<< this->group << '\n'
				<< this->years.size() << '\n';
			for (std::list<Year>::const_iterator i = this->years.begin();
				i != this->years.end(); ++i) 
			{
				out << *i << '\n';
			}
		}


		private:
			///���������� ��� ������� � �����������.
			const Student& student;
			const Program& program;
			///���� �� ���������
			std::list<Year> years;
			///����-����� �� ������� �� ����� �������.
			int group;

};
#endif // !STUDENTTOPROGRAM_H_INCLUDE
