#include "University.h"
#include "Student.h"
#include "Year.h"
#include "Program.h"
#include "Grade.h"

#include<iostream>
#include<string>


int main()
{
	University university;
	const int n = 128;
	char console[n];
	std::string filename;
	while (true)
	{
		std::cout << "\n\nAvailable options: open, close, save, help, exit ";
		std::cin.getline(console, n);
		if (strcmp("open", console) == 0)
		{
			std::getline(std::cin, filename);

			university.open("nameFile.txt");
		}
		else if (strcmp("close", console) == 0)
		{
			university.close();
		}
		else if (strcmp("save", console) == 0)
		{
			university.save();
		}

		else if (strcmp("help", console) == 0)
		{
			std::cout << "The following commands are supported: \n";
			std::cout << "open <file>	opens <file> \n";
			std::cout << "close			closes currently opened file \n";
			std::cout << "save			saves the currently open file \n";
			std::cout << "saveas <file>	saves the currently open file in <file> \n";
			std::cout << "help			prints this information \n";
			std::cout << "exit			exists the program \n";
		}
		else if (strcmp("exit", console) == 0)
		{
			return 0;
		}

		//std::cout << "\n\nAvailable options: Enroll, Advance, Graduate, Change, Interrupt, Resume, Print, PrintAll, EnrollIn, AddGrade, Protocol, Report: ";
		if (strcmp("Enroll", console) == 0)
		{
			char name[Student::MAX_STNAME_LEN + 1];
			std::cout << "Name: ";
			std::cin.getline(name, Student::MAX_STNAME_LEN);
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			int group;
			std::cout << "Group: ";
			std::cin >> group;
			unsigned int prId;
			std::cout << "Program ID: ";
			std::cin >> prId;
			university.enroll(fn, prId, group, name);

		}
		if (strcmp("listPrograms", console) == 0)
		{
			university.listPrograms(std::cout);
		}
		else if (strcmp("Advance", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.advance(fn);
		}
		else if (strcmp("Change", console) == 0) 
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			char option[n];
			std::cout << "\n\nAvailable options: newGroup, newYear, newProgram: ";
			std::cin.getline(option, n);
			int value;
			std::cout << "Value: ";
			std::cin >> value;
			university.change(fn, option, value);
		}
		else if (strcmp("Graduate", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.graduate(fn);
		}
		else if (strcmp("Interrupt", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.interrupt(fn);
		}
		else if (strcmp("Resume", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.resume(fn);
		}
		else if (strcmp("Print", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.print(fn, std::cout);
		}
		else if (strcmp("PrintAll", console) == 0)
		{
			unsigned int prId;
			std::cout << "Program ID: ";
			std::cin >> prId;
			int year;
			std::cout << "Year: ";
			std::cin >> year;
			university.printall(prId, Year(year), std::cout);
		}
		else if (strcmp("EnrollIn", console) == 0) 
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			unsigned int crId;
			std::cout << "Course ID: ";
			std::cin >> crId;
			university.enrollin(fn, crId);
		}
		else if (strcmp("AddGrade", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			double grade;
			std::cout << "Grade: ";
			std::cin >> grade;
			unsigned int crId;
			std::cout << "Course ID: ";
			std::cin >> crId;
			university.addGrade(fn, crId, Grade(grade));
		}
		else if (strcmp("Protocol", console) == 0)
		{
			unsigned int crId;
			std::cout << "Course ID: ";
			std::cin >> crId;
			university.protocol(crId, std:: cout);
		}
		else if (strcmp("Report", console) == 0)
		{
			int fn;
			std::cout << "FN: ";
			std::cin >> fn;
			university.report(fn, std::cout);
		}

	}

	return 0;
}
