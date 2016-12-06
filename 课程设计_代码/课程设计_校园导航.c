//西邮校园导航系统（注：下标一律从零开始）
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 32767
#define N 100 //建筑物的上限数量

typedef struct 	//邻接矩阵
{
	float road[N][N];	
	char name[N][20];	
	int num_build;	
	int num_road;			
}AdjMatrix;

struct queue//队列（广度遍历）
{
	int name[N];
	int rear,front;
};

void Map() //平面图
{   
    printf("\n\t\t               西区大致平面图\n\n");
    printf("\t*********************************************************\n");
    printf("\t*                       北大门                          *\n");
    printf("\t*                              中国邮政                 *\n");
    printf("\t*                       喷泉              行政楼        *\n");
    printf("\t*          教学楼                                       *\n");
    printf("\t*        1号实验楼                大活                  *\n");
    printf("\t*       2号实验楼             图书馆                    *\n");
    printf("\t*      3号实验楼                                        *\n");
    printf("\t*洗浴中心                                               *\n");
	printf("\t*                                               西区东门*\n");
    printf("\t*医疗中心                                               *\n");
	printf("\t*                                                       *\n");
	printf("\t*                                         体育馆        *\n");
    printf("\t*美食广场       篮球场                                  *\n");
	printf("\t*                                                       *\n");
    printf("\t*学生公寓                 旭日苑          西区学生公寓  *\n");
	printf("\t*                        学生超市                       *\n");
	printf("\t*********************************************************\n");
}

void menu()
{
	printf("\n\n\t************欢迎使用西邮校园导航系统***************\n\n");
	printf("\t*          1.校园大致平面图                       *\n");
        printf("\t*          2.用深度遍历算法查看所有地点           *\n");
	printf("\t*          3.用广度遍历算法查看所有地点           *\n");
	printf("\t*          4.查询任意地点的信息                   *\n");
	printf("\t*          5.任意景点之间的全部路径               *\n");
	printf("\t*          6.增添地点和路径                       *\n");
	printf("\t*          7.任意两地点最佳布线                   *\n");
	printf("\t*          8.任意点到达其他地点最短距离           *\n");
	printf("\t*          9.修改相关信息                         *\n");
	printf("\t*          10.删除相关信息                        *\n");
	printf("\t*          11.退出                                *\n");
	printf("\n\t***************************************************\n");
	printf("\n\t键入选择:");
}

void init(struct queue *q)	//初始化队列
{
	q->front=0;
	q->rear=0;
}

int empty(struct queue *q)//判空队
{
	if(q->front==q->rear)
		return 0;
	else 
		return 1;
}

void push(struct queue *q,int name)	//入队操作
{
	q->name[q->rear]=name;
	q->rear=(q->rear+1)%N;
}

int pop(struct queue *q)//出队操作
{
	int name;
	name=q->name[q->front];
	q->front=(q->front+1)%N;
	return name;
}

int locate(AdjMatrix *G,char *name)//根据建筑的名字来获取建筑物的编号
{
	int i;
	for(i=0;i<G->num_build;i++)
		if(strcmp(G->name[i],name)==0)
			break;
		return i;
}

AdjMatrix *Create()//邻接矩阵的创建无向图
{
	AdjMatrix *G;
	FILE *fp;	//打开路径信息的文件
	FILE *fp2;	//打开建筑物信息的文件
	int x,y;
	float weight;
	int i,j;
	int num;
	char temp_name[20];
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	for(i=0;i<N;i++)//初始化矩阵
		for(j=0;j<N;j++)
		{
			G->road[i][j]=0;//没有路径的建筑之间的权值为0
		    G->name[0][0]='\0';//没有用到的存'\0'
		}
	fp=fopen("1.txt","r");
	if(fp==NULL)
	{
		printf("文件打开出错!\n");
		exit(1);
	}	
	fscanf(fp,"%d %d",&G->num_build,&G->num_road);
	while(fscanf(fp,"%d %d %f",&x,&y,&weight)!=EOF)	//从文件中把路径信息读出来
	{
		G->road[x-1][y-1]=weight;
		G->road[y-1][x-1]=weight;	//无向网
	}
	fclose(fp);	
	fp2=fopen("2.txt","r");
	if(fp2==NULL)
	{
		printf("文件打开出错!\n");
		exit(1);
	}
	while(fscanf(fp2,"%d %s",&num,temp_name)!=EOF)
		strcpy(G->name[num-1],temp_name);
	fclose(fp2);
	return G;
}

