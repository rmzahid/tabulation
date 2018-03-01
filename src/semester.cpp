//! semester implementation
#include "semester.hh"

semester::semester()
{
  registered=false;
}

int semester::set_sheet(int subj_no, subject * subj)
{
  registered=true;
  mark_sheet *Mark_sheet;
  Mark_sheet=new mark_sheet;
  Mark_sheet->set_sheet(subj_no, subj);
  Mark_Sheet_list.push_back(*Mark_sheet);

}


int semester::set_mark(int subject_no, int mark, type t_type)
{
  std::list<mark_sheet>::iterator i;
  if(!Mark_Sheet_list.empty())
    {
      for(i=Mark_Sheet_list.begin();i !=Mark_Sheet_list.end();++i)
	{
	  if(*i==subject_no)
	    {
	      i->set_mark(subject_no, mark, t_type);
	      break;
	    }
	}
    }
  else
    {
      int session=0;
      int semester=0;
      mark_sheet new_m;
      new_m.set_sheet( subject_no, NULL);
      new_m.set_mark(subject_no, mark, t_type);
      Mark_Sheet_list.push_back(new_m);
      registered=true;
      return 1;
    }
return 0;

}

bool semester::get_avg_mark(int subject_no, std::string &avg_sheet)
{
  // Yet to implement
}
bool semester::is_register()
{
  std::list<mark_sheet>::iterator j;
   int i;
      for(i=0,j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
	i++;
      if (i>1)
	return (true);
      else
	return(false);

}
bool semester::is_register(int subject_no)
{
  bool result=false;
  int i;
  std::list<mark_sheet>::iterator j;
  result=false;
    {
      for(i=0,j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
	{
	  i++;
	  if (j->get_subject_no()!=subject_no)
	    continue;
	  else
	    {
	      //      j->get_avg_mark(subject_no, avg_sheet);
	      result=true;
	      break;
	    }
	}
    }
    //bug is open !
    // how to detect student is not registered?
return (result && (registered));
}
bool semester::get_avg_mark(int subject_no, char *avg_sheet)

{
  // iterate through marksheet for subject
  // if found then collect mark for 1, 2, diff, 3 and avg  mark
  //               and return
  bool result=false;
  std::list<mark_sheet>::iterator j;
 
    {
      for(j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
	{
	  if (j->get_subject_no()!=subject_no)
	    continue;
	  else
	    {
	      j->get_avg_mark(subject_no, avg_sheet);
	      result=true;
	      //cout<<"Fro Semester"<< avg_sheet;
	      break;
	    }
	}
    }
return result;
}

bool semester::get_avg_mark(int subject_no)
{
  // returns whether difference is 20% of the limit
  bool result=false;
  int avg_sheet;
  std::list<mark_sheet>::iterator j;
 
    {
      for(j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
	{
	  if (j->get_subject_no()!=subject_no)
	    continue;
	  else
	    {
	      result=j->get_avg_mark(subject_no, avg_sheet);
	      //if(!result)
	      //result=avg_sheet;
	      //result=true;
	      //cout<<"Fro Semester"<< avg_sheet;
	      break;
	    }
	}
    }
return result;

}

int semester::get_grade(int subj, int &mark_obt, char *letterGrade, double &grade)
{
  // search for subj mark_sheet  j->get_grade(subj, mark_obt, letterGrade, grade)
  bool result;
  
  std::list<mark_sheet>::iterator j;
 
    {
      for(j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
	{
	  if (j->get_subject_no()!=subj)
	    continue;
	  else
	    {
	      result=j->get_grade(subj, mark_obt, letterGrade, grade);
	      //result=true;
	      //cout<<"Fro Semester"<< avg_sheet;
	      break;
	    }
	}
    }
return result;


}
double semester::get_gpa(double &total_credit)
{
  double gpa, gp, credit;
  gpa=0.0;
  total_credit=0.0;
  std::list<mark_sheet>::iterator i;
  for(i=Mark_Sheet_list.begin();i!=Mark_Sheet_list.end();++i)
    {
      gp=i->get_grade(credit);
      total_credit+=credit;
      gpa+=(gp*(double)credit);
      cout<<"GP "<<gp<<"/ "<<credit<<"/ "<<total_credit<<"// "<<gpa<<"; ";
     
      
    }
  gpa=gpa/total_credit;
  cout<<"GPA--in semester-->"<<gpa<<"--"<<setprecision(3)<<gpa<<endl;

  return gpa;
}
int semester::get_grade(int subj[], int tuto[], int mark_obt[], int tot_obt[], char* letterGrade[], double grade[])
{
  //loop for each subject gradings information for ptinting in tabulation sheet
  bool result;
  std::list<mark_sheet>::iterator j;
  
  int i;
  for(i=0,j=Mark_Sheet_list.begin();j!=Mark_Sheet_list.end();++j)
    {
      subj[i]=j->get_subject_no();
      result=j->get_grade(subj[i], tot_obt[i], letterGrade[i], grade[i]);
      tuto[i]=j->get_mark(Tutorial,subj[i]);
      j->get_avg_mark(subj[i],mark_obt[i]);
      

      i++;
    }
  
  return i;

}


