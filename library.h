#include <iostream>
#include <string>
using namespace std;

// structure declarations
  struct Calendar{
    int month_number; 
    int week_number; // week
    int days_in_week = 0; // amount of days in the week, this will go up by "1" per day
    double illumination[7]; // the moon's illumination for the night
    double highest_illu = 0; 
    double lowest_illu = 120;
    string moon_phase[7]; // the moon phase for the day/night
  };

// function protoypes
  int menu();
  void collect(ifstream& input, Calendar& c); // general collect
  void collect_all(ifstream& input, Calendar weeks[], int& size); // collect_all
  void display(Calendar c); // displays one line
  void display_all(Calendar weeks[], int size); // displays all
  void search(Calendar weeks[], int size); // search by month
  void search_week(Calendar weeks[], int size); // search by month -> week
  void sort(Calendar weeks[], int& size); // sorting by L -> G
  void sort2(Calendar weeks[], int& size); // sorting by G -> L
  void remove(Calendar weeks[], int size); // removing a specific week
  void astronomical_calendar(); // moon phase calander (aesthetics)
  void astrological_calendar(); // zodiac calander (aesthetics)