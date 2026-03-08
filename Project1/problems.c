#include <stdio.h>

/*
//1
int main() {
	int i, j, k; //total, each, space

	printf("How many steps do you want your triangles to be? : \n");
	scanf("%d", &i);

	for (j = 0; j <= i; j++) {
		for (k = 0; k < i - j; k++) {
			printf(" ");
		}
		for (k = 0; k < 2 * j - 1; k++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
	}
*/
//2
/*
int main() {
	int i, j, k; //total, eachline, space

	for (;;) {
		printf("How many steps do you want your triangles to be? : \n");
		scanf("%d", &i);
		
			for (j = 0; j <= i; j++) {
				for (k = 0; k < j; k++) {
					printf(" ");
				}
				for (k = 2 * (i - j) - 1; k > 0; k -= 1) {
					printf("*");
				}
				printf("\n");
		}
	}

	return 0;
}
*/

/*
//3
int main() {
	int i, sum = 0;

	for (i = 0; i <= 1000; i++) {
		if ((i % 3 == 0) || (i % 5 == 0)) {
			sum = sum + i;
		}
	}
	printf("The sum of numbers from 1 to 1000 that are multiples of 3 or 5 is %d\n", sum);

	return 0;
}
*/

/*
//4
int main() {
	int i = 1, j = 1, sum = 0;

	while (i < 1000000 && j < 1000000) {
		i = i + j;
		j = j + i;
		
		if (i % 2 == 0) {
			sum += i;
		}
		if (j % 2 == 0) {
			sum += j;
		}
	}

	printf("The sum of the Fibonacci numbers less than 1 million is %d\n", sum);

	return 0;
}
*/

/*
//5
int main() {
	int i, j, mul = 1;

	printf("Type any number : ");
	scanf("%d", &i);

	for (j = 1; j <= i; j++) {
		mul = mul * j;
	}
	printf("The multiplication of the number from 1 to %d is %d.\n", i, mul);

	return 0;
}
*/

/*
//6
int main() {
	int a, b, d = 0;

	for (a = 1; a < 2000; a++) {
		for (b =  1 ; b < 2000; b++) {
			if ( a < b && b < 2000 - a - b) {
				d++;
			}
			else {
				continue;
			}
		}
	}
	printf("The total possible combination of a,b,c is %d.\n", d);
	return 0;
}
*/

//7 Factorise number N
int main() {
	int i, j;

	printf("Type any number : ");
	scanf("%d", &i);

	for (j = 2; j < i; j++) {
		do {
			printf("%d *", j);
		}
		while (i % j == 0) {
			printf("*%d", j);
		}
	}
}