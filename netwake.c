#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char* argv[])
{
	if(argc<3 || !strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))
	{
		printf("netwake: usage: netwake [MAC Address(aa:bb:cc:dd:ee:ff)] [IP Address] [addtional options...]\n");
		printf("\t-b [Boardcast Address]\n");
		printf("\t-c Number of packets will be sent default: 4\n");
		printf("\t-h display this help\n");
		exit(0); 
	}
	/*var defination*/
	FILE *fp=NULL;
	int count=4;
	char bc_addr[255];
	char ip_addr[255];
	int mac[6]; 
	/*process flags*/
	for(int i=0;i<argc;i++)
	{
		//printf(argv[i]);
		if(strstr(argv[i],"-b"))	strcpy(bc_addr,strstr(argv[i],"-b")+strlen("-b")+1);
		if(strstr(argv[i],"-c"))	sscanf(strstr(argv[i],"-c")+strlen("-c")+1,"%d",&count);
	}
	strcpy(ip_addr,argv[2]);
	sscanf(argv[1],"%x:%x:%x:%x:%x:%x",mac,mac+1,mac+2,mac+3,mac+4,mac+5);
	//exit(0);
	/*generate magic package*/
	if((fp=fopen("/tmp/magicpkg","wb+"))==NULL)
	{
		printf("create magic package failed,please check /tmp\n");
	}
	char blank=0xff;
	for(int j=0;j<6;j++)	fwrite(&blank,sizeof(char),1,fp);
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<6;j++)
		{
			fwrite(mac+j,sizeof(char),1,fp);
		}
	}
	fclose(fp);
	/*send magic package*/	
	for(int i=0;i<count;i++)
	{
		char cmd[512];
		sprintf(cmd,"%s%s%s","cat /tmp/magicpkg | nc -u ",ip_addr," 9 &");
		system(cmd);
		//printf(cmd);
		if(strlen(bc_addr))	
		{
			sprintf(cmd,"%s%s%s","cat /tmp/magicpkg | nc -u -b ",bc_addr," 9 &");
			system(cmd);
			//printf(cmd);
		}
	}
	system("killall nc");
	//printf("killall nc");
	printf("\n remote computer started successfully!\n");
	return 0;
} 
