/////////////////////////////////////////////////////////////
//  						function:graph.h							
//					     	LastedDate:2012年6月12日 05:06:37 									
//							created by:qingsonwang						
/////////////////////////////////////////////////////////////




#include <graphics.h>     
#include <conio.h>
#include <iostream>  
#include <fstream> 
//#include "image.h"

using namespace std; 
#define MAX_VERTEX_NUM 30//顶点最大个数
bool visited[100]; //顶点是否被访问标志 


struct loc  //结点坐标信息
{
	int v; //结点序号
	int x; //x坐标
	int y; //y坐标
};




//邻接多重表的存储 

struct Edgenode		//边结点 
 
{ 
 
    int mark;//标志域，指示该边是否被访问过(0:没有1:有) 
    int ivex,jvex;//该边关联的两个顶点的位置 
    Edgenode *ilink,*jlink;//分别指向关联这两个顶点的下一条边 
 
}; 
 
 
struct Vexnode		//顶点结点 
 
{ 
 
    int data;  //顶点名称,用数字表示城市
    Edgenode *firstedge;//指向第一条关联该结点的边 
 
}; 
 
 
 
class AMLGraph 
 
{ 
 
private: 
	
	loc *l; //坐标信息指针
    Vexnode *adjmulist; //顶点数组指针 
    int vexnum; //定点数目 
    int edgenum; //边数目 
    int maxnum; //顶点数最大值 
 
public: 
 
	//构造函数
    AMLGraph(int num1=26,int num2=30)
 
    { 
        adjmulist=new Vexnode[num1]; 
		vexnum=num1;edgenum=num2;
        maxnum=MAX_VERTEX_NUM;
    } 
     
	//析构函数
    ~AMLGraph()		
    { 
        delete[]adjmulist; 
    } 
 
	
    //定位顶点在顶点数组中的位置 
    int Locate_Vex(int v) 
    { 
         for(int i=0;i<vexnum;i++)
             if((adjmulist[i].data)==v) 
 				 return i; 
		return -1; 
    } 
	
	//构造无向图
    void AML_Init() 
    { 
		
			
		ifstream icin;
		icin.open("d:\wenjian2.txt"); 
        int i,j,k;
		int edge[30][2];//二维数组来存储边的关系,30条边和ivex，jvex边集的两结点
        for(i=0;i<edgenum;i++)
			for(j=0;j<2;j++)	
				icin>>edge[i][j];
		    
 
		
		for(i=0;i<vexnum;i++)  //初始化顶点
        { 
            adjmulist[i].data=i+1; 
            adjmulist[i].firstedge=NULL; 
        } 
 
        for(k=0;k<edgenum;k++)	//初始化边信息
        { 
            Edgenode *e=new Edgenode;  //申请边结点空间
 			e->ivex=edge[k][0];
			e->jvex=edge[k][1];//读入2个顶点的值
			e->ilink=adjmulist[e->ivex].firstedge;//将头结点的firstedge指针赋给新结点的ilink
			adjmulist[e->ivex].firstedge=e;//将头结点的指针指向新结点
			e->jlink=adjmulist[e->jvex].firstedge;//将新结点的jlink指针指向其jvex结点所依附的结点
			adjmulist[e->jvex].firstedge=e;
        } 
	
		init_location();  //初始化所有结点的坐标信息
    } 
 
 
    //深度优先遍历 
    void DFS_Traverse() 
    { 
        for(int i=0;i<vexnum;i++) 
             visited[i]=false;		//初始化所有顶点未被访问过
 
        for(i=0;i<vexnum;i++) 
            if(!visited[i])		//如果未被访问过，进行访问DFS遍历
               DFS(i); 
            cout<<endl; 
    } 
  
