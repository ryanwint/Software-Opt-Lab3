/*
Ryan Winters
1-30-19
EE599 Lab3

*/


#include <iostream> 
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <stdio.h> 

#include <sstream>

#include <string.h>
#include <stdlib.h>

#define MAXLEN 512
using namespace std;

class Pancake         {

public:
	int size;
	bool burnt;
	Pancake(){//default constructor
		//size=0
		//burnt=0;
	}
	~Pancake(){//default constructor
		//printf("Pancake Destroyed");

	}
	void flip_pancake()  {
		burnt = !burnt;
	}
	void printPancake(){
		printf("Size: %d\n",this->size);
		printf("Burnt: %d\n",this->burnt);
	}
};


class PancakePile         {
public:
	int len;
	Pancake* stack;//init array of pancakes
	PancakePile(){//default constructor
		//printf("PancakePile Constructor!!\n");
		//Pancake** stack;
		stack = new Pancake[MAXLEN];//more initialize the stack of pancakes
	}
	~PancakePile(){//default constructor
		//printf("PancakePile Destroyed");

	}
    //All sorting function reference: https://www.geeksforgeeks.org/pancake-sorting/--Cited!
	/* Reverses arr[0..i] */
	void flip(int i) 
	{
		int temp, start = 0; 
		while (start < i) 
		{
            temp = stack[start].size;
			stack[start].size = stack[i].size; 
			stack[i].size = temp; 
			start++; 
			i--; 
		} 
	} 

	// Returns index of the  
	// maximum element in  
	// arr[0..n-1]  
	int findMax(int n) 
	{ 
		int mi, i; 
		for (mi = 0, i = 0; i < n; ++i) 
			if (stack[i].size > stack[mi].size) 
				mi = i; 
		return mi; 
	}

	int findMin(int n) 
	{ 
		int mi, i; 
		for (mi = 0, i = 0; i < n; ++i) 
			if (stack[i].size < stack[mi].size) 
				mi = i; 
		return mi; 
	}

    
	//Pancake pancake[MAXLEN];
	//printf("Hello there");
	void print_PancakePile()  {
		printf("Pancake Pile\n");
	}
	void pancake_sort_ascending()  {
		//printf("Sort Ascending\n");
    // Start from the complete 
    // array and one by one  
    // reduce current size  
    // by one 
    for (int curr_size = len; curr_size > 1; --curr_size) 
    { 
        // Find index of the  
        // maximum element in  
        // arr[0..curr_size-1] 
        int mi = findMax(curr_size); 
  
        // Move the maximum 
        // element to end of  
        // current array if 
        // it's not already 
        // at the end 
        if (mi != curr_size-1) 
        { 
            // To move at the end, 
            // first move maximum  
            // number to beginning  
            flip(mi); 
  
            // Now move the maximum  
            // number to end by  
            // reversing current array 
            flip(curr_size-1); 
        }
    }
	}
	void pancake_sort_descending()  {
		//printf("Sort Descending\n");
    for (int curr_size = len; curr_size > 1; --curr_size) 
    { 
        int mi = findMin(curr_size); 
        if (mi != curr_size-1) 
        { 
            flip(mi); 
            flip(curr_size-1); 
        }
    }
	}
	void pancake_sort_ascending_burnt_down()  {
		//printf("Sort Ascending Burnt Down\n");
        pancake_sort_ascending();//get it ascending
    for (int i=0; i<len; i++) 
    { 
        
        if (stack[i].burnt == 1)//facing wrong direction 
        {
            if(i>0){
                flip(i);
            }
            stack[i].flip_pancake();//flip pancake on top
            if(i>0){
                flip(i);
            }
        }
    }
	}
	void pancake_sort_descending_burnt_up()  {
		//printf("Sort Descending Burnt Up\n");
        pancake_sort_descending();//get it ascending
    for (int i=0; i<len; i++) 
    { 
        
        if (stack[i].burnt == 0)//facing wrong direction 
        {
            if(i>0){
                flip(i);
            }
            stack[i].flip_pancake();//flip pancake on top
            if(i>0){
                flip(i);
            }
        }
    }
	}
};

