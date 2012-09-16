#ifndef RANDOM_H
#define RANDOM_H

int random( int smallest, int largest )
{
	rand();
	rand();
	return (double)smallest + int(((((double)largest - (double)smallest) + 1.0) * (double)rand()) / ((double)RAND_MAX + 1.0));
}

#endif