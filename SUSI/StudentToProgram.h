#ifndef STUDENTTOPROGRAM_H_INCLUDE
#define STUDENTTOPROGRAM_H_INCLUDE

#include "Student.h"
#include "Program.h"
#include "Year.h"

#include<iostream>

/// Клас "StudentToProgram", който пази данните за всеки студент в коя специалност, група и година е.
class StudentToProgram 
{
	public:
		///Конструктор с параметри
		///Записва студент от сцециалност в първи курс.
		StudentToProgram(const Student& s, const Program& p, int group) : student(s), program(p), group(group)
		{
			addYear(Year::FIRST);
		}

		///Добавя година към списъкът.
		void addYear(Year year) { years.push_back(year); }

		/// Фунцкията, която  връща  стойността на student.
		const Student& getStudent() const { return this->student; }
		/// Фунцкията, която  връща  стойността на program.
		const Program& getProgram() const { return this->program; }
		/// Фунцкията, която  връща  стойността на group.
		int getGroup() const { return this->group; }

		///Връща последния елемент на листа, т.е последно записания курс за студента.
		const Year getCurrentYear() const { return years.back(); }
		///Връща дали не е предишен курс.
		bool isPreviousYear() const { return getCurrentYear() - 1; }
		/// Фунцкията, която  дава стойността на group.
		void setGroup(int group) const { this->group == group; }

		///Функцията, която принтира информация за всеки студент, специалност, група и година.
		/**
		*Функцията принтира студентът и специалността по id,
		*годината я принтира, като първо вземе нейния размер, 
		*след това с цикъл изкарва всички години.
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
			///Референции към студент и специалност.
			const Student& student;
			const Program& program;
			///Лист за курсовете
			std::list<Year> years;
			///Член-данна за групата на всеки студент.
			int group;

};
#endif // !STUDENTTOPROGRAM_H_INCLUDE
