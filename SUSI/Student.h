#ifndef STUDENT_H_INCLUDE
#define STUDENT_H_INCLUDE

#include<iostream>


///����������� enum ����, ����� ��������� ������ �� �������� - �������, ��������� ��� ��������.
enum Status {ENROLLED, INTERRUPTED, GRADUATED};
 
/// ���� "Student", ����� ���� ������� �� ����� �������
class Student 
{
    public:
        ///�������� ����-����� �� ��������� �� �����
        const static int MAX_STNAME_LEN = 60;
        ///����������� � ���������
        Student(const char*, const int, Status);
        ///����������� �� ��������� � ������� ����.
        Student(std::istream& in);
        
        ///��������� ���� ���� ����� �������� � ������� ���������� ������
        bool operator== (const Student& s2) const;

        ///���������� ������, ����� �� �������� ��������
        const char* getNameStudent() const;
        const int getFN() const;
        Status getStatus() const;
        unsigned int getId() const;

        ///�������, ����� �������� ���������� �� ����-�������
        void setNameStudent(const char*);
        void setFN(const int);
        void setStatus(Status);

        ///�������� �� ���������
        void print(std::ostream& out) const;

     private:
         static unsigned int idStudent;
         /// ���������, ����� ����� id-�� �� ��������� �������
         static unsigned int getNextId() { return idStudent++; }
         const unsigned int id;
         const static int MAX_FN_LEN = 5;
         ///����������� �� ����-�������.
         char name_student[MAX_STNAME_LEN+1];
         int fn;
         Status status;
};

#endif // !STUDENT_H_INCLUDE

