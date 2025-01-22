#include "library.h"
#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// this is the menu function
int menu() {
  int input;
  cout << "\nChoose from the following options:\n";
  cout << "1. Display All Data For November & December 2023\n";
  cout << "2. Diplay All Data For A Specific Month\n";
  cout << "3. Display All Data For A Specific Week\n";
  cout << "4. Sort Information By Smallest to Greatest Illumination\n";
  cout << "5. Sort Information By Greatest to Smallest Weekly Illumination\n";
  cout << "6. Remove A Specific Week In The Calendar\n";
  cout << "7. Display Astronomical Information in November & December 2023\n";
  cout << "8. Display Astrological Information For November & December 2023\n";
  cout << "9. Exit The Program\n";
  cout << "\nEnter Your Option (1 - 9)\n";
  cin >> input;

  cin.ignore();

  // if the user inputs a number below 1 or above 6
  while (input < 1 || input > 9) {
    cout << "Invalid option. Please try again.\n";
    cin >> input;
    cin.ignore();
  }
  return input;
}


// collect function : collects singular information
void collect(ifstream &input, Calendar &c) {
  input >> c.month_number;
  input >> c.week_number;
  input >> c.days_in_week;

  for (int i = 0; i < c.days_in_week; i++) {
    input >> c.illumination[i];

    // changes the highest illumination
    if (c.highest_illu < c.illumination[i]) {
      c.highest_illu = c.illumination[i];
    }

    // changes the lowest illumination
    if (c.lowest_illu > c.illumination[i]) {
      c.lowest_illu = c.illumination[i];
    }
  }

  for (int i = 0; i < c.days_in_week; i++) {
    input >> c.moon_phase[i];
  }
}


// collect function: collects all information
void collect_all(ifstream &input, Calendar weeks[], int &size) {
  while (input.eof() == false) {
    Calendar c;
    collect(input, c);

    weeks[size] = c;

    size++;
  }
}


// display feature: displays a line of information
void display(Calendar c) {
  cout << left << " " << setw(9) << c.month_number << setw(10) << c.week_number
       << setw(6) << c.days_in_week;

  for (int i = 0; i < c.days_in_week; i++) {
    cout << setw(3) << c.illumination[i];
    if (i == c.days_in_week - 1)
      cout << setw((7 - c.days_in_week) * 4 + 1) << ' ';
    else
      cout << ' ';
  }

  cout << setw(10) << ' ';

  for (int i = 0; i < c.days_in_week; i++) {
    cout << setw(3) << c.moon_phase[i];
    if (i == c.days_in_week - 1)
      cout << setw((7 - c.days_in_week) * 4 + 1) << ' ';
    else
      cout << ' ';
  }
  cout << setw(6) << ' ';

  cout << setw(12) << c.highest_illu << setw(5) << c.lowest_illu << endl;

}


// display all feature: displays all information through a loop
void display_all(Calendar weeks[], int size) {
  for (int i = 0; i < size; i++) {
    display(weeks[i]);
  }
}


// generic search feature : regards the month
void search(Calendar weeks[], int size) {
  int search_month;
  cout << "Which month would you like the data for?\n" << endl;
  cout << "11 - November" << endl;
  cout << "12 - December"
       << "\n"
       << endl;
  cin >> search_month;

  if (search_month != 11 && search_month != 12) {
    cout << "\nPlease enter valid month number. . .\nRepooting back to main menu. . .\n";
  }

  else {
    // choosing November's information
    if (search_month == 11) {
      cout << "\nShowing the data for the month of November. . ." << endl;
    }

    else // choosing December's information
      cout << "\nShowing the data for the month of December. . ." << endl;

    cout << "\n";
    cout << "\n" << left << setw(8) << "MONTH" << setw(8) << "WEEK #" << setw(15) << "DAYS/WEEK" << setw(40) << "ILLUMINATION" << setw(25) << "MOON PHASES" << setw(12) << "HIGHEST" << setw(2) << "LOWEST" << endl;
    cout << "===================================================================================================================" << "\n";
    for (int i = 0; i < size; i++) {
      if (weeks[i].month_number == search_month)
        display(weeks[i]);
    }
    cout << "===================================================================================================================" << "\n";

    cout << "\n" << endl;
    cout << "Reopening menu. . .\n";
  }
}


