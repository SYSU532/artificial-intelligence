#include "GenerticAlgorithm.h"

double distanceTable[CITY_NUMBER][CITY_NUMBER];

GA::GA(){
	for(int i=0; i<GROUP_SIZE; i++){
		this->group.push_back(Path());
	}
}

Path GA::getShortestPath(){
	srand((unsigned)time(NULL));

	Path bestResult;

	for(int i=0; i<ITER_TIME; i++){
		vector<Path> prevGroup = group;
		// Populations choose, cross, variation
		choose(group);
		cross(group);
		for(int j=0; j<5; j++){
			varia(group);
			holdGoodPath(prevGroup, group);
		}
		for(int j=0; j<GROUP_SIZE; j++){
			if(group[j].length < bestResult.length){
				bestResult = group[j];
			}
		}
	}
	writePathFile(bestResult);
	bestResult.calculateLength();
	return bestResult;
}

// Roulette Gambling
void GA::choose(vector<Path>& oth){
	double sum_fitness = 0,  // Choose fitness sum
			pick_pro = 0;  // Gambling Pick random number
	double fitness[GROUP_SIZE];  // Gamble Roulette Fitness
  	double chance[GROUP_SIZE];  // chance probability
  	vector<Path> nextGroup;  // Produce result
  	// Init values
  	for(int i=0; i<GROUP_SIZE; i++){
  		fitness[i] = 1 / oth[i].length;
  		sum_fitness += fitness[i];
  	}
  	for(int i=0; i<GROUP_SIZE; i++){
  		chance[i] = fitness[i] / sum_fitness;
  	}
  	// Gambling
  	for(int i=0; i<GROUP_SIZE; i++){
  		pick_pro = ((double)rand()) / RAND_MAX;
  		for(int j=0; j<GROUP_SIZE; j++){
  			pick_pro -= chance[j];
  			if(pick_pro <= 0){
  				nextGroup.push_back(oth[j]);
  				break;
  			}
  			if(j == GROUP_SIZE - 1){
  				nextGroup.push_back(oth[j]);
  			}
  		}
  	}
  	oth = nextGroup;
}

void GA::cross(vector<Path>& oth){
	int index = 0;
	int choice_1, choice_2;
	while(index < GROUP_SIZE){
		double pick_pro = ((double)rand()) / RAND_MAX;
		if(pick_pro > CROSS_PRO){
			continue;
		}else {
			// Do groups cross over
			choice_1 = index;  choice_2 = index + 1;
			oth[choice_1].singlePointCross(oth[choice_2]);
		}
		index += 2;
	}
}

// Do variation
void GA::varia(vector<Path>& oth){
	int index = 0;
	while(index < GROUP_SIZE){
		double pick_pro = ((double)rand()) / RAND_MAX;
		if(pick_pro < VARIA_PRO){
			oth[index].randomVariation();
		}
		index++;
	}
}

void GA::holdGoodPath(vector<Path>& old, vector<Path>& gr){
	int index = 0;
	while(index < GROUP_SIZE){
		if(old[index].length < gr[index].length){
			gr[index] = old[index];
		}
		index++;
	}
}

void GA::writePathFile(Path& in){
	string path = "Web/static/path.txt";
	ofstream out(path);
	for(int i=0; i<CITY_NUMBER; i++){
		out << in.path[i] << " ";
	}
	out.close();
}