int visited[N]={0};//初始未被访问全赋值0

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

void TraverseDFS(AdjMatrix *G)//邻接矩阵的深度遍历（防止非连通图）
{
	int i;
	system("cls");//清空前面的所有残留的控制台信息
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

void tbfs(AdjMatrix *G)	//邻接矩阵的广度遍历（防止非连通图）
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

void find(AdjMatrix *G)//查询
{
	FILE *fp;
	char name[20];
	char introduce[50];
	int i,k,flag;
	system("cls");	//清屏函数
    loop:;
	printf("输入查找的建筑物:");
	scanf("%s",name);
	fp=fopen("3.txt","r");
	if(fp==NULL)
	{
		printf("文件打开出错！\n");
	    exit(1);
	}
	flag=locate(G,name)+1;	//下标从零开始，故+1
    while(fscanf(fp,"%d %s",&k,introduce)!=EOF)
		 if(k==flag)
			 break;
	fclose(fp);
	if(flag>G->num_build)
	{
		 system("cls");	
		 printf("不存在此建筑物!(重新输入)\n");
		 goto loop;
	 }
	else
	{
		printf("  建筑介绍： %s\n",introduce);
		printf("  %s能到的达建筑物有:\n",name);
		for(i=0;i<G->num_build;i++)
			if(G->road[flag-1][i])//下标从零开始，结束于最大值-1
				printf("  %s   距离:%.1f\n",G->name[i],G->road[flag-1][i]);
	}
}

void increase(AdjMatrix *G)//增加地点和路径
{
	FILE *fp,*fp2,*fp3;		
	int num_b,num_r;
	char name[20];	//地点名称
	char introduce[50];	//地点简单介绍
	float length;	//路径长度
	char target[20];//目的地
	int i,j;
	system("cls");
	num_b=G->num_build;//地点数量
	num_r=G->num_road;	//路径数量
	printf("新的建筑名称: ");
    loop:; 
	scanf("%s",name); 
	for(i=0;i<G->num_build;i++)
		if(strcmp(G->name[i],name)==0)
		{
			 system("cls");
			 printf("建筑已经存在!(请重新输入一个)\n");
			 goto loop;
		}
	G->num_build++;//只增加了一个地点
	printf("简单介绍: ");
	scanf("%s",introduce);
	fp3=fopen("3.txt","at+");//简单介绍文件的写回
	if(fp3==NULL)
	{
		printf("文件打开出错!\n");
	    exit(1);
	}
	fprintf(fp3,"%d %s\n",num_b+1,introduce);
	fclose(fp3);
	fp2=fopen("2.txt","at+");	//地点名称的写回
	if(fp2==NULL)
	{
	    printf("文件打开出错!\n");
		exit(1);
	}
	fprintf(fp2,"%d %s\n",num_b+1,name);
	strcpy(G->name[num_b],name);
	fclose(fp2);
	fp=fopen("1.txt","at+");
	if(fp==NULL)
	{
		 printf("文件打开出错!\n");
		 exit(1);
	}
	printf("可以到达的建筑名称、路经长度(名称为no时退出): ");
	//后面添加“该地点可以到达的地点序号”连续加入两个地点 之间可以到达(可以到达的地点可能不存在)	 
    loop2:;
	scanf("%s%f",target,&length);
	if(strcmp(target,name)==0)
	  {
		  printf("自己不能到自己!(请重新输入)\n");
		  goto loop2;
	  }
	  if(locate(G,target)+1>G->num_build)
	  {
		  printf("没有这个终点建筑!(请重新输入)\n");
		  goto loop2;
	  }
	  while(strcmp("no",target))
	  {
		  G->road[num_b][locate(G,target)]=length;
		  G->road[locate(G,target)][num_b]=length;
		  G->num_road+=2;//增加一条路径，即两条路，无向网
          loop3:;
	      printf("可以到达的建筑名称、路经长度:");
	      scanf("%s%f",target,&length);
	      if(strcmp(target,name)==0)
		  {
		      printf("自己不能到自己!(请重新输入)\n");
		      goto loop3;
		  }
	      if(strcmp(target,"no")==0)
		     break;
	      if(locate(G,target)+1>G->num_build)
		  {
		      printf("没有这个终点建筑!(请重新输入)\n");
		      goto loop3;
		  }
	  }
	  fclose(fp);
	  fp=fopen("1.txt","w");
	  if(fp==NULL)
	  {
		  printf("文件打开出错!");
		  exit(1);
	  }
	  fprintf(fp,"%d %d\n",G->num_build,G->num_road);
	  for(i=0;i<G->num_build;i++)
		  for(j=0;j<G->num_build;j++)
			  if(G->road[i][j]!=0.0)
				  fprintf(fp,"%d %d %.1f\n",i+1,j+1,G->road[i][j]);	//下标从零开始，故+1
			  fclose(fp);
			  printf("\n增加成功!\n");
}

void floyd(AdjMatrix *adjrec,int flag_)//弗洛伊德算法点对点最短,flag标记(0点对点,1点对全部)
{
	float f[N][N];	//邻接矩阵(利用最终的矩阵判断两建筑之间到底有路径可走)
	int path[N][N];	//路径矩阵
	int i,j,k;			//循环控制变量
	char start[20],finish[20];	//起点,终点
	int int_start,int_finish;	//起点序号，终点序号
	int flag=0;
	int all=0;	//点对全部时使用
	system("cls");	
	for(i=0;i<adjrec->num_build;i++)//f[][]为对称矩阵
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
			printf("键入起点: ");
     loop:;
	 scanf("%s",start);
	 int_start=locate(adjrec,start);
	 if(int_start>=adjrec->num_build)
	 {
		 system("cls");
		 printf("没有这个建筑!(请重新输入)\n");
		 goto loop;
	 }
	 if(flag_==0)
	 {
		 printf("键入终点: ");
      loop2:;
      scanf("%s",finish);
	  int_finish=locate(adjrec,finish);
	  if(int_finish>=adjrec->num_build)
	  {
		  printf("没有这个建筑!(请重新输入)\n");
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
							 printf("没有路径可走!\n");
							 exit(1);
						 }
						 printf("起点和终点最短距离为:%.1fm\n最佳布线路径为: %s  ",f[int_start][int_finish],adjrec->name[int_start]);
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
								 printf("<%s>无法到达<%s>!\n\n",adjrec->name[int_start],adjrec->name[all]);
								 continue;
							 }
							 if(all!=int_start)
							 {
								 printf("最短路径:%.1f\n走法:%s  ",f[int_start][all],adjrec->name[int_start]);
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

int path_[MAX];	//存路径数组
int top=-1;	//类似栈顶指针

void all_path(AdjMatrix *G,int start,int end)//全部路径
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

void path(AdjMatrix *G)//两点间全部路径
{
	char name1[20],name2[20]; 
	int start,end,i;	//起点,终点建筑
	system("cls");	
	for(i=0;i<G->num_build;i++)//初始化
		visited[i]=0;
    loop:;
	printf("请输入起点:  ");
	gets(name1);
	start=locate(G,name1);
	if(start+1>G->num_build)
	{
		system("cls");
		printf("没有此建筑!(请重新输入)\n");
		goto loop;
	}
    loop2:;
	printf("请输入终点:  ");
	gets(name2);
	end=locate(G,name2);
	if(end+1>G->num_build)
	{    
		 system("cls");
		 printf("没有此建筑!(重新输入)\n");
		 goto loop2;
	}  
	printf("\n从%s到%s的所有路径为:\n\n",name1,name2);
	all_path(G,start,end);  
}

void modify_introduce(AdjMatrix *adjrec)//建筑介绍的修改
{
	FILE *fp;
	char build_name[20];	//建筑名称
	char introduce[50];	//建筑介绍
	char all_introduce[N][50];//全部的建筑介绍
	int i;
	fp=fopen("3.txt","r");
	if(fp==NULL)
	{
		printf("文件打开出错!\n");
		exit(1);
	}	
	while(!feof(fp))
	{
		fscanf(fp,"%d %s",&i,introduce);
		strcpy(all_introduce[i-1],introduce);
	}
	fclose(fp);	
	system("cls");	
	printf("键入地点名称: ");
    loop:;
	 scanf("%s",build_name);
	 i=locate(adjrec,build_name);
	 if(i>=adjrec->num_build)
	 {
		 system("cls");
		 printf("无此地点!(请重新输入)\n");
		 goto loop;
	 }
	 printf("原来的建筑介绍: %s\n",all_introduce[i]);
	 printf("键入新的建筑介绍: ");
	 scanf("%s",introduce);
	 strcpy(all_introduce[i],introduce);	 
	 fp=fopen("3.txt","w");
	 if(fp==NULL)
	 {
		 printf("文件打开出错!\n");
		 exit(1);
	 }
	 for(i=0;i<adjrec->num_build;i++)
		 fprintf(fp,"%d %s\n",i+1,all_introduce[i]);
	 printf("\n修改成功!\n");	 
	 fclose(fp);
}

void modify_name(AdjMatrix *G)//建筑名称的修改
{
	FILE *fp;
	char name[20];
	int num,i;	
	system("cls");	
	printf("键入修改的建筑物的名称: ");
   loop:;
	 scanf("%s",name);
	 num=locate(G,name);
	 if(num>=G->num_build)
	 {
		 system("cls");
		 printf("无此建筑!(请重新输入)\n");
		 goto loop;
	 }	 
	 printf("键入修改后的名称: ");
	 scanf("%s",name);
	 strcpy(G->name[num],name);
	 fp=fopen("2.txt","w");
	 if(fp==NULL)
	 {
		 printf("文件打开出错!\n");
		 exit(1);
	 }	 
	 for(i=0;i<G->num_build;i++)
		 fprintf(fp,"%d %s\n",i+1,G->name[i]);
	 printf("修改成功!\n");
	 fclose(fp);	 
}

void modify_length(AdjMatrix *adjrec)  //修改路径长度
{
	FILE *fp;
	float length;
	char name_start[20];	//路径起点
	char name_end[20];	//路径终点
	int i,j;	
	system("cls");	
	printf("键入路径起点: ");
    loop:;
	 scanf("%s",name_start);
	 if(locate(adjrec,name_start)>=adjrec->num_build)
	 {
		 system("cls");
		 printf("无此建筑!(请重新输入)\n");
		 goto loop;
	 }	 
	 printf("键入路径终点: ");
     loop2:;
	  scanf("%s",name_end);
	  if(locate(adjrec,name_end)>=adjrec->num_build)
	  {
		  printf("无此建筑!(请重新输入)\n");
		  goto loop2;
	  }  
	  adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]!=0?printf("原路径长度:%.1f\n",adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]):0;
	  if(adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]==0)//本来路径长度为0,修改为非0等于增加两条路径
		  adjrec->num_road=adjrec->num_road+2;
	  printf("键入新的路径长度: ");
      loop3:;
 	  scanf("%f",&length);
	  if(length<0)
	  {
		  printf("路径长度不能为负值!(请重新输入)\n");
		  goto loop3;
	  }  
	  adjrec->road[locate(adjrec,name_start)][locate(adjrec,name_end)]=length;
	  adjrec->road[locate(adjrec,name_end)][locate(adjrec,name_start)]=length;
	  
	  fp=fopen("1.txt","w");
	  if(fp==NULL)
	  {
		  printf("文件打开出错!\n");
		  exit(1);
	  } 
	  fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);
	  for(i=0;i<adjrec->num_build;i++)
		  for(j=0;j<adjrec->num_build;j++)
			  adjrec->road[i][j]!=0?fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]):1;
		  printf("修改成功!\n");
		  fclose(fp);
		  
}

