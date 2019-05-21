#include <iostream>
using namespace std;
struct thread{
	bool blocked;
	int core;
	struct thread* next;
};
thread* now=NULL;
thread* prev=NULL;
void new_thread(int thread_id)
{
	struct thread* p;
	if (now==NULL) {
	now=new thread;

	now->core=thread_id;
	now->blocked=false;
	now->next=now;
	prev=now;
	} else {
		prev->next= new thread;
		prev=prev->next;
		prev->core=thread_id;
		prev->blocked=false;
		prev->next=now;

	}

}
void exit_thread()
{
	struct thread* p=now->next;
	delete now;
	if (p==now) now=NULL;
}
void block_thread()
{
	now->blocked=true;
}
void wake_thread(int thread_id)
{
	thread* p=now;
	do{
		if (p->core==thread_id){
			p->blocked=false;
			break;
		} else {
			p=p->next;
		}
	}while(p!=now);
}
void timer_tick()
{
	do{
		now=now->next;
	}while(now->blocked==true);
}
int current_thread()
{
	if (now==NULL) return -1;
	return now->core;
}
void scheduler_setup (int timeslice)
{
	now=NULL;
	prev=NULL;
}
