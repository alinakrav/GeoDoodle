#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "./*GUIDIRECTORIES*"
#include "./image_graph/ImageGraph.h"
#include "./*BACKENDDEVDIRECTORIES*"

using namespace std;

int main () {
    /*
    GUI Invoke

    Obtain image, location, and radius as inputs.

    */


   vector<double> location; //set equal to {43.684921, -79.477013} via GUI
   vector<vector<float>> points; //set equal to one of the templates given by image selection
   float radius; //set to user input

    /*
    ImageGraph Invoke

    Pass parameters to object and obtain string for SnapToRoads

    */
    ImageGraph graph(points);
    graph.place_on_map(location, radius);
    string path = graph.path();

    /*
    API Backend Invoke

    Handle SnapToRoads string and obtain final route.

    */






    /*
    Display link to console
    */
   string link;
   cout << "Link to route is: " << link << endl;


    return 0;
}