void modify(AdjMatrix *adjrec)	//修改各种信息
{
	int choice1;
	char choice2;//选择	
    loop:fflush(stdin);
	 while(1)
	 {
		 printf("\n\t1,建筑介绍\n\t2,建筑名称\n\t3,路径长度\n\t4,退出修改\n");
		 printf("\n\t选择修改哪一个？  ");
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
			     printf("命令有误!(请重新输入)!\n");
			     goto loop;
			 }break;
		 }
		 printf("还要继续修改功能吗(y/n)？");
		 fflush(stdin);
		 scanf("%c",&choice2);
		 if(choice2=='n')
			 break;
		 else
			 system("cls");
	 }
     loop2:;
}

void cut_build(AdjMatrix *adjrec)//删除建筑信息
{
	char name[20];
	FILE *fp;
	int number;
	int i,j;
	int flag=0;	//记录与之相关的路径数量
	int temp;//没有用处抵消读取文件
	char introduce[N][50];//建筑介绍字符串数组
	char introduce_[50];	
	system("cls");	
	printf("键入地点名称: ");
    loop:;
	 scanf("%s",name);
	 number=locate(adjrec,name);
	 if(number>=adjrec->num_build)
	 {
		 system("cls");
		 printf("无此地点!(请重新输入)\n");
		 goto loop;
	 }
	 adjrec->name[number][0]='\0';//建筑的名称置空
	 for(i=0;i<adjrec->num_build;i++)//路径不存在
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
	 fp=fopen("3.txt","r");//建筑介绍文件的复制
	 if(fp==NULL)
	 {
		 printf("文件打开出错!\n");
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
		 adjrec->num_build=adjrec->num_build-1;//建筑的数量变化 
	 adjrec->num_road=adjrec->num_road-flag;//路径的数量变化
	 fp=fopen("1.txt","w");//更改距离文件
	 if(fp==NULL)
	 {
		 printf("文件打开有误!\n");
		 exit(1);
	 }
	 fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);	 
	 for(i=0;i<adjrec->num_build;i++)
		 for(j=0;j<adjrec->num_build;j++)
			 if(adjrec->road[i][j]!=0)
				 fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]);		 
			 fclose(fp);
			 fp=fopen("2.txt","w"); //更改建筑名称文件
			 if(fp==NULL)
			 {
				 printf("文件打开有误!\n");
				 exit(1);
			 }
			 for(i=0;i<adjrec->num_build;i++)
				 if(adjrec->name[i][0]!='\0')
					 fprintf(fp,"%d %s\n",i+1,adjrec->name[i]); 
			 fclose(fp);
				 fp=fopen("3.txt","w");//更改建筑介绍文件
				 if(fp==NULL)
				 {
					 printf("文件打开出错!\n");
					 exit(1);
				 }
				 for(i=0;i<adjrec->num_build;i++)
					 if(introduce[i][0]!='\0')
						 fprintf(fp,"%d %s\n",i+1,introduce[i]);
					 fclose(fp);	 
					 printf("\n删除成功!\n");
}

