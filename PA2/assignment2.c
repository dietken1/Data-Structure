#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1000  //최대 항

typedef struct node* polyPointer;
typedef struct node {
    int coef;   //계수
    int expon;  //차수
    polyPointer link;   //다음 노드를 가리키는 포인터
} node;

polyPointer header; //헤더 노드
polyPointer avail = NULL;   //가용 공간 리스트 포인터

//노드 생성 함수
polyPointer getNode(void) {
    polyPointer node;
    if (avail) {
        node = avail;
        avail = avail->link;
    }
    else {
        node = (polyPointer)malloc(sizeof(node));
    }
    return node;
}

//다항식 반환함수
void perase(polyPointer* ptr) {
    polyPointer temp;
    if (*ptr) {
        temp = (*ptr)->link;    //다항식의 첫번째 항
        (*ptr)->link = avail;   //다항식의 헤더노드를 가용 공간 리스트에 연결
        avail = temp;   //가용 공간 리스트 포인터 업데이트
        *ptr = NULL;    //기존 포인터 해제
    }
}

//다항식 읽기함수
polyPointer pread() {
    header = getNode(); //헤더 노드
    header->link = header;

    polyPointer last = header;  //마지막 노드를 헤더로 초기화
    int coef, expon;

    printf("다항식의 항의 계수와 지수를 공백으로 구분해서 입력해 주세요. (EX. 3x^2는 3 2, -2x는 -2 1)\n");
    printf("0 0 입력시 입력이 종료됩니다.\n");
    while (1) {
        scanf("%d %d", &coef, &expon);
        if (coef == 0 && expon == 0) {
            break;
        }
        polyPointer newNode = getNode();    //새 노드 생성
        newNode->coef = coef;
        newNode->expon = expon;
        newNode->link = header; //새 노드는 헤더를 가리키도록 설정

        last->link = newNode;   //새 노드 연결
        last = newNode; //마지막 노드 업데이트
    }

    return header;  //헤더 노드 반환
}

//다항식 출력함수
void pwrite(polyPointer header) {
    polyPointer node = header->link; //다항식의 첫번째 항

    if (node == header) {
        printf("0\n");
        return;
    }

    //첫항 출력
    if (node->coef != 0) {
        if (node->expon != 0) {
            printf("%dx^%d ", node->coef, node->expon);
        }
        else {
            printf("%d", node->coef);
        }
        node = node->link;
    }

    //이후의 항 출력
    while (node != header) {
        if (node->coef > 0) {
            if (node->expon != 0) {
                printf("+ %dx^%d ", node->coef, node->expon);
            }
            else {
                printf("+ %d", node->coef);
            }
        }
        else if (node->coef < 0) {
            if (node->expon != 0) {
                printf("- %dx^%d ", (node->coef) * (-1), node->expon);
            }
            else {
                printf("- %d", (node->coef) * (-1));
            }
        }
        node = node->link;
    }
    printf("\n");
}

//다항식 덧셈함수
polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer rheader = getNode();    //헤더 노드
    rheader->link = rheader;
    polyPointer last = rheader; //마지막 노드 포인터 초기화
    polyPointer ra = a->link;   //A의 첫번째 항
    polyPointer rb = b->link;   //B의 첫번째 항

    while (ra != a || rb != b) {
        polyPointer rnode = getNode();

        if (ra == a) {  //B의 남은 항 처리
            rnode->coef = rb->coef;
            rnode->expon = rb->expon;
            rb = rb->link;
        }
        else if (rb == b) { //A의 남은 항 처리
            rnode->coef = ra->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
        }
        else if (ra->expon > rb->expon) {   //A의 지수가 큰 경우
            rnode->coef = ra->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
        }
        else if (ra->expon < rb->expon) {   //B의 지수가 큰 경우
            rnode->coef = rb->coef;
            rnode->expon = rb->expon;
            rb = rb->link;
        }
        else {  //지수가 같은 경우
            rnode->coef = ra->coef + rb->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
            rb = rb->link;
        }
        last->link = rnode; //새 항 연결
        last = rnode;   //마지막 노드 업데이트
        rnode->link = rheader;  //원형 연결 리스트의 구조 구성
    }
    return rheader; //결과 헤더 반환
}

