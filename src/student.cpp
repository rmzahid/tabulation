#include "student.hh"
using namespace std;
int student::set_serial(int serial_no)
{
  Serial_no=serial_no;
}

int student::set_bname(string b_name)
{
  bengName=b_name;
}

int student::set_name(string name)
{
  Name=name;
}

int student::set_father(string father)
{
  Father=father;
}

int student::set_class_roll(int class_roll)
{
  Class_roll=class_roll;
}

int student::set_exam_roll(int exam_roll)
{
  Exam_roll=exam_roll;
}

int student::set_hall(string hall)
{
  Hall=hall;
}

int student::set_address(string address)
{
  Address=address;
}

int student::enter_mark(int semester, int subject_no, double mark, type t_type)
{
  // add some error checking here
  Semester[semester-1].set_mark(subject_no, mark, t_type);
}

int student::register_course(int semester, int sub_no, subject* subj)
{
  Semester[semester-1].set_sheet(sub_no, subj);
}
int student::get_mark(int subj[], int mark[])
{

}

//bool student::get_subject(int semester, int subject)
//{
//}
int student::get_grade(int semester, int subj[], int tuto[], int obt[], int tot_obt[], char* letterGrade[], double grade[])
{
  int size;
  size=Semester[semester-1].get_grade(subj, tuto, obt, tot_obt, letterGrade, grade);
  return size;
}

bool student::get_avg_mark(int semester, int subject_no, string avg_sheet)
{
}
bool student::get_avg_mark(int semester, int subject_no, char * avg_sheet)
{
  if (Semester[semester-1].get_avg_mark(subject_no,avg_sheet))
    return true;
  else
    return false;
  
}

bool student::get_avg_mark(int semester, int subject_no)
{
  int result;
  if(result=Semester[semester-1].get_avg_mark(subject_no))
    {cout<<"RESULT "<<result;
    return result;
    }
  else
    return false;
}
bool student::is_register(int semester)
{
  return(Semester[semester-1].is_register());
}
bool student::is_register(int semester, int subject_no)
{
  return(Semester[semester-1].is_register(subject_no));
}
double student::get_cgpa(int semester, double &t_credit)
{
  double gpa;
  gpa= Semester[semester-1].get_gpa(t_credit);
  cout<<"GPA-in student --->"<<gpa<<setprecision(6)<<gpa<<endl;

  return gpa;
}
int student::operator<(const student rhs) const
{
  // if(this->Class_roll<rhs.Class_roll)
   if(this->Exam_roll<rhs.Exam_roll)
    return 1;
  return 0;
}

ostream& operator <<(ostream &output, const student &std)
{
  student x;
  
  x=std;
  output<<std.Exam_roll<<" "<<std.Class_roll<<std.Name<<endl;
  /*
  list<mark_sheet>::iterator i;
  for(i=x.Mark_Sheet_list.begin();i!=x.Mark_Sheet_list.end();++i)
    {
      output<<*i<<"\t|\t";
    }
  */
  output<<"--STUDENT";
  output<<endl;
  return output;
}

