// Road simulation
// Simulate cars moving along a road using the simnplifications of the cellular automata model

// includes
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "functions.h" // include functions header file

using namespace std;
int main() {
    int attempt1=0;//	|
    int attempt2=0;//	|
    int attempt3=0;//	|
	int attempt4=0;//	|
	int attempt5=0;//	|
	int attempt6=0;//	|
	int attempt7=0;//	|	
    int placed1=0;//	|	 TL Variables
    int placed2=0;//	|	
    int placed3=0;//	|
	int placed4=0;//	|
	int placed5=0;//	|
	int placed6=0;//	|
	int placed7=0;//	|	

    srand(time(NULL)); // seed random number generator
    int cars=1;
    long double KEresults[ROADLENGTH];
    long double FLOWresults[ROADLENGTH];
	
	for (int c=0; c<ROADLENGTH; c++){
        cout<<"Running program, iteration "<<c+1<<endl;
        long double flow_rates[TOTALRUNS];
        long double KE_LOSS[TOTALRUNS];
        for (int runs=0; runs<TOTALRUNS; runs++) {
            int road[ROADLENGTH]; // set up road array
            int temproad[ROADLENGTH];// temp array to move cars
            reset_road(road); // put all road=-1
            long double moved=0;
            long double ke_loss[TIMESTEP-1];
            for (int i=0; i<TIMESTEP-1; i++) {
                ke_loss[i]=0;
            }

            generate_cars(road, cars);//add in cars with randomly chosen velocities
            shuffle_cars(road); // shuffle car positions
            //show_road(road);
            //system("pause");

            for (int t=0; t<TIMESTEP; t++) { // loop over timesteps
				//Traffic lights							
				road[6]=TL(t, placed1, road[6], attempt1, 100, 0, 10);//			timestep, placed, position, attempt, time comes on, t>, time lights are on for
				road[17]=TL(t, placed2, road[17], attempt2, 100, 5, 10);//			t%onfor=limit && t>limit
				road[29]=TL(t, placed3, road[29], attempt3, 100, 10, 10);
				road[54]=TL(t, placed4, road[54], attempt4, 100, 15, 10);
				road[69]=TL(t, placed5, road[69], attempt5, 100, 20, 10);
				road[85]=TL(t, placed6, road[85], attempt6, 100, 25, 10);
				road[96]=TL(t, placed7, road[96], attempt7, 100, 30, 10);
				// do the road rules
				acceleration(road); //adjust speed due to acceleration
				deceleration(road); // adjust speed due to deceleration
				randomize(road);// adjust speed randomly
				for(int i=0; i<ROADLENGTH; i++) {//compare KE losses
					if (t>0){
						if (temproad[i]>0) {
							if(road[i]<temproad[i]) {
								ke_loss[t-1]+=((pow((double)temproad[i],2)-pow((double)road[i],2))/cars);
							}
						}
					}
				}

            reset_road(temproad); // reset temp road to all -1s

            // Move the cars
            for (int i=0; i<ROADLENGTH; i++) {
                if (road[i]==-1) {
                // no car there, do nothing
                }
                else if (road[i]==0) {
                    temproad[i]=0; // car but no velocity
                }
                else if (road[i]==-3) {
                    temproad[i]=-3; // copy over traffic light
                }
                else {
                    if (i+road[i]<ROADLENGTH) {//Doesn't move off end of road
                        temproad[i+road[i]]=road[i];
                        //cars_moved[t]++;
                    }
                    else {
                        temproad[(i+road[i])%ROADLENGTH]=road[i];//Account for cars moving off end of road
                        //cars_moved[t]++;
                        moved++;
                    }
                }
            }

            update_road(road,temproad);//update the road array

            /*show_road(road);// print out the result
            system("pause"); // incase want to run 1 iteration at a time
            cout<<endl;
            cout<<"------------"<<t<<"----------------";
            cout<<endl;*/
            flow_rates[runs]=moved/TIMESTEP; //store flow results
            KE_LOSS[runs]=ke_loss[t-1]/TIMESTEP;
            }
        }
        long double FLOWaverage=0;
        for (int i=0; i<TOTALRUNS; i++) {
			FLOWaverage+=flow_rates[i];
        }
        FLOWresults[c]=FLOWaverage/TOTALRUNS;
        long double KEaverage=0;
        for (int i=0; i<TOTALRUNS; i++) {
			KEaverage+=KE_LOSS[i];
        }
        KEresults[c]=KEaverage/TOTALRUNS;
        cars++;
	}
	ofstream KE("keloss.txt"); // open the file
    if (KE.is_open()) {//if the file is open
		for (int i=0; i<ROADLENGTH; i++) {
			KE<<KEresults[i]<<endl;
        }
        KE.close(); // close the file
    }
    else {
		cout<<"Error opening file. Check something! Exiting now....";
        exit(1);
    }
    ofstream RESULTS("FLOWaverages.txt"); // open the file
    if (RESULTS.is_open()) {//if the file is open
		for (int i=0; i<ROADLENGTH; i++) {
			RESULTS<<FLOWresults[i]<<endl;
        }
        RESULTS.close(); // close the file
    }
    else {
		cout<<"Error opening file. Check something! Exiting now....";
		exit(1);
    }
    return 0;
}