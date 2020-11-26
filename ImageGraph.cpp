#include <sstream>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include "ImageGraph.h"

using namespace std;

#define LATKM 110.567
#define LONGCOEFF 111.320
#define R_EARTH 6378.1370000

/*
#include <iostream>
void print(vector<vector<float>> vec){
    for (int i = 0; i < vec.size(); i++){
        cout << "[";
        for (int j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << ",";
        }
        cout << "]";
    }
}
*/

ImageGraph::ImageGraph(vector<vector<float>> pts){
    cartesian_points = pts;
    n = cartesian_points.size();
    recenter();
    polar_points = to_polar(cartesian_points);
    max_r = 0;
    for (auto point : polar_points){max_r = max(point[0], max_r);}
}

void ImageGraph::recenter(){
    float x_sum = 0;
    float y_sum = 0;

    for (auto point : cartesian_points){
        x_sum += point[0];
        y_sum += point[1];
    }

    //compute centroid of image
    const float centroid_x = x_sum/n;
    const float centroid_y = y_sum/n;
    
    for (int i=0; i<n; i++){
        cartesian_points[i][0] -= centroid_x; //make x values relative to new origin
        cartesian_points[i][1] -= centroid_y; //make y values relative to new origin
    }
}

vector<vector<float>> ImageGraph::to_polar(vector<vector<float>> cartesian){
    vector<vector<float>> polar(cartesian.size(), vector<float>(2,0));
    size_t i = 0;
    
    for (auto point : cartesian){
        float r = sqrt(pow(point[0], 2) + pow(point[1], 2));
        float theta = atan2(point[1],point[0]);
        
        polar[i] = {r, theta};
        i++;
    }

    return polar;
}

vector<vector<float>> ImageGraph::to_cartesian(vector<vector<float>> polar){
    vector<vector<float>> cartesian(polar.size(), vector<float>(2,0));
    size_t i = 0;

    for (auto point : polar){
        float x = point[0]*cos(point[1]);
        float y = point[0]*sin(point[1]);
        
        cartesian[i] = {x,y};
        i++;
    }

    return cartesian;
}

void ImageGraph::set_radius(float r){
    float factor = r/max_r;

    for (int i = 0; i < n; i++){
        polar_points[i][0] *= factor;
    }

    cartesian_points = to_cartesian(polar_points);
}

void ImageGraph::place_on_map(vector<double> loc, float radius){
    location = loc;
    vector<vector<double>> gps(n, vector<double>(2,0));

    for (int i = 0; i<n; i++) {
        double lat_calc = location[0] + cartesian_points[i][1]/LATKM;
        double long_calc = location[1] + cartesian_points[i][0]/(LONGCOEFF*cos(lat_calc*M_PI/180.0));

        gps[i] = {lat_calc, long_calc};
    }

    gps_points = gps;
}

string ImageGraph::path(){
    stringstream s;
    s << fixed << setprecision(6);

    for (auto point : gps_points){
        s << point[0] << "," << point[1] << "|";
    }

    return s.str();
}

vector<vector<float>> ImageGraph::get_cartesian(){
    return cartesian_points;
}

vector<vector<float>> ImageGraph::get_polar(){
    return polar_points;
}

vector<vector<double>> ImageGraph::get_gps(){
    return gps_points;
}