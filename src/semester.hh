//! A temporary locality for semester probably needs not


#ifndef SEMESTER
#define SEMESTER

#include "mark_sheet.hh"
#include <iomanip>
using namespace std;
class semester{

private:
  std::list<mark_sheet> Mark_Sheet_list;
  bool registered;
public:
  semester();
  int set_sheet(int subj_no, subject * subj);
  int get_grade(int subj[], int tuto[], int obt[], int tot_obt[], char *letterGrade[], double grade[]);
  double get_gpa(double & total_credit);
  int set_mark(int subject, int mark, type t_type);
  bool get_avg_mark(int subject_no, string &avg_sheet);
  bool get_avg_mark(int subject_no, char *avg_sheet);
  bool get_avg_mark(int subject_no);
  int get_grade(int subj, int &mark_obt, char letterGrade[2], double &grade);
  bool is_register(int subject);
  bool is_register();
};
#endif
