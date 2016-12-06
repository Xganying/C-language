//����У԰����ϵͳ��ע���±�һ�ɴ��㿪ʼ��
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 32767
#define N 100 //���������������

typedef struct 	//�ڽӾ���
{
	float road[N][N];	
	char name[N][20];	
	int num_build;	
	int num_road;			
}AdjMatrix;

struct queue//���У���ȱ�����
{
	int name[N];
	int rear,front;
};

void Map() //ƽ��ͼ
{   
    printf("\n\t\t               ��������ƽ��ͼ\n\n");
    printf("\t*********************************************************\n");
    printf("\t*                       ������                          *\n");
    printf("\t*                              �й�����                 *\n");
    printf("\t*                       ��Ȫ              ����¥        *\n");
    printf("\t*          ��ѧ¥                                       *\n");
    printf("\t*        1��ʵ��¥                ���                  *\n");
    printf("\t*       2��ʵ��¥             ͼ���                    *\n");
    printf("\t*      3��ʵ��¥                                        *\n");
    printf("\t*ϴԡ����                                               *\n");
	printf("\t*                                               ��������*\n");
    printf("\t*ҽ������                                               *\n");
	printf("\t*                                                       *\n");
	printf("\t*                                         ������        *\n");
    printf("\t*��ʳ�㳡       ����                                  *\n");
	printf("\t*                                                       *\n");
    printf("\t*ѧ����Ԣ                 ����Է          ����ѧ����Ԣ  *\n");
	printf("\t*                        ѧ������                       *\n");
	printf("\t*********************************************************\n");
}

void menu()
{
	printf("\n\n\t************��ӭʹ������У԰����ϵͳ***************\n\n");
	printf("\t*          1.У԰����ƽ��ͼ                       *\n");
        printf("\t*          2.����ȱ����㷨�鿴���еص�           *\n");
	printf("\t*          3.�ù�ȱ����㷨�鿴���еص�           *\n");
	printf("\t*          4.��ѯ����ص����Ϣ                   *\n");
	printf("\t*          5.���⾰��֮���ȫ��·��               *\n");
	printf("\t*          6.����ص��·��                       *\n");
	printf("\t*          7.�������ص���Ѳ���                   *\n");
	printf("\t*          8.����㵽�������ص���̾���           *\n");
	printf("\t*          9.�޸������Ϣ                         *\n");
	printf("\t*          10.ɾ�������Ϣ                        *\n");
	printf("\t*          11.�˳�                                *\n");
	printf("\n\t***************************************************\n");
	printf("\n\t����ѡ��:");
}

void init(struct queue *q)	//��ʼ������
{
	q->front=0;
	q->rear=0;
}

int empty(struct queue *q)//�пն�
{
	if(q->front==q->rear)
		return 0;
	else 
		return 1;
}

void push(struct queue *q,int name)	//��Ӳ���
{
	q->name[q->rear]=name;
	q->rear=(q->rear+1)%N;
}

int pop(struct queue *q)//���Ӳ���
{
	int name;
	name=q->name[q->front];
	q->front=(q->front+1)%N;
	return name;
}

int locate(AdjMatrix *G,char *name)//���ݽ�������������ȡ������ı��
{
	int i;
	for(i=0;i<G->num_build;i++)
		if(strcmp(G->name[i],name)==0)
			break;
		return i;
}

AdjMatrix *Create()//�ڽӾ���Ĵ�������ͼ
{
	AdjMatrix *G;
	FILE *fp;	//��·����Ϣ���ļ�
	FILE *fp2;	//�򿪽�������Ϣ���ļ�
	int x,y;
	float weight;
	int i,j;
	int num;
	char temp_name[20];
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	for(i=0;i<N;i++)//��ʼ������
		for(j=0;j<N;j++)
		{
			G->road[i][j]=0;//û��·���Ľ���֮���ȨֵΪ0
		    G->name[0][0]='\0';//û���õ��Ĵ�'\0'
		}
	fp=fopen("1.txt","r");
	if(fp==NULL)
	{
		printf("�ļ��򿪳���!\n");
		exit(1);
	}	
	fscanf(fp,"%d %d",&G->num_build,&G->num_road);
	while(fscanf(fp,"%d %d %f",&x,&y,&weight)!=EOF)	//���ļ��а�·����Ϣ������
	{
		G->road[x-1][y-1]=weight;
		G->road[y-1][x-1]=weight;	//������
	}
	fclose(fp);	
	fp2=fopen("2.txt","r");
	if(fp2==NULL)
	{
		printf("�ļ��򿪳���!\n");
		exit(1);
	}
	while(fscanf(fp2,"%d %s",&num,temp_name)!=EOF)
		strcpy(G->name[num-1],temp_name);
	fclose(fp2);
	return G;
}

