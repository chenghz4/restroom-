#include "p2_threads.h"
#include "utils.h"
#include <vector>
using namespace std;
void *threadfunc(void *parm);
extern pthread_cond_t  cond;
extern pthread_mutex_t mutex;
extern int num;
extern struct timeval t_global_start;
vector<Person>z;
vector<Person>wl;
Restroom restroom;
vector<Person>person;
int order2=0;
int order3=0;
int done=0;
int count=0;
int t1=1;
void *threadfunc(void *parm)
{
	int o=*(int*)parm;
	int pnum=num; 
	
if(o==0){
	Person p[2*num];
	for(int l=0;l<2*pnum;l++)  p[l].set_time(3+rand()%8);//3 8
	int t,j=0;

	int count=0,count1=0;
        int b[2]={0};
	while(j<2*pnum){
	t=rand()%2;
	if(b[t]==0) {
	p[j].set_gender(t);
	 j++;
	if(t==0) count++;
   	if(t==1) count1++;
}	
	if(count==pnum) b[0]=1;
	if(count1==pnum) b[1]=1;

}

for(int i=0;i<2*num;i++) {
p[i].set_order(i);
p[i].wtime=rand()%5+1;

}


for(int i=0;i<2*num;i++) person.push_back(p[i]);

}



if(o==1){
int i;
int zch=0;
//gettimeofday(&t_global_start, NULL);
for( zch=0;zch<2*num;zch++){
	usleep(MSEC(person[zch].wtime));
	gettimeofday(&person[zch].t_create,NULL);
	wl.push_back(person[zch]);
if(person[zch].get_gender()==0)cout<<"["<<get_elasped_time(t_global_start, person[zch].t_create)<<" ms]"<<"[Input] A person (Man) goes into the queue"<<endl;//w:1 m:0
else cout<<"["<<get_elasped_time(t_global_start, person[zch].t_create)<<" ms]"<<"[Input] A person (Woman) goes into the queue"<<endl;//w:1 m:0

	
}
//cout<<"e1"<<endl;
}	



if(o==2){
int m=0,w=0;
int tempflag;

while(order2<2*pnum){
tempflag=restroom.status;
usleep(MSEC(0.8));
if(wl.size()>0&&(wl[0].get_gender()==tempflag||tempflag==2)){
pthread_mutex_lock(&mutex);
while(done!=0) pthread_cond_wait(&cond, &mutex);

//wl[0].start();
gettimeofday(&wl[0].t_start,NULL);
if(wl.size()>1){
for(int u=0;u<wl.size();u++) {
if(wl[u].get_gender()==1) w++;
else m++;
}
}
if(wl[0].get_gender()==1) cout<<"["<<get_elasped_time( t_global_start, wl[0].t_start)<<" ms]"<<"[Queue] Send (Woman) into the restroom (Stay "<<wl[0].time_to_stay_ms<<" ms), Status"<<": Total: "<<wl.size()-1<<" (Men: "<<m<<", Women: "<<w<<")"<<endl;
else cout<<"["<<get_elasped_time( t_global_start, wl[0].t_start)<<" ms]"<<"[Queue] Send (Man) into the restroom (Stay "<<wl[0].time_to_stay_ms<<" ms), Status"<<": Total: "<<wl.size()-1<<" (Men: "<<m<<", Women: "<<w<<")"<<endl;



restroom.add_person(wl[0]);
wl.erase(wl.begin());
m=0;
w=0;
order2++;

pthread_cond_signal(&cond);
done=1;
pthread_mutex_unlock(&mutex);
}


};
//cout<<"e2"<<endl;
}
	

	


if(o==3){

while(order3<2*pnum){


pthread_mutex_lock(&mutex);
while(done!=1) pthread_cond_wait(&cond, &mutex);

if(restroom.test.begin()->get_gender()==0){

restroom.man_wantsto_enter();
//restroom.print_status();
}


else{
restroom.woman_wantsto_enter();
//restroom.print_status();
}




//cout<<"order"<<order<<endl;


pthread_cond_signal(&cond);
done=0;
pthread_mutex_unlock(&mutex);
order3++;


};
//cout<<"e3"<<endl;
}



if(o==4){
vector<Person>::iterator it;

while(count<2*pnum){
usleep(MSEC(0.8));
if(restroom.test.size()>0){


for(it=restroom.test.begin();it!=restroom.test.end();it++){

if(it->ready_to_leave()){
	count++;

if(it->get_gender()==1) restroom.womanleaves();
else restroom.manleaves();//m:0 f:1
//it->complete();
restroom.test.erase(it);

}

if(restroom.test.size()==0) break;
}
}

};
//cout<<"e4"<<endl;
}





pthread_exit(0);
}