void cut_road(AdjMatrix *adjrec)//删除路径
{
	FILE *fp;
	char name_build[20];
	int start,end;	//路径起点，终点
	int i,j;
	system("cls");
    loop3:;
	  printf("键入待删除路径的起点: ");
    loop:;
	 scanf("%s",name_build);
	 start=locate(adjrec,name_build);
	 if(start>=adjrec->num_build)
	 {
		 system("cls");
		 printf("无此建筑!(请重新输入)\n");
		 goto loop;
	 }
	 printf("键入待删除路径的终点:  ");
     loop2:;
	  scanf("%s",name_build);
	  end=locate(adjrec,name_build);
	  if(end==start)
	  {
		  system("cls");
		  printf("自己无法达到自己!(请重新输入起点和终点)\n");
		  goto loop3;
	  }
	  if(end>=adjrec->num_build)
	  {
		  printf("无此建筑!(请重新输入)\n");
		  goto loop2;
	  }
	  if(adjrec->road[start][end]==0.0)
	  {
		  printf("\n该两点间没有路径!\n");
		  return ;
	  }
	  else
	  {
		  printf("<%s>与<%s>的路径长度为: %.1f\n",adjrec->name[start],adjrec->name[end],adjrec->road[start][end]);
		  adjrec->road[start][end]=adjrec->road[end][start]=0;
		  adjrec->num_road-=2;//无向图 删除两个路径
		  fp=fopen("1.txt","w");
		  if(fp==NULL)
		  {
			  printf("\n文件打开出错!\n");
			  exit(1);
		  }
		  fprintf(fp,"%d %d\n",adjrec->num_build,adjrec->num_road);
		  for(i=0;i<adjrec->num_build;i++)
			  for(j=0;j<adjrec->num_build;j++)
				  if(adjrec->road[i][j]!=0)
					  fprintf(fp,"%d %d %.1f\n",i+1,j+1,adjrec->road[i][j]);
				  fclose(fp);
				  printf("\n删除成功!\n");
	  }  
}