// a sub-search feature to get a specific week
void search_week(Calendar weeks[], int size) {
  int search_month;
  int search_week; 
    cout << "Which month would you like the data for?\n" << endl;
    cout << "11 - November" << endl;
    cout << "12 - December\n" << endl;
    cin >> search_month;

  cout << "Which week would you like the data for?\nPlease pick a number between (1 - 5)\n" << endl;
  cin >> search_week;
  
    if ((search_month != 11 && search_month != 12) || (search_week > 5 || search_week < 1)) {
      cout << "\nPlease enter valid numbers. . .\nRepooting back to main menu. . .\n";
    }
      
  else {

      if (search_month == 11) {
        cout << "\nShowing the data for week #" << search_week << " in the month of November. . ." << endl;
        }

       else // choosing December's information
        cout << "\nShowing the data for week #" << search_week << " in the month of December. . ." << endl;

      cout << "\n";
      cout << "\n" << left << setw(8) << "MONTH" << setw(8) << "WEEK #" << setw(15) << "DAYS/WEEK" << setw(40) << "ILLUMINATION" << setw(25) << "MOON PHASES" << setw(12) << "HIGHEST" << setw(2) << "LOWEST" << endl;
      cout << "===================================================================================================================" << "\n";
  
          for (int i = 0; i < size; i++) {
            if (weeks[i].month_number == search_month && weeks[i].week_number == search_week)
              display(weeks[i]);
          }
    cout << "===================================================================================================================" << "\n";

    cout << "\n" << endl;
    cout << "Reopening menu. . .\n";
       }
  }


// a sort feature that's organize the information based on least to greatest illumination
  void sort(Calendar weeks[], int& size){
    for(int j = 1; j < size; j++){
      for(int i = j; i > 0; i--){
        if (weeks[i - 1].highest_illu > weeks[i].highest_illu){
          swap(weeks[i - 1], weeks[i]);
        }
      } 
    }

      cout << "\nShowing the data based on smallest to greatest weekly illumination. . ." << endl;
      cout << "\n";
      cout << "\n" << left << setw(8) << "MONTH" << setw(8) << "WEEK #" << setw(15) << "DAYS/WEEK" << setw(40) << "ILLUMINATION" << setw(25) << "MOON PHASES" << setw(12) << "HIGHEST" << setw(2) << "LOWEST" << endl;
      cout << "===================================================================================================================" << "\n";
    
      display_all(weeks, size);
    
    cout << "===================================================================================================================" << "\n";
      cout << "\n";
      cout << "Reopening menu. . .\n";
  }


// a sort feature that's organize the information based on highest to lowest illumination
void sort2(Calendar weeks[], int& size){
  for(int j = 1; j < size; j++){
    for(int i = j; i > 0; i--){
      if (weeks[i - 1].highest_illu < weeks[i].highest_illu){
        swap(weeks[i - 1], weeks[i]);
      }
    } 
  }

   cout << "\nShowing the data based on greatest to smallest weekly illumination. . ." << endl;
  cout << "\n";
  cout << "\n" << left << setw(8) << "MONTH" << setw(8) << "WEEK #" << setw(15) << "DAYS/WEEK" << setw(40) << "ILLUMINATION" << setw(25) << "MOON PHASES" << setw(12) << "HIGHEST" << setw(2) << "LOWEST" << endl;
  cout << "===================================================================================================================" << "\n";
  
    display_all(weeks, size);

  cout << "===================================================================================================================" << "\n";
    cout << "\n";
    cout << "Reopening menu. . .\n";
  
}


void remove(Calendar weeks[], int size){
  int search_month;
  int search_week; 
    cout << "You have chosen to remove a specific week from the program." << endl;
    cout << "Which month would you like the data for?\n" << endl;
    cout << "11 - November" << endl;
    cout << "12 - December\n" << endl;
    cin >> search_month;

  cout << "Which week would you like the data for?\nPlease pick a number between (1 - 5)\n" << endl;
  cin >> search_week;

    if ((search_month != 11 && search_month != 12) || (search_week > 5 || search_week < 1)) {
      cout << "\nPlease enter valid numbers. . .\nRepooting back to main menu. . .\n";
    }

  else {
    int pos = -1;
    for (int i = 0; i < size; i++){
      if(weeks[i].month_number == search_month && weeks[i].week_number == search_week){
        pos = i;
        break;
      }
    }
    for (int i = pos; i < size - 1; i++){
      weeks[i] = weeks[i + 1];
    }
    size--;

    cout << "Week #" << search_week << " in the #" << search_month << "th month has been removed from the Calendar." << endl;
    cout << "\n";
    cout << "Reopening menu. . .\n";
  }
}


