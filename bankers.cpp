#include <iostream>
#include <vector>
#include <fstream>

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
                        work[k] += allocation[i][k];
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
    std::cout << "Safe Sequence:" << std::endl;
    for(int i = 0; i < safeSequence.size(); i++){
        std::cout << safeSequence[i] << ' ';
    }
    std::cout << std::endl;
    return true;
}

int main(){
    //open file
    std::ifstream file("input.txt");

    //set the number of processes
    int n;
    file >> n;

    //set the number of resource types
    int m;
    file >> m;

    //get allocation n*m vector where allocation[i,j] = k means process pi is currently allocated k resources of type rj
    std::vector<std::vector<int>> allocation(n, std::vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            file >> allocation[i][j];
        }
    }

    //get max n*m vector where max[i,j] = k means process pi may request at most k instances of resource type rj
    std::vector<std::vector<int>> max(n, std::vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            file >> max[i][j];
        }
    }

    //get available m array where available[i] = k means there are k instances of resource type ri
    std::vector<int> available(3);
    for(int i = 0; i < m; i++){
        file >> available[i];
    }

    //close file
    file.close();

    bool res = isSafe(n,m,available,max,allocation);
    if(res == true){
        std::cout << "system is safe" << std::endl;
    } else {
        std::cout << "system isn't safe" << std::endl;
    }

    return 0;
}