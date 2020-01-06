#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "trackingh.h"


idNodeList* makeIdNodeList(void)
{
	idNodeList* re = (idNodeList*)malloc(sizeof(idNodeList));
	re->maxId = -1;
	re->list = NULL;
	return re;

}

void makeIdNode(idNodeList* idList)
{
	idNode* re = (idNode*)malloc(sizeof(idNode));
	re->next = idList->list;
	idList->maxId+=1;
	re->id = idList->maxId;
	idList->list = re;
	
}

int getId(idNodeList* idList)
{
		 if(idList->list==NULL)
		 {
		 	makeIdNode(idList);
		 }
	
	
	idNode* n = idList->list;
	idList->list = n->next;
	int re = n->id;
	free(n);
	
	return re;
}

void freeId(idNodeList* idList, int id)
{ 
  idNode* re = (idNode*)malloc(sizeof(idNode));
  re->next = idList->list;
  re->id = id;
  idList->list = re;
	
}

void initC(table C[],int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		C[i].box = 0;
		C[i].next = NULL;
	}
}

void initI(table I[], points* past)
{
	int i;
	for(i=0;i<past->length;i++)
	{
		I[i].box = past->list[i].id;
		I[i].next = NULL;
	}
}


void addC(table C[], int index, point data)
{
	
	point* newD = (point*)malloc(sizeof(point));
	*newD = data;
	newD->next = NULL;
	
	if(C[index].next == NULL)
	{
		C[index].next = newD;
	}
	else
	{
		point* next = C[index].next;
		point* befor = NULL;
		
		while(next != NULL)
		{
			if(next->distance >= newD->distance)
			{
				if(befor == NULL)
				{
					C[index].next = newD;
					newD->next = next;
				}
				else
				{
					befor->next = newD;
					newD->next = next;
				}
				break;
			}
			befor = next;
			next = next->next;
		}
	}
	C[index].box+=1;
}

void addI(table I[], int index, point data)
{
	point* newD = (point*)malloc(sizeof(point));
	*newD = data;
	newD->next = NULL;
	
	if(I[index].next == NULL)
	{
		I[index].next = newD;
	}
	else
	{
		point* next = I[index].next;
		point* befor = NULL;
		
		while(next != NULL)
		{
			if(next->distance >= newD->distance)
			{
				if(befor == NULL)
				{
					I[index].next = newD;
					newD->next = next;
				}
				else
				{
					befor->next = newD;
					newD->next = next;
				}
				break;
			}
			befor = next;
			next = next->next;
		}
	}
}

void deletC(table C[], int index, int id, point** data)
{
	*data = NULL;
	if(C[index].next != NULL)
	{
		point* befor = NULL;
		point* next = C[index].next;
		
		while(next!=NULL)
		{
			if(next->id == id)
			{
				C[index].box -= 1;
			 
				if(befor == NULL)
				{
					*data = C[index].next;
					C[index].next = next->next;
				}
				else
				{
					*data = next;
					befor->next = next->next;
				}
				break;
			}
			befor = next;
			next = next->next;
		}
	}
}

void deletI(table I[], int index, int id, point** data)
{
	*data = NULL;
	if(I[index].next != NULL)
	{
		point* befor = NULL;
		point* next = I[index].next;
		
		while(next!=NULL)
		{
			if(next->id == id)
			{
				if(befor == NULL)
				{
					*data = I[index].next;
					I[index].next = next->next;
				}
				else
				{
					*data = next;
					befor->next = next->next;
				}
				break;
			}
			befor = next;
			next = next->next;
		}
	}
}

int insertI(table I[], int len, point data, int current)
{
	int i;
	for(i=0;i<len;i++)
	{
		if((I[i].box == data.id))
		{
			data.id = current;
			addI(I,i,data);
			break;
		}
	}
	return i;
}

int isAllZero(table C[],int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		if(C[i].box!=0)
		  return 0;
	}
	return 1;
}

