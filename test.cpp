#include <stdlib.h>
#include <vector>
#include <string>
#include "ImageGraph.h"

using namespace std;

string test() {

    int n = 4;
    vector<vector<float>> pic { {-1,-1}, {-1,1}, {1,1}, {1,-1} };
    vector<float> center = {0,0};

    ImageGraph::ImageGraph picture(center, pic); //initialization of object


    vector<float> toronto = {43.6532, 79.3832}; //in lat long
    float r = 1; //in km
    ImageGraph::ImageGraph mapped = picture.place_on_map(r, toronto);

    return mapped.get_path();
}