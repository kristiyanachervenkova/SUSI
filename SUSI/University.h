#ifndef UNIVERSITY_H_INCLUDE
#define UNIVERSITY_H_INCLUDE

#include <iostream>
#include <ostream>
#include <fstream>

#include "Student.h"
#include "Course.h"
#include "StudentToCourse.h"
#include "Year.h"
#include "Program.h"
#include "Grade.h"
#include "StudentToProgram.h"
#include "CoursesForProgram.h"


/// Клас "University", който пази данните за всеки студент
class University
{
	public:
		///Пресмята средният успех на студента.
		double getAvarageGrades(int fn);

		///Функция, принтираща всички специалности.
		void listPrograms(std::ostream& out) const;
		
		///Записва нов студент.
		int enroll(int fn, const unsigned int idProgram, int group,const char* name);
		///Записва студент в следващ курс.
		int advance(int fn);
		///Променя групата, курсът или специалността на студента.
		int change(int fn, char* option, int value);
		///Отбелязва, ако студентът е завършил.
		int graduate(int fn);
		///Отбелязава, ако студентът е прекъснал.
		int interrupt(int fn);
		///Връща студентските права на прекънал студент.
		int resume(int fn);
		///Принтира справка за студента.
		int print(int fn, std::ostream& out);
		///Принтира справка за всички студент от дадена специалност и даден курс.
		int printall(const unsigned int idProgram, Year year, std::ostream& out);
		///Записва студент в дисциплина.
		int enrollin(int fn, const unsigned int idCourse);
		///Довабя оценка по дисциплина на студент.
		int addGrade(int fn, const unsigned int idCourse, Grade grade);
		///Извежда протокол за дисциплина.
		int protocol(const unsigned int idCourse, std::ostream& out);
		///Извежда справка за оценките на даден студент
		int report(int fn, std::ostream& out);

		///Функции за работа с файл.
		bool open(const char*);
		void close();
		bool save();
		bool saveas(const char*);



    private:
		std::list<Student*> students;
		std::list<Course*> courses;
		std::list<StudentToCourse*> studentCourseGrades;
		std::list<Program*> programs;
		std::list<StudentToProgram*> studentPrograms;
		std::list<CourseForProgram*> coursePrograms;

		///Функции, които взимат id-то съответно на специалността, студента и дисциплината.
		Program* getProgramViaId(const unsigned int id);
		Student* getStudentViaFN(const unsigned int id);
		Course* getCourseViaId(const unsigned int id);

		std::fstream universityFile;
};
#endif // !UNIVERSITY_H_INCLUDE

