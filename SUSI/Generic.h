#ifndef GENERIC_H_INCLUDE
#define GENERIC_H_INCLUDE

#include<iostream>
#include<cstring>

inline int getNextIntNumber(std::istream& in)
{
	int c;
	in >> c;
	return c;
} 

#define STUDENT  "#STUDENT:"
#define COURSE  "#COURSE:"
#define PROGRAM  "#PROGRAM:"
#define STUDENT_TO_PROGRAM  "#STUDENT TO PROGRAM:"
#define STUDENT_TO_COURSE  "#STUDENT TO COURSE"
#define COURSE_FOR_PROGRAM  "#COURSE FOR PROGRAM:"

#endif // !GENERIC_H_INCLUDE
