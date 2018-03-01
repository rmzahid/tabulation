//! A session class
/*! The session class is unique to any program.
  A session enrolls students.
  A session offers course for a given semester.

  A session when asked 
       -  prepare average sheet
       - prepare tabulation sheet

*/

#ifndef SESSION
#define SESSION

#include "grade_def.hh"
#include "definition.hh"
#include "student.hh"
#include "subject.hh"

#include <list>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class session{

private:
  //! Session such as 2000-01
  int Session;
  
  //! session enrolls student 
  /*! list of students are here
   */
  list<student> Student_list;

  //! session offers subject
  list<subject> Subject_list;
  
  //! number of students to track a size of class
  int number_of_student;
  //! for internal use only
  double buffer_mark[4];
  double buffer_diff;
  double buffer_final;
  double buffer_total;
 
public:
  //! Constructor of a Session
  session(int session);

  //! Subject offers in which semester
  int subject_offers(//! subject number
		 int sub_no, 
		 //! in which semester
		 int semester,
		 string name, 
		 int tutorial_mark,
		 int final_mark,
		 double credit);

  //! student registration in a session
  int student_register(
		   //! Serial number as supplied from exam section
		   int serial,
		   //! Bengalee name probably in Unicode
		   string bengName, 
		   //! own name in english
		   string name, 
		   string father, 
		   int class_roll, 
		   int exam_roll, 
		   string hall, 
		   string address);

  //! course is registered by student in any semester
  int course_register(int semester,
		  int class_roll, 
		  int subject_no);

  //! show list of students for tutorial or final
  /*! Type of arrangement is either tutorial i.e. class roll
    or final i.e. exam roll. 
    Return value is only roll numbers array.
  */
  int show_list (type t_type,
	     int roll_list[]);

  //!enter a mark for a student
  bool enter_mark( int semester,
		   int subject,
		   int roll,
		   double mark,
		   type t_type);

  //!Prepare average sheet for a subject
  strstream& prepare_avg_sheet( int semester, 
				strstream & strout, 
				int subject_no);

  //!list for students registered in any subject
  bool list_for_exam( int semester,
		      int exam_type,
		      int subject_no,
		      int roll_list[]);
  //! list for thid examination
  int list_for_third_exam(int semester,
		      int subject_no,
		      int roll_list[]);

  //! Prepare tabulation sheet
  int prepare_tabulation_sheet(int semester,
			   strstream &strout,
			   int subject_no);

  //! Prepare tabulation sheet
  int prepare_tabulation_sheet_v2(int semester,
			   strstream &strout,
			   int subject_no);

  //! Output streaming << operator overloading
  friend ostream & operator<<(ostream &output, const session & ses);

private:
  //! initialize printer tab position
  /*! This part needs printer dependent code
   */
  int init_tab (strstream &strout);
  float round2(float x);
};

#endif