//다항식 뺄셈함수
polyPointer pmult(polyPointer a, polyPointer b) {
    polyPointer rheader = getNode();    //헤더 노드
    rheader->link = rheader;
    polyPointer last = rheader; //마지막 노드 포인터 초기화
    polyPointer ra = a->link;   //A의 첫번째 항
    polyPointer rb = b->link;   //B의 첫번째 항

    while (ra != a || rb != b) {
        polyPointer rnode = getNode();

        if (ra == a) { //B의 남은 항 처리
            rnode->coef = -rb->coef;
            rnode->expon = rb->expon;
            rb = rb->link;
        }
        else if (rb == b) { //A의 남은 항 처리
            rnode->coef = ra->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
        }
        else if (ra->expon > rb->expon) {   //A의 지수가 큰 경우
            rnode->coef = ra->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
        }
        else if (ra->expon < rb->expon) {   //B의 지수가 큰 경우
            rnode->coef = -rb->coef;
            rnode->expon = rb->expon;
            rb = rb->link;
        }
        else {  //지수가 같은 경우
            rnode->coef = ra->coef - rb->coef;
            rnode->expon = ra->expon;
            ra = ra->link;
            rb = rb->link;
        }
        last->link = rnode;   //새 항 연결
        last = rnode; //마지막 노드 업데이트
        rnode->link = rheader;  //원형 연결 리스트의 구조 구성
    }
    return rheader; //결과 헤더 반환
}

polyPointer eval(polyPointer a, polyPointer b) {
    polyPointer rheader = getNode();    //최종결과 헤더 노드
    rheader->link = rheader;

    polyPointer ra = a->link;   //A의 첫번째 항
    while (ra != a) {
        polyPointer rb = b->link;   //B의 첫번째 항
        polyPointer theader = getNode();    //중간 결과 헤더 노드
        theader->link = theader;
        polyPointer last = theader;

        while (rb != b) {
            polyPointer rnode = getNode();  //새 노드 생성
            rnode->coef = ra->coef * rb->coef;  //계수
            rnode->expon = ra->expon + rb->expon;   //지수
            last->link = rnode; //새 항 연결
            rnode->link = theader;  //원형 연결 리스트 구조 설정
            last = rnode;   //마지막 노드 업데이트
            rb = rb->link;
        }
        rheader = padd(rheader, theader);   //최종 결과에 중간 결과 합산
        perase(&theader);
        ra = ra->link;
    }
    return rheader; //최종 결과 반환
}

int main() {
    int menu;
    polyPointer a = NULL;
    polyPointer b = NULL;

    while (1) {
        printf("-------------메뉴-------------\n");
        printf("1. 다항식 입력\n");
        printf("2. 다항식 출력\n");
        printf("3. 다항식 덧셈\n");
        printf("4. 다항식 뺄셈\n");
        printf("5. 다항식 곱셈\n");
        printf("6. 프로그램 종료\n");
        printf("원하는 메뉴의 번호를 입력해주세요.: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1:
            printf("다항식A 입력\n");
            a = pread();    //다항식A 입력
            printf("다항식B 입력\n");
            b = pread();    //다항식B 입력
            break;
        case 2:
            if (a == NULL || b == NULL) {
                printf("다항식을 먼저 입력해 주세요.\n");
            }
            else {
                printf("다항식A: ");
                pwrite(a);  //다항식A 출력
                printf("다항식B: ");
                pwrite(b);  //다항식B 출력
            }
            break;
        case 3:
            if (a == NULL && b == NULL) {
                printf("다항식을 먼저 입력해 주세요.\n");
            }
            else {
                polyPointer plus = padd(a, b); //A + B
                printf("A + B = ");
                pwrite(plus);    //결과 출력
                perase(&plus);   //결과 노드 메모리 반환
            }
            break;
        case 4:
            if (a == NULL && b == NULL) {
                printf("다항식을 먼저 입력해 주세요.\n");
            }
            else {
                polyPointer minus = pmult(a, b); //A - B
                printf("A - B = ");
                pwrite(minus);   //결과 출력
                perase(&minus);  //다항식 반환
            }
            break;
        case 5:
            if (a == NULL && b == NULL) {
                printf("다항식을 먼저 입력해 주세요.\n");
            }
            else {
                polyPointer product = eval(a, b); // A * B
                printf("A * B = ");
                pwrite(product);    //결과 출력
                perase(&product);   //결과 다항식 반환
            }
            break;
        case 6:
            exit(0);    //프로그램 종료
        default:
            printf("해당 기능은 지원하지 않습니다.\n");
            break;
        }
    }
}
