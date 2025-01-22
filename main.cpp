#include <iostream>
#include <iomanip>
#include <array>
#include <fstream> 
#include <cstdlib> 
#include <cmath> 
#include <string>
#include "library.h"
using namespace std;

int main() {
  //variable declaration 
    int option; // the option for the menu
    Calendar c; // the structure
    const int MAX = 10;
    Calendar weeks[MAX]; 
    int size = 0; // size is set to "0"
    ifstream input; // file declaration
    string file; // what the file name we're inputting is named
    string enter; // the enter key for aesthetics

  
  cout << "Hello! (｀ᴗ´)っ Welcome to your personal monthly lunar calandar. Please press enter to continue.\n";
  getline(cin,enter);

  do{
  cout << "Enter a file name: "; 
  getline(cin,file);
  input.open(file.c_str());
    
  // if you put a different file name, then this message appears
  } while(input.is_open() == false);

  collect_all(input, weeks, size);


  do{
  option = menu(); // calls the menu

    if (option == 1){ // displays info for both months
      
      cout << "\n" << left << setw(8) << "MONTH" << setw(8) << "WEEK #" << setw(15) << "DAYS/WEEK" << setw(40) << "ILLUMINATION" << setw(25) << "MOON PHASES" << setw(12) << "HIGHEST" << setw(2) << "LOWEST" << endl;
      cout << "===================================================================================================================" << "\n";
      display_all(weeks, size);

      cout << "===================================================================================================================" << "\n";
      cout << "\n" << endl;
      cout << "Reopening menu. . .\n";
    } // option 1's bracket

      
    else if(option == 2){ // displays info for one month
      
      search(weeks,size);
      
    } // option 2's bracket

      
    else if (option == 3){ // displays info for one week
      
      search_week(weeks, size);
      
    } //option 3's bracket

    else if(option == 4){ // displays the month's info based on sorting it by least to greatest illuminations 
      
       sort(weeks, size);
      
    } // option 4's bracket

    else if(option == 5){ // displays the month's info based on sorting it by greatest to least illuminations 
        sort2(weeks, size);
      
    } // option 5's bracket

      else if(option == 6){ // this allows the user to remove a specific week from the program

        remove(weeks, size);

      } // option 6's bracket

      
    else if(option == 7){ // this will be a collection of "cout" statements, purely for aesthetics

      astronomical_calendar();
      
    } // option 7's bracket

    else if(option == 8){ // same as option 6 but astrologically-wise rather than astromony-based
      
      astrological_calendar();

    } // option 8's bracket
    
  } while (option != 9); // exits the program
    cout << "\nExiting the program. . .thank you! (｀ᴗ´)っ";

    return option;

  
} // the main's bracket