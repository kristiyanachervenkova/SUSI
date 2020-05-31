#ifndef COURSE_H_INCLUDE
#define COURSE_H_INCLUDE

#include<cassert>
#include<cstring>
#include<iostream>

#include "Generic.h"

/// Клас "Course", който пази данните за всяка дисциплина
class Course {
    public:
		//Статична член-данна за дължината на името.
		const static int MAX_NAME_LEN = 60;
		///Конструктор с параметри.
		///Проверява дали името на дисциплината е в позаволените граници.
		Course(const char* name, const bool isRequired) : isRequred(isRequired), id(getNextId())
		{
			assert(name_course && strlen(name_course) <= MAX_NAME_LEN);
			strcpy_s(this->name_course, name_course);
		}
		///Конструктор за записване в текстов файл.
		Course(std::istream& in) : id(getNextIntNumber(in))
		{
			assert(in);

			std::cin.getline(this->name_course, MAX_NAME_LEN);
			in >> isRequred;

		}
		///Проверява дали няма две дисциплини с еднакво id
		bool operator== (const Course& c2) const { return c2.id == this->id; }
		///Проверява дали записаната дисциплина е задължителна
		bool getIsRequired() const { return this->isRequred; }

		/// Фунцкията, която  връща  стойността на name_course
		const char* getNameCourse() const { return this->name_course; }
		/// Фунцкията, която  връща  стойността на id
		unsigned int getId() const { return this->id; }

		///Функцията, която принтира информация за всяка дисциплина
		void print(std::ostream& out) const
		{
			out << COURSE << '\n';
			out << this->id << '\n';
			out << this->name_course << '\n' << this->isRequred << '\n';
		}
		

    private:
		///Деклариране на член-данните.
		static unsigned int idCourse;

		const unsigned int id;
		char name_course[MAX_NAME_LEN+1];
		 bool isRequred;
		 /// Фунцкията, която връща id-то на следващата дисциплина
		unsigned int getNextId() {return idCourse++;}

};
#endif // !COURSE_H_INCLUDE