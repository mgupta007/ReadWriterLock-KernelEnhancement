/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include<lock.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
 
 
SYSCALL chprio(int pid, int newprio)
{
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return(SYSERR);
	}
	pptr->pprio = newprio;
	
		if(pptr->pstate == PRREADY){
		
		int address;
		
		q[pid].qkey = 0;
		
		address = q[pid].qnext;
		q[address].qprev=q[pid].qprev;
		
		address = q[pid].qprev;
		q[address].qnext = q[pid].qnext;
		
		q[pid].qprev=-1;
		
		q[pid].qnext = -1;
		
		
		insert(pid, rdyhead, pptr->pprio);
	}

		int j = 0;
	
		do{
			if(pptr->plocks[j] == LOCK_IS_FREE){
		
				priority_modify(j, pid);
			}
			j=j+1;
		}while(j<NLOCKS);
	
	
	
	
	restore(ps);
	return(newprio);
}
