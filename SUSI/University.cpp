#include "University.h"
#include "StudentToCourse.h"
#include "Student.h"
#include "Year.h"
#include "Program.h"
#include "StudentToProgram.h"
#include "CoursesForProgram.h"
#include "Generic.h"

#include<cassert>
#include<list>
#include<iostream>
#include<cstring>
#include <sstream>


/// �������, ����� �������� ����� ��������.
int CompareStudents(const Student* s1, const Student* s2)
{
	return s1->getFN() - s2->getFN();
}


/// �������, ���������� ������� ����� �� �������
/**
* ��������� ����� ������� �� ������� ���������� �����.
* ����������� ���� ��� ����� �������, �������� � ��������� ��������� �����,
* � ���� ��� ������ �� ���������� �������.
* ��� �� ��������� ���������, ������ ������� ���������, ����� �� ����� ������ �� ��������, � ���� �����, ���������� ��������.
* ������� ������� ����� �� ��������� : ������ �� �������� �������� �� ����� ��.
*/
double University::getAvarageGrades(int fn)
{
	Student* s = getStudentViaFN(fn);
	double gradeSum = 0;
	int gradeCount = 0;
	for (std::list<StudentToCourse*>::const_iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		//*i �� ����� ������� �� StudentToCourse* � �� ������ getStudent
		if (((*i)->getStudent() == *s) && ((*i)->hasGrade())) {
			// (*i)->getLastGrade() == Grade*
			gradeSum += (*i)->getLastGrade().getGrade();
			gradeCount++;
		}
	}
	return gradeSum / gradeCount;
}
///������� ������ � ��������������.
void University::listPrograms(std::ostream& out) const
{
	for (std::list<Program*>::const_iterator i = this->programs.begin();
		i != this->programs.end(); ++i)
	{
		out << (*i)->getId() << "\n" << (*i)->getNameProgram() << '\n';
	}
}

///�������, ����� ������ id-�� ��������� �� �������������, �������� � ������������.
Program* University::getProgramViaId(const unsigned int prId)
{
	for (std::list<Program*>::iterator i = this->programs.begin();
		i != this->programs.end(); ++i)
	{
		if ((*i)->getId() == prId) return *i;
	}
	return nullptr;
}
Course* University::getCourseViaId(const unsigned int crId)
{
	for (std::list<Course*>::iterator i = this->courses.begin();
		i != this->courses.end(); ++i)
	{
		if ((*i)->getId() == crId) return *i;
	}
	return nullptr;
}
Student* University::getStudentViaFN(const unsigned int stFN)
{
	{
		for (std::list<Student*>::iterator i = this->students.begin();
			i != this->students.end(); ++i)
		{
			if ((*i)->getFN() == stFN) return *i;
		}
		//assert(false);
		return nullptr;
	}
}

///�������, ��������� ��� �������.
/**
* ������� ������� �� ������� ���������� ����� � ����������� �� ������� id.
* ��� ���� ��� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� �� ���������� ����������� � ���������� id, �� ������ ���������� ����� return 2.
* �������� ��� ������� ��� ������: �������.
* ������ ������� �� ������� � ����� ��� ����������.
* �� ����, � ����� �� ���������� � ��������������, ��������� ����� ������� � ����������� � ����� � ������� return 0.
*/
int University::enroll(int fn, const unsigned int idProgram, int group, const char* name)
{
	Student* s = getStudentViaFN(fn);
	Program* p = getProgramViaId(idProgram);
	if (s != nullptr) return 1;
	if (p == nullptr) return 2;
	s = new Student(name, fn, Status::ENROLLED);
	students.push_back(s);
	studentPrograms.push_back(new StudentToProgram(*s, *p, group));
}


///�������, ��������� ������� � ������� ����.
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* � ����� for() �������� ��� ���� � ����� StudentToProgram,
* ���� ������� ������� ���� � �� ����������� � +1 � ������� return 0.
*/
int University::advance(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
		i != this->studentPrograms.end(); ++i)
	{
		if ((*i)->getStudent() == *s) {
			(*i)->addYear((Year)((*i)->getCurrentYear() + 1));
		}
	}
	return 0;
}


