#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class ImageGraph {
    private:
        vector<float> center;
        vector<vector<float>> cartesian_points;
        vector<vector<float>> polar_points;
        vector<vector<float>> gps_points;

        void update_polar();
        void update_cartesian();
        void dilate(float);

    public:
        ImageGraph(vector <float>, vector<vector<float>>);
        //array of x,y coordinates

        ImageGraph place_on_map(float, vector <float>);

        vector<vector<float>> get_polar();
        vector<vector<float>> get_gps();

        string get_path();
};
