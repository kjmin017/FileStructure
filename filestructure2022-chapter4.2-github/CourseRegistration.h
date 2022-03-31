#pragma once
#ifndef COURSE
#define COURSE

class Course
{
public:
	// data members
	int CourseIdentifier; int StudentIdentifier;
	float CourseGrade; int NumberOfCreditHours;
	// method
	Course(); // default constructor
	Course& operator = (const Course&);
};

Course::Course()
{//constructor
	CourseIdentifier = 0; StudentIdentifier = 0;
	CourseGrade = 0; NumberOfCreditHours = 0;
}

#endif