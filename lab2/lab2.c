#include <stdio.h>
#include <stdlib.h>

#define maxKeyLenght 5

typedef struct List {
  char key[maxKeyLenght];
  struct List *next;
} List;

List *createList(int n)
{
  List *head = NULL;
  List *cur = NULL;
  List *prev = NULL;

  for (int i = 0; i < n; i++) {
    cur = (List *)malloc(sizeof(List));
    if (cur == NULL) {
      exit(EXIT_FAILURE);
    }

    printf("Enter the key of element %d: ", i + 1);
    scanf("%s", cur->key);
    cur->next = NULL;

    if (head == NULL) {
      head = cur;
    } else {
      prev->next = cur;
    }
    prev = cur;
  }
  return head;
}

void reverseList(List **head) {
  List *prev = NULL;
  List *cur = *head;
  List *next = NULL;

  while (cur != NULL) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  *head = prev;
}

void printList(List *head) {
  for (int i; head != NULL; i++) {
    printf("%s ", head->key);
    head = head->next;
  }
  printf("\n");
}

void freeList(List *head) {
  List *temp = NULL;
  for (int i; head != NULL; i++) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int main() {
  int n;
  printf("Enter the number of elements in the list: ");
  scanf("%d", &n);

  List *createList(int n);
  void reverseList(List * *head);
  void printList(List * head);
  void freeList(List * head);

  List *head = createList(n);
  printf("Original list: ");
  printList(head);

  reverseList(&head);
  printf("Reversed list: ");
  printList(head);

  freeList(head);
  return 0;
}