int visited[N]={0};//��ʼδ������ȫ��ֵ0

void DFS(AdjMatrix *G,int i)
{
	int j=0;
	printf("%s\n",G->name[i]);
	visited[i]=1;
	while(j<G->num_build)
	{
		if(!visited[j]&&G->road[i][j])
			DFS(G,j);
		j++;
	}
}

void TraverseDFS(AdjMatrix *G)//�ڽӾ������ȱ�������ֹ����ͨͼ��
{
	int i;
	system("cls");//���ǰ������в����Ŀ���̨��Ϣ
	for(i=0;i<G->num_build;i++)
		visited[i]=0;
	for(i=0;i<G->num_build;i++)
		if(!visited[i])
			DFS(G,i);
		system("pause");
}

void bfs(AdjMatrix *G,int i)
{
	int j,k;
	struct queue *q;
	q=(struct queue *)malloc(sizeof(struct queue));
	init(q);
	printf("%s\n",G->name[i]);
	visited[i]=1;
	push(q,i);
	while(empty(q))
	{
		k=pop(q);
		for(j=0;j<G->num_build;j++)
			if(!visited[j]&& G->road[k][j])
			{
				printf("%s\n",G->name[j]);
				visited[j]=1;
				push(q,j);
			}
	}
}

void tbfs(AdjMatrix *G)	//�ڽӾ���Ĺ�ȱ�������ֹ����ͨͼ��
{
	int i;
	system("cls");
	for(i=0;i<G->num_build;i++)
		visited[i]=0;
	for(i=0;i<G->num_build;i++)
		if(!visited[i])
			bfs(G,i);
		system("pause");
}

void find(AdjMatrix *G)//��ѯ
{
	FILE *fp;
	char name[20];
	char introduce[50];
	int i,k,flag;
	system("cls");	//��������
    loop:;
	printf("������ҵĽ�����:");
	scanf("%s",name);
	fp=fopen("3.txt","r");
	if(fp==NULL)
	{
		printf("�ļ��򿪳���\n");
	    exit(1);
	}
	flag=locate(G,name)+1;	//�±���㿪ʼ����+1
    while(fscanf(fp,"%d %s",&k,introduce)!=EOF)
		 if(k==flag)
			 break;
	fclose(fp);
	if(flag>G->num_build)
	{
		 system("cls");	
		 printf("�����ڴ˽�����!(��������)\n");
		 goto loop;
	 }
	else
	{
		printf("  �������ܣ� %s\n",introduce);
		printf("  %s�ܵ��Ĵｨ������:\n",name);
		for(i=0;i<G->num_build;i++)
			if(G->road[flag-1][i])//�±���㿪ʼ�����������ֵ-1
				printf("  %s   ����:%.1f\n",G->name[i],G->road[flag-1][i]);
	}
}

