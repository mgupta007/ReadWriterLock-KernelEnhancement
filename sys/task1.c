#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>
#include <lock.h>

#define DEFAULT_LOCK_PRIO 20

#define assert(x,error) if(!(x)){ \
            kprintf(error);\
            return;\
            }
			
			
int mystrncmp(char* des,char* target,int n)
{
    int i;
    for (i=0;i<n;i++)
	{
        if (target[i] == '.') continue;
        if (des[i] != target[i]) return 1;
    }
    return 0;
}



char output2[10];
int count2;

void writer1(char msg, int lck, int lprio)
{
	kprintf ("  %c: to acquire lock\n", msg);
       if( lock (lck, WRITE, DEFAULT_LOCK_PRIO)==1)
	   {
		            int i = 0;
            for(i=0; i < 100;i++){
                    kprintf("A");
	   }
	   }
        output2[count2++]=msg;
        kprintf ("  %c: acquired lock, sleep 3s\n", msg);
        sleep (1);
        output2[count2++]=msg;
        kprintf ("  %c: to release lock\n", msg);
        releaseall (1, lck);
}

void writer2(char msg, int lck, int lprio)
{
	kprintf ("  %c: to acquire lock\n", msg);
       if( lock (lck, WRITE, DEFAULT_LOCK_PRIO)==1)
	   {
		            int i = 0;
            for(i=0; i < 100;i++){
                    kprintf("B");
	   }
	   }
        output2[count2++]=msg;
        kprintf ("  %c: acquired lock, sleep 3s\n", msg);
        sleep (1);
        output2[count2++]=msg;
        kprintf ("  %c: to release lock\n", msg);
        releaseall (1, lck);
}


void writer3(char msg, int lck, int lprio)
{
	kprintf ("  %c: to acquire lock\n", msg);
       if( lock (lck, WRITE, DEFAULT_LOCK_PRIO)==1)
	   {
		            int i = 0;
            for(i=0; i < 100;i++){
                    kprintf("C");
	   }
	   }
        output2[count2++]=msg;
        kprintf ("  %c: acquired lock, sleep 3s\n", msg);
        sleep (1);
        output2[count2++]=msg;
        kprintf ("  %c: to release lock\n", msg);
        releaseall (1, lck);
}


void test4()
{
    int lck;
    lck = lcreate();



 int pr1 = create(writer1, 2000, 10, "writer1", 2, 'A', lck, 10);
 int pr2 = create(writer2, 2000, 20, "writer2", 2, 'B', lck, 20);
 int pr3 = create(writer3, 2000, 30, "writer3", 2, 'C', lck, 30);
    
  resume(pr1);


   resume(pr2);

    sleep(1);  
    resume(pr3);
    sleep(4);

    ldelete(lck);
}




int main( )
{
        kprintf("-test4");
        test4();
        sleep(5);
        shutdown();
}