class MPancakePiles         {
public:
	int rowCount = MAXLEN;
	int colCount = MAXLEN;
	PancakePile** XY = new PancakePile*[rowCount];
	MPancakePiles(){//default constructor
		for(int i = 0; i < rowCount; ++i){//reference https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
			XY[i] = new PancakePile[colCount];
		}
		//printf("MPancakePiles Constructor!!\n");
		//remember to match each "new" to a "delete" later

	}
	~MPancakePiles(){//default constructor
		printf("MPancakePiles Destroyed\n");

	}
	//Pancake pancake[MAXLEN];
	//printf("Hello there");
	void MPancakePilesPrint()  {
		printf("Hello there");
	}
	void sortExterior(int x, int y)  {
		//printf("Sort interior\n");
        for(int i=0;i<y;i++){
            XY[0][i].pancake_sort_descending_burnt_up();
        }
        for(int i=0;i<y;i++){
            XY[x-1][i].pancake_sort_descending_burnt_up();
        }
        for(int i=0;i<x;i++){
            XY[i][0].pancake_sort_descending_burnt_up();
        }
        for(int i=0;i<x;i++){
            XY[i][y-1].pancake_sort_descending_burnt_up();
        }
	}
	void sortInterior(int x, int y)  {//check edge cases of only like two rows!!!
        for(int i=1;i<x-1;i++){//all middle rows
            for(int j=1;j<y-1;j++){//all middle columns
                XY[i][j].pancake_sort_ascending_burnt_down();
            }
        }
	}    };          

//Reference Code Cited! https://www.quora.com/How-do-I-convert-a-string-into-an-integer-in-C++-I-have-many-strings-like-98756-and-433-and-I-want-to-convert-them-to-integer-variables-How-can-I-do-that
int StringToInteger(string NumberAsString)
{
	int NumberAsInteger;
	stringstream ss;
	ss << NumberAsString;
	ss >> NumberAsInteger;
	return NumberAsInteger;
}


// MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN
int main( ) {
//http://www.cplusplus.com/doc/tutorial/files/ for IO below Cited!

	int x=5;
	int y=5;
	int z=5;
  int a=0;
  int b=0;
  int c=0;
  string line;
  ifstream myfile ("input.txt");
  char * pch;
  
  
  int first=0;
  int i=-1;
  int j=0;
  int k=0;
  int count=0;
  int hold=0;
  MPancakePiles table;
  if (myfile.is_open())
  {
      //getline (myfile,line);
      getline (myfile,line);
      char* buf = strdup(line.c_str());//remember to free char later!!! https://stackoverflow.com/questions/16495527/error-trying-to-use-strtok-for-a-string
      pch = strtok (buf," ,.-");
      //printf ("%s\n",pch);
      x = StringToInteger(pch);
      //printf("%d\n",x);
      pch = strtok (NULL, " ,.-");
      y = StringToInteger(pch);
      //printf("%d\n",y);
      pch = strtok (NULL, " ,.-");
      z = StringToInteger(pch);
      //printf("%d\n",z);
      b=0;
    while ( getline (myfile,line) )
    {
      if(count%y==0){
          i++;
          j=0;
      }
		PancakePile pancakePile;
        pancakePile.len=z;
        table.XY[i][j] = pancakePile;
      char* buf = strdup(line.c_str());//remember to free char later!!! https://stackoverflow.com/questions/16495527/error-trying-to-use-strtok-for-a-string
      pch = strtok (buf," ,.-");
    k=0;
    first=0;
      while (pch != NULL)//http://www.cplusplus.com/reference/cstring/strtok/ --Cited!
    {
        if(first==0){//for first loop store size, second loop store burnt
            a = StringToInteger(pch);
			Pancake pancake;
			table.XY[i][j].stack[k] = pancake;
			table.XY[i][j].stack[k].size=a;
            pch = strtok (NULL, " ,.-");
            //k++;//increase column count
            first=1;
        }
        else{
            a = StringToInteger(pch);
            table.XY[i][j].stack[k].burnt=a;
            pch = strtok (NULL, " ,.-");
            first=0;
            k++;
        }
    }
    count++;
    j++;
    //printf("\n");
    }
    myfile.close();
  }
  

/*    //print the first stack
    for(int i=0;i<z;i++){
        table.XY[1][1].stack[i].printPancake();
}*/
    table.sortInterior(x,y);
    table.sortExterior(x,y);
    printf("\n");
    /*//print the first stack
    for(int i=0;i<z;i++){
        table.XY[1][1].stack[i].printPancake();
    }*/
    
/////////Output to File////////
  ofstream myoutputfile ("output.txt");
  if (myoutputfile.is_open())
  {
      //print x,y,z
      myoutputfile << x << " ";
      myoutputfile << y << " ";
      myoutputfile << z << "\n";
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			for(int k=0;k<z;k++){
				myoutputfile << table.XY[i][j].stack[k].size <<",";
				myoutputfile << table.XY[i][j].stack[k].burnt <<" ";
			}
            if(j==(y-1) && i==(x-1)){//dont add newline for last line
                myoutputfile << "\n";//actually i do
            }
            else{
                myoutputfile << "\n";
            }
		}
	}
    myoutputfile.close();
  }
  else cout << "Unable to open file";


    //exit(0);
 
	//Destruction
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			delete[] table.XY[i][j].stack;
		}
		delete[] table.XY[i];
	}
	delete[] table.XY;
    delete[] pch;

	exit(0);


	return 0;    }
