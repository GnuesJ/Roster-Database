//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

#include <iostream>
#include "roster.h"


void Roster::grow()
{
    Student tempStudent[listSize];
    int tempSize =listSize;
    for(int i=0; i<tempSize; i++)
    {
        tempStudent[i] = listOfStudents[i];
    }
    delete [] listOfStudents;
    listSize = listSize*2;
    listOfStudents = new Student[listSize];
    for(int i=0; i<tempSize; i++)
    {
        listOfStudents[i] = tempStudent[i];
    }
}

Roster::Roster()
{
    courseName = "Default";
    courseCode = 0;
    numberOfCredits = 0;
    instructorName = "Default";
    listSize = MAX_CAPACITY;
    listOfStudents = new Student[listSize];

}

Roster::Roster(std::string cN, int cC, int nC, std::string iN)
{
    courseName = cN;
    courseCode = cC;
    numberOfCredits = nC;
    instructorName = iN;
    listSize = MAX_CAPACITY;
    listOfStudents = new Student[listSize];
}
/*
Roster::Roster(std::string cN,  int cC, int nC, std::string iN, Student& lS)
{
    courseName = cN;
    courseCode = cC;
    numberOfCredits = nC;
    instructorName = iN;
    listSize = MAX_CAPACITY;
    listOfStudents = new Student[listSize];
    for(int i=0;i<listSize;i++)
    {
        listOfStudents[i] = lS[i];
    }
    sortStudentList();
}
*/
Roster::Roster(Roster& roster)
{
    courseName = roster.courseName;
    courseCode = roster.courseCode;
    numberOfCredits = roster.numberOfCredits;
    instructorName = roster.instructorName;
    listSize = roster.listSize;
    listOfStudents = new Student[listSize];

}


Roster::~Roster()
{
    delete [] listOfStudents;
}

Roster& Roster::operator=(const Roster& roster)
{
    if(this == &roster)
        return *this;
    courseName = roster.courseName;
    courseCode = roster.courseCode;
    numberOfCredits = roster.numberOfCredits;
    instructorName = roster.instructorName;
    listSize = roster.listSize;
    delete [] listOfStudents;
    listOfStudents = new Student[listSize];
    for(int i=0; i<listSize; i++)
        {
            listOfStudents[i] = roster.listOfStudents[i];
        }
    return *this;
}

void Roster::input()
{
    std::string cN;
    int cC, nC;
    std::string iN;
    std::string last,first;
    std::cout<<"Enter the Course Name: "<<std::endl;
    std::cin>>cN;
    courseName = cN;
    std::cout<<"Enter the Course Code: "<<std::endl;
    std::cin>>cC;
    courseCode = cC;
    std::cout<<"Enter the Number Of Credits: "<<std::endl;
    std::cin>>nC;
    numberOfCredits = nC;
    std::cout<<"Enter the Instructor Name: "<<std::endl;
    std::cin>>iN;
    instructorName = iN;
    std::cout<<"Adding a student to the List\n";
    for(int i = 0; i<listSize; i++)
    {
        listOfStudents[i].input();
    }
    sortStudentList();
}

const void Roster::output()
{
    std::cout<<"Course Name:         "<<getCourseName()<<std::endl;
    std::cout<<"Course Code:         "<<getCourseCode()<<std::endl;
    std::cout<<"Number Of Credits:   "<<getNumberOfCredits()<<std::endl;
    std::cout<<"Instructor Name:     "<<getInstructorName()<<std::endl;
    outputListOfStudents();

}

const void Roster::outputListOfStudents() {
    bool emptyList = true;
    std::string space = "  ";
    std::cout << "List Of Students:" << std::endl;
    int counter = 1;
    for (int i = 0; i < listSize; i++) {
        if (!(listOfStudents[i].compare("DefaultLast","DefaultFirst"))) {
            emptyList = false;
            if(i>8)
            {
                space = " ";
            }
            std::cout << "  " <<counter<<"."<<space;
            listOfStudents[i].output();
            counter++;
        }
    }
    if (emptyList == true)
    {
        std::cout<<"  List of Students is EMPTY"<<std::endl;
    }
}

//definitions of the Accessors
const std::string Roster::getCourseName()
{
    return courseName;
}

const int Roster::getCourseCode()
{
    return courseCode;
}

const int Roster::getNumberOfCredits()
{
    return numberOfCredits;
}

const std::string Roster::getInstructorName()
{
    return instructorName;
}

const std::string Roster::getStudentName(const int i)
{
    if(i>=listSize)
    {
        return "Error input";
    }
    return listOfStudents[i].getName();
}

//definitions of the Mutators
void Roster::setCourseName(const std::string cN)
{
    courseName = cN;
}

void Roster::setCourseCode(const int cC)
{
    courseCode = cC;
}

void Roster::setNumberOfCredits(const int nC)
{
    numberOfCredits = nC;
}

void Roster::setInstructorName(const std::string iN)
{
    instructorName = iN;
}

void Roster::setDefault()
{
    courseName = "Default";
    courseCode = 0;
    numberOfCredits = 0;
    instructorName = "Default";
    delete [] listOfStudents;
    listSize = MAX_CAPACITY;
    listOfStudents = new Student[listSize];

}

