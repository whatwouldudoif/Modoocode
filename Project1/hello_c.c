#include <stdio.h>
/*
int main() {
	printf("Hello, World!\n");
	return 0;
}
*/
/* 
"""와 같이 multiple-lines에 주석
*/
// 한 문장에만 주석을 단다.
int main() {
	float b = 3.141582f; // floating의 경우 끝에 f를 삽입하여 소수점 자리 표시를 명시
	double c = 3.141592; // 없을 시 자동으로 double로 인식
	printf("b : %f \n", b); //float
	printf("c : %f \n", c);

	//main2();
	return 0;
}
/* printf 형식 */
/*
int main2() {
	float a = 3.1412941f;  //실수로 선언하면 %d로 출력해도 X.
	double b = 3.14214324; //얘도 마찬가지. 정수로 보지 않음.
	int c = 123;
	printf("a : %.2f \n", a); //소수점 둘째자리까지 시현 (3.14)
	printf("c : %5d \n", c); //자릿수를 5자리 시현(  123) 123456의 경우 %5여도 모두 출력
	printf("b : %6.3f \n", b); //위 두개 모두 적용. 전체자리 6자리로 맞추되 소수점 이하는 반드시 3째 자리까지만 표시
	return 0;
}*/