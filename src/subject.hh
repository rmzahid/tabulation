//! A subject class
/*!
  subject class contains the information of subjects offerred
  in any session through out 8 semester.

  May probably introduce who are the course teacher, 2nd examiner etc.
*/

#ifndef SUBJECT
#define SUBJECT
#include <cstring>
#include <iostream>
using namespace std; 
class subject{
private:
  //! Subject number
  int Sub_no;
  //! Title of the subject
  string Name;
  //! Tutorial mark of the subject
  int Tutorial_mark;
  //! Semester end final mark
  int Final_exam;
  //! Credit for this subject
  double Credit;
public:
  //! Inititalize a subject
  int set_subject(int sub_no, int semester, string name, int tutorial_mark, int final_exam, double credit);
  //! Collect information of subject code, title, tutorial, final and credit hour
  int get_subject_no();
  string get_name();
  int get_tutorial();
  int get_final();
  double get_credit();

  friend ostream& operator<<(ostream &output, const subject & sub);
  bool operator==(const int subject) const;

};

#endif

