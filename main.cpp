#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include "types_p2.h"
#include "p2_threads.h"
#include "utils.h"
using namespace std;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct timeval t_global_start;
int num;

int main(int argc, char** argv)
{	
if(argc == 2 && (atoi(argv[1]) > 0 )){
	
        num=atoi(argv[1]);
	pthread_t  tid[5];
	
	int 	i0=0;
	int	i1=1;
	int	i2=2;
	int	i3=3;
	int     i4=4;
 	pthread_create(&tid[0],NULL,threadfunc,(void*)(&i0));
	pthread_join(tid[0],NULL);
gettimeofday(&t_global_start, NULL);
	pthread_create(&tid[1],NULL,threadfunc,(void*)(&i1));
	pthread_create(&tid[2],NULL,threadfunc,(void*)(&i2));
	pthread_create(&tid[3],NULL,threadfunc,(void*)(&i3));
	pthread_create(&tid[4],NULL,threadfunc,(void*)(&i4));
		pthread_join(tid[1],NULL);
		pthread_join(tid[2],NULL);
		pthread_join(tid[3],NULL);	
		pthread_join(tid[4],NULL);
}


else	{

	printf("[ERROR] Expecting 1 arguments with integral value greater than zero.\n");
	printf("[Usage] p2_exec<number>.\n");
}	



		
return 0;


}

/*Example code for sleep and class usage
	Person p1;
	p1.set_order(1);

	usleep(MSEC(200));
	p1.start();


	usleep(MSEC(150));
	p1.complete();
	

	usleep(MSEC(10));
        
	for (int i=0; i<5; i++) {
		printf("Wake up thread after (%d) seconds\n", (5-i));
		usleep(MSEC(1000));
	}

	printf("Wake up thread\n");
	//status1= pthread_cond_signal(&cond);



	/* wait for the second thread to finish */
	

