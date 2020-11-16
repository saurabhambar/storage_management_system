#include <stdio.h>
int mem[20]={0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0}, sz;
void search();
void fill();
void best(int b[]);
void worst(int b[]);
void first(int b[]);
void last(int b[]);
void next(int b[]);
void buddy(int b[]);


struct cordsize{
    int c1;
    int c2;
    int size;
};

void search(){
	int i;
	printf("Memory Details: \n");
	for(i=0;i<20;i++)
	{
		printf(" %d ",mem[i]);
	}
	printf("\n");
	return;
}
void fill(){
    int reqsz, i;
    printf("GENERATE ALLOCATION REQUEST \n\n\n");
    printf("Enter Number of Requests: \t");
    scanf("%d",&reqsz);
    sz = reqsz;
    int reqar[reqsz];

    for(i=0;i<reqsz;i++)
    {
        printf("Enter Size For Request Number %d :  ",i+1 );
        scanf("%d",&reqar[i]);
    }

    //Create Sample Allocation Here
    first(reqar);
    best(reqar);
    worst(reqar);
    last(reqar);
    next(reqar);
    buddy(reqar);

    printf("\n Choose type of Allocation: \n");
    //printf("\n Choose type of Allocation: \n");
    //printf("1.First Fit \n2.Best Fit \n3.Last Fit \n4.Worst Fit \n");

   return;
}

void first(int b[])
{
	printf("\n\n FIRST FIT ALLOCATION \n\n");
    int far[20],i,x,s;
    for(i = 0; i<20; i++ )
    {
        far[i] = mem[i];
    }
    int space[20];
	int j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    j=0;
    i=0;
    while(i<20) //fill blank index in space
    {
        if(far[i] == 0)
        {
            space[j] = i;
            j++ ;
        }
        i++;
    }
    j=0;
    struct cordsize gaps[20];
    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    i=0;
    j=0;
    int t = 0,totavl=0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            t++;
            j=i;
        }
        else
            j++;
    }
    j=0;
    i=0;
    t=0;
    int flag,totreq=0,altreq=0,vac=0;
    for(i=0;i<sz;i++)
    {
    	flag = 1;
        x=b[i];
        j=0;
        while(gaps[j].c1!=-1)
        {
            if(gaps[j].size>=x)
            {
             altreq = altreq + x;
             for(t=gaps[j].c1;t<=gaps[j].c2;t++)
             {
                far[t]=1;
             }
             vac = vac + gaps[j].size - x;
             gaps[j].size=0;
             printf("Request of size %d has been allocated from %d to %d \n",x,gaps[j].c1,gaps[j].c2);
             break;
            }
            else
            {
            	 flag = 0;
			}

            j++;
        }
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
    }
	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
	printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}
}
 void best(int b[])
{
    printf("\n\n BEST FIT ALLOCATION \n\n");
    int far[20],i,x,s,gapscount;
    struct cordsize gaps[20], temp;
    for(i = 0; i<20; i++ )
    {
        far[i] = mem[i];
    }
    int space[20],j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    for(i=0;i<20;i++) //fill blank index in space
    {
        if(far[i]==0)
        {
            space[j] = i;
            j++;
        }
    }
    j=0;
    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    gapscount=0;


    i=0;
    j=0;
    int t = 0,totavl=0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            t++;
            j=i;
        }
        else
            j++;
    }
    for(i=0;i<20;i++) //fill gaps array with -1
    {
        if(gaps[i].c1 != -1)
            gapscount++;
         else
                break;

    }

    for(i=0; i<gapscount-1;++i)
    {
        int min=i;
        for(j=i+1;j<gapscount;++j)
        {
            if(gaps[min].size>gaps[j].size)
                min=j;
        }
        if(min!=i)
        {
            temp=gaps[min];
            gaps[min]=gaps[i];
            gaps[i]=temp;

        }

    }
    t=0;
    int flag,totreq=0,altreq=0,vac=0;
    for(i=0;i<sz;i++)
    {
    	flag = 1;
        x=b[i];
        j=0;
        while(gaps[j].c1!=-1)
        {
            if(gaps[j].size>=x)
            {
             altreq = altreq + x;
             for(t=gaps[j].c1;t<=gaps[j].c2;t++)
             {
                far[t]=1;
             }
             vac = vac + gaps[j].size - x;
             gaps[j].size=0;
             printf("Request of size %d has been allocated from %d to %d \n",x,gaps[j].c1,gaps[j].c2);
             break;
            }
            else
            {
            	 flag = 0;
			}

            j++;
        }
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
    }
	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
	printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}



}

