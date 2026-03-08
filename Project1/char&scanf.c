#include <stdio.h>

/*
int main() {
	char a;
	a = 'a';

	printf("a의 값은 %d이고 이 값은 %c입니다.\n", a, a); //%d 는 정수형으로 출력, %c는 문자형으로 출력
	return 0;
}
*/
//ASCII 코드 표에서 'a'는 97입니다. 따라서 a의 값은 97이고 이 값은 a입니다. 0~~127까지의 숫자는 각각 대응하는 문자가 있다.
//여기서 1비트를 추가하여 0~255까지의 Extended ASCII 코드가 만들어졌습니다.
//Unicode는 ASCII표를 유지하면서 전세계 문자들을 표현하기 위해 만들어진 문자 인코딩 시스템입니다.

// 섭씨를 화씨로 변환하기


int main() {
	double celsius;

	printf("섭씨를 화씨로 변환하는 프로그램입니다.\n");
	printf("섭씨 온도를 입력하세요 : ");
	scanf("%lf", &celsius); //%lf는 double형으로 입력받는다는 의미입니다.
	//scanf 함수는 입력된 값을 변수에 저장하기 위해 변수의 주소를 필요로 합니다. 따라서 &celsius를 사용하여 celsius 변수의 주소를 전달합니다.

	//scanf의 경우 double은 %lf, float는 %f로 입력받습니다. printf에서는 double과 float 모두 %f로 출력할 수 있습니다.

	printf("섭씨 %f도는 화씨 %f도 입니다.\n", celsius, 9 * celsius / 5 + 32);
	printf("섭씨  %f도는 화씨 %f도 입니다.\n", celsius, 9 / 5 * celsius + 32);
	// 위 두 출력값은 다른 결과를 출력한다.
	// 9 * celsius / 5 + 32는 산술 변환에 의한 double 연산(더 큰 단위의 연산으로 자동 변환)이 적용되어 올바른 결과 출력한다
	// 반면에 9 / 5 * celsius + 32는 int의 계산으로 9 / 5가 1로 계산되어 잘못된 결과를 출력합니다.
	// 따라서 항상 나눗셈을 할 때는 피연산자 중 하나를 실수형(9.0)으로 만들어야 합니다.
	return 0;
}


/*
int main() {
	char ch; //문자, 1byte, 한글은 2바이트 이상 차지하기 때문에 오류.
			//변수형의 메모리를 초과하는 데이터를 집어넣을 경우 발생하는 오류를 버퍼 오버플로우 라고 하며,
			//이를 이용하여 공격자들이 자신들이 원하는 코드를 실행하게 할 수 있으므로 보안상 취약하다.
			//+ 근처 데이터를 손상시켜 문제를 일으킬 수 있으므로 항상 버퍼 오버플로우를 주의하자.

	short sh; //정수
	int i;
	long lo;

	float fl; //실수
	double du;

	printf("char 형 변수 입력: ");
	scanf("%c", &ch);

	printf("short 형 변수 입력: ");
	scanf("%hd", &sh);
	printf("int 형 변수 입력: ");
	scanf("%d", &i);
	printf("long 형 변수 입력: ");
	scanf("%ld", &lo);

	printf("float 형 변수 입력: ");
	scanf("%f", &fl);
	printf("double 형 변수 입력: ");
	scanf("%lf", &du);

	printf("char : %c, short : %hd, int : %d", ch, sh, i);
	printf("long : %ld, float: %f, double: %fl", lo, fl, du);
	return 0;
}
*/