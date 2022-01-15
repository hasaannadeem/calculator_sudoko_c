#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 9

int check = 1;

void *validate(void *puzz)
{
	int *array;
	int flag=0;
	array = (int *)puzz;
	for(int i=1; i<=9; i++)
	{
		flag=0;
		for(int j=0; j<9; j++)
		{
			if(i==array[j])
			{
				flag=1;
			}
			else if(flag!=1&&i!=array[j])
			{ 
				flag=0; 
			}
		}
		if(flag==0)
		{
			check = 0;
			break;
		}
	}

}



int main()
{

	int puzzle[9][9] = {{6,2,4,5,3,9,1,8,7},{5,1,9,7,2,8,6,3,4},{8,3,7,6,1,4,2,9,5},{1,4,3,8,6,5,7,2,9},{9,5,8,2,4,7,3,6,1},{7,6,2,3,9,1,4,5,8},{3,7,1,9,5,6,8,4,2},{4,9,6,1,8,2,5,7,3},{2,8,5,4,7,3,9,1,6}};

	int rc;
	pthread_t tid[NUM_THREADS];
	//validating rows
	for(long i=0; i<NUM_THREADS; i++)
	{
		rc = pthread_create(&tid[i],NULL,validate,(void *)puzzle[i]);
	}

	for(int i=0; i<9; i++)
	{
		pthread_join(tid[i],NULL);
	}
	//validating columns
	int temp[9];

	for(int i=0; i<9; i++)
	{	
		for(int j=0; j<9; j++)
		{
			temp[j] = puzzle[j][i];
		}

		rc = pthread_create(&tid[i],NULL,validate,(void *)temp);
	}
	
	for(int i=0; i<9; i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	//validating 3x3 boxes
	int k = 0;
	int s = 0;
	for(int l=0; l<6; l+=3)
	{
		for(int m=0; m<6; m+=3)
		{
			
			k=0;
			for(int i=l; i<i+3; i++)
			{
				if(m<9){
				for(int j=m; j<j+3; j++)
				{
					temp[k]=puzzle[i][j];
					k++;
				}
				}
			}

			rc = pthread_create(&tid[s],NULL,validate,(void *)temp);
			s++;
			
		}
		
	}

	for(int i=0; i<9; i++)
	{
		pthread_join(tid[i],NULL);
	}
	

	if(check==1)
		printf("solution is valid %i", check);
	else
		printf("solution is invalid");


	pthread_exit(NULL);

}