void worst(int b[])
{
    printf("\n\n WORST FIT ALLOCATION \n\n");
    int far[20],i,x,s,gapscount;
    struct cordsize gaps[20], temp;
    for(i = 0; i<20; i++ ) //to copy original memory
    {
        far[i] = mem[i];
    }
    int space[20],j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    for(i=0;i<20;i++) //fill blank index in space
    {
        if(far[i]==0)
        {
            space[j] = i;
            j++;
        }
    }
    j=0;

    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    gapscount=0;


    i=0;
    j=0;
   int t = 0,totavl=0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            t++;
            j=i;
        }
        else
            j++;
    }
    for(i=0;i<20;i++)
    {
        if(gaps[i].c1 != -1)
            gapscount++;
            else
                break;
    }

    for(i=0; i<gapscount-1;++i)
    {
        int max=i;
        for(j=i+1;j<gapscount;++j)
        {
            if(gaps[max].size<gaps[j].size)
                max=j;
        }
        if(max!=i)
        {
            temp=gaps[max];
            gaps[max]=gaps[i];
            gaps[i]=temp;

        }

    }
    t=0;
    int flag,totreq=0,altreq=0,vac=0;
    for(i=0;i<sz;i++)
    {
        flag = 1;
        x=b[i];
        j=0;
        while(gaps[j].c1!=-1)
        {
            if(gaps[j].size>=x)
            {
             altreq = altreq + x;
             for(t=gaps[j].c1;t<=gaps[j].c2;t++)
             {
                far[t]=1;
             }
             vac = vac + gaps[j].size - x;
             gaps[j].size=0;
             printf("Request of size %d has been allocated from %d to %d \n",x,gaps[j].c1,gaps[j].c2);
             break;
            }
            else
            {
            	 flag = 0;
			}

            j++;
        }
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
    }
	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
	printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}



}
void last(int b[])
{
    printf("\n\n LAST FIT ALLOCATION \n\n");
    int far[20],i,x,s;
    for(i = 0; i<20; i++ )
    {
        far[i] = mem[i];
    }
    int space[20];
	int j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    j=0;
    i=0;
    while(i<20) //fill blank index in space
    {
        if(far[i] == 0)
        {
            space[j] = i;
            j++ ;
        }
        i++;
    }
    j=0;
    struct cordsize gaps[20];
    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    i=0;
    j=0;
    int t = 0,totavl=0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            t++;
            j=i;
        }
        else
            j++;
    }
    j=0;
    i=0;
    t=0;
    int flag,totreq=0,altreq=0,vac=0;
    for(i=0;i<sz;i++)
    {
    	flag = 1;
        x=b[i];
        j=20;
        while(gaps[j].c1==-1)
        {
        	j--;
		}
        while(gaps[j].c1!=-1)
        {
            if(gaps[j].size>=x)
            {
             altreq = altreq + x;
             for(t=gaps[j].c1;t<=gaps[j].c2;t++)
             {
                far[t]=1;
             }
             vac = vac + gaps[j].size - x;
             gaps[j].size=0;
             printf("Request of size %d has been allocated. \n",x);
             break;
            }
            else
            {
            	 flag = 0;
			}

            j--;
        }
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
    }
	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
    printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}
}

void next(int b[])
{
	printf("\n\n NEXT FIT ALLOCATION \n\n");
    int far[20],i,x,s,gapscount;
    struct cordsize gaps[20], temp;
    for(i = 0; i<20; i++ ) //to copy original memory
    {
        far[i] = mem[i];
    }
    int space[20],j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    for(i=0;i<20;i++) //fill blank index in space
    {
        if(far[i]==0)
        {
            space[j] = i;
            j++;
        }
    }
    j=0;

    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    gapscount=0;


    i=0;
    j=0;
   int t = 0,totavl=0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            t++;
            j=i;
        }
        else
            j++;
    }
    for(i=0;i<20;i++)
    {
        if(gaps[i].c1 != -1)
            gapscount++;
            else
                break;
    }
    t=0;
    int flag,totreq=0,altreq=0,vac=0;
    for(i=0;i<sz;i++)
    {
        flag = 1;
        x=b[i];
        j=0;
        while(gaps[j].c1!=-1)
        {
            if(gaps[j].size>=x)
            {
                 altreq = altreq + x;
                 for(t=gaps[j].c1;t<=gaps[j].c2;t++)
                 {
                    far[t]=1;
                 }
                 vac = vac + gaps[j].size - x;
                 gaps[j].size=0;
                 printf("Request of size %d has been allocated from %d to %d \n",x,gaps[j].c1,gaps[j].c2);
                 break;
                }
                else
                {
                     flag = 0;
                }

            i=j;
            j++;

        }
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
    }
	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
	printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}
}

