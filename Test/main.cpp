#include <iostream>
#include "../Network/ANN/ANN.h"
#include "../Eigen/Dense"
#include "../Network/ANN/activation_functions.h"

using namespace std;

int main() 
{
    ANN n = ANN();
    n.setInputSize(2);
    n.addLayer(2, "tanh");
    n.addLayer(2, "tanh");
    Eigen::MatrixXd input = Eigen::MatrixXd(1, 2);
    for(int i = 0; i < 2; i++) {
        input(0, i) = 2;
    }
    cout << "Prediction" << endl;
    cout << n.predict(input) << endl;
    return 0;
}