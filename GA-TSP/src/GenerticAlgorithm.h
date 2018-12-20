/*
* GenerticAlgorithm -- Solving TSP
*/
#ifndef GENERTIC_ALGORITHM_H
#define GENERTIC_ALGORITHM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>

#define VARIA_PRO 0.5
#define CROSS_PRO 0.8
#define CITY_NUMBER 130
#define GROUP_SIZE 500
#define ITER_TIME 50

using namespace std;

// Global distance array storing distances between two citise
extern double distanceTable[CITY_NUMBER][CITY_NUMBER];

struct linearGen{
	int seed;
	linearGen(int seed_ = -1){
		seed = seed_;
	}
	int operator() (){
		return seed += 1;
	}
};

struct Node{
	double x, y;
	int num;
};

struct Path{
	// Path's basic infos
	double length;
	int path[CITY_NUMBER];
	// Path's behavior methods
	Path(){
		length = 0;
		// Initial random generation
		generate(path, path + CITY_NUMBER, linearGen(0));
		random_shuffle(path, path + CITY_NUMBER);  // Randomly shuffle
		// Calculate init length
		calculateLength();
	}

	void initDistance(){
	    vector<Node> cityNodes;

	    ifstream in("src/cities.txt");
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

	// Calculating path's length
	void calculateLength(){
		length = 0;
		// Interation on path
		if(distanceTable[0][0] == 0.0){
			initDistance();
		}
		for(int i=1; i<CITY_NUMBER; i++){
			length += distanceTable[path[i-1] - 1][path[i]-1];
		}
		// Don't forget to add first and last city's distance
		length += distanceTable[path[CITY_NUMBER-1] - 1][path[0] - 1];
	}

	// Single Point CrossOver behavior
	void singlePointCross(Path& oth){
		int randomMark = rand() % (CITY_NUMBER - 2) + 1;
		// Swapping with another population
		for(int i=randomMark; i<CITY_NUMBER; i++){
			int temp = path[i];
			path[i] = oth.path[i];
			oth.path[i] = temp;
		}
		// Establish two population's corss state array
		int index = 0, oth_index = 0;
		bool crossFlag[CITY_NUMBER + 1] = { false };
		bool oth_crossFlag[CITY_NUMBER + 1] = { false };
		// Start two path's single point cross
		while(index < CITY_NUMBER && oth_index < CITY_NUMBER){
			if(crossFlag[path[index]] && oth_crossFlag[oth.path[oth_index]]){
				int temp = path[index];
				path[index] = oth.path[oth_index];
				oth.path[oth_index] = temp;
				++index;
				++oth_index;
			}
			// Judge whether reach depth
			if(index >= CITY_NUMBER || oth_index >= CITY_NUMBER)
				break;
			if(!crossFlag[path[index]]){
				crossFlag[path[index]] = true;
				++index;
			}
			if(!oth_crossFlag[oth.path[oth_index]]){
				oth_crossFlag[oth.path[oth_index]] = true;
				++oth_index;
			}
		}
		calculateLength();
		oth.calculateLength();
	}

	// Variation behavior
	void randomVariation(){
		int a = rand() % CITY_NUMBER, b = rand() % CITY_NUMBER;
		if(a > b){
			swap(a, b);
		}else if(a == b){
			return;
		}
		// Switch random variation type
		int target = rand() % 3;
		switch(target){
			case 0: 
				swap(path[a], path[b]);
				break;
			case 1:
				reverse(path + a, path + b);
				break;
			default:
				if(b < CITY_NUMBER - 1){
					rotate(path + a, path + b, path + b + 1);
				}
		}
		calculateLength();
	}

};

class GA{
public:
	GA();
	Path getShortestPath();
	void clearPath(){
		for(int i=0; i<GROUP_SIZE; i++){
			group[i] = Path();
		}
	}

private:
	// All classified population group
	vector<Path> group;
	Path bestPath;
	// Private inline methods
	inline void choose(vector<Path>& oth);
	inline void cross(vector<Path>& oth);
	inline void varia(vector<Path>& oth);
	inline void holdGoodPath(vector<Path>& old, vector<Path>& gr);
	inline void writePathFile(Path& in);

};

#endif