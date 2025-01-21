#include <stdio.h>
#include <stdlib.h>

//동적 메모리 할당 매크로
#define MALLOC(ptr, size) ptr = (treePointer)malloc(size)

//BST 노드 구조체
typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer leftChild;
    treePointer rightChild;
};

//Inorder Traversal 함수 (LVR)
void inorder(treePointer root) {
    if (root != NULL) {
        inorder(root->leftChild);   //Left Child 방문
        printf("%d ", root->key);   //현재노드 출력
        inorder(root->rightChild);  //Right Child 방문
    }
}

//탐색 함수
treePointer modifiedSearch(treePointer node, int k) {
    treePointer temp = NULL;    //현재 탐색 위치

    while (node != NULL) {
        temp = node;
        if (k == node->key) {   //이미 존재
            return NULL;
        }
        else if (k < node->key) {   //찾는 값이 더 작으면 왼쪽으로
            node = node->leftChild;
        }
        else {  //찾는 값이 더 크면 오른쪽으로
            node = node->rightChild;
        }
    }
    return temp;
}

//삽입 함수
void insert(treePointer* node, int k) {
    treePointer ptr;
    treePointer temp = modifiedSearch(*node, k);

    if (temp == NULL) { //해당 노드가 이미 트리에 존재하는 경우
        printf("해당 노드가 이미 트리에 존재합니다.\n");
        return;
    }
    MALLOC(ptr, sizeof(*ptr));  //새 노드 생성
    ptr->key = k;
    ptr->leftChild = ptr->rightChild = NULL;

    if (*node) {
        if (k < temp->key) {
            temp->leftChild = ptr;
        }
        else {
            temp->rightChild = ptr;
        }
    }
    else {
        *node = ptr;
    }
}

//삭제 함수
treePointer delete(treePointer parent, int k) {
    if (parent == NULL) { //찾는 노드가 없는 경우
        printf("해당 노드는 존재하지 않습니다.")
            return NULL;
    }
    if (k < parent->key) {    //찾는 값이 더 작으면 왼쪽으로
        parent->leftChild = delete(parent->leftChild, k);
    }
    else if (k > parent->key) {   //찾는 값이 더 크면 오른쪽으로
        parent->rightChild = delete(parent->rightChild, k);
    }
    else {  //노드 발견
        if (parent->leftChild == NULL && parent->rightChild == NULL) {  //삭제 노드가 leaf노드인 경우
            free(parent);
            return NULL;
        }
        if (parent->leftChild == NULL) {  //삭제 노드가 right child만 가지고 있는 경우
            treePointer temp = parent->rightChild;
            free(parent);
            return temp;
        }
        else if (parent->rightChild == NULL) {    //삭제 노드가 left child만 가지고 있는 경우
            treePointer temp = parent->leftChild;
            free(parent);
            return temp;
        }
        else {  //삭제 노드의 자식이 두 개인 경우
            treePointer temp = parent->rightChild;
            while (temp && temp->leftChild != NULL) {
                temp = temp->leftChild;
            }
            parent->key = temp->key;  //노드 교체
            parent->rightChild = delete(parent->rightChild, temp->key); //최소값 노드 삭제
        }
    }
    return parent;
}

//메뉴 출력 함수
void printMenu() {
    printf("\n[[ Menu ]]\n");
    printf("1. 노드 삽입\n");
    printf("2. 노드 삭제\n");
    printf("3. 프로그램 종료\n");
}

int main() {
    treePointer root = NULL;
    int menu, key;

    while (1) {
        printMenu();
        printf("원하는 메뉴의 번호를 입력해주세요 : ");
        scanf("%d", &menu);

        switch (menu) {
        case 1: //삽입
            printf("삽입하고싶은 노드의 Key값을 입력해주세요 : ");
            scanf("%d", &key);
            if (root == NULL) { //루트 노드 설정
                treePointer newNode;
                MALLOC(newNode, sizeof(*newNode));
                newNode->key = key;
                newNode->leftChild = newNode->rightChild = NULL;
                root = newNode;
            }
            else {
                insert(&root, key);
            }
            //Inorder Traversal
            printf("Inorder Traversal 결과 : ");
            inorder(root);
            printf("\n");
            break;
        case 2: //삭제
            printf("삭제하고싶은 노드의 Key값을 입력해주세요 : ");
            scanf("%d", &key);
            root = delete(root, key);
            //Inorder Traversal
            printf("Inorder Traversal 결과 : ");
            inorder(root);
            printf("\n");
            break;
        case 3: //종료
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("지원하지 않는 기능입니다. 올바른 메뉴를 선택해주세요.\n");
        }
    }

    return 0;
}
