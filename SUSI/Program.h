#ifndef PROGRAM_H_INCLUDE
#define PROGRAM_H_INCLUDE

#include<iostream>

#include "Year.h"
#include "Course.h"
#include "Generic.h"

/// ���� "Program", ����� ���� ������� �� ����� �����������
class Program {
    public:
        //�������� ����-����� �� ��������� �� �����.
        const static int MAX_PRNAME_LEN = 60;
        ///����������� � ���������.
        ///��������� ���� ����� �� ������������� � � ������������ �������.
        Program(char* name_program) : id(getNextId()) {}
        ///����������� �� ��������� � ������� ����.
        Program(std::istream& in) : id(getNextIntNumber(in))
        {
            assert(in);

            std::cin.getline(this->name_program, MAX_PRNAME_LEN);

        }

        ///��������� ���� ���� ��� ������������ � ������� id
        bool operator== (const Program& p2) const { return p2.id == this->id; }

        /// ���������, �����  �����  ���������� �� id
        unsigned int getId() const { return this->id; }
        /// ���������, �����  �����  ���������� �� name_program
        const char* getNameProgram() const { return this->name_program; }

        ///���������, ����� �������� ���������� �� ����� �����������.
        void print(std::ostream& out) const 
        { 
            out << PROGRAM << '\n';
            out << id << '\n';
            out << this->name_program << '\n'; }

    private:
        ///�������� ����-�����.
        static unsigned int idProgram;
        /// ���������, ����� ����� id-�� �� ���������� �����������.
        static unsigned int getNextId() { return idProgram++; }
        
        //����������� �� ����-�������.
        char name_program[MAX_PRNAME_LEN + 1];
        const unsigned int id;
};

#endif // !PROGRAM_H_INCLUDE
