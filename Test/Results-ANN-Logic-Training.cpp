#include <iostream>
#include "Network/ANN/ANN.h"
#include "Eigen/Core"
#include "Network/ANN/activation_functions.h"
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

int main() 
{
    ANN n = ANN();
    n.setInputSize(2);
    n.addLayer(3, "tanh");
    n.addLayer(3, "tanh");
    n.addLayer(1, "tanh");

    Eigen::MatrixXd X = Eigen::MatrixXd(4, 2);
    Eigen::MatrixXd y = Eigen::MatrixXd(4, 1);
    
    double learning_rate = 0.1;

    vector<vector<double>> xor_dataset = {{0,0},{0,1},{1,0},{1,1}};
    vector<double> xor_labels = {-1, 1, 1, -1};

    vector<vector<double>> and_dataset = {{0,0},{0,1},{1,0},{1,1}};
    vector<double> and_labels = {-1, -1, -1, 1};

    vector<vector<double>> or_dataset = {{0,0},{0,1},{1,0},{1,1}};
    vector<double> or_labels = {-1, 1, 1, 1};
    
    for(int j = 0; j < 4; j++) {
        X(j,0) = or_dataset[j][0];
        X(j,1) = or_dataset[j][1];
        y(j,0) = or_labels[j];
    }

    for(int i = 0; i < 2000; i++) {
        n.setLearningRate(learning_rate);
        n.fit(X, y);
        if(i % 10 == 0) {
            Eigen::MatrixXd se = (y - n.predict(X)).array().pow(2);
            cout << i << "," << se.mean() << endl;
        }
    }
    
    return 0;
}