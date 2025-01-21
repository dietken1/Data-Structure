#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define _CRT_SECURE_NO_WARNINGS
#define INF 10000000

//인접리스트 노드 구조체
typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    int weight;
    nodePointer link;
};

void show_graph(int n, int** matrix);

//Dijkstra 알고리즘 (인접 행렬)
void dijkstra_matrix(int n, int** matrix, int start) {
    int* distance = (int*)malloc(n * sizeof(int));
    int* found = (int*)malloc(n * sizeof(int));
    int* pi = (int*)malloc(n * sizeof(int));

    //초기화
    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        found[i] = 0;
        pi[i] = -1;
    }
    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INF;
        int u = -1;

        //최단거리 정점 탐색
        for (int v = 0; v < n; v++) {
            if (!found[v] && distance[v] < minDist) {
                minDist = distance[v];
                u = v;
            }
        }

        found[u] = 1;

        //거리 업데이트
        for (int v = 0; v < n; v++) {
            if (matrix[u][v] != INF && !found[v] && distance[u] + matrix[u][v] < distance[v]) {
                distance[v] = distance[u] + matrix[u][v];
                pi[v] = u;
            }
        }
    }

    //최단경로 출력
    for (int i = 0; i < n; i++) {
        if (distance[i] == INF) {
            printf("정점 0에서 %2d까지의 최단 경로 길이: X\n", i);
        }
        else {
            printf("정점 0에서 %2d까지의 최단 경로 길이: %3d | 경로: ", i, distance[i]);
            int* path = (int*)malloc(n * sizeof(int));
            int cnt = 0;
            for (int v = i; v != -1; v = pi[v]) {
                path[cnt++] = v;
            }
            for (int j = cnt - 1; j >= 0; j--) {
                printf("%d ", path[j]);
            }
            printf("\n");
            free(path);
        }
    }
    free(distance);
    free(found);
    free(pi);
}

//Dijkstra 알고리즘 (인접 리스트)
void dijkstra_list(int n, nodePointer* adjLists, int start) {
    int* distance = (int*)malloc(n * sizeof(int));
    int* found = (int*)malloc(n * sizeof(int));
    int* pi = (int*)malloc(n * sizeof(int));

    //초기화
    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        found[i] = 0;
        pi[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INF;
        int u = -1;

        //최단거리 정점 찾기
        for (int v = 0; v < n; v++) {
            if (!found[v] && distance[v] < minDist) {
                minDist = distance[v];
                u = v;
            }
        }

        found[u] = 1;

        //인접한 정점에 대해 거리 갱신
        nodePointer temp = adjLists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (!found[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pi[v] = u;
            }
            temp = temp->link;
        }
    }

    //최단경로 출력
    for (int i = 0; i < n; i++) {
        if (distance[i] == INF) {
            printf("정점 0에서 %d까지의 최단 경로 길이: X\n", i);
        }
        else {
            printf("정점 0에서 %2d까지의 최단 경로 길이: %3d | 경로: ", i, distance[i]);
            int* path = (int*)malloc(n * sizeof(int));
            int cnt = 0;
            for (int v = i; v != -1; v = pi[v]) {
                path[cnt++] = v;
            }
            for (int j = cnt - 1; j >= 0; j--) {
                printf("%d ", path[j]);
            }
            printf("\n");
            free(path);
        }
    }
    free(distance);
    free(found);
    free(pi);
}

//Bellman-Ford 알고리즘 (인접 행렬)
int bellman_ford_matrix(int n, int** matrix, int start) {
    int* dist = (int*)malloc(n * sizeof(int));
    int* pi = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pi[i] = -1;
    }
    dist[start] = 0;

    for (int i = 1; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (matrix[u][v] != INF && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                    pi[v] = u;
                }
            }
        }
    }

    //음의 사이클 체크
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (matrix[u][v] != INF && dist[u] != INF && dist[u] + matrix[u][v] < dist[v]) {
                printf("음의 사이클이 존재합니다!!!\n");
                free(dist);
                free(pi);
                return 1;
            }
        }
    }

    //최단경로 출력
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("정점 0에서 %d까지의 최단 경로 길이: X\n", i);
        }
        else {
            printf("정점 0에서 %2d까지의 최단 경로 길이: %3d | 경로: ", i, dist[i]);

            //경로 추적
            int* path = (int*)malloc(n * sizeof(int));
            int cnt = 0;
            for (int v = i; v != -1; v = pi[v]) {
                path[cnt++] = v;
            }

            //경로 출력 (역순)
            for (int j = cnt - 1; j >= 0; j--) {
                printf("%d ", path[j]);
            }
            printf("\n");
        }
    }
    free(dist);
    free(pi);
    return 0;
}

