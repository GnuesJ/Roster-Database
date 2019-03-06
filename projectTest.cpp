//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include "student.h"
#include "roster.h"
#include "Date.h"

////////////////////////////////
//for adding new roster option
//to extend the amount of student to be added
//change #define MAX_CAPACITY 1 (located on roster.h) to any other number
//
//Supervisor Mode
//Username: admin  Password: 123
////////////////////////////////

//checks username and password for supervisor mode
bool checkAuthentication();

//Superviser Mode & User Mode
void supervisorMode();
void userMode();

//grows the roster if it reaches the cap
void grow();

//UI for Supervisor Mode
void createRoster(Roster& roster);
void dropRoster(int courseCode);
void displayRoster(int courseCode);

//selecting a roster for change
void rosterSelect(int i);

//rostersize keeps track of the total amount of dynamic memory for roster
int rosterSize;
//dynamic memory for roster
Roster* roster;


int main()
{
    //sets the roster size to 2
    rosterSize =2;
    roster = new Roster[rosterSize];

    //opens the rosters.txt
    ifstream inputfile;
    inputfile.open("rosters.txt");
    if(inputfile.is_open())
    {
        int index = 0;

        //checks if the file is empty
        if(!(inputfile.peek() == std::ifstream::traits_type::eof()))
        {
            //runs the inputfile till it has no more characters
            while(!inputfile.eof())
            {
                //variables
                std::string courseName;
                int courseCode;
                int credits;
                float gpa;
                std::string professorName;
                std::string first,last, studentID, standing, blank;
                Roster tempRoster;
                Student tempStudent;
                Date date;

                //inputs the data from file to the variables
                inputfile>>courseName>>blank>>courseCode>>blank;
                inputfile>>credits>>blank>>professorName;

                //assigns the variables to the tempRoster
                tempRoster.setCourseName(courseName);
                tempRoster.setCourseCode(courseCode);
                tempRoster.setNumberOfCredits(credits);
                tempRoster.setInstructorName(professorName);

                //takes the student data till it finds "end_roster"
                while(true)
                {
                    //inputs the data from file to the variables
                    inputfile>>first>>blank;

                    //if the first variable find end_roster or if it is blank(eof)
                    //it will break away from the loop
                    if(first == "end_roster" || first == "") break;

                    inputfile>>last>>blank>>studentID>>blank>>standing>>blank;
                    inputfile>>credits>>blank>>gpa>>blank>>date>>blank;

                    //assigns the variables to the tempRoster
                    tempStudent.setName(last,first);
                    tempStudent.setStudentID(studentID);
                    tempStudent.setCredits(credits);
                    tempStudent.setGpa(gpa);
                    tempStudent.setDateOfBirth(date);
                    inputfile>>date;
                    tempStudent.setMatriculationDate(date);
                    tempRoster.addStudent(tempStudent);
                }

                //if the tempRoster ends with a empty name it will not copy to the roster
                if(tempRoster.getCourseName() != "")
                    roster[index] = tempRoster;

                //increase the index to move to the next roster
                ++index;

                //grows the dynamic memory of roster if it gets full
                if(index==rosterSize-1)
                {
                    grow();
                }
            }
        }
        //closes the inputfile
        inputfile.close();
    }
    else
    {
        //tell the user if the file did not open and close the program
        std::cout<<"Error opening the file"<<std::endl;
        return 0;
    }

    //option to select Supervisor Mode or User Mode
    int select;
    std::cout<<"Enter 1 for Supervisor Mode, 2 for User Mode, 3 to EXIT"<<std::endl;
    std::cin>>select;
    if(select == 1){
        //it will continue to Supervisor Mode if the User is verified
        if(checkAuthentication())
        {
            supervisorMode();
        }
        else
        {
            //if it fails it will close the program
            std::cout<<"Error"<<std::endl;
            return 0;
        }
    }
    if(select == 2)
    {
        //enters the User Mode
        userMode();
    }
    if(select ==3){
        return 0;
    }

    //output the data from roster to rosters.txt file
    std::ofstream outfile;
    outfile.open("rosters.txt");
    //if it fails, it will display that it failed
    if(outfile.fail())
    {
        std::cout<<"Failed to open\n";
        return 0;
    }
    for(int i=0; i<rosterSize; i++)
    {
        if(roster[i].getCourseName() != "Default")
        {
            //writes back to the file using overloaded << operator for roster
            outfile<<roster[i];
            outfile<<"end_roster |\n";
        }
    }
    //closes the outfile
    outfile.close();

    return 0;
}






