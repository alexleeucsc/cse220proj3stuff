#include <MiniDNN.h>

using namespace MiniDNN;

typedef Eigen::MatrixXd Matrix;
typedef Eigen::VectorXd Vector;

int main()
{
    // Set random seed and generate some data
    std::srand(123);
    // Predictors -- each column is an observation
    int matrixSize = 1600;
    Matrix x = Matrix::Random(matrixSize, 100);
    // Response variables -- each column is an observation
    Matrix y = Matrix::Random(2, 100);

    // Construct a network object
    Network net;


    Layer* layer1 = new FullyConnected<Identity>(matrixSize,matrixSize);
    Layer* layer2 = new FullyConnected<Identity>(matrixSize,matrixSize);
    Layer* layer3 = new FullyConnected<Identity>(matrixSize,matrixSize);
    Layer* layer4 = new FullyConnected<Identity>(matrixSize,matrixSize);
    Layer* layer5 = new FullyConnected<Identity>(matrixSize,2);

    // Add layers to the network object
    net.add_layer(layer1);
    net.add_layer(layer2);
    net.add_layer(layer3);
    net.add_layer(layer4);
    net.add_layer(layer5);

    // Set output layer
    net.set_output(new RegressionMSE());

    // Create optimizer object
    RMSProp opt;
    opt.m_lrate = 0.001;

    // (Optional) set callback function object
    VerboseCallback callback;
    net.set_callback(callback);

    // Initialize parameters with N(0, 0.01^2) using random seed 123
    net.init(0, 0.01, 123);

    // Fit the model with a batch size of 100, running 10 epochs with random seed 123
    net.fit(opt, x, y, 100, 10, 123);

    // Obtain prediction -- each column is an observation
    Matrix pred = net.predict(x);

    // Layer objects will be freed by the network object,
    // so do not manually delete them

    return 0;
}
