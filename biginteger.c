#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

void insertAtBegin(node **head, int value)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->next = *head;
    *head = temp;
}

void insertAtEnd(node **head, int value)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    node *itr;
    itr = *head;
    while (itr->next != NULL)
        itr = itr->next;
    itr->next = temp;
}

void initialize(node **p1, node **p2, char a[1000], char b[1000])
{
    int x = 0, y = 0, i = strlen(a), j = strlen(b);
    while (i != 0)
    {
        insertAtBegin(p1, a[x] - '0');
        x++;
        i--;
    }
    while (j != 0)
    {
        insertAtBegin(p2, b[y] - '0');
        y++;
        j--;
    }
}

int length(node *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

void printList(node *res)
{
    node *itr;
    itr = res;
    while (itr != NULL)
    {
        printf("%d", itr->data);
        itr = itr->next;
    }
    printf("\n");
}

node *sum(char a[1000], char b[1000])
{
    node *p1 = NULL, *p2 = NULL;
    initialize(&p1, &p2, a, b);
    int l1 = length(p1), l2 = length(p2);
    if (l1 < l2)
    {
        node *temp1 = p1;
        p1 = p2;
        p2 = temp1;
        int temp2 = l1;
        l1 = l2;
        l2 = temp2;
    }
    node *res = NULL;
    int carry = 0;
    while (p1 && p2)
    {
        int sum = (p1->data + p2->data + carry);
        carry = sum / 10;
        sum = sum % 10;
        insertAtBegin(&res, sum);
        p1 = p1->next;
        p2 = p2->next;
    }
    int diffLength = l1 - l2, i = 0;
    while (i < diffLength)
    {
        int sum = p1->data + carry;
        carry = sum / 10;
        sum = sum % 10;
        insertAtBegin(&res, sum);
        p1 = p1->next;
        i++;
    }
    if (carry > 0)
        insertAtBegin(&res, carry);
    return res;
}

node *diff(char a[1000], char b[1000])
{
    node *p1 = NULL, *p2 = NULL;
    initialize(&p1, &p2, a, b);
    int l1 = length(p1), l2 = length(p2);
    int isNegative = 0;
    if (l1 < l2 || (l1 == l2 && strcmp(a, b) < 0))
    {
        isNegative = 1;
        node *temp1 = p1;
        p1 = p2;
        p2 = temp1;
        int temp2 = l1;
        l1 = l2;
        l2 = temp2;
    }
    node *res = NULL;
    int borrow = 0;
    while (p1 && p2)
    {
        p1->data -= borrow;
        if (p1->data < p2->data)
        {
            p1->data += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        int diff = p1->data - p2->data;
        insertAtBegin(&res, diff);
        p1 = p1->next;
        p2 = p2->next;
    }
    int diffLength = l1 - l2, i = 0;
    while (i < diffLength)
    {
        p1->data -= borrow;
        if (p1->data < 0)
        {
            p1->data += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        insertAtBegin(&res, p1->data);
        p1 = p1->next;
        i++;
    }
    if (res->data == 0)
        res = res->next;
    if (isNegative)
        res->data *= (-1);
    return res;
}

node *mult(char a[1000], char b[1000])
{
    node *p1 = NULL, *p2 = NULL;
    initialize(&p1, &p2, a, b);
    int l1 = length(p1), l2 = length(p2);
    if (l1 < l2)
    {
        node *temp = p1;
        p1 = p2;
        p2 = temp;
    }
    node *res = NULL;
    int zeroCount = 0;
    while (p2)
    {
        node *tempres = NULL;
        int carry = 0, x = 0, i = zeroCount;
        node *itr = p1;
        while (i)
        {
            insertAtBegin(&tempres, 0);
            i--;
        }
        while (itr)
        {
            int product = (p2->data * itr->data) + carry;
            carry = product / 10;
            product = product % 10;
            insertAtBegin(&tempres, product);
            itr = itr->next;
        }
        if (carry != 0)
            insertAtBegin(&tempres, carry);
        char str1[1000], str2[1000];
        node *itr1 = tempres, *itr2 = res;
        while (itr1 != NULL)
        {
            str1[x] = (itr1->data) + '0';
            itr1 = itr1->next;
            x++;
        }
        x = 0;
        while (itr2 != NULL)
        {
            str2[x] = (itr2->data) + '0';
            itr2 = itr2->next;
            x++;
        }
        res = sum(str1, str2);
        p2 = p2->next;
        zeroCount++;
    }
    return res;
}

node *divi(char dividend[1000], char divisor[1000])
{
    node *dividendList = NULL;
    node *divisorList = NULL;
    initialize(&dividendList, &divisorList, dividend, divisor);
    node *result = NULL;
    node *currentDividend = dividendList;
    int divisorInt = atoi(divisor);
    int temp = 0;
    while (currentDividend != NULL)
    {
        temp = temp * 10 + currentDividend->data;
        if (temp >= divisorInt)
        {
            insertAtBegin(&result, temp / divisorInt);
            temp = temp % divisorInt;
        }
        else
        {
            insertAtBegin(&result, 0);
        }
        currentDividend = currentDividend->next;
    }
    return result;
}
