#pragma once
class SeededRandom {
public:
	double NextDouble();
	float get_Value();
	float NextNormal();
	int Next();
	int NormalRange(int min, int max);
	float NormalRange_Float(float min, float max);
	int Range(int min, int max);
	float Range_Float(float min, float max);
	void ReportUseCount();
	void SetSeed(unsigned int seed);
	void SetSeed_Long(long long seed);
	void ctor(long long seed);
	void ctor_Int(int seed);
	int sign();

	long long initialSeed;
	long long currentSeed;
	int useCount;
	bool reportUsecountFlag; //why is it named like this...
};

