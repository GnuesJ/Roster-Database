//Seung Lee
//12/7/2018
//Project 1
//CS211 Lab

/* Date.h
 *
 * Declaration of the class that holds a date,
 * which is a month-day-year combination.
 *
 * Author: Yosef Alayev
 */


#ifndef DATE_H

#define DATE_H


#include <string>
using namespace std;


class Date
{

   public:

      // Initializes a date to the default value of January 1, 1970.

      Date();


      // Initializes a date to the values in the parameters.  If the

      // date is not legal, sets the date to one of the legal values.

      Date(int m, int d, int y);


      // Returns the month stored by the class

      string getMonth() const;


      // Returns the month stored by the class as a number

      int getMonthNum() const;


      // Returns the day stored by the class

      int getDay() const;


      // Returns the year stored by the class

      int getYear() const;


      // solicit the date from the user

      void input();


      // output the date in a nice format

      void output() const;

    //overloaded operator << and >>

      friend std::ostream& operator <<(std::ostream& outs, const Date&);
      friend std::istream& operator >>(std::istream& inputs, Date&);

      //Big 3, copy constructor, deconstructor, copy operator
      Date(Date&);
      ~Date();
      Date& operator=(const Date&);

   private:

      int month, day, year;

	  void adjust();

};


#endif
