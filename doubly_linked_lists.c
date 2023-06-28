#include <stdio.h>
#include <stdlib.h>

struct  Node {
	int data;
	struct Node *prevNode;
	struct Node *nextNode;
};

struct Node *getNode(int data)
{
	struct Node *node;
	node = (struct Node *)malloc(sizeof(struct Node));
	node->data = data;
	node->prevNode = NULL;
	node->nextNode = NULL;

	return node;
}

struct Node *InsetAtHead(struct Node *headRef, int data)
{
	struct Node *newNode = getNode(data);
	// Check for Empty case
	if (headRef == NULL)
	{
		headRef = newNode;
		return headRef;
	}

	newNode->nextNode = headRef;
	newNode->prevNode = NULL;
	headRef = newNode;

	return headRef;
}

void InsetAtPos(struct Node **headRef, int data, int pos)
{
	int i = 1;
	struct Node *newNode = getNode(data);

	// Check for head Node and Empty list case
	if (pos == 1)
	{
		if (headRef == NULL)
		{
			*headRef = newNode;
			return;
		}
		newNode->nextNode = *headRef;
		newNode->prevNode = NULL;
		*headRef = newNode;
		return;
	}

	struct Node *current = *headRef;
	while(i < pos - 1 && current != NULL)
	{
		current = current->nextNode;
		i++;
	}

	// For my case, if someone passes an invalid position, I will insert
	// at the end, else, I will insert at the position passed. You can
	// raise an error, but it depends with the use case. Feel free to
	// customize your linked list as per your needs.
	if (current == NULL)
	{
		current = *headRef;
		while (current->nextNode != NULL)
		{
			current = current->nextNode;
		}
		current->nextNode = newNode;
		newNode->prevNode = current;
	}
	else
	{
		newNode->nextNode = current->nextNode;
		current->nextNode = newNode;
		newNode->prevNode = current;
	}
}


struct Node *InsetAtEnd(struct Node *headRef, int data)
{
	struct Node *newNode = getNode(data);
	// Check for empty list case
	if (headRef == NULL)
	{
		headRef = newNode;
		return headRef;
	}

	struct Node *current = headRef;
	while (current->nextNode != NULL)
	{
		current = current->nextNode;
	}
	current->nextNode = newNode;
	newNode->prevNode = current;

	return headRef;
}

// Delete a node at the given position.
struct Node *Delete(struct Node *headRef, int pos)
{
	int i = 1;
	struct Node *current = headRef;
	if (headRef == NULL)
		return headRef;
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

	// Invalid index(greater than list size) case.
	if (current == NULL)
	{
		printf("Invalid position.\n");
		return headRef;
	}
	struct Node *temp = current->nextNode;
	current->nextNode = temp->nextNode;
	temp->nextNode->prevNode = current;
	free(temp);

	return headRef;

}

// Reverse using iteration approach.
struct Node *Reverse_iter(struct Node *headRef)
{
	struct Node *prev, *current, *next;
	current = headRef;
	prev = NULL;
	while (current != NULL)
	{
		next = current->nextNode;
		current->nextNode = prev;
		current->prevNode = next;
		prev = current;
		current = next;
	}
	headRef = prev;

	return (headRef);
}

// Reverse using recursive approach.
struct Node *Reverse_recursive(struct Node *headRef)
{
	if (headRef == NULL || headRef->nextNode == NULL)
		return headRef;
	struct Node *newHead = Reverse_recursive(headRef->nextNode);
	headRef->nextNode->nextNode = headRef;
	headRef->nextNode->prevNode = headRef->nextNode;
	headRef->nextNode = NULL;

	return newHead;
}

void Print(struct Node *headRef)
{
	printf("List: >>>||[");
	while(headRef != NULL)
	{
		printf("%d", headRef->data);
		if (headRef->nextNode != NULL)
			printf(" --> ");
		headRef = headRef->nextNode;
	}
	printf("]||<<< Done!\n");
}

void freeMem(struct Node *headRef)
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
	head = InsetAtHead(head, 1);
	head = InsetAtHead(head, 2);
	head = InsetAtHead(head, 3);
	head = InsetAtHead(head, 4);
	head = InsetAtHead(head, 5);
	head = InsetAtHead(head, 6);
	Print(head);
	InsetAtPos(&head, 10, 1);
	InsetAtPos(&head, 20, 2);
	InsetAtPos(&head, 30, 3);
	InsetAtPos(&head, 40, 4);
	InsetAtPos(&head, 50, 10);
	InsetAtPos(&head, 60, 15);
	Print(head);
	head = InsetAtEnd(head, 100);
	head = InsetAtEnd(head, 200);
	head = InsetAtEnd(head, 300);
	head = InsetAtEnd(head, 400);
	head = InsetAtEnd(head, 500);
	head = InsetAtEnd(head, 600);
	Print(head);
	printf("After reversing iteratively\n");
	head = Reverse_iter(head);
	Print(head);
	printf("After reversing recursively\n");
	head = Reverse_recursive(head);
	Print(head);
	printf("After deleting\n");
	head = Delete(head, 1);
	head = Delete(head, 20);
	Print(head);
	head = Delete(head, 5);
	Print(head);
	freeMem(head);

	return (0);
}
