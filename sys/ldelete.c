#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>



void lock_used(int l)
{
	
	int i=0;
	do
	{
		if(locktab[l].lock_using[i] !=4)
		{
			proctab[i].pwaitret = DELETED;
		  
		    
        
		   if(locktab[l].wait_list[i] !=  -2)
			{
              ready(i, RESCHNO);
            }
			
			 chprio(i, proctab[i].pinh);
		     proctab[i].pinh = 0;
		
		}
		
		i=i+1;
		
	}while(i<NPROC);
	
	resched();

}



void lock_set(int l)
{

	int i = 0;
	
	do
	{

        locktab[l].lock_using[i] = LOCK_NOT_USED;
        locktab[l].process_in_lock[i] = -1;    
        locktab[l].wait_list[i] = -2;
    
		
		i=i+1;
    }while(i<NPROC);
    
	struct lentry *t = &locktab[l];
	
	t->lock_status = 2;
	t->priority_lock = 0;
    t->state_of_lock = 1;
    t->ltype = -1;
}




int ldelete(int ldes){
    
	STATWORD ps;
    disable(ps);
    lock_set(ldes);
    lock_used(ldes);
    
    restore(ps);
    return OK;
}
