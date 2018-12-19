#include <node.h>
#include "src/GenerticAlgorithm.h"

using namespace v8;

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

GA ga;

void RunGA(const FunctionCallbackInfo<Value>& args){
    ga.getShortestPath();
}

void InitMember(const FunctionCallbackInfo<Value>& args){
    initDistance();
    RunGA(args);
}

void GetBestPath(const FunctionCallbackInfo<Value>& args){
    Path bestResult = ga.getShortestPath();
    bestResult.calculateLength();
    string result = "";
    for(int i=0; i<CITY_NUMBER; i++){
        result += to_string(bestResult.path[i]);
        result += " ";
    }
    result += to_string((int)bestResult.length);
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void init(Local<Object> exports){
    NODE_SET_METHOD(exports, "getBestPath", GetBestPath);
    NODE_SET_METHOD(exports, "init", InitMember);
    NODE_SET_METHOD(exports, "run", RunGA);
}

NODE_MODULE(GA, init)