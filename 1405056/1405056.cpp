#include <iostream>
#include <fstream>

using namespace std;



ifstream inputFile("in2.txt");

int main() {

    int numProcess, numResources;
    int *availableResources;
    int **currentlyAssigned;
    int **stillNeeded;
    string str;

    int flag = 1;
    if(inputFile.is_open()) {
        inputFile >> str;
        numProcess = stoi(str);
        inputFile >> str;
        numResources = stoi(str);
        availableResources = new int[numResources];
//        cout << "Number of processes: " << numProcess << endl;
//        cout << "Number of resources: " << numResources << endl;
//        cout << "Available resources: ";
        for(int i = 0; i < numResources && inputFile >> str; i++){
            availableResources[i] = stoi(str);
//            cout << availableResources[i] << " ";
        }
//        cout << endl;
//        cout << "Currently assigned resources:" << endl;
        currentlyAssigned = new int*[numProcess];
        for(int i = 0; i < numProcess; i++){
            currentlyAssigned[i] = new int[numResources];
            for(int j = 0; j < numResources && inputFile >> str; j++){
                currentlyAssigned[i][j] = stoi(str);
//                cout << currentlyAssigned[i][j] << " ";
            }
//            cout << endl;
        }
//        cout << "Resources still needed:" << endl;
        stillNeeded = new int*[numProcess];
        for(int i = 0; i < numProcess; i++){
            stillNeeded[i] = new int[numResources];
            for(int j = 0; j < numResources && inputFile >> str; j++){
                stillNeeded[i][j] = stoi(str);
//                cout << stillNeeded[i][j] << " ";
            }
//            cout << endl;
        }
    }
    else{
        cout << "Unable to open file" << endl;
        return 0;
    }
    bool *isFinished = new bool[numProcess];
    //true means process finished, false means process not finished yet
    for(int i = 0; i < numProcess; i++){
        isFinished[i] = false;
    }
    while(flag){
        flag = 0;
        for(int i = 0; i < numProcess; i++){
            int counter = 0;
            for(int j = 0; j < numResources; j++){
                if(!isFinished[i] && stillNeeded[i][j] <= availableResources[j]){
                    counter++;
                    if(counter == numResources){
                        for(int q = 0; q < numResources; q++){
                            availableResources[q] += currentlyAssigned[i][j];
                            isFinished[i] = true;
                            flag = 1;
                        }
                        if(isFinished[i]){
                            i = numProcess;
                        }
                    }
                }
            }
        }
    }

    int counter = 0;
    for(int i = 0; i < numProcess; i++){
        if(isFinished[i]){
            counter++;
        }
    }
    if(counter == numProcess){
        cout << "Safe" << endl;
    }
    else{
        cout << "Unsafe" << endl;
    }
    return 0;
}