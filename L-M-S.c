#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 10

struct BookInformation{
	char booknumber[20];
	char title[20];
	char category[20];
	char writer[20];
	int storagecapcity;
	int hasborrowed;
	int surpluse;
};

struct Date{
	int year;
	int month;
	int day;	
};

struct StudentInformation{
	char studentnumber[20];
	char borrowbooknum[MAXSIZE][20];
	int hasborrowed;
	struct Date borrowdate[MAXSIZE];
	struct Date shouldreturndate[MAXSIZE];
};

struct BookStore{
	struct BookInformation BookInf;
	struct BookStore* next;
};

struct StudentStore{
	struct StudentInformation StuInf;
	struct StudentStore* next;
};

struct BookStore* Read_Book_Storage(int *allbook_number);//图书信息文件读取 ，将文件中的第一个int类型（4个字节）写入allbook_number便于后序数据显示。 
struct StudentStore* Read_Student_Storage(int *allstudent_number);//学生信息文件读取 ， 将文件中的第一个int类型（4个字节）写入allstudent_number便于后续数据显示。 

void Print_Book(struct BookStore*Book_head);//通过给定一个头节点，输出这个链表上所有的图书信息 

struct BookStore* Insert_Book(struct BookStore*Book_head,struct BookStore*newbook,int *allbook_number);//给定头节点，新书的数据，以及链表上的所有书的数目 
struct StudentStore* Insert_Student(struct StudentStore* Student_head,struct StudentStore* newstudent,int *allstudent_number);//给定头节点，新学生的数据，以及链表上所有学生的数目 

struct BookStore* Delete_Book(struct BookStore*Book_head,char delete_booknumber[20],int *allbook_number);//通过给定书号，删除链表上的书籍，并改变书数目的值 
struct StudentStore* Delete_Student(struct StudentStore*Student_head,char delete_studentnumber[20],int *allstudent_number);//通过给定学生学号，删除链表上的学生信息，并改变学生数目 

struct BookStore* Search_Book_by_booknumber(struct BookStore*Book_head,char search_booknumber[20]);//通过书号，遍历链表，查找书籍。 
struct BookStore* Search_Book_by_title(struct BookStore*Book_head,char search_title[20]);//通过书名， 遍历链表，查找书籍。 
struct BookStore* Search_Book_by_category(struct BookStore*Book_head,char search_category[20]);//通过类型，遍历链表，查找书籍 
struct BookStore* Search_Book_by_writer(struct BookStore*Book_head,char search_writer[20]);//通过作者，遍历链表，查找书籍。 

struct StudentStore* Find_Student(struct StudentStore* Student_head,char using_studentnumber[20]);//通过学号，遍历链表，查找某位学生。 
struct BookStore* Find_Book(struct BookStore* Book_head,char borrow_book[20]);//通过书号，遍历链表，查找某本书籍。 

int isLeapYear(int year);//判断是否为润年 
int SumDay(int year,int month,int day);//计算总天数 
int Calculate_Date_Difference(struct Date Today,struct Date borrowdate);//计算差值，用于罚款判断。 
struct Date* Calculate_Date(struct Date Today); //计算两个月后是几号。 