///�������, ����� ������� �������, ������ ��� ������������� �� ���������.
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* �� ������ ����� <option> ����������� ���� ������ �� �� ����� �������, ������ ��� �������������.
* ������� � �������� �� �� ����� ������.
* ������ ���� �� �� ����� ����, ��� ��� �������� ��� ������� ������.
* �������������� ���� �� �� �����, ��� �� ����� ������ ������ �� ���������� ������. 
*/
int University::change(int fn, char* option, int value)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	if (strcmp("newGroup", option) == 0)
	{
		for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
			i != this->studentPrograms.end(); ++i)
		{
			if ((*i)->getStudent() == *s) {
				(*i)->setGroup(value);
			}
		}
		return 0;
	}
	if (strcmp("newYear", option) == 0)
	{
		for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
			i != this->studentPrograms.end(); ++i)
		{
			int isRequiredCourse = 0;
			int isPossitiveGrade = 0;
			if ((*i)->getStudent() == *s)
			{
				for (std::list<CourseForProgram*>::iterator j = this->coursePrograms.begin();
					j != this->coursePrograms.end(); ++i)
				{
					if ((*j)->getProgram() == (*i)->getProgram())
					{
						for (std::list<StudentToCourse*>::iterator k = this->studentCourseGrades.begin();
							k != this->studentCourseGrades.end(); ++i)
						{
							if (((*k)->getCourse() == (*j)->getCourse()) && ((*k)->getCourse().getIsRequired()))
							{
								isRequiredCourse++;
								if (((*k)->hasGrade()) && ((*k)->getLastGrade().isPossitive()))
								{
									isPossitiveGrade++;
								}
							}
						}
					}
				}
				if ((isRequiredCourse - isPossitiveGrade) <= 2)
				{
					(*i)->addYear((Year)((*i)->getCurrentYear() + 1));
				}
			}
		}
		return 0;
	}
	if (strcmp("newProgram", option) == 0)
	{
		for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
			i != this->studentPrograms.end(); ++i)
		{
			int isRequiredCourse = 0;
			int isPossitiveGrade = 0;
			if (((*i)->getStudent() == *s) && ((*i)->isPreviousYear()))
			{
				for (std::list<CourseForProgram*>::iterator j = this->coursePrograms.begin();
					j != this->coursePrograms.end(); ++i)
				{
					if ((*j)->getProgram() == (*i)->getProgram())
					{
						for (std::list<StudentToCourse*>::iterator k = this->studentCourseGrades.begin();
							k != this->studentCourseGrades.end(); ++i)
						{
							if (((*k)->getCourse() == (*j)->getCourse()) && (*k)->getCourse().getIsRequired())
							{
								isRequiredCourse++;
								if (((*k)->hasGrade()) && ((*k)->getLastGrade().isPossitive()))
								{
									isPossitiveGrade++;
								}
							}
						}
					}
				}
				if (isRequiredCourse == isPossitiveGrade)
				{
					(*i)->getProgram().getNameProgram();
				}

			}
		}
		return 0;
	}

}


///�������, ����� ��������� ��������� ���� ��������
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� �������� �� ��������� � ���������, ���������� ����� return 2.
* ����������� ���� ��������� �� �����  StudentToCourse ������� � ������� �������.
* ��� ��� ������ < 3, ������ ���������� ����� return 3.
* ��� ������ ������ �� > 3, ������ ������� ������� �� �������� ��� : �������� � ������� return 0.
*/
int University::graduate(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	if (s->getStatus() == INTERRUPTED) return 2;
	for (std::list<StudentToCourse*>::iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		if ((*i)->getStudent() == *s) {
			if (!((*i)->getLastGrade().isPossitive())) return 3;
		}
	}
	s->setStatus(GRADUATED);
	return 0;
}


///�������, ����� ��������� ��������� ���� ���������.
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� ��� ����� ������� ��������� �������� ������ �� ��������� � ����� return 0.
*/
int University::interrupt(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	s->setStatus(INTERRUPTED);
	return 0;
}


//�������, ����� ����� ������������ ����� �� ����� �������.
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� ��� ����� ������� ��������� �������� ������ �� ������� � ����� return 0.
*/
int University::resume(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	s->setStatus(ENROLLED);
	return 0;
}


///�������, ����� �������� ������� �� �������.
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ����������� ���� ��������� �� �����  StudentToCourse ������� � ������� �������.
* �������� ����� id-�� �� �������������, � ���� ���� � ����� �� ������������� � ����� return 0.
*/
int University::print(int fn, std::ostream& out)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	out << "Name: " << s->getNameStudent() << '\n';
	for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
		i != this->studentPrograms.end(); ++i)
	{
		if ((*i)->getStudent() == *s)
			out << (*i)->getProgram().getId() << "\n" << (*i)->getProgram().getNameProgram() << '\n';
	}
	return 0;
}


///�������, ����� �������� �� ������ ������� �� ������ ����������� � ����� ����.
/**
* ������� ����������� �� ������� id.
* ��� �� ���������� ����������� � ���������� id, �� ������ ���������� ����� return 1.
* ���������� ����� �� �������������.
* ����������� ���� ������������� �� ����� StudentToCourse ������� � ������� ����������� � ���� � ���������� ����
* ��������� ������������ ����� � ����� �� ����� ������� �� ���� ������������ � ����� return 0.
*/
int University::printall(const unsigned int idProgram, Year year, std::ostream& out)
{
	Program* p = getProgramViaId(idProgram);
	if (p == nullptr) return 1;
	out << "Name: " << p->getNameProgram() << "\n";
	for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
		i != this->studentPrograms.end(); ++i)
	{
		if ((*p == (*i)->getProgram()) && ((*i)->getCurrentYear() == year))
			out << (*i)->getStudent().getFN() << " " << (*i)->getStudent().getNameStudent() << '\n';
	}
	return 0;
}


