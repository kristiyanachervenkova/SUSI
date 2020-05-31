#ifndef COURSEFORPROGRAM_H_INCLUDE
#define COURSEFORPROGRAM_H_INCLUDE

#include "Course.h"
#include "Program.h"
#include "Year.h"

#include<list>
#include<iostream>

/// ���� "CourseForProgram", ����� ���� ������� �� ����� ���������� � ��� ����������� �� ����� � ���� ��� ����.
class CourseForProgram {
    public:
        ///����������� � ���������.
        CourseForProgram(const Course& c, const Program& p) : course(c), program(p) {}

        ///�������, ����� ������ ������ ��� �����.
        void addYear(Year year) { this->years.push_back(year); }

        /// ���������, �����  �����  ���������� �� course.
        const Course& getCourse() const { return this->course; }
        /// ���������, �����  �����  ���������� �� program.
        const Program& getProgram() const { return this->program; }

        ///�������, ����������� ���� ��� ���� � �������
        bool hasYear(Year year) {
            for (std::list<Year>::iterator i = this->years.begin();
                i != this->years.end(); ++i) {
                if (*i == year) {
                    return true;
                }
            }
            return false;
        }
        ///�������� ���� �� �������
        void removeYear(Year year) {
            for (std::list<Year>::iterator i = this->years.begin();
                i != this->years.end(); ++i) {
                if (*i == year) {
                    // remove element in i
                    years.erase(i);
                }
            }
        }        

        ///���������, ����� �������� ���������� �� ����� ����������, ����������� � ����.
        /**
        *��������� �������� ������������ � ������������� �� id,
        * ������ �� ��������, ���� ����� ����� ������� ������,
        * ���� ���� � ����� ������� ������ �������
        */
        void print(std::ostream& out) const
        {
            out << COURSE_FOR_PROGRAM << '\n'
                << this->course.getId() << '\n'
                << this->program.getId() << '\n'
                << this->years.size() << '\n';
            for (std::list<Year>::const_iterator i = this->years.begin();
                i != this->years.end(); ++i)
            {
                out << *i << '\n';
            }
        }


        private:
            ///���������� ��� ���������� � �����������.
            const Course& course;
            const Program& program;
            ///���� � ���������.
            std::list<Year> years;
};
#endif // !COURSEFORPROGRAM_H_INCLUDE

