#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *right;
    struct node *down;
} node;

typedef enum dir{
    RIGHT, DOWN
} dir;

int n = 0;
int m = 0;
int q = 0;
node *lineHead[2501];
long long getSum(int Id);
node *buildLine(int Id);
void *linkDown(node *p1, node *p2);
node *getNode(int line, int col);
void *swap(node *p1, node *p2, int len, dir flag);
int main(void){
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 0; i <= n; i++){
        lineHead[i] = buildLine(i);
        if(i != 0){
            linkDown(lineHead[i - 1], lineHead[i]);
        }
    }
    for(int i = 0; i < q; i++){
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        int x3 = 0;
        int y3 = 0;
        int x4 = 0;
        int y4 = 0;
        int a = 0;
        scanf("%d%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &a);
        node *x1y1_1 = getNode(x1, y1 - 1);
        node *x3y3_1 = getNode(x3, y3 - 1);
        node *x1_1y1 = getNode(x1 - 1, y1);
        node *x3_1y3 = getNode(x3 - 1, y3);
        node *x1y2 = getNode(x1, y2);
        node *x2y1 = getNode(x2, y1);
        node *x3y4 = getNode(x3, y4);
        node *x4y3 = getNode(x4, y3);
        swap(x1y1_1, x3y3_1, x2 - x1 + 1, DOWN);
        swap(x1_1y1, x3_1y3, y2 - y1 + 1, RIGHT);
        swap(x1y2, x3y4, x2 - x1 + 1, DOWN);
        swap(x2y1, x4y3, y2 - y1 + 1, RIGHT);
        long long sum = getSum(a);
        printf("%lld", sum);
        if(i != q - 1){
            printf("\n");
        }
    }
    return 0;
}

node *buildLine(int Id){
    node *head = (node *) malloc(sizeof (node));
    node *temp = head;
    for(int i = 1; i <= m; i++){
        temp->right = (node *) malloc(sizeof (node));
        temp->right->val = Id * m + i;
        temp = temp->right;
    }
    return head;
}
void *linkDown(node *p1, node *p2){
    for(int i = 0; i <= m; i++){
        p1->down = p2;
        p1 = p1->right;
        p2 = p2->right;
    }
}

long long getSum(int Id){
    long long sum = 0;
    node *pos = lineHead[Id];
    for(int i = 1; i <= m; i++){
        sum += pos->right->val;
        pos = pos->right;
    }
    return sum;
}

node *getNode(int line, int col){
    node *temp = lineHead[line];
    for(int i = 1; i <= col; i++){
        temp = temp->right;
    }
    return temp;
}

void *swap(node *p1, node *p2, int len, dir flag){
    if(flag == RIGHT){
        for(int i = 1; i <= len; i++){
            node *temp = p1->down;
            p1->down = p2->down;
            p2->down = temp;
            p1 = p1->right;
            p2 = p2->right;
        }
    } else{
        for(int i = 1; i <= len; i++){
            node *temp = p1->right;
            p1->right = p2->right;
            p2->right = temp;
            p1 = p1->down;
            p2 = p2->down;
        }
    }
}