void buddy(int b[])
{
	printf("\n\n BUDDY FIT ALLOCATION \n\n");
    int far[20],i,x,s;
    for(i = 0; i<20; i++ )
    {
        far[i] = mem[i];
    }
    int space[20];
	int j=0;
    for(i=0;i<20;i++) //fill space array with -1
    {
        space[i] = -1;
    }
    j=0;
    i=0;
    while(i<20) //fill blank index in space
    {
        if(far[i] == 0)
        {
            space[j] = i;
            j++ ;
        }
        i++;
    }
    j=0;
    struct cordsize gaps[20], temp;
    for(i=0;i<20;i++) //fill gaps array with -1
    {
        gaps[i].c1 = -1;
    }
    i=0;
    j=0;
    int t = 0,totavl=0, numavl = 0;
    while(space[j]!=-1) //to create an array of gaps and their size to fill up accordingly
    {
        if(space[j+1]==space[j]+1)
		{
            gaps[t].c1=space[j];
            i=j;
            //printf("|%d|",j);//
            while(space[i+1]==space[i]+1)
            {
                i++;
            }
            gaps[t].c2=space[i];
            gaps[t].size = gaps[t].c2 - gaps[t].c1 + 1 ;
            totavl=totavl+gaps[t].size;
            numavl++;
            t++;
            j=i;
        }
        else
            j++;
    }
    j=0;
    i=0;
    t=0;
    for(i=0; i<numavl-1;++i) //sort in ascending order
    {
        int min=i;
        for(j=i+1;j<numavl;++j)
        {
            if(gaps[min].size>gaps[j].size)
                min=j;
        }
        if(min!=j)
        {
            temp=gaps[min];
            gaps[min]=gaps[i];
            gaps[i]=temp;

        }

    }
    int flag,totreq=0,altreq=0,vac=0;
    i=0;
    while(i<sz)
    {
    	flag = 1;
        x=b[i];
        j=0;
        while(j<numavl)
        {
            if(gaps[j].size>=x)
            {
             altreq = altreq + x;
        	 t = gaps[j].size;
        	 if(t/2 > x) //creating and adding buddies
        	 {
        	 	while(gaps[j].size > x)
        	 	{
					int tempc2 = gaps[j].c2;
        	 		gaps[j].c2 = gaps[j].c1 + (x/2) -1;
        	 		gaps[j].size = gaps[j].c2 - gaps[j].c1+1;
        	 		struct cordsize temps;
        	 		temps.c1 = gaps[j].c2 + 1;
        	 		temps.c2 = tempc2;
        	 		temps.size = temp.c2 - temp.c1+1;
        	 		gaps[numavl].c1 = temps.c1;
        	 		gaps[numavl].c2 = temps.c2;
        	 		gaps[numavl].size = temps.size;
        	 		numavl++;
        	 		for(i=0; i<numavl-1;++i) //sort in ascending order
    				{
        				int min=i;
				        for(j=i+1;j<numavl;++j)
				        {
				            if(gaps[min].size>gaps[j].size)
				                min=j;
				        }
				        if(min!=j)
				        {
				            temp=gaps[min];
				            gaps[min]=gaps[i];
				            gaps[i]=temp;

				        }

				    }

				 }

        	 j=0;
        	 continue;
			}
        	else
        	{
        		for(t=gaps[j].c1;t<=gaps[j].c2;t++)
	             {
	                far[t]=1;
    	         }
	             vac = vac + gaps[j].size - x;
	             gaps[j].size=0;
	             printf("Request has been allocated from %d to %d \n",gaps[j].c1,gaps[j].c2);
	             break;
            }
			}

        	else
			{
    			flag = 0;
			}
			j++;
    	}

		}
        if(flag==0)
        {
        	printf("Request of Size %d could not be allocated.",x);
        	flag = 1;
		}
		totreq = totreq + x;
		i++;

	printf("Total Requested Memory: %d \n",totreq);
	printf("Total Available Memory: %d \n",totavl);
	printf("Remaining Requested Memory: %d \n",totreq-altreq);
	printf("Remaining Available Memory: %d \n",vac);
	printf("Resultant Allocation : ");
	for(i=0;i<20;i++)
	{
		printf(" %d ",far[i]);
	}
}

int main()
{	int x;
    printf("---------------MEMORY ALLOCATION PROGRAM--------------- \n\n\n");
    printf("1.Current Memory Status \n2.Create Memory Allocation request\n\n");
    printf("Your Choice: ");
    scanf("%d",&x);
    switch(x)
    {
    	case 1:
    		search();
    		break;
    	case 2:
			fill();
			break;
		default:
			break;

	}
    return 0;
}





