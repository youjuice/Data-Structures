int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the Queue:\n");
	printf("2: Recursively reverse the queue;\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the queue: ");
			scanf("%d", &i);
			enqueue(&q, i);
			printf("The resulting queue is: ");
			printList(&q.ll);
			break;
		case 2:
			recursiveReverse(&q); // You need to code this function
			printf("The resulting reversed queue is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////

void recursiveReverse(Queue *q)
{
	// 1. 재귀 탈출 조건 설정
	// 2. 우선 큐에서 아이템 빼고
	// 3. 콜스택이 쌓이면 재귀적으로 reverse
	
	/* add your code here */
	if (isEmptyQueue(q)) 
		return 0;
	
	int item = dequeue(q);
	recursiveReverse(q);

	enqueue(q, item);
}