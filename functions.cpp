#include <iostream> 
#include <cmath> 
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
#include <fstream> 
  
#define NCARS 10 //number of cars 
#define VMAX 5//maximum velocity of cars 
#define ROADLENGTH 100//length of the road 
#define TIMESTEP 1000 //maximum number of iterations 
#define THRESHOLD 50 // threshold for car initial position 
#define PROB 70 // probability for car velocity to randomly decrease 
#define TOTALRUNS 100 
#define TIMEDIFF 3 //difference between one light turning off and the other turning off 
  
using namespace std; 
 
int TL(int t, int placed, int position, int attempt, int onfor, int limit, int delay) {
	if(t==placed+delay){//turn off the traffic light
		if (position==-3){
			position=-1;
			placed=0;
        }
	 }

    if(attempt>0){//second attempt to turn on
		if (position==-1){
			position=-3;
            attempt=0;
            placed=t;
         }
         else if(position!=-1){
			attempt++;
         }
     }

     if (t%onfor==limit && t>limit){//attempt to put TL in
         if (position==-1){
             position=-3;
             attempt=0;
             placed=t;
          }
          else if (position!=-1){
			attempt++;
          }
     }
	 return position;
}

void show_road(int road[ROADLENGTH]) { 
    // function to display the road 
    for (int i=0; i<ROADLENGTH; i++) { 
        cout<<road[i]<< " "; 
    } 
    cout<< endl; 
    cout<< endl; 
} 
  
void reset_road(int road[ROADLENGTH]) { 
    // function to reset the road to an array of -1s 
    for (int i=0; i<ROADLENGTH; i++) { 
        road[i]=-1; 
    } 
} 
  
void update_road(int road[ROADLENGTH], int temproad[ROADLENGTH]) { 
    // function to update the velocities in the road 
    for (int i=0; i<ROADLENGTH; i++) { 
        road[i]=temproad[i]; 
    } 
} 
  
void acceleration(int road[ROADLENGTH]) { 
    // function to implement acceleration rule 
    for(int i=0; i<ROADLENGTH; i++){ //acceleration 
        if(road[i]!=-1 && road[i]!=-3){ 
            if (road[i]<VMAX){ 
                road[i]++; //increase all velocities which are less than VMAX by 1 
            } 
        } 
        else { 
        //do nothing 
        } 
    } 
} 
  
void deceleration(int road[ROADLENGTH]) { 
     // function to implement deceleration rules 
    for(int i=0; i<ROADLENGTH; i++) { //deceleration 
        int a = 0; 
        if (road[i]!=0 && road[i]!=-1 && road[i]!=-3){ // If there is a car there and it has a velocity bigger than 0 
            for(int j=1; j<=road[i]; j++){ // Loop 
                if (a<1){ //so that only one car is found 
                     if (road[(i+j)%ROADLENGTH]==-3){ 
                        road[i]=j-1; 
                        a++; 
                        } 
                    if (i+j>=ROADLENGTH) { 
                        if (road[(i+j)%ROADLENGTH]!=-1) { 
                            road[i]=j-1; 
                            a++; 
                        } 
                        else { 
                            // do nothing 
                        } 
                    } 
                    else {// Not gone over the end of array 
                        if (road[i+j]!=-1){ // check spaces in front of the car. If a car is found less spaces 
                            road[i]=j-1; // than the current velocity away, change the velocity to j-1 
                            a++; // A car was found so increment a by 1 
                        } 
                        else { 
                            // do nothing 
                        } 
                    } 
                } 
                else { 
                    // do nothing 
                } 
            } 
        } 
    } 
} 
  
void randomize(int road[ROADLENGTH]) { 
    // function to randomly decrease the car velocity 
    for (int i=0; i<ROADLENGTH; i++) { //Randomisation of car velocities. PROB of the cars will have velocity-- 
        if (road[i]!=-1&&road[i]!=-3){ 
            int p=rand() % 100; 
            if (p>=PROB){// If the car has been randomly selected to decrease velocity 
                if(road[i]>0){ // and if it has a non-zero velocity 
                    road[i]--; 
                } 
            } 
        } 
    } 
} 
  
void shuffle_cars(int road[ROADLENGTH]) { 
    // function to shuffle the cars on the road 
    for (int i=0; i<ROADLENGTH; i++) { 
        int r = rand() % ROADLENGTH;  // generate a random position 
        int temp = road[i]; 
        road[i] = road[r]; 
        road[r] = temp; 
    } 
} 
  
void generate_cars(int road[ROADLENGTH], int cars) { 
    // function to generate the cars with random velocities 
    int number=0; 
    for (int i=0; i<ROADLENGTH; i++){// loop over road 
        if (number<cars) { 
            road[i]=((int) rand() % VMAX); //randomly choose velocity 
            number++; 
        } 
    } 
} 
  
void move_cars(int road[ROADLENGTH],int temproad[ROADLENGTH]) { 
    // function to move cars along and then update the road layout 
    for (int i=0; i<ROADLENGTH; i++) { 
        if (road[i]==-1) { 
            // no car there, do nothing 
        } 
        else if (road[i]==0) { 
            temproad[i]=0; 
        } 
        else { 
            if (i+road[i]<ROADLENGTH) { 
                temproad[i+road[i]]=road[i]; 
            } 
            else { 
                temproad[(i+road[i])%ROADLENGTH]=road[i]; 
            } 
        } 
    } 
} 