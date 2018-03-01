#include "session.hh"
#include <math.h>
using namespace std;
//! Constructor of a Session
session::session(int session)
{
  Session=session;
}

//! Subject offers in which semester
int session::subject_offers(int sub_no,
			int semester,
			string name, 
			int tutorial_mark,
			int final_mark,
			double credit)
{
  subject *aSubject;
  aSubject=new subject;
  aSubject->set_subject(sub_no, semester, name, tutorial_mark, final_mark, credit);
  Subject_list.push_back(*aSubject);

}

//! student registration in a session
int session::student_register(int serial,
			  string bengName, 
			  string name, 
			  string father, 
			  int class_roll, 
			  int exam_roll, 
			  string hall, 
			  string address)
{
  int found=0;
  list<student>::iterator i;
  for(i=Student_list.begin();i!=Student_list.end();++i)
    {
      if (i->get_Class_roll()==class_roll)
	{
	  found=1;
	  break;
	}
    }
  if(found==0)
    {
      student *Student;
      Student=new student;
      Student->set_serial(serial);
      Student->set_bname(bengName);
      Student->set_name(name);
      Student->set_father(father);
      Student->set_class_roll(class_roll);
      Student->set_exam_roll(exam_roll);
      Student->set_hall(hall);
      Student->set_address(address);
      Student_list.push_back(*Student);
    }
  return found;
}
//! course is registered by student in any semester
int session::course_register(int semester,
		int class_roll, 
		int subject_no)
{
  list<student>::iterator i;
  for(i=Student_list.begin();i!=Student_list.end();++i)
    {
      if (i->get_Class_roll()==class_roll)
	{
	  static subject *temp_subj;
		
	  // find out subject object and pass it to mark sheet
	  list<subject>::iterator j;
	  for(j=Subject_list.begin();j!=Subject_list.end();++j)
	    {
	      if (subject_no==j->get_subject_no())
		{
		  temp_subj=&(*j);
		  break;
		}
	    }
	  i->register_course(semester, subject_no, temp_subj);
	  break;
	}
    }

  
}

//! show list of students for tutorial or final
/*! Type of arrangement is either tutorial i.e. class roll
  or final i.e. exam roll. 
  Return value is only roll numbers array.
*/

int session::show_list (type t_type,
	     int roll_list[])
{
  int  j;
  if(t_type == Tutorial)
    {
      list<student>::iterator i;
      //Student_list.sort();
      list<student> newStudent_list;
      newStudent_list=Student_list;

      for(i=newStudent_list.begin(),j=0;i!=newStudent_list.end();++i,j++)
	{
	  roll_list[j]=i->get_Class_roll();
	}
      return 1; // sorted on class roll
    }
  else
    {
      list<student> newStudent_list;
      newStudent_list=Student_list;
      list<student>::iterator i;
      newStudent_list.sort();
      for(i=newStudent_list.begin(),j=0;i!=newStudent_list.end();++i,j++)
	{
	  roll_list[j]=i->get_Exam_roll();
	}
      return 2; // sorted on exam roll
    }
}

//!enter a mark for a student
// check for maximum mark should be 
// less or equal to 40% for Theory 
// and 60% for Practical
bool session::enter_mark( int semester,
		 int subject,
		 int roll,
		 double mark,
		 type t_type)
{
  list<student>::iterator i;
  bool got;
  if(t_type== Tutorial)
    {
      got=false;
      //Student_list.sort();
      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  if(i->get_Class_roll()==roll)
	    {
	      got=true;
	      break;
	    }
	}
      if(got)
	i->enter_mark(semester, subject,  mark, t_type);
      //break;
    }
  else
    {
      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  //	  cout<<i->get_Exam_roll()<<endl;
	  if(i->get_Exam_roll()==roll)
	    {
	      got=true;
	      break;
	    }
	}
      if(got)
	i->enter_mark(semester, subject, mark, t_type);
      //break;
          }
  return got;

}