void increase(AdjMatrix *G)//���ӵص��·��
{
	FILE *fp,*fp2,*fp3;		
	int num_b,num_r;
	char name[20];	//�ص�����
	char introduce[50];	//�ص�򵥽���
	float length;	//·������
	char target[20];//Ŀ�ĵ�
	int i,j;
	system("cls");
	num_b=G->num_build;//�ص�����
	num_r=G->num_road;	//·������
	printf("�µĽ�������: ");
    loop:; 
	scanf("%s",name); 
	for(i=0;i<G->num_build;i++)
		if(strcmp(G->name[i],name)==0)
		{
			 system("cls");
			 printf("�����Ѿ�����!(����������һ��)\n");
			 goto loop;
		}
	G->num_build++;//ֻ������һ���ص�
	printf("�򵥽���: ");
	scanf("%s",introduce);
	fp3=fopen("3.txt","at+");//�򵥽����ļ���д��
	if(fp3==NULL)
	{
		printf("�ļ��򿪳���!\n");
	    exit(1);
	}
	fprintf(fp3,"%d %s\n",num_b+1,introduce);
	fclose(fp3);
	fp2=fopen("2.txt","at+");	//�ص����Ƶ�д��
	if(fp2==NULL)
	{
	    printf("�ļ��򿪳���!\n");
		exit(1);
	}
	fprintf(fp2,"%d %s\n",num_b+1,name);
	strcpy(G->name[num_b],name);
	fclose(fp2);
	fp=fopen("1.txt","at+");
	if(fp==NULL)
	{
		 printf("�ļ��򿪳���!\n");
		 exit(1);
	}
	printf("���Ե���Ľ������ơ�·������(����Ϊnoʱ�˳�): ");
	//������ӡ��õص���Ե���ĵص���š��������������ص� ֮����Ե���(���Ե���ĵص���ܲ�����)	 
    loop2:;
	scanf("%s%f",target,&length);
	if(strcmp(target,name)==0)
	  {
		  printf("�Լ����ܵ��Լ�!(����������)\n");
		  goto loop2;
	  }
	  if(locate(G,target)+1>G->num_build)
	  {
		  printf("û������յ㽨��!(����������)\n");
		  goto loop2;
	  }
	  while(strcmp("no",target))
	  {
		  G->road[num_b][locate(G,target)]=length;
		  G->road[locate(G,target)][num_b]=length;
		  G->num_road+=2;//����һ��·����������·��������
          loop3:;
	      printf("���Ե���Ľ������ơ�·������:");
	      scanf("%s%f",target,&length);
	      if(strcmp(target,name)==0)
		  {
		      printf("�Լ����ܵ��Լ�!(����������)\n");
		      goto loop3;
		  }
	      if(strcmp(target,"no")==0)
		     break;
	      if(locate(G,target)+1>G->num_build)
		  {
		      printf("û������յ㽨��!(����������)\n");
		      goto loop3;
		  }
	  }
	  fclose(fp);
	  fp=fopen("1.txt","w");
	  if(fp==NULL)
	  {
		  printf("�ļ��򿪳���!");
		  exit(1);
	  }
	  fprintf(fp,"%d %d\n",G->num_build,G->num_road);
	  for(i=0;i<G->num_build;i++)
		  for(j=0;j<G->num_build;j++)
			  if(G->road[i][j]!=0.0)
				  fprintf(fp,"%d %d %.1f\n",i+1,j+1,G->road[i][j]);	//�±���㿪ʼ����+1
			  fclose(fp);
			  printf("\n���ӳɹ�!\n");
}