bool checkAuthentication()
{
    std::vector<std::string> fileUser;
    std::vector<std::string> filePassword;
    std::string fileuserr, filepasswordd;
    ifstream myfile;
    myfile.open("database.txt");
    if(myfile.is_open())
    {
        //stores all the username and password to the vectors
        while(!myfile.eof())
        {
            myfile>>fileuserr>>filepasswordd;
            fileUser.push_back(fileuserr);
            filePassword.push_back(filepasswordd);
        }

        //it will loop till the user puts the correct username and password
        while(true){
            std::string userName, password;
            std::cout<<"Enter the user name: ";
            std::cin>>userName;
            for(int i=0; i<userName.length(); i++)
            {
                //changes all the inputs to lowercase
                userName[i] = tolower(userName[i]);
            }
            std::cout<<"Enter the password: ";
            std::cin>>password;
            for(int i=0; i<fileUser.size(); i++)
            {
                if(userName == fileUser[i] && password == filePassword[i])
                {
                    //closes myfile and returns true if it matches the username and password
                    myfile.close();
                    return true;
                }
            }
            std::cout<<"Wrong Username or Password, Try Again\n";
        }
    }
    //if it doesn't open it will return false
    std::cout<<"Error opening the file"<<std::endl;
    return false;
}

void supervisorMode()
{
    int select;
    int selectedRoster;
    int courseCode;
    Roster tempRoster;
    while(true)
    {
        bool found = false;
        Roster tempRoster;

        //selection menu for Supervisor Mode
        std::cout<<"Menu for Supervisor Mode"<<std::endl;
        std::cout<<"Press 1 to adding new Roster"<<std::endl;
        std::cout<<"Press 2 to dropping a Roster"<<std::endl;
        std::cout<<"Press 3 to Displaying a Roster's information"<<std::endl;
        //DISPLAY in the order of last name, first name, student ID
        std::cout<<"Press 4 to Display all Rosters"<<std::endl;
        std::cout<<"Press 5 to Select a Roster"<<std::endl;
        std::cin>>select;
        switch (select)
        {
            case 1:
                tempRoster.input();
                for(int i = 0; i<rosterSize; i ++)
                {
                    if(i == rosterSize-1)
                    {
                        grow();
                    }
                    if(roster[i].getCourseName() == "Default")
                    {
                        roster[i] = tempRoster;
                        std::cout<<"Successfully added\n";
                        break;
                    }
                }
                break;
            case 2:
                std::cout<<"Enter the Course Number to Drop a Roster\n";
                std::cin>>courseCode;
                dropRoster(courseCode);
                break;
            case 3:
                std::cout<<"Enter the Course Number to Display a Roster\n";
                std::cin>>courseCode;
                displayRoster(courseCode);
                break;
            case 4:
                for(int i= 0; i<rosterSize; i++)
                {
                    if(roster[i].getCourseName()!= "Default")
                    {
                        //DISPLAYS in the order of last name, first name, student ID
                        roster[i].output();
                        std::cout<<"\n";
                        found =true;
                    }
                }
                if(!found) std::cout<<"Roster List is EMPTY\n";
                break;
            case 5:
                while(true){
                    std::cout<<"Select a Roster\n";
                    for(int i=0; i<rosterSize; i++)
                    {
                        if(roster[i].getCourseName()!= "Default")
                        {
                            std::cout<<"Press "<<i+1<<" for the Roster: "<<roster[i].getCourseName()<<" "<<roster[i].getCourseCode()<<std::endl;
                        }
                    }
                    std::cin>>selectedRoster;
                    if((selectedRoster>0) && (selectedRoster<=rosterSize) && (roster[selectedRoster-1].getCourseName()!="Default"))
                    {
                        break;
                    }
                    std::cout<<"Wrong input\n";
                }
                rosterSelect(selectedRoster-1);
            default: break;
        }
        std::cout<<"Press 0 to end, else press 1 for Menu"<<std::endl;
        std::cin>>select;
        if(select == 0) break;
    }
}

