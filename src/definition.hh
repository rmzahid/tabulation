#ifndef DEFINITION
#define DEFINITION

//! Enumeration for exam type
/*! tutorial, first examiner, second examiner and third examiner

*/
enum type {Tutorial, Internal, External, Third};

//! Type of result
/*! Pass       = who passes all subject with GPA 2.5
    Probation  = who's GPA is less than 2.5 but 
                 higher or equal to 2.0
    Incomplete = due to some reason who failed to appear in any subject.
    Failed     = GPA is less than 2.0
*/
enum list_type {Pass, Probation, Incomplete, Failed};

//! Tabulator type
/*! First and second tabulator
 */
enum tab_type {Tabulator_one, Tabulator_two};

#define FormFeed 0x0c

//======================
#define SIZE 80
#define OPTIONS "Do you want to enter \n\t1=Turorial\n\t2=Internal\n\t3=External\n\t4=Third examiner\n\n\t5=Semester of choice\n\t6=Prepare average sheet\n\t7=List of students for thid examine\n\t8=Prepare tabulation sheet\n\n\t9=Tabulator number\n\t0=Quit"
#define FILENAME "exam_  .dat"

#define HALL_SIZE 10
#define BSC 2
#define MSC 1
// New Grade definition for MSc
//----- Mark range ----
#define MGRADE_APLUS 90
#define MGRADE_A 80
#define MGRADE_BPLUS 70
#define MGRADE_B 60
#define MGRADE_C 50
#define MGRADE_F 49
// -------------- grade point ----
#define MG_APLUS 4.0
#define MG_A 3.5
#define MG_BPLUS 3.0
#define MG_B 2.5
#define MG_C 2.0
#define MG_F 0.0
// ------------- letter grade ----
#define MS_APLUS "A+"
#define MS_A "A"
#define MS_BPLUS "B+"
#define MS_B "B"
#define MS_C "C"
#define MS_F "F"

//New Grade definitions for BSc
//----- Mark range ---- 
#define GRADE_APLUS 80
#define GRADE_A 75
#define GRADE_AMINUS 70
#define GRADE_BPLUS 65
#define GRADE_B 60
#define GRADE_BMINUS 55
#define GRADE_CPLUS 50
#define GRADE_C 45
#define GRADE_D 40
#define GRADE_F 39
// -------------- grade point ---- 
#define G_APLUS 4.0
#define G_A 3.75
#define G_AMINUS 3.5
#define G_BPLUS 3.25
#define G_B 3.0
#define G_BMINUS 2.75
#define G_CPLUS 2.5
#define G_C 2.25
#define G_D 2.0
#define G_F 0
// ------------- letter grade ---- 
#define S_APLUS "A+"
#define S_A "A"
#define S_AMINUS "A-"
#define S_BPLUS "B+"
#define S_B "B"
#define S_BMINUS "B-"
#define S_CPLUS "C+"
#define S_C "C"
#define S_D "D"
#define S_F "F"
 
         
#endif
