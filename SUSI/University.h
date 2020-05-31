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


/// ���� "University", ����� ���� ������� �� ����� �������
class University
{
	public:
		///�������� �������� ����� �� ��������.
		double getAvarageGrades(int fn);

		///�������, ���������� ������ ������������.
		void listPrograms(std::ostream& out) const;
		
		///������� ��� �������.
		int enroll(int fn, const unsigned int idProgram, int group,const char* name);
		///������� ������� � ������� ����.
		int advance(int fn);
		///������� �������, ������ ��� ������������� �� ��������.
		int change(int fn, char* option, int value);
		///���������, ��� ��������� � ��������.
		int graduate(int fn);
		///����������, ��� ��������� � ���������.
		int interrupt(int fn);
		///����� ������������ ����� �� �������� �������.
		int resume(int fn);
		///�������� ������� �� ��������.
		int print(int fn, std::ostream& out);
		///�������� ������� �� ������ ������� �� ������ ����������� � ����� ����.
		int printall(const unsigned int idProgram, Year year, std::ostream& out);
		///������� ������� � ����������.
		int enrollin(int fn, const unsigned int idCourse);
		///������ ������ �� ���������� �� �������.
		int addGrade(int fn, const unsigned int idCourse, Grade grade);
		///������� �������� �� ����������.
		int protocol(const unsigned int idCourse, std::ostream& out);
		///������� ������� �� �������� �� ����� �������
		int report(int fn, std::ostream& out);

		///������� �� ������ � ����.
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

		///�������, ����� ������ id-�� ��������� �� �������������, �������� � ������������.
		Program* getProgramViaId(const unsigned int id);
		Student* getStudentViaFN(const unsigned int id);
		Course* getCourseViaId(const unsigned int id);

		std::fstream universityFile;
};
#endif // !UNIVERSITY_H_INCLUDE