void FreedomList(struct BookStore* FindLine);//释放只是一次使用而malloc产生的空间 
void Freedom_Stu_List(struct StudentStore* Student_head); 
void Store_Book_Information(struct BookStore*Book_head,int allbook_number);//存储图书信息 
void Store_Student_Information(struct StudentStore*Student_head,int allstudent_number);//储存学生信息 
void Print_Student(struct StudentStore*Student_head){
	struct StudentStore*p=Student_head;
	while(p!=NULL){
		printf("%s\n",(p->StuInf).studentnumber);
		printf("%d\n",(p->StuInf).hasborrowed);
		int i;
		for(i=0;i<p->StuInf.hasborrowed;i++){
			printf("%s\n",p->StuInf.borrowbooknum[i]);
		}
		p=p->next;
	} 
}
int main()
{
	
	int allbook_number=0,allstudent_number=0; 	//通过后续读取文件来知道，目前图书馆所存储的藏书以及学生数目。 
	struct BookStore* Book_head=Read_Book_Storage(&allbook_number);//读取文件 
	struct StudentStore* Student_head=Read_Student_Storage(&allstudent_number);//读取文件 
	
	printf("\t\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
	printf("\t\t\t\t\t    欢迎使用图书馆管理系统!\n\n");
	printf("\t\t\t\t目前图书馆含有书目：%d\t学生数目：%d\n\n",allbook_number,allstudent_number);
	printf("\t\t\t\t是否进入图书馆管理系统，进入请输入1，退出请输入0！\n\n");
	int enterkey;
	printf("\t\t\t\t进入或者退出请选择<0,1>:");
	int count1=0;	//记录输入判断次数，后续判断次数超过3次则自动退出系统。 
	//使用do while语句比较方便
	 
	do{
		
		count1++;
		scanf("%d",&enterkey);
		printf("\n");
		if(count1>3){
			printf("\t\t\t\t输入错误多次自动默认退出系统！\n\n");
			enterkey=0;
			break;
		}
		if(enterkey!=0&&enterkey!=1){
			printf("\t\t\t\t输入错误，请重新输入！进入或者退出请选择<0,1>:");
		}
	}while(enterkey!=0&&enterkey!=1);
	
	
	if(enterkey==0){
		
		printf("\t\t\t\t\t\t谢谢您的使用,再见！\n\n"); 

	}else if(enterkey==1){
		while(1){
			int outkey2=0;
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
			printf("\t\t\t\t\t\t 图书馆系统\n\n");
			printf("\n");
			printf("\t\t\t\t[1]管理员模式------------------------[2]查询图书\n\n"); 
			printf("\t\t\t\t[3]显示所有书籍----------------------[4]查询借阅信息\n\n");
			printf("\t\t\t\t[5]归还书籍--------------------------[6]借阅书籍\n\n");
			printf("\t\t\t\t[0]退出\n\n\n");
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n"); 
			int choice1;
			printf("\t\t\t\t请选择<0~6>:"); 
			scanf("%d",&choice1); //利用后续的switch case 
			getchar();
			printf("\n");
			char key1[20];
			char key2[20]="123456";//管理员进入密码
			 
			switch(choice1){
				case 0:outkey2=1;break;
				case 1:	
					//管理员模式，考虑到不是每一个人都能进入，所以需要输入密码 
					printf("\t\t\t\t请输入管理员密码：");
					gets(key1);
					printf("\n");
					if(strcmp(key1,key2)!=0){
						printf("\t\t\t\t管理员密码输入错误已自动退出该模式\n\n");
						printf("\t\t\t\t是否返回上一级菜单？\n\n");
						printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
						int choices_m4;
						scanf("%d",&choices_m4);
						getchar();
						printf("\n");
						if(choices_m4!=1){									
							outkey2=1;
						}else {
							outkey2=0;
						}
					}else{
						while(1){
							int outkey=0;
							printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
							printf("\t\t\t\t\t\t 管理员模式\n\n");
							printf("\t\t\t\t[1]添加图书=========================[2]删除图书\n\n");
							printf("\t\t\t\t[3]添加学生=========================[4]删除学生\n\n");
							printf("\t\t\t\t[0]退出\n\n\n");
							printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
							printf("\t\t\t\t请选择<0~4>:");
							int choice2;
							scanf("%d",&choice2);//同样后续使用switch case 
							getchar();
							printf("\n"); 
							switch(choice2){
								case 0:
									printf("\t\t\t\t是否返回上一级菜单？\n\n");//增加询问 
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choices;
									scanf("%d",&choices);
									getchar();
									printf("\n");
									if(choices!=1){									
										outkey2=1;
									}else {
										outkey2=0;
									}
									outkey=1;
									break;
								
								case 1:						
										while(1){			
												printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
												printf("\t\t\t\t\t\t 入库模式\n\n");
												struct BookStore* newbook=(struct BookStore*)malloc(sizeof(struct BookStore)); 
												newbook->next=NULL;
												printf("\t\t\t\t请输入新书的书号：");
												gets((newbook->BookInf).booknumber);
												printf("\n\t\t\t\t请输入新书的书名：");
												gets((newbook->BookInf).title);
												printf("\n\t\t\t\t请输入新书的种类：");
												gets((newbook->BookInf).category);
												printf("\n\t\t\t\t请输入新书的作者：");
												gets((newbook->BookInf).writer);
												printf("\n\t\t\t\t请输入新书的总库存：");
												scanf("%d",&((newbook->BookInf).storagecapcity));
												getchar();
												printf("\n\t\t\t\t请输入新书已出借册数：");
												scanf("%d",&((newbook->BookInf).hasborrowed));
												getchar();
												newbook->BookInf.surpluse=newbook->BookInf.storagecapcity-newbook->BookInf.hasborrowed;
												printf("\n");					
												
												Book_head=Insert_Book(Book_head,newbook,&allbook_number); //插入图书函数，函数参数包含存储书籍链表的头节点，新书的内容，以及所含有的所有书籍的数目，添一本则number++ 
													
												printf("\t\t\t\t是否需要继续进行图书的入库？\n\n");
												printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
												int choice3=0;
												scanf("%d",&choice3);
												printf("\n");
												getchar();
												if(choice3!=1){
													break;
												}
											}
										printf("\t\t\t\t是否需要继续使用管理员模式？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
										int choice4=0;
										scanf("%d",&choice4);
										printf("\n");
										getchar();
										if(choice4!=1){
											printf("\t\t\t\t是否返回上一级菜单？\n\n");
											printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
											int choices;
											scanf("%d",&choices);
											getchar();
											printf("\n");
											if(choices!=1){									
												outkey2=1;
											}else {
												outkey2=0;
											}
											outkey=1;
										}
										break;
									
								case 2:
									while(1){
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t\t\t 图书出库模式\n\n"); 
										printf("\t\t\t\t请输入要删除的图书的书号：");
										char delete_booknumber[20];
										gets(delete_booknumber);
										printf("\n");
										Book_head=Delete_Book(Book_head,delete_booknumber,&allbook_number);//为了保证书籍删除的准确性，输入书号删除，参数为头节点，删书的书号，所有书的数量，删除成功则数量-- 
										printf("\t\t\t\t是否需要继续进行图书出库？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t是否需要继续使用管理员模式？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choice6=0;
									scanf("%d",&choice6);
									printf("\n");
									getchar();
									if(choice6!=1){
										printf("\t\t\t\t是否返回上一级菜单？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
										int choices;
										scanf("%d",&choices);
										getchar();
										printf("\n");
										if(choices!=1){									
											outkey2=1;
										}else {
											outkey2=0;
										}
										outkey=1;
									}
									break;
								case 3:
									
									while(1){
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t\t\t 学生信息入库模式\n\n");
										struct StudentStore* newstudent=(struct StudentStore*)malloc(sizeof(struct StudentStore)); 
										newstudent->next=NULL;
										printf("\t\t\t\t请输入新学生的学号：");
										gets(newstudent->StuInf.studentnumber);
										newstudent->StuInf.hasborrowed=0;
										printf("\n");					
				
										Student_head=Insert_Student(Student_head,newstudent,&allstudent_number);//插入新学生函数，参数头节点，新学生学号，所有学生数目，添加一个学生成功则数量++ 
				
										printf("\t\t\t\t是否需要继续进行学生信息入库？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t是否需要继续使用管理员模式？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choice5=0;
									scanf("%d",&choice5);
									printf("\n");
									getchar();
									if(choice5!=1){
											printf("\t\t\t\t是否返回上一级菜单？\n\n");
											printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
											int choices;
											scanf("%d",&choices);
											getchar();
											printf("\n");
											if(choices!=1){									
												outkey2=1;
											}else {
												outkey2=0;
											}
											outkey=1;
										}
									break;
									
								case 4:
									while(1){
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t\t\t 学生信息出库模式\n\n"); 
										printf("\t\t\t\t请输入要删除的学生的学号：");
										char delete_studentnumber[20];
										gets(delete_studentnumber);
										printf("\n");
										Student_head=Delete_Student(Student_head,delete_studentnumber,&allstudent_number);//学生信息删除，参数头指针，学生学号，所有学生数目，删除成功则数量-- 
										printf("\t\t\t\t是否需要继续进行学生信息出库？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t是否需要继续使用管理员模式？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choice7=0;
									scanf("%d",&choice7);
									printf("\n");
									getchar();
									if(choice7!=1){
										printf("\t\t\t\t是否返回上一级？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
										int choices;
										scanf("%d",&choices);
										getchar();
										printf("\n");
										if(choices!=1){									
											outkey2=1;
										}else {
											outkey2=0; 
										}
										outkey=1;
									}
									
									break;
								default:
									outkey=1;
									printf("\t\t\t\t输入错误，已自动退出该菜单并返回上一个菜单，如需帮助请再次进入该菜单！谢谢！\n\n");
									break;
								}
								if(outkey==1){
									break;
								}
							}
					}
						break;
						 
				case 2:
					while(1){
						int outkey_m1=0;
						printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						printf("\t\t\t\t\t\t 查询书籍模式\n\n");
						printf("\t\t\t\t[1]书号查书=========================[2]书名查书\n\n");
						printf("\t\t\t\t[3]类型查书=========================[4]作者查书\n\n");
						printf("\t\t\t\t[0]退出\n\n");
						printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						printf("\t\t\t\t请选择<0~4>:");
						int choice_l2;
						scanf("%d",&choice_l2);//进入查询书籍模式后，有四种小模式，仍然使用switch case来表示 
						getchar();
						printf("\n");
						switch(choice_l2){
							char search_booknumber[20];
							char search_title[20];
							char search_category[20];
							char search_writer[20];
							case 0:
								outkey_m1=1;
								break;
							case 1:
								while(1){
									int outkey4=0;
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t\t\t 书号查书模式\n\n");
									printf("\t\t\t\t请输入所要查询书籍的书号：");
									gets(search_booknumber);
									printf("\n");
									struct BookStore* Find_Node=Search_Book_by_booknumber(Book_head,search_booknumber);//书号查询，该查询出来的最多仅有一本书，所有即为一个节点。 
									if(Find_Node==NULL){
										printf("\t\t\t\t对不起，您所查找的书号不存在！\n\n");//书号不存在则Find_Node为空 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}else{
										Print_Book(Find_Node);
										free(Find_Node);//因为是多mallo出来的查询成功之后最好将其free释放空间 
										printf("\t\t\t\t查书成功！\n\n");
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t是否继续使用书号查询模式？\n\n");//优化，再次询问 
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
									scanf("%d",&choice_s1);
									getchar();
									printf("\n");
									if(choice_s1!=1){
										outkey4=1;
									}else {
										outkey4=0;
									}
									if(outkey4==1){
										break;
									}
								}
								printf("\t\t\t\t是否继续使用查询书籍模式？\n\n");
								printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
								int choice_m1=0;
								scanf("%d",&choice_m1);
								getchar();
								printf("\n");
								if(choice_m1!=1){
									outkey_m1=1;
								}else {
									outkey_m1=0;
								} 
								break;
							case 2:
								while(1){
									int outkey4=0;
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t\t\t 书名查书模式\n\n");
									printf("\t\t\t\t请输入所要查询书籍的书名：");
									gets(search_title);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_title(Book_head,search_title);//书名查询，书名可以是模糊的 
									if(FindLine==NULL){
										printf("\t\t\t\t对不起，不存在与该书名相关的书籍!\n\n");//如果不存在，则输出这个。 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}else {
										Print_Book(FindLine);//找到的书籍可能不止一本，所以可能是一连串节点相连的链表 
										FreedomList(FindLine);//malloc产生的空间需要将其free释放 
										printf("\t\t\t\t查书成功！\n\n");
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t是否继续使用书名查询模式？\n\n");//优化询问 
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
									scanf("%d",&choice_s1);
									getchar();
									printf("\n");
									if(choice_s1!=1){
										outkey4=1;
									}else {
										outkey4=0;
									}
									if(outkey4==1){
										break;
									}
								}
								printf("\t\t\t\t是否继续使用查询书籍模式？\n\n");//优化询问 
								printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
								int choice_m4=0;
								scanf("%d",&choice_m4);
								getchar();
								printf("\n");
								if(choice_m4!=1){
									outkey_m1=1;
								}else {
									outkey_m1=0;
								} 
								break;
							case 3:
								while(1){
									int outkey4=0;
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t\t\t 类型查书模式\n\n");
									printf("\t\t\t\t请输入所要查询书籍的类型：");
									gets(search_category);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_category(Book_head,search_category);
									if(FindLine==NULL){
										printf("\t\t\t\t对不起，您所查找的书籍类型不存在！\n\n");//查询不到这种书籍类型则打印这个 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}else {
										Print_Book(FindLine);//可能一种类型的书籍不止一本 
										FreedomList(FindLine);//释放空间 
										printf("\t\t\t\t查书成功！\n\n");
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t是否继续使用类型查询模式？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
									scanf("%d",&choice_s1);
									getchar();
									printf("\n");
									if(choice_s1!=1){
										outkey4=1;
									}else {
										outkey4=0;
									}
									if(outkey4==1){
										break;
									}
								}
								printf("\t\t\t\t是否继续使用查询书籍模式？\n\n");
								printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
								int choice_m2=0;
								scanf("%d",&choice_m2);
								getchar();
								printf("\n");
								if(choice_m2!=1){
									outkey_m1=1;
								}else {
									outkey_m1=0;
								} 
								break;
							case 4:
								while(1){
									int outkey4=0;
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t\t\t 作者查书模式\n\n");
									printf("\t\t\t\t请输入所要查询书籍的作者：");
									gets(search_writer);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_writer(Book_head,search_writer);
									if(FindLine==NULL){
										printf("\t\t\t\t对不起，不存在该作者的书籍！\n\n");//未查询到该作者的书籍则打印这个 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}else {
										Print_Book(FindLine);//打印该作者的书籍 
										FreedomList(FindLine);//释放空间 
										printf("\t\t\t\t查书成功！\n\n");
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t是否继续使用作者查询模式？\n\n");//优化询问 
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
									scanf("%d",&choice_s1);
									getchar();
									printf("\n");
									if(choice_s1!=1){
										outkey4=1;
									}else {
										outkey4=0;
									}
									if(outkey4==1){
										break;
									}
								}
								printf("\t\t\t\t是否继续使用查询书籍模式？\n\n");
								printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
								int choice_m3=0;
								scanf("%d",&choice_m3);
								getchar();
								printf("\n");
								if(choice_m3!=1){
									outkey_m1=1;
								}else {
									outkey_m1=0;
								} 
								break;
							default:
								outkey_m1=1;
								printf("\t\t\t\t输入错误已自动退出该菜单！\n\n");
								break;
						}
						if(outkey_m1==1){
							break;
						}
					}
					printf("\t\t\t\t是否返回上一个菜单？\n\n");//优化询问 
					printf("\t\t\t\t是请选择1，否请选择0,<0,1>："); 
					int choice_l3=0;
					scanf("%d",&choice_l3);
					getchar();
					printf("\n");
					if(choice_l3!=1){
						outkey2=1;
					}else {
						outkey2=0;
					}
					break;
				case 3:
					printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
					printf("\t\t\t\t\t\t 显示所有书籍模式\n\n"); //显示所有书籍，通过头节点打印 
					Print_Book(Book_head);
					printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
					printf("\t\t\t\t是否需要继续使用图书馆系统？\n\n"); 
					printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
					int choice_l;
					scanf("%d",&choice_l);
					getchar();
					printf("\n");
					if(choice_l!=1){
						outkey2=1;
					}else{
						outkey2=0;
					}
					break;
				case 4:
					while(1){
						int outkey4=0;
						printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						printf("\t\t\t\t\t\t 查询借阅信息模式\n\n");//首先输入学号，判断是否存在该学生信息。 
						printf("\t\t\t\t请输入你的学号：");
						char search_studentnumber[20];
						gets(search_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,search_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\t学号输入错误或不存在该学生信息,请更正或确认自己的信息\n\n");
							printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						}else{
							printf("\t\t\t\t学生信息：\n\n");//打印该学生的借阅信息 
							printf("\t\t\t\t学号：%s\t已借阅书籍数目：%d\n\n",Find_Student_Node->StuInf.studentnumber,Find_Student_Node->StuInf.hasborrowed);
							int i=0;
							for(i=0;i<Find_Student_Node->StuInf.hasborrowed;i++){
								printf("\t\t\t\t借阅书籍书号：%s\n",Find_Student_Node->StuInf.borrowbooknum[i]);
								printf("\t\t\t\t借阅时间为：%d年%d月%d日\n",Find_Student_Node->StuInf.borrowdate[i].year,Find_Student_Node->StuInf.borrowdate[i].month,Find_Student_Node->StuInf.borrowdate[i].day);
								printf("\t\t\t\t归还时间为：%d年%d月%d日\n\n",Find_Student_Node->StuInf.shouldreturndate[i].year,Find_Student_Node->StuInf.shouldreturndate[i].month,Find_Student_Node->StuInf.shouldreturndate[i].day);	
							}
							printf("\t\t\t\t查询成功！\n\n");
							printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						}
						printf("\t\t\t\t是否继续进行借阅信息查询？\n\n");//优化询问 
						int choice_m5=0;
						printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
						scanf("%d",&choice_m5);
						getchar();
						printf("\n");
						if(choice_m5!=1){
							outkey4=1;
						}
						if(outkey4==1){
							break;
						} 
					}
					break;
				case 5:
					while(1){
						int outkey4=0;
						printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						printf("\t\t\t\t\t\t 还书模式\n\n");
						printf("\t\t\t\t请输入你的学号：");//输入学号还书 
						char using_studentnumber[20];
						gets(using_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,using_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\t学号输入错误或不存在该学生信息，请更正或确认自己的信息\n\n");		
							printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");					
						}else{
							while(1){
								int outkey_m3=0;
								char return_borrow_booknumber[20];
								printf("\t\t\t\t请输入归还书籍的书号：");//保证归还书籍的准确性（书籍与书号一一对应）输入归还书籍书号 
								gets(return_borrow_booknumber);
								printf("\n");
								struct BookStore* Find_Book_Node=Find_Book(Book_head,return_borrow_booknumber);
								if(Find_Book_Node==NULL){
									printf("\t\t\t\t书籍书号信息输入错误，请确认是否存在该书籍，或者书号输入是否正确\n\n");
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t是否重新输入书号归还书籍？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choice_s6=0;
									scanf("%d",&choice_s6);
									getchar();
									printf("\n"); 
									if(choice_s6!=1){
										outkey_m3=1;
									}
								}else {
									int i=0,index=0,isprime=0;
									for(i=0;i<Find_Student_Node->StuInf.hasborrowed;i++){
										if(strcmp(Find_Student_Node->StuInf.borrowbooknum[i],return_borrow_booknumber)==0){
											index=i;
											isprime=1;
										}
									}
									if(isprime==1){
										struct Date Today;
										printf("\t\t\t\t归还日期:\n\n");//记录归还日期 
										time_t timep;
									    struct tm *p;
									    time (&timep);
									    p=gmtime(&timep);
									    Today.year=1900+p->tm_year;
									    Today.month=1+p->tm_mon;
									    Today.day=p->tm_mday;
										printf("\t\t\t\t今天的日期为：");
										printf("%d年%d月%d日\n",Today.year,Today.month,Today.day); 
										printf("\n");
										int n=Calculate_Date_Difference(Today,Find_Student_Node->StuInf.borrowdate[index]);//计算是否超过两个月，超过了的话超过几天
										struct Date shouldreturndate=Find_Student_Node->StuInf.shouldreturndate[index];
										//下面是将书籍与结构体内部数组的最后一位做交换，其中有书号交换，借阅日期交换，归还日期交换，然后再将最后一位删除，然后改变学生节点借书数，以及书节点的剩余和借出 
										int temp_index=Find_Student_Node->StuInf.hasborrowed-1;
										char temp_booknumber[20];
										struct Date Temp_Date1,Temp_Date2;
										strcpy(temp_booknumber,Find_Student_Node->StuInf.borrowbooknum[temp_index]);
										Temp_Date1=Find_Student_Node->StuInf.borrowdate[temp_index];
										Temp_Date2=Find_Student_Node->StuInf.shouldreturndate[temp_index];
										strcpy(Find_Student_Node->StuInf.borrowbooknum[temp_index],Find_Student_Node->StuInf.borrowbooknum[index]);
										Find_Student_Node->StuInf.borrowdate[temp_index]=Find_Student_Node->StuInf.borrowdate[index];
										Find_Student_Node->StuInf.shouldreturndate[temp_index]=Find_Student_Node->StuInf.shouldreturndate[index];
										strcpy(Find_Student_Node->StuInf.borrowbooknum[index],temp_booknumber);
										Find_Student_Node->StuInf.borrowdate[index]=Temp_Date1;
										Find_Student_Node->StuInf.shouldreturndate[index]=Temp_Date2;
										Find_Student_Node->StuInf.borrowdate[temp_index].day=0;
										Find_Student_Node->StuInf.borrowdate[temp_index].month=0;
										Find_Student_Node->StuInf.borrowdate[temp_index].year=0;
										Find_Student_Node->StuInf.shouldreturndate[temp_index].day=0;
										Find_Student_Node->StuInf.shouldreturndate[temp_index].month=0;
										Find_Student_Node->StuInf.shouldreturndate[temp_index].year=0;
										Find_Student_Node->StuInf.borrowbooknum[temp_index][0]='\0';
										Find_Student_Node->StuInf.hasborrowed--;
										Find_Book_Node->BookInf.surpluse++;
										Find_Book_Node->BookInf.hasborrowed--;
										if(n>0){
											printf("\t\t\t\t应该归还日期：%d年%d月%d日\n\n",shouldreturndate.year,shouldreturndate.month,shouldreturndate.day);
											printf("\t\t\t\t超出归还时间%d天，共计罚款金额：%f元\n\n",n,n*0.2);//超出的话要打印罚款 
										}
										printf("\t\t\t\t归还成功！\n\n");
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t是否需要继续归还书籍?\n\n");
										printf("\t\t\t\t是请选择1，否请选择0,<0,1>：");
										int choice_last1=0;
										scanf("%d",&choice_last1);
										getchar();
										printf("\n");
										if(choice_last1!=1){
											outkey_m3=1;
										} 
									}else{
										printf("\t\t\t\t该书号并未出现在借阅信息中，请确认归还书籍书号，谢谢！\n\n");//如果没有这本书的借阅信息则返回这个 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t是否重新输入书号归还书籍？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
										int choice_s6=0;
										scanf("%d",&choice_s6);
										getchar();
										printf("\n"); 
										if(choice_s6!=1){
										outkey_m3=1;
										}
									}
									
								}
								
								if(outkey_m3==1){
									break;
								}
							}
						}
						printf("\t\t\t\t是否重新进入借阅书籍模式?\n\n");//优化询问 
						printf("\t\t\t\t是请输入1，否请输入0，<0,1>：");
						int choice_last3=0;
						scanf("%d",&choice_last3);
						printf("\n");
						getchar();
						if(choice_last3!=1){
							outkey4=1;
							printf("\t\t\t\t是否返回上一个菜单？\n\n");//优化询问 
							printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
							int choice_last2;
							scanf("%d",&choice_last2);
							getchar(); 
							printf("\n");
							if(choice_last2!=1){
								outkey2=1;
							}
						}
						
						if(outkey4==1){
							break;
						}
					}
					break;
				case 6:
					while(1){
						int outkey4=0;
						printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
						printf("\t\t\t\t\t\t 借书模式\n\n");//借书仍然第一步输入学号 
						printf("\t\t\t\t请输入你的学号：");
						char using_studentnumber[20];
						gets(using_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,using_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\t学号输入错误或不存在该学生信息,请更正或确认自己的信息\n\n");//输入错误判断 
						}else {
							while(1){
								int outkey_m3=0;
								char borrow_booknumber[20];
								printf("\t\t\t\t为保证借阅书籍准确性，请输入借阅书籍的书号：");
								gets(borrow_booknumber);
								printf("\n");
								struct BookStore* Find_Book_Node=Find_Book(Book_head,borrow_booknumber);//查找书节点 
								if(Find_Book_Node==NULL){
									printf("\t\t\t\t书籍书号信息输入错误，请确认是否存在该书籍，或者书号输入是否正确\n\n");
									printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
									printf("\t\t\t\t是否重新输入书号借阅书籍？\n\n");
									printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
									int choice_s6=0;
									scanf("%d",&choice_s6);
									getchar();
									printf("\n"); 
									if(choice_s6!=1){
										outkey_m3=1;
									}
								}else {
									if(Find_Student_Node->StuInf.hasborrowed>=MAXSIZE){
										printf("\t\t\t\t借阅书目数量达到最大值（10本），暂停借阅书籍！\n\n");//如果借阅书籍达到10本不能再借，需归还后才可借书 
										printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										printf("\t\t\t\t自动退出该学号借阅书籍页面！\n\n");
										outkey_m3=1;
									}else {
										if(Find_Book_Node->BookInf.surpluse==0){
											printf("\t\t\t\t该书籍均被借出，请等待他人归还后再来借阅，谢谢！\n\n");//没有剩余书籍也无法借书 
											printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										}else{
											printf("\t\t\t\t请输入今天的日期（年月日，如2021 7 22）："); //输入借书的日期 
											struct Date Today;
											scanf("%d%d%d",&Today.year,&Today.month,&Today.day);
											printf("\n");
											//改变节点数据 
											struct Date*Back_day=Calculate_Date(Today);
											Find_Book_Node->BookInf.hasborrowed++;
											Find_Book_Node->BookInf.surpluse--;
											strcpy(Find_Student_Node->StuInf.borrowbooknum[Find_Student_Node->StuInf.hasborrowed],borrow_booknumber);
											Find_Student_Node->StuInf.borrowdate[Find_Student_Node->StuInf.hasborrowed]=Today;
											Find_Student_Node->StuInf.shouldreturndate[Find_Student_Node->StuInf.hasborrowed]=*Back_day;
											Find_Student_Node->StuInf.hasborrowed++;
											printf("\t\t\t\t借阅成功！请注意在%d年%d月%d日前归还\n\n",Back_day->year,Back_day->month,Back_day->day);
											printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
										} 
										printf("\t\t\t\t是否继续输入书号借阅书籍？\n\n");
										printf("\t\t\t\t是请选择1，否请选择0，<0,1>:");
										int choice_s6=0;
										scanf("%d",&choice_s6);
										getchar();
										printf("\n"); 
										if(choice_s6!=1){
											outkey_m3=1;
										}
									}
									
								}
								if(outkey_m3==1){
									break;
								}
							}
						}
						printf("\t\t\t\t是否再次进行借书模式?\n\n");
						printf("\t\t\t\t是请选择1,否请选择0,<0,1>:");
						int choice_s5=0;
						scanf("%d",&choice_s5);
						getchar();
						printf("\n");
						if(choice_s5!=1){
							outkey4=1;
						}
						if(outkey4==1){
							break;
						}
						
					}
					break;
				default:
					outkey2=1;
					printf("\t\t\t\t输入错误，已自动退出程序，如需帮助请再次进入程序！\n\n");break;
	
			}
			
			if(outkey2==1){
				break;
			}
	
		}
	printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
	printf("\t\t\t\t谢谢您的使用,再见！\n\n");
	}
	
	Store_Book_Information(Book_head,allbook_number);//存储图书信息数据 
	Store_Student_Information(Student_head,allstudent_number);//存储学生借阅信息数据 

	FreedomList(Book_head);//释放malloc产生的空间 
	Freedom_Stu_List(Student_head);//释放malloc产生的空间 

	return 0;
}

//从文件中读出数据，并用链表串联 
struct BookStore* Read_Book_Storage(int *allbook_number){
	FILE *fp;
	
	if((fp=fopen("BookStore4","rb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	fread(allbook_number,sizeof(int),1,fp);//文件开头存储的是所含有的书数目的总数，方便显示以及统计。 
	struct BookStore* ListHead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p;
	ListHead->next=NULL; 
	p=ListHead;
	int i=0;
	//通过链表串联数据 
	for(i=0;i<*allbook_number;i++){
		struct BookStore* onebook=(struct BookStore*)malloc(sizeof(struct BookStore));
		onebook->next=NULL;
		fread(&(onebook->BookInf),sizeof(struct BookInformation),1,fp);
		p->next=onebook;
		p=onebook;
	}
	
	p=ListHead;
	ListHead=ListHead->next;
	free(p);
	fclose(fp);
	return ListHead;
}
//同上 
struct StudentStore* Read_Student_Storage(int *allstudent_number){
	FILE *fp;
	
	if((fp=fopen("StudentStore4","rb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	
	fread(allstudent_number,sizeof(int),1,fp);//文件的前四个字节存储的是int类型未所含有学生的数量 
	int i=0;
	struct StudentStore* ListHead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p;
	ListHead->next=NULL; 
	p=ListHead;
	//通过链表串联起来 
	for(i=0;i<*allstudent_number;i++){	
		struct StudentStore* onestudent=(struct StudentStore*)malloc(sizeof(struct StudentStore));
		onestudent->next=NULL;
		fread(&(onestudent->StuInf),sizeof(struct StudentInformation),1,fp);
		p->next=onestudent;
		p=onestudent;
	}
	
	p=ListHead;
	ListHead=ListHead->next;
	free(p);
	fclose(fp);
	return ListHead;
}

void Print_Book(struct BookStore*Book_head){
	struct BookStore *p=Book_head;
	//通过头节点遍历链表输出信息 
	while(p!=NULL){
		printf("\n");
		printf("\t\t\t\t书号：%s\t",(p->BookInf).booknumber);
		printf("书名：%s\n",(p->BookInf).title);
		printf("\t\t\t\t类型：%s\t\t",(p->BookInf).category);
		printf("作者：%s\n",(p->BookInf).writer);
		printf("\t\t\t\t总库存：%d\t已借出：%d\t剩余数目：%d\n\n",p->BookInf.storagecapcity,p->BookInf.hasborrowed,p->BookInf.surpluse);
		p=p->next;
	} 
}

struct BookStore* Insert_Book(struct BookStore*Book_head,struct BookStore*newbook,int *allbook_number){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p;
	Listhead->next=Book_head;
	p=Listhead;
	//找到插入位置，通过strcmp来发现 
	while(p->next!=NULL&&strcmp(newbook->BookInf.booknumber,p->next->BookInf.booknumber)>0){
		p=p->next;
	}
	//如果为空则没有找到，或者找到了和他相同的书号则通过询问继续 
	if(p->next!=NULL&&strcmp(newbook->BookInf.booknumber,p->next->BookInf.booknumber)==0){
		printf("\t\t\t\t新书入库失败，请确认是否为旧书增加库存：\n\n");
		printf("\t\t\t\t是请选择1，否请选择0，<0,1>：");
		int choice;
		scanf("%d",&choice);
		getchar();
		printf("\n");
		if(choice==1){
			p->next->BookInf.storagecapcity=newbook->BookInf.storagecapcity;	
		}
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else{
		newbook->next=p->next;
		p->next=newbook;
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		(*allbook_number)++;  //入库成功书目加一 
		printf("\t\t\t\t新书入库成功！\n\n");
		printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		return Listhead;
	} 
}

struct StudentStore* Insert_Student(struct StudentStore*Student_head,struct StudentStore* newstudent,int *allstudent_number){
	struct StudentStore* Listhead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p;
	Listhead->next=Student_head;
	p=Listhead;
	//找到插入位置，同样通过strcmp来找到 
	while(p->next!=NULL&&strcmp(newstudent->StuInf.studentnumber,p->next->StuInf.studentnumber)>0){
		p=p->next;
	}
	//如果为空，或者与学生库某位学生相同则入库失败 
	if(p->next!=NULL&&strcmp(newstudent->StuInf.studentnumber,p->next->StuInf.studentnumber)==0){
		printf("\t\t\t\t新学生入库失败，该学生已存在于学生库，自动返回！\n\n");
		printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else{
		newstudent->next=p->next;
		p->next=newstudent;
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		(*allstudent_number)++;//入库成功则学生数量+1 
		printf("\t\t\t\t新学生入库成功！\n\n");
		printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		return Listhead;
	}
	
}

struct BookStore* Delete_Book(struct BookStore*Book_head,char delete_booknumber[20],int *allbook_number){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p,*p1;
	Listhead->next=Book_head;
	p=Listhead;
	//找到删除的节点 
	while(p->next!=NULL&&strcmp((((p->next)->BookInf).booknumber),delete_booknumber)!=0){
		p=p->next;
	}
	if(p->next==NULL){//为空则没有找到 
		printf("\t\t\t\t未查找到该书籍，删除失败，自动返回！\n\n");
		printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else {
		
		if(p->next->BookInf.hasborrowed!=0){
			printf("\t\t\t\t该书籍仍处于借阅状态，无法删除！\n\n");//处在借阅状态下则也没法删除 
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
			p=Listhead;
			Listhead=Listhead->next;
			free(p);
			return Listhead;
		}else{
			p1=p->next;
			p->next=p->next->next;
			free(p1);
			p=Listhead;
			Listhead=Listhead->next;
			free(p);
			(*allbook_number)--;//出库成功书数-1 
			printf("\t\t\t\t书籍出库成功！\n\n");
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
			return Listhead;
		}
	}
	
}

struct StudentStore* Delete_Student(struct StudentStore*Student_head,char delete_studentnumber[20],int *allstudent_number){
	struct StudentStore* Listhead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p,*p1;
	Listhead->next=Student_head;
	p=Listhead;
	//找到删除节点 
	while(p->next!=NULL&&strcmp(p->next->StuInf.studentnumber,delete_studentnumber)!=0){
		p=p->next;
	}	
	//没找到则为空无法删除 
	if(p->next==NULL){
		printf("\t\t\t\t未查找到该学生，删除失败，自动返回！\n\n");
		printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else {
		if(p->next->StuInf.hasborrowed!=0){//如果有借阅信息也无法删除 
			printf("\t\t\t\t该学生还存在借阅书籍情况，无法删除!\n\n");
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
			p=Listhead;
			Listhead=Listhead->next;
			free(p);
			return Listhead;
		}else{			
			p1=p->next;
			p->next=p->next->next;
			free(p1);
			p=Listhead;
			Listhead=Listhead->next;
			free(p);
			(*allstudent_number)--;//学生信息删除成功数目-1 
			printf("\t\t\t\t学生信息删除成功！\n\n");
			printf("\t\t\t\t〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n\n");
			return Listhead;
		}
	}
	
}

struct BookStore* Search_Book_by_booknumber(struct BookStore*Book_head,char search_booknumber[20]){
	struct BookStore* p;
	//通过书号查书，利用strcmp来查找书籍 
	p=Book_head;
	while(p!=NULL){
		if(strcmp(p->BookInf.booknumber,search_booknumber)==0){
			break;
		}
		p=p->next;
	}
	struct BookStore* CopyNode=(struct BookStore*)malloc(sizeof(struct BookStore));//找到就malloc一个节点来复制信息 
	//p不空则复制，空返回NULL 
	if(p){
		CopyNode->BookInf=p->BookInf;
		CopyNode->next=NULL;
		return CopyNode;
	}else {
		return NULL;
	}
}

struct BookStore* Search_Book_by_title(struct BookStore*Book_head,char search_title[20]){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p1,*p2;
	Listhead->next=NULL;
	p1=Book_head;
	p2=Listhead;
	//利用模糊书名查找时 
	while(p1){//strstr找到是否是子字符串 
		if(strstr(p1->BookInf.title,search_title)!=NULL){
			struct BookStore* FindNode=(struct BookStore*)malloc(sizeof(struct BookStore));
			FindNode->next=NULL;
			FindNode->BookInf=p1->BookInf;
			p2->next=FindNode;
			p2=FindNode;
		}
		p1=p1->next; 
	}
	p2=Listhead;
	Listhead=Listhead->next;
	free(p2);
	return Listhead;
}

struct BookStore* Search_Book_by_category(struct BookStore*Book_head,char search_category[20]){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p1,*p2;
	Listhead->next=NULL;
	p1=Book_head;
	p2=Listhead;
	while(p1){//通过类型查找，strcmp来比较 
		if(strcmp(p1->BookInf.category,search_category)==0){
			struct BookStore* FindNode=(struct BookStore*)malloc(sizeof(struct BookStore));
			FindNode->next=NULL;
			FindNode->BookInf=p1->BookInf;
			p2->next=FindNode;
			p2=FindNode;
		}
		p1=p1->next;
	}
	p2=Listhead;
	Listhead=Listhead->next;
	free(p2);
	return Listhead;
}

struct BookStore* Search_Book_by_writer(struct BookStore*Book_head,char search_writer[20]){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p1,*p2;
	Listhead->next=NULL;
	p1=Book_head;
	p2=Listhead;
	while(p1){//通过strcmp比较作者名来查找 
		if(strcmp(p1->BookInf.writer,search_writer)==0){
			struct BookStore* FindNode=(struct BookStore*)malloc(sizeof(struct BookStore));
			FindNode->next=NULL;
			FindNode->BookInf=p1->BookInf;
			p2->next=FindNode;
			p2=FindNode;
		}
		p1=p1->next;
	}
	p2=Listhead;
	Listhead=Listhead->next;
	free(p2);
	return Listhead;
}

struct StudentStore* Find_Student(struct StudentStore* Student_head,char using_studentnumber[20]){
	struct StudentStore* p=Student_head;//查找某一学生节点通过strcmp比较获得 
	while(p){
		if(strcmp(p->StuInf.studentnumber,using_studentnumber)==0){
			break;
		}
		p=p->next;
	}
	return p;
}

struct BookStore* Find_Book(struct BookStore* Book_head,char borrow_book[20]){
	struct BookStore* p=Book_head;//查找某一图书节点，通过strcmp比较获得 
	while(p){
		if(strcmp(p->BookInf.booknumber,borrow_book)==0){
			break;
		}
		p=p->next;
	}
	return p;
}


struct Date* Calculate_Date(struct Date Today){
	//计算日期，计算从今天开始60天后是哪一天 
	struct Date* Back_day=(struct Date*)malloc(sizeof(struct Date));
	int day_tap[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int year=Today.year,month=Today.month,day=Today.day;
	int isprime=0;
	int dayquantity=60;
	if((year%4==0&&year%100==0)||(year%100==0)){
			isprime=1;
		}
	while(dayquantity!=0){
		dayquantity--;
		day++;
		if(day>day_tap[month]){
			if(month==2&&isprime==1){
				isprime=0;
			}else {
				day=1;
				month++;
				if(month>12){
					year++;
					month=1;
				}
			}
		}
	}
	Back_day->day=day;
	Back_day->month=month;
	Back_day->year=year;
	return Back_day;    
}

int isLeapYear(int year){//闰年判断 
	return((year%4==0&&year%100!=0)||year%400==0);
}

int SumDay(int year,int month,int day){
	//计算总共天数 
	int day_tap[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(isLeapYear(year))day_tap[2]++;
	int sum=0;
	int i;
	for(i=1;i<year;i++){
		sum+=365;
		if(isLeapYear(i)){
			sum++;
		}
	}
	for(i=1;i<month;i++){
		sum+=day_tap[i];
	}
	sum+=day;
	return sum;
}

int Calculate_Date_Difference(struct Date Today,struct Date borrowdate){
	int difference_day=SumDay(Today.year,Today.month,Today.day)-SumDay(borrowdate.year,borrowdate.month,borrowdate.day);
	difference_day-=60;
	//算差值 
	if(difference_day>0){
		return difference_day;
	}else {
		return 0;
	}

}

void FreedomList(struct BookStore* FindLine){
	struct BookStore* p1,*p2;//释放空间 
	p1=FindLine;
	while(p1){
		p2=p1;
		p1=p1->next;
		free(p2);
	}
	return;
}

void Freedom_Stu_List(struct StudentStore* Student_head){
	struct StudentStore* p1,*p2;//释放空间 
	p1=Student_head;
	while(p1){
		p2=p1;
		p1=p1->next;
		free(p2);
	}
	return ;
}

void Store_Book_Information(struct BookStore*Book_head,int allbook_number){
	FILE *fp;
	//将经过处理后的数据再次存回图书信息库 
	if((fp=fopen("BookStore4","wb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	int n=allbook_number;
	fwrite(&n,sizeof(int),1,fp);
	struct BookStore*p=Book_head;
	while(p!=NULL){
		fwrite(&(p->BookInf),sizeof(struct BookInformation),1,fp);
		p=p->next;
	}
	fclose(fp);
	return;
}

void Store_Student_Information(struct StudentStore*Student_head,int allstudent_number){
	FILE *fp;
	//将经过处理后的数据再次存回 
	if((fp=fopen("StudentStore4","wb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	int n=allstudent_number;
	fwrite(&n,sizeof(int),1,fp);
	struct StudentStore*p=Student_head;
	while(p!=NULL){
		fwrite(&(p->StuInf),sizeof(struct StudentInformation),1,fp);
		p=p->next;
	}
	fclose(fp);
	return;
}















