#include <stdio.h>
/*
int main() {
	int i;
	for (i = 0; i < 20; i++) {
		printf("Number : %d \n", i);
	}

		return 0;
	}
*/

// for 문의 기본 구조는 아래와 같습니다
// for (초기식 ; 조건식; 증감식) {
//     명령1;
//     명령2;
//     ...
// }
/*
초기식에서 제어변수가 초기화 됨.
뭔말? 제어변수(위 예시에선 i)를 통해 반복문을 얼마나 반복할 것인가를 결정함.
그리고 이 제어변수는 특정 조건을 만족할 때에만 반복을 계속함.
제어변수의 초기값은 for문의 '초기식' 부분에서 지정됨.

조건식은 제어변수 i가 만족해야 될 특정 조건.
해당 조건이 참(1)일때만 실행

증감식은 1회 실행시 i값을 어떻게 만들어야 됨?
위 예시에선 i++ 이므로 값이 1씩 증가됨.

만약 i-=2 라고 하면 2씩 감소됨.
*/

/*
int main() {
	int i, sum = 0;
	for (i = 0; i <= 10000; ++i) {
		sum = sum + i;
	}
	printf("sum from 1 to 19 : %d \n", sum);

	return 0;
}
*/
/*
int main() {
	int i;
	int subject, score;
	double sum_score = 0;

	printf("How many subjects have you taken?");
	scanf("%d", &subject);

	printf("\n Enter grade for each subject \n");
	for (i = 1; i <= subject; i++) {
		printf("Subject %d : ", i);
		scanf("%d", &score);
		sum_score = sum_score + score;
	}

	printf("You average score is : %.2f \n", sum_score / subject);

	return 0;
}
*/

// 위의 코드도 해석하기에 어렵지 않을 것이다.
// 총 몇 과목을 수강했는지 입력받고, 해당 과목들의 점수를 입력하여 총합을 구하고 평균을 낸다

/*
int main() {
	int usranswer;

	printf("Guess the number? \n");

	for (;;) { //for (;;)는 항상 참이란 뜻이다. 즉 무한 루프이다.
		scanf("%d", &usranswer);
		if (usranswer == 3) {
			printf("Correct! \n");
			break;
		}
		else {
			printf("Wrong \n");
		}
	}
	return 0;
}
*/

/*
int main() {
	int j;

	for (j = 0; j < 100; j++) {
		if (j % 5 == 0) continue; // continue는 for 문을 빠져나가지 않고 아무 기능도 실행하지 않고 다음으로 넘어간다.

		printf("%d\n", j);
	}
	return 0;
}
*/
/*
int main() {
	int i, j;

	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) { // for문 안에 for문을 또 넣어 사용할 수 있다.
			printf("%d x %d = %d\n", i, j, i * j);

		}
	}
	return 0;
}
*/

/*
//기본적인 while 문
int main() {
	int i = 1, sum = 0;

	while (i <= 100) { // for 문과 단순하게 비슷하다
		sum += i;
		i++;
	}

	printf("Sum from 1 to 100 : %d \n", sum);
	return 0;
}
*/

/*
while (조건식) {
	명령1;
	명령2;
	...
}
*/

//do-while 문

/*
int main() {
	int i = 1, sum = 0;

	do {
		sum += i;
		i++;
	} while (i <= 100);

	printf("Sum from 1 to 100 using do-while: %d\n", sum);

	return 0;
}
*/
//while과 거의 같지만 while 문은 조건을 먼저 검사하는 반면, do-while 문은 명령을 먼저 실행한 후 조건을 검사한다.
//따라서 do-while 문은 최소 한 번은 명령이 실행된다