///�������, ��������� ����� ������� � ����������
/**
*������� ������� �� ������� ���������� ����� � ���������� �� ������� id.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� �� ���������� ���������� � ���������� id, �� ������ ���������� ����� return 2.
* ����������� ���� ��������� �� ����� StudentToCourse ������� � ������ �������.
* ���� ���� ����������� ���� ������������ �� ����� CourseForProgram ������� � ������� ����������.
* � ���� ������������ �� ����� StudentToCourse ������� ��� ������������� �� ����� CourseForProgram,
* ������ ������������� ���� � �������� �����.
* ������ �������� ��� ������� �� ������� ��� ������� � ���������� � ������� return 0;
*/
int University::enrollin(int fn, const unsigned int idCourse)
{
	Student* s = getStudentViaFN(fn);
	Course* c = getCourseViaId(idCourse);
	if (s == nullptr) return 1;
	if (c == nullptr) return 2;
	for (std::list<StudentToProgram*>::iterator i = this->studentPrograms.begin();
		i != this->studentPrograms.end(); ++i)
	{
		if ((*i)->getStudent() == *s)
		{
			for (std::list<CourseForProgram*>::iterator j = this->coursePrograms.begin();
				j != this->coursePrograms.end(); ++i)
			{
				if (((*j)->getCourse() == *c) && ((*j)->getProgram() == (*i)->getProgram()))
				{
					((*j)->hasYear((*i)->getCurrentYear()));
				}
			}
		}
	}
	studentCourseGrades.push_back(new StudentToCourse(*s, *c));
	return 0;
}


///�������, �������� ������ �� ������ ���������� �� ����� �������
/**
* ������� ������� �� ������� ���������� ����� � ���������� �� ������� id.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ��� �� ���������� ���������� � ���������� id, �� ������ ���������� ����� return 2.
* ��� ��������� � ���������, ����� return 3.
* ��� ��������� � ��������, ����� return 4.
* ����������� ���� ��������� � ������������ �� ����� StudentToCourse �������� � ������ ������� � ����������.
* �������� ������ � ������� return 0.
*/
int University::addGrade(int fn, const unsigned int idCourse, Grade grade)
{
	Student* s = getStudentViaFN(fn);
	Course* c = getCourseViaId(idCourse);
	if (s == nullptr) return 1;
	if (c == nullptr) return 2;
	if (s->getStatus() == INTERRUPTED) return 3;
	if (s->getStatus() == GRADUATED) return 4;
	for (std::list<StudentToCourse*>::iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		if (((*i)->getStudent() == *s) && ((*i)->getCourse() == *c)) {
			(*i)->addGrade(grade);
		}
	}
	return 0;
}


///�������, ����� �������� �������� �� ����� ����.
/**
* ������� ���������� �� ������� id.
* ��� �� ���������� ���������� � ���������� id, �� ������ ���������� ����� return 1.
* ������ ������, � ����� �� �������� ����������, ����� �� �������� �� ����� ���������� ����������.
* ��� ������������ �� ����� StudentToCourse ������� � ������� ������������, 
* ������ ��������� ������� � ������ ������.
* ���������� ���������� � ��������� CompareStudents() � �� ���������,
* �� ���� ��������� ������������ ������ � ������� �� ���������� � ��������� ���������� � ������� return 0.
*/
int University::protocol(const unsigned int idCourse, std::ostream& out)
{
	Course* c = getCourseViaId(idCourse);
	if (c == nullptr) return 1;
	std::list<const Student*> s;
	for (std::list<StudentToCourse*>::const_iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		if ((*i)->getCourse() == *c)
		{
			s.push_back(&((*i)->getStudent()));
		}
	}
	s.sort(CompareStudents);
	for (std::list<const Student*>::const_iterator i = s.begin(); i != s.end(); ++i)
	{
		out << (*i)->getFN() << "\n" << (*i)->getNameStudent() << '\n';
	}
	return 0;
}


