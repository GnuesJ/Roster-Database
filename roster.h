//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

#ifndef ROSTER_H
#define ROSTER_H
#define MAX_CAPACITY 1
#include <iostream>
#include "student.h"
#include "Date.h"

class Roster{
    private:
        //variables
        std::string courseName;
        int courseCode;
        int numberOfCredits;
        std::string instructorName;
        //std::string listOfStudents[MAX_CAPACITY];
        Student* listOfStudents;
        int listSize;

        //grow function will grow the dynamic array size
        void grow();

    public:
        //constructors
        Roster();
        Roster(std::string cN, int cC, int nC, std::string iN);
        //Roster(std::string cN, int cC, int nC, std::string iN, Student& lS);

        //Big 3, copy constructor, deconstructor, copy operator
        Roster(Roster&);
        ~Roster();
        Roster& operator=(const Roster&);

        //I/O input
        void input();
        const void output();
        const void outputListOfStudents();

        //Accessors
        const std::string getCourseName();
        const int getCourseCode();
        const int getNumberOfCredits();
        const std::string getInstructorName();
        const std::string getStudentName(const int i);

        //Mutators
        void setCourseName(const std::string cN);
        void setCourseCode(const int cC);
        void setNumberOfCredits(const int nC);
        void setInstructorName(const std::string iN);
        void setDefault();
        void updateStudent();

        //Mutators to add/delete/compare students from the listOfStudents
        void addStudent(); //creates a student obj
        void addStudent(Student& student);
        void addStudent(const std::string last,const std::string first);
        void deleteStudent(std::string last, std::string first);
        void searchStudent(std::string last, std::string first);

        //Operators
        friend std::ostream& operator <<(std::ostream& outs, const Roster&);
        friend std::istream& operator >>(std::istream& inputs, Roster&);
        const Student& operator [](int);

    private:
        //sorting the Student list
        void sortStudentList();
    public:
        //check for default value
        bool checkDefault(const int i)const;
};

#endif
