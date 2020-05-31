#ifndef STUDENTTOCOURSE_H_INCLUDE
#define STUDENTTOCOURSE_H_INCLUDE

#include "Student.h"
#include "Course.h"
#include "Grade.h"

#include<iostream>
#include<list>

/// Клас "StudentToCourse", който пази данните за всеки студент в коя дисциплина е и оценка.
class StudentToCourse
{
	public:
		///Конструктор с параметри.
		StudentToCourse(const Student& s, const Course& c) : student(s), course(c) {}
		
		///Добавя се нова оценка към листа с оценки.
		void addGrade(Grade grade) { grades.push_back(grade); }

		/// Фунцкията, която  връща  стойността на student.
		const Student& getStudent() const { return this->student; }
		/// Фунцкията, която  връща  стойността на course.
		const Course& getCourse() const { return this->course; }
		///Връща последния елемент на листа, т.е последната записана оценка на студента.
		const Grade getLastGrade() const { return grades.back(); }
		///Проверява дали има записана оценка за дисциплината.
		bool hasGrade() const { return grades.size() > 0; }

		///Функцията, която принтира информация за всеки студент, дисциплина и оценка.
		/**
		*Функцията принтира студентът и дисциплината по id,
		* оценката я принтира, като първо вземе нейния размер,
		* след това с цикъл изкарва всички оценки.
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
		///Референция към студент и дисциплина.
		const Student& student;
		const Course& course;
		///Лист с оценки.
		std::list<Grade> grades;
};
#endif // !STUDENTTOCOURSE_H_INCLUDE
