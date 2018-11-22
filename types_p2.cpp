#include "types_p2.h"
#include "utils.h"
using namespace std;
extern struct timeval t_global_start;

void Person::set_gender(int data) { gender = data; }
int Person::get_gender(void)      { return gender; }
void Person::set_order(unsigned long data) { order = data; }
unsigned long Person::get_order(void)      { return order; }

void Person::set_use_order(unsigned long data) { use_order = data; }
unsigned long Person::get_use_order(void)      { return use_order; }

void Person::set_time(long data) { time_to_stay_ms = data; }

int Person::ready_to_leave(void) {
	struct timeval t_curr;
	gettimeofday(&t_curr, NULL);

	if (get_elasped_time(t_start, t_curr) >= time_to_stay_ms) { return 1; }
	else { return 0; }
}




void Person::start(void) {
	gettimeofday(&t_start, NULL);
	printf(" - (%lu)th person enters the restroom: \n", order+1);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_start));
}

void Person::complete(void) {
	gettimeofday(&t_end, NULL);
	printf(" - (%lu)th person comes out of the restroom: \n", order+1);
	printf(" - (%lu) milliseconds after the creation\n", get_elasped_time(t_create, t_end));
	printf(" - (%lu) milliseconds after using the restroom\n", get_elasped_time(t_start, t_end));
}

Person::Person() {
	//gettimeofday(&t_create, NULL);
	//r=0;
	rest=0;
}



// You need to use this function to print the Restroom's status
void Restroom::print_status(void) {
	int m1,w1;
	m1=0;
	w1=0;
	
	for(int i=0;i<test.size();i++) 	{
	if(test[i].get_gender()==1) w1++;
	else m1++;

}
if(status==1) cout<<", Status(empty)"<<" Man: "<<m1<<" Women: "<<w1<<" Total: "<<m1+w1<<endl;
else if(status==2) cout<<", Status(WomenPresent)"<<" Men: "<<m1<<" Women: "<<w1<<" Total: "<<m1+w1<<endl;
else if(status==0) cout<<", Status(MenPresent)"<<" Men: "<<m1<<" Women: "<<w1<<" Total: "<<m1+w1<<endl;
}


// Call by reference
// This is just an example. You can implement any function you need
void Restroom::add_person(Person p) {
	test.push_back(p);
	//if(test[a].get_gender()==1) status=1;
	//if(p.get_gender()==1) status=1;
	//else status=0;
}
bool Restroom::man_wantsto_enter(){
	struct timeval t_curr;
	int m1,w1;
	if(status==2) {
	m1=0;
	w1=0;
	for(int i=0;i<test.size();i++) 	{
	if(test[i].get_gender()==1) w1++;
	else m1++;

}
	status=0;
	gettimeofday(&t_curr,NULL);
	cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms][Restroom] (Man) goes into the restroom, State is (MenPresent): Total: "<<m1<<" (Men: "<<m1<<", Women: "<<0<<")"<<endl;
	return true;
}	



	else if(status==0){

	m1=0;
	w1=0;
	int l=test.size();
	for(int i=0;i<test.size();i++) 	{
	if(test[i].get_gender()==1) w1++;
	else m1++;

}
	status=0;
	gettimeofday(&t_curr,NULL);
	cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms][Restroom] (Man) goes into the restroom, State is (MenPresent): Total: "<<m1<<" (Men: "<<m1<<", Women: "<<0<<")"<<endl;
	return true;


}
	else return false;


}


bool Restroom::woman_wantsto_enter(){
	struct timeval t_curr;
	int m1,w1;
	if(status==2) {
	m1=0;
	w1=0;
	for(int i=0;i<test.size();i++) 	{
	if(test[i].get_gender()==1) w1++;
	else m1++;

}
	status=1;
	gettimeofday(&t_curr,NULL);
	cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms][Restroom] (Woman) goes into the restroom, State is (WomenPresent): Total: "<<w1<<" (Men: "<<0<<", Women: "<<w1<<")"<<endl;
	return true;
}	


	else if(status==1){
	m1=0;
	w1=0;
	int l=test.size();
	for(int i=0;i<test.size();i++) 	{
	if(test[i].get_gender()==1) w1++;
	else m1++;

}
	gettimeofday(&t_curr,NULL);
	cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms][Restroom] (Woman) goes into the restroom, State is (WomenPresent): Total: "<<w1<<" (Men: "<<0<<", Women: "<<w1<<")"<<endl;
	return true;



}
	else return false;


}



void Restroom::womanleaves(){
int m=0,w=0;
struct timeval t_curr;

gettimeofday(&t_curr, NULL);
cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms]"<<"[Restroom] ";
	
if(test.size()==1) {
status=2;//empty
cout<<"(Woman) left the restroom. Status is changed, Status is (empty): Total: "<<0<<" (Men: "<<0<<", Women: "<<0<<")"<<endl;
}
else{
for(int j=0;j<test.size();j++) if(test[j].get_gender()) w++;
cout<<"(Woman) left the restroom. Status is changed, Status is (WomenPresent): Total: "<<w-1<<" (Men: "<<0<<", Women: "<<w-1<<")"<<endl;
}
}


void Restroom:: manleaves(){

int m=0,w=0;
struct timeval t_curr;

gettimeofday(&t_curr, NULL);
cout<<"["<<get_elasped_time(t_global_start, t_curr)<<" ms]"<<"[Restroom] ";
if(test.size()==1) {
status=2;//empty
cout<<"(Man) left the restroom. Status is changed, Status is (empty): Total: "<<0<<" (Men: "<<0<<", Women: "<<0<<")"<<endl;
}
else{
for(int j=0;j<test.size();j++) if(!test[j].get_gender()) m++;
cout<<"(Man) left the restroom. Status is changed, Status is (MenPresent): Total: "<<m-1<<" (Men: "<<m-1<<", Women: "<<0<<")"<<endl;
}



}
//(Stay "<<test[l-1].time_to_stay_ms<<" ms),