int inDirection(Location a, Location b)
{
	double ab = a.x*b.x + a.y*b.y;
	double absA = sqrt(a.x*a.x + a.y*a.y);
	double absB = sqrt(b.x*b.x + b.y*b.y);
	
	if(ab == 0)
	{
		return 1;
	}
	
	double cos = ab/(absA*absB);
	if((cos<=1)&&(cos>=0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double distance(Location zero, Location a)
{
	double x = zero.x - a.x;
	double y = zero.y - a.y;
	return fabs(sqrt(x*x + y*y));
}

void stateChange(idState stateI[],int id,int state)
{
	int i = 0;
	while(stateI[i].id != id)
	{
		i+=1;
	}
	stateI[i].state = state;
}

void deletAll(table C[],int index)
{
	point* next = C[index].next;
	point* befor = C[index].next;
	while(next != NULL)
	{
		next = next->next;
		free(befor);
		befor = next;
	}
	C[index].next = NULL;
	C[index].box = 0;
}

Location sub(Location a, Location b)
{
	Location c={0.0,0.0};
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	
	return c;
}

Location normalize(Location a)
{
	Location c={0.0,0.0};
	c.x = a.x/sqrt((a.x*a.x)+(a.y*a.y));
	c.y = a.y/sqrt((a.x*a.x)+(a.y*a.y));
	
	return c;
}

double crossMultiple(Location a, Location b)
{
	return a.x*b.y - a.y*b.x;
}

int ccw(Location a, Location c, Location d)
{
  Location n1 = sub(c,a);
  Location n2 = sub(d,a);
  n1 = normalize(n1);
  n2 = normalize(n2);
  
  double crossV = crossMultiple(n1,n2);
  
  if(crossV>0)
   return -1;
  else if(crossV<0)
   return 1;
  else
    return 0;  
  	
}

int inThreshold(Location p,Location t1,Location t2,Location t3,Location t4)
{
	int c1 = ccw(t1,t2,p);
	int c2 = ccw(t2,t3,p);
	int c3 = ccw(t3,t4,p);
	int c4 = ccw(t4,t1,p);
	if(c1 == 1)
	{
		if(c2 == 1)
		{
			if(c3 == 1)
			{
				if(c4 == 1)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

points* makeInitPoints(int len,Location plist[],idNodeList*idList,double r)
{
	points* re = (points*)malloc(sizeof(points)+(sizeof(point)*len));
	re->length = len;
	int i;
	Location dd = {0.0,0.0};
	for(i=0;i<len;i++)
	{
		re->list[i].p = plist[i];
		re->list[i].id = getId(idList);
		re->list[i].distance = 0.0;
		re->list[i].r = r;
		re->list[i].direction = dd;
		re->list[i].next = NULL;	
	}
	return re;
}

points* makePoints(int len,Location plist[])
{
	points* re = (points*)malloc(sizeof(points)+(sizeof(point)*len));
	re->length = len;
	int i;
	Location dd = {0.0,0.0};
	for(i=0;i<len;i++)
	{
		re->list[i].p = plist[i];
		re->list[i].id = -1;
		re->list[i].distance = 0.0;
		re->list[i].r = 0.0;
		re->list[i].direction = dd;
		re->list[i].next = NULL;	
	}
	return re;
}

points* makeCurrentToPast(points* current)
{
	int count = 0;
	int i;
	for(i=0;i<current->length;i++)
	{
		if(current->list[i].id != -1)
		 count+=1;
	}
	points* re = (points*)malloc(sizeof(points)+(sizeof(point)*count));
	re->length = count;
	
	count = 0;
	for(i=0;i<current->length;i++)
	{
		if(current->list[i].id != -1)
		{
			re->list[count] = current->list[i];
			count+=1;
		}
	}
	free(current);
	return re;

}

void deletAllI(table I[],int index)
{
	point* next = I[index].next;
	point* befor = I[index].next;
	while(next!=NULL)
	{
		next = next->next;
		free(befor);
		befor = next;
	}
	I[index].next = NULL;
}

void tracking(points* current, points* past,idNodeList*idList, double margin,double alpha,double dr,Location t1,Location t2,Location t3,Location t4)
{
  int i,j,k;	
  table C[current->length];
  table I[past->length];
  idState stateI[past->length];
  
  for(i=0;i<past->length;i++)
  {
  	stateI[i].id = past->list[i].id;
  	stateI[i].state = 0;
  }
  
  initC(C,current->length);
  initI(I,past);
  
  for(i=0;i<past->length;i++)
  {
  	 for(j=0;j<current->length;j++)
  	 {
  		double d1 = distance(past->list[i].p,current->list[j].p);
  		double d2 = fabs(past->list[i].r - d1);
  		past->list[i].distance = d2;
  		if(d2 < margin)
  		{
  		  if((past->list[i].direction.x != 0.0)&&(past->list[i].direction.y != 0.0))
		  {

  		   if(inDirection(past->list[i].direction, sub(current->list[j].p,past->list[i].p)) == 1)	
  		   {
  		     addC(C,j,past->list[i]);	
  	       }
  	       
  	      }
  	      else
  	      {
  	      	 addC(C,j,past->list[i]);
		  }
		}
	 }
  }
  
  do
  {
   for(i=0;i<current->length;i++)
   {
   	 if(C[i].next != NULL)
   	 {
  	   insertI(I,past->length,*(C[i].next),i);
     }
   }

   for(i=0;i<past->length;i++)
   {
   	 
   	 point* next = I[i].next;
   	 
	 int s = 0;
   	 while(next != NULL)
   	 {
   	 	if(C[next->id].box == 1)
   	 	{
   	 		s = 1;
   	 		current->list[next->id].id = I[i].box;
   	 		current->list[next->id].distance = next->distance;
   	 		Location newL = {-next->p.x + current->list[next->id].p.x,-next->p.y + current->list[next->id].p.y};
   	 		current->list[next->id].direction = newL;
   	 		current->list[next->id].r = alpha*next->r+((1-alpha)*sqrt((newL.x*newL.x)+(newL.y*newL.y)));
   	 		current->list[next->id].next = NULL;
   	 		stateChange(stateI,I[i].box,1);
   	 		deletAll(C,next->id);
   	 		break;
		}
		next = next->next;
	 }
	 
	 if(s == 0)
	 {
	 	next = I[i].next;
	 	if(next != NULL)
	 	{
	 	current->list[I[i].next->id].id = I[i].box;
	 	current->list[next->id].distance = next->distance;
   	 	Location newL = {-I[i].next->p.x + current->list[I[i].next->id].p.x,-I[i].next->p.y + current->list[I[i].next->id].p.y};
   	 	current->list[I[i].next->id].direction = newL;
   	 	current->list[I[i].next->id].r = alpha*I[i].next->r+((1-alpha)*sqrt((newL.x*newL.x)+(newL.y*newL.y)));
   	 	current->list[I[i].next->id].next = NULL;
	 	stateChange(stateI,I[i].box,1);
	 	deletAll(C,next->id);
	    }
	 }
	 deletAllI(I,i);
   }
   
   for(i=0;i<past->length;i++)
   {
   	 point* data;
   	 if(stateI[i].state == 1)
   	 {
   	   for(j=0;j<current->length;j++)
		{   
			deletC(C,j,stateI[i].id,&data);
			if(data != NULL)
			{
				free(data);
			}
			
		}	
	 }
   }
   
 }while(isAllZero(C,current->length)==0);
 
 for(i=0;i<current->length;i++)
 {
 	if(current->list[i].id == -1)
 	{
 		current->list[i].id = getId(idList);
 		current->list[i].r = dr;
 		Location dd ={0.0,0.0};
 		current->list[i].direction = dd;
 		current->list[i].distance = 0.0;
		current->list[i].next = NULL; 	
 		
	}
	if(inThreshold(current->list[i].p,t1,t2,t3,t4)==0)
	{
		freeId(idList,current->list[i].id);
		current->list[i].id = -1;
	}
	
 }
 
 for(i=0;i<past->length;i++)
 {
 	if(stateI[i].state == 0)
 	{
 		freeId(idList,stateI[i].id);
	}
 }
 
 free(past);
}
