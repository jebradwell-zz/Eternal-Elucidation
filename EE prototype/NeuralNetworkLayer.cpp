#include "NeuralNetworkLayer.h"
#include <iostream>
#include "time.h"
#include "math.h"

NeuralNetworkLayer::NeuralNetworkLayer()
{
	ParentLayer = NULL;
	ChildLayer = NULL;
	LinearOutput = false;
	HyperbolicOutput = false;
	UseMomentum = false;
	MomentumFactor = 0.9;
}

void NeuralNetworkLayer::Initialize(int NumNodes, 
									NeuralNetworkLayer *parent, 
									NeuralNetworkLayer *child)
{
	int i, j;

	//Allocate memory
	NeuronValues = (double*) malloc(sizeof(double) * NumberOfNodes);
	DesiredValues = (double*) malloc(sizeof(double) * NumberOfNodes);
	Errors = (double*) malloc(sizeof(double) * NumberOfNodes);

	if( parent != NULL )
	{
		ParentLayer = parent;
	}

	if( child != NULL )
	{
		ChildLayer = child;

		Weights = (double**) malloc(sizeof(double*) * NumberOfNodes);
		WeightChanges = (double**) malloc(sizeof(double*) * NumberOfNodes);
		for(i = 0; i < NumberOfNodes; i++)
		{
			Weights[i] = (double*) malloc(sizeof(double) * NumberOfNodes);
			WeightChanges[i] = (double*) malloc(sizeof(double) * NumberOfNodes);
		}

		BiasValues = (double*) malloc(sizeof(double) * NumberOfChildNodes);
		BiasWeights = (double*) malloc(sizeof(double) * NumberOfChildNodes);
	}
	else
	{
		Weights = NULL;
		BiasValues = NULL;
		BiasWeights = NULL;
		WeightChanges = NULL;
	}

	//Make sure everything contains 0s
	for( i = 0; i < NumberOfNodes; i++ )
	{
		NeuronValues[i] = 0;
		DesiredValues[i] = 0;
		Errors[i] = 0;

		if(ChildLayer != NULL )
		{
			for(j = 0; j < NumberOfChildNodes; j++ )
			{
				Weights[i][j] = 0;
				WeightChanges[i][j] = 0;
			}
		}
	}

	//Initialize the bias values and weights
	if( ChildLayer != NULL )
	{
		for( j = 0; j < NumberOfChildNodes; j++ )
		{
			BiasValues[j] = -1;
			BiasWeights[j] = 0;
		}
	}
}

void NeuralNetworkLayer::CleanUp()
{
	int i;

	free(NeuronValues);
	free(DesiredValues);
	free(Errors);

	if(Weights != NULL)
	{
		for( i = 0; i < NumberOfNodes; i++ )
		{
			free(Weights[i]);
			free(WeightChanges[i]);
		}
		free(Weights);
		free(WeightChanges);
	}

	if(BiasValues != NULL )
	{
		free(BiasValues);
	}
	if( BiasWeights != NULL )
	{
		free(BiasWeights);
	}
}

void NeuralNetworkLayer::RandomizeWeights()
{
	int i, j;
	int min = 0;
	int max = 200;
	int number;

	srand( (unsigned)time(NULL) );

	for( i = 0; i < NumberOfNodes; i++ )
	{
		for( j = 0; j < NumberOfChildNodes; j++ )
		{
			number = ( ( ( abs( rand() ) % ( max - min + 1 ) ) + min ) );
			if( number > max )
			{
				number = max;
			}
			if( number < min )
			{
				number = min;
			}
			Weights[i][j] = number / 100.0f - 1;
		}
	}
	
	for( j = 0; j < NumberOfChildNodes; j++ )
	{
		number = ( ( ( abs( rand() ) % ( max - min + 1 ) ) + min ) );

		if( number > max )
		{
			number = max;
		}
		if(number < min )
		{
			number = min;
		}
		BiasWeights[j] = number / 100.0f - 1;
	}
}

void NeuralNetworkLayer::CalculateNeuronValues()
{
	int i, j;
	double x;

	if( ParentLayer != NULL )
	{
		for( j = 0; j < NumberOfNodes; j++ )
		{
			x = 0;
			for( i = 0; i < NumberOfParentNodes; i++ )
			{
				x += ParentLayer->NeuronValues[i] * ParentLayer->Weights[i][j];
			}
			x += ParentLayer->BiasValues[j] * ParentLayer->BiasWeights[j];

			if( ( ChildLayer == NULL ) && LinearOutput ) 
			{
				NeuronValues[j] = x;
			}
			else
			{
				if( HyperbolicOutput )
				{
					NeuronValues[j] = (((exp( x ) - exp( -x )) / (exp( x ) + exp( -x ))) / 2) + 0.5;
				}
				else
				{
					NeuronValues[j] = 1.0f / ( 1 + exp( -x ) );
				}
			}
		}
	}
}

void NeuralNetworkLayer::CalculatedErrors()
{
	int i, j;
	double sum;

	if( ChildLayer == NULL ) //output layer
	{
		for( i = 0; i < NumberOfNodes; i++ )
		{
			Errors[i] = (DesiredValues[i] - NeuronValues[i] ) * 
				NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	}
	else if( ParentLayer == NULL )
	{
		for( i = 0; i < NumberOfNodes; i++ )
		{
			Errors[i] = 0.0f;
		}
	}
	else
	{
		for( i = 0; i < NumberOfNodes; i++ )
		{
			sum = 0;
			for( j = 0; j < NumberOfChildNodes; j++ )
			{
				sum += ChildLayer->Errors[j] * Weights[i][j];
			}
			Errors[i] = sum * NeuronValues[i] * (1.0f - NeuronValues[i] );
		}
	}
}

void NeuralNetworkLayer::AdjustWeights()
{
	int i, j;
	double dw;

	if( ChildLayer != NULL )
	{
		for( i = 0; i < NumberOfNodes; i++ )
		{
			for( j = 0; j < NumberOfChildNodes; j++ )
			{
				dw = LearningRate * ChildLayer->Errors[j] * NeuronValues[i];
				if( UseMomentum )
				{
					Weights[i][j] += dw + MomentumFactor * WeightChanges[i][j];
					WeightChanges[i][j] = dw;
				}
				else
				{
					Weights[i][j] += dw;
				}
			}
		}
		for( j = 0; j < NumberOfChildNodes; j++ )
		{
			BiasWeights[j] += LearningRate * ChildLayer->Errors[j] * BiasValues[j];
		}
	}
}