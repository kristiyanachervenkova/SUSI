#ifndef COURSEFORPROGRAM_H_INCLUDE
#define COURSEFORPROGRAM_H_INCLUDE

#include "Course.h"
#include "Program.h"
#include "Year.h"

#include<list>
#include<iostream>

/// Клас "CourseForProgram", който пази данните за всяка дисциплина в коя специалност се среща и през кой курс.
class CourseForProgram {
    public:
        ///Конструктор с параметри.
        CourseForProgram(const Course& c, const Program& p) : course(c), program(p) {}

        ///Функция, която довабя оценка към листа.
        void addYear(Year year) { this->years.push_back(year); }

        /// Фунцкията, която  връща  стойността на course.
        const Course& getCourse() const { return this->course; }
        /// Фунцкията, която  връща  стойността на program.
        const Program& getProgram() const { return this->program; }

        ///Функция, проверяваща дали има курс в списъка
        bool hasYear(Year year) {
            for (std::list<Year>::iterator i = this->years.begin();
                i != this->years.end(); ++i) {
                if (*i == year) {
                    return true;
                }
            }
            return false;
        }
        ///Премахва курс от списъка
        void removeYear(Year year) {
            for (std::list<Year>::iterator i = this->years.begin();
                i != this->years.end(); ++i) {
                if (*i == year) {
                    // remove element in i
                    years.erase(i);
                }
            }
        }        

        ///Функцията, която принтира информация за всеки дисциплина, специалност и курс.
        /**
        *Функцията принтира дисциплината и специалността по id,
        * курсът го принтира, като първо вземе неговия размер,
        * след това с цикъл изкарва всички курсове
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
            ///Референция към дисциплина и специалност.
            const Course& course;
            const Program& program;
            ///Лист с курсовете.
            std::list<Year> years;
};
#endif // !COURSEFORPROGRAM_H_INCLUDE

