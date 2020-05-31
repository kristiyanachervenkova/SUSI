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


/// Функция, която сравнява двама студенти.
int CompareStudents(const Student* s1, const Student* s2)
{
	return s1->getFN() - s2->getFN();
}


/// Функция, пресмятаща средния успех на студент
/**
* Функцията взима студент по неговия факултетен номер.
* Проверяваме дали има такъв студент, съвпадащ с подадения факултетн номер,
* и дали има оценка по съответния предмет.
* Ако са изпълнени условията, тогава взимаме параметър, който да смята сумата на оценките, и един брояч, преброяващ оценките.
* Смятаме средния успех по формулата : сумата на оценките раделена на брочт им.
*/
double University::getAvarageGrades(int fn)
{
	Student* s = getStudentViaFN(fn);
	double gradeSum = 0;
	int gradeCount = 0;
	for (std::list<StudentToCourse*>::const_iterator i = this->studentCourseGrades.begin();
		i != this->studentCourseGrades.end(); ++i)
	{
		//*i ще върне елемент от StudentToCourse* и ще изкара getStudent
		if (((*i)->getStudent() == *s) && ((*i)->hasGrade())) {
			// (*i)->getLastGrade() == Grade*
			gradeSum += (*i)->getLastGrade().getGrade();
			gradeCount++;
		}
	}
	return gradeSum / gradeCount;
}
///Извежда списък с специалностите.
void University::listPrograms(std::ostream& out) const
{
	for (std::list<Program*>::const_iterator i = this->programs.begin();
		i != this->programs.end(); ++i)
	{
		out << (*i)->getId() << "\n" << (*i)->getNameProgram() << '\n';
	}
}

///Функции, които взимат id-то съответно на специалността, студента и дисциплината.
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

///Функция, записваща нов студент.
/**
* Взимаме студент по неговия факултетен номер и специалност по нейното id.
* Ако вече има записан студент с този факултетен номер, програмата връща return 1.
* Ако не съществува специалност с подаденото id, то тогава програмата връща return 2.
* Добавяме нов студент със статус: Записан.
* Новият студент се записва в листа със студентите.
* На края, в листа за студентите и специалностите, записваме новия студент в специалност и група и връщаме return 0.
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


///Функция, записваща студент в следващ курс.
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* С цикъл for() добавяме нов курс в класа StudentToProgram,
* като взимаме текущия курс и го увеливачаме с +1 и връщаме return 0.
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


///Функция, която пременя групата, курсът или специалността на студентът.
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* По дадена опция <option> преверяваме дали трябва да се смени групата, курсът или специалността.
* Групата е възможно да се смени винаги.
* Курсът може да се смени само, ако има максимум два невзети изпита.
* Спрециалността може да се смени, ако са взети всички изпити от предишната година. 
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


///Функция, която отбелязва студентът като завършил
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Ако статусът на студентът е Прекъснал, програмата връща return 2.
* Проверяваме дали студентът от класа  StudentToCourse съвпада с взетият студент.
* Ако има оценка < 3, тогава програмата връща return 3.
* Ако всички оценки са > 3, тогава сменяма статуса на студента със : Завършил и връщаме return 0.
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


///Функция, която отбелязва студентът като прекъснал.
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Ако има такъв студент променяме неговият статус на Прекъснал и връща return 0.
*/
int University::interrupt(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	s->setStatus(INTERRUPTED);
	return 0;
}


//Функция, която връща студентските права на даден студент.
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Ако има такъв студент променяме неговият статус на Записан и връща return 0.
*/
int University::resume(int fn)
{
	Student* s = getStudentViaFN(fn);
	if (s == nullptr) return 1;
	s->setStatus(ENROLLED);
	return 0;
}


///Функция, която принтира справка за студент.
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Проверяваме дали студентът от класа  StudentToCourse съвпада с взетият студент.
* Принтира първо id-то на специалността, а след това и името на специалността и връща return 0.
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


///Функция, която принтира за всички студент от дадена специалност и даден курс.
/**
* Взимаме специалност по нейното id.
* Ако не съществува специалност с подаденото id, то тогава програмата връща return 1.
* Принтираме името на специалността.
* Проверяваме дали специалността от класа StudentToCourse съвпада с взетата специалност и дали е настоящият курс
* Извеждаме факултетният номер и името на всеки студент от тази свпециалност и връща return 0.
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


///Функция, записваща даден студент в дисциплина
/**
*Взимаме студент по неговия факултетен номер и дисциплина по нейното id.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Ако не съществува дисциплина с подаденото id, то тогава програмата връща return 2.
* Проверяваме дали студентът от класа StudentToCourse съвпада с взетия студент.
* След това проверяваме дали дисциплината от класа CourseForProgram съвпада с взетата дисциплина.
* и дали специалноста от класа StudentToCourse съвпада със специалността от класа CourseForProgram,
* тогава съществуащият курс е текущият куррс.
* Накрая добавяме нов елемент на списъка със студент и дисциплина и връщаме return 0;
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


///Функция, добавяща оценка по дадена дисциплина на даден студент
/**
* Взимаме студент по неговия факултетен номер и дисциплина по нейното id.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Ако не съществува дисциплина с подаденото id, то тогава програмата връща return 2.
* Ако студентът е прекъснал, връща return 3.
* Ако студентът е завършил, връща return 4.
* Проверяваме дали студентът и дисциплината от класа StudentToCourse съвпадат с взетия студент и дисциплина.
* Добавяме оценка и връщаме return 0.
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


///Функция, която принтира протокол за даден курс.
/**
* Взимаме дисциплина по нейното id.
* Ако не съществува дисциплина с подаденото id, то тогава програмата връща return 1.
* Правим списък, в който да довабяме студентите, които са записани за точно определена дисциплина.
* Ако дисциплината от класа StudentToCourse съвпада с взетата дисциплината, 
* тогава записваме студент в новият списък.
* Сравняваме студентите с функцията CompareStudents() и ги сортираме,
* На края извеждаме факултетните номера и имената на студентите в запсаната дисциплина и връщаме return 0.
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


///Функция, която принтира справка за оценките на студент
/**
* Взимаме студент по неговия факултетен номер.
* Ако няма записан студент с този факултетен номер, програмата връща return 1.
* Правим два нови списъка за положителните оценки ( >=3) и за отрицателните оценки (== 2) на студента.
* Добавяме си две променливи, които да смятат сумите съответно на положителните и отрицателните оценки.
* Ако студентът от класа StudentToCourse съвпада с взетия студент
* и съществува положетиелна оценка, добавяме елемент към списъка за положителни оценки и смятаме сумата им.
* Ако оценката е отрицателна, добавяме елемент към списъка за отрицателни оценки и смятаме сумата им.
* Принтираме оценките от списъка с положителните оценки.
* Прнтиреаме оценките от списъка с отрицателни оценки.
* На края смятаме средният успех и връщаме return 0;
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
