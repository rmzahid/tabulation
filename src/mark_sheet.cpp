#include "mark_sheet.hh"

mark_sheet::mark_sheet()
{
  Subject_no=0;
  int i;
  for(i=0;i<4;i++)
    {
      Marks[i]=-1;
    }

}
int  mark_sheet::set_sheet(int subject_no, subject* subj)
{
  Subject_no=subject_no;
  Subject=subj;
}


bool  mark_sheet::set_mark(int sub_no, int mark, type t_type)
{
 if(Subject_no==sub_no)
    {
      Marks[t_type]=mark;
      return true;
    }
  else
    return false;


}
double  mark_sheet::get_mark(type t_type, int sub_no)
{
  if(Subject_no==sub_no)
    return Marks[t_type];
  else
    return -1.0;

}

bool mark_sheet::get_avg_mark(int subject_no, int &mark_avg)
{
  bool ret_type=false;
  mark_avg=0;
  if (subject_no != Subject_no)
    return ret_type;
  if((Marks[Internal]==-1)&&(Marks[External]==-1))
    return false;
  else
    {
      int diff;
      diff=abs(Marks[Internal]-Marks[External]);
      if( (double)diff > (Subject->get_final()*0.2) )
	{
	  ret_type=true;
	  if(abs(Marks[Internal]-Marks[Third])>abs(Marks[External]-Marks[Third]))
	    mark_avg=round((Marks[External]+Marks[Third])/2);
	  else if (abs(Marks[Internal]-Marks[Third])<abs(Marks[External]-Marks[Third]))
	    mark_avg=round((Marks[Internal]+Marks[Third])/2);
	  else
	    {
	      if(round((Marks[Internal]+Marks[Third])/2)>round((Marks[External]+Marks[Third])/2))
		mark_avg=round((Marks[Internal]+Marks[Third])/2);
	      else
		mark_avg=round((Marks[External]+Marks[Third])/2);
	    }

	}
      else 
	{
	  ret_type=false;
	  mark_avg=round((Marks[Internal]+Marks[External])/2);
	}
    }
return ret_type;
}

  bool  mark_sheet::get_avg_mark(int subject_no, std::string &avg_sheet)
{
}

  bool  mark_sheet::get_avg_mark(int subject_no, char *avg_sheet)

{
  if (subject_no != Subject_no)
    return false;
  else
    {
      //char *buffer;
      //buffer=new char[128];
      std::strstream x(avg_sheet,128,(std::_Ios_Openmode)1);
      int diff,mark_avg;
      diff=abs(Marks[Internal]-Marks[External]);
      x<<Marks[Internal]<<"\t"<<Marks[External]<<"\t"<<diff<<"\t";
      if(Marks[Third]==-1)
	x<<"--";
      else
	x<<Marks[Third];
      x<<"\t";
      if(get_avg_mark(subject_no,mark_avg))
	{
	  x<<mark_avg<<std::endl;
	  return true;
	}
      else
	{
	  x<<mark_avg<<std::endl;
	  return false;
	}
      //cout<<"From mark sheet "<< avg_sheet<<"-X-"<<endl;
	   
    }
}

// In  subject_no
// Out mark obtain
//     letter grade
//     grade point
bool mark_sheet::get_grade(int subject_no, int& mark_obt,  char* grade, double & gp)
{
  int mark_avg, total_mark;
  int percentage;
  if(subject_no<600)
    {
      if(subject_no%50!=0)
	{
	  get_avg_mark(subject_no, mark_avg); 
	  mark_obt=Marks[Tutorial]+mark_avg;
	}
      else
	mark_obt=Marks[Internal];
      total_mark=Subject->get_final()+Subject->get_tutorial();
      percentage=(int)((double)mark_obt/(double)total_mark*100.0);
      
      if(percentage>=GRADE_APLUS)
	{
	  strcpy(grade,S_APLUS);
	  gp=G_APLUS;
	}
      else
	if(percentage>=GRADE_A)
	  {
	    strcpy(grade,S_A);
	    gp=G_A;
	  }
	else
	  if(percentage>=GRADE_AMINUS)
	    {
	      strcpy(grade,S_AMINUS);
	      gp=G_AMINUS;
	    }
	  else
	    if(percentage >= GRADE_BPLUS)
	      {
		strcpy(grade,S_BPLUS);
		gp=G_BPLUS;
	      }
	    else
	      if (percentage >= GRADE_B)
		{
		  strcpy(grade , S_B);
		  gp=G_B;
		}
	      else
		if(percentage>=GRADE_BMINUS)
		  {
		    strcpy(grade,S_BMINUS);
		    gp=G_BMINUS;
		  }
		else
		  if (percentage >=GRADE_CPLUS)
		    {
		      strcpy(grade,  S_CPLUS);
		      gp=G_CPLUS;
		    }
		  else
		    if(percentage >=GRADE_C)
		      {
			strcpy(grade , S_C);
			gp=G_C;
		      }
		    else
		      if(percentage >= GRADE_D)
			{
			  strcpy(grade,S_D);
			  gp=G_D;
			}
		      else
			{
			  strcpy(grade,  S_F);
			  gp=G_F;
			}
    }
  else //MSc Grade preparation
    {
     get_avg_mark(Subject_no, mark_avg);
      mark_obt=Marks[Tutorial]+mark_avg;
      
      total_mark=Subject->get_final()+Subject->get_tutorial();
      percentage=(int)((double)mark_obt/(double)total_mark*100.0);
      /*  
	  for(int i=0;i<4;i++)
	  std::cout<<"MARK OBTAINED--->"<<Marks[i]<<"-";
	  std::cout<<"--"<<mark_obt<<"-"<<mark_avg<<std::endl;
      */
      if(percentage>=MGRADE_APLUS)
	{
	  strcpy(grade,MS_APLUS);
	  gp=MG_APLUS;
	}
      else
	if(percentage>=MGRADE_A)
	  {
	    strcpy(grade,MS_A);
	    gp=MG_A;
	  }
	else
	  
	  if(percentage >= MGRADE_BPLUS)
	    {
	      strcpy(grade,MS_BPLUS);
	      gp=MG_BPLUS;
	    }
	  else
	    if (percentage >= MGRADE_B)
	      {
		strcpy(grade , MS_B);
		gp=MG_B;
	      }
	    else
	      if (percentage >=MGRADE_C)
		{
		  strcpy(grade,  MS_C);
		  gp=MG_C;
		}
	      else
		{
		  strcpy(grade,  MS_F);
		  gp=MG_F;
		}
    }
      return true;         
}