void floyd(AdjMatrix *adjrec,int flag_)//���������㷨��Ե����,flag���(0��Ե�,1���ȫ��)
{
	float f[N][N];	//�ڽӾ���(�������յľ����ж�������֮�䵽����·������)
	int path[N][N];	//·������
	int i,j,k;			//ѭ�����Ʊ���
	char start[20],finish[20];	//���,�յ�
	int int_start,int_finish;	//�����ţ��յ����
	int flag=0;
	int all=0;	//���ȫ��ʱʹ��
	system("cls");	
	for(i=0;i<adjrec->num_build;i++)//f[][]Ϊ�Գƾ���
		for(j=0;j<adjrec->num_build;j++)
			if(adjrec->road[i][j]==0)
			{
				f[i][j]=MAX;
				path[i][j]=-1;
			}
			else
			{
				f[i][j]=adjrec->road[i][j];
				path[i][j]=j;
			}	
			printf("�������: ");
     loop:;
	 scanf("%s",start);
	 int_start=locate(adjrec,start);
	 if(int_start>=adjrec->num_build)
	 {
		 system("cls");
		 printf("û���������!(����������)\n");
		 goto loop;
	 }
	 if(flag_==0)
	 {
		 printf("�����յ�: ");
      loop2:;
      scanf("%s",finish);
	  int_finish=locate(adjrec,finish);
	  if(int_finish>=adjrec->num_build)
	  {
		  printf("û���������!(����������)\n");
		  goto loop2;
	  }
	 }
	 for(k=0;k<adjrec->num_build;k++)	
		 for(i=0;i<adjrec->num_build;i++)
			 for(j=0;j<adjrec->num_build;j++)
				 if(f[i][j]>(f[i][k]+f[k][j]))
				 {
					 f[i][j]=f[i][k]+f[k][j];
					 path[i][j]=path[i][k];
				 }
				 switch(flag_)	
				 {
				 case 0:	
					 {
						 if(f[int_start][int_finish]==MAX)
						 {
							 printf("û��·������!\n");
							 exit(1);
						 }
						 printf("�����յ���̾���Ϊ:%.1fm\n��Ѳ���·��Ϊ: %s  ",f[int_start][int_finish],adjrec->name[int_start]);
						 k=path[int_start][int_finish];
						 while(k!=int_finish)
						 {
							 printf("%s  ",adjrec->name[k]);
							 k=path[k][int_finish];
						 }
						 printf("%s\n",adjrec->name[int_finish]);	
					 }break;
				 case 1:
					 {
						 for(all=0;all<adjrec->num_build;all++)
						 {
							 if(f[int_start][all]==MAX)
							 {
								 printf("<%s>�޷�����<%s>!\n\n",adjrec->name[int_start],adjrec->name[all]);
								 continue;
							 }
							 if(all!=int_start)
							 {
								 printf("���·��:%.1f\n�߷�:%s  ",f[int_start][all],adjrec->name[int_start]);
								 k=path[int_start][all];
								 while(k!=all)
								 {
									 printf("%s  ",adjrec->name[k]);
									 k=path[k][all];
								 }		 
								 printf("%s\n\n",adjrec->name[all]);	 
							 }
						 }
						 
					 }break;
				 }
}

int path_[MAX];	//��·������
int top=-1;	//����ջ��ָ��

void all_path(AdjMatrix *G,int start,int end)//ȫ��·��
{
	int v,i;
	top++;
	path_[top]=start;
	visited[start]=1;
	if(start==end)
	{
		for(i=0;i<=top;i++)
			printf("%s   ",G->name[path_[i]]);
		printf("\n\n\n",i+1);
		visited[start]=0;
		top--;
		return ;
	}
	for(v=0;v<G->num_build;v++)
	{
		if(!visited[v]&&G->road[start][v]!=0) 
			all_path(G,v,end);
	}
	visited[end]=0;
	top--;
}

void path(AdjMatrix *G)//�����ȫ��·��
{
	char name1[20],name2[20]; 
	int start,end,i;	//���,�յ㽨��
	system("cls");	
	for(i=0;i<G->num_build;i++)//��ʼ��
		visited[i]=0;
    loop:;
	printf("���������:  ");
	gets(name1);
	start=locate(G,name1);
	if(start+1>G->num_build)
	{
		system("cls");
		printf("û�д˽���!(����������)\n");
		goto loop;
	}
    loop2:;
	printf("�������յ�:  ");
	gets(name2);
	end=locate(G,name2);
	if(end+1>G->num_build)
	{    
		 system("cls");
		 printf("û�д˽���!(��������)\n");
		 goto loop2;
	}  
	printf("\n��%s��%s������·��Ϊ:\n\n",name1,name2);
	all_path(G,start,end);  
}