// this is an option for important dates in astronomy/moon phases. Purely for aesthetics
  void astronomical_calendar(){
    cout << "\n";
    cout << "\nNow opening astronomical calandar. . ." << endl; 
    cout << "\n";
    cout << "===================================================================================================================" << "\n";

    cout << "\n";
    cout << "November Moon Phase Dates:\n";
    cout << "\t ♡ Waning Gibbous : 1, 2, 3, 4, 28, 29, 30" << endl;
    cout << "\t ♡ Last Quarter : 5" << endl;
    cout << "\t ♡ Waning Crescent : 6, 7, 8, 9, 10, 11, 12" << endl;
    cout << "\t ♡ 🌑 New Moon : 13 🌑" << endl;
    cout << "\t ♡ Waxing Crescent : 14, 15, 16, 17, 18, 19" << endl;
    cout << "\t ♡ First Quarter : 20" << endl;
    cout << "\t ♡ Waxing Gibbous : 21, 22, 23, 24, 25, 26" << endl;
    cout << "\t ♡ 🌕 Full Moon : 27 🌕" << endl;

    cout << "\n";
    
    cout << "\n";
    cout << "December Moon Phase Dates:\n";
    cout << "\t ♡ Waning Gibbous : 1, 2, 3, 4, 5, 29, 30, 31" << endl;
    cout << "\t ♡ Last Quarter : 6" << endl;
    cout << "\t ♡ Waning Crescent 7, 8, 9, 10, 11, 12: " << endl;
    cout << "\t ♡ 🌑 New Moon : 13 🌑" << endl;
    cout << "\t ♡ Waxing Crescent : 14, 15, 16, 17, 18, 19" << endl;
    cout << "\t ♡ First Quarter : 20, 21" << endl;
    cout << "\t ♡ Waxing Gibbous : 22, 23, 24, 25, 26" << endl;
    cout << "\t ♡ 🌕 Full Moon : 27, 28 🌕" << endl;
    cout << "\n";

    cout << "===================================================================================================================" << "\n";
    cout << "\n";
    cout << "Reopening menu. . .\n";
  }


// this is an option for important dates in astrology/zodiacs. Purely for aesthetics
void astrological_calendar(){
  cout << "\n";
  cout << "\nNow opening astrological calandar. . ." << endl; 
  cout << "\n";
  cout << "===================================================================================================================" << "\n";

  cout << "\n";

  cout << "November's Astrological Chart':\n";
  cout << "\t ♡ 11/1: Scorpio New Moon ♏ " << endl; 
  cout << "\t ♡ 11/2: Mecury Sagittarius ♐ " << endl; 
  cout << "\t ♡ 11/3: Mars Enters Leo ♌ " << endl;
  cout << "\t ♡ 11/9: First Quarter Moon in Aquarius ♒ " << endl; 
  cout << "\t ♡ 11/11: Venus Enters Capricorn ♑ " << endl; 
  cout << "\t ♡ 11/15: Full Moon In Taurus ♉ " << endl; 
  cout << "\t ♡ 11/18: Pluto Enters Aquarius ♒ " << endl;
  cout << "\t ♡ 11/21: Sagittarius Season Begins ♐ " << endl; 
  cout << "\t ♡ 11/22: Last Quarter Moon In Virgo ♍ " << endl; 
  cout << "\t ♡ 11/25: Mecury Retrograde Begins In Sagittarius ♐ " << endl; 

  cout << "\n";
  
  cout << "December's Astrological Chart':\n";
  cout << "\t ♡ 12/1: Mecury Enters Capricorn ♑ " << endl; 
  cout << "\t ♡ 12/04: Venus Enters Scorpio ♏ " << endl; 
  cout << "\t ♡ 12/05: Last Quarter Moon In Virgo ♍ " << endl; 
  cout << "\t ♡ 12/06: Neptune Directs Into Pisces ♓ " << endl; 
  cout << "\t ♡ 12/12: New Moon In Sagittarius ♐ " << endl; 
  cout << "\t ♡ 12/13 Mecury Retrograde Enters Capricorn ♑ " << endl; 
  cout << "\t ♡ 12/21 Capricorn Season Begins ♑ " << endl; 
  cout << "\t ♡ 12/23 Mecury Retrograde Reenters Into Sagittarius ♐ " << endl; 
  cout << "\t ♡ 12/26: Full Moon In Cancer ♋ " << endl; 
  cout << "\t ♡ 12/29: Venus Enters Sagittarius ♐ " << endl; 
  cout << "\t ♡ 12/30: Jupiter Directs In Taurus ♉ " << endl; 
  
  cout << "\n";
  cout << "===================================================================================================================" << "\n";
  cout << "\n";
  cout << "Reopening menu. . .\n";
}