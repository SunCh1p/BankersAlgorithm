#include <iostream>
#include <vector>

bool isSafe(int n, int m, std::vector<int> available, std::vector<std::vector<int>> max, std::vector<std::vector<int>> allocation){
    //set need n*m array where need[i,j] = max[i,j] - allocation[i,j] which indicates how much a process needs for a specific resource type
    //create need n*m array
    std::vector<std::vector<int>> need(n, std::vector<int>(m,0));
    
    //fill need n*m array using formula
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    //mark processes as not finished
    std::vector<bool> finish(n, false);

    //vector to store safe sequences of process
    std::vector<int> safeSequence;

    //copy available resources
    std::vector<int> work = available;
    return false;

    //while all processes are no finished or system is not in safe state
    int count = 0;
    while(count < n){
        //find process that is not finished but whose needs can be satisfied with current resources in work
        bool found = false;
        for(int i = 0; i < n; i++){
            //check if process is finished, if not, go for next condition.
            if(finish[i] == false){
                //check if for all resources of current process, need of cureent process is less than work
                int j;
                for(j = 0; j < m; j++){
                    if(need[i][j] > work[j]){
                        break;
                    }
                }

                //check if all needs of process i were satisfied
                if(j == m){
                    //if so, free the resources of current process by adding them to available work
                    for(int k = 0; k < m; k++){
                        work[k] += allocation[i][j];
                    }
                    //add process to safe sequence
                    safeSequence.push_back(i);

                    //mark process as finished
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        //if couldn't find next process in safe sequence
        if(found == false){
            return false;
        }

    }
    
    //system is in safe state
    std::cout << "System is in safe state" << std::endl;
    for(int i = 0; i < safeSequence.size(); i++){
        std::cout << safeSequence[i] << ' ';
    }
    return true;


}

int main(){
    //set the number of processes
    int n = 5;

    //set the number of resource types
    int m = 3;

    //set allocation n*m array where allocation[i,j] = k means process pi is currently allocated k resources of type rj
    std::vector<std::vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    //set max n*m array where max[i,j] = k means process pi may request at most k instances of resource type rj
    std::vector<std::vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    //set available m array where available[j] = k means there are k instances of resource type rj
    std::vector<int> available = {3, 3, 2};

}