#ifndef STUDENT_H_INCLUDE
#define STUDENT_H_INCLUDE

#include<iostream>


///Декларираме enum клас, който представя статус на студента - записан, прекъснал или завършил.
enum Status {ENROLLED, INTERRUPTED, GRADUATED};
 
/// Клас "Student", който пази данните за всеки студент
class Student 
{
    public:
        ///статична член-данна за дължината на името
        const static int MAX_STNAME_LEN = 60;
        ///конструктор с параметри
        Student(const char*, const int, Status);
        ///конструктор за записване в текстов файл.
        Student(std::istream& in);
        
        ///Проверява дали няма двама студенти с еднакви факултетни номера
        bool operator== (const Student& s2) const;

        ///Константни методи, които не променят обектите
        const char* getNameStudent() const;
        const int getFN() const;
        Status getStatus() const;
        unsigned int getId() const;

        ///Функции, които променят стойността на член-данните
        void setNameStudent(const char*);
        void setFN(const int);
        void setStatus(Status);

        ///Селектор за извеждане
        void print(std::ostream& out) const;

     private:
         static unsigned int idStudent;
         /// Фунцкията, която връща id-то на следващия студент
         static unsigned int getNextId() { return idStudent++; }
         const unsigned int id;
         const static int MAX_FN_LEN = 5;
         ///Деклариране на член-данните.
         char name_student[MAX_STNAME_LEN+1];
         int fn;
         Status status;
};

#endif // !STUDENT_H_INCLUDE

