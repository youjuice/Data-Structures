//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll)
{
	// 1. 링크드 리스트 순회 후 홀수인지 확인 (노드와 리스트가 비어있는지 체크 필요!!)
	// 2. 홀수 노드를 찾으면 해당 노드를 연결 리스트에서 제거 (제거 후 짝수 노드들끼리 연결!!)
	// 3. oddHead부터 시작해서 홀수 노드들끼리 모으기 (홀수 노드끼리 연결하려면, oddTail 필요!!)
	// 4. 짝수 노드들끼리 모인 링크드 리스트와 홀수 노드들끼리 모인 링크드 리스트 연결

	/* add your code here */
	// 리스트가 비어있다면 return
	if (ll == NULL || ll->head == NULL) {
		return;
	}

	ListNode* curr = ll->head;		// head 노드부터 탐색
	ListNode* prev = NULL;			// 이전 노드 초기화
	ListNode* evenHead = NULL;		// 짝수 링크드 리스트 head 초기화
	ListNode* evenTail = NULL;		// 짝수 링크드 리스트 tail 초기화

	// 노드가 비어있지 않다면
	while (curr != NULL) {
		if (curr->item % 2 == 0) {			// 현재 노드가 짝수일 때,
			if (evenHead == NULL) {			// evenHead가 비어있다면,
				evenHead = curr;			// evenHead 설정
				evenTail = curr;			// evenTail 설정
			}
			else {							
				evenTail->next = curr;		// 이미 차있다면, 
				evenTail = curr;			// 링크드 리스트 연결
			}

			if (prev == NULL) {				// head 노드가 짝수라면
				ll->head = curr->next;		// 다음 노드를 head로 지정
			}
			else {							// 아니라면,
				prev->next = curr->next;	// 링크드 리스트에서 제거
			}

			curr = curr->next;				// 이동하면서 탐색
			evenTail->next = NULL;			// tail 노드의 next는 NULL
		}

		else {								// 홀수 노드들끼리 연결
			prev = curr;
			curr = curr->next;
		}
	}

	if (evenHead != NULL) {					// evenHead가 있을 경우
		if(ll->head == NULL) {				// 링크드 리스트가 모두 짝수인 경우
			ll->head = evenHead;
		}

		else {
			prev->next = evenHead;			// 홀수 노드들과 짝수 노드들 연결
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
