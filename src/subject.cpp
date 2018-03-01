#include "subject.hh"

std::ostream & operator<<(std::ostream &output, const subject & sub)
{
  output<<sub.Sub_no<<" "<<sub.Name<<"\n"<<sub.Tutorial_mark<<"-"<<sub.Final_exam<<std::endl;
}

bool subject::operator==(const int subject_no) const
{
  if(Sub_no==subject_no)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int subject::get_subject_no()
{
  return Sub_no;
}

std::string subject::get_name()
{
  std::string temp;
  temp=Name;
  return temp;
}

double subject::get_credit()
{
  return Credit;
}
int subject::get_tutorial()
{
  return Tutorial_mark;
}

int subject::get_final()
{
  return Final_exam;
}

int subject::set_subject(int semester, int sub_no, std::string name, int tutorial_mark, int final_exam, double credit)
{
  Sub_no=sub_no;
  Name=name;
  Tutorial_mark=tutorial_mark;
  Final_exam=final_exam;
  Credit=credit;
}
