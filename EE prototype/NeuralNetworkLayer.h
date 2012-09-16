#ifndef NEURAL_NETWORK_LAYER
#define NEURAL_NETWORK_LAYER

class NeuralNetworkLayer
{
public:
	int NumberOfNodes;
	int NumberOfChildNodes;
	int NumberOfParentNodes;
	double **Weights;
	double **WeightChanges;
	double *NeuronValues;
	double *DesiredValues;
	double *Errors;
	double *BiasWeights;
	double *BiasValues;
	double LearningRate;

	bool LinearOutput;
	bool HyperbolicOutput;
	bool UseMomentum;
	double MomentumFactor;
	NeuralNetworkLayer *ParentLayer;
	NeuralNetworkLayer *ChildLayer;

	NeuralNetworkLayer();

	void Initialize( int NumNodes, NeuralNetworkLayer *parent, NeuralNetworkLayer *child);
	void CleanUp();
	void RandomizeWeights();
	void CalculatedErrors();
	void AdjustWeights();
	void CalculateNeuronValues();
};

#endif //NEURAL_NETWORK_LAYER