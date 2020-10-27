#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include "ImageGraph.h"

using namespace std;


ImageGraph::ImageGraph(vector<float> center, vector<vector<float>> points){
    this->center = center;
    this->cartesian_points = points;
    vector<vector<float>> temp (points.size());
    this->polar_points = temp;
    this->update_polar();
}

void ImageGraph::update_polar(){
    vector<vector<float>> v = cartesian_points;

    for (int i = 0; i < v.size(); i++){
        vector<float> point = v.at(i);
        
        float r = pow(pow(point.at(0), 2) + pow(point.at(0), 2) , 0.5);
        float theta = atan(point.at(1)/point.at(0));
        
        vector<float> new_coordinates = {r, theta};
        
        polar_points[i] = new_coordinates;
    }
}

void ImageGraph::update_cartesian(){
    vector<vector<float>> v = polar_points;

    for (int i = 0; i < v.size(); i++){
        vector<float> point = v.at(i);
        
        float x = point.at(0)*cos(point.at(1));
        float y = point.at(0)*sin(point.at(1));
        
        vector<float> new_coordinates = {x,y};
        
        cartesian_points[i] = new_coordinates;
    }
}

void ImageGraph::dilate(float factor){
    for (int i = 0; i < this->polar_points.size(); i++){
        this->polar_points[i][0] *= factor;
    }

    update_cartesian();
}

/*
Checkpoint: Oct 27 2:10pm

Perform vector addition of the converted cartesian points to our new center for below function

Must complete accessors and sting function
*/
ImageGraph::ImageGraph ImageGraph::place_on_map(float factor, vector <float> location){
    center = location;
    dilate(factor);

    return *this;
}