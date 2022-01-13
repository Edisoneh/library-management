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

struct BookStore* Read_Book_Storage(int *allbook_number);//ͼ����Ϣ�ļ���ȡ �����ļ��еĵ�һ��int���ͣ�4���ֽڣ�д��allbook_number���ں���������ʾ�� 
struct StudentStore* Read_Student_Storage(int *allstudent_number);//ѧ����Ϣ�ļ���ȡ �� ���ļ��еĵ�һ��int���ͣ�4���ֽڣ�д��allstudent_number���ں���������ʾ�� 

void Print_Book(struct BookStore*Book_head);//ͨ������һ��ͷ�ڵ㣬���������������е�ͼ����Ϣ 

struct BookStore* Insert_Book(struct BookStore*Book_head,struct BookStore*newbook,int *allbook_number);//����ͷ�ڵ㣬��������ݣ��Լ������ϵ����������Ŀ 
struct StudentStore* Insert_Student(struct StudentStore* Student_head,struct StudentStore* newstudent,int *allstudent_number);//����ͷ�ڵ㣬��ѧ�������ݣ��Լ�����������ѧ������Ŀ 

struct BookStore* Delete_Book(struct BookStore*Book_head,char delete_booknumber[20],int *allbook_number);//ͨ��������ţ�ɾ�������ϵ��鼮�����ı�����Ŀ��ֵ 
struct StudentStore* Delete_Student(struct StudentStore*Student_head,char delete_studentnumber[20],int *allstudent_number);//ͨ������ѧ��ѧ�ţ�ɾ�������ϵ�ѧ����Ϣ�����ı�ѧ����Ŀ 

struct BookStore* Search_Book_by_booknumber(struct BookStore*Book_head,char search_booknumber[20]);//ͨ����ţ��������������鼮�� 
struct BookStore* Search_Book_by_title(struct BookStore*Book_head,char search_title[20]);//ͨ�������� �������������鼮�� 
struct BookStore* Search_Book_by_category(struct BookStore*Book_head,char search_category[20]);//ͨ�����ͣ��������������鼮 
struct BookStore* Search_Book_by_writer(struct BookStore*Book_head,char search_writer[20]);//ͨ�����ߣ��������������鼮�� 

struct StudentStore* Find_Student(struct StudentStore* Student_head,char using_studentnumber[20]);//ͨ��ѧ�ţ�������������ĳλѧ���� 
struct BookStore* Find_Book(struct BookStore* Book_head,char borrow_book[20]);//ͨ����ţ�������������ĳ���鼮�� 

int isLeapYear(int year);//�ж��Ƿ�Ϊ���� 
int SumDay(int year,int month,int day);//���������� 
int Calculate_Date_Difference(struct Date Today,struct Date borrowdate);//�����ֵ�����ڷ����жϡ� 
struct Date* Calculate_Date(struct Date Today); //���������º��Ǽ��š� 

