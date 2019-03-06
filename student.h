//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Date.h"

class Student
{
    private:
    //Member Variables
        std:: string lastName;
        std:: string firstName;
        std:: string studentID;
        std:: string standing;
        int credits;
        float gpa;
        Date dateOfBirth;
        Date matriculationDate;

    public:
        //Constructors
        Student();
        Student(std::string last, std::string first, std::string id);
        Student(std::string last,std::string first, int cred, float gpaa, Date dateBirth,Date matric);

        //Big 3, copy constructor, deconstructor, copy operator
        Student(Student&);
        ~Student();
        Student& operator=(const Student&);

        //Console I/O functions
        void input();
        const void output();
        //lets the user choose what to change
        void change();

        //Accessors
        const std::string getName();
        const std::string getLastName();
        const std::string getFirstName();
        const std::string getStudentID();
        const std::string getStanding();
        const int getCredits();
        const float getGpa();

        //compare method of names
        bool compare(std::string last, std::string first) const;

        //Operators for compare
        bool operator == (const Student& student) ;
        bool operator != (const Student& student) const;
        bool operator < (const Student& student) const;
        bool operator > (const Student& student) const;
        bool operator <= (const Student& student) const;
        bool operator >= (const Student& student) const;

        //Operator for overloading cin and cout
        friend std::ostream& operator <<(std::ostream& outs, const Student&);
        friend std::istream& operator >>(std::istream& inputs, Student&);

        //Mutators
        void setName(std::string last, std::string first);
        void setStudentID(string id);
        void setCredits(int c);
        void setGpa(float g);
        void setDateOfBirth(Date& d);
        void setMatriculationDate(Date& d);

};

#endif