void cut(AdjMatrix *adjrec)//删除各种信息
{
	int choice;
	char choice_;
    loop:fflush(stdin); 
	while(1)
	 {
		 printf("\t1、建筑\n\t2、路径\n\t3、退出删除\n\n");
		 printf("\t删除哪一个？( )\b\b");
		 scanf("%d",&choice);
		 switch(choice)
		 {
		 case 1: cut_build(adjrec);	break;
		 case 2: cut_road(adjrec);  break;
		 case 3: goto loop2;		break;
		 default: 
			 {
				 system("cls");
				 printf("指令有误!(请重新输入!)\n");
				 goto loop;
			 }
		 } 
		 printf("\n还要继续删除吗？(y/n)");
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
	AdjMatrix *G;	//创建邻接矩阵
	int choice1;	//初始选择
	char choice2;	//继续选择
	G=(AdjMatrix *)malloc(sizeof(AdjMatrix));
	G=Create();	//邻接矩阵的创建
	system("color 75");
	while(1)
	{
		menu();
        loop:;
	    scanf("%d",&choice1);
	    switch(choice1)
		{
		 case 1:system("cls"); Map();break;
	     case 2:system("cls"); TraverseDFS(G);	break;	//邻接矩阵的深度遍历
	     case 3:system("cls"); tbfs(G);	break;	//邻接矩阵的广度遍历
	     case 4:system("cls"); find(G);	break;	//查询建筑物的信息
	     case 5:system("cls"); path(G);	break;	//两建筑之间全部路径
	     case 6:system("cls"); increase(G);break;	//增加建筑和路径
	     case 7:system("cls"); floyd(G,0);	break;	//弗洛伊德算法点对点最短
	     case 8:system("cls"); floyd(G,1);	break;	//弗洛伊德算法点对其余全部最短
	     case 9:system("cls"); modify(G);	break;	//修改各个信息
	     case 10:system("cls"); cut(G);		break;	//删除各种信息
	     case 11: printf("\n\t\t感谢使用本系统!\n\n\n");exit(1); 	break;	//退出全部
	     default:
			 {
			    printf("指令错误!(请重新输入)\n"); 
			    fflush(stdin);	//清缓冲区
			    goto loop;
			 }break;
		}
	    printf("继续使用此系统？(y/n)");
	    fflush(stdin);	
	    scanf("%c",&choice2);
	    if(choice2=='n')
		    break;
	    else
		    system("cls");
	}
	return 0;
}














