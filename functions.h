#ifndef FUNCTIONS_H_INCLUDED 
#define FUNCTIONS_H_INCLUDED 
  
#include <iostream> 
#include <cmath> 
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
#include <fstream> 
  
#define NCARS 10 //number of cars 
#define VMAX 5//maximum velocity of cars 
#define ROADLENGTH 100//length of the road 
#define TIMESTEP 1000//maximum number of iterations 
#define THRESHOLD 50 // threshold for car initial position 
#define PROB 70 // probability for car velocity to randomly decrease 
#define TOTALRUNS 100 
#define TIMEDIFF 3 //difference between one light turning off and the other turning off 
  
  
using namespace std; 
  
void show_road(int road[ROADLENGTH]); 
void reset_road(int road[ROADLENGTH]); 
void update_road(int road[ROADLENGTH], int temproad[ROADLENGTH]); 
void acceleration(int road[ROADLENGTH]); 
void deceleration(int road[ROADLENGTH]); 
void randomize(int road[ROADLENGTH]); 
void shuffle_cars(int road[ROADLENGTH]); 
void generate_cars(int road[ROADLENGTH], int cars); 
void move_cars(int road[ROADLENGTH],int temproad[ROADLENGTH]);
int TL(int t, int placed, int position, int attempt, int onfor, int limit, int delay);
  
  
  
  
#endif // FUNCTIONS_H_INCLUDED 