//!Prepare average sheet for a subject
//* If subject no is 0 means all subject to call
//*
strstream& session::prepare_avg_sheet(int semester, 
				      strstream & strout, 
				      int subject_no)
{
  double final_mark;
  double i_mark[2],i_diff;
  int c_subject_no;
 
  // ask for subject title
  list<subject>::iterator j;
  for(j=Subject_list.begin();j!=Subject_list.end();++j)
    {
      if (subject_no==0)
	{
	  c_subject_no=j->get_subject_no();
	  final_mark=j->get_final();
	}

      else
      	{
	  if(j->get_subject_no()!=subject_no)
	    continue;
	  else
	    {
	      final_mark=j->get_final();
	      c_subject_no=subject_no;
	    }
	  
	}
     
      if((c_subject_no>((int((semester-1)/2)+1)*100+int((semester-1)%2)*50)) && c_subject_no<((((semester)/2+1)*100)+int((semester)%2)*50))
	{
	  strout<<"\n\nSubject CSE: "<<c_subject_no<<"\nFull Mark: "<<final_mark<<endl;
	  strout<<"Roll\t| 1st\t2nd\tDiff\t3rd\tAverage"<<endl;
	  //ask for averagemark from student list
	  //string avg_sheet
	  char* avg_sheet;
	  int line_max_limit=180;
	  avg_sheet=new char[line_max_limit];
	  for(int countx=0;countx<line_max_limit;countx++)
	    avg_sheet[countx]='\0';
	  list<student> newStudent_list;
	  newStudent_list=Student_list;
	  newStudent_list.sort();
	  list<student>::iterator i;
	  for(i=newStudent_list.begin();i!=newStudent_list.end();++i)
	    {
	      //avg_sheet=new char[180];
	      if(i->is_register(semester,c_subject_no))
	      {
	      strout<<i->get_Exam_roll()<<"\t|  ";
	      i->get_avg_mark(semester,c_subject_no,avg_sheet);
	      strout<<avg_sheet;	
	      //strout<<endl;
	      avg_sheet[0]='\0';
	      for(int countx=0;countx<line_max_limit;countx++)
		avg_sheet[countx]='\0';
	      }
	      //delete avg_sheet;
	    }
	    delete avg_sheet;
	}
    }
  return strout;

  
}


  
//! list for thid examination
int session::list_for_third_exam(int semester,
			     int subject_no,
			     int roll_list[])
{
  int k=0;
  int c_subject_no;

  // find the final mark for the subject

  list<subject>::iterator j;
  for(j=Subject_list.begin();j!=Subject_list.end();++j)
    {
      if (subject_no!=0)
	if(j->get_subject_no()!=subject_no)
	  {
	    continue;
	  }
      // final_mark=j->get_final();
	 
      c_subject_no=j->get_subject_no();
    

      Student_list.sort();
      list<student>::iterator i;
      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  //	  calc_avg(c_subject_no,i->get_Exam_roll());
	  
	  if( i->get_avg_mark(semester,c_subject_no)!=false )
	    {
	      roll_list[k]=i->get_Exam_roll();
	      k++;
	    }
	}
    }
}
//! list for final or tutorial examination
bool session::list_for_exam(int semester,
			    int exam_type,
			     int subject_no,
			     int roll_list[])
{
  int k=0;
  bool answer;
  int c_subject_no;
  answer=false;
  // find the final mark for the subject

  list<subject>::iterator j;
  for(j=Subject_list.begin();j!=Subject_list.end();++j)
    {
      if (subject_no!=0)
	if(j->get_subject_no()!=subject_no)
	  {
	    continue;
	  }
      // final_mark=j->get_final();
	 
      c_subject_no=j->get_subject_no();
    
      if(exam_type!=Tutorial)
	{
	  list<student> newStudent_list;
	  newStudent_list=Student_list;
	  newStudent_list.sort();
	  list<student>::iterator i;
	  for(i=newStudent_list.begin();i!=newStudent_list.end();++i)
	    {
	      
	      if( i->is_register(semester,c_subject_no)!=false )
		{
		  roll_list[k]=i->get_Exam_roll();
		  answer=true;
		  k++;
		}
	    }
	}
      else
	{	 
	  list<student> newStudent_list;
	  newStudent_list=Student_list;
	  list<student>::iterator i;
	  for(i=newStudent_list.begin();i!=newStudent_list.end();++i)
	    {
	      
	      if( i->is_register(semester,c_subject_no)!=false )
		{
		  roll_list[k]=i->get_Class_roll();
		  answer=true;
		  k++;
		}
	    }

	}
    }
}
#define LINE 70
#define LINESIZE 250
#define MAX_SIZE 13
#define SUB_SIZE 69
#define Top 14
#define Mark_Space 8
int session::init_tab(strstream& strout)
{
  int char_count=0;
  char Esc=0x1b;
  char PrnLineSpace=0x32;
  char PrnDollar=0x24;
  char *HorPos;
  int AbsHorPrnPos=500;
  HorPos=(char*)&AbsHorPrnPos;
 
  //int sub
  //double final_fullmark,tutorial_fullmark,  total_gp, gpa, credit, total_credit;
  //int x_final, t_final, total_fullmark;
  //double i_mark[4],i_diff;
  //bool got;
  int k,m;
     
  //====================== initialize printer tabs
  //  unsigned char tab_init[23]={0x1b,0x44,22,33,39,46,53,59,66,73,79,86,93,100,107,113,121,127,132,137,139,144,150};
  unsigned char tab_init[24]={0x1b,0x44,0x08,0x0c,0x10,0x13,0x17,0x1a,0x1e,0x21,0x25,0x28,0x2c,0x2f,0x33,0x37,0x3b,0x3f,0x43,0x47,0x4c,0x50,0x55,0x00};
  int tab_stops[]={22,33,39,46,53,59,66,73,79,86,93,100,107,113,121,127,132,137,139,144,150,0};
  //char Tab_stops[21];
  //for(k=0;k<21;k++)
  //  Tab_stops[k]=(char)tab_stops[k];
 
  strout.write((const char*)tab_init,24);
  char_count+=24;
  //====================== initialize font pitch
  unsigned char font_pitch[2]={0x1b,0x4d};
  strout.write((const char*) font_pitch,2);
  char_count+=2;
  return char_count;
          
}

