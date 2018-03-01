test:rnd.o session.o student.o mark_sheet.o semester.o subject.o main.o
	g++ -g rnd.o mark_sheet.o subject.o student.o semester.o session.o main.o  -o test 
main.o:main.cpp 
	g++ -ansi -c -g main.cpp -o main.o
session.o:session.hh session.cpp
	g++ -ansi -c -g session.cpp -o session.o
student.o:student.hh student.cpp
	g++ -c -g student.cpp -o student.o
semester.o:semester.cpp semester.hh
	g++ -c -g semester.cpp -o semester.o
mark_sheet.o:mark_sheet.hh mark_sheet.cpp
	g++ -c -g mark_sheet.cpp -o mark_sheet.o
subject.o:subject.cpp subject.hh
	g++ -c -g subject.cpp -o subject.o
rnd.o: rnd.c
	g++ -c -g rnd.c -o rnd.o
clean:
	rm *.o *.*~ test
tar:
	tar -cvj *.cpp *.c *.hh Makefile -f Sem_exam_src.tar.bz2





# DO NOT DELETE
