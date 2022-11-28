#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t> workSched, size_t workDay){   
    if( dailyNeed <= (sched[workDay].size()) ){ //finished current day's schedule
			workDay += 1;
      return scheduleHelper(avail, dailyNeed, maxShifts, sched, workSched, workDay); //recursive call
    }
		else if(avail.size() <= workDay){  //scheduled == matrix
      return 1;
    } 
    else{
			bool flag1 = 0; //keeps track of whether an individual is working the current day
			bool flag2 = 0; //keeps track of the availability, and is used to schedule an individual if there is room
			for(Worker_T i = 0; i < avail[0].size(); i++){ //similar to wordle implementation; finds availability of individuals instead of letters
				if( !(sched[workDay].empty()) ){
						for(size_t j = 0; j < sched[workDay].size(); j++){
							if(sched[workDay][j] == i){
								flag1 = 1;
							}
					}
				}
				if( !(flag1) && (avail[workDay][i]) && (workSched[i] < maxShifts) ){
						sched[workDay].push_back(i);
						workSched[i]++;
						flag2 = scheduleHelper(avail, dailyNeed, maxShifts, sched, workSched, workDay); //recursive call
						if(flag2){ //the individual is working, so remove them from schedule
							return 1;
						}
						sched[workDay].pop_back();
						workSched[i] -= 1;
				}
			}	        
    } 
    return 0; //no solution
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

		for(size_t k = 0; k < avail.size(); k++){
			std::vector<Worker_T> temp;
			sched.push_back(temp);
    }

    std::vector<size_t> tempWorkSched;
    for(size_t k = 0; k < avail[0].size(); k++){
			tempWorkSched.push_back(0);
		}

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, tempWorkSched, 0);
}
