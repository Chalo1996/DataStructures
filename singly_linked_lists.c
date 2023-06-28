#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *nextNode;
};

struct Node *getNode(int value)
{
	struct Node *node;
	node = (struct Node *)malloc(sizeof(struct Node));
	node->data = value;
	node->nextNode = NULL;

	return node;
}

struct Node *InsertAtHead(struct Node *headRef, int value)
{
	struct Node *newNode = getNode(value);
	newNode->nextNode = headRef;
	headRef = newNode;

	return headRef;
}

struct Node *InsertAtPos(struct Node *headRef, int value, int pos)
{
	int i = 1;
	struct Node *newNode = getNode(value);

	if (pos == 1)
	{
		newNode->nextNode = headRef;
		headRef = newNode;
		return headRef;
	}

	struct Node *current = headRef;
	while (i < pos - 1 && current != NULL)
	{
		current = current->nextNode;
		i++;
	}

	if (current == NULL)
	{
		current = headRef;
		while(current->nextNode != NULL)
		{
			current = current->nextNode;
		}
		current->nextNode = newNode;
	}
	else
	{
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
	}

	return headRef;
}

void InsertAtEnd(struct Node **headRef, int value)
{
	struct Node *newNode = getNode(value);
	if (*headRef == NULL)
	{
		*headRef = newNode;
		return;
	}
	struct Node *current = *headRef;
	while(current->nextNode != NULL)
	{
		current = current->nextNode;
	}
	current->nextNode = newNode;
}

struct Node *Delete(struct Node *headRef, int pos)
{
	int i = 1;
	struct Node *current = headRef;
	if (headRef == NULL)
	{
		printf("Nothing to delete, empty list\n");
		return headRef;
	}
	if (pos == 1)
	{
		headRef = headRef->nextNode;
		free(current);
		return headRef;
	}
	while (i < pos - 1 && current != NULL)
	{
		current = current->nextNode;
		i++;
	}
	if (current == NULL)
	{
		printf("Invalid Node Position.\n");
		return (headRef);
	}
	struct Node *temp = current->nextNode;
	current->nextNode = temp->nextNode;
	free(temp);

	return headRef;
}

struct Node *Reverse_Iter(struct Node *headRef)
{
	struct Node *current, *prev, *next;
	current = headRef;
	prev = NULL;
	while (current != NULL)
	{
		next = current->nextNode;
		current->nextNode = prev;
		prev = current;
		current = next;
	}
	headRef = prev;

	return (headRef);
}

struct Node *Recursive_Rev(struct Node *headRef)
{
	if (headRef == NULL || headRef->nextNode == NULL)
	{
		return headRef;
	}
	struct Node *reversed_list = Recursive_Rev(headRef->nextNode);
	headRef->nextNode->nextNode = headRef;
	headRef->nextNode = NULL;

	return reversed_list;
}

void Print(struct Node *headRef)
{
	printf("List: >>>|| ");
	while (headRef != NULL)
	{
		printf("%d", headRef->data);
		if (headRef->nextNode != NULL)
			printf(" --> ");
		headRef = headRef->nextNode;
	}
	printf(" ||<<< Done!\n");
}

void Print_Rec(struct Node *headRef)
{
	if (headRef == NULL)
	{
		printf(" ||<<< Done!\n");
		return;
	}
	printf("%d", headRef->data);
	if (headRef->nextNode != NULL)
		printf(" --> ");
	Print_Rec(headRef->nextNode);
}

void FreeMem(struct Node *headRef)
{
	struct Node *temp;
	while (headRef != NULL)
	{
		temp = headRef;
		headRef = headRef->nextNode;
		free(temp);
	}
}

int main()
{
	struct Node *head = NULL;
	head = InsertAtHead(head, 1);
	head = InsertAtHead(head, 2);
	head = InsertAtHead(head, 3);
	head = InsertAtHead(head, 4);
	head = InsertAtHead(head, 5);
	head = InsertAtHead(head, 6);
	Print(head);
	head = InsertAtPos(head, 7, 1);
	head = InsertAtPos(head, 8, 2);
	head = InsertAtPos(head, 9, 3);
	head = InsertAtPos(head, 10, 4);
	head = InsertAtPos(head, 11, 5);
	head = InsertAtPos(head, 15, 15);
	Print(head);
	InsertAtEnd(&head, 100);
	InsertAtEnd(&head, 200);
	InsertAtEnd(&head, 300);
	InsertAtEnd(&head, 400);
	InsertAtEnd(&head, 500);
	InsertAtEnd(&head, 600);
	Print(head);
	printf("After deleting.\n");
	head = Delete(head, 1);
	head = Delete(head, 6);
	head = Delete(head, 20);
	Print(head);
	printf("After Iterating Recursion.\n");
	head = Reverse_Iter(head);
	Print(head);
	printf("After Recursive Recursion\n");
	head = Recursive_Rev(head);
	Print(head);
	printf("Recursive Printing\n");
	Print_Rec(head);
	FreeMem(head);

	return (0);
}
