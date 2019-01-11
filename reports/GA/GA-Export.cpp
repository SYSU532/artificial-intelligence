#include <node.h>
#include "src/GenerticAlgorithm.h"

using namespace v8;

GA ga;

void RunGA(const FunctionCallbackInfo<Value>& args){
    ga.getShortestPath();
}

void initGAPath(const FunctionCallbackInfo<Value>& args){
    ga.clearPath();
}

void GetBestPath(const FunctionCallbackInfo<Value>& args){
    Path bestResult = ga.getShortestPath();
    bestResult.calculateLength();
    cout << bestResult.length << endl;
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
    NODE_SET_METHOD(exports, "clear", initGAPath);
    NODE_SET_METHOD(exports, "run", RunGA);
}

NODE_MODULE(GA, init)