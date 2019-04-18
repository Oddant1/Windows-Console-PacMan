#include "stdafx.h"

using namespace std;

/*string IntToChar(int nConvert)
{
	int nDigit = 10; // Variable for counting which digit place we are in
	char *cScore;	 // Result of conversion

	// Determine number of digits
	while (nDigit < nConvert)
	{
		if ((nDigit * 10) > nConvert)
		{
			break;
		}

		nDigit *= 10;
		nLength++;
	}
	
	// Set length of string and first variable
	cScore = new char[nLength];
	cScore[0] = nConvert / nDigit;

	for (int i = 1; i < nLength; i++)
	{
		int j = nConvert % nDigit;

		i < nLength - 1 ? cScore[i] = j / (nDigit / 10) : cScore[i] = j;
	}

	return cScore;
}*/