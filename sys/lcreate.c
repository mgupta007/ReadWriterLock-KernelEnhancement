#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>

int lcreate()
{
    
	STATWORD ps;
    
	disable(ps);

    int ID_lock = 0;
	int flag = 0;
	
	do
	{
		if(locktab[ID_lock].state_of_lock == LOCK_IS_FREE)
		{
		locktab[ID_lock].state_of_lock	= LOCK_IS_OCCUPIED;
		flag = 1;
		break;
		}
		
	ID_lock = ID_lock + 1;	
		
	}while(ID_lock < NLOCKS);
	
	if(flag==1)
	{
		restore(ps);
		return ID_lock;
	}
	
	if(flag==0)
	{
		restore (ps);
		return SYSERR;
	}
	

    restore(ps);
    return SYSERR;
}