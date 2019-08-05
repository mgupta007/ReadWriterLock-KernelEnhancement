#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>




int calculating_priority(int ld, int process_id)
{
	
	if(process_id==-1)
		return process_id;
	
	return (locktab[ld].lockp[process_id]);
	
}


int flag = 0;

int calculating_timediff(struct lentry *pointer, int process_id, int ld, int read_pid)   
{

int TimeDiff;

if(pointer->extra_time[process_id] > locktab[ld].extra_time[read_pid])  
return (pointer->extra_time[process_id] - pointer->extra_time[read_pid]);
                                        
return (pointer->extra_time[read_pid] - locktab[ld].extra_time[process_id]);

}
int getMaxValue(int ld, int types)
{
    int i = 0, max = -1, process_id = -1;
    unsigned long time_wait = 0;
	
	struct lentry *pointer  = &locktab[ld];

    do{
        
		if(pointer->wait_list[i] == types &&  ( (locktab[ld].lockp[i] > max) || (pointer->lockp[i] == max && time_wait > locktab[ld].extra_time[i])))
		
		{
            max = locktab[ld].lockp[i];
            process_id = i;
            time_wait = pointer->extra_time[i];
        }
		i=i+1;
    }while(i<NPROC);
	
    return process_id;
}




int releaseall(int numlocks, ...){
    STATWORD ps;
    disable(ps);

    int l_rel[numlocks];
    unsigned int *value = (unsigned int *)(&numlocks) + (numlocks); 
    

 int j=0,i;
	
    do{
        l_rel[j] = *value--;
		j=j+1;
    }while(j<numlocks);


    
    for(i = 0; i < numlocks; i++){
        int ld = l_rel[i];


      
	  if(locktab[ld].process_in_lock[currpid] != 1)
	  {    
             restore(ps);
            return SYSERR;
        }
		
		
		struct lentry *pointer = &locktab[ld];
		
		
		if(1)
		{
            pointer->process_in_lock[currpid] = 0;
			
            priority_revise(currpid);
			
          int flag1=0;
			
		int i ;
        for(i=0;i<NPROC;i++)
		{
        if(locktab[ld].process_in_lock[i] == 1)
        {
           flag1=1;
		   break;
          
		}			
       }
   
			
			
				int flag2=0;
			

            if(flag1 != 1)
			
			{
                int process_id= getMaxValue(ld,2);
                int read_pid = getMaxValue(ld,1);
				
                int TimeDiff = 2000;
				
				if(process_id==-1)
				{
					TimeDiff = 2000;
					int y = 10;
				}
				
			
				
                else if(process_id == read_pid){
                TimeDiff = calculating_timediff(&locktab[ld], process_id, ld, read_pid);
				
				if(TimeDiff>1000)
					flag2=1;
		  
             }
			 
			 
			 
			 
                int m_Prio =  calculating_priority(ld, process_id);
				
				
                
				
				
				int flag3= 0, j = 0;
				
				struct lentry *point = &locktab[ld];

                if(flag2==1){
                    do{
                        if(locktab[ld].lockp[j] > m_Prio && locktab[ld].wait_list[j] == READ){

                    
                             point->process_in_lock[j] = 1;
						     point->lockp[j] = -1;
                             locktab[ld].wait_list[j] = -1;
                          
                            priority_modify(ld, j);
                            ready(j, RESCHNO);
							
							j=j+1;
							
							flag3=1;
                        }
                    }while(j<NPROC);
                }
				
				
                if(flag3==1)
				{
                    locktab[ld].ltype = 1;
                    locktab[ld].lock_status = LOCK_IS_LOCKED;
                    if(flag == 0)
                        resched();
                }
				
				else if(process_id >=0 && process_id<NPROC){
                       
					   setting(ld, point, process_id);
               
                    if(flag == 0){
                        resched();
                    }
                }
				
				
				else{
     
                    locktab[ld].lock_status = LOCK_NOT_LOCKED;
                    point->ltype = -1;
                }
            }
        }
    }
   
    restore(ps);
    return OK;
    
}



void setting(int ld, struct lentry *points, int process_id)
{
	     points->ltype = WRITE;
         points->lock_status = 1;
         locktab[ld].wait_list[process_id] = -1;
         locktab[ld].lockp[process_id] = -1;
         points->process_in_lock[process_id] = LOCK_IS_FREE;
         priority_modify(ld, process_id);
        ready(process_id, RESCHNO);
}




/*

int priority_revise(int pid){
    int i = 0, j = 0, maximum = -1;


do
{
	struct lentry *point = &locktab[i];
	if(proctab[pid].plocks[i] == 1)
	{
	do
	{
		 if(point->process_in_lock[j] != -1){
			 
			             if(maximum<priority_revise(j))
                         maximum = priority_revise(j);            
          
                }
		
	  j=j+1;
	}while(j<NPROC);
}
	i=i+1;
}while(i<NPROC);

int flag1 =0;

    if(maximum > proctab[pid].pinh){
        chprio(pid, maximum);
		flag1=1;
    }
	
	
	if(flag1==0)
	{
        chprio(pid, proctab[pid].pinh);
        proctab[pid].pinh = 0;
    }

    int answer;
	
	if((proctab[pid].pinh < proctab[pid].pprio))
     return (proctab[pid].pprio);

return (proctab[pid].pinh) ;


}
*/

int release_locks(int pid){
    STATWORD ps;
    disable(ps);
    
    flag = 1;

    int j=0;
	
    do{

     struct lentry *p = &locktab[j];

        if(p->process_in_lock[pid] == LOCK_IS_LOCKED){      

            releaseall(1, j);
        }
		
		j=j+1;
    }while(j<NLOCKS);

    flag = 0;

    restore(ps);
    return(OK);
}
