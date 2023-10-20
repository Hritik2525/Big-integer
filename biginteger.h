#ifndef biginteger
#define biginterger

typedef struct node
{
    int data;
    struct node *next;
} node;
void printList(node *res);
node *sum(char a[1000], char b[1000]);
node *diff(char a[1000], char b[1000]);
node *mult(char a[1000], char b[1000]);
node *divi(char a[1000], char b[1000]);

#endif