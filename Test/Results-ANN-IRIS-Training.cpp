#include <iostream>
#include "Network/ANN/ANN.h"
#include "Eigen/Core"
#include "Network/ANN/activation_functions.h"
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

int matrixMax(Eigen::MatrixXd input) {
    int maxIndex = 0;
    for(int i = 0; i < 3; i++) {
        if(input(0, i) > input(0, maxIndex)) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

double comparePrediction(Eigen::MatrixXd prediction, Eigen::MatrixXd label) {
    int correctPredictions = 0;
    int wrongPredictions = 0;
    for(int i = 0; i < prediction.rows(); i++) {
        if(matrixMax(prediction.block<1,3>(i,0)) == matrixMax(label.block<1,3>(i,0))) {
            correctPredictions++;
        }
        else {
            wrongPredictions++;
        }
    }
    return (double)correctPredictions / prediction.rows();
}

int main() 
{
    ANN n = ANN();
    n.setInputSize(4);
    n.addLayer(50, "tanh");
    n.addLayer(50, "tanh");
    n.addLayer(3, "sigmoid");

    ifstream file("/home/haukur/MasterProject/Plotting/iris.csv");
    string delimiter = ",";

    Eigen::MatrixXd X = Eigen::MatrixXd::Zero(150, 4);
    Eigen::MatrixXd y = Eigen::MatrixXd::Zero(150, 3);

    if(file.is_open()) {
        string line;
        int line_index = 0;
        while(getline(file, line)) {
            size_t pos = 0;
            int token;
            int index = -1;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = stod(line.substr(0, pos));
                if(index == -1) {
                    y(line_index, token) = 1;
                }
                else {
                    X(line_index, index) = stod(line.substr(0, 1)) + stod(line.substr(2, 1))/10;
                }
                line.erase(0, pos + delimiter.length());
                index++;
            }
            line_index++;
        }
    }

    int batch_size = 20;

    Eigen::MatrixXd batch_X = Eigen::MatrixXd::Zero(batch_size, 4);
    Eigen::MatrixXd batch_y = Eigen::MatrixXd::Zero(batch_size, 3);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,119);
    
    double learning_rate = 0.1;

    Eigen::MatrixXd validate_X = X.block<30,4>(120,0);
    Eigen::MatrixXd validate_y = y.block<30,3>(120,0);

    for(int i = 0; i < 1000; i++) {
        for(int i = 0; i < batch_size; i++) {
            int pick = distribution(generator);
            batch_X.block<1,4>(i, 0) = X.block<1,4>(pick, 0);
            batch_y.block<1,3>(i,0) = y.block<1,3>(pick, 0);
        }
        n.setLearningRate(learning_rate);
        n.fit(batch_X, batch_y);
        if(i % 1 == 0) {
            Eigen::MatrixXd prediction = n.predict(validate_X);
            Eigen::MatrixXd accuracy = n.predict(batch_X);
            cout << i << "," << comparePrediction(accuracy, batch_y) << "," << comparePrediction(prediction, validate_y) << endl;
            // Eigen::MatrixXd se = (y - n.predict(X)).array().pow(2);
            // cout << "Epoch: " << i << " MSE: " << se.mean() << " learning rate: " << learning_rate << endl;
        }
        if(learning_rate > 0.01)
            learning_rate *= 0.99;
    }
    
    return 0;
}