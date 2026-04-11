#include <stdio.h>

/*
int main() {
	int i;
	printf("Type any number! :");
	scanf("%d", &i);

	if (i != 7) {
		printf("Type another number than than %d.\n", i);
	}

	else {
		printf("You got it right! Today is your lucky day!\n");

		return 0;
	}
}
*/
/*
int main() {
	double i, j;
	printf("Type any two integers you would like to divide: ");
	scanf("%lf, %lf", &i, &j);

	printf("The result of %f divided by %f is: %f", i, j, i / j);
	return 0;
}
*/
//만약 위 함수에 1, 0을 입력하면 inf라는 에러를 내뿜고 종료한다.
//이는 프로그램을 종료시킬 수도 있는 굉장히 큰 문제다.
//따라서, 우리는 if문을 이용하여 0으로 나누는 경우를 방지하여야 한다.
/*
int main() {
	double i, j;
	printf("Type any two integers you would like to divide: ");
	scanf("%lf, %lf", &i, &j);
	if (j == 0) {
		printf("You cannot divide by zero! Please enter another integer.");
	} else {
		printf("The result of %f divided by %f is : %f.", i, j, i / j);
	}
	return 0;
}
*/
/*
int main() {
	int num;

	printf("Type any integer : ");
	scanf("%d%", &num);

	if (num == 7) {
		printf("Lucky number 7! Wish you all the best!");
	}
	else if (num == 13) {
		printf("Is it Friday the 13th? Be careful!");
	}
	else {
		printf("You typed %d. Normal day as usual, but best of luck!", num);
	}
	return 0;
}
*/

//Logical AND(&&)
/*
int main() {
	int a;
	printf("Type any integer : ");
	scanf("%d", &a);

	if (a >= 10 && a < 20) {
		printf("%d is between 10 and 20.", a);
	}
	return 0;
}
*/

//다 아는 내용이다. 다만 파이썬과 다르게 c에서는 else if, and, or, not 대신 &&, ||, !를 사용한다는 점이 다르다.
// & 은 비트 연산자(비트 사이의 1 AND(&) 1, 1 & 0 연산, &&은 논리 연산자(True/False)이다.
// 어차피 &연산 시에 1 AND 1만 1을 출력한다면 &을 사용하지 않는 이유는 무엇일까?
// if (height >= 180 && weight >= 90) 이란 조건이 있다
// 만약 height가 179 이면 뒤 weight는 계산할 필요가 없다.
// 이렇듯 앞 조건이 False 일때 뒤 조건을 확인하지 않아 쓸데없는 연산을 줄여주는 방식을 Short Circuit Evaluation(SCE)라고 부른다.
// &은 모든 조건을 계산하여 정확한 연산결과를 제공하기 때문에 SCE를 사용할 수 없다.

//Local OR(||)

int main() {
	int a;
	printf("Type any integer : ");
	scanf("%d", &a);
	if (a < 10 || a >= 20) {
		printf("%d is less than 10 or greater than or equal to 20.", a);
	}
	return 0;
}

//OR은 두 조건이 모두 거짓일 때만 False(0)를 반환한다.

//NOT(!)
int main() {
	double height, weight;
	printf("Type your height and weight : ");
	scanf("%fl, %fl", &height, &weight);

	if (!(height >= 180 && weight >= 90)) {
		printf("You are not qualified for the basketball team.");
	}
	else {
		printf("Congratulations! You are qualified for the basketball team!");
	}
	return 0;
}

//NOT은 참(1)을 거짓(0)으로, 거짓(0)을 참(1)으로 전환시킨다.
// if (!p) {}
// if (p == 0) {} 과 같은 의미이지만 짧기 때문에 자주 사용된다.