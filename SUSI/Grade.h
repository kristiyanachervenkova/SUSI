#ifndef GRADE_H_INCLUDE
#define GRADE_H_INCLUDE

#include<iostream>
#include <cassert>
/// Клас "Grade", който пази данните за оценките
class Grade
{
	public:
		///Конструктор с параметъри
		Grade(const double grade) : grade(grade)
		{
			assert((grade >= 2) && (grade <= 6));
		}

		/// Фунцкията, която ще  връща  стойността на grade.
		double getGrade() const { return this->grade; }

		///Функция, проверяваща дали оценката е по-голяма от Слаб 2.
		bool isPossitive() const { return grade >= 3; }

		///Функцията, която принтира оценките.
		void print(std::ostream& out) const { out << this->grade; }

	private:
		///Деклариране на член-данните.
		const double grade;
};
#endif // !GRADE_H_INCLUDE
