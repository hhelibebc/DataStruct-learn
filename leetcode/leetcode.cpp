#include "common\stdafx.h"
#include "common\queue.h"
#include "common\list.h"
#include "common\stack.h"

BaseData base1;
Stack s1;
Queue q1;
Deque q2;
LoopQueue q3;
LoopDeque q4;
LinkQueue q5;
LinkDeque q6;
LinearList L1;
LinkList L2;
DLinkList L3;

void stack_test(){
	int i;
	for(i=0;i<11;i++){
		base1.var = i;
		s1.Push(&base1);
		s1.Print();
	}
	for(i=0;i<9;i++){
		base1 = s1.Pop();
		s1.Print();
	}
}
void queue_test(){
	int i;
	//q1.SetAllowOverlap(true);
	for(i=0;i<15;i++){
		base1.var = i;
		q1.Push(&base1);
		q1.Print();
	}
	for(i=0;i<9;i++){
		base1 = q1.Pop();
		q1.Print();
	}
}
void deque_test(){
	int i;
	q2.SetAllowOverlap(true);
	for(i=0;i<11;i++){
		base1.var = i;
		q2.Push(&base1);
		q2.Print();
	}
	for(i=0;i<7;i++){
		base1.var = i;
		q2.rPush(&base1);
		q2.Print();
	}
	for(i=0;i<9;i++){
		base1 = q2.Pop();
		q2.Print();
	}
	for(i=0;i<9;i++){
		base1 = q2.rPop();
		q2.Print();
	}
}
void loop_queue_test(){
	int i;
	q3.SetAllowOverlap(true);
	for(i=0;i<15;i++){
		base1.var = i;
		q3.Push(&base1);
		q3.Print();
	}
	for(i=0;i<9;i++){
		base1 = q3.Pop();
		q3.Print();
	}
}
void loop_deque_test(){
	int i;
	q4.SetAllowOverlap(true);
	for(i=0;i<11;i++){
		base1.var = i;
		q4.Push(&base1);
		q4.Print();
	}
	for(i=0;i<7;i++){
		base1.var = i;
		q4.rPush(&base1);
		q4.Print();
	}
	for(i=0;i<4;i++){
		base1 = q4.Pop();
		q4.Print();
	}
	for(i=0;i<4;i++){
		base1 = q4.rPop();
		q4.Print();
	}
}
void link_queue_test(){
	int i;
	for(i=0;i<30;i++){
		base1.var = i;
		q5.Push(&base1);
		q5.Print();
	}
	for(i=0;i<15;i++){
		base1 = q5.Pop();
		q5.Print();
	}
}
void link_deque_test(){
	int i;
	for(i=0;i<11;i++){
		base1.var = i;
		q6.Push(&base1);
		q6.Print();
	}
	for(i=0;i<7;i++){
		base1.var = i;
		q6.rPush(&base1);
		q6.Print();
	}
	for(i=0;i<9;i++){
		base1 = q6.Pop();
		q6.Print();
	}
	for(i=0;i<9;i++){
		base1 = q6.rPop();
		q6.Print();
	}
}
void linear_list_test(){
	int i;
	for(i=0;i<11;i++){
		base1.var = i;
		L1.Insert(&base1,0);
		L1.Print();
	}
	L1.Delete(4);
	L1.Print();
	L1.Delete(7);
	L1.Print();
	L1.Delete(5);
	L1.Print();
	L1[0].Print();
	L1[3].Print();
	L1[5].Print();
}
void link_list_test(){
	int i;
	for(i=0;i<11;i++){
		base1.var = i;
		L2.Insert(&base1,0);
		L2.Print();
	}
	for(i=0;i<5;i++){
		L2.Delete(3);
		L2.Print();
	}
}
void dlink_list_test(){
	int i;
	for(i=0;i<11;i++){
		base1.var = i;
		L3.Insert(&base1,0);
		L3.Print();
	}
	for(i=0;i<5;i++){
		L3.Delete(2);
		L3.Print();
	}
	L3[3]->data.Print();
	L3[4]->data.Print();
	L3[5]->data.Print();
	L3[0]->data.Print();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//stack_test();
	queue_test();
	//deque_test();
	//loop_queue_test();
	//loop_deque_test();
	//link_queue_test();
	//link_deque_test();
	//linear_list_test();
	//link_list_test();
	//dlink_list_test();
	system("pause");
}
