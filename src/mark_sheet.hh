//! Mark sheet for a subject for a given student

#ifndef MARK_SHEET
#define MARK_SHEET

//#include <tgmath.h>
#include <strstream>
#include <cstring>
#include <iostream>
#include <list>
#include <stdlib.h>
#include "definition.hh"
#include "subject.hh"
extern int round(float);
using namespace std;
class mark_sheet{
private:
  //int Session;
  //int Semester;
  //double tutorial;
  double Marks[4];
  int Subject_no;
  subject *Subject;
public:
  mark_sheet();
  int set_sheet(int subject_no, subject* subj);
  bool set_mark(int sub_no, int mark, type t_type);
  int get_subject_no(){return Subject_no;}
  double get_mark(type t_type, int sub_no);
  bool get_avg_mark(int subject_no, string &avg_sheet);
  bool  get_avg_mark(int subject_no, char *avg_sheet);
  bool  get_avg_mark(int subject_no, int &mark_avg);
  bool get_grade(int subject_no,int &mark_obt,  char *grade, double &gp);
  double get_grade(double &credit);
  bool operator==(int const sub_no) const;
  friend ostream & operator<<(ostream &output, const mark_sheet & msheet);

};

#endif
