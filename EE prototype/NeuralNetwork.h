#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

#include "NeuralNetworkLayer.h"
#pragma warning(disable:4996)

class NeuralNetwork
{
public:
	NeuralNetworkLayer InputLayer;
	NeuralNetworkLayer HiddenLayer;
	NeuralNetworkLayer OutputLayer;

	void Initialize( int nNodesInput, int nNodesHidden, int nNodesOutput );
	void CleanUp();
	void SetInput( int i, double value );
	double GetOutput( int i );
	void SetDesiredOutput( int i, double value );
	void FeedForward();
	void BackPropagate();
	int GetMaxOutputID();
	double CalculateError();
	void SetLearningRate( double rate );
	void SetLinearOutput( bool useLinear);
	void SetHyperbolicOutput( bool useHyperbolic );
	void SetMomentum( bool useMomentum, double factor );
	void DumpData( char *filename );
};

#endif //NEURAL_NETWORK