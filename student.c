// Do not remove #ifdef ... #endif before and after each function.
// 
// They are used to test different functions in your program and give
// partial credits, in case your program does not work completely.

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msort.h"

void StudentPrint(Student * stu, int num)
{
  printf("There are %d students\n", num);
  for (int ind = 0; ind < num; ind ++)
    {
      printf("ID = %d, First Name = %s, Last Name = %s\n",
	     stu[ind].ID,  stu[ind].firstname, stu[ind].lastname);
    }
}

#ifdef TEST_READ
// return false if anything is wrong 
// return true if reading the file successfully and the data is save in
// the allocated memory
// input: filename, the name of the input file
// output: address of the allocated memory
// output: number of students
bool StudentRead(char * filename, Student * * stu, int * numelem)
{
  // open the file to read
  FILE * name = fopen(filename, "r");



  // if fopen fails, return false
  // do not use fclose since fopen already fails
  if(name == NULL)
  {
   return false;
  }

  // count the number of lines to determine the number of students
  
  int lines=0;
  int che =0;
  while(!feof(name))
  {
   che = fgetc(name);
   if(che == '\n')
    {
     lines++;
    }
  }
  * numelem = lines;
  // return to the beginning of the file
  // you can use fseek or
  // fclose followed by fopen
  // You need to check whether fseek or fopen fails
  // Do not use rewind because it does not report whether it fails

  int finder = fseek(name, 0, SEEK_SET);
  if(finder != 0)
  {
   fclose(name);
   return false;
  }

  // allocate memory for the data
  Student * studentfinder;//student is a type
  studentfinder = malloc(sizeof(Student) * lines);//malloc allocates multiple spaces of memory in larger memory hold


  // check whether memory allocation fails
  if(studentfinder == NULL)
  {
   return false;
  }

  // read the data from the file and store the data in the allocated memory
  int stud1, stud2, stud3;
  for(int i = 0; i < lines; i++)
  {
   stud1 = fscanf(name, "%d", & studentfinder[i].ID);
   stud2 = fscanf(name, "%s", studentfinder[i].firstname);
   stud3 = fscanf(name, "%s\n", studentfinder[i].lastname);
   if((stud1 < 0) || (stud2 < 0) || (stud3 < 0))
   {
    fclose(name);
    return false;
   }
  }
  
  *stu = studentfinder;
  // close the file
  fclose(name);
  return true;
}
#endif

#ifdef TEST_WRITE
// return false if anything is wrong 
// return true if writing the file successfully
// input: filename, the name of the output file
// input: address of the student array
// input: number of students

bool StudentWrite(char * filename, Student * stu, int numelem)
{
  // open the file to write 
  FILE * name2 = fopen(filename, "w");
  

  // if fopen fails, return false
  // do not use fclose since fopen already fails
  if(name2 == NULL)
  {
   return false;
  }

  // write the students to the output file
  int output1, output2, output3;

  for(int j = 0; j < numelem; j++){
  output1 = fprintf(name2, "%d ", stu[j].ID);
  output2 = fprintf(name2, "%s ", stu[j].firstname);
  output3 = fprintf(name2, "%s\n", stu[j].lastname); 
  }
  if((output1 < 1) || (output2 < 1) || (output3 < 1))
  {
   fclose(name2);
   return false;
  }

  fclose(name2);
  return true;
}


int comparefunc(const void * arg1, const void * arg2)
{ 
  const Student * ptr1 = (Student *) arg1;
  const Student * ptr2 = (Student *) arg2;
  int val1 = ptr1 -> ID;
  int val2 = ptr2 -> ID;
  if(val1 < val2)
  {
   return -1;
  }
  if(val1 == val2)
  {
  return 0;
  } 
  return 1;
} 

int cmpstringfirst(const void *arg1, const void *arg2)
{
  const Student * ptr1 = (Student *) arg1;
  const Student * ptr2 = (Student *) arg2;
  const char * str1 = ptr1 -> firstname;
  const char * str2 = ptr2 -> firstname;
  return strcmp(str1, str2);
}

int cmpstringlast(const void *arg1, const void *arg2)
{
  const Student * ptr1 = (Student *) arg1;
  const Student * ptr2 = (Student *) arg2;
  const char * str1 = ptr1 -> lastname;
  const char * str2 = ptr2 -> lastname;
  return strcmp(str1, str2);
}

#endif 

#ifdef TEST_SORTID
void StudentSortbyID(Student * stu, int numelem)
{
 msort(stu, numelem, comparefunc); 
}
#endif

#ifdef TEST_SORTFIRSTNAME
void StudentSortbyFirstName(Student * stu, int numelem)
{
 msort(stu, numelem, cmpstringfirst);
}
#endif

#ifdef TEST_SORTLASTNAME
void StudentSortbyLastName(Student * stu, int numelem)
{
 msort(stu, numelem, cmpstringlast);
}
#endif
