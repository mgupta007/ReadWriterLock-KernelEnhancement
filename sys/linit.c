#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>


void setting_each_process(int lock)
{
	int i=0;
	struct lentry *t = &locktab[lock];
	
	    do{
			t->process_in_lock[i] = -1;    
            t->wait_list[i] = -1;
            t->lock_using[i] = 4;
			
			i=i+1;
        }while(i<NPROC);
	
	
	t->lock_status = LOCK_NOT_LOCKED;
}


void setting_lock()
 {     
       int i=0;
      
	   do
	   {
		   
		   struct lentry *t = &locktab[i];
       
        t->priority_lock= 0;
        t->state_of_lock = 1;
        t->ltype = -1;
		
		setting_each_process(i);
       
       
    }while(++i<NLOCKS);

	
	
}


int linit(){
	
    STATWORD ps;
    disable(ps);
	setting_lock();
	restore(ps);
    return OK;
}