void modify_introduce(AdjMatrix *adjrec)//�������ܵ��޸�
{
	FILE *fp;
	char build_name[20];	//��������
	char introduce[50];	//��������
	char all_introduce[N][50];//ȫ���Ľ�������
	int i;
	fp=fopen("3.txt","r");
	if(fp==NULL)
	{
		printf("�ļ��򿪳���!\n");
		exit(1);
	}	
	while(!feof(fp))
	{
		fscanf(fp,"%d %s",&i,introduce);
		strcpy(all_introduce[i-1],introduce);
	}
	fclose(fp);	
	system("cls");	
	printf("����ص�����: ");
    loop:;
	 scanf("%s",build_name);
	 i=locate(adjrec,build_name);
	 if(i>=adjrec->num_build)
	 {
		 system("cls");
		 printf("�޴˵ص�!(����������)\n");
		 goto loop;
	 }
	 printf("ԭ���Ľ�������: %s\n",all_introduce[i]);
	 printf("�����µĽ�������: ");
	 scanf("%s",introduce);
	 strcpy(all_introduce[i],introduce);	 
	 fp=fopen("3.txt","w");
	 if(fp==NULL)
	 {
		 printf("�ļ��򿪳���!\n");
		 exit(1);
	 }
	 for(i=0;i<adjrec->num_build;i++)
		 fprintf(fp,"%d %s\n",i+1,all_introduce[i]);
	 printf("\n�޸ĳɹ�!\n");	 
	 fclose(fp);
}

void modify_name(AdjMatrix *G)//�������Ƶ��޸�
{
	FILE *fp;
	char name[20];
	int num,i;	
	system("cls");	
	printf("�����޸ĵĽ����������: ");
   loop:;
	 scanf("%s",name);
	 num=locate(G,name);
	 if(num>=G->num_build)
	 {
		 system("cls");
		 printf("�޴˽���!(����������)\n");
		 goto loop;
	 }	 
	 printf("�����޸ĺ������: ");
	 scanf("%s",name);
	 strcpy(G->name[num],name);
	 fp=fopen("2.txt","w");
	 if(fp==NULL)
	 {
		 printf("�ļ��򿪳���!\n");
		 exit(1);
	 }	 
	 for(i=0;i<G->num_build;i++)
		 fprintf(fp,"%d %s\n",i+1,G->name[i]);
	 printf("�޸ĳɹ�!\n");
	 fclose(fp);	 
}

void modify_length(AdjMatrix *adjrec)  //�޸�·������
{
	FILE *fp;
	float length;
	char name_start[20];	//·�����
	char name_end[20];	//·���յ�
	int i,j;	
	system("cls");	
	printf("����·�����: ");
    loop:;
	 scanf("%s",name_start);
	 if(locate(adjrec,name_start)>=adjrec->num_build)
	 {
		 system("cls");
		 printf("�޴˽���!(����������)\n");
		 goto loop;
	 }	 
	 printf("����·���յ�: ");
     loop2:;
	  scanf("%s",name_end);
	  if(locate(adjrec,name_end)>=adjrec->num_build)
	  {
		  printf("�޴˽���!(����������)\n");
		  goto loop2;
	  }  
	  adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]!=0?printf("ԭ·������:%.1f\n",adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]):0;
	  if(adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]==0)//����·������Ϊ0,�޸�Ϊ��0������������·��
		  adjrec->num_road=adjrec->num_road+2;
	  printf("�����µ�·������: ");
      loop3:;
 	  scanf("%f",&length);
	  if(length<0)
	  {
		  printf("·�����Ȳ���Ϊ��ֵ!(����������)\n");
		  goto loop3;
	  }  
	  adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]=length;
	  adjrec->road[locate(adjrec,name_end)][locate(adjrec,name_start)]=length;
	  
	  fp=fopen("1.txt","w");
	  if(fp==NULL)
	  {
		  printf("�ļ��򿪳���!\n");
		  exit(1);
	  } 
	  fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);
	  for(i=0;i<adjrec->num_build;i++)
		  for(j=0;j<adjrec->num_build;j++)
			  adjrec->road[i][j]!=0?fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]):1;
		  printf("�޸ĳɹ�!\n");
		  fclose(fp);
		  
}

