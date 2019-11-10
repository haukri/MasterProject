#include <iostream>
#include "../Network/ANN/ANN.h"
#include "../Eigen/Dense"
#include "../Network/ANN/activation_functions.h"

using namespace std;

int main() 
{
    ANN n = ANN();
    n.setLearningRate(0.1);
    n.setInputSize(2);
    n.addLayer(3, "tanh");
    n.addLayer(3, "tanh");
    n.addLayer(1, "tanh");

    vector<vector<double>> dataset = {{0,0},{0,1},{1,0},{1,1}};
    vector<double> labels = {-1, 1, 1, -1};
    
    Eigen::MatrixXd X = Eigen::MatrixXd(4, 2);
    Eigen::MatrixXd y = Eigen::MatrixXd(4, 1);
    
    for(int j = 0; j < 4; j++) {
        X(j,0) = dataset[j][0];
        X(j,1) = dataset[j][1];
        y(j,0) = labels[j];
    }
    
    for(int i = 0; i < 5000; i++) {
        n.fit(X, y);
        if(i % 10 == 0) {
            Eigen::MatrixXd se = (y - n.predict(X)).array().pow(2);
            cout << se.mean() << endl;
        }
    }
    return 0;
}