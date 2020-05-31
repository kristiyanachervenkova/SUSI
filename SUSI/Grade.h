#ifndef GRADE_H_INCLUDE
#define GRADE_H_INCLUDE

#include<iostream>
#include <cassert>
/// ���� "Grade", ����� ���� ������� �� ��������
class Grade
{
	public:
		///����������� � ����������
		Grade(const double grade) : grade(grade)
		{
			assert((grade >= 2) && (grade <= 6));
		}

		/// ���������, ����� ��  �����  ���������� �� grade.
		double getGrade() const { return this->grade; }

		///�������, ����������� ���� �������� � ��-������ �� ���� 2.
		bool isPossitive() const { return grade >= 3; }

		///���������, ����� �������� ��������.
		void print(std::ostream& out) const { out << this->grade; }

	private:
		///����������� �� ����-�������.
		const double grade;
};
#endif // !GRADE_H_INCLUDE
