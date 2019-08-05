#ifndef _LOCK_H_
#define _LOCK_H_

#ifndef NLOCKS
#define NLOCKS 50
#endif

#ifndef DELETED
#define DELETED -6
#endif

#ifndef READ
#define READ 1
#endif

#ifndef WRITE
#define WRITE 2
#endif

#define LOCK_IS_FREE 1
#define LOCK_IS_OCCUPIED 2 

#define LOCK_IS_LOCKED 1
#define LOCK_NOT_LOCKED 2

#define LOCK_IS_USED 3
#define LOCK_NOT_USED 4


struct lentry{
    int priority_lock;
    int state_of_lock; 
    int ltype; 
    int lock_status; 
    int process_in_lock[NPROC];
    int wait_list[NPROC]; 
    int lockp[NPROC];
    int lock_using[NPROC];
    unsigned long extra_time[NPROC];
};


extern	struct	lentry locktab[];
extern  void priority_modify(int , int);
extern  int priority_revise(int);
extern  int release_locks(int);
extern  int erasing_extraTime(int);
extern  int free_locks(int);
extern  unsigned long ctr1000;


#endif