    void DFS(int v)		//深度优先搜索遍历(递归)
	{
		
		Edgenode *p;
		visited[v]=1;	//标志v已被访问
		cout<<v<<" ";
	
		int i=v;
		p=adjmulist[v].firstedge;//取v边表的头指针，使P指向firstedge
		while(p!=NULL)	 //依次搜索v的邻接点
		{
			if(p->ivex==i)
			{
			if(visited[p->jvex]==0)    //邻近点未被访问过
			{   
			   dline(l[v].x,l[v].y,l[p->jvex].x,l[p->jvex].y);
			   DFS(p->jvex);   //递归调用
			}
			p=p->ilink;
	    }
		else
		{
		   if(visited[p->ivex]==0)
		   {
			  dline(l[v].x,l[v].y,l[p->ivex].x,l[p->ivex].y);
			   DFS(p->ivex);	//递归调用
		   }
		   p=p->jlink;
		}
		}  

	}
 
 
    //广度优先遍历 
    void BFS_Traverse() 
    { 
        for(int i=0;i<vexnum;i++) 
            visited[i]=false; 
        for(i=0;i<vexnum;i++) 
            if(!visited[i]) 
                BFS(i); 
        cout<<endl; 
    } 
 


	void BFS(int v)//广度优先搜索遍历
	{
		int i,vi;
		int Queue[MAX_VERTEX_NUM],front=0,rear=0; //建立队列数组
		Edgenode *p;
		for(i=0;i<vexnum;i++)	//全部节点标记为未访问
			visited[i]=0;
		visited[v]=1;  //开始结点标记为已访问
		cout<<v;  //输出当前访问结点位置	
		cout<<"\n";
		rear=(rear+1)%MAX_VERTEX_NUM;  //取模初始化队列
		Queue[rear]=v;	//入队
		while(front!=rear)//队头和队尾计数器不相等，即当队列非空
		{
			front=(front+1)%MAX_VERTEX_NUM;	//出队
			vi=Queue[front];//vi即表头数据元素值
			p=adjmulist[vi].firstedge;//p指向表头节点所指的邻接点
			while(p!=NULL)//当表头指针所指的邻接点不为空
			{
				if(p->ivex==vi)
				{
					if(visited[p->jvex]==0)//边节点内元素未被访问则访问节点内元素，并对其标记已访问
					{
						visited[p->jvex]=1;
						cout<<p->jvex<<" ";
						dline(l[vi].x,l[vi].y,l[p->jvex].x,l[p->jvex].y);   //绘制路径
						rear=(rear+1)%MAX_VERTEX_NUM;//队列的尾指针计数器加一，即后移一位
						Queue[rear]=p->jvex;
					}
					p=p->ilink;//边节点内元素已被访问，指向下一邻接点
				}
				else
				{
					if(visited[p->ivex]==0)
					{
						visited[p->ivex]=1;
						cout<<p->ivex<<" ";
						dline(l[vi].x,l[vi].y,l[p->ivex].x,l[p->ivex].y);   //绘制路径
					   	rear=(rear+1)%MAX_VERTEX_NUM;
						Queue[rear]=p->ivex;
					}
				  p=p->jlink;
				}
			}
		}
	}
 

	void dline(int x1,int y1,int x2,int y2)   //画线
	{

		setlinestyle(PS_DASH, NULL, 3); //设置线形为宽度 3 像素的虚线
		line(x1,y1,x2,y2);
	
	}
	

	
	void init_location()  //初始化结点的坐标信息
	{
		ifstream icin;
		l=new loc[20];
	
		icin.open("d:\wenjian1.txt");	
		for(int i=1;i<=26;i++)
			icin>>l[i].v>>l[i].x>>l[i].y;
	}


	void image()	//绘制矢量无向图
	{
		HWND hWnd = GetHWnd();
		// 使用 API 函数修改窗口名称
		SetWindowText(hWnd, "图的遍历演示");

		HWND initgraph(
			int Width,
			int Height,
			int Flag =SHOWCONSOLE  

		);

		initgraph(800, 600);   
		loadimage(NULL, "D:\\map1.bmp");
	   // circle(350,365, 10);
		//floodfill(600,100, COLORREF WHITE);
	
	
	}

}; 