// Initial intention to returns 
// grade point for a subject and pass credit of that subject
// Probably incomplete 
// Comment: Need to remove
double mark_sheet::get_grade( double & credit)
{
  double gp;
  int mark_avg, total_mark, mark_obt;
  int percentage;
  if(Subject_no<600)
    {
      if(Subject_no%50!=0)
	{
	  get_avg_mark(Subject_no, mark_avg);
	  mark_obt=Marks[Tutorial]+mark_avg;
	}
      else
	mark_obt=Marks[Internal];
      total_mark=Subject->get_final()+Subject->get_tutorial();
      percentage=(int)((double)mark_obt/(double)total_mark*100.0);
      
      credit=Subject->get_credit();

      if(percentage>=GRADE_APLUS)
	{
	  gp=G_APLUS;
	}
      else
	if(percentage>=GRADE_A)
	  {
	    //strcpy(grade,S_A);
	    gp=G_A;
	  }
	else
	  if(percentage>=GRADE_AMINUS)
	    {
	      //strcpy(grade,S_AMINUS);
	      gp=G_AMINUS;
	    }
	  else
	    if(percentage >= GRADE_BPLUS)
	      {
		//strcpy(grade,S_BPLUS);
		gp=G_BPLUS;
	      }
	    else
	      if (percentage >= GRADE_B)
		{
		  //strcpy(grade , S_B);
		  gp=G_B;
		}
	      else
		if(percentage>=GRADE_BMINUS)
		  {
		    //strcpy(grade,S_BMINUS);
		    gp=G_BMINUS;
		  }
		else
		  if (percentage >=GRADE_CPLUS)
		    {
		      //strcpy(grade,  S_CPLUS);
		      gp=G_CPLUS;
		    }
		  else
		    if(percentage >=GRADE_C)
		      {
			//strcpy(grade , S_C);
			gp=G_C;
		      }
		    else
		      if(percentage >= GRADE_D)
			{
			  //strcpy(grade,S_D);
			  gp=G_D;
			}
		      else
			{
			  //strcpy(grade,  S_F);
			  gp=G_F;
			}
    }
  else
    {     
      
      get_avg_mark(Subject_no, mark_avg);
      mark_obt=Marks[Tutorial]+mark_avg;
      
      total_mark=Subject->get_final()+Subject->get_tutorial();
      percentage=(int)((double)mark_obt/(double)total_mark*100.0);
      
      credit=Subject->get_credit();

      if(percentage>=MGRADE_APLUS)
	{
	  //strcpy(grade,MS_APLUS);
	  gp=MG_APLUS;
	}
      else
	if(percentage>=MGRADE_A)
	  {
	    //strcpy(grade,MS_A);
	    gp=MG_A;
	  }
	else
	  
	  if(percentage >= MGRADE_BPLUS)
	    {
	      //strcpy(grade,MS_BPLUS);
	      gp=MG_BPLUS;
	    }
	  else
	    if (percentage >= MGRADE_B)
	      {
		//strcpy(grade , MS_B);
		gp=MG_B;
	      }
	    else
	      if (percentage >=MGRADE_C)
		{
		  //strcpy(grade,  MS_C);
		  gp=MG_C;
		}
	      else
		{
		  //strcpy(grade,  MS_F);
		  gp=MG_F;
		}
      
    }
return gp;         
}
std::ostream & operator <<(std::ostream & output, const mark_sheet &msheet)
{
  int i;
  output<<"--"<<std::endl;
  for(i=0;i<4;i++)
    {
      if(msheet.Marks[i]==-1)
	output<<"!!-";
      else
	output<<msheet.Marks[i]<<"-";
    }
  return output;
}


bool mark_sheet::operator==(int sub_no) const
{
  if(Subject_no==sub_no)
  return true;
  else return false;
}





