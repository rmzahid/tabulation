//! A student class.
/*! 
  The student class is  for keeping students information
  such as
  - name
  - father's name
  - bengali name
  etc.
*/

#ifndef STUDENT 
#define STUDENT

#include <stdio.h>
#include <string>
#include <list>
#include "subject.hh"
#include "mark_sheet.hh"
#include "definition.hh"
#include "semester.hh"
#include <iomanip>
using namespace std;

class student{
  //! This number is based on the exam office generation
  int Serial_no;
  string bengName;
  string Name;
  string Father;
  int Class_roll;
  int Exam_roll;
  string Hall;
  string Address;
  //  list<mark_sheet> Mark_Sheet_list;
  //! Eight semester for a session is it maximum??
   semester Semester[8];
public:
  //! this is copy constructor used for STL
  student(const student& obj)  { *this = obj; }
  //!Normal initializer
  student(){}
  //! this assignment operator
  // student& operator=(const student& obj); 
  //  student& operator=(student const &obj);
  //! entry of serial number as supplied from exm office
  int set_serial(int serial_no);
  int set_bname(string bengName);
  int set_name(string name);
  int set_father(string father);
  int set_class_roll(int class_roll);
  int set_exam_roll(int exam_roll);
  int set_hall(string hall);
  int set_address(string address);
  // set_session(int session, int semester, int subject);
  int enter_mark(int semester, int subject, double mark, type t_type);
  int register_course(int semester, int sub_no, subject* subj);
  int get_mark(int subj[], int mark[]);
  int get_grade(int semester, int subj[], int tuto[], int obt[], int tot_obt[], char* letterGrade[], double grade[]);
  bool get_avg_mark(int semester, int subject_no, string avg_sheet);
  bool get_avg_mark(int semester, int subject_no, char * avg_sheet);
  bool get_avg_mark(int semester, int subject_no);
  double get_cgpa(int semester, double &t_credit);
    bool is_register(int semester, int subject_no);
  bool is_register(int semester);
  int get_Exam_roll(){return Exam_roll;}
  int get_Class_roll(){return Class_roll;}
  std::string get_name(){return Name;} 
  std::string get_hall(){return Hall;}
  // operator over loading
  int operator<(const student rhs) const;
  friend ostream& operator <<(ostream &output, const student &std);
};

#endif 