void Roster::updateStudent()
{
    std::string last, first;
    std::cout<<"Enter the last name of the Student\n";
    std::cin>>last;
    std::cout<<"Enter the first name of the Student\n";
    std::cin>>first;
    bool found = false;
    last[0] = toupper(last[0]);
    first[0] = toupper(first[0]);
    for(int i=0; i<listSize; i++)
    {
        if(listOfStudents[i].compare(last,first))
        {
            int selection;
            std::string id;
            int credits;
            float gpa;
            Date date;
            while(true){
                std::cout<<"Press 1 to change the student's name\n";
                std::cout<<"Press 2 to change the student's ID#\n";
                std::cout<<"Press 3 to change the Credits\n";
                std::cout<<"Press 4 to change the GPA\n";
                std::cout<<"Press 5 to change the Date Of Birth\n";
                std::cout<<"Press 6 to change the Matriculation Date\n";
                std::cin>>selection;
                switch(selection)
                {
                    case 1:
                        std::cout<<"Enter the updated last name of the Student\n";
                        std::cin>>last;
                        std::cout<<"Enter the updated first name of the Student\n";
                        std::cin>>first;
                        listOfStudents[i].setName(last,first);
                        break;
                    case 2:
                        std::cout<<"Enter the updated Student ID#\n";
                        std::cin>>id;
                        listOfStudents[i].setStudentID(id);
                        break;
                    case 3:
                        std::cout<<"Enter the updated Credits\n";
                        std::cin>>credits;
                        listOfStudents[i].setCredits(credits);
                        break;
                    case 4:
                        std::cout<<"Enter the updated GPA\n";
                        std::cin>>gpa;
                        listOfStudents[i].setGpa(gpa);
                        break;
                    case 5:
                        std::cout<<"Enter the updated Date of Birth\n";
                        date.input();
                        listOfStudents[i].setDateOfBirth(date);
                        break;
                    case 6:
                        std::cout<<"Enter the updated Matriculation Date\n";
                        date.input();
                        listOfStudents[i].setMatriculationDate(date);
                        break;
                    default: break;
                }
                std::cout<<"Press 0 to EXIT else, Press 1 to update more\n";
                std::cin>>selection;
                if(selection == 0) break;
            }

            sortStudentList();
            found = true;
            break;
        }
    }
    if(!found) std::cout<<"Student Not found\n";
}

void Roster::addStudent()
{
    Student temp;
    temp.input();
    for(int i=0; i<listSize; i++)
    {
        if(listOfStudents[i].compare("DefaultLast","DefaultFirst"))
        {
            listOfStudents[i] = temp;
            sortStudentList();
            break;
        }
        //checks if the list is capped
        if(i==(listSize-1))
        {
            grow();
        }
    }
}

void Roster::addStudent(Student& student)
{
    for(int i=0; i<listSize; i++)
    {
        if(i==(listSize-1))
        {
            grow();
        }
        if(listOfStudents[i].compare("DefaultLast","DefaultFirst"))
        {
            listOfStudents[i] = student;
            sortStudentList();
            break;
        }
        //checks if the list is capped
    }
}


//definitions of add/delete/search
void Roster::addStudent(const std::string last,const std::string first)
{
    for(int i=0; i<listSize; i++)
    {
        if(listOfStudents[i].compare("DefaultLast","DefaultFirst"))
        {
            listOfStudents[i].setName(last,first);
            sortStudentList();
            break;
        }
        //checks if the list is capped
        if(i==(listSize-1))
        {
            grow();
        }
    }
}

void Roster::deleteStudent(std::string last, std::string first)
{
    bool found = false;
    last[0] = toupper(last[0]);
    first[0] = toupper(first[0]);
    for(int i=0; i<listSize; i++)
    {
        if(listOfStudents[i].compare(last,first))
        {
            listOfStudents[i].setName("DefaultLast","DefaultFirst");
            sortStudentList();
            found = true;
            break;
        }
    }
    if(!found) std::cout<<"Student Not found\n";
}

void Roster::searchStudent(std::string last, std::string first)
{
    last[0] = toupper(last[0]);
    first[0] = toupper(first[0]);
    bool found = false;
    for(int i=0; i<listSize; i++)
    {
        if(listOfStudents[i].compare(last,first))
        {
            std::cout<<listOfStudents[i].getName()<<" is found"<<std::endl;
            found =true;
            break;
        }
    }
    if(!found)
    {
        std::cout<<"Not found"<<std::endl;
    }
}

std::ostream& operator <<(std::ostream& outs, const Roster& roster){
    outs<<roster.courseName<<" | "<<roster.courseCode<<" | "<<roster.numberOfCredits<<" | "
    <<roster.instructorName<<std::endl;
    for (int i = 0; i < roster.listSize; i++) {
        if (!(roster.checkDefault(i))) {
            outs <<roster.listOfStudents[i];
        }
    }
    return outs;
}

std::istream& operator >>(std::istream& inputs, Roster& roster)
{
    string cN;
    int cC, nC;
    string iN;
    inputs>>cN;
    roster.courseName = cN;
    inputs>>cC;
    roster.courseCode = cC;
    inputs>>nC;
    roster.numberOfCredits = nC;
    inputs>>iN;
    roster.instructorName = iN;
    for(int i = 0; i<roster.listSize; i++)
    {
        inputs>>roster.listOfStudents[i];
    }
    roster.sortStudentList();
    return inputs;
}

const Student& Roster::operator [](int i)
{
    if(i < listSize)
        return listOfStudents[i];
    else
    return listOfStudents[0];
    cout<<"Invalid index"<<endl;
}

void Roster:: sortStudentList(){
    for(int i=0; i<listSize; i++){
        int lowest = i;
        for(int j=i+1; j<listSize; j++){
            if((listOfStudents[lowest]>listOfStudents[j]) || checkDefault(lowest))
                lowest =j;
        }
        if(i!=lowest){
            Student temp;
            temp = listOfStudents[i];
            listOfStudents[i] = listOfStudents[lowest];
            listOfStudents[lowest] = temp;
        }
    }
}

bool Roster:: checkDefault(const int i)const {
    if(listOfStudents[i].compare("DefaultLast","DefaultFirst"))
        return true;
    else return false;
}
