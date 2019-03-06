//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

#include <iostream>
#include "student.h"

Student:: Student()
{
    lastName="DefaultLast";
    firstName="DefaultFirst";
    studentID="00000000";
    credits=0;
    standing="default";
    gpa=0;
}

Student::Student(std::string last, std::string first, std::string id)
{
    lastName = last;
    firstName = first;
    studentID = id;
    credits = 0;
    standing = "default";
    gpa = 0;
}

Student:: Student(std::string last,std::string first, int cred, float gpaa, Date dateBirth, Date matric)
{
    lastName=last;
    firstName=first;
    setCredits(cred);
    gpa=gpaa;
    dateOfBirth=dateBirth;
    matriculationDate=matric;
}

Student::Student(Student& student)
{
    lastName = student.lastName;
    firstName = student.firstName;
    studentID = student.studentID;
    credits = student.credits;
    standing = student.standing;
    gpa = student.gpa;
    dateOfBirth = student.dateOfBirth;
    matriculationDate = student.matriculationDate;
}

Student::~Student()
{

}

Student& Student::operator=(const Student& student)
{
    if(this == &student)
        return *this;
    lastName = student.lastName;
    firstName = student.firstName;
    studentID = student.studentID;
    credits = student.credits;
    standing = student.standing;
    gpa = student.gpa;
    dateOfBirth = student.dateOfBirth;
    matriculationDate = student.matriculationDate;
    return *this;
}

void Student:: input()
{
    std::string last, first, id;
    int credits;
    float gpa;
    std::cout<<"Last name: "<<std:: endl;
    std::cin>>last;
    std::cout<<"First name: "<<std:: endl;
    std::cin>>first;
    setName(last,first);
    std::cout<<"Student ID\n";
    std::cin>>id;
    setStudentID(id);
    std::cout<<"Credits: "<<std:: endl;
    std::cin>>credits;
    setCredits(credits);
    std::cout<<"Gpa: "<<std:: endl;
    std::cin>>gpa;
    setGpa(gpa);
    //cin.ignore() clears /0 for the getline to work
    std::cin.ignore();
    std::cout<<"Date of Birth: "<<std:: endl;
    dateOfBirth.input();
    std::cout<<"Matriculated Date: "<<std:: endl;
    matriculationDate.input();
}

const void Student:: output()
{
    std::cout<<lastName<<" | "<<firstName<<" | "<<studentID
    <<" | "<<standing<<" | "<<credits<<" | "<<gpa<<" | "<<dateOfBirth<<" | "<<matriculationDate<<std::endl;
}

void Student:: change()
{
    char fix;
    std::cout<<"Do you want to change the information? (y/n): " << std::endl;
    std::cin>>fix;
    if(fix == 'y' || fix == 'Y')
    {
        int selection;
        char select;
        std::string last, first;
        std::string dateOfBirth, matriculationdate;
        do{
            std::cout<<"Enter: (1 for name), (2 for credits), (3 for GPA), (4 for date of birth), (5 for matriculation date: "<<std::endl;
            std::cin>>selection;
            std::cin.ignore();
            switch (selection)
            {
                case 1:
                    std::cout<<"Enter last name: " << std::endl;
                    std::cin>>last;
                    std::cout<<"Enter first name: " << std::endl;
                    std::cin>>first;
                    setName(last, first);
                    break;
                case 2:
                    int credit;
                    std::cout<<"Enter credits: " << std::endl;
                    std::cin>>credit;
                    setCredits(credit);
                    break;
                case 3:
                    float gpa;
                    std::cout<<"Enter gpa: " << std::endl;
                    std::cin>>gpa;
                    setGpa(gpa);
                    break;
                case 4:
                    std::cout<<"Enter date of birth: " << std::endl;
                    std::cin>>dateOfBirth;
                    break;
                case 5:
                    std::cout<<"Enter the matriculation date: " << std::endl;
                    std::cin>>matriculationDate;
                    break;
            }
            std::cout<<"If done press (y)  else press (n): " << std::endl;
            std::cin>>select;
        }while(select=='n');
    }
}


const std::string Student::getName()
{
    //puts the last and first string together
    return lastName + ", " + firstName;
}


