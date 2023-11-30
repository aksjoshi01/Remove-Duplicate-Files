#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LSIZ 128
#define RSIZ 10
struct filename
{
	char fname[50];
	int length;
};

typedef struct filterfile
{
	char filename[50];
	int status;
}FF;

int comparelinebyline(char a[20],char b[20])
{
    char line[RSIZ][LSIZ];
    char LINE[RSIZ][LSIZ];
    FILE *fptr = NULL,*FPTR=NULL;
    int i = 0,I=0;
    int tot = 0,TOT=0;
    fptr = fopen(a, "r");
    while(fgets(line[i], LSIZ, fptr))
{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;

    FPTR=fopen(b,"r");
    while(fgets(LINE[I], LSIZ, FPTR))
{
        LINE[I][strlen(LINE[I]) - 1] = '\0';
        I++;
    }
    TOT = I;

    if(tot=TOT)
    {
        int flag=0;
        for(i=0,I=0;i<tot;i++)
        {
            if(strcmp(line[i],LINE[I])!=0)
            flag=1;
            I++;
        }
        if(flag==1)
            return 1;
        else
            return 0;

    }
}

int main()
{
	struct filename arr[10];
	FF filter[10];
	int n = -1;
	int m = -1;
	DIR *d;
	struct dirent *dp;
	d = opendir(".");
	if(d == NULL)
	{
		perror("");
	}
	else
	{
		printf("Files present in the directory: \n");
		for(;;)
		{
			dp = readdir(d);
			if(dp == NULL)
				break;
			n++;
			strcpy(arr[n].fname,dp->d_name);
			arr[n].length = strlen(arr[n].fname);
			printf("%d\t",arr[n].length);
		}
		printf("\n");
		closedir(d);
	}

	for(int i=0; i<=n; i++)
	{
		printf("%s\t",arr[i].fname);
	}

	for(int i=0; i<=n; i++)
	{
		if(arr[i].fname[arr[i].length - 1] == 116)
		{
			if(arr[i].fname[arr[i].length - 2] == 120)
			{
				if(arr[i].fname[arr[i].length - 3] == 116)
        			{
            				if(arr[i].fname[arr[i].length - 4] == 46)
            				{
                 				m++;
                 				strcpy(filter[m].filename,arr[i].fname);
                 				filter[m].status=0;
            				}
        			}
    			}
		}
	}
	printf("\n\nText files present in the directory:\n");
	for(int i=0; i<=m; i++)
	{
		printf("%s\n",filter[i].filename);
	}
	for(int i=0;i<=m;i++)
	{
	    if(filter[i].status==1)
                continue;
		for(int j=0;j<=m;j++)
        {
            if(i==j)
                continue;
            filter[j].status=comparelinebyline(filter[i].filename,filter[j].filename);

        }
	}
	for(int i=0;i<=m;i++)
    {
        if(filter[i].status==1)
            remove(filter[i].filename);
    }


	return 0;
}

