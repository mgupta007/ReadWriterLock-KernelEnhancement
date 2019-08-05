#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lock.h>
#include <stdio.h>


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







void priority_modify(int ld, int pid){
   
 int j = 0, m_place = -1;
   
 do{
	
int m_places, js;

 if(proctab[m_place].pinh>proctab[m_place].pprio)
 m_places =  proctab[m_place].pinh;


else
 m_places =  proctab[m_place].pprio;
	
 
 if(proctab[j].pinh>proctab[j].pprio)
 js =  proctab[j].pinh;


else
 js =  proctab[j].pprio;	
	
if(locktab[ld].wait_list[j] != -1)
{
	if(m_places< js)
{
            m_place = j;
}
	}
	j=j+1;
	
}while(j<NPROC);

	
	
int m_placess, jss;

 if(proctab[m_place].pinh>proctab[m_place].pprio)
 m_placess =  proctab[m_place].pinh;


else
 m_placess =  proctab[m_place].pprio;
	
 
 if(proctab[pid].pinh>proctab[pid].pprio)
 jss =  proctab[pid].pinh;


else
 jss =  proctab[pid].pprio;	

  
  struct pentry *p = &proctab[pid];

if(m_place==-1)
{
int y;
y=p->pinh;	
}


  else  if(p->pinh < m_placess)
	{   
        
		   if(p->pinh==0)
           p->pinh = p->pprio;
    
        
        chprio(pid, m_placess);
		
		
		struct pentry *pt1 = &proctab[pid];
        int temporary;
		
        if(pt1->wait_lock != -1){
            temporary = pt1->wait_lock;
            int j= 0;
       do{
                if(locktab[temporary].process_in_lock[j] != -1)
				{
                    priority_modify(temporary, j);
                }
				j=j+1;
            }while(j<NPROC);
        }
    }
}


void setlockentries(int p, int i)
{
	       locktab[i].wait_list[p] = -1;
            locktab[i].lockp[p] = -1;
}

void changep(struct pentry *pointer)
{

  if(pointer->pinh !=0)
  {
	  int t= pointer->pinh;
	  pointer->pinh = 0;
  pointer->pprio = t;
 
  }
					
					
}


int erasing_extraTime(int pid){
    STATWORD ps;
    disable(ps);
    
    int i;
	
    for(i=0; i < NLOCKS;i++){

       setlockentries(pid, i);
     
        
           int j;
			
			//struct pentry *pointer = &proctab[j];
			
            for(j=0;j< NPROC; j++){
				struct pentry *pointer = &proctab[j];
				
                if(locktab[i].process_in_lock[j] >=0){
	
//c

changep(pointer);	
                  
             
                    priority_modify(i, j);
                }
            }
        
    }

    restore(ps);
    return(OK);
}

int free_locks(int priority){
    STATWORD ps;
    disable(ps);

    int i = 0;
    do{
        
		locktab[i].lock_using[priority] = LOCK_NOT_USED;
		
		i=i+1;
    }while(i<NLOCKS);
    restore(ps);
    return OK;
}
