//! Prepare tabulation sheet
int session::prepare_tabulation_sheet(
				  int semester,
				  strstream &strout,
				  int registration_no)
{
  int total_size;

  char SI=0x0f;
  char DC2=0x12;
  int char_count[LINE];
  char line_space=' '; 
  char Esc=0x1b;
  char PrnLineSpace=0x30; //1/8 inch line spacing
  char PrnDollar=0x24;    // $ code
  char *HorPos, *FrontHorPos;
  int AbsHorPrnPos=335; //341; //360;
  HorPos=(char*)&AbsHorPrnPos;
  int FrontPrnPos=116;
  FrontHorPos=(char*)&FrontPrnPos;
  int flag;
  int size;
  int cnt,k,m;
  double gpa,pcgpa,cgpa;
  int *subj, *tut, *mark_obt, *tot_obt;
  subj=new int[MAX_SIZE];
  tut=new int[MAX_SIZE];
  mark_obt=new int[MAX_SIZE];
  tot_obt=new int[MAX_SIZE];
  
  char **letterGrade;
  letterGrade= new char*[MAX_SIZE];
  for(cnt=0;cnt<MAX_SIZE;cnt++)
    letterGrade[cnt]=new char[3];
  double *gp;
  gp= new double[MAX_SIZE];


  //============ ::::::::::: Printing Session :::::::::::::============

  init_tab(strout);
  
  strout<<endl;

  strstream *tempstr[LINE];
  strstream *subject_title[MAX_SIZE];
  char x[LINE][LINESIZE];
  char sub[MAX_SIZE][SUB_SIZE];

  //===================== initialize printable lines
  for(k=0;k<LINE;k++)
    {
      for(m=0;m<LINESIZE;m++)
        x[k][m]='\0';
      tempstr[k]=new strstream(x[k],LINESIZE);
      // initialize with endl
      //      *tempstr[k]<<k%10;
      //      char_count[k]=1;
    }

  //====================== initialize subject information
  for(k=0;k<MAX_SIZE;k++)
    {
      for(m=0;m<SUB_SIZE;m++)
        sub[k][m]='\0';
      subject_title[k]=new strstream(sub[k],SUB_SIZE);
    }                                                                           
 //===================== put subject titles
  int sub_no_avg,First,Second,ses_sem;
  list<subject>::iterator sub_j;
  for(sub_j=Subject_list.begin(),k=0; sub_j!=Subject_list.end(); ++sub_j)
    {
      sub_no_avg=sub_j->get_subject_no();
//--->clean it
      First=int(sub_no_avg/100);
      Second=int((sub_no_avg-First*100)/10);
      if(Second>=5)
	ses_sem=First+1;
      else
	ses_sem=First;
//-->upto this
      if(ses_sem==semester)
	{
	  subject_title[k]->write(&Esc,1);
	  subject_title[k]->write(&PrnDollar,1);
	  subject_title[k]->write(HorPos,2);
	  
	  *subject_title[k]<<""<<sub_j->get_subject_no()<<"    "<<sub_j->get_name();
	  k++;
	}
    }
  int t_credit;                                                                                
  //======================= End of initialization ================
  if (registration_no==0)
    {
      //loop for all students
      //j->get_cgpa(semester);
      //j->get_grade(subj[],tut[],mark_obt[],tot_obt[],letterGrade[],gp[]);
      Student_list.sort();
      list<student>::iterator i;

      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  gpa=i->get_cgpa(semester,(double&)t_credit);
	  size=i->get_grade(semester,subj,tut,mark_obt,tot_obt,letterGrade,gp);
	  
	}
    }
  else
    {
      
      //loop till the student found
      list<student>::iterator i;
     for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  if (i->get_Exam_roll()!= registration_no)
	    {
	      continue;
	    }
	  else
	    {
	      int line_count;
	      line_count=0;
	      
	      gpa=i->get_cgpa(semester,(double&)t_credit);

	      size=i->get_grade(semester,subj,tut,mark_obt,tot_obt,letterGrade,gp);
	      if(semester>1)
		{
		  pcgpa=0;
		  for(cnt=1;cnt<semester;cnt++)
		    {
		      pcgpa+=i->get_cgpa(cnt,(double&)t_credit);
		    }
		  cgpa=(gpa+pcgpa)/semester;

		}
	      // ---------- Init line spacing
	      tempstr[line_count]->write(&Esc,1);
	      //tempstr[line_count]->write(&PrnLineSpace,1);
	      char Plus='+';
	      char Line360Sp=0x31;
	      tempstr[line_count]->write(&Plus   ,1);
	      tempstr[line_count]->write(&Line360Sp, 1);
	      char_count[line_count]+=2;

	      int line_loop;
	      // loop till printable zone is there
	      //	      for(line_loop=0;line_loop<Top;line_loop++)
	      //*tempstr[line_count]<<endl;
	      //char_count+=Top;

	      //------------ 9th line
	      line_count=11;//9 for 1/8 gap
	      //*tempstr[line_count]<<Line_Space<<serial_no;
	      tempstr[line_count]->write(&SI,1);
	      *tempstr[line_count]<<sub[0];
	      tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      tempstr[line_count]->write(&SI,1);
	      char_count[line_count]+=strlen(sub[0]);
	      tempstr[line_count]->write(&DC2,1);
	      line_count++;
	      
	      //------------  10th line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
	      char_count[line_count]+=4;
 	      *tempstr[line_count]<<" "<<Session<<"-"<<Session+1;
	      tempstr[line_count]->write(&SI,1);

	      *tempstr[line_count]<<sub[1];
	      tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      //char_count[line_count]+=10;
	      //char_count[line_count]+=strlen(sub[1]);
	      line_count++;
	      //------------ 11th line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<i->get_name();
		  tempstr[line_count]->write(&SI,1);

	      *tempstr[line_count]<<sub[2];
		  tempstr[line_count]->write(&DC2,1);
	      char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[2]);

	      //*tempstr[line_count]<<endl;
	      line_count++;
	      //------------ 12th line
	      //*tempstr[line_count]<<i->get_Father();
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
		  tempstr[line_count]->write(&SI,1);

 	      *tempstr[line_count]<<sub[3];
		  tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[3]);
	      line_count++;
	      //------------ 13th line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<i->get_Class_roll();
		  tempstr[line_count]->write(&SI,1);

	      *tempstr[line_count]<<sub[4];
		  tempstr[line_count]->write(&DC2,1);
	      char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[4]);

	      //*tempstr[line_count]<<endl;
	      line_count++;
	      //------------- 14th line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<"000"<<i->get_Exam_roll();
		  tempstr[line_count]->write(&SI,1);

	      *tempstr[line_count]<<sub[5];
		  tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[5]);

	      line_count++;
	      //------------- 15th line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<i->get_hall();
		  tempstr[line_count]->write(&SI,1);

	      *tempstr[line_count]<<sub[6];
		  tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[5]);

	      line_count++;
	      //------------- 16th line
	      //tempstr[line_count]->write(&Esc,1);
	      //tempstr[line_count]->write(&PrnDollar,1);
	      //tempstr[line_count]->write(FrontHorPos,2);
	      tempstr[line_count]->write(&SI,1);

 	      *tempstr[line_count]<<sub[7];
		  tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      //char_count[line_count]+=4;
	      //char_count[line_count]+=strlen(sub[5]);
	      line_count++;
	      //------------- 17th line
	      //tempstr[line_count]->write(&Esc,1);
	      //tempstr[line_count]->write(&PrnDollar,1);
	      //tempstr[line_count]->write(FrontHorPos,2);
		  tempstr[line_count]->write(&SI,1);

 	      *tempstr[line_count]<<sub[8];
		  tempstr[line_count]->write(&DC2,1);
	      //*tempstr[line_count]<<endl;
	      line_count++;
	      //------------- 18th line
	      //tempstr[line_count]->write(&Esc,1);
	      //tempstr[line_count]->write(&PrnDollar,1);
	      //tempstr[line_count]->write(FrontHorPos,2);
 	      //*tempstr[line_count]<<sub[9];
	      //*tempstr[line_count]<<endl;
	      //line_count++;
	      //------------- enter tab stopage
	      //for(k=0;k<Mark_Space-4;k++)
	      //	*tempstr[line_count]<<endl;
	      

	      //----------- Semester
	      //for(;k<Mark_Space;k++)
	      //*tempstr[line_count]<<endl;
	      int line_number[]={30,31,34,37,41,44,47,49};
	      //int line_number[]={26,27,29,31,34,37,39,41};
	      for(k=0;k<8;k++)
		*tempstr[line_number[k]]<<"\t";

	      *tempstr[25]<<"\t\t\t\t\t\t\t\t\t\t\t\t\t"<<semester;

	      //------------ repeat each course no
	      flag=0;
	      for(k=0;k<size;k++)
		{
		  
		  list<subject>::iterator j;
		  //================ for all subjects
		  for(j=Subject_list.begin();j!=Subject_list.end();++j)
		    {
		      if(j->get_subject_no() == subj[k])
			break;
		    }
          
		  //final_fullmark=j->get_final();
		  //tutorial_fullmark=j->get_tutorial();
		  //total_fullmark=final_fullmark+tutorial_fullmark;
		  //credit=j->get_credit();
		  //total_credit+=credit;          
		  *tempstr[line_number[0]]<<""<<subj[k];
		  if(subj[k]%50==0)
		    {
		      *tempstr[line_number[1]]<<""<<j->get_credit()<<"";
		      *tempstr[line_number[2]]<<j->get_final()<<"\t";
		      *tempstr[line_number[3]]<<"";
		    }
		  else
		    {
		      *tempstr[line_number[0]]<<"\t";
		      *tempstr[line_number[1]]<<""<<j->get_credit()<<"\t";
		      *tempstr[line_number[2]]<<j->get_tutorial()<<"\t";
		      *tempstr[line_number[2]]<<j->get_final()<<"\t";
		      *tempstr[line_number[3]]<<tut[k]<<"\t"; //tutorial
 
		    }
		  *tempstr[line_number[0]]<<"\t";
		  *tempstr[line_number[1]]<<"\t"; 
		  *tempstr[line_number[3]]<<mark_obt[k]<<"\t"; // final calculated mark
 		  *tempstr[line_number[4]]<<tot_obt[k]<<"\t";
		  
		  *tempstr[line_number[5]]<<setprecision(5)<<letterGrade[k]<<"\t";
		  *tempstr[line_number[6]]<<setprecision(5)<<gp[k]<<"\t";
		  if(gp[k]==0)
		    {
		      if(flag==1)
			*tempstr[line_number[7]]<<",";
		      else
			*tempstr[line_number[7]]<<" ";
		      *tempstr[line_number[7]]<<subj[k];
		      flag=1;
		    }
		}
	      //

	      //	      *tempstr[line_number[6]]<<setprecision(3)<<gpa<<"\t";
              int ix=(int)fabs(gpa*100);
              double igpa=ix/100.0;
              //                *tempstr[line_number[6]]<<setprecision(3)<<iy+0.01<<"\t";
	      
	      cout<<"GPA-in session--->"<<gpa<<"-"<<setprecision(5)<<gpa;
	      cout<<"-"<<igpa<<"-"<<(gpa-igpa)<<endl;
              if(( fabs(gpa-igpa)-0.005)>=0||(fabs( fabs(gpa-igpa)-0.005)>1e-16&&fabs( fabs(gpa-igpa)-0.005)<1e-13))
                *tempstr[line_number[6]]<<(igpa=igpa+0.01)<<"\t";
              else
                *tempstr[line_number[6]]<<igpa<<"\t";
                                                         
	      if(semester==1)
		{
		  *tempstr[line_number[6]]<<"---"<<"\t";
		  *tempstr[line_number[6]]<<"---";

		}
	      else
		{
		  *tempstr[line_number[6]]<<setprecision(3)<<round2(pcgpa)<<"\t";
		  *tempstr[line_number[6]]<<setprecision(3)<<round2(cgpa)<<"\t";


		}
	      if(gpa>=2.5 && flag==1)
		*tempstr[line_number[7]]<< " subject(s) is(are) to be repeated.";
	      //else
	      //if(gpa>=2.0 && flag==1)
	      //  *tempstr[7]<< " subject are to be repeated if probation is crossed. "; 
	      //------------------------ Grade sheet
	      char lgrade_pos[]={0x1b,0x24,0xc3,0x02};
	      char grade_pos[]= {0x1b,0x24,0xe3,0x02};
	      char gs_sem[]=    {0x1b,0x24,0x49,0x02};
	      char gs_exam[]=   {0x1b,0x24,0xd0,0x02};
	      char gs_dep[]=    {0x1b,0x24,0x3a,0x02};
	      char gs_reg[]=    {0x1b,0x24,0xa3,0x02};
	      char gs_sess[]=   {0x1b,0x24,0xee,0x02};

	      tempstr[24]->write(gs_sem,4);
	      *tempstr[24]<<semester;
	      tempstr[24]->write(gs_exam,4);
	      *tempstr[24]<<Session;
	      char_count[24]+=4;

	      tempstr[25]->write(gs_dep,4);
	      *tempstr[25]<<"Electronics & Computer Science";
	      char_count[25]+=4;

	      tempstr[26]->write(gs_dep,4);
	      *tempstr[26]<<i->get_name();
	      char_count[26]+=4;

	      tempstr[27]->write(gs_dep,4);
	      *tempstr[27]<<"000"<<i->get_Exam_roll();
	      char_count[27]+=4;


	      line_count=34; 

	      for(cnt=0;cnt<MAX_SIZE;cnt++)
		{
		  sub[cnt][2]=0xf5;
		  sub[cnt][3]=0x01;
		  
		  tempstr[line_count]->write(&SI,1);
		  *tempstr[line_count]<<sub[cnt];
		  tempstr[line_count]->write(&DC2,1);

		  tempstr[line_count]->write(lgrade_pos,4);
		  *tempstr[line_count]<<letterGrade[cnt];
		  tempstr[line_count]->write(grade_pos,4);
		  *tempstr[line_count]<<""<<gp[cnt];
		  char_count[line_count]+=4;

		  line_count++;
		}
	      //char grade_pos[]={0x1b,0x24,0xb3,0x02};
	      tempstr[55]->write(grade_pos,4);
	      *tempstr[55]<<setprecision(3)<<igpa;
	      if(semester >1)
		{
		  //  char grade_pos[]={0x1b,0x24,0xb3,0x02};
		  tempstr[57]->write(grade_pos,4);
		  *tempstr[57]<<setprecision(3)<<round2(pcgpa);
		  //char grade_pos[]={0x1b,0x24,0xb3,0x02};
		  tempstr[60]->write(grade_pos,4);
		  *tempstr[60]<<setprecision(3)<<round2(cgpa);
		}
	      else
		{
		  tempstr[57]->write(grade_pos,4);
		  *tempstr[57]<<"---";
		  tempstr[60]->write(grade_pos,4);
		  *tempstr[60]<<"---";
		}
	      total_size=0;

	      //-------------------------Now load to strout ----
	      for(cnt=0;cnt<LINE;cnt++)
		{
		  *tempstr[cnt]<<endl;
		  
		  int line_size;
		  for(line_size=161;line_size>0 && (x[cnt][line_size]!='\n');line_size--)
		    ;
		    line_size+=2;
		    total_size+=line_size;
		  // *tempstr[line_number[cnt]]<<endl;
		  
		  //switch(cnt)
		  //{
		  //case 0:
		  //case 1:break;
		  //case 2 :*tempstr[line_count]<<"\n";break;//need extra \n
		  //default: *tempstr[line_count]<<"\n";
		  //}
		  if(line_number[4]==cnt)
		    {
		       unsigned char tab_init[15]={0x1b,0x44,0x07,0x0c,0x14,0x1b,0x21,0x29,0x30,0x37,0x3f,0x46,0x4b,0x50,0x00};
		       strout.write((const char*)tab_init,15);
		    }
		  
		  if(line_number[7]==cnt && gpa>=2.0 && gpa<2.5)
		    {
		      //strout<<"  "<<x[cnt];
		      strout.write(x[cnt],line_size);
		    }
		  else
		    {
		    
		      if(cnt!=line_number[7])
			{
			  if(char_count[cnt]<4)
			    strout.write(x[cnt],line_size);
			//			    strout<<x[cnt];
			  else
		      strout.write(x[cnt],line_size);

			//			    strout.write(x[cnt],161);
			}
		      else
			strout<<endl;
		    }
		}
	      char ff=FormFeed;
	      strout.write(&ff,1);
	      //return *tempstr[line_count];        
	      
	    }
	}
    }
  return total_size;
}

