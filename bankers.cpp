#include <iostream>
#include <vector>



int main(){
    //number of processes
    int n;
    //number of resource types
    int m;
    //available
    //1-d array of size m indicating number of available resources of each type
    std::vector<int> available(m);
    //max
    //2-d array of size n*m that defines maximum demand of each process in a system
    std::vector<std::vector<int>> max(n, std::vector<int>(m,0));
    //allocation
    //2-d size array of size n*m that defines the number of resources of each type currently allocated to each processs
    std::vector<std::vector<int>> allocation(n, std::vector<int>(m,0));

}