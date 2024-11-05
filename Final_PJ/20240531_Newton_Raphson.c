#if 0

#include<stdio.h>

//Newton-Raphson
int int_sqrt(int n) {
    if (n < 0) {
        return -1; // 음수의 제곱근은 없음
    }

    int x = n;
    int y = (x + 1) / 2;

    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }

    return x;
}

#endif

#if 01

#include <stdio.h>

// 제곱근의 근사치를 구하는 함수
int intSqrt(int n, int max_iterations) {
    if (n < 0) {
        return -1; // 음수의 제곱근은 없음
    }

    int x = n;
    int y = (x + 1) / 2;
    int iteration = 0;

    while (iteration < max_iterations && y < x) {
        x = y;
        y = (x + n / x) / 2;
        iteration++;
        printf("Iteration %d: x = %d\n", iteration, x);
    }

    return x;
}

int main() {
    int number, max_iterations;

    // 사용자로부터 정수를 입력받음
    printf("정수를 입력하세요: ");
    scanf("%d", &number);

    // 사용자로부터 최대 반복 횟수를 입력받음
    printf("최대 반복 횟수를 입력하세요: ");
    scanf("%d", &max_iterations);

    // 제곱근의 근사치를 계산
    int result = intSqrt(number, max_iterations);

    if (result == -1) {
        printf("음수의 제곱근은 존재하지 않습니다.\n");
    } else {
        // 결과 출력
        printf("%d의 제곱근의 근사치는 %d입니다.\n", number, result);
    }

    return 0;
}

#endif

#if 0
정수를 입력하세요: 32000000
최대 반복 횟수를 입력하세요: 30
Iteration 1: x = 16000000
Iteration 2: x = 8000001
Iteration 3: x = 4000002
Iteration 4: x = 2000004
Iteration 5: x = 1000009
Iteration 6: x = 500020
Iteration 7: x = 250041
Iteration 8: x = 125084
Iteration 9: x = 62669
Iteration 10: x = 31589
Iteration 11: x = 16301
Iteration 12: x = 9132
Iteration 13: x = 6318
Iteration 14: x = 5691
Iteration 15: x = 5656
#endif

#if 0
정수를 입력하세요: 64000000000000
최대 반복 횟수를 입력하세요: 50
Iteration 1: x = 346161152
Iteration 2: x = 173080577
Iteration 3: x = 86540290
Iteration 4: x = 43270148
Iteration 5: x = 21635081
Iteration 6: x = 10817556
Iteration 7: x = 5408809
Iteration 8: x = 2704468
Iteration 9: x = 1352361
Iteration 10: x = 676436
Iteration 11: x = 338729
Iteration 12: x = 170386
Iteration 13: x = 87224
Iteration 14: x = 47580
Iteration 15: x = 31065
Iteration 16: x = 26675
Iteration 17: x = 26314
Iteration 18: x = 26312
#endif