// Bellman-Ford 알고리즘 (인접 리스트)
int bellman_ford_list(int n, nodePointer* adjLists, int start) {
    int* dist = (int*)malloc(n * sizeof(int));
    int* pi = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pi[i] = -1;
    }
    dist[start] = 0;

    for (int i = 1; i < n; i++) {
        for (int u = 0; u < n; u++) {
            nodePointer temp = adjLists[u];
            while (temp != NULL) {
                int v = temp->vertex;
                int weight = temp->weight;
                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pi[v] = u;
                }
                temp = temp->link;
            }
        }
    }

    //음의 사이클 체크
    for (int u = 0; u < n; u++) {
        nodePointer temp = adjLists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                printf("음의 사이클이 존재합니다!!!\n");
                free(dist);
                free(pi);
                return 1;
            }
            temp = temp->link;
        }
    }

    //최단경로 출력
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("정점 0에서 %d까지의 최단 경로 길이: X\n", i);
        }
        else {
            printf("정점 0에서 %2d까지의 최단 경로 길이: %3d | 경로: ", i, dist[i]);

            //경로 추적
            int* path = (int*)malloc(n * sizeof(int));
            int cnt = 0;
            for (int v = i; v != -1; v = pi[v]) {
                path[cnt++] = v;
            }

            //경로 출력 (역순)
            for (int j = cnt - 1; j >= 0; j--) {
                printf("%d ", path[j]);
            }
            printf("\n");
        }
    }
    free(dist);
    free(pi);
    return 0;
}

//인접 행렬 최단경로 함수
void shortest_path_from_matrix_graph(int flag, int n, int** matrix) {
    printf("\n[ 인접 행렬 ]\n");
    if (flag == 1) {    //Bellman-Ford 알고리즘
        bellman_ford_matrix(n, matrix, 0);
    }
    else {  //Dijkstra 알고리즘
        dijkstra_matrix(n, matrix, 0);
    }
}

//인접 리스트 최단경로 함수
void shortest_path_from_list_graph(int flag, int n, nodePointer* adjLists) {
    printf("\n[ 인접 리스트 ]\n");
    if (flag == 1) {    //Bellman-Ford 알고리즘
        bellman_ford_list(n, adjLists, 0);
    }
    else {  //Dijkstra 알고리즘
        dijkstra_list(n, adjLists, 0);
    }
}

//그래프 생성 함수
void generate_graph(int n, int e, int flag) {
    int** matrix = (int**)malloc(n * sizeof(int*)); //인접 행렬
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    nodePointer* adjLists = (nodePointer*)malloc(n * sizeof(nodePointer));  //인접 리스트

    //인접 행렬 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;   //자신
            }
            else {
                matrix[i][j] = INF; //다른 노드
            }
        }
    }

    //인접 리스트 초기화
    for (int i = 0; i < n; i++) {
        adjLists[i] = NULL;
    }

    //간선 입력받기
    for (int i = 0; i < e; i++) {
        int u, v, w;
        printf("%d번째 간선: (시작정점, 도착정점, 가중치)를 순서대로 입력하세요(EX. 0 5 3) (가중치는 10000이하의 값을 권장합니다.): ", i + 1);
        scanf("%d %d %d", &u, &v, &w);

        if (u < 0 || u >= n || v < 0 || v >= n) {   //정점 번호 체크
            printf("존재하지 않는 정점입니다. 현재 존재하는 정점은 0번 ~ %d번 입니다.\n", n - 1);
            i--;
            continue;
        }

        if (u == v) {   //Self edge 체크
            printf("self edge는 불가능합니다. 다시 입력해주세요.\n");
            i--;
            continue;
        }

        if (matrix[u][v] != INF) {  //Multi-graph 체크
            printf("Multi-graph는 불가능합니다. 다시 입력해주세요.\n");
            i--;
            continue;
        }

        if (w < 0 && flag == 0) {   //음의 가중치 체크
            printf("음의 가중치는 허용되지 않습니다.\n");
            i--;
            continue;
        }

        //인접 행렬 간선 추가
        matrix[u][v] = w;

        //인접 리스트 간선 추가
        nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
        newNode->vertex = v;
        newNode->weight = w;
        newNode->link = adjLists[u];    //새 노드를 기존 리스트의 앞에 추가
        adjLists[u] = newNode;
    }

    show_graph(n, matrix);
    shortest_path_from_matrix_graph(flag, n, matrix);
    shortest_path_from_list_graph(flag, n, adjLists);
}

//그래프 출력 함수
void show_graph(int n, int** matrix) {
    printf("\n[ 그래프 ]\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF) {
                printf(" INF ");
            }
            else {
                printf("%4d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

//메인 함수
int main() {
    int n, e, flag = 0;

    //사용자 입력
    printf("정점의 개수를 입력해주세요: ");
    scanf("%d", &n);
    printf("간선의 개수를 입력해주세요: ");
    scanf("%d", &e);
    printf("음의 가중치 허용 여부를 입력해주세요 (금지: 0 | 허용: 1): ");
    scanf("%d", &flag);

    //그래프 생성 함수 호출
    generate_graph(n, e, flag);

    return 0;
}