void FreedomList(struct BookStore* FindLine);//�ͷ�ֻ��һ��ʹ�ö�malloc�����Ŀռ� 
void Freedom_Stu_List(struct StudentStore* Student_head); 
void Store_Book_Information(struct BookStore*Book_head,int allbook_number);//�洢ͼ����Ϣ 
void Store_Student_Information(struct StudentStore*Student_head,int allstudent_number);//����ѧ����Ϣ 
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
	
	int allbook_number=0,allstudent_number=0; 	//ͨ��������ȡ�ļ���֪����Ŀǰͼ������洢�Ĳ����Լ�ѧ����Ŀ�� 
	struct BookStore* Book_head=Read_Book_Storage(&allbook_number);//��ȡ�ļ� 
	struct StudentStore* Student_head=Read_Student_Storage(&allstudent_number);//��ȡ�ļ� 
	
	printf("\t\t\t\t\t��������������������������������\n\n");
	printf("\t\t\t\t\t    ��ӭʹ��ͼ��ݹ���ϵͳ!\n\n");
	printf("\t\t\t\tĿǰͼ��ݺ�����Ŀ��%d\tѧ����Ŀ��%d\n\n",allbook_number,allstudent_number);
	printf("\t\t\t\t�Ƿ����ͼ��ݹ���ϵͳ������������1���˳�������0��\n\n");
	int enterkey;
	printf("\t\t\t\t��������˳���ѡ��<0,1>:");
	int count1=0;	//��¼�����жϴ����������жϴ�������3�����Զ��˳�ϵͳ�� 
	//ʹ��do while���ȽϷ���
	 
	do{
		
		count1++;
		scanf("%d",&enterkey);
		printf("\n");
		if(count1>3){
			printf("\t\t\t\t����������Զ�Ĭ���˳�ϵͳ��\n\n");
			enterkey=0;
			break;
		}
		if(enterkey!=0&&enterkey!=1){
			printf("\t\t\t\t����������������룡��������˳���ѡ��<0,1>:");
		}
	}while(enterkey!=0&&enterkey!=1);
	
	
	if(enterkey==0){
		
		printf("\t\t\t\t\t\tлл����ʹ��,�ټ���\n\n"); 

	}else if(enterkey==1){
		while(1){
			int outkey2=0;
			printf("\t\t\t\t������������������������������������������������\n\n");
			printf("\t\t\t\t\t\t ͼ���ϵͳ\n\n");
			printf("\n");
			printf("\t\t\t\t[1]����Աģʽ------------------------[2]��ѯͼ��\n\n"); 
			printf("\t\t\t\t[3]��ʾ�����鼮----------------------[4]��ѯ������Ϣ\n\n");
			printf("\t\t\t\t[5]�黹�鼮--------------------------[6]�����鼮\n\n");
			printf("\t\t\t\t[0]�˳�\n\n\n");
			printf("\t\t\t\t������������������������������������������������\n\n"); 
			int choice1;
			printf("\t\t\t\t��ѡ��<0~6>:"); 
			scanf("%d",&choice1); //���ú�����switch case 
			getchar();
			printf("\n");
			char key1[20];
			char key2[20]="123456";//����Ա��������
			 
			switch(choice1){
				case 0:outkey2=1;break;
				case 1:	
					//����Աģʽ�����ǵ�����ÿһ���˶��ܽ��룬������Ҫ�������� 
					printf("\t\t\t\t���������Ա���룺");
					gets(key1);
					printf("\n");
					if(strcmp(key1,key2)!=0){
						printf("\t\t\t\t����Ա��������������Զ��˳���ģʽ\n\n");
						printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");
						printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
							printf("\t\t\t\t������������������������������������������������\n\n");
							printf("\t\t\t\t\t\t ����Աģʽ\n\n");
							printf("\t\t\t\t[1]���ͼ��=========================[2]ɾ��ͼ��\n\n");
							printf("\t\t\t\t[3]���ѧ��=========================[4]ɾ��ѧ��\n\n");
							printf("\t\t\t\t[0]�˳�\n\n\n");
							printf("\t\t\t\t������������������������������������������������\n\n");
							printf("\t\t\t\t��ѡ��<0~4>:");
							int choice2;
							scanf("%d",&choice2);//ͬ������ʹ��switch case 
							getchar();
							printf("\n"); 
							switch(choice2){
								case 0:
									printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");//����ѯ�� 
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
												printf("\t\t\t\t������������������������������������������������\n\n");
												printf("\t\t\t\t\t\t ���ģʽ\n\n");
												struct BookStore* newbook=(struct BookStore*)malloc(sizeof(struct BookStore)); 
												newbook->next=NULL;
												printf("\t\t\t\t�������������ţ�");
												gets((newbook->BookInf).booknumber);
												printf("\n\t\t\t\t�����������������");
												gets((newbook->BookInf).title);
												printf("\n\t\t\t\t��������������ࣺ");
												gets((newbook->BookInf).category);
												printf("\n\t\t\t\t��������������ߣ�");
												gets((newbook->BookInf).writer);
												printf("\n\t\t\t\t������������ܿ�棺");
												scanf("%d",&((newbook->BookInf).storagecapcity));
												getchar();
												printf("\n\t\t\t\t�����������ѳ��������");
												scanf("%d",&((newbook->BookInf).hasborrowed));
												getchar();
												newbook->BookInf.surpluse=newbook->BookInf.storagecapcity-newbook->BookInf.hasborrowed;
												printf("\n");					
												
												Book_head=Insert_Book(Book_head,newbook,&allbook_number); //����ͼ�麯�����������������洢�鼮�����ͷ�ڵ㣬��������ݣ��Լ������е������鼮����Ŀ����һ����number++ 
													
												printf("\t\t\t\t�Ƿ���Ҫ��������ͼ�����⣿\n\n");
												printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
												int choice3=0;
												scanf("%d",&choice3);
												printf("\n");
												getchar();
												if(choice3!=1){
													break;
												}
											}
										printf("\t\t\t\t�Ƿ���Ҫ����ʹ�ù���Աģʽ��\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
										int choice4=0;
										scanf("%d",&choice4);
										printf("\n");
										getchar();
										if(choice4!=1){
											printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");
											printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t\t\t ͼ�����ģʽ\n\n"); 
										printf("\t\t\t\t������Ҫɾ����ͼ�����ţ�");
										char delete_booknumber[20];
										gets(delete_booknumber);
										printf("\n");
										Book_head=Delete_Book(Book_head,delete_booknumber,&allbook_number);//Ϊ�˱�֤�鼮ɾ����׼ȷ�ԣ��������ɾ��������Ϊͷ�ڵ㣬ɾ�����ţ��������������ɾ���ɹ�������-- 
										printf("\t\t\t\t�Ƿ���Ҫ��������ͼ����⣿\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t�Ƿ���Ҫ����ʹ�ù���Աģʽ��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
									int choice6=0;
									scanf("%d",&choice6);
									printf("\n");
									getchar();
									if(choice6!=1){
										printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t\t\t ѧ����Ϣ���ģʽ\n\n");
										struct StudentStore* newstudent=(struct StudentStore*)malloc(sizeof(struct StudentStore)); 
										newstudent->next=NULL;
										printf("\t\t\t\t��������ѧ����ѧ�ţ�");
										gets(newstudent->StuInf.studentnumber);
										newstudent->StuInf.hasborrowed=0;
										printf("\n");					
				
										Student_head=Insert_Student(Student_head,newstudent,&allstudent_number);//������ѧ������������ͷ�ڵ㣬��ѧ��ѧ�ţ�����ѧ����Ŀ�����һ��ѧ���ɹ�������++ 
				
										printf("\t\t\t\t�Ƿ���Ҫ��������ѧ����Ϣ��⣿\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t�Ƿ���Ҫ����ʹ�ù���Աģʽ��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
									int choice5=0;
									scanf("%d",&choice5);
									printf("\n");
									getchar();
									if(choice5!=1){
											printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");
											printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t\t\t ѧ����Ϣ����ģʽ\n\n"); 
										printf("\t\t\t\t������Ҫɾ����ѧ����ѧ�ţ�");
										char delete_studentnumber[20];
										gets(delete_studentnumber);
										printf("\n");
										Student_head=Delete_Student(Student_head,delete_studentnumber,&allstudent_number);//ѧ����Ϣɾ��������ͷָ�룬ѧ��ѧ�ţ�����ѧ����Ŀ��ɾ���ɹ�������-- 
										printf("\t\t\t\t�Ƿ���Ҫ��������ѧ����Ϣ���⣿\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
										int choice3=0;
										scanf("%d",&choice3);
										printf("\n");
										getchar();
										if(choice3!=1){
											break;
										}
									}
									printf("\t\t\t\t�Ƿ���Ҫ����ʹ�ù���Աģʽ��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
									int choice7=0;
									scanf("%d",&choice7);
									printf("\n");
									getchar();
									if(choice7!=1){
										printf("\t\t\t\t�Ƿ񷵻���һ����\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
									printf("\t\t\t\t����������Զ��˳��ò˵���������һ���˵�������������ٴν���ò˵���лл��\n\n");
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
						printf("\t\t\t\t������������������������������������������������\n\n");
						printf("\t\t\t\t\t\t ��ѯ�鼮ģʽ\n\n");
						printf("\t\t\t\t[1]��Ų���=========================[2]��������\n\n");
						printf("\t\t\t\t[3]���Ͳ���=========================[4]���߲���\n\n");
						printf("\t\t\t\t[0]�˳�\n\n");
						printf("\t\t\t\t������������������������������������������������\n\n");
						printf("\t\t\t\t��ѡ��<0~4>:");
						int choice_l2;
						scanf("%d",&choice_l2);//�����ѯ�鼮ģʽ��������Сģʽ����Ȼʹ��switch case����ʾ 
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
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t\t\t ��Ų���ģʽ\n\n");
									printf("\t\t\t\t��������Ҫ��ѯ�鼮����ţ�");
									gets(search_booknumber);
									printf("\n");
									struct BookStore* Find_Node=Search_Book_by_booknumber(Book_head,search_booknumber);//��Ų�ѯ���ò�ѯ������������һ���飬���м�Ϊһ���ڵ㡣 
									if(Find_Node==NULL){
										printf("\t\t\t\t�Բ����������ҵ���Ų����ڣ�\n\n");//��Ų�������Find_NodeΪ�� 
										printf("\t\t\t\t������������������������������������������������\n\n");
									}else{
										Print_Book(Find_Node);
										free(Find_Node);//��Ϊ�Ƕ�mallo�����Ĳ�ѯ�ɹ�֮����ý���free�ͷſռ� 
										printf("\t\t\t\t����ɹ���\n\n");
										printf("\t\t\t\t������������������������������������������������\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t�Ƿ����ʹ����Ų�ѯģʽ��\n\n");//�Ż����ٴ�ѯ�� 
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
								printf("\t\t\t\t�Ƿ����ʹ�ò�ѯ�鼮ģʽ��\n\n");
								printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t\t\t ��������ģʽ\n\n");
									printf("\t\t\t\t��������Ҫ��ѯ�鼮��������");
									gets(search_title);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_title(Book_head,search_title);//������ѯ������������ģ���� 
									if(FindLine==NULL){
										printf("\t\t\t\t�Բ��𣬲��������������ص��鼮!\n\n");//��������ڣ����������� 
										printf("\t\t\t\t������������������������������������������������\n\n");
									}else {
										Print_Book(FindLine);//�ҵ����鼮���ܲ�ֹһ�������Կ�����һ�����ڵ����������� 
										FreedomList(FindLine);//malloc�����Ŀռ���Ҫ����free�ͷ� 
										printf("\t\t\t\t����ɹ���\n\n");
										printf("\t\t\t\t������������������������������������������������\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t�Ƿ����ʹ��������ѯģʽ��\n\n");//�Ż�ѯ�� 
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
								printf("\t\t\t\t�Ƿ����ʹ�ò�ѯ�鼮ģʽ��\n\n");//�Ż�ѯ�� 
								printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t\t\t ���Ͳ���ģʽ\n\n");
									printf("\t\t\t\t��������Ҫ��ѯ�鼮�����ͣ�");
									gets(search_category);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_category(Book_head,search_category);
									if(FindLine==NULL){
										printf("\t\t\t\t�Բ����������ҵ��鼮���Ͳ����ڣ�\n\n");//��ѯ���������鼮�������ӡ��� 
										printf("\t\t\t\t������������������������������������������������\n\n");
									}else {
										Print_Book(FindLine);//����һ�����͵��鼮��ֹһ�� 
										FreedomList(FindLine);//�ͷſռ� 
										printf("\t\t\t\t����ɹ���\n\n");
										printf("\t\t\t\t������������������������������������������������\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t�Ƿ����ʹ�����Ͳ�ѯģʽ��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
								printf("\t\t\t\t�Ƿ����ʹ�ò�ѯ�鼮ģʽ��\n\n");
								printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t\t\t ���߲���ģʽ\n\n");
									printf("\t\t\t\t��������Ҫ��ѯ�鼮�����ߣ�");
									gets(search_writer);
									printf("\n");
									struct BookStore* FindLine=Search_Book_by_writer(Book_head,search_writer);
									if(FindLine==NULL){
										printf("\t\t\t\t�Բ��𣬲����ڸ����ߵ��鼮��\n\n");//δ��ѯ�������ߵ��鼮���ӡ��� 
										printf("\t\t\t\t������������������������������������������������\n\n");
									}else {
										Print_Book(FindLine);//��ӡ�����ߵ��鼮 
										FreedomList(FindLine);//�ͷſռ� 
										printf("\t\t\t\t����ɹ���\n\n");
										printf("\t\t\t\t������������������������������������������������\n\n");
									}
									int choice_s1=0;
									printf("\t\t\t\t�Ƿ����ʹ�����߲�ѯģʽ��\n\n");//�Ż�ѯ�� 
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
								printf("\t\t\t\t�Ƿ����ʹ�ò�ѯ�鼮ģʽ��\n\n");
								printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
								printf("\t\t\t\t����������Զ��˳��ò˵���\n\n");
								break;
						}
						if(outkey_m1==1){
							break;
						}
					}
					printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");//�Ż�ѯ�� 
					printf("\t\t\t\t����ѡ��1������ѡ��0,<0,1>��"); 
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
					printf("\t\t\t\t������������������������������������������������\n\n");
					printf("\t\t\t\t\t\t ��ʾ�����鼮ģʽ\n\n"); //��ʾ�����鼮��ͨ��ͷ�ڵ��ӡ 
					Print_Book(Book_head);
					printf("\t\t\t\t������������������������������������������������\n\n");
					printf("\t\t\t\t�Ƿ���Ҫ����ʹ��ͼ���ϵͳ��\n\n"); 
					printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
						printf("\t\t\t\t������������������������������������������������\n\n");
						printf("\t\t\t\t\t\t ��ѯ������Ϣģʽ\n\n");//��������ѧ�ţ��ж��Ƿ���ڸ�ѧ����Ϣ�� 
						printf("\t\t\t\t���������ѧ�ţ�");
						char search_studentnumber[20];
						gets(search_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,search_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\tѧ���������򲻴��ڸ�ѧ����Ϣ,�������ȷ���Լ�����Ϣ\n\n");
							printf("\t\t\t\t������������������������������������������������\n\n");
						}else{
							printf("\t\t\t\tѧ����Ϣ��\n\n");//��ӡ��ѧ���Ľ�����Ϣ 
							printf("\t\t\t\tѧ�ţ�%s\t�ѽ����鼮��Ŀ��%d\n\n",Find_Student_Node->StuInf.studentnumber,Find_Student_Node->StuInf.hasborrowed);
							int i=0;
							for(i=0;i<Find_Student_Node->StuInf.hasborrowed;i++){
								printf("\t\t\t\t�����鼮��ţ�%s\n",Find_Student_Node->StuInf.borrowbooknum[i]);
								printf("\t\t\t\t����ʱ��Ϊ��%d��%d��%d��\n",Find_Student_Node->StuInf.borrowdate[i].year,Find_Student_Node->StuInf.borrowdate[i].month,Find_Student_Node->StuInf.borrowdate[i].day);
								printf("\t\t\t\t�黹ʱ��Ϊ��%d��%d��%d��\n\n",Find_Student_Node->StuInf.shouldreturndate[i].year,Find_Student_Node->StuInf.shouldreturndate[i].month,Find_Student_Node->StuInf.shouldreturndate[i].day);	
							}
							printf("\t\t\t\t��ѯ�ɹ���\n\n");
							printf("\t\t\t\t������������������������������������������������\n\n");
						}
						printf("\t\t\t\t�Ƿ�������н�����Ϣ��ѯ��\n\n");//�Ż�ѯ�� 
						int choice_m5=0;
						printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
						printf("\t\t\t\t������������������������������������������������\n\n");
						printf("\t\t\t\t\t\t ����ģʽ\n\n");
						printf("\t\t\t\t���������ѧ�ţ�");//����ѧ�Ż��� 
						char using_studentnumber[20];
						gets(using_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,using_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\tѧ���������򲻴��ڸ�ѧ����Ϣ���������ȷ���Լ�����Ϣ\n\n");		
							printf("\t\t\t\t������������������������������������������������\n\n");					
						}else{
							while(1){
								int outkey_m3=0;
								char return_borrow_booknumber[20];
								printf("\t\t\t\t������黹�鼮����ţ�");//��֤�黹�鼮��׼ȷ�ԣ��鼮�����һһ��Ӧ������黹�鼮��� 
								gets(return_borrow_booknumber);
								printf("\n");
								struct BookStore* Find_Book_Node=Find_Book(Book_head,return_borrow_booknumber);
								if(Find_Book_Node==NULL){
									printf("\t\t\t\t�鼮�����Ϣ���������ȷ���Ƿ���ڸ��鼮��������������Ƿ���ȷ\n\n");
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t�Ƿ�����������Ź黹�鼮��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
										printf("\t\t\t\t�黹����:\n\n");//��¼�黹���� 
										time_t timep;
									    struct tm *p;
									    time (&timep);
									    p=gmtime(&timep);
									    Today.year=1900+p->tm_year;
									    Today.month=1+p->tm_mon;
									    Today.day=p->tm_mday;
										printf("\t\t\t\t���������Ϊ��");
										printf("%d��%d��%d��\n",Today.year,Today.month,Today.day); 
										printf("\n");
										int n=Calculate_Date_Difference(Today,Find_Student_Node->StuInf.borrowdate[index]);//�����Ƿ񳬹������£������˵Ļ���������
										struct Date shouldreturndate=Find_Student_Node->StuInf.shouldreturndate[index];
										//�����ǽ��鼮��ṹ���ڲ���������һλ����������������Ž������������ڽ������黹���ڽ�����Ȼ���ٽ����һλɾ����Ȼ��ı�ѧ���ڵ���������Լ���ڵ��ʣ��ͽ�� 
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
											printf("\t\t\t\tӦ�ù黹���ڣ�%d��%d��%d��\n\n",shouldreturndate.year,shouldreturndate.month,shouldreturndate.day);
											printf("\t\t\t\t�����黹ʱ��%d�죬���Ʒ����%fԪ\n\n",n,n*0.2);//�����Ļ�Ҫ��ӡ���� 
										}
										printf("\t\t\t\t�黹�ɹ���\n\n");
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t�Ƿ���Ҫ�����黹�鼮?\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0,<0,1>��");
										int choice_last1=0;
										scanf("%d",&choice_last1);
										getchar();
										printf("\n");
										if(choice_last1!=1){
											outkey_m3=1;
										} 
									}else{
										printf("\t\t\t\t����Ų�δ�����ڽ�����Ϣ�У���ȷ�Ϲ黹�鼮��ţ�лл��\n\n");//���û���Ȿ��Ľ�����Ϣ�򷵻���� 
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t�Ƿ�����������Ź黹�鼮��\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
						printf("\t\t\t\t�Ƿ����½�������鼮ģʽ?\n\n");//�Ż�ѯ�� 
						printf("\t\t\t\t��������1����������0��<0,1>��");
						int choice_last3=0;
						scanf("%d",&choice_last3);
						printf("\n");
						getchar();
						if(choice_last3!=1){
							outkey4=1;
							printf("\t\t\t\t�Ƿ񷵻���һ���˵���\n\n");//�Ż�ѯ�� 
							printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
						printf("\t\t\t\t������������������������������������������������\n\n");
						printf("\t\t\t\t\t\t ����ģʽ\n\n");//������Ȼ��һ������ѧ�� 
						printf("\t\t\t\t���������ѧ�ţ�");
						char using_studentnumber[20];
						gets(using_studentnumber);
						printf("\n");
						struct StudentStore* Find_Student_Node=Find_Student(Student_head,using_studentnumber);
						if(Find_Student_Node==NULL){
							printf("\t\t\t\tѧ���������򲻴��ڸ�ѧ����Ϣ,�������ȷ���Լ�����Ϣ\n\n");//��������ж� 
						}else {
							while(1){
								int outkey_m3=0;
								char borrow_booknumber[20];
								printf("\t\t\t\tΪ��֤�����鼮׼ȷ�ԣ�����������鼮����ţ�");
								gets(borrow_booknumber);
								printf("\n");
								struct BookStore* Find_Book_Node=Find_Book(Book_head,borrow_booknumber);//������ڵ� 
								if(Find_Book_Node==NULL){
									printf("\t\t\t\t�鼮�����Ϣ���������ȷ���Ƿ���ڸ��鼮��������������Ƿ���ȷ\n\n");
									printf("\t\t\t\t������������������������������������������������\n\n");
									printf("\t\t\t\t�Ƿ�����������Ž����鼮��\n\n");
									printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
									int choice_s6=0;
									scanf("%d",&choice_s6);
									getchar();
									printf("\n"); 
									if(choice_s6!=1){
										outkey_m3=1;
									}
								}else {
									if(Find_Student_Node->StuInf.hasborrowed>=MAXSIZE){
										printf("\t\t\t\t������Ŀ�����ﵽ���ֵ��10��������ͣ�����鼮��\n\n");//��������鼮�ﵽ10�������ٽ裬��黹��ſɽ��� 
										printf("\t\t\t\t������������������������������������������������\n\n");
										printf("\t\t\t\t�Զ��˳���ѧ�Ž����鼮ҳ�棡\n\n");
										outkey_m3=1;
									}else {
										if(Find_Book_Node->BookInf.surpluse==0){
											printf("\t\t\t\t���鼮�����������ȴ����˹黹���������ģ�лл��\n\n");//û��ʣ���鼮Ҳ�޷����� 
											printf("\t\t\t\t������������������������������������������������\n\n");
										}else{
											printf("\t\t\t\t�������������ڣ������գ���2021 7 22����"); //������������ 
											struct Date Today;
											scanf("%d%d%d",&Today.year,&Today.month,&Today.day);
											printf("\n");
											//�ı�ڵ����� 
											struct Date*Back_day=Calculate_Date(Today);
											Find_Book_Node->BookInf.hasborrowed++;
											Find_Book_Node->BookInf.surpluse--;
											strcpy(Find_Student_Node->StuInf.borrowbooknum[Find_Student_Node->StuInf.hasborrowed],borrow_booknumber);
											Find_Student_Node->StuInf.borrowdate[Find_Student_Node->StuInf.hasborrowed]=Today;
											Find_Student_Node->StuInf.shouldreturndate[Find_Student_Node->StuInf.hasborrowed]=*Back_day;
											Find_Student_Node->StuInf.hasborrowed++;
											printf("\t\t\t\t���ĳɹ�����ע����%d��%d��%d��ǰ�黹\n\n",Back_day->year,Back_day->month,Back_day->day);
											printf("\t\t\t\t������������������������������������������������\n\n");
										} 
										printf("\t\t\t\t�Ƿ����������Ž����鼮��\n\n");
										printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>:");
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
						printf("\t\t\t\t�Ƿ��ٴν��н���ģʽ?\n\n");
						printf("\t\t\t\t����ѡ��1,����ѡ��0,<0,1>:");
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
					printf("\t\t\t\t����������Զ��˳���������������ٴν������\n\n");break;
	
			}
			
			if(outkey2==1){
				break;
			}
	
		}
	printf("\t\t\t\t������������������������������������������������\n\n");
	printf("\t\t\t\tлл����ʹ��,�ټ���\n\n");
	}
	
	Store_Book_Information(Book_head,allbook_number);//�洢ͼ����Ϣ���� 
	Store_Student_Information(Student_head,allstudent_number);//�洢ѧ��������Ϣ���� 

	FreedomList(Book_head);//�ͷ�malloc�����Ŀռ� 
	Freedom_Stu_List(Student_head);//�ͷ�malloc�����Ŀռ� 

	return 0;
}

//���ļ��ж������ݣ����������� 
struct BookStore* Read_Book_Storage(int *allbook_number){
	FILE *fp;
	
	if((fp=fopen("BookStore4","rb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	fread(allbook_number,sizeof(int),1,fp);//�ļ���ͷ�洢���������е�����Ŀ��������������ʾ�Լ�ͳ�ơ� 
	struct BookStore* ListHead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p;
	ListHead->next=NULL; 
	p=ListHead;
	int i=0;
	//ͨ������������ 
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
//ͬ�� 
struct StudentStore* Read_Student_Storage(int *allstudent_number){
	FILE *fp;
	
	if((fp=fopen("StudentStore4","rb"))==NULL){
		printf("\t\t\t\tcannot open this file\n\n");
	}
	
	fread(allstudent_number,sizeof(int),1,fp);//�ļ���ǰ�ĸ��ֽڴ洢����int����δ������ѧ�������� 
	int i=0;
	struct StudentStore* ListHead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p;
	ListHead->next=NULL; 
	p=ListHead;
	//ͨ������������ 
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
	//ͨ��ͷ�ڵ�������������Ϣ 
	while(p!=NULL){
		printf("\n");
		printf("\t\t\t\t��ţ�%s\t",(p->BookInf).booknumber);
		printf("������%s\n",(p->BookInf).title);
		printf("\t\t\t\t���ͣ�%s\t\t",(p->BookInf).category);
		printf("���ߣ�%s\n",(p->BookInf).writer);
		printf("\t\t\t\t�ܿ�棺%d\t�ѽ����%d\tʣ����Ŀ��%d\n\n",p->BookInf.storagecapcity,p->BookInf.hasborrowed,p->BookInf.surpluse);
		p=p->next;
	} 
}

struct BookStore* Insert_Book(struct BookStore*Book_head,struct BookStore*newbook,int *allbook_number){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p;
	Listhead->next=Book_head;
	p=Listhead;
	//�ҵ�����λ�ã�ͨ��strcmp������ 
	while(p->next!=NULL&&strcmp(newbook->BookInf.booknumber,p->next->BookInf.booknumber)>0){
		p=p->next;
	}
	//���Ϊ����û���ҵ��������ҵ��˺�����ͬ�������ͨ��ѯ�ʼ��� 
	if(p->next!=NULL&&strcmp(newbook->BookInf.booknumber,p->next->BookInf.booknumber)==0){
		printf("\t\t\t\t�������ʧ�ܣ���ȷ���Ƿ�Ϊ�������ӿ�棺\n\n");
		printf("\t\t\t\t����ѡ��1������ѡ��0��<0,1>��");
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
		(*allbook_number)++;  //���ɹ���Ŀ��һ 
		printf("\t\t\t\t�������ɹ���\n\n");
		printf("\t\t\t\t������������������������������������������������\n\n");
		return Listhead;
	} 
}

struct StudentStore* Insert_Student(struct StudentStore*Student_head,struct StudentStore* newstudent,int *allstudent_number){
	struct StudentStore* Listhead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p;
	Listhead->next=Student_head;
	p=Listhead;
	//�ҵ�����λ�ã�ͬ��ͨ��strcmp���ҵ� 
	while(p->next!=NULL&&strcmp(newstudent->StuInf.studentnumber,p->next->StuInf.studentnumber)>0){
		p=p->next;
	}
	//���Ϊ�գ�������ѧ����ĳλѧ����ͬ�����ʧ�� 
	if(p->next!=NULL&&strcmp(newstudent->StuInf.studentnumber,p->next->StuInf.studentnumber)==0){
		printf("\t\t\t\t��ѧ�����ʧ�ܣ���ѧ���Ѵ�����ѧ���⣬�Զ����أ�\n\n");
		printf("\t\t\t\t������������������������������������������������\n\n");
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
		(*allstudent_number)++;//���ɹ���ѧ������+1 
		printf("\t\t\t\t��ѧ�����ɹ���\n\n");
		printf("\t\t\t\t������������������������������������������������\n\n");
		return Listhead;
	}
	
}

struct BookStore* Delete_Book(struct BookStore*Book_head,char delete_booknumber[20],int *allbook_number){
	struct BookStore* Listhead=(struct BookStore*)malloc(sizeof(struct BookStore)),*p,*p1;
	Listhead->next=Book_head;
	p=Listhead;
	//�ҵ�ɾ���Ľڵ� 
	while(p->next!=NULL&&strcmp((((p->next)->BookInf).booknumber),delete_booknumber)!=0){
		p=p->next;
	}
	if(p->next==NULL){//Ϊ����û���ҵ� 
		printf("\t\t\t\tδ���ҵ����鼮��ɾ��ʧ�ܣ��Զ����أ�\n\n");
		printf("\t\t\t\t������������������������������������������������\n\n");
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else {
		
		if(p->next->BookInf.hasborrowed!=0){
			printf("\t\t\t\t���鼮�Դ��ڽ���״̬���޷�ɾ����\n\n");//���ڽ���״̬����Ҳû��ɾ�� 
			printf("\t\t\t\t������������������������������������������������\n\n");
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
			(*allbook_number)--;//����ɹ�����-1 
			printf("\t\t\t\t�鼮����ɹ���\n\n");
			printf("\t\t\t\t������������������������������������������������\n\n");
			return Listhead;
		}
	}
	
}

struct StudentStore* Delete_Student(struct StudentStore*Student_head,char delete_studentnumber[20],int *allstudent_number){
	struct StudentStore* Listhead=(struct StudentStore*)malloc(sizeof(struct StudentStore)),*p,*p1;
	Listhead->next=Student_head;
	p=Listhead;
	//�ҵ�ɾ���ڵ� 
	while(p->next!=NULL&&strcmp(p->next->StuInf.studentnumber,delete_studentnumber)!=0){
		p=p->next;
	}	
	//û�ҵ���Ϊ���޷�ɾ�� 
	if(p->next==NULL){
		printf("\t\t\t\tδ���ҵ���ѧ����ɾ��ʧ�ܣ��Զ����أ�\n\n");
		printf("\t\t\t\t������������������������������������������������\n\n");
		p=Listhead;
		Listhead=Listhead->next;
		free(p);
		return Listhead;
	}else {
		if(p->next->StuInf.hasborrowed!=0){//����н�����ϢҲ�޷�ɾ�� 
			printf("\t\t\t\t��ѧ�������ڽ����鼮������޷�ɾ��!\n\n");
			printf("\t\t\t\t������������������������������������������������\n\n");
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
			(*allstudent_number)--;//ѧ����Ϣɾ���ɹ���Ŀ-1 
			printf("\t\t\t\tѧ����Ϣɾ���ɹ���\n\n");
			printf("\t\t\t\t������������������������������������������������\n\n");
			return Listhead;
		}
	}
	
}

struct BookStore* Search_Book_by_booknumber(struct BookStore*Book_head,char search_booknumber[20]){
	struct BookStore* p;
	//ͨ����Ų��飬����strcmp�������鼮 
	p=Book_head;
	while(p!=NULL){
		if(strcmp(p->BookInf.booknumber,search_booknumber)==0){
			break;
		}
		p=p->next;
	}
	struct BookStore* CopyNode=(struct BookStore*)malloc(sizeof(struct BookStore));//�ҵ���mallocһ���ڵ���������Ϣ 
	//p�������ƣ��շ���NULL 
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
	//����ģ����������ʱ 
	while(p1){//strstr�ҵ��Ƿ������ַ��� 
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
	while(p1){//ͨ�����Ͳ��ң�strcmp���Ƚ� 
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
	while(p1){//ͨ��strcmp�Ƚ������������� 
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
	struct StudentStore* p=Student_head;//����ĳһѧ���ڵ�ͨ��strcmp�Ƚϻ�� 
	while(p){
		if(strcmp(p->StuInf.studentnumber,using_studentnumber)==0){
			break;
		}
		p=p->next;
	}
	return p;
}

struct BookStore* Find_Book(struct BookStore* Book_head,char borrow_book[20]){
	struct BookStore* p=Book_head;//����ĳһͼ��ڵ㣬ͨ��strcmp�Ƚϻ�� 
	while(p){
		if(strcmp(p->BookInf.booknumber,borrow_book)==0){
			break;
		}
		p=p->next;
	}
	return p;
}


struct Date* Calculate_Date(struct Date Today){
	//�������ڣ�����ӽ��쿪ʼ60�������һ�� 
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

int isLeapYear(int year){//�����ж� 
	return((year%4==0&&year%100!=0)||year%400==0);
}

int SumDay(int year,int month,int day){
	//�����ܹ����� 
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
	//���ֵ 
	if(difference_day>0){
		return difference_day;
	}else {
		return 0;
	}

}

void FreedomList(struct BookStore* FindLine){
	struct BookStore* p1,*p2;//�ͷſռ� 
	p1=FindLine;
	while(p1){
		p2=p1;
		p1=p1->next;
		free(p2);
	}
	return;
}

void Freedom_Stu_List(struct StudentStore* Student_head){
	struct StudentStore* p1,*p2;//�ͷſռ� 
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
	//�����������������ٴδ��ͼ����Ϣ�� 
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
	//�����������������ٴδ�� 
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















