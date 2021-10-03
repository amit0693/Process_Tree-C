#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <time.h>


int main(int argc,char *argv[])
{
  if(argc != 3){
    fprintf(stderr, "Invalid Arguments. Please pass no. of levels & no of children as arguments...!!!\n" );
    exit(1);
  }
  int levels=atoi(argv[1]);
	int children=atoi(argv[2]);
  if(levels < 1 || (levels > 1 && children < 1)){
    fprintf(stderr, "Invalid Input...!!!\n" );
    exit(1);
  }
	int i;
	printf("(%d): Process starting\n",(int)getpid());
	printf("(%d): Parent's id = %d\n",(int)getpid(),(int)getppid());
	
	printf("(%d): Level in the tree %d\n",(int)getpid(),atoi(argv[1]));
	printf("(%d): Creating %d children at level %d\n",(int)getpid(),children,levels-1);

	 if(levels>1)
	{   
		
    	for(i=0;i<children;i++)
    	{	
       		pid_t cpid=fork();
        	if(cpid<0)
        	{
        			fprintf(stderr, "Failed to create child.!!!\n" );
        			exit(1);
        	}	
	        else if(cpid==0)
	        {	           
	           levels=levels-1;
             char childstr[5];
              char levelstr[5];
              
	           sprintf(levelstr,"%d",levels);
	           sprintf(childstr,"%d",children);
            int op = execl(argv[0],argv[0],levelstr,childstr,NULL);
            if(op == -1){
                fprintf(stderr, "Error in exec...!!!\n" );
        		exit(1);
            }
	        }
          else { 
	 	/* parent will wait for the child to complete */
     //printf("PID %d (parent) waiting for child PID %d\n", getpid(), cpid);
        wait(NULL);
    }
    			    		
    	}
    }
    else {
    exit(0);
  }
  
printf("(%u): Terminating at level %d\n",(int)getpid(),levels);
 


return 0;
}