#define COMMENT 16
#define GPA 57
#define PGPA 60
#define CGPA 62
//! Prepare tabulation sheet second form
int session::prepare_tabulation_sheet_v2(
				  int semester,
				  strstream &strout,
				  int registration_no)
{
  int total_size;

  int line_number[]={35,36,37,38,39,40,41,42,43,44,45,46,47,48,58,62,65};
  int gs_line_number[]={27,28,29,30,35};
  //  int line_number[]={35,36,37,38,39,40,41,42,43,44,45,46,47,48,56,58,62};

  int line_count;
  double igpa;
  char SI=0x0f;
  char DC2=0x12;
  int char_count[LINE];
  char line_space=' '; 
  char Esc=0x1b;
  char PrnLineSpace=0x30; //1/8 inch line spacing
  char PrnDollar=0x24;    // $ code
  char *HorPos, *FrontHorPos;
  int AbsHorPrnPos=35; //341; //360;
  HorPos=(char*)&AbsHorPrnPos;
  int FrontPrnPos=116;
  FrontHorPos=(char*)&FrontPrnPos;
  int flag;
  int size;
  int cnt,k,m;
  double gpa,pcgpa,cgpa;
  int *subj, *tut, *mark_obt, *tot_obt;
  subj=new int[MAX_SIZE];
  tut=new int[MAX_SIZE];
  mark_obt=new int[MAX_SIZE];
  tot_obt=new int[MAX_SIZE];
  
  char **letterGrade;
  letterGrade= new char*[MAX_SIZE];
  for(cnt=0;cnt<MAX_SIZE;cnt++)
    letterGrade[cnt]=new char[3]; 
 double *gp;
  gp= new double[MAX_SIZE];


  //============ ::::::::::: Printing Session :::::::::::::============

  //init_tab(strout);
  
  //strout<<endl;

  strstream *tempstr[LINE];
  strstream *subject_title[MAX_SIZE];
  strstream *cur_subject_title;
  char x[LINE][LINESIZE];
  char sub[MAX_SIZE][SUB_SIZE];
  char cur_sub[SUB_SIZE],cur_sub_template[SUB_SIZE];

  //Pagelength Seting
  char page_length[]={0x1b,0x43,0x00,0x0b};//Ecs C Nul 11 (inch)
 
  strout.write((const char*) page_length,4);

  //Initialising Tab Position
  unsigned char tab_init[20]={0x1b,0x44,0x17,0x1a,0x1e,0x21,0x25,0x28,0x2c,0x2f,0x33,0x37,0x3b,0x3f,0x43,0x47,0x4c,0x50,0x55,0x00};
    
  strout.write((const char*) tab_init,20);

 
 //----------------------- Tabulation part
  char title_pos[]   ={0x1b,0x24,0x40,0x00};
  char credit_pos[]  ={0x1b,0x24,0xd8,0x00};
  char tut_pos[]     ={0x1b,0x24,0xf2,0x00};
  char tut_ob_pos[]  ={0x1b,0x24,0x0e,0x01};
  char  final_pos[]  ={0x1b,0x24,0x36,0x01};
  char final_ob_pos[]={0x1b,0x24,0x54,0x01};
  char  total_pos[]={0x1b,0x24,0x72,0x01};
  char gradeT_pos[]={0x1b,0x24,0x9a,0x01};
  char gPoint_pos[]={0x1b,0x24,0xb8,0x01};
  //ar lgrade_pos[]={0x1b,0x24,0xc3,0x02};
  //ar lgrade_pos[]={0x1b,0x24,0xc3,0x02};

  //------------------------ Grade sheet part
  char gs_title_pos[]={0x1b,0x24,0xf5,0x01};
  char gs_lgrade_pos[]={0x1b,0x24,0xc3,0x02};
  char gs_grade_pos[]= {0x1b,0x24,0xe3,0x02};
  char gs_sem[]=    {0x1b,0x24,0x49,0x02};
  char gs_exam[]=   {0x1b,0x24,0xd0,0x02};
  char gs_dep[]=    {0x1b,0x24,0x3a,0x02};
  char gs_reg[]=    {0x1b,0x24,0xa3,0x02};
  char gs_sess[]=   {0x1b,0x24,0xee,0x02};

  //===================== initialize printable lines
  for(k=0;k<LINE;k++)
    {
      for(m=0;m<LINESIZE;m++)
        x[k][m]='\0';
      tempstr[k]=new strstream(x[k],LINESIZE);
      // initialize with endl
      //      *tempstr[k]<<k%10;
      //      char_count[k]=1;
    }

  //====================== initialize subject information
  for(k=0;k<MAX_SIZE;k++)
    {
      for(m=0;m<SUB_SIZE;m++)
        sub[k][m]='\0';
      subject_title[k]=new strstream(sub[k],SUB_SIZE);
    }
  for(m=0;m<SUB_SIZE;m++)
    cur_sub_template[m]='\0';
  cur_subject_title=new strstream(cur_sub,SUB_SIZE);
 
 //===================== put subject titles in a list
  int sub_no_avg,First,Second,ses_sem;
  list<subject>::iterator sub_j;
 
  for(sub_j=Subject_list.begin(),k=0; sub_j!=Subject_list.end(); ++sub_j)
    {
      sub_no_avg=sub_j->get_subject_no();

      //To calculate semester from subject number
      ses_sem=(floor(sub_no_avg/100)-1)*2+1+floor((sub_no_avg%100)/50);

      if(ses_sem==semester)
	{
	  //horizontal print tab 'Esc$' 
	  subject_title[k]->write(&Esc,1);
	  subject_title[k]->write(&PrnDollar,1);
	  subject_title[k]->write(HorPos,2);
	  
	  *subject_title[k]<<""<<sub_j->get_subject_no()<<"    "<<sub_j->get_name();
	  k++;
	}
    }

  

  //======================= End of initialization ================
  double t_credit;
  if (registration_no==0)
    {
// --> Incomplete
      //loop for all students
      //j->get_cgpa(semester);
      //j->get_grade(subj[],tut[],mark_obt[],tot_obt[],letterGrade[],gp[]);
      Student_list.sort();
      list<student>::iterator i;
      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  gpa=i->get_cgpa(semester,t_credit);
	  size=i->get_grade(semester,subj,tut,mark_obt,tot_obt,letterGrade,gp);
	  
	}
//-->Incomplete
    }
  else//if ??
    {
      
      //loop till the student found
      double c_credit;
      double tgpa,gpa_temp,total_credit;
      list<student>::iterator i;
      for(i=Student_list.begin();i!=Student_list.end();++i)
	{
	  if (i->get_Exam_roll()!= registration_no)
	    {
	      continue;
	    }
	  else
	    {

	  if(!(i->is_register(semester))){return -1;}//no subject taken
	      
	      line_count=0;
	      // find gpa of current semester	      
	      gpa=i->get_cgpa(semester,c_credit);
	      // find subject taken by student
	      size=i->get_grade(semester,subj,tut,mark_obt,tot_obt,letterGrade,gp);
	      //if semester >1 calculate cgpa
	      if(semester>1)
		{
		  tgpa=0;
		  total_credit=0;
		  for(cnt=1;cnt<semester;cnt++)
		    {
		      gpa_temp=(i->get_cgpa(cnt,t_credit));
		      tgpa+=gpa_temp*t_credit;
		      total_credit+=t_credit;
		      
		    }
		  pcgpa=tgpa/total_credit;
		  // calculate cgpa but probably need some correction
		  cgpa=(gpa*c_credit+tgpa)/(c_credit+total_credit);
		}
	      


	      //  ^^^^^^^^^^^^^^^^^^^^^
	      // ---------- Init line spacing Esc '+' 031H
	      
	      tempstr[line_count]->write(&Esc,1);
//--- line spacing
	      char Plus='+';
	      char Line360Sp=0x31;
	      tempstr[line_count]->write(&Plus   ,1);
	      tempstr[line_count]->write(&Line360Sp, 1);
	      
	      
	      int line_loop;
	      
	      //----------- Top  line
	      line_count=Top;  //TOP=11, it is 9 for 1/8 gap
	      
	      //------------  Top+1 line session
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<" "<<Session<<"-"<<Session+1;
	      
	      line_count++;
	      
	      //------------ Top+2 line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<i->get_name();

	      line_count++;
	      //------------ Top+3 line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
	      //*tempstr[line_count]<<i->get_Father();

	      line_count++;
	      //------------ Top+4  line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<i->get_Class_roll();

	      line_count++;
	      //------------- Top+5 line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<"00"<<i->get_Exam_roll();

	      line_count++;
	      //------------- Top+6 line
	      tempstr[line_count]->write(&Esc,1);
	      tempstr[line_count]->write(&PrnDollar,1);
	      tempstr[line_count]->write(FrontHorPos,2);
 	      *tempstr[line_count]<<line_space<<i->get_hall();


	      //----------- Semester
	      
	      //int line_number[]={26,27,29,31,34,37,39,41};
	      //Why tab introduces???????????????
	      //May be 13
	      *tempstr[Top+14]<<"\t\t\t\t\t\t\t\t\t\t"<<semester;

	      //------------ repeat each course no
	      flag=0;
	      for(k=0;k<size;k++)
		{
		  
		  list<subject>::iterator j;
		  int registered=0;
		  //================ for all subjects PROBLEM
		  for(j=Subject_list.begin();j!=Subject_list.end();j++)
		    {
		      if(j->get_subject_no() == subj[k])
			{
			  registered=1;
			  cur_subject_title->seekp(0);
			  cur_subject_title->write(cur_sub_template,SUB_SIZE);//clean out
			  cur_subject_title->seekp(0);
			  //			  cur_subject_title->write(&Esc,1);//printer control sequence
			  //cur_subject_title->write(&PrnDollar,1);//ditto
			  //cur_subject_title->write(HorPos,2);//ditto
			  *cur_subject_title<<""<<j->get_subject_no()<<"    "<<j->get_name();//print subject number and title
			  
			  break;
			}
		    }
          
		  
		  //>>>CHECK
		  //if(registered==1)
		  //{
		      int sz;
		      //findout size of cur_sub
		      for(sz=SUB_SIZE-1;sz--;)
			{
			  if(cur_sub[sz]=='\00')
			    continue;
			  else
			    break;
			}
		      tempstr[line_number[k]]->write(&SI,1);
		      //sub[k][2]=0x40;
		      //sub[k][3]=0x00;
		      //cur_sub[2]=0x40;
		      //cur_sub[3]=0x00;
		      tempstr[line_number[k]]->write(title_pos,4);
		      tempstr[line_number[k]]->write(cur_sub,(sz+1));
		      tempstr[line_number[k]]->write(&DC2,1);
		      //For MSC this rule should be lifted for viva
		      
			
		      if(subj[k]%50==0 && subj[k]<600)
			{
			  tempstr[line_number[k]]->write(credit_pos,4);
			  *tempstr[line_number[k]]<<j->get_credit();
			  tempstr[line_number[k]]->write(final_pos,4);
			  *tempstr[line_number[k]]<<j->get_final();
			  
			}
		
		      else
			{
			  tempstr[line_number[k]]->write(credit_pos,4);
			  *tempstr[line_number[k]]<<j->get_credit();
			  tempstr[line_number[k]]->write(tut_pos,4);
			  *tempstr[line_number[k]]<<j->get_tutorial();
			  tempstr[line_number[k]]->write(tut_ob_pos,4);
			  if(tut[k]>=0)
			    *tempstr[line_number[k]]<<tut[k]; //tutorial
			  else
			    *tempstr[line_number[k]]<<"--"; //tutorial
			  tempstr[line_number[k]]->write(final_pos,4);
			  *tempstr[line_number[k]]<<j->get_final()<<"\t";
			  
			}
		
		      tempstr[line_number[k]]->write(final_ob_pos,4);

		      if(mark_obt[k]>0)
			*tempstr[line_number[k]]<<mark_obt[k]<<"\t"; // final calculated mark
		      else
			*tempstr[line_number[k]]<<"--"; //final 

		      tempstr[line_number[k]]->write(total_pos,4);
		      if(tot_obt[k]>0)
			*tempstr[line_number[k]]<<tot_obt[k]<<"\t";
		      else
			*tempstr[line_number[k]]<<"--"; //total obtain

		      tempstr[line_number[k]]->write(gradeT_pos,4);
		      *tempstr[line_number[k]]<<setprecision(5)<<letterGrade[k]<<"\t";
		      tempstr[line_number[k]]->write(gPoint_pos,4);
		      *tempstr[line_number[k]]<<setprecision(5)<<gp[k]<<"\t";

		      //if any grade obtained is 0, it should be repeated
		      if(gp[k]==0)
			{
			  if(flag==1)
			    *tempstr[58]<<",";
			  else
			    tempstr[58]->write(credit_pos,4);
			  *tempstr[58]<<subj[k];
			  flag=1;
			}

		      //--------------------Grade Sheet part
		      tempstr[line_number[k]]->write(&SI,1);
		      tempstr[line_number[k]]->write(gs_title_pos,4);
		      tempstr[line_number[k]]->write(cur_sub,(sz+1));
		      tempstr[line_number[k]]->write(&DC2,1);

		      tempstr[line_number[k]]->write(gs_lgrade_pos,4);
		      *tempstr[line_number[k]]<<setprecision(5)<<letterGrade[k]<<"\t";
		      tempstr[line_number[k]]->write(gs_grade_pos,4);
		      *tempstr[line_number[k]]<<setprecision(5)<<gp[k]<<"\t";



		    }//for size
	      //Final Previous CGPA and Final CGPA                                                         
	      //

	      //   
	      //------------------ROUNDING OF GPA --------
	      
	      /*
              int ix=(int)fabs(gpa*100);
              igpa=ix/100.0;
	      */
	       
	      /*
	      if((gpa*100.0-ix)>=0.5)
		cout<<"IGPA "<<igpa+0.1<<endl;
	      else
		cout<<"TGPA "<<igpa<<endl;
	      */
	      igpa=round2(gpa);
	      tempstr[GPA]->write(gPoint_pos,4);

	      *tempstr[GPA]<<igpa<<"\t";

	      cout<<"GPA-in session--->"<<gpa<<"-"<<setprecision(3)<<gpa;
	      cout<<"-"<<igpa<<"-"<<(gpa-igpa)<<endl;
	      
	      /*

              if(( fabs(gpa-igpa)-0.005)>=0) //||(fabs( fabs(gpa-igpa)-0.005)>1e-16&&fabs( fabs(gpa-igpa)-0.005)<1e-13))
                *tempstr[GPA]<<(igpa=igpa+0.01)<<"\t";
              else
                *tempstr[GPA]<<igpa<<"\t";

		*/
	      //---------- ROUNDING OF GPA END------

	    }
	  

	  if(semester==1)
	    {
	      tempstr[PGPA]->write(gPoint_pos,4);
	      *tempstr[PGPA]<<"---"<<"\t";
	      
	      tempstr[CGPA]->write(gPoint_pos,4);
	      *tempstr[CGPA]<<"---";
		  
	    }
	  else
	    {
	      tempstr[PGPA]->write(gPoint_pos,4);
	      *tempstr[PGPA]<<setprecision(3)<<round2(pcgpa)<<"\t";
	      
	      tempstr[CGPA]->write(gPoint_pos,4);
	      *tempstr[CGPA]<<setprecision(3)<<round2(cgpa)<<"\t";
	    }
	
	  //---------------	  
// NEED REDEFINE THE RULE
	  if(gpa>=2.5 && flag==1)
	    {
	      tempstr[PGPA]->write(credit_pos,4);
	    *tempstr[PGPA]<< " subject(s) is(are) to be repeated.";
	    }

	  // ----------------------- GRADE SHEET Filling up
	  int gs_line=0;
	      tempstr[gs_line_number[gs_line]]->write(gs_sem,4);
	      *tempstr[gs_line_number[gs_line]]<<semester;
	      tempstr[gs_line_number[gs_line]]->write(gs_exam,4);
	      *tempstr[gs_line_number[gs_line]]<<Session+1;
	      
	      //next line
	      gs_line++;

	      tempstr[gs_line_number[gs_line]]->write(gs_dep,4);
	      *tempstr[gs_line_number[gs_line]]<<"Computer Science & Engineering";
	      // next line
	      gs_line++;

	      tempstr[gs_line_number[gs_line]]->write(gs_dep,4);
	      *tempstr[gs_line_number[gs_line]]<<i->get_name();
	      
	      //next line
	      gs_line++;
	      tempstr[gs_line_number[gs_line]]->write(gs_dep,4);
	      *tempstr[gs_line_number[gs_line]]<<"00"<<i->get_Exam_roll();
	      
	      //Next print position
	      gs_line++;
	      line_count=gs_line_number[gs_line]; 
	      //Try to accomodate this with above
	      /*
	      for(cnt=0;cnt<MAX_SIZE;cnt++)
		{
		  sub[cnt][2]=0xf5;
		  sub[cnt][3]=0x01;
		  
		  tempstr[line_count]->write(&SI,1);
		  *tempstr[line_count]<<sub[cnt];
		  tempstr[line_count]->write(&DC2,1);

		  tempstr[line_count]->write(lgrade_pos,4);
		  *tempstr[line_count]<<letterGrade[cnt];
		  tempstr[line_count]->write(grade_pos,4);
		  *tempstr[line_count]<<""<<gp[cnt];
		  char_count[line_count]+=4;

		  line_count++;
		}
	      */
	      //char grade_pos[]={0x1b,0x24,0xb3,0x02};
	      tempstr[GPA]->write(gs_grade_pos,4);
	      *tempstr[GPA]<<setprecision(3)<<igpa;
	      if(semester >1)
		{
		  //  char grade_pos[]={0x1b,0x24,0xb3,0x02};

		  tempstr[PGPA]->write(gs_grade_pos,4);
		  *tempstr[PGPA]<<setprecision(3)<<round2(pcgpa);

		  //char grade_pos[]={0x1b,0x24,0xb3,0x02};

		  tempstr[CGPA]->write(gs_grade_pos,4);
		  *tempstr[CGPA]<<setprecision(3)<<round2(cgpa);
		}
	      else
		{
		  tempstr[PGPA]->write(gs_grade_pos,4);
		  *tempstr[PGPA]<<"---";
		  tempstr[CGPA]->write(gs_grade_pos,4);
		  *tempstr[CGPA]<<"---";
		}
	      total_size=0;

	      //-------------------------Now load to strout ----
	      for(cnt=0;cnt<LINE;cnt++)
		{
		  *tempstr[cnt]<<endl;
		  
		  int line_size;
		  for(line_size=LINESIZE;line_size>0 && (x[cnt][line_size]!='\n');line_size--)
		    ;
		    line_size+=2;
		    total_size+=line_size;
		  // *tempstr[line_number[cnt]]<<endl;
		  
		  //switch(cnt)
		  //{
		  //case 0:
		  //case 1:break;
		  //case 2 :*tempstr[line_count]<<"\n";break;//need extra \n
		  //default: *tempstr[line_count]<<"\n";
		  //}
		    /*
		    if(line_number[4]==cnt)
		    {
		     unsigned char tab_init[15]={0x1b,0x44,0x07,0x0c,0x14,0x1b,0x21,0x29,0x30,0x37,0x3f,0x46,0x4b,0x50,0x00};
		     strout.write(tab_init,15);
		    }
		    */
		    
		    strout.write(x[cnt],line_size);
		    /*
		    if(line_number[7]==cnt && gpa>=2.0 && gpa<2.5)
		    {
		      //strout<<"  "<<x[cnt];
		      strout.write(x[cnt],line_size);
		    }
		  else
		    {
		    
		      if(cnt!=line_number[7])
			{
			  if(char_count[cnt]<4)
			    strout.write(x[cnt],line_size);
			//			    strout<<x[cnt];
			  else
		      strout.write(x[cnt],line_size);

			//			    strout.write(x[cnt],161);
			}
		      else
			strout<<endl;
		    }
		    */
		}
	      char cr=0x0d;
	      strout.write(&cr,1);
	      char ff=FormFeed;
	      strout.write(&ff,1);
	      //return *tempstr[line_count];        
	      
	    }
	
	}

  return total_size;
}

//! Output streaming << operator overloading
 ostream & operator<<(ostream &output, const session & ses)
{
 session x=ses;

  output<<"\nList of courses offerred\n";
  list<subject>::iterator j;
  for(j=x.Subject_list.begin();j!= x.Subject_list.end();j++)
    {
      output<<*j<<endl;
    }
  list<student>::iterator i;
  x.Student_list.sort();
  output<<"List of students\n";
  for(i = x.Student_list.begin(); i != x.Student_list.end(); i++)
    {
      output <<*i<<endl;
    }
  //  output<<"\n\nList of courses offerred\n";
  return output;
}


float session::round2(float input)
{
  float i_input;
  int ix=(int)fabs(input*100);
  i_input=ix/100.0;
  cout<<"INPUT -- "<<input<<" I INPUT "<<i_input<<endl;
  if(( fabs(input-i_input)-0.005)>=0) //||(fabs( fabs(input-i_input)-0.005)>1e-16&&fabs( fabs(input-i_input)-0.005)<1e-13))
    return(i_input+0.01);
  else
    return(i_input);
  
  
}
