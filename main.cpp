#include "graph.h" 
#include <iostream> 
#include <cstdlib>


using namespace std; 
void main() 
 
{ 
	system("color f0");
	
  AMLGraph G; 
  G.AML_Init(); 
	int v,op;
	char op1;	
	 
	cout<<"\t\t\t图的DFS和BFS的演示V1.0\n";
	cout<<"\t\t\t正在从文件中读取。。。\n";
	cout<<"\t\t\t从文件中读取信息完毕\n";
    //cout<<"邻接多重表结构："<<endl; 
     
 
	cout<<"\n1:长春2:哈尔滨3:呼和浩特4:北京5:沈阳6:宁夏7:太原8:石家庄9:天津10:济南\n11:西安12:郑州13:南京14:上海15:合肥16:成都17:重庆18:武汉19:杭州20:贵州\n21:长沙22:南昌23:福州24:昆明25:南宁26:广州";
	
	while(1){  
	cout<<"\n\t\t\t请输入起始位置（用地名前的数字表示）：\n";
	cin>>v;
	cout<<"\t\t1.DFS"<<endl;
	cout<<"\t\t2.BFS"<<endl;
	cout<<"\t\t请选择遍历方式:";
	cin>>op;
	switch(op)
	{

	case 1:cout<<"DFS如下：\n";G.image();G.DFS(v);break;
	case 2:cout<<"BFS如下：\n";G.image();G.BFS(v);;break;
	
	}
	cout<<"\n\t\t\t是否继续？(Y/N)";
	cin>>op1;
	if(op1=='N'||op1=='n')
	{	
		cout<<"\t\t\t感谢使用！";break;
	}

	}

	
	
	
} 
