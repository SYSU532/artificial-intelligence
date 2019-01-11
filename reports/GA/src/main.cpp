#include "GenerticAlgorithm.h"

void initDistance();

int main(){
	// Init TSP cities distances
	initDistance();
	// Establish GA-TSP Object, begin solving the problem
	GA ga;


	// Get GA result
	Path bestResult = ga.getShortestPath();

    for(int i=0; i< 130; i++){
        if(i != 129){
            cout << bestResult.path[i] << " -> ";
        }else {
            cout << bestResult.path[i] ;
        }
    }
    cout << endl;
	return 0;
}

void initDistance(){
    vector<Node> cityNodes;

    ifstream in("cities.txt");
    for(int i=0; i<CITY_NUMBER; i++){
        cityNodes.push_back(Node());
        in >> cityNodes[i].num >> cityNodes[i].x >> cityNodes[i].y;
    }
    for(int i=0; i<CITY_NUMBER; i++){
        distanceTable[i][i] = (double)INT_MAX;
        for(int j=i+1; j<CITY_NUMBER; j++){
            double dist = sqrt((cityNodes[i].x - cityNodes[j].x) * (cityNodes[i].x - cityNodes[j].x) + 
                               (cityNodes[i].y - cityNodes[j].y) * (cityNodes[i].y - cityNodes[j].y));
            distanceTable[i][j] = distanceTable[j][i] = dist;
        }
    }
}
