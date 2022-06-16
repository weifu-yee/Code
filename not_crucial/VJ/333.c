#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m, i,input,tempt,j;
	scanf("%d", &n,&m);
	int v[n];
	v[0] = 1;
    for (i = 1; i < n; i++)
	    {
		 v[i] = v[i-1] + 1;
	    }

   for(int k = 0; k < m; k++)
    {
    scanf("%d", &input);
    for(i=0;i<n;i++)
       if(input==v[i])
        {
           tempt=v[i];
           for(m=0;m<i;m++)
           {
               v[m+1]=v[m];
           }
           v[0]=tempt;
           break;
        }
    }

    for(i=0;i<n;i++)
    {
        printf("%d", v[i]);
        printf("\n");
    }


   return 0;

}