///�������, ����� �������� ������� �� �������� �� �������
/**
* ������� ������� �� ������� ���������� �����.
* ��� ���� ������� ������� � ���� ���������� �����, ���������� ����� return 1.
* ������ ��� ���� ������� �� ������������� ������ ( >=3) � �� ������������� ������ (== 2) �� ��������.
* �������� �� ��� ����������, ����� �� ������ ������ ��������� �� ������������� � ������������� ������.
* ��� ��������� �� ����� StudentToCourse ������� � ������ �������
* � ���������� ������������ ������, �������� ������� ��� ������� �� ����������� ������ � ������� ������ ��.
* ��� �������� � �����������, �������� ������� ��� ������� �� ����������� ������ � ������� ������ ��.
* ���������� �������� �� ������� � ������������� ������.
* ���������� �������� �� ������� � ����������� ������.
* �� ���� ������� �������� ����� � ������� return 0;
*/
int University::report(int fn, std::ostream& out)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	std::list<const StudentToCourse*> positiveGrades;
	std::list<const StudentToCourse*> nonpositiveGrades;
	double positivegradeSum = 0;
	double nonpositivegradeSum = 0;
	for (std::list<StudentToCourse*>::const_iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		if ((*i)->getStudent() == *s)
		{
			if (((*i)->hasGrade()) && ((*i)->getLastGrade().isPossitive()))
			{
				positiveGrades.push_back((*i));
				positivegradeSum += (*i)->getLastGrade().getGrade();
			}
			else
			{
				nonpositiveGrades.push_back((*i));
				nonpositivegradeSum += 2;
			}

		}

	}
	for (std::list<const StudentToCourse*>::const_iterator i = positiveGrades.begin(); i != positiveGrades.end(); ++i)
	{
		out << (*i)->getStudent().getFN() << "\n" << (*i)->getCourse().getNameCourse() << "\n " << (*i)->getLastGrade().getGrade() << '\n';
	}
	for (std::list<const StudentToCourse*>::const_iterator i = positiveGrades.begin(); i != nonpositiveGrades.end(); ++i)
	{
		out << (*i)->getStudent().getFN() << "\n " << (*i)->getCourse().getNameCourse() << '\n';
	}
	((positivegradeSum + nonpositivegradeSum) / (positiveGrades.size() + nonpositiveGrades.size()));
	return 0;
}



bool University::open(const char* fileName)
{
	universityFile.open(fileName, std::ios::app);

	if (!(universityFile.is_open()))
	{
		std::cout << "The file can't be open!" << '\n';
		return 0;
	}

	std::string line;
	while (std::getline(universityFile, line))
	{
		if (line.compare(STUDENT) == 0)
		{
			this->students.push_back(new Student(universityFile));
		}
		else if (line.compare(COURSE) == 0)
		{
			this->courses.push_back(new Course(universityFile));
		}
		else if (line.compare(PROGRAM) == 0)
		{
			this->programs.push_back(new Program(universityFile));
		}
		else if (line.compare(STUDENT_TO_PROGRAM) == 0)
		{
			Student* s = this->getStudentViaFN(getNextIntNumber(universityFile));
			Program* p = this->getProgramViaId(getNextIntNumber(universityFile));
			if (s == nullptr) return 1;
			if (p == nullptr) return 2;
			StudentToProgram* sp = new StudentToProgram(*s, *p, getNextIntNumber(universityFile));
			const int count = getNextIntNumber(universityFile);
			for (int i = 0; i < count; ++i) 
			{
				sp->addYear(Year(getNextIntNumber(universityFile)));
			}
			this->studentPrograms.push_back(sp);
			
		}
		else if (line.compare(STUDENT_TO_COURSE) == 0)
		{
			Student* s = this->getStudentViaFN(getNextIntNumber(universityFile));
			Course* c = this->getCourseViaId(getNextIntNumber(universityFile));
			if (s == nullptr) return 3;
			if (c == nullptr) return 4;
			StudentToCourse* sc = new StudentToCourse(*s, *c);
			const int count = getNextIntNumber(universityFile);
			for (int i = 0; i < count; ++i)
			{
				sc->addGrade(Grade(getNextIntNumber(universityFile)));
			}
			this->studentCourseGrades.push_back(sc);
		}
		else if (line.compare(COURSE_FOR_PROGRAM) == 0)
		{
			Course* c = this->getCourseViaId(getNextIntNumber(universityFile));
			Program* p = this->getProgramViaId(getNextIntNumber(universityFile));
			if (c == nullptr) return 5;
			if (p == nullptr) return 6;
			CourseForProgram* cp = new CourseForProgram(*c, *p);
			const int count = getNextIntNumber(universityFile);
			for (int i = 0; i < count; ++i);
			{
				cp->addYear(Year(getNextIntNumber(universityFile)));
			}
			this->coursePrograms.push_back(cp);
		}
	}
}
void University::close()
{
	universityFile.close();
	
}
bool University::save()
{
	if (!universityFile || !universityFile.is_open())
	{
		std::cout << "The file can't be open!\n";
		return false;
	}

	universityFile <<  std::endl;
	return !universityFile;
}