const std::string Student::getLastName()
{
    return lastName;
}

const std::string Student::getStudentID()
{
    return studentID;
}

const std::string Student::getFirstName()
{
    return firstName;
}

const std::string Student:: getStanding()
{
    return standing;
}

const int Student:: getCredits()
{
    return credits;
}

const float Student:: getGpa(){
    return gpa;
}

bool Student::compare(std::string last, std::string first) const
{
    if(lastName == last && firstName == first) return true;
    else return false;
}

bool Student::operator == (const Student& student) {
    return (this->lastName == student.lastName) && (this->firstName == student.firstName) && (this->studentID == student.studentID);
}

bool Student::operator != (const Student& student) const{
    return !((this->lastName == student.lastName) && (this->firstName == student.firstName) && (this->studentID == student.studentID));
}

bool Student::operator < (const Student& student) const{
    if(lastName != student.lastName)
        return lastName > student.lastName;
    if(firstName != student.firstName)
        return firstName > student.firstName;
    return studentID > student.studentID;
}

bool Student::operator > (const Student& student) const{
    if(lastName != student.lastName)
        return lastName > student.lastName;
    if(firstName != student.firstName)
        return firstName > student.firstName;
    return studentID > student.studentID;
}

bool Student::operator <= (const Student& student) const{
    if(lastName == student.lastName)
    {
        if(firstName == student.firstName)
            return studentID <= student.studentID;
        else return firstName <= student.firstName;
    }
    return lastName <= student.lastName;
}

bool Student::operator >= (const Student& student) const{
    if(lastName == student.lastName)
    {
        if(firstName == student.firstName)
            return studentID >= student.studentID;
        else return firstName >= student.firstName;
    }
    return lastName >= student.lastName;
}

std::ostream& operator <<(std::ostream& outs, const Student& student)
{
    outs<<student.firstName<<" | "<<student.lastName<<" | "<< student.studentID
    <<" | "<<student.standing<<" | "<<student.credits<<" | "<<student.gpa<<" | "<<student.dateOfBirth<<" | "<<student.matriculationDate<<std::endl;
    return outs;
}

std::istream& operator >>(std::istream& inputs, Student& student)
{
    std::string last, first, id;
    inputs >>last;
    if(last!= "roster_end"){
    last[0] = toupper(last[0]);
    student.lastName = last;
    inputs >>first;
    first[0] = toupper(first[0]);
    student.firstName = first;
    inputs >>id;
    student.studentID = id;

    std::string stand;
    int cred;
    float gpaa;
    Date dob;
    Date matric;
    inputs>>stand;
    student.standing = stand;
    inputs>>cred;
    student.credits = cred;
    inputs>>gpaa;
    student.gpa = gpaa;
    inputs>>dob;
    student.dateOfBirth = dob;
    inputs>>matric;
    student.matriculationDate = matric;
    }
    return inputs;
}

void Student:: setName(std::string last, std::string first)
{
    // toupper will change the first character of the string to a upper case
    last[0]=toupper(last[0]);
    first[0]=toupper(first[0]);
    lastName=last;
    firstName=first;
}

void Student:: setStudentID(std::string id)
{
    studentID = id;
}

void Student:: setCredits(int c)
{
    credits=c;
    //term will determine the correct standing for the credit input
    int term=c/15;
    if(term>=7)
    {
        term = 7;
    }
    switch(term)
    {
        case 0:
            standing = "Lower-Freshman";
            break;
        case 1:
            standing = "Upper-Freshman";
            break;
        case 2:
            standing = "Lower-Sophomore";
            break;
        case 3:
            standing = "Upper-Sophomore";
            break;
        case 4:
            standing = "Lower-Junior";
            break;
        case 5:
            standing = "Upper-Junior";
            break;
        case 6:
            standing = "Lower-Senior";
            break;
        case 7:
            standing = "Upper-Senior";
            break;
    }

}

void Student:: setGpa(float g)
{
    gpa=g;
}

void Student:: setDateOfBirth(Date& d)
{
    dateOfBirth= d;
}

void Student:: setMatriculationDate(Date& d)
{
    matriculationDate = d;
}