void modify(AdjMatrix *adjrec)	//�޸ĸ�����Ϣ
{
	int choice1;
	char choice2;//ѡ��	
    loop:fflush(stdin);
	 while(1)
	 {
		 printf("\n\t1,��������\n\t2,��������\n\t3,·������\n\t4,�˳��޸�\n");
		 printf("\n\tѡ���޸���һ����  ");
		 scanf("%d",&choice1);
		 fflush(stdin);
		 switch(choice1)
		 {
		 case 1: modify_introduce(adjrec);break;
		 case 2: modify_name(adjrec);     break;
		 case 3: modify_length(adjrec);   break;
		 case 4: goto loop2;			  break;
		 default:
			 {
			     system("cls");
			     printf("��������!(����������)!\n");
			     goto loop;
			 }break;
		 }
		 printf("��Ҫ�����޸Ĺ�����(y/n)��");
		 fflush(stdin);
		 scanf("%c",&choice2);
		 if(choice2=='n')
			 break;
		 else
			 system("cls");
	 }
     loop2:;
}

void cut_build(AdjMatrix *adjrec)//ɾ��������Ϣ
{
	char name[20];
	FILE *fp;
	int number;
	int i,j;
	int flag=0;	//��¼��֮��ص�·������
	int temp;//û���ô�������ȡ�ļ�
	char introduce[N][50];//���������ַ�������
	char introduce_[50];	
	system("cls");	
	printf("����ص�����: ");
    loop:;
	 scanf("%s",name);
	 number=locate(adjrec,name);
	 if(number>=adjrec->num_build)
	 {
		 system("cls");
		 printf("�޴˵ص�!(����������)\n");
		 goto loop;
	 }
	 adjrec->name[number][0]='\0';//�����������ÿ�
	 for(i=0;i<adjrec->num_build;i++)//·��������
	 {
		 if(adjrec->road[number][i]!=0)
		 {
			 adjrec->road[number][i]=0;
			 flag++;
		 }
		 if(adjrec->road[i][number]!=0)
		 {
			 adjrec->road[i][number]=0;
			 flag++;
		 }
		 introduce[i][0]='\0';
	 } 
	 fp=fopen("3.txt","r");//���������ļ��ĸ���
	 if(fp==NULL)
	 {
		 printf("�ļ��򿪳���!\n");
		 exit(1);
	 }
	 for(i=0;i<adjrec->num_build;i++)
	 {
		 fscanf(fp,"%d %s",&temp,introduce_);
		 if(temp-1!=number)
			 strcpy(introduce[temp-1],introduce_);
	 }	 
	 fclose(fp);
	 if(number+1==adjrec->num_build)
		 adjrec->num_build=adjrec->num_build-1;//�����������仯 
	 adjrec->num_road=adjrec->num_road-flag;//·���������仯
	 fp=fopen("1.txt","w");//���ľ����ļ�
	 if(fp==NULL)
	 {
		 printf("�ļ�������!\n");
		 exit(1);
	 }
	 fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);	 
	 for(i=0;i<adjrec->num_build;i++)
		 for(j=0;j<adjrec->num_build;j++)
			 if(adjrec->road[i][j]!=0)
				 fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]);		 
			 fclose(fp);
			 fp=fopen("2.txt","w"); //���Ľ��������ļ�
			 if(fp==NULL)
			 {
				 printf("�ļ�������!\n");
				 exit(1);
			 }
			 for(i=0;i<adjrec->num_build;i++)
				 if(adjrec->name[i][0]!='\0')
					 fprintf(fp,"%d %s\n",i+1,adjrec->name[i]); 
			 fclose(fp);
				 fp=fopen("3.txt","w");//���Ľ��������ļ�
				 if(fp==NULL)
				 {
					 printf("�ļ��򿪳���!\n");
					 exit(1);
				 }
				 for(i=0;i<adjrec->num_build;i++)
					 if(introduce[i][0]!='\0')
						 fprintf(fp,"%d %s\n",i+1,introduce[i]);
					 fclose(fp);	 
					 printf("\nɾ���ɹ�!\n");
}

