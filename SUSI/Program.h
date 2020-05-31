#ifndef PROGRAM_H_INCLUDE
#define PROGRAM_H_INCLUDE

#include<iostream>

#include "Year.h"
#include "Course.h"
#include "Generic.h"

/// Клас "Program", който пази данните за всяка специалност
class Program {
    public:
        //Статична член-данна за дължината на името.
        const static int MAX_PRNAME_LEN = 60;
        ///Конструктор с параметри.
        ///Проверява дали името на специалността е в позаволените граници.
        Program(char* name_program) : id(getNextId()) {}
        ///Конструктор за записване в текстов файл.
        Program(std::istream& in) : id(getNextIntNumber(in))
        {
            assert(in);

            std::cin.getline(this->name_program, MAX_PRNAME_LEN);

        }

        ///Проверява дали няма две специалности с еднакво id
        bool operator== (const Program& p2) const { return p2.id == this->id; }

        /// Фунцкията, която  връща  стойността на id
        unsigned int getId() const { return this->id; }
        /// Фунцкията, която  връща  стойността на name_program
        const char* getNameProgram() const { return this->name_program; }

        ///Функцията, която принтира информация за всяка специалност.
        void print(std::ostream& out) const 
        { 
            out << PROGRAM << '\n';
            out << id << '\n';
            out << this->name_program << '\n'; }

    private:
        ///Статична член-данна.
        static unsigned int idProgram;
        /// Фунцкията, която връща id-то на следващата специалност.
        static unsigned int getNextId() { return idProgram++; }
        
        //Деклариране на член-данните.
        char name_program[MAX_PRNAME_LEN + 1];
        const unsigned int id;
};

#endif // !PROGRAM_H_INCLUDE
