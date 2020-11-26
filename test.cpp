#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "ImageGraph.h"

using namespace std;


void test(string tested, string correct) {
    map<bool ,string> outcome = {{true, "PASSED."},{false, "FAILED."}};
    bool state = tested == correct;
    cout << endl << "The following test " << outcome[state] << endl;
    cout << "Output is: " << tested << endl;
    cout << "Output should be: " << correct << endl;
}

int main() {
    vector<double> toronto = {43.684921, -79.477013};

    vector<vector<float>> pic_A {{0,2},{1,0},{3,0},{4,2},{2,3}}; //irregular pentagon
    ImageGraph graph_A(pic_A);
    graph_A.place_on_map(toronto, 6.4);
    test(graph_A.path(), "43.690348,-79.501860|43.672259,-79.489433|43.672259,-79.464593|43.690348,-79.452166|43.699392,-79.477013|");

    vector<vector<float>> pic_B {{1,1},{-1,1},{0,-1}}; //triangle
    ImageGraph graph_B(pic_B);
    graph_B.place_on_map(toronto, 3.24);
    test(graph_B.path(), "43.690951,-79.464590|43.690951,-79.489436|43.672862,-79.477013|");

    vector<vector<float>> pic_C {{0,0},{0,1},{1,1},{1,0}}; //unit square
    ImageGraph graph_C(pic_C);
    graph_C.place_on_map(toronto, 1.6);
    test(graph_C.path(), "43.680399,-79.483224|43.689443,-79.483225|43.689443,-79.470801|43.680399,-79.470802|");

    vector<vector<float>> pic_D {{1,4},{0,2},{1,0},{4,0},{5,2},{4,4}}; //irregular hexagon
    ImageGraph graph_D(pic_D);
    graph_D.place_on_map(toronto, 10.324);
    test(graph_D.path(), "43.703010,-79.495652|43.684921,-79.508069|43.666832,-79.495641|43.666832,-79.458385|43.684921,-79.445957|43.703010,-79.458374|");

    vector<vector<float>> pic_E {{2,0},{0,2},{-2,0},{0,-2}}; //regular rhombus
    ImageGraph graph_E(pic_E);
    graph_E.place_on_map(toronto, 15.4);
    test(graph_E.path(), "43.684921,-79.452169|43.703010,-79.477013|43.684921,-79.501857|43.666832,-79.477013|");

    return 0;
}
