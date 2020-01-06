#include <iostream>
#include "trackingh.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	/*하나만 직선으로  
	Location list1[1] = {{1,1}};
	Location list2[1] = {{1.5,2.5}};
	Location list3[5] = {{1.7,3.1},{1.6,3.9},{1.3,5},{1.2,6.2},{1.5,1.5}};
	*/
	
	/*두점 크로스로 이동 
	Location list1[2] = {{2.0,1.0},{1.0,1.0}};
	Location list2[2] = {{1.7,2.0},{1.3,2.0}};
	Location list3[2][5] = {{{1.5,3.0},{1.0,4.0},{0.7,5.0},{0.6,6.0},{0.5,7.0}},{{1.6,3.0},{1.8,4.0},{2.1,5.0},{2.2,6.0},{2.2,7.0}}};
	
	Location t1 = {0.0,6.5};
	Location t2 = {3.0,6.5};
	Location t3 = {3.0,0.0};
	Location t4 = {0.0,0.0};
	*/
	/* 두점 크로스 한점 위에서 아래 
	Location list1[3] = {{1.5,7.0},{2.0,1.0},{1.0,1.0}};
	Location list2[3] = {{1.7,6.0},{1.7,2.0},{1.3,2.0}};
	Location list3[3][5] = {{{1.6,5.3},{1.3,4.5},{1.5,3.2},{1.4,2.5},{1.6,1.6}},{{1.5,3.0},{1.0,4.0},{0.7,5.0},{0.6,6.0},{0.5,7.0}},{{1.6,3.0},{1.8,4.0},{2.1,5.0},{2.2,6.0},{2.2,7.0}}};
	*/
	//두점 위 아래 로 이 동 
	Location list1[2] = {{1.5,7.0},{2.0,1.0}};
	Location list2[2] = {{1.7,6.0},{1.7,2.0}};
	Location list3[2][5] = {{{1.6,5.3},{1.3,4.5},{1.5,3.2},{1.4,2.5},{1.6,1.6}},{{1.5,3.0},{1.0,4.0},{0.7,5.0},{0.6,6.0},{0.5,7.0}}};
	
	/*
	//점 4 
	Location list1[4] = {{2.5,7.0},{1.5,7.0},{2.0,1.0},{1.0,1.0}};
	Location list2[4] = {{2.7,6.0},{1.7,6.0},{1.7,2.0},{1.3,2.0}};
	Location list3[4][5] = {{{2.6,5.3},{2.3,4.5},{2.5,3.2},{2.4,2.5},{2.6,1.6}},{{1.6,5.3},{1.3,4.5},{1.5,3.2},{1.4,2.5},{1.6,1.6}},{{1.5,3.0},{1.0,4.0},{0.7,5.0},{0.6,6.0},{0.5,7.0}},{{1.6,3.0},{1.8,4.0},{2.1,5.0},{2.2,6.0},{2.2,7.0}}};
	*/
	 
	Location t1 = {0.0,6.5};
	Location t2 = {3.0,6.5};
	Location t3 = {3.0,0.0}; 
	Location t4 = {0.0,0.0};
	
	
	int n = 2;
	double r = 1.0;
	idNodeList* idList = makeIdNodeList();
	
	points* past = makeInitPoints(n,list1,idList,r);
	int j;

	printf("length: %d\n",past->length);
	puts("----------------------------");	
	for(j=0;j<n;j++)
	{
	printf("id: %d r:%f distance: %f direction x y:%f %f point x y: %f %f \n"
	,past->list[j].id, past->list[j].r, past->list[j].distance, past->list[j].direction.x, past->list[j].direction.y, past->list[j].p.x, past->list[j].p.y);
    }
    puts("----------------------------");	
    
	points* current = makePoints(n,list2);
	int num = 6;
	int i=0;

	do
	{
		tracking(current,past,idList,0.5,0.7,1.0,t1,t2,t3,t4);
		past = makeCurrentToPast(current);
		for(j=0;j<n;j++)
		{
		list1[j] = list3[j][i];
	    }
	    
	    if(past->length == 0)
	    {
	    	puts("----------------------------");	
	    	puts("no data");
	    	puts("----------------------------");	
		}
		else
		{
		puts("----------------------------");		
		for(j=0;j<past->length;j++)
		{
		printf("id: %d r:%f distance: %f direction x y:%f %f point x y: %f %f \n"
	     ,past->list[j].id, past->list[j].r, past->list[j].distance, past->list[j].direction.x, past->list[j].direction.y, past->list[j].p.x, past->list[j].p.y);
	    }
	    puts("----------------------------");	
	    }
		current = makePoints(n,list1);
	    
		i+=1;
	}while(i<num);
	
	return 0;
}