void userMode()
{
    int select;
    int selectedRoster;
    //loops the menu till the user wants to end the session
    while(true)
    {
        //loops till it displays all the roster's names
        //and till the user gives a correct response
        while(true){
            std::cout<<"Select a Roster\n";
            for(int i=0; i<rosterSize; i++)
            {
                if(roster[i].getCourseName()!= "Default")
                {
                    std::cout<<"Press "<<i+1<<" for the Roster: "<<roster[i].getCourseName()<<" "<<roster[i].getCourseCode()<<std::endl;
                }
            }
            std::cin>>selectedRoster;
            if((selectedRoster>0) && (selectedRoster<=rosterSize) && (roster[selectedRoster-1].getCourseName()!="Default"))
            {
                break;
            }
            std::cout<<"Wrong input\n";
        }
        //selection menu
        string last,  first;
        std::cout<<"Press 1 to Insert new Student to the Roster\n";
        std::cout<<"Press 2 to Remove a Student from the Roster\n";
        std::cout<<"Press 3 to Update a Student in a Roster\n";
        std::cin>>select;
        switch(select)
        {
            case 1:
                roster[selectedRoster-1].addStudent();
                break;
            case 2:
                std::cout<<"Enter the last name of the Student\n";
                std::cin>>last;
                std::cout<<"Enter the first name of the Student\n";
                std::cin>>first;
                roster[selectedRoster-1].deleteStudent(last,first);
                break;
            case 3:
                roster[selectedRoster-1].updateStudent();
                break;
            default: break;
        }
        std::cout<<"Press 0 to EXIT else, Press 1 for Menu\n";
        std::cin>>select;
        if(select == 0) break;
    }
}

void grow()
{
    //temp will store the roster's data
    //the roster will expand the size of its array
    //then the roster will copy all the data from the temp
    Roster temp[rosterSize];
    int tempSize = rosterSize;
    for(int i=0; i<rosterSize; i++)
    {
        temp[i] = roster[i];
    }
    delete [] roster;
    rosterSize*=2;
    roster = new Roster[rosterSize];
    for(int i=0;i<tempSize; i++)
    {
        roster[i] = temp[i];
    }
}


void dropRoster(int courseCode)
{
    bool found = false;
    for(int i=0; i<rosterSize; i++)
    {
        if(roster[i].getCourseCode() == courseCode)
        {
            roster[i].setDefault();
            std::cout<<"Successfully Dropped\n";
            found = true;
            break;
        }
    }
    if(!found)
    {
        std::cout<<"Not found\n";
    }
}

//checks if the courseCode is found first before displaying
void displayRoster(int courseCode)
{
    bool found = false;
    for(int i=0; i<rosterSize; i++)
    {
        if(roster[i].getCourseCode() == courseCode)
        {
            roster[i].output();
            found = true;
            break;
        }
    }
    if(!found)
    {
        std::cout<<"Not found\n";
    }
}
    //selection menu for making change for a roster (supervisor mode only)
void rosterSelect(int i)
{
    int select;
    string last,  first;
    std::cout<<"Press 1 to Insert new Student to the Roster\n";
    std::cout<<"Press 2 to Remove a Student from the Roster\n";
    std::cout<<"Press 3 to Update a Student in a Roster\n";
    std::cout<<"Press 4 to List all Students in the Roster in sorted order\n";
    std::cin>>select;
    switch(select)
    {
        case 1:
            roster[i].addStudent();
            break;
        case 2:
            std::cout<<"Enter the last name of the Student\n";
            std::cin>>last;
            std::cout<<"Enter the first name of the Student\n";
            std::cin>>first;
            roster[i].deleteStudent(last,first);
            break;
        case 3:
            roster[i].updateStudent();
            break;
        case 4:
            roster[i].outputListOfStudents();
            break;
        default: break;
    }
}
