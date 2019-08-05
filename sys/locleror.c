#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>


int setting_lock_status(struct lentry *ptr , int t, int p)
{
	    ptr->lock_status = LOCK_IS_LOCKED;
        ptr->ltype = t;
        ptr->priority_lock = p;
        ptr->process_in_lock[currpid] = 1;
		
		return 1;
}

 //  checking_write(&proctab[currpid], pointer,type,priority);
 
 void setting_wait(struct lentry *pointer , int t, int p, int l)
 {
	 	pointer -> wait_list[currpid] = t;
         pointer -> extra_time[currpid] = ctr1000;
		 locktab[l].lockp[currpid] = p;
 }

int checking_write(struct pentry *ptr, struct lentry *pointer , int t, int p, int l)
{
	
	    if(pointer->ltype != READ)
		{
	     		
        int  j=0;
	
	
	     pointer -> wait_list[currpid] = t;
         pointer -> extra_time[currpid] = ctr1000;
		 locktab[l].lockp[currpid] = p;
		 
		do
		{
			if(pointer->process_in_lock[j]!=-1)
			{
				priority_modify(l, j);
			}
			
			j=j+1;
		}while(j<NPROC);
		
		
		
		return OK;
	}
	
	return SYSERR;
}



	void checking_process_list(l)
	{
				
            int j= 0;
           do{
                if(locktab[l].process_in_lock[j] != -1)
                    priority_modify(l, j);
				
			j=j+1;
            }while(j<NPROC);
	}

int lock(int ldes1, int type, int priority)
{
 
    STATWORD ps;
    disable(ps);


    int flag = 0;
   
    //struct pentry *pptr = &proctab[currpid];
    locktab[ldes1].lock_using[currpid] = LOCK_IS_USED;

    if(ldes1 < 0 || ldes1 >= NLOCKS || proctab[currpid].pwaitret == DELETED)
	{
       flag = 1;
    }


    if((type != 1 && type != 2) || locktab[ldes1].state_of_lock == LOCK_IS_LOCKED)
	{
        flag =1 ;
    }

 
 if(flag==1)
 {   
     restore(ps);
	return SYSERR;
 }



    struct lentry *pointer = &locktab[ldes1];
    
  

   if( checking_write(&proctab[currpid], pointer,type,priority,ldes1) != -1)
   {
		
		proctab[currpid].pstate = PRWAIT;
        resched();
        restore(ps);
        return proctab[currpid].pwaitret;
	   
   }


 if(pointer->lock_status != LOCK_IS_LOCKED)
	{
        
		if(setting_lock_status(pointer,type,priority) == 1)
		{
        restore(ps);
        return OK;
		}
    }

 


    if(locktab[ldes1].ltype == 1)
	{
        	
        if(type == WRITE){
        

		
			setting_wait(pointer ,type, priority,  ldes1);	 
			checking_process_list(ldes1);

            	flag=0;
           
		proctab[currpid].pstate = PRWAIT;
        resched();
        restore(ps);
        return proctab[currpid].pwaitret;



        }
		
		
		if(flag != 1)
		{
        

	    
	   int j = 0;
       int m_place = -1;
       
	   do
	    {
        if(pointer->wait_list[j] == WRITE)
		{
		if( locktab[ldes1].lockp[j] > m_place)
		{
            m_place= locktab[ldes1].lockp[j];
        }
		}
		j=j+1;
    }while(j<NPROC);
			
			
			
			
            if(priority >= m_place)
			{
            locktab[ldes1].process_in_lock[currpid] = LOCK_IS_FREE;
			flag = 1;
             }
			
		if(flag == 0)
		{
         
		 setting_wait(pointer ,type, priority,  ldes1);	 
         checking_process_list(ldes1);
         
		 proctab[currpid].pstate = PRWAIT;
        resched();
        restore(ps);
        return proctab[currpid].pwaitret;
            }
        }
    }
    restore(ps);
    return OK;
}



