#include "session.hh"
#include <fstream>
#include "definition.hh"
#include <math.h>
#define EXAM_INFO "exam_info_0.dat"
int semester_value(int semester_no);
main()
{
  char exam_info[]=EXAM_INFO;
	int First,Second;
  
  int junk=0;
  char junk_char;
  int number_of_hall;
  char buffer[SIZE];
  double sub_mark;
  int i;
  double sub_credit;
  int ses_course, ses_year, ses_sem;
  int sub_no,sub_tut,sub_final;

  char hall_name[HALL_SIZE][SIZE];
  char hall_abbr[HALL_SIZE][3];

  char hall_abr[4];
  int t_roll,t_e_roll;
  char name[SIZE];
  int course;
  int isemester=2;
  int current_ses_sem=1;
  // ******************** Exam info load from file ==============
  std::ifstream fcin;
  fcin.open("session_info.dat");
  if(fcin.fail())
    {
      cerr<<"session_info.dat File cannot open"<<std::endl;
      exit(2);
    }
  fcin>>ses_course;//MSc=1;BSc=2
  fcin>>ses_year;
  fcin>>isemester;
  fcin.close();
  session Session(ses_year);
  
  exam_info[10]='1';
  int sem_count;
  for(sem_count=1;sem_count<=isemester;sem_count++,exam_info[10]++)
    {
      //
      //if(
      fcin.open(exam_info);
      //==NULL
      //)
      if(fcin.fail())
      {
	std::cout<<exam_info<<" file not found"<<endl ;
	exit(2);
      }
      std::cout<<"Reading "<<exam_info<<" file.."<<std::endl;
      fcin>>ses_year>>ses_sem;
      // Register session
      
      cout<<Session<<endl;
      // Register subjects those offerred
      sub_no=0;
      i=0;
      while( (fcin>>sub_no) > 0 && sub_no>=100)
	{
	  fcin.getline(buffer, SIZE, '|');
	  fcin>>sub_credit>>sub_tut>>sub_final;
	  Session.subject_offers(ses_sem, sub_no,buffer,sub_tut, sub_final, sub_credit);
	  //      cout<<++i<<buffer<<sub_tut<<sub_final<<sub_credit<<endl;
	  sub_no=0;
	}
      //cout<<sub_no<<endl;  
      fcin>>junk_char;
      fcin.putback(junk_char);
     //Load hall information abbr;hall name until blank line 
      junk=0;
      while(fcin.getline(hall_abbr[junk],3,';') && isalpha(hall_abbr[junk][0]) ){
	fcin.getline(hall_name[junk],SIZE);
	//cout<<hall_abbr[junk]<<"--"<<hall_name[junk]<<endl;
	junk++;
      }
  
      number_of_hall=junk;
      cout<<"Number of halls "<<number_of_hall<<endl;
      // ********** 
      // Load student information
      //Hall ID (2); class_roll exam_roll Name;Father's name;
      // *********
      junk_char=' ';
      fcin.clear();
      fcin.getline(buffer,SIZE);
      
      junk=0;
      while(fcin.getline(hall_abr,3,';') && isalpha(hall_abr[0]))
	{
	  //cout<<hall_abr<<endl;
	  junk++;
	  fcin.ignore();
	  fcin>>t_roll>>t_e_roll;
	  
	  fcin.getline(buffer,SIZE,';');
	  fcin.getline(name,SIZE,';');
	  int x;
	  for(x=0;x<number_of_hall;x++)//4 should be number_of_hall
	    {
	      if(strcmp(hall_abbr[x],hall_abr)==0)
		break;
	    }
	  Session.student_register(junk,"Bengali name",buffer,"Father\'s name", t_roll, t_e_roll, hall_name[x],"Address\nTest");

	  //Bengali name and fathers name is no in the file	  
	  while(fcin>>course)
	    {
	      //  register course for each student <<==
	      Session.course_register(ses_sem,t_roll,course);
	    }
	  
	  fcin.clear();
	  fcin.getline(buffer,SIZE);
	}// end of while
      //
      fcin.clear();
     fcin.close();
      if(fcin.fail())
	std::cout<<exam_info<<"Failed to close"<<std::endl;
    }// end of for loop

  // *************** Load completed 
  cout<<"*************** Session,Subject & Student information loading completed"<<std::endl;
  //cout<<"WHO and WHAT SUBJECT:"<<endl;
  //cout<<Session<<endl;
  //

  // load student class and exam roll
  int r_l[100], exm_rol[100];
  for(i=0;i<100;i++){
    r_l[i]=-1;
    exm_rol[i]=-1;
  }

  Session.show_list(Tutorial, r_l);
  Session.show_list(Internal,exm_rol);

  // Main loop for marks entry 
  // The tabulator may choose 1 or 2
  // Mark tutorial, internal, external and third examiner

  // **************** Tabulator info from exam_ini.dat file
  ifstream tabulator_info;
  tabulator_info.open("exam_ini.dat");
  char tab_type='0';
  int data_pos=0;
  char tabulator_name[40];
  while(tabulator_info.getline(buffer,SIZE))
    {
     if(buffer[0]=='#')
       continue;
     switch (data_pos)
       {
       case 0:
	 tab_type=buffer[0]; break;
       case 1:
	 strcpy(tabulator_name,buffer); break;
       }
     data_pos++;
    }
  tabulator_info.close();

  int opt;
  char filename[13]=FILENAME;
  cout<<OPTIONS<<endl;
  cin>>opt;
  int ses_count;
  char sem_value='0';
  while(opt!=0){
    sem_value='0';
    switch(opt){
    case 1:
      {
	int exam_type;
	exam_type=1;
	filename[6]='t';

	filename[11]=tab_type;
	char ans='y';
	cout<<"Tutorial Mark for ";
	cin>>sub_no;
	int ses_sem;
	switch(ses_course){
	case BSC:
	  {
	    ses_sem=semester_value(sub_no);
	    break;
	  }
	case MSC:
	  {
	    ses_sem=isemester;
	    break;
	  }
	}
	
	// If ses_course == MSC ses_sem remains same as in file
	  
	// To increase semmester value in fileName to character
	for(ses_count=1;ses_count<=ses_sem;ses_count++)
	  sem_value++;
	filename[5]=sem_value;

	ofstream ftut(filename,ofstream::out|ofstream::app);
	  
	while(ans=='y'){
	  i=0;
	  ftut<<sub_no<<endl;
	  // Web based entry need to pass roll numbers
	  // get subject marks
	  // seperate it and puback in file
	  //==
	  int rol_l[100];
	  for(i=0;i<100;i++)
	    rol_l[i]=-1;
	  
	  Session.list_for_exam(ses_sem, Tutorial, sub_no, rol_l);
	  i=0;
	  while(rol_l[i]!=-1)
	    {
	      cout<<"Roll :"<<rol_l[i]<<" ";
	      ftut<<rol_l[i]<<" ";

	  //==
	      //check for subject registered equals to subject number
	      //if yes do the following else try next
	      cin>>sub_mark;
	      ftut<<sub_mark<<endl;
	      i++;
	    }
	  ftut<<";"<<endl;
	  cout<<"Do you want to continue? y/n ";
	  //cin.flush();
	  cin>>ans;
	  if(ans=='y')
	    {
	      cout<<"Tutorial Mark for "<<sem_value <<": ";
	      cin>>sub_no;
	    }
	}
	ftut.clear();
	ftut.close();
	break;
      }
    case 2:
      {
	int exam_type;
	exam_type=2;
	filename[6]='i';
	filename[11]=tab_type;
	char ans='y';
	cout<<"Internal Mark for ";
	cin>>sub_no;
	
	int ses_sem;
	switch(ses_course){
	case BSC:
	  {
	    ses_sem=semester_value(sub_no);
	    break;
	  }
	case MSC:
	  {
	    ses_sem=isemester;
	    break;
	  }
	}
	for(ses_count=1;ses_count<=ses_sem;ses_count++)
	  sem_value++;
	filename[5]=sem_value;
	ofstream ftut(filename,ofstream::out|ofstream::app);
	 
	//---
	
	while(ans=='y'){
	  i=0;
	  ftut<<sub_no<<endl;

	  
	  // //check for subject registered equals to subject number
	  ///  //if yes do the following else try next
	  int rol_l[100];
	  for(i=0;i<100;i++)
	    rol_l[i]=-1;
	  Session.list_for_exam(ses_sem,Internal,sub_no, rol_l);
	  i=0;
	  while(rol_l[i]!=-1)
	    {
	      cout<<"Roll :"<<rol_l[i]<<" ";
	      ftut<<rol_l[i]<<" ";
	      
	      cin>>sub_mark;
	      ftut<<sub_mark<<endl;
	      
	      i++;
	    }
	  ftut<<";"<<endl;
	  cout<<"Do you want to continue? y/n ";
	  //cin.flush();
	  cin>>ans;
	  if(ans=='y')
	    {
	      cout<<"Internal Mark for subject "<<sem_value <<": ";
	      cin>>sub_no;
	    }
	}
	ftut.close();
	break;
      }

    case 3:
      {
	int exam_type;
	exam_type=3;
	filename[6]='e';	
	filename[11]=tab_type;
	char ans='y';
	cout<<"External Mark for ";
	cin>>sub_no;
	int ses_sem;
	switch(ses_course){
	case BSC:
	  {
	    ses_sem=semester_value(sub_no);
	    break;
	  }
	case MSC:
	  {
	    ses_sem=isemester;
	    break;
	  }
	}

	for(ses_count=1;ses_count<=ses_sem;ses_count++)
	  sem_value++;
	filename[5]=sem_value;
	ofstream ftut(filename,ofstream::out|ofstream::app);
	 

	while(ans=='y'){
	  
	  i=0;
	  ftut<<sub_no<<endl;
	  //==
	  int rol_l[100];
	  for(i=0;i<100;i++)
	    rol_l[i]=-1;
	  Session.list_for_exam(ses_sem,exam_type, sub_no, rol_l);
	  i=0;
	  while(rol_l[i]!=-1)
	    {
	      cout<<"Roll :"<<rol_l[i]<<" ";
	      ftut<<rol_l[i]<<" ";

	  //==	
	  //i=0;
	  //ftut<<sub_no<<endl;
	      //	  while(rol_l[i]!=-1)
	      //{
	      //check for subject registered equals to subject number
	      //if yes do the following else try next
	      //cout<<"Roll :"<<rol_l[i]<<" ";
	      //ftut<<rol_l[i]<<" ";
	      cin>>sub_mark;
	      ftut<<sub_mark<<endl;

	      i++;
	    }
	  ftut<<";"<<endl;
	  cout<<"Do you want to continue? y/n ";
	  //cin.flush();
	  cin>>ans;
	  if(ans=='y')
	    {
	      cout<<"External Mark for "<<sem_value <<": ";
	      cin>>sub_no;
	    }
	}
	ftut.close();
	break;
      }
    case 4:
      {
	filename[6]='3';	
	filename[11]=tab_type;
	char ans='y';
	cout<<"3rd examiner Mark for ";
	cin>>sub_no;
	
	int ses_sem;
	switch(ses_course){
	case BSC:
	  {
	    ses_sem=semester_value(sub_no);
	    break;
	  }
	case MSC:
	  {
	    ses_sem=isemester;
	    break;
	  }
	}

	for(ses_count=1;ses_count<=ses_sem;ses_count++)
	  sem_value++;
	filename[5]=sem_value;
	ofstream ftut(filename,ofstream::out|ofstream::app);
	 

	while(ans=='y'){
	  i=0;
	  ftut<<sub_no<<endl;
	  int rol_l[100];
	  for(i=0;i<20;i++)
	    rol_l[i]=-1;
	  Session.list_for_third_exam(ses_sem,sub_no, rol_l);
	  i=0;
	  while(rol_l[i]!=-1)
	    {
	      cout<<"Roll :"<<rol_l[i]<<" ";
	      ftut<<rol_l[i]<<" ";
	      cin>>sub_mark;
	      ftut<<sub_mark<<endl;
	      i++;
	    }
	  ftut<<";"<<endl;
	  cout<<"Do you want to continue? y/n ";
	  //cin.flush();
	  cin>>ans;
	  if(ans=='y')
	    {
	      cout<<"3rd examiner Mark for "<<sem_value <<": ";
	      cin>>sub_no;
	    }
	}
	ftut.close();
	break;
      }
    case 5: // Semester for mark entry
      {

	cout<<"Which semester you are interested? ";
	cin>>current_ses_sem;
	break;
      }
    case 6: // prepare average sheet
      {
	//======================= AVERAGE SHEET =============
	
	// Prepare Averge sheet
	int roll;
	char delim;
	char infilename[13]=FILENAME;
	// The filename consists of
	//     exam_st.dat
	//          ^^
	//          ||
	//semester--++--type of mark
	// 1-8            tutorial, internal, external & third
	//
	// semester value increases
	// type of mark is 't', 'i', 'e' and '3'
	// 
	// Load tutorial mark from file
	infilename[6]='t';
	infilename[5]='1';
	infilename[11]='\0';
	ifstream ftut1;
	for(ses_sem=1;ses_sem<=isemester;ses_sem++)
	  {
	    ftut1.clear();
	    ftut1.open(infilename);
	    if(ftut1.fail())
	      {
		cerr<<"Cannot open file "<<infilename<<std::endl;
		exit(2);
	      }
	    while(ftut1>>sub_no){
	      while(ftut1>>roll)
		{
		  ftut1>>sub_mark;
		  Session.enter_mark(ses_sem,sub_no,roll,ceil(sub_mark),Tutorial);
		}
	      ftut1.clear();
	      ftut1.get(delim);
	    }
	    ftut1.clear();
	    ftut1.close();
	
	    // Load internal mark from file
	    infilename[6]='i';
	    
	    ftut1.open(infilename);
	    if(ftut1.fail())
	      {
		cerr<<"Cannot open file "<<infilename<<std::endl;
		exit(2);
	      }
	    while(ftut1>>sub_no){
	      while(ftut1>>roll)
		{
		  ftut1>>sub_mark;
		  Session.enter_mark(ses_sem,sub_no,roll,ceil(sub_mark),Internal);
		  // Laboratory marks only internal so to match he rule of inernal & external, same mark is entered as exernal
		  if(sub_no%2==0)
		    Session.enter_mark(ses_sem,sub_no,roll,ceil(sub_mark),External);
		}
	      ftut1.clear();
	      ftut1.get(delim);
	    }
	    ftut1.close();
  
	    // Load external mark
	    
	    infilename[6]='e';
	    ftut1.clear();
	    ftut1.open(infilename);
	    if(ftut1.fail())
	      {
		cerr<<"Cannot open file "<<infilename<<std::endl;
		exit(2);
	      }
	    while(ftut1>>sub_no){
	      while(ftut1>>roll)
		{
		  ftut1>>sub_mark;
		  Session.enter_mark(ses_sem,sub_no,roll,ceil(sub_mark),External);
		}
	      ftut1.clear();
	      ftut1.get(delim);
	    }
	    ftut1.close();

	    //load 3rd examiner mark
	    infilename[6]='3';
	    ftut1.clear();
	    
	    ftut1.open(infilename);
	    if(ftut1.fail())
	      {
		cerr<<"Cannot open file "<<infilename<<std::endl;;
		exit(2);
	      }
	
	    while(ftut1>>sub_no){
	      while(ftut1>>roll)
		{
		  ftut1>>sub_mark;
		  Session.enter_mark(ses_sem,sub_no,roll,ceil(sub_mark),Third);
		}
	      ftut1.clear();
	      ftut1.get(delim);
	  
	    }
	    ftut1.close();
	    // increase semester value
	    infilename[5]++;
	    infilename[6]='t';
	
	  }
	int sub_no_avg;
	char fileAnswer='Y';
	cout<<"The subject number for average sheet: 0 for all\n\t Your entry is is ECS: ";
	cin>> sub_no_avg;
	cout<<"Do you want to print in file?[Y]";
	cin>>fileAnswer;
	//cout<<"WHO AND WHAT MARK"<<endl;
	//cout<<Session<<endl;

	char *datax;
	long int buff_size,icount;
	if(sub_no_avg!=0)
	  buff_size=4000;
	else
	  buff_size=40000;
	datax=new char[buff_size];
	for(icount=0;icount<buff_size;icount++)
	  datax[icount]='\0';
	std::strstream test(datax, buff_size); 
	if(sub_no_avg!=0)
	  {
	    switch(ses_course){
	    case BSC:
	      {
		ses_sem=semester_value(sub_no);
		break;
	      }
	    case MSC:
	      {
		ses_sem=isemester;
		break;
	      }
	    }
	    
	  }
	else
	  ses_sem=current_ses_sem;
	Session.prepare_avg_sheet(ses_sem,test, sub_no_avg);
	  
	if(!(fileAnswer=='y' || fileAnswer=='Y'))
	  {
	    cout<<"AVERAGE SHEET:"<<endl;
	    cout<<datax<<flush;
	  }
	else
	  {
	    ofstream fout;
	    fout.open("Avg.prn");
	    fout<<datax<<flush;
	    fout.close();
	  }
	  
	delete datax;
	break;
      }
    case 7: //Prepare third examination list
      {
	//======================= Third examiner ============
	int sub_no_third;
	for(i=0;i<100;i++)
	  r_l[i]=-1;
	cout<<"\nThe list third examine for subject number : ";
	cin>>sub_no_third;
	int ses_sem;
	switch(ses_course){
	case BSC:
	  {
	    ses_sem=semester_value(sub_no);
	    break;
	  }
	case MSC:
	  {
	    ses_sem=isemester;
	    break;
	  }
	}

	/*	First=int(sub_no_third/100);
	Second=int((sub_no_third-First*100)/10);
	if(Second>=5)
	  ses_sem=First+1;
	else
	ses_sem=First;*/
	Session.list_for_third_exam(ses_sem,sub_no_third, r_l);
	i=0;
	cout<<"ROLL for THIRD EXAMINER in subject ECS: "<<sub_no_third<<endl;
	while(r_l[i]!=-1)
	  {
	    cout<<r_l[i]<<endl;
	    i++;
	  }
	break;
      }
    case 8: //Prepare tabulation sheet
      {
	// ===================== TABULATION SHEET ==========
	long int myroll;
	char *datay;
	char fileans;
	cout<<"Do you want to print in file? ";
	cin >> fileans;
	cout<<"The roll number for tabulation .. 0 for all ...";
	cin>>myroll;
	cout<<"Semester : ";
	cin>>ses_sem;
	if(myroll==0)
	  {
	    datay=new char[560000l];
	    std::strstream testy(datay,560000l);
	    for(i=0;i<100;i++)
	      r_l[i]=-1;
	    Session.show_list(Internal, r_l);
	    //
	    long file_size;
	    file_size=0l;
	    int cur_file_size;
	    for(i=0;r_l[i]!=-1;i++)
	      {
		
		  cur_file_size=Session.prepare_tabulation_sheet_v2(ses_sem,testy, r_l[i]);
		  if(cur_file_size!=-1)
		    file_size+=cur_file_size;
	    //	    Session.prepare_tabulation_sheet(ses_sem,testy, 0);
		cout<<"TABULATION SHEET FOR ALL:"<<r_l[i]<<"current size "<<file_size<<endl;
	      }
	    if(fileans=='y')
	      {
		ofstream tabfile("TAB.prn");
		tabfile.write(datay,file_size+3000);
		tabfile.close();
	      }
	    else
	      cout<<datay<<endl;

	  }
	else
	  {
	    datay=new char[4000];
	    std::strstream testy(datay,4000);
	    if(Session.prepare_tabulation_sheet_v2(ses_sem,testy, myroll)!=-1)
	      {
		cout<<"TABULATION SHEET:"<<endl;
		if(fileans=='y')
		  {
		    ofstream tabfile("TAB.prn");
		    tabfile.write(datay,4000);
		  }
		else
		  cout<<datay<<endl;
	      }
	    else
	      cout<<"STUDENT "<<myroll<<" IS NOT REGISTERED"<<endl;
	  }
	break;
      }
    case 9:
      {
	int tabulator_value;
	cout<<" You are tabulator (1st == 1 2nd == 2) ... ";
	cin>>tabulator_value;
	for(int x=0;x<tabulator_value;x++)
	  tab_type++;
	break;
      }
    }
    cout<<OPTIONS<<endl;
    //cin.flush();
    cin>>opt;
  }


 
 
 
}



int semester_value(int subject_no)
{
int semester_cnt=(floor(subject_no/100)-1)*2+1+floor((subject_no%100)/50);
return semester_cnt;
}
