void cut_road(AdjMatrix *adjrec)//ɾ��·��
{
	FILE *fp;
	char name_build[20];
	int start,end;	//·����㣬�յ�
	int i,j;
	system("cls");
    loop3:;
	  printf("�����ɾ��·�������: ");
    loop:;
	 scanf("%s",name_build);
	 start=locate(adjrec,name_build);
	 if(start>=adjrec->num_build)
	 {
		 system("cls");
		 printf("�޴˽���!(����������)\n");
		 goto loop;
	 }
	 printf("�����ɾ��·�����յ�:  ");
     loop2:;
	  scanf("%s",name_build);
	  end=locate(adjrec,name_build);
	  if(end==start)
	  {
		  system("cls");
		  printf("�Լ��޷��ﵽ�Լ�!(���������������յ�)\n");
		  goto loop3;
	  }
	  if(end>=adjrec->num_build)
	  {
		  printf("�޴˽���!(����������)\n");
		  goto loop2;
	  }
	  if(adjrec->road[start][end]==0.0)
	  {
		  printf("\n�������û��·��!\n");
		  return ;
	  }
	  else
	  {
		  printf("<%s>��<%s>��·������Ϊ: %.1f\n",adjrec->name[start],adjrec->name[end],adjrec->road[start][end]);
		  adjrec->road[start][end]=adjrec->road[end][start]=0;
		  adjrec->num_road-=2;//����ͼ ɾ������·��
		  fp=fopen("1.txt","w");
		  if(fp==NULL)
		  {
			  printf("\n�ļ��򿪳���!\n");
			  exit(1);
		  }
		  fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);
		  for(i=0;i<adjrec->num_build;i++)
			  for(j=0;j<adjrec->num_build;j++)
				  if(adjrec->road[i][j]!=0)
					  fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]);
				  fclose(fp);
				  printf("\nɾ���ɹ�!\n");
	  }  
}

void cut(AdjMatrix *adjrec)//ɾ��������Ϣ
{
	int choice;
	char choice_;
    loop:fflush(stdin); 
	while(1)
	 {
		 printf("\t1������\n\t2��·��\n\t3���˳�ɾ��\n\n");
		 printf("\tɾ����һ����( )\b\b");
		 scanf("%d",&choice);
		 switch(choice)
		 {
		 case 1: cut_build(adjrec);	break;
		 case 2: cut_road(adjrec);  break;
		 case 3: goto loop2;		break;
		 default: 
			 {
				 system("cls");
				 printf("ָ������!(����������!)\n");
				 goto loop;
			 }
		 } 
		 printf("\n��Ҫ����ɾ����(y/n)");
		 fflush(stdin);
		 scanf("%c",&choice_);
		 if(choice_=='n')
			 break;
		 else
			 system("cls");
	 }	 
     loop2:;
}

int main(void)
{
	AdjMatrix *G;	//�����ڽӾ���
	int choice1;	//��ʼѡ��
	char choice2;	//����ѡ��
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	G=Create();	//�ڽӾ���Ĵ���
	system("color 75");
	while(1)
	{
		menu();
        loop:;
	    scanf("%d",&choice1);
	    switch(choice1)
		{
		 case 1:system("cls"); Map();break;
	     case 2:system("cls"); TraverseDFS(G);	break;	//�ڽӾ������ȱ���
	     case 3:system("cls"); tbfs(G);	break;	//�ڽӾ���Ĺ�ȱ���
	     case 4:system("cls"); find(G);	break;	//��ѯ���������Ϣ
	     case 5:system("cls"); path(G);	break;	//������֮��ȫ��·��
	     case 6:system("cls"); increase(G);break;	//���ӽ�����·��
	     case 7:system("cls"); floyd(G,0);	break;	//���������㷨��Ե����
	     case 8:system("cls"); floyd(G,1);	break;	//���������㷨�������ȫ�����
	     case 9:system("cls"); modify(G);	break;	//�޸ĸ�����Ϣ
	     case 10:system("cls"); cut(G);		break;	//ɾ��������Ϣ
	     case 11: printf("\n\t\t��лʹ�ñ�ϵͳ!\n\n\n");exit(1); 	break;	//�˳�ȫ��
	     default:
			 {
			    printf("ָ�����!(����������)\n"); 
			    fflush(stdin);	//�建����
			    goto loop;
			 }break;
		}
	    printf("����ʹ�ô�ϵͳ��(y/n)");
	    fflush(stdin);	
	    scanf("%c",&choice2);
	    if(choice2=='n')
		    break;
	    else
		    system("cls");
	}
	return 0;
}














