#include "stdlib.h"
using namespace std;

#include <stdio.h>

int MAX_SAMPLE = 2000;
int decom = 3;

double n;
double sum;
float current_sample;
double array[2000];
int flag;
int index = 0;
int init_count = 0;
double data;

/////////////////////////////////////////////////
void initialize() {
	flag = 0;
	init_count = 0;
	index = 0;
	sum = 0.0;
}

	double dRessult = 0;
	dResult = *(double*)p_pClient;

	data = d_dY2;
	n = p_dY3;

	initialize();
		if (init_count < n) {
			array[index] = data;
			sum = sum + data;
			if (index == (n - 1)) {
				index = 0;
			}
			else {
				index++;
				init_count++;
			}
		}
		else {
			current_sample = data;
			sum = sum - array[index] + data;
			array[index] = current_sample;
			if (index == (n - 1)) {
				index = 0;
			}
			else {
				index++;
				dResult = (current_sample - (sum / n));
			}
		}

		return dResult;
			}
	}