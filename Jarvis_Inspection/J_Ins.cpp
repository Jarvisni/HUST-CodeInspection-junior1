#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <thread>
using namespace std;

#define rint register int
#define nextSize 100
#define MaxChar 200

inline void read(int& x) {
	char ch = getchar(); int f = 1; x = 0;
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	x *= f;
}

string KeyWord[100] = { "int","char","float","double","enum","long","short","signed","unsigned","struct","union","void","for","do","while","break","continue","if","else","goto","switch","case","default","return","auto","extern","register","static","const","typedef","volatile","sizeof","incline","restrict","_Bool","_Complex","_Imaginary" };
string KeyToken[100] = { "_INT","_CHAR","_FLOAT","_DOUBLE","_ENUM","_LONG","_SHORT","_SIGNED","_UNSIGNED","_STRUCT","_UNION","_VOID","_FOR","_DO","_WHILE","_BREAK","_CONTINUE","_IF","_ELSE","_GOTO","_SWITCH","_CASE","_DEFAULT","_RETURN","_AUTO","_EXTERN","_REGISTER","_STATIC","_CONST","_TYPEDEF","_VOLATILE","_SIZEOF","_INCLINE","_RESTRICT","_BOOL","_COMPLEX","_IMAGINARY" };
//���Ϲؼ�����ʱ֧�ֵ�99��׼�������½�����Ӽ����ؼ���
//Ĭ��һ��һ�����


typedef struct Function {   //ÿ������Ĭ������������������־�С��20����������С��10
	char re_value[10];      //�����ĺ�������������¼�ļ������к��������ڱȽ�
	char Name[20];
	int parasum;
	char para1[10];
	char para2[10];
	char para3[10];
	struct Function* next;
}Function;

typedef struct FuncList {   //�ڲ��Ӻ���������
	char Name[20];
	struct FuncList* next;
}FuncList;

typedef struct List {      //�����ϸ������������а����Ӻ��������ͷָ��
	struct List* next;
	struct FuncList* head;
}List;

typedef struct Var
{
	char Name[20];
	char type[10];
	int size;
	int realSize;
	int row;
	int kind;
	struct Var* next;
}Var;


typedef struct MiGan
{
	char Name[10];
	int row;
	int n;
	char Mudi[20];
	char yuan[20];
	struct MiGan* next;
}MiGan;

typedef struct HuanChong
{
	char Name[10];
	char type[10];
	int size;
	int realSize;
	struct HuanChong* next;
}HuanChong;

typedef struct BianJie
{
	int row;
	char type[10];
	char num[100];
	struct BianJie* next;
}BianJie;

typedef struct FunctionSOF
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct FunctionSOF* next;
}FunctionSOF;

typedef struct FunctionHOF
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct HuanChong* hlist;
	struct BianJie* bjlist;
	struct FunctionHOF* next;
}FunctionHOF;

typedef struct XiangTongB2
{
	int row;
	char left[20];
	char right[20];
	struct XiangTongB2* next;
}XiangTongB2;

typedef struct FunctionB2
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct HuanChong* hlist;
	struct BianJie* bjlist;
	struct XiangTongB2* xtlist;
	struct FunctionB2* next;
}FunctionB2;

typedef struct Calcu
{
	int row;
	char yuan1[20];
	char yuan2[20];
	char mudi[20];
	struct Calcu* next;
}Calcu;

typedef struct FunctionB3
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct HuanChong* hlist;
	struct Calcu* clist;
	struct FunctionB3* next;
}FunctionB3;

typedef struct FunctionB4
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct FunctionB4* next;
}FunctionB4;

typedef struct FunctionR5
{
	int begin;
	int end;
	struct Var* vlist;
	struct MiGan* mlist;
	struct FunctionR5* next;
}FunctionR5;

char infile1[20];
char infile2[20];
char infile3[20];
char infile4[20];
char infile5[20];
char outfile1[20] = "cfg1.cpp";
char outfile2[20] = "cfg2.cpp";
struct Function* tempfun2;
struct Function* tempfun4;


int CFG();                                       //CFGʹ�ô˺���
void CFG_THR1(char s1[MaxChar], char s2[MaxChar]);//CFG���߳�ʹ�ô˺���
void CFG_THR2(char s1[MaxChar], char s2[MaxChar]);//CFG���߳�ʹ�ô˺���
void CFG_THR3(char s1[MaxChar], char s2[MaxChar]);//CFG���߳�ʹ�ô˺���
void CFG_THR4(char s1[MaxChar], char s2[MaxChar]);//CFG���߳�ʹ�ô˺���
void PreTreat(FILE* inFile, FILE* outFile, char name1[20], char name2[20]);
struct List* CreateList(FILE* fp);
void showCFG(struct List* list);
struct Function* CreateFunction(FILE* fp);
bool PanDuan(char s[MaxChar]);
void GetData(char s[MaxChar], struct Function* f);
int NumOfChar(char s[MaxChar], const char s2[]);
bool PanFunc(char s[MaxChar]);
int XiangTong(char s1[20], char s2[20]);


int SOF();//R4
struct FunctionSOF* CreateFuncR4(FILE* fp);
bool PanFuncR4(char s[MaxChar]);
void V_analysisR4(char s[MaxChar], struct Var* var);
void M_analysisR4(char s[MaxChar], struct MiGan* mig);
bool PanMinR4(char s[MaxChar]);
void Show(FILE* fp, int row);


int HOF();//B1
struct FunctionHOF* CreateFuncB1(FILE* fp);
bool PanFuncB1(char s[MaxChar]);
void V_analysisB1(char s[MaxChar], struct Var* var);
void M_analysisB1(char s[MaxChar], struct MiGan* mig);
void H_analysisB1(char s[MaxChar], struct HuanChong* h);
void BJ_analysisB1(char s[MaxChar], struct BianJie* bj);
bool PanMinB1(char s[MaxChar]);


int INTwidth();//B2
struct FunctionB2* CreateFuncB2(FILE* fp);
bool PanFuncB2(char s[MaxChar]);
void V_analysisB2(char s[MaxChar], struct Var* var);
void M_analysisB2(char s[MaxChar], struct MiGan* mig);
void H_analysisB2(char s[MaxChar], struct HuanChong* h);
void BJ_analysisB2(char s[MaxChar], struct BianJie* bj);
struct XiangTongB2* XT_analysis(char s[MaxChar], struct XiangTongB2* XT);
bool PanMinB2(char s[MaxChar]);
bool PanTongB2(char s[MaxChar]);


int INTcalc();//B3
struct FunctionB3* CreateFuncB3(FILE* fp);
bool PanFuncB3(char s[MaxChar]);
void V_analysisB3(char s[MaxChar], struct Var* var);
void M_analysisB3(char s[MaxChar], struct MiGan* mig);
void H_analysisB3(char s[MaxChar], struct HuanChong* h);
void C_analysisB3(char s[MaxChar], struct Calcu* c);
bool PanMinB3(char s[MaxChar]);
bool PanCalB3(char s[MaxChar]);


int INTSym();//B4
struct FunctionB4* CreateFuncB4(FILE* fp);
bool PanFuncB4(char s[MaxChar]);
void M_analysisB4(char s[MaxChar], struct MiGan* mig);
bool PanMinB4(char s[MaxChar]);


int GSH();//R5
struct FunctionR5* CreateFuncR5(FILE* fp);
bool PanFuncR5(char s[MaxChar]);
int M_analysisR5(char s[MaxChar], struct MiGan* mig);
bool PanMinR5(char s[MaxChar]);


int string_same();//�ַ���ƥ��ʹ�ô˺���
void pretreat1_1(string fileInput, string fileOutput);
void pretreat1_2(string fileInput, string fileOutput);
void Getnext(int next[], string t);
int KMP(string s, string t);



char logo1[] = "\
       __                 _         ____                           __  _               \n\
      / /___ _______   __(_)____   /  _/___  _________  ___  _____/ /_(_)___  ____     \n\
 __  / / __ `/ ___/ | / / / ___/   / // __ \\/ ___/ __ \\/ _ \\/ ___/ __/ / __ \\/ __ \\    \n\
/ /_/ / /_/ / /   | |/ / (__  )  _/ // / / (__  ) /_/ /  __/ /__/ /_/ / /_/ / / / /    \n\
\\____/\\__,_/_/    |___/_/____/  /___/_/ /_/____/ .___/\\___/\\___/\\__/_/\\____/_/ /_/     \n\
                                              /_/                                      \n\
";

char logo2[] = "\
  ________                __                                              __    ____  \n\
 /_  __/ /_  ____ _____  / /_______   _________     ____ ___  __  _______/ /_  / / /  \n\
  / / / __ \\/ __ `/ __ \\/ //_/ ___/  / ___/ __ \\   / __ `__ \\/ / / / ___/ __ \\/ / /   \n\
 / / / / / / /_/ / / / / ,< (__  )  (__  ) /_/ /  / / / / / / /_/ / /__/ / / /_/_/    \n\
/_/ /_/ /_/\\__,_/_/ /_/_/|_/____/  /____/\\____/  /_/ /_/ /_/\\__,_/\\___/_/ /_(_|_)     \n\
                                                                                      \n\
";

int main()       //�պ�������Ĭ����һ���ո�,������ָ���Ͳ�����int*���Ϊint
{
	int op = 0, op2 = 0;
	while (op != 4)
	{
		op2 = 0;
		system("cls");
		printf("%s", logo1);
		printf("Welcome to Jarvis Inspection!\n");
		printf("You Can Analyse The Homology or Discover The Loophole\n");
		printf("Please Choose from below(input 1 or 2) : 1��ͬԴ�Լ��  2��©�����\n");
		printf("input 4 to quit the exe\n");
		scanf("%d", &op);
		if (op == 1)
		{
			while (op2 != 4)
			{
				system("cls");
				printf("%s", logo1);
				printf("Which kind of homology analysis would you choose?\n");
				printf("(input 1 or 2 or 3) 1���ַ���  2��CFG  3�����߳�CFG\n");
				printf("input 4 to quit this section\n");
				scanf("%d", &op2);

				if (op2 == 1)
				{
					string_same();
				}
				else if (op2 == 2)
				{
					CFG();
				}
				else if (op2 == 3)
				{
					char infile1[20];
					char infile2[20];
					char infile3[20];
					char infile4[20];
					char infile5[20];
					printf("Jarvis>  ������Ҫ���ĸ��ļ���Ϊ�Ƚ�ģ��(���� 3.c)\n");
					scanf("%s", infile1);
					printf("Jarvis>  �����ĸ�����֮���бȽϵ��ļ�(����4 4 4 4��\n");
					scanf("%s", infile2);
					scanf("%s", infile3);
					scanf("%s", infile4);
					scanf("%s", infile5);
					thread first(CFG_THR1, infile1, infile2);
					thread second(CFG_THR2, infile1, infile3);
					thread third(CFG_THR3, infile1, infile4);
					thread fourth(CFG_THR4, infile1, infile5);

					first.join();
					second.join();
					third.join();
					fourth.join();

					system("pause");
				}


			}
		}
		else if (op == 4)
		{
			system("cls");
			printf("%s", logo1);
			printf("%s", logo2);
			printf("Thanks for using the Jarvis Inspection!!!\n");
			return 0;
		}
		else if (op == 2)
		{
			while (op2 != 7)
			{
				system("cls");
				printf("%s", logo1);
				printf("Which kind of loophole analysis would you choose?\n");
				printf("(input 1~6) 1��ջ���  2�������  3������������  4�������������  5�������������  6����ʽ���ַ���©��  \n");
				printf("input 7 to quit this section\n");
				scanf("%d", &op2);

				if (op2 == 1)
				{
					SOF();
				}
				else if (op2 == 2)
				{
					HOF();
				}
				else if (op2 == 3)
				{
					INTwidth();
				}
				else if (op2 == 4)
				{
					INTcalc();
				}
				else if (op2 == 5)
				{
					INTSym();
				}
				else if (op2 == 6)
				{
					GSH();
				}
			}
		}

	}


}








void pretreat1_1(string fileInput, string fileOutput)
{
	ifstream filein(fileInput.c_str());//��ȡ�����ļ�
	ofstream fileout(fileOutput);      //Ԥ�������򱣴浽"temp1.cpp"��
	unsigned int i, j, k;
	unsigned int size;
	string instring, outstring;           //�ַ��� instring,outstring
	bool flag = false;                      //���ڱ��
	while (getline(filein, instring))     //��ȡ�ļ�����
	{
		size = instring.size();
		outstring = "";                 //outstringԤ���
		flag = false;                   //flag��ʼ��
		for (i = 0; i < size; )         //������һ���ڵĴ���
		{
			if (instring[i] == '\t' || instring[i] == '\n')
			{
				i++;
				continue;
			}

			while (instring[i] == ' ')//����ʵ����ǰ��ո�Ԥ�������пո��������һ��
			{
				i++;
				flag = true;
			}
			if (flag == true)
			{
				outstring += " ";
				flag = false;
			}

			if (instring[i] == '/' && instring[i + 1] == '/')  //���ڵ���ע�ͽ��д���ע�;��ǵ����Ļ��л��
			{
				break;
			}
			else if (instring[i] == '/' && instring[i + 1] == '*') //���ڶ���ע�ͽ��д�����Ҫֱ��*/��ȫ���𣬿��ǵ���һ���ַ���Ŀո�
			{
				while (instring[i] != '*')
				{
					if (instring[i] == '\n')
					{
						fileout << outstring << endl;  //���ַ���outstring���浽fileout;
						getline(filein, instring);     //Ĭ��/**/����ע�Ͳ��������ĩ��
						i = 0;
						continue;
					}
					i++;
				}
				if (instring[i + 1] == '/')
				{
					i++; i++;
					continue;
				}
			}


			j = i;//�˴�j��i��������ע�ͺ��ٴ������ķǿո��ע���ַ���λ��
			if (instring[j] == ';')
			{
				outstring += "_SEMI";   //�зֺžͽ������滻
				break;                  //һ��֮�зֺŽ�β��Ĭ�Ϸֺź�û����䣬��û�п������ַ���䣨�����ƣ�
			}
			else if (instring[j] == '{')
			{
				outstring += "_LSP";    //��������Ž������滻��Ĭ�����Ҵ����ŵ������У������ƣ�
				break;                  //һ��֮���������Ҵ�����Ĭ�ϴ���ֻ��һ������
			}
			else if (instring[j] == '}')
			{
				outstring += "_RSP";    //���Ҵ����Ž������滻��Ĭ�����Ҵ����ŵ������У������ƣ�
				break;                  //һ��֮���������Ҵ�����Ĭ�ϴ���ֻ��һ������
			}
			else if (instring[j] == '(')
			{
				outstring += "_LP";    //�������Ž������滻
				i = j + 1;               //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == ')')
			{
				outstring += "_RP";    //�������Ž������滻
				i = j + 1;               //����һ���ַ���������Ԥ����
				if (i >= size) break;  //�����������Ž�β�����
				continue;
			}
			else if (instring[j] == '[')
			{
				outstring += "_LSB";    //�������Ž������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == ']')
			{
				outstring += "_RSB";    //���ҷ����Ž������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '+')
			{
				outstring += "_PLUS";    //�мӺŽ������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '-')
			{
				outstring += "_MINUS";    //�м����Ž������滻
				i = j + 1;                  //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '*')
			{
				outstring += "_MULTIPLED";    //�г˺Ž������滻
				i = j + 1;                      //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '/')
			{
				outstring += "_DIVIDED";    //�г��Ž������滻
				i = j + 1;                    //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '=')
			{
				outstring += "_ASSIGN";    //�еȺŽ������滻
				i = j + 1;                 //����һ���ַ���������Ԥ����
				continue;
			}


			while (instring[j] != ' ' && instring[j] != '(' && instring[j] != ')' && instring[j] != ';' && instring[j] != '+' && instring[j] != '-' && instring[j] != '*' && instring[j] != '/' && instring[j] != '=')//���϶����ǣ���ӵ�һ���ǿո�ֱ����һ�������ո��м���ַ��������ǹؼ��ֻ��Ǳ�ʶ��
				j++;
			string temp = instring.substr(i, j - i);
			for (rint k = 0; k < 37; k++)
			{
				if (KeyWord[k] == temp)
				{
					outstring += KeyToken[k];   //�йؼ��ֽ������滻
					flag = true;
					break;
				}
			}
			if (flag == true)  //�ٴδ���ո��������һ�ǿո��ע��   �о���Ҫ����һ������ѭ�����
			{
				flag = false;
				i = j;
				continue;
			}
			else               //���ǹؼ��֣����Ǳ�ʶ��
			{
				outstring += "_ID";   //�б�ʶ���������滻
				i = j;
				continue;
			}

		}
		if (outstring == "")
			fileout << outstring;          //���ַ�����ʲô���������
		else
			fileout << outstring << endl;  //���ַ���outstring���浽fileout

	}
}

void pretreat1_2(string fileInput, string fileOutput)
{
	ifstream filein(fileInput.c_str());//��ȡ�����ļ�
	ofstream fileout(fileOutput);      //Ԥ�������򱣴浽"temp1.cpp"��
	unsigned int i, j, k;
	unsigned int size;
	string instring, outstring;           //�ַ��� instring,outstring
	bool flag = false;                    //���ڱ��
	while (getline(filein, instring))     //��ȡ�ļ�����
	{
		size = instring.size();
		outstring = "";                 //outstringԤ���
		flag = false;                   //flag��ʼ��
		for (i = 0; i < size; )         //������һ���ڵĴ���
		{
			if (instring[i] == '\t' || instring[i] == '\n')
			{
				i++;
				continue;
			}

			while (instring[i] == ' ')//����ʵ����ǰ��ո�Ԥ�������пո��������һ��
			{
				i++;
				flag = true;
			}
			if (flag == true)
			{
				outstring += " ";
				flag = false;
			}

			if (instring[i] == '/' && instring[i + 1] == '/')  //���ڵ���ע�ͽ��д���ע�;��ǵ����Ļ��л��
			{
				break;
			}
			else if (instring[i] == '/' && instring[i + 1] == '*') //���ڶ���ע�ͽ��д�����Ҫֱ��*/��ȫ���𣬿��ǵ���һ���ַ���Ŀո�
			{
				i += 2;
				while (instring[i] != '*')
				{
					if (i == size)
					{
						fileout << outstring;		   //���ַ���outstring���浽fileout;
						getline(filein, instring);     //Ĭ��/**/����ע�Ͳ��������ĩ��
						size = instring.length();
						i = 0;
						continue;
					}
					i++;
				}
				if (instring[i + 1] == '/')
				{
					i++; i++;
					continue;
				}
			}


			j = i;//�˴�j��i��������ע�ͺ��ٴ������ķǿո��ע���ַ���λ��
			if (instring[j] == ';')
			{
				outstring += "_SEMI";   //�зֺžͽ������滻
				break;                  //һ��֮�зֺŽ�β��Ĭ�Ϸֺź�û����䣬��û�п������ַ���䣨�����ƣ�
			}
			else if (instring[j] == '{')
			{
				outstring += "_LSP";    //��������Ž������滻��Ĭ�����Ҵ����ŵ������У������ƣ�
				break;                  //һ��֮���������Ҵ�����Ĭ�ϴ���ֻ��һ������
			}
			else if (instring[j] == '}')
			{
				outstring += "_RSP";    //���Ҵ����Ž������滻��Ĭ�����Ҵ����ŵ������У������ƣ�
				break;                  //һ��֮���������Ҵ�����Ĭ�ϴ���ֻ��һ������
			}
			else if (instring[j] == '(')
			{
				outstring += "_LP";    //�������Ž������滻
				i = j + 1;               //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == ')')
			{
				outstring += "_RP";    //�������Ž������滻
				i = j + 1;               //����һ���ַ���������Ԥ����
				if (i >= size) break;  //�����������Ž�β�����
				continue;
			}
			else if (instring[j] == '[')
			{
				outstring += "_LSB";    //�������Ž������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == ']')
			{
				outstring += "_RSB";    //���ҷ����Ž������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '+')
			{
				outstring += "_PLUS";    //�мӺŽ������滻
				i = j + 1;                //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '-')
			{
				outstring += "_MINUS";    //�м����Ž������滻
				i = j + 1;                  //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '*')
			{
				outstring += "_MULTIPLED";    //�г˺Ž������滻
				i = j + 1;                      //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '/')
			{
				outstring += "_DIVIDED";    //�г��Ž������滻
				i = j + 1;                    //����һ���ַ���������Ԥ����
				continue;
			}
			else if (instring[j] == '=')
			{
				outstring += "_ASSIGN";    //�еȺŽ������滻
				i = j + 1;                 //����һ���ַ���������Ԥ����
				continue;
			}


			while (instring[j] != ' ' && instring[j] != '(' && instring[j] != ')' && instring[j] != ';' && instring[j] != '+' && instring[j] != '-' && instring[j] != '*' && instring[j] != '/' && instring[j] != '=')//���϶����ǣ���ӵ�һ���ǿո�ֱ����һ�������ո��м���ַ��������ǹؼ��ֻ��Ǳ�ʶ��
				j++;
			string temp = instring.substr(i, j - i);
			for (rint k = 0; k < 37; k++)
			{
				if (KeyWord[k] == temp)
				{
					outstring += KeyToken[k];   //�йؼ��ֽ������滻
					flag = true;
					break;
				}
			}
			if (flag == true)  //�ٴδ���ո��������һ�ǿո��ע��   �о���Ҫ����һ������ѭ�����
			{
				flag = false;
				i = j;
				continue;
			}
			else               //���ǹؼ��֣����Ǳ�ʶ��
			{
				outstring += "_ID";   //�б�ʶ���������滻
				i = j;
				continue;
			}

		}
		if (outstring == "")
			fileout << outstring;          //���ַ�����ʲô���������,��ʱoutstringΪ��
		else
			fileout << outstring;          //���ַ���outstring���浽fileout

	}
}

void Getnext(int next[], string t)  //KMP�е�next����
{
	int j = 0, k = -1;
	next[0] = -1;
	while (j < t.length() - 1)
	{
		if (k == -1 || t[j] == t[k])
		{
			j++; k++;
			if (t[j] == t[k])		//�������ַ���ͬʱ��������
				next[j] = next[k];
			else
				next[j] = k;
		}
		else k = next[k];
	}
}

int KMP(string s, string t)
{
	int next[nextSize], i = 0, j = 0;
	Getnext(next, t);
	while (i < s.length() && j < t.length())
	{
		if (j == -1 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else j = next[j];              //j���ˡ�����
	}
	if (j >= t.length())
		return (i - (t.length()));         //ƥ��ɹ��������Ӵ���λ��
	else
		return (-1);                  //û�ҵ�
}

int string_same()
{
	string fileInput_1, fileOutput_1;
	string fileInput_2, fileOutput_2;

	printf("Jarvis>  ��������Ҫ���м����ļ�����������1.cpp��\n");
	cin >> fileInput_1;
	fileOutput_1 = "temp1.cpp";
	pretreat1_1(fileInput_1, fileOutput_1);

	printf("Jarvis>  ��������Ҫ���ڶԱȵ��ļ�����������2.cpp��\n");
	cin >> fileInput_2;
	fileOutput_2 = "temp2.cpp";
	pretreat1_2(fileInput_2, fileOutput_2);

	ifstream filein(fileOutput_2.c_str());//��ȡ�����ļ�
	string instring;
	getline(filein, instring);
	int total = instring.length();
	double ratio;
	double sameThing = 0;

	ifstream fileintemp(fileOutput_1.c_str());//��ȡ�����ļ�
	string temp;
	while (getline(fileintemp, temp))     //��ȡ�ļ�����
	{
		if (KMP(instring, temp) != (-1))
		{
			sameThing += temp.length();
		}
	}
	ratio = sameThing / total;
	printf("Jarvis>  ��һ���ļ��͵ڶ����ļ������ƶ�Ϊ  %lf  \n", ratio);
	if (ratio <= 0.2)
		printf("Jarvis>  ���ʺ�С��Congratulations��\n");
	else if (ratio <= 0.5)
		printf("Jarvis>  �����еȣ�����ע�⣡\n");
	else
		printf("Jarvis>  �벻Ҫ��Ϯ���˴��룡WARNING PLEASE DO NOT COPY\n");

	system("pause");

	return 0;
}




void PreTreat(FILE* inFile, FILE* outFile, char name1[20], char name2[20])
{
	inFile = fopen(name1, "r");
	outFile = fopen(name2, "w");
	char temp[MaxChar];
	char temp2[MaxChar];
	char* flag;
	char* flag1;
	char* flag2;
	while (!feof(inFile))
	{
		while (fgets(temp, MaxChar, inFile))
		{
			if (temp[0] == '#')
			{
				temp[0] = '\n'; temp[1] = '\0';
			}
			else
			{
				flag = strstr(temp, "//");
				if (flag)
				{
					*flag = '\n'; *(flag + 1) = '\0';
				}
				else
				{
					flag1 = strstr(temp, "/*");
					if (flag1)
					{
						*flag1 = '\n'; *(flag1 + 1) = '\0';
						strcpy(temp2, temp);
						flag2 = strstr(flag1 + 2, "*/");
						while (flag2 == NULL)
						{
							fgets(temp, MaxChar, inFile);
							flag2 = strstr(temp, "*/");//ֱ���ҵ�һ���������ұߵķ��ţ������������ѭ����ȡ��һ�м�������
						}
						strcpy(temp, temp2);
					}
				}
			}
			char* back = temp;
			while (isspace(*back))    back++;
			fputs(back, outFile);
		}
	}
	fclose(inFile); fclose(outFile);
}

void showCFG(struct List* list)
{
	struct FuncList* ll;
	while (list->next != NULL)
	{
		list = list->next;
		ll = list->head;
		while (ll->next != NULL)
		{
			ll = ll->next;
			printf("   %s   ", ll->Name);
		}
		printf("\n");
	}
}

struct List* CreateList(FILE* fp)
{
	struct List* LT, * tail;
	struct Function* fun1, * fun2;
	struct FuncList* funhead, * funtail;

	fun1 = CreateFunction(fp);

	LT = (struct List*)malloc(sizeof(struct List));
	tail = LT;
	tail->next = NULL;

	char line[MaxChar];
	while (!(feof(fp)))
	{
		fgets(line, MaxChar, fp);
		if (PanFunc(line))           //�Ǻ����忪ͷ�������Ǻ��������������˺�����
		{
			funhead = (struct FuncList*)malloc(sizeof(FuncList));
			funtail = funhead;
			funtail->next = NULL;

			struct FuncList* funnew = (struct FuncList*)malloc(sizeof(FuncList));

			char* ch;
			ch = strstr(line, " ");
			ch++;
			sscanf(ch, "%[^(]", funnew->Name);
			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			int NumOfZuo = 0;  //ͬһ�������Ӧ�����Ҵ�����һ����һ��������
			NumOfZuo = NumOfChar(line, "{");
			int NumOfFu = 0;
			NumOfFu += NumOfZuo;
			int NumOfYou = 0;

			do {
				fgets(line, MaxChar, fp);
				NumOfZuo = NumOfChar(line, "{");
				NumOfFu += NumOfZuo;
				NumOfYou = NumOfChar(line, "}");
				NumOfFu -= NumOfYou;

				fun2 = fun1->next;
				while (fun2->next != NULL)
				{
					if (strstr(line, fun2->Name))
					{
						funnew = (struct FuncList*)malloc(sizeof(FuncList));
						strcpy(funnew->Name, fun2->Name);
						funtail->next = funnew;
						funtail = funnew;
						funtail->next = NULL;
					}
					fun2 = fun2->next;
				}

			} while (NumOfFu);

			struct List* newlist;
			newlist = (struct List*)malloc(sizeof(struct List));
			newlist->head = funhead;
			tail->next = newlist;
			tail = newlist;
			tail->next = NULL;
		}
	}

	return LT;
}

struct Function* CreateFunction(FILE* fp)  //���ں�����ʹ��Ĭ��ֻ����ȫ�����������ʹ�ã��ҿո���Ҫ�ϸ����
{
	struct Function* head, * tail;
	char line[MaxChar] = { 0 };

	head = (struct Function*)malloc(sizeof(struct Function));
	head->next = NULL;
	tail = head;

	while (!(feof(fp)))
	{
		fgets(line, MaxChar, fp);
		if (PanDuan(line))//�ж�Ϊ�����������ߺ����忪ͷ�������Ƕ��ں�����ʹ�ã��˴������������и�����ͬ�ĺ��������γɵ�����
		{
			struct Function* newNode;
			newNode = (struct Function*)malloc(sizeof(struct Function));
			GetData(line, newNode);

			struct Function* temp;
			int flag = 0;
			temp = head->next;
			while (temp != (tail->next))
			{
				if (temp != NULL)
				{
					if (strcmp(temp->Name, newNode->Name) == 0)//�����ж��Ƿ���������Ѿ�д����
					{
						flag = 1;
						break;
					}
				}
				temp = temp->next;
			}
			if (flag != 1)
			{
				tail->next = newNode;
				tail = newNode;
				tail->next = NULL;
			}
		}
	}
	rewind(fp);
	return head;
}

bool PanDuan(char s[MaxChar])  //�ж�
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
			flag = 1;
	}
	return flag;
}

void GetData(char s[MaxChar], struct Function* f)
{
	sscanf(s, "%[^ ]", f->re_value);//��һ����Ϊ����ֵ
	s = strstr(s, " ");
	s++;                                          //��ʱ�����пո����ҵ���

	sscanf(s, "%[^(]", f->Name);//�ڶ�����Ϊ����
	s = strstr(s, "(");
	s++;							             //��ʱ���������ҵ���

	int temp;
	temp = NumOfChar(s, ",");
	f->parasum = temp + 1;//��������Ϊ����������һ��

	if (temp == 0)//��ʱ����һ������
	{
		sscanf(s, "%[^ ]", f->para1);
	}
	else if (temp == 1)//��ʱ����������
	{
		sscanf(s, "%[^ ]", f->para1);
		s = strstr(s, ",");//���ڶ��ź������Ǹ��пո����Դ˴��ƶ�����
		s++;
		s++;
		sscanf(s, "%[^ ]", f->para2);
	}
	else if (temp == 2)//��ʱ��������������࿼�ǵ������������
	{
		sscanf(s, "%[^ ]", f->para1);
		s = strstr(s, ",");
		s++;
		s++;
		sscanf(s, "%[^ ]", f->para2);
		s = strstr(s, ",");
		s++;
		s++;
		sscanf(s, "%[^ ]", f->para3);
	}


}

int NumOfChar(char s[MaxChar], const char s2[])
{
	unsigned long length = strlen(s2);
	int sum = 0;
	do {
		s = strstr(s, s2);
		if (s != NULL)
		{
			sum++;
			s += length;
		}
		else
			break;
	} while (*s != '\0');
	return sum;
}

bool PanFunc(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

int XiangTong(char s1[20], char s2[20])
{
	struct Function* ttfun2;
	struct Function* ttfun4;
	ttfun2 = tempfun2->next;
	ttfun4 = tempfun4->next;
	char tempfunx[20];
	char tempfuny[20];
	while (strcmp(ttfun2->Name, s1) != 0)
	{
		ttfun2 = ttfun2->next;
	}
	while (strcmp(ttfun4->Name, s2) != 0)
	{
		ttfun4 = ttfun4->next;
	}
	if (!strcmp(ttfun2->re_value, ttfun4->re_value) && (ttfun2->parasum == ttfun4->parasum))
		return 1;
	else
		return 0;
}

int CFG()      //�պ�������Ĭ����һ���ո�,������ָ���Ͳ�����int*���Ϊint
{
	printf("Jarvis>  ��������Ҫ���м����ļ�����������3.c��\n");
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	scanf("%s", infile1);
	printf("Jarvis>  ��������Ҫ���ڶԱȵ��ļ�����������4��\n");
	scanf("%s", infile2);
	fp1 = fopen(infile1, "r");
	fp2 = fopen(outfile1, "w");
	fp3 = fopen(infile2, "r");
	fp4 = fopen(outfile2, "w");
	PreTreat(fp1, fp2, infile1, outfile1);
	PreTreat(fp3, fp4, infile2, outfile2);
	fp2 = fopen(outfile1, "r");
	fp4 = fopen(outfile2, "r");
	rewind(fp2);
	rewind(fp4);


	tempfun2 = CreateFunction(fp2);
	tempfun4 = CreateFunction(fp4);

	rewind(fp2);
	rewind(fp4);

	struct List* L1;
	struct List* L2;
	struct List* templ1;
	struct List* templ2;

	L1 = CreateList(fp2);
	L2 = CreateList(fp4);



	templ1 = L1;
	templ2 = L2;

	printf("\nע��CFGͼ�е�һ����Ϊ�����еĺ��������˳��ÿһ�к��漸��Ϊ��һ���к������ڰ������Ӻ�������˳��\n");
	printf("---------------------------------\n");
	showCFG(templ1);
	printf("---------------------------------\n");
	showCFG(templ2);
	printf("---------------------------------\n");

	struct List* L2head = L2->next;
	int flag1 = 0;
	int flag2 = 0;
	struct FuncList* f1;
	struct FuncList* f2;
	struct FuncList* f2head;
	int FunNum = 0;   //�����������к��������,Ĭ��ȫ���������ո�λ
	int f1Num = 0;    //��һ���������е��Ӻ�������
	int SameNum = 0;  //�����������к�������ͬ�ĸ���
	char L1Name[20] = { 0 };
	char L2Name[20] = { 0 };
	char f1Name[20] = { 0 };
	char f2Name[20] = { 0 };
	double ratio = 0;
	double Allratio[100] = { 0 };
	int k = 0;
	while (L1->next != NULL)
	{
		flag1 = 0;
		L1 = L1->next;
		f1 = L1->head;//�ĳ�f1=L1->head->next;ɾȥ������
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//�ĳ�f2=L2->head->next;ɾȥ������
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //�ӵڶ����������ҵ��͵�һ����������ͬ�ĺ��������
				f2head = f2;
				while (f1->next != NULL)  //�������������Ӻ���������flag2Ϊ1������0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //ÿ��f2��ͷ����f1���бȽ�

					strcpy(f1Name, f1->Name);
					while (f2->next != NULL)
					{
						f2 = f2->next;
						strcpy(f2Name, f2->Name);
						if (strcmp(f1Name, f2Name) == 0)
						{
							SameNum++;
							break;
						}
						else if (XiangTong(f1Name, f2Name))
						{
							SameNum++;
							break;
						}
					}


				}
				if (flag2)
				{
					ratio = SameNum / f1Num;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next == NULL)   //�������������嵫���ڲ���û���Ӻ�������ʱ�޷��϶���Ĭ�ϴ�ʱ������������ͬ
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //�������������嵫�ǵ�һ���ڲ�û���Ӻ������ڶ����У���ʱĬ�����������岻��ͬ
				{
					ratio = 0.0;
					Allratio[k] = ratio;
				}
				k++;
				SameNum = 0;
				f1Num = 0;
				flag2 = 0;
			}
		}
		L2 = L2head;
		if (!flag1)//��û�к͵�һ��������һ���ĵڶ��������壬��ʱ���ڴ˵�һ���������Ӧ�Ŀ�����Ϊ0
		{
			Allratio[k] = 0;
			k++;
		}

	}
	ratio = 0;
	for (int i = 0; i < k; i++)
	{
		ratio += Allratio[i];
	}
	ratio = ratio / k * 100;
	printf("��CFGͼ���бȽϿ�֪�������ƶ�Ϊ��%.5lf \n", ratio);
	system("pause");
	return 0;
}

void CFG_THR1(char s1[MaxChar], char s2[MaxChar])
{
	char outfile1[] = "cfgthr1-1.cpp";
	char outfile2[] = "cfgthr1-2.cpp";
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	fp1 = fopen(s1, "r");
	fp2 = fopen(outfile1, "w");
	fp3 = fopen(s2, "r");
	fp4 = fopen(outfile2, "w");
	PreTreat(fp1, fp2, s1, outfile1);
	PreTreat(fp3, fp4, s2, outfile2);
	fp2 = fopen(outfile1, "r");
	fp4 = fopen(outfile2, "r");
	rewind(fp2);
	rewind(fp4);


	tempfun2 = CreateFunction(fp2);
	tempfun4 = CreateFunction(fp4);

	rewind(fp2);
	rewind(fp4);

	struct List* L1;
	struct List* L2;
	struct List* templ1;
	struct List* templ2;

	L1 = CreateList(fp2);
	L2 = CreateList(fp4);



	templ1 = L1;
	templ2 = L2;

	printf("\nע��CFGͼ�е�һ����Ϊ�����еĺ��������˳��ÿһ�к��漸��Ϊ��һ���к������ڰ������Ӻ�������˳��\n");
	printf("---------------------------------\n");
	showCFG(templ1);
	printf("---------------------------------\n");
	showCFG(templ2);
	printf("---------------------------------\n");

	struct List* L2head = L2->next;
	int flag1 = 0;
	int flag2 = 0;
	struct FuncList* f1;
	struct FuncList* f2;
	struct FuncList* f2head;
	int FunNum = 0;   //�����������к��������,Ĭ��ȫ���������ո�λ
	int f1Num = 0;    //��һ���������е��Ӻ�������
	int SameNum = 0;  //�����������к�������ͬ�ĸ���
	char L1Name[20] = { 0 };
	char L2Name[20] = { 0 };
	char f1Name[20] = { 0 };
	char f2Name[20] = { 0 };
	double ratio = 0;
	double Allratio[100] = { 0 };
	int k = 0;
	while (L1->next != NULL)
	{
		flag1 = 0;
		L1 = L1->next;
		f1 = L1->head;//�ĳ�f1=L1->head->next;ɾȥ������
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//�ĳ�f2=L2->head->next;ɾȥ������
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //�ӵڶ����������ҵ��͵�һ����������ͬ�ĺ��������
				f2head = f2;
				while (f1->next != NULL)  //�������������Ӻ���������flag2Ϊ1������0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //ÿ��f2��ͷ����f1���бȽ�

					strcpy(f1Name, f1->Name);
					while (f2->next != NULL)
					{
						f2 = f2->next;
						strcpy(f2Name, f2->Name);
						if (strcmp(f1Name, f2Name) == 0)
						{
							SameNum++;
							break;
						}
						else if (XiangTong(f1Name, f2Name))
						{
							SameNum++;
							break;
						}
					}


				}
				if (flag2)
				{
					ratio = SameNum / f1Num;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next == NULL)   //�������������嵫���ڲ���û���Ӻ�������ʱ�޷��϶���Ĭ�ϴ�ʱ������������ͬ
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //�������������嵫�ǵ�һ���ڲ�û���Ӻ������ڶ����У���ʱĬ�����������岻��ͬ
				{
					ratio = 0.0;
					Allratio[k] = ratio;
				}
				k++;
				SameNum = 0;
				f1Num = 0;
				flag2 = 0;
			}
		}
		L2 = L2head;
		if (!flag1)//��û�к͵�һ��������һ���ĵڶ��������壬��ʱ���ڴ˵�һ���������Ӧ�Ŀ�����Ϊ0
		{
			Allratio[k] = 0;
			k++;
		}

	}
	ratio = 0;
	for (int i = 0; i < k; i++)
	{
		ratio += Allratio[i];
	}
	ratio = ratio / k * 100;
	printf("��CFGͼ���бȽϿ�֪�������ƶ�Ϊ��%.5lf \n", ratio);
	return;
}
void CFG_THR2(char s1[MaxChar], char s2[MaxChar])
{
	char outfile1[] = "cfgthr2-1.cpp";
	char outfile2[] = "cfgthr2-2.cpp";
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	fp1 = fopen(s1, "r");
	fp2 = fopen(outfile1, "w");
	fp3 = fopen(s2, "r");
	fp4 = fopen(outfile2, "w");
	PreTreat(fp1, fp2, s1, outfile1);
	PreTreat(fp3, fp4, s2, outfile2);
	fp2 = fopen(outfile1, "r");
	fp4 = fopen(outfile2, "r");
	rewind(fp2);
	rewind(fp4);


	tempfun2 = CreateFunction(fp2);
	tempfun4 = CreateFunction(fp4);

	rewind(fp2);
	rewind(fp4);

	struct List* L1;
	struct List* L2;
	struct List* templ1;
	struct List* templ2;

	L1 = CreateList(fp2);
	L2 = CreateList(fp4);



	templ1 = L1;
	templ2 = L2;

	printf("\nע��CFGͼ�е�һ����Ϊ�����еĺ��������˳��ÿһ�к��漸��Ϊ��һ���к������ڰ������Ӻ�������˳��\n");
	printf("---------------------------------\n");
	showCFG(templ1);
	printf("---------------------------------\n");
	showCFG(templ2);
	printf("---------------------------------\n");

	struct List* L2head = L2->next;
	int flag1 = 0;
	int flag2 = 0;
	struct FuncList* f1;
	struct FuncList* f2;
	struct FuncList* f2head;
	int FunNum = 0;   //�����������к��������,Ĭ��ȫ���������ո�λ
	int f1Num = 0;    //��һ���������е��Ӻ�������
	int SameNum = 0;  //�����������к�������ͬ�ĸ���
	char L1Name[20] = { 0 };
	char L2Name[20] = { 0 };
	char f1Name[20] = { 0 };
	char f2Name[20] = { 0 };
	double ratio = 0;
	double Allratio[100] = { 0 };
	int k = 0;
	while (L1->next != NULL)
	{
		flag1 = 0;
		L1 = L1->next;
		f1 = L1->head;//�ĳ�f1=L1->head->next;ɾȥ������
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//�ĳ�f2=L2->head->next;ɾȥ������
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //�ӵڶ����������ҵ��͵�һ����������ͬ�ĺ��������
				f2head = f2;
				while (f1->next != NULL)  //�������������Ӻ���������flag2Ϊ1������0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //ÿ��f2��ͷ����f1���бȽ�

					strcpy(f1Name, f1->Name);
					while (f2->next != NULL)
					{
						f2 = f2->next;
						strcpy(f2Name, f2->Name);
						if (strcmp(f1Name, f2Name) == 0)
						{
							SameNum++;
							break;
						}
						else if (XiangTong(f1Name, f2Name))
						{
							SameNum++;
							break;
						}
					}


				}
				if (flag2)
				{
					ratio = SameNum / f1Num;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next == NULL)   //�������������嵫���ڲ���û���Ӻ�������ʱ�޷��϶���Ĭ�ϴ�ʱ������������ͬ
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //�������������嵫�ǵ�һ���ڲ�û���Ӻ������ڶ����У���ʱĬ�����������岻��ͬ
				{
					ratio = 0.0;
					Allratio[k] = ratio;
				}
				k++;
				SameNum = 0;
				f1Num = 0;
				flag2 = 0;
			}
		}
		L2 = L2head;
		if (!flag1)//��û�к͵�һ��������һ���ĵڶ��������壬��ʱ���ڴ˵�һ���������Ӧ�Ŀ�����Ϊ0
		{
			Allratio[k] = 0;
			k++;
		}

	}
	ratio = 0;
	for (int i = 0; i < k; i++)
	{
		ratio += Allratio[i];
	}
	ratio = ratio / k * 100;
	printf("��CFGͼ���бȽϿ�֪�������ƶ�Ϊ��%.5lf \n", ratio);
	return;
}
void CFG_THR3(char s1[MaxChar], char s2[MaxChar])
{
	char outfile1[] = "cfgthr3-1.cpp";
	char outfile2[] = "cfgthr3-2.cpp";
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	fp1 = fopen(s1, "r");
	fp2 = fopen(outfile1, "w");
	fp3 = fopen(s2, "r");
	fp4 = fopen(outfile2, "w");
	PreTreat(fp1, fp2, s1, outfile1);
	PreTreat(fp3, fp4, s2, outfile2);
	fp2 = fopen(outfile1, "r");
	fp4 = fopen(outfile2, "r");
	rewind(fp2);
	rewind(fp4);


	tempfun2 = CreateFunction(fp2);
	tempfun4 = CreateFunction(fp4);

	rewind(fp2);
	rewind(fp4);

	struct List* L1;
	struct List* L2;
	struct List* templ1;
	struct List* templ2;

	L1 = CreateList(fp2);
	L2 = CreateList(fp4);



	templ1 = L1;
	templ2 = L2;

	printf("\nע��CFGͼ�е�һ����Ϊ�����еĺ��������˳��ÿһ�к��漸��Ϊ��һ���к������ڰ������Ӻ�������˳��\n");
	printf("---------------------------------\n");
	showCFG(templ1);
	printf("---------------------------------\n");
	showCFG(templ2);
	printf("---------------------------------\n");

	struct List* L2head = L2->next;
	int flag1 = 0;
	int flag2 = 0;
	struct FuncList* f1;
	struct FuncList* f2;
	struct FuncList* f2head;
	int FunNum = 0;   //�����������к��������,Ĭ��ȫ���������ո�λ
	int f1Num = 0;    //��һ���������е��Ӻ�������
	int SameNum = 0;  //�����������к�������ͬ�ĸ���
	char L1Name[20] = { 0 };
	char L2Name[20] = { 0 };
	char f1Name[20] = { 0 };
	char f2Name[20] = { 0 };
	double ratio = 0;
	double Allratio[100] = { 0 };
	int k = 0;
	while (L1->next != NULL)
	{
		flag1 = 0;
		L1 = L1->next;
		f1 = L1->head;//�ĳ�f1=L1->head->next;ɾȥ������
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//�ĳ�f2=L2->head->next;ɾȥ������
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //�ӵڶ����������ҵ��͵�һ����������ͬ�ĺ��������
				f2head = f2;
				while (f1->next != NULL)  //�������������Ӻ���������flag2Ϊ1������0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //ÿ��f2��ͷ����f1���бȽ�

					strcpy(f1Name, f1->Name);
					while (f2->next != NULL)
					{
						f2 = f2->next;
						strcpy(f2Name, f2->Name);
						if (strcmp(f1Name, f2Name) == 0)
						{
							SameNum++;
							break;
						}
						else if (XiangTong(f1Name, f2Name))
						{
							SameNum++;
							break;
						}
					}


				}
				if (flag2)
				{
					ratio = SameNum / f1Num;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next == NULL)   //�������������嵫���ڲ���û���Ӻ�������ʱ�޷��϶���Ĭ�ϴ�ʱ������������ͬ
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //�������������嵫�ǵ�һ���ڲ�û���Ӻ������ڶ����У���ʱĬ�����������岻��ͬ
				{
					ratio = 0.0;
					Allratio[k] = ratio;
				}
				k++;
				SameNum = 0;
				f1Num = 0;
				flag2 = 0;
			}
		}
		L2 = L2head;
		if (!flag1)//��û�к͵�һ��������һ���ĵڶ��������壬��ʱ���ڴ˵�һ���������Ӧ�Ŀ�����Ϊ0
		{
			Allratio[k] = 0;
			k++;
		}

	}
	ratio = 0;
	for (int i = 0; i < k; i++)
	{
		ratio += Allratio[i];
	}
	ratio = ratio / k * 100;
	printf("��CFGͼ���бȽϿ�֪�������ƶ�Ϊ��%.5lf \n", ratio);
	return;
}
void CFG_THR4(char s1[MaxChar], char s2[MaxChar])
{
	char outfile1[] = "cfgthr4-1.cpp";
	char outfile2[] = "cfgthr4-2.cpp";
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	fp1 = fopen(s1, "r");
	fp2 = fopen(outfile1, "w");
	fp3 = fopen(s2, "r");
	fp4 = fopen(outfile2, "w");
	PreTreat(fp1, fp2, s1, outfile1);
	PreTreat(fp3, fp4, s2, outfile2);
	fp2 = fopen(outfile1, "r");
	fp4 = fopen(outfile2, "r");
	rewind(fp2);
	rewind(fp4);


	tempfun2 = CreateFunction(fp2);
	tempfun4 = CreateFunction(fp4);

	rewind(fp2);
	rewind(fp4);

	struct List* L1;
	struct List* L2;
	struct List* templ1;
	struct List* templ2;

	L1 = CreateList(fp2);
	L2 = CreateList(fp4);



	templ1 = L1;
	templ2 = L2;

	printf("\nע��CFGͼ�е�һ����Ϊ�����еĺ��������˳��ÿһ�к��漸��Ϊ��һ���к������ڰ������Ӻ�������˳��\n");
	printf("---------------------------------\n");
	showCFG(templ1);
	printf("---------------------------------\n");
	showCFG(templ2);
	printf("---------------------------------\n");

	struct List* L2head = L2->next;
	int flag1 = 0;
	int flag2 = 0;
	struct FuncList* f1;
	struct FuncList* f2;
	struct FuncList* f2head;
	int FunNum = 0;   //�����������к��������,Ĭ��ȫ���������ո�λ
	int f1Num = 0;    //��һ���������е��Ӻ�������
	int SameNum = 0;  //�����������к�������ͬ�ĸ���
	char L1Name[20] = { 0 };
	char L2Name[20] = { 0 };
	char f1Name[20] = { 0 };
	char f2Name[20] = { 0 };
	double ratio = 0;
	double Allratio[100] = { 0 };
	int k = 0;
	while (L1->next != NULL)
	{
		flag1 = 0;
		L1 = L1->next;
		f1 = L1->head;//�ĳ�f1=L1->head->next;ɾȥ������
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//�ĳ�f2=L2->head->next;ɾȥ������
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //�ӵڶ����������ҵ��͵�һ����������ͬ�ĺ��������
				f2head = f2;
				while (f1->next != NULL)  //�������������Ӻ���������flag2Ϊ1������0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //ÿ��f2��ͷ����f1���бȽ�

					strcpy(f1Name, f1->Name);
					while (f2->next != NULL)
					{
						f2 = f2->next;
						strcpy(f2Name, f2->Name);
						if (strcmp(f1Name, f2Name) == 0)
						{
							SameNum++;
							break;
						}
						else if (XiangTong(f1Name, f2Name))
						{
							SameNum++;
							break;
						}
					}


				}
				if (flag2)
				{
					ratio = SameNum / f1Num;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next == NULL)   //�������������嵫���ڲ���û���Ӻ�������ʱ�޷��϶���Ĭ�ϴ�ʱ������������ͬ
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //�������������嵫�ǵ�һ���ڲ�û���Ӻ������ڶ����У���ʱĬ�����������岻��ͬ
				{
					ratio = 0.0;
					Allratio[k] = ratio;
				}
				k++;
				SameNum = 0;
				f1Num = 0;
				flag2 = 0;
			}
		}
		L2 = L2head;
		if (!flag1)//��û�к͵�һ��������һ���ĵڶ��������壬��ʱ���ڴ˵�һ���������Ӧ�Ŀ�����Ϊ0
		{
			Allratio[k] = 0;
			k++;
		}

	}
	ratio = 0;
	for (int i = 0; i < k; i++)
	{
		ratio += Allratio[i];
	}
	ratio = ratio / k * 100;
	printf("��CFGͼ���бȽϿ�֪�������ƶ�Ϊ��%.5lf \n", ratio);
	return;
}




int SOF()
{
	int n = 0;
	int flag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "SOF.cpp";//Ԥ���������SOF.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;
	FILE* fp1, * fp2;

	struct Var* v;
	struct MiGan* m;
	struct FunctionSOF* f;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionSOF*)malloc(sizeof(struct FunctionSOF));

	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncR4(fp2);

	rewind(fp2);

	f = f->next;
	m = f->mlist->next;
	while (f != NULL)
	{
		while (m != NULL)
		{
			flag = 0;

			strcpy(MuDi, m->Mudi);
			strcpy(Yuan, m->yuan);
			int lenMuDi;
			int lenYuan;
			n = m->n;

			v = f->vlist->next;
			int flag1 = 0;
			int flag2 = 0;

			while (v != NULL)
			{
				if (strcmp(MuDi, v->Name) == 0)
				{
					MudiSize = v->size;
					lenMuDi = v->realSize;
					flag1 = 1;
				}
				if (strcmp(Yuan, v->Name) == 0)
				{
					YuanSize = v->size;
					lenYuan = v->realSize;
					flag2 = 1;
				}
				if (flag1 && flag2)
					flag = 1;
				v = v->next;
			}

			if (flag == 1)
			{
				if (!strcmp(m->Name, "strcpy") || !strcmp(m->Name, "sscanf"))
				{
					if (MudiSize < lenYuan)
						OF = 1;
					else
						OF = 2;
				}
				else if (!strcmp(m->Name, "strncpy") || !strcmp(m->Name, "memcpy"))
				{
					if (MudiSize < n)
						OF = 1;
					else
						OF = 2;
				}
				else if (!strcmp(m->Name, "strcat"))
				{
					if (MudiSize < (lenYuan + lenMuDi))
						OF = 1;
					else
						OF = 2;
				}
				else if (!strcmp(m->Name, "strncat"))
				{
					if (MudiSize < (n + lenMuDi))
						OF = 1;
					else
						OF = 2;
				}
				if (OF == 1)
				{
					printf("Jarvis>  ջ��������ڵ�%d��\n", m->row);
					Show(fp2, m->row);
					system("pause");
				}
				else if (OF == 2)
				{
					printf("Jarvis>  ��%d�д������к�����δ����ջ���\n", m->row);
					system("pause");
				}
			}
			else if (flag == 0)
			{
				printf("Jarvis>  ��δ�������к���\n");
				system("pause");
			}

			m = m->next;
		}
		f = f->next;
		if (f == NULL)
			break;
		m = f->mlist->next;

	}
	return 0;
}

struct FunctionSOF* CreateFuncR4(FILE* fp)
{   //�������γ�����
	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionSOF* funhead, * funtail, * funnew;


	funhead = (struct FunctionSOF*)malloc(sizeof(struct FunctionSOF));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncR4(line1))//�Ǻ����壬�����˺�����
		{
			funnew = (struct FunctionSOF*)malloc(sizeof(struct FunctionSOF));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;

			funnew->mlist = mtail;
			funnew->vlist = vtail;

			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (strstr(line2, "print") == NULL && (strstr(line2, "int") != NULL || strstr(line2, "long") != NULL || strstr(line2, "short") != NULL || strstr(line2, "float") != NULL || strstr(line2, "double") != NULL || strstr(line2, "char") != NULL))
				{
					vnew = (struct Var*)malloc(sizeof(struct Var));

					V_analysisR4(line2, vnew);
					vnew->row = row;

					vtail->next = vnew;
					vtail = vnew;
					vtail->next = NULL;
				}

				if (PanMinR4(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					M_analysisR4(line2, mnew);

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}
			} while (NumOfFu);

			funnew->end = row;
		}
	}
	return funhead;
}

bool PanFuncR4(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

void V_analysisR4(char s[MaxChar], struct Var* var)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };

	if (strstr(s, "[") != NULL) //���ҵ������ţ�˵��������������
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", var->type);

		s = strstr(s, " ");
		s++;

		sscanf(s, "%[^[]", var->Name);
		s = strstr(s, "[");
		s++;

		if (*s != ']') //�������к��о�����ֵ��ʾ�����Сʱ
		{
			sscanf(s, "%[^]]", temp1);
			var->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//Ҳ�����˳�ʼ��
			{
				sscanf(s, "%[^;]", temp2);
				var->realSize = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			}
		}
		else //�������в����о�����ֵ��ʾ�����Сʱ����������ֱ����ʾ��������ʱ�����˳�ʼ�������������ʱĬ�Ͻ����ַ���������г�ʼ��                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			var->size = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			var->realSize = var->size;
		}
	}
	else //��������
	{
		if (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			sscanf(s, "%[^ ]", var->type);

			if (strcmp(var->type, "char") == 0)
				var->size = 1;
			if (strcmp(var->type, "short") == 0)
				var->size = 2;
			if (strcmp(var->type, "int") == 0)
				var->size = 4;
			if (strcmp(var->type, "float") == 0)
				var->size = 4;
			if (strcmp(var->type, "long") == 0)
				var->size = 4;
			if (strcmp(var->type, "double") == 0)
				var->size = 8;

			if (strstr(s, "=") == NULL) //û�еȺţ���û�н��г�ʼ���������
			{
				s = strstr(s, " ");
				s++;
				sscanf(s, "%[^;]", var->Name);
			}
			else //�еȺ�
			{
				s = strstr(s, " ");
				s++;
				sscanf(s, "%[^=]", var->Name);
			}
		}
	}
}

bool PanMinR4(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
		flag = true;
	return flag;
}

void M_analysisR4(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		if (!strcmp(mig->Name, "strcpy") || !strcmp(mig->Name, "strcat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");              //����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո�
			s++;
			s++;
			sscanf(s, "%[^)]", mig->yuan);
		}
		else if (!strcmp(mig->Name, "strncpy") || !strcmp(mig->Name, "memcpy") || !strcmp(mig->Name, "strncat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp);
			mig->n = atoi(temp);
		}
		else if (!strcmp(mig->Name, "sscanf"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");//�����м�������ʽ�����
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", mig->Mudi);
		}


	}
}

void Show(FILE* fp, int row)
{
	int i = 0;
	char line1[MaxChar];
	while (i != row)
	{
		fgets(line1, MaxChar, fp);
		i++;
	}
	printf("Jarvis>  ԭ���룺 %s  \n", line1);
	rewind(fp);
}



int HOF()
{
	int n = 0;
	int flag = 0;
	int bjflag = 0;
	int migflag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "HOF.cpp";//Ԥ���������HOF.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;
	FILE* fp1, * fp2;

	struct Var* v;
	struct MiGan* m;
	struct FunctionHOF* f;
	struct HuanChong* h;
	struct BianJie* bj;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionHOF*)malloc(sizeof(struct FunctionHOF));
	h = (struct HuanChong*)malloc(sizeof(struct HuanChong));
	bj = (struct BianJie*)malloc(sizeof(struct BianJie));
	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncB1(fp2);

	rewind(fp2);

	f = f->next;
	m = f->mlist->next;
	while (f != NULL)
	{
		while (m != NULL)
		{
			migflag = 1;

			strcpy(MuDi, m->Mudi);
			strcpy(Yuan, m->yuan);
			int lenMuDi = 0;
			int lenYuan = 0;
			n = m->n;

			h = f->hlist->next;
			bj = f->bjlist->next;

			while (h != NULL)
			{
				if (!strcmp(MuDi, h->Name))
				{
					MudiSize = h->size;
					lenMuDi = h->realSize;
				}
				if (!strcmp(Yuan, h->Name))
				{
					YuanSize = h->size;
					lenYuan = h->realSize;
				}

				h = h->next;
			}


			if (!strcmp(m->Name, "strcpy") || !strcmp(m->Name, "sscanf"))
			{
				if (MudiSize < YuanSize)
					migflag = 1;
				else
					migflag = 2;
			}
			else if (!strcmp(m->Name, "strncpy") || !strcmp(m->Name, "memcpy"))
			{
				if (MudiSize < n)
					migflag = 1;
				else
					migflag = 2;
			}
			else if (!strcmp(m->Name, "strcat"))
			{
				if (MudiSize < (lenMuDi + lenYuan))
					migflag = 1;
				else
					migflag = 2;
			}
			else if (!strcmp(m->Name, "strncat"))
			{
				if (MudiSize < (n + lenMuDi))
					migflag = 1;
				else
					migflag = 2;
			}

			while (bj != NULL)
			{
				bjflag = 1;
				v = f->vlist->next;
				while (v != NULL)
				{
					if (strstr(bj->num, v->Name))
					{
						bjflag = 2;
						break;
					}
					v = v->next;
				}
				bj = bj->next;
			}

			if (migflag == 1 && bjflag == 0)
				OF = 1;
			if (migflag == 1 && bjflag == 2)
				OF = 2;
			if ((migflag == 0) || (migflag == 2 && bjflag == 0))
				OF = 3;
			if (OF == 1)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  ����������ڵ�%d��\n", m->row);
				Show(fp2, m->row);
			}
			else if (OF == 2)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  ��������ܷ����ڵ�%d��\n", m->row);
				Show(fp2, m->row);
			}
			else if (OF == 3)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  ��%d�д������к�����δ���������\n", m->row);
			}

			m = m->next;
		}
		f = f->next;
		if (f == NULL)
			break;
		m = f->mlist->next;

	}
	system("pause");
	return 0;
}

struct FunctionHOF* CreateFuncB1(FILE* fp)
{   //�������γ�����
	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionHOF* funhead, * funtail, * funnew;
	struct HuanChong* hhead, * htail, * hnew;
	struct BianJie* bjhead, * bjtail, * bjnew;


	funhead = (struct FunctionHOF*)malloc(sizeof(struct FunctionHOF));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncB1(line1))//�Ǻ����壬�����˺�����
		{
			funnew = (struct FunctionHOF*)malloc(sizeof(struct FunctionHOF));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;
			hhead = (struct HuanChong*)malloc(sizeof(struct HuanChong));
			htail = hhead;
			htail->next = NULL;
			bjhead = (struct BianJie*)malloc(sizeof(struct BianJie));
			bjtail = bjhead;
			bjtail->next = NULL;


			funnew->mlist = mtail;
			funnew->vlist = vtail;
			funnew->hlist = htail;
			funnew->bjlist = bjtail;


			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (strstr(line2, "print") == NULL && (strstr(line2, "int") != NULL || strstr(line2, "long") != NULL || strstr(line2, "short") != NULL || strstr(line2, "float") != NULL || strstr(line2, "double") != NULL || strstr(line2, "char") != NULL))
				{//printf�е�int�ַ����������
					if (strstr(line2, "*") != NULL || strstr(line2, "[") != NULL)
					{
						hnew = (struct HuanChong*)malloc(sizeof(struct HuanChong));

						H_analysisB1(line2, hnew);

						htail->next = hnew;
						htail = hnew;
						htail->next = NULL;
					}
					else
					{
						vnew = (struct Var*)malloc(sizeof(struct Var));

						V_analysisB1(line2, vnew);
						vnew->row = row;

						vtail->next = vnew;
						vtail = vnew;
						vtail->next = NULL;
					}
				}

				if (PanMinB1(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					M_analysisB1(line2, mnew);

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

				if (strstr(line2, "if") != NULL)
				{
					bjnew = (struct BianJie*)malloc(sizeof(struct BianJie));

					BJ_analysisB1(line2, bjnew);

					bjnew->row = row;
					bjtail->next = bjnew;
					bjtail = bjnew;
					bjtail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
		}
	}
	return funhead;
}

bool PanFuncB1(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

void V_analysisB1(char s[MaxChar], struct Var* var)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };


	//��������
	if (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
	{
		sscanf(s, "%[^ ]", var->type);

		if (strcmp(var->type, "char") == 0)
			var->size = 1;
		if (strcmp(var->type, "short") == 0)
			var->size = 2;
		if (strcmp(var->type, "int") == 0)
			var->size = 4;
		if (strcmp(var->type, "float") == 0)
			var->size = 4;
		if (strcmp(var->type, "long") == 0)
			var->size = 4;
		if (strcmp(var->type, "double") == 0)
			var->size = 8;

		if (strstr(s, "=") == NULL) //û�еȺţ���û�н��г�ʼ���������
		{
			s = strstr(s, " ");
			s++;
			sscanf(s, "%[^;]", var->Name);
		}
		else //�еȺ�
		{
			s = strstr(s, " ");
			s++;
			sscanf(s, "%[^=]", var->Name);
		}
	}

}

bool PanMinB1(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
		flag = true;
	return flag;
}

void M_analysisB1(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		if (!strcmp(mig->Name, "strcpy") || !strcmp(mig->Name, "strcat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");              //����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո����Դ
			s++;
			s++;
			sscanf(s, "%[^)]", mig->yuan);
		}
		else if (!strcmp(mig->Name, "strncpy") || !strcmp(mig->Name, "memcpy") || !strcmp(mig->Name, "strncat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp);
			mig->n = atoi(temp);
		}
		else if (!strcmp(mig->Name, "sscanf"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");//�����м�������ʽ�����
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", mig->Mudi);
		}


	}
}

void H_analysisB1(char s[MaxChar], struct HuanChong* h)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };

	if (strstr(s, "[") != NULL)//���ҵ������ţ�˵��������������
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //�������к��о�����ֵ��ʾ�����Сʱ
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//Ҳ�����˳�ʼ��
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			}
		}
		else //�������в����о�����ֵ��ʾ�����Сʱ����������ֱ����ʾ��������ʱ�����˳�ʼ�������������ʱĬ�Ͻ����ַ���������г�ʼ��                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			h->realSize = h->size;
		}
	}
	if (strstr(s, "char*") != NULL || strstr(s, "short*") != NULL || strstr(s, "int*") || strstr(s, "long*") != NULL)
	{
		if (strstr(s, "HeapAlloc") == NULL)
		{
			sscanf(s, "%[^*]", h->type);
			s = strstr(s, "* ");//Ĭ��*�ź���һ���ո�
			s++;
			s++;
			sscanf(s, "%[^=]", h->Name);
		}
		else
		{
			sscanf(s, "%[^=]", h->Name);
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^)]", h->type);
			s = strstr(s, ",");//����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո�
			s++;
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp1);
			h->size = atoi(temp1);
		}
	}
}

void BJ_analysisB1(char s[MaxChar], struct BianJie* bj)
{
	if (strstr(s, "if"))
	{
		sscanf(s, "%[^(]", bj->type);
		s = strstr(s, "(");
		s++;
		sscanf(s, "%[^)]", bj->num);
	}
}




int INTwidth()
{
	int n = 0;
	int flag = 0;
	int bjflag = 0;
	int migflag = 0;
	int xtflag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "INTwidthOF.cpp";//Ԥ���������INTwidthOF.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;
	FILE* fp1, * fp2;

	int lkind = 0, rkind = 0;
	char xtleft[20] = { 0 };
	char xtright[20] = { 0 };

	struct Var* v;
	struct MiGan* m;
	struct FunctionB2* f;
	struct HuanChong* h;
	struct BianJie* bj;
	struct XiangTongB2* XT;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionB2*)malloc(sizeof(struct FunctionB2));
	h = (struct HuanChong*)malloc(sizeof(struct HuanChong));
	bj = (struct BianJie*)malloc(sizeof(struct BianJie));
	XT = (struct XiangTongB2*)malloc(sizeof(struct XiangTongB2));

	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncB2(fp2);

	rewind(fp2);

	f = f->next;
	

	while (f != NULL)
	{
		m = f->mlist->next;
		v = f->vlist->next;
		h = f->hlist->next;
		bj = f->bjlist->next;
		XT = f->xtlist->next;
		while (XT != NULL) //��ֵ������
		{
			xtflag = 1;

			strcpy(xtleft, XT->left);
			strcpy(xtright, XT->right);

			while (v != NULL)
			{
				if (!strcmp(xtleft, v->Name))
					lkind = v->kind;
				if (!strcmp(xtright, v->Name))
					rkind = v->kind;

				v = v->next;
			}
			if (lkind < rkind)//���ڵ��¿����������
			{
				xtflag = 2;
				break;
			}

			if (xtflag != 2)
				XT = XT->next;
		}

		while (bj != NULL)
		{
			bjflag = 1;
			v = f->vlist->next;
			while (v != NULL)
			{
				if (strstr(bj->num, v->Name))//���ڶ���߽���
				{
					bjflag = 2;
					break;
				}
				v = v->next;
			}
			bj = bj->next;
		}

		while (m != NULL)
		{
			migflag = 1;

			strcpy(MuDi, m->Mudi);

			while (h != NULL)
			{
				if (!strcmp(h->Name, MuDi))//���к���Ŀ������ͻ�������ͬ
				{
					migflag = 2;
					break;
				}

				h = h->next;
			}

			if (migflag != 2)
				m = m->next;
			else
				break;
		}


		if (xtflag == 2 && migflag == 2 && bjflag != 2)//��ֵ������С���ұߣ����к�����Ŀ��������֮��ͬ�����
			OF = 1;
		if (xtflag == 2 && migflag == 2 && bjflag == 2)//�������
			OF = 2;
		if ((xtflag == 2 && migflag != 2) || (xtflag == 0 && bjflag == 2))//�޸�ֵ���������к������б߽��飬�����
			OF = 3;
		if (OF == 1)
		{
			if (XT == NULL || m == NULL)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  δ��������������\n");
			}
			else
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  �ɵ�%d����������������������ڵ�%d��\n", XT->row, m->row);
				Show(fp2, XT->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 2)
		{
			if (XT == NULL || m == NULL)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  δ��������������\n");
			}
			else
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  �ɵ�%d��������������������ܷ����ڵ�%d��\n", XT->row, m->row);
				Show(fp2, XT->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
			printf("Jarvis>  δ��������������\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB2* CreateFuncB2(FILE* fp)
{   //�������γ�����
	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionB2* funhead, * funtail, * funnew;
	struct HuanChong* hhead, * htail, * hnew;
	struct BianJie* bjhead, * bjtail, * bjnew;
	struct XiangTongB2* xthead, * xttail, * xtnew;


	funhead = (struct FunctionB2*)malloc(sizeof(struct FunctionB2));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncB2(line1))//�Ǻ����壬�����˺�����
		{
			funnew = (struct FunctionB2*)malloc(sizeof(struct FunctionB2));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;
			hhead = (struct HuanChong*)malloc(sizeof(struct HuanChong));
			htail = hhead;
			htail->next = NULL;
			bjhead = (struct BianJie*)malloc(sizeof(struct BianJie));
			bjtail = bjhead;
			bjtail->next = NULL;
			xthead = (struct XiangTongB2*)malloc(sizeof(struct XiangTongB2));
			xttail = xthead;
			xttail->next = NULL;

			funnew->mlist = mtail;
			funnew->vlist = vtail;
			funnew->hlist = htail;
			funnew->bjlist = bjtail;
			funnew->xtlist = xttail;

			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (strstr(line2, "print") == NULL && (strstr(line2, "int") != NULL || strstr(line2, "long") != NULL || strstr(line2, "short") != NULL || strstr(line2, "float") != NULL || strstr(line2, "double") != NULL || strstr(line2, "char") != NULL))
				{//printf�е�int�ַ����������
					if (strstr(line2, "*") != NULL || strstr(line2, "[") != NULL)
					{
						hnew = (struct HuanChong*)malloc(sizeof(struct HuanChong));

						H_analysisB2(line2, hnew);

						htail->next = hnew;
						htail = hnew;
						htail->next = NULL;
					}
					else
					{
						vnew = (struct Var*)malloc(sizeof(struct Var));

						V_analysisB2(line2, vnew);
						vnew->row = row;

						vtail->next = vnew;
						vtail = vnew;
						vtail->next = NULL;
					}
				}

				if (PanMinB2(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					M_analysisB2(line2, mnew);

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

				if (strstr(line2, "if") != NULL)
				{
					bjnew = (struct BianJie*)malloc(sizeof(struct BianJie));

					BJ_analysisB2(line2, bjnew);

					bjnew->row = row;

					bjtail->next = bjnew;
					bjtail = bjnew;
					bjtail->next = NULL;
				}

				if (PanTongB2(line2))
				{
					xtnew = (struct XiangTongB2*)malloc(sizeof(struct XiangTongB2));
					xtnew->row = row;

					XT_analysis(line2, xtnew);

					xttail->next = xtnew;
					xttail = xtnew;
					xttail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
		}
	}
	return funhead;
}

bool PanFuncB2(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

void V_analysisB2(char s[MaxChar], struct Var* var)
{
	char temp[10] = { 0 };
	if (strstr(s, "short ") != NULL || strstr(s, "int ") != NULL || strstr(s, "long ") != NULL)
	{
		if (strstr(s, "unsigned ") != NULL)  //ǰ���Ƿ���unsigned
		{
			sscanf(s, "%[^ ]", var->type);
			strcat(var->type, " ");//�ȸ�unsigned
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^ ]", temp);
			strcat(var->type, temp);//�ٸ����������
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}
		else
		{
			sscanf(s, "%[^ ]", var->type);//ֱ�Ӹ�����
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}


		if (strstr(var->type, "short") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 1;  //short Ϊ1������
			}
			else
			{
				var->kind = 2;  //unsigned short Ϊ2������
			}
		}
		if (strstr(var->type, "int") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 3;  //int Ϊ3������
			}
			else
			{
				var->kind = 4;  //unsigned int Ϊ4������
			}
		}
		if (strstr(var->type, "long") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 5;  //long Ϊ5������
			}
			else
			{
				var->kind = 6;  //unsigned long Ϊ6������
			}
		}
	}
}

bool PanMinB2(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
		flag = true;
	return flag;
}

void M_analysisB2(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		if (!strcmp(mig->Name, "strcpy") || !strcmp(mig->Name, "strcat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");              //����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո����Դ
			s++;
			s++;
			sscanf(s, "%[^)]", mig->yuan);
		}
		else if (!strcmp(mig->Name, "strncpy") || !strcmp(mig->Name, "memcpy") || !strcmp(mig->Name, "strncat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp);
			mig->n = atoi(temp);
		}
		else if (!strcmp(mig->Name, "sscanf"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");//�����м�������ʽ�����
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", mig->Mudi);
		}


	}
}

void H_analysisB2(char s[MaxChar], struct HuanChong* h)
{
	char temp1[MaxChar] = { 0 };
	char temp2[100] = { 0 };

	if (strstr(s, "[") != NULL)//���ҵ������ţ�˵��������������
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //�������к��о�����ֵ��ʾ�����Сʱ
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//Ҳ�����˳�ʼ��
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			}
		}
		else //�������в����о�����ֵ��ʾ�����Сʱ����������ֱ����ʾ��������ʱ�����˳�ʼ�������������ʱĬ�Ͻ����ַ���������г�ʼ��                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			h->realSize = h->size;
		}
	}
}

void BJ_analysisB2(char s[MaxChar], struct BianJie* bj)
{
	if (strstr(s, "if"))
	{
		sscanf(s, "%[^(]", bj->type);
		s = strstr(s, "(");
		s++;
		sscanf(s, "%[^)]", bj->num);
	}
}

bool PanTongB2(char s[MaxChar])
{
	char* temp1;
	char temp2[100] = { 0 };

	bool flag = 1;
	temp1 = s;

	if (strstr(s, "=") != NULL)//���ڵȺ�ʱ
	{
		temp1 = strstr(temp1, "=");
		temp1++;
		temp1++;//�Զ���ӵĿո�

		sscanf(temp1, "%[^;]", temp2);

		for (int i = 0; i < strlen(temp2); i++)
		{
			if (!(temp2[i] >= '0' && temp2[i] <= '9'))
				continue;
			else  //�Ⱥ��ұߴ���0-9ʱ������Ϊ��ĸ��ֵʱ
			{
				flag = 0;
				break;
			}
		}
	}
	else
		flag = 0;

	return flag;
}

struct XiangTongB2* XT_analysis(char s[MaxChar], struct XiangTongB2* XT)
{
	sscanf(s, "%[^ =]", XT->left);
	s = strstr(s, "=");
	s++;
	s++;
	sscanf(s, "%[^;]", XT->right);
	return XT;
}




int INTcalc()
{
	int n = 0;
	int flag = 0;
	int bjflag = 0;
	int migflag = 0;
	int cflag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "INTcalcuOF.cpp";//Ԥ���������INTcalcuOF.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;
	int MudiFlag;
	FILE* fp1, * fp2;

	struct Var* v;
	struct MiGan* m;
	struct FunctionB3* f;
	struct HuanChong* h;
	struct Calcu* c;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionB3*)malloc(sizeof(struct FunctionB3));
	h = (struct HuanChong*)malloc(sizeof(struct HuanChong));
	c = (struct Calcu*)malloc(sizeof(struct Calcu));

	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncB3(fp2);

	rewind(fp2);

	f = f->next;
	

	while (f != NULL)
	{
		m = f->mlist->next;
		v = f->vlist->next;
		h = f->hlist->next;
		c = f->clist->next;
		while (c != NULL)
		{
			cflag = 1;

			strcpy(MuDi, c->mudi);
			while (v != NULL)
			{
				if (!strcmp(MuDi, v->Name))
				{
					MudiFlag = v->kind;
					break;
				}
				v = v->next;
			}
			if (MudiFlag < 5)
			{
				cflag = 2;
				break;
			}

			if (cflag != 2)
				c = c->next;
		}

		while (m != NULL)
		{
			migflag = 1;

			strcpy(MuDi, m->Mudi);

			while (h != NULL)
			{
				if (!strcmp(h->Name, MuDi))//���к���Ŀ������ͻ�������ͬ
				{
					migflag = 2;
					break;
				}

				h = h->next;
			}

			if (migflag != 2)
				m = m->next;
			else
				break;
		}

		if (cflag == 2 && migflag == 2)//Ŀ�������Ϊlong��ʱ�������к�����Ŀ��������֮��ͬ
			OF = 2;
		else
			OF = 3;

		if (OF == 2)
		{
			if (c == NULL || m == NULL)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  δ���������������\n");
			}
			else
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  �ɵ�%d���������������������ܷ����ڵ�%d��\n", c->row, m->row);
				Show(fp2, c->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
			printf("Jarvis>  δ���������������\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB3* CreateFuncB3(FILE* fp)
{   //�������γ�����
	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionB3* funhead, * funtail, * funnew;
	struct HuanChong* hhead, * htail, * hnew;
	struct Calcu* chead, * ctail, * cnew;


	funhead = (struct FunctionB3*)malloc(sizeof(struct FunctionB3));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncB3(line1))//�Ǻ����壬�����˺�����
		{
			funnew = (struct FunctionB3*)malloc(sizeof(struct FunctionB3));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;
			hhead = (struct HuanChong*)malloc(sizeof(struct HuanChong));
			htail = hhead;
			htail->next = NULL;
			chead = (struct Calcu*)malloc(sizeof(struct Calcu));
			ctail = chead;
			ctail->next = NULL;

			funnew->mlist = mtail;
			funnew->vlist = vtail;
			funnew->hlist = htail;
			funnew->clist = ctail;

			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (strstr(line2, "print") == NULL && (strstr(line2, "int") != NULL || strstr(line2, "long") != NULL || strstr(line2, "short") != NULL || strstr(line2, "float") != NULL || strstr(line2, "double") != NULL || strstr(line2, "char") != NULL))
				{//printf�е�int�ַ����������
					if (strstr(line2, "*") != NULL || strstr(line2, "[") != NULL)
					{
						hnew = (struct HuanChong*)malloc(sizeof(struct HuanChong));

						H_analysisB3(line2, hnew);

						htail->next = hnew;
						htail = hnew;
						htail->next = NULL;
					}
					else
					{
						vnew = (struct Var*)malloc(sizeof(struct Var));

						V_analysisB3(line2, vnew);
						vnew->row = row;

						vtail->next = vnew;
						vtail = vnew;
						vtail->next = NULL;
					}
				}

				if (PanMinB3(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					M_analysisB3(line2, mnew);

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

				if (PanCalB3(line2))
				{
					cnew = (struct Calcu*)malloc(sizeof(struct Calcu));
					cnew->row = row;

					C_analysisB3(line2, cnew);

					ctail->next = cnew;
					ctail = cnew;
					ctail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
		}
	}
	return funhead;
}

bool PanFuncB3(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

void V_analysisB3(char s[MaxChar], struct Var* var)
{
	char temp[10] = { 0 };
	if (strstr(s, "short ") != NULL || strstr(s, "int ") != NULL || strstr(s, "long ") != NULL)
	{
		if (strstr(s, "unsigned ") != NULL)  //ǰ���Ƿ���unsigned
		{
			sscanf(s, "%[^ ]", var->type);
			strcat(var->type, " ");//�ȸ�unsigned
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^ ]", temp);
			strcat(var->type, temp);//�ٸ����������
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}
		else
		{
			sscanf(s, "%[^ ]", var->type);//ֱ�Ӹ�����
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}


		if (strstr(var->type, "short") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 1;  //short Ϊ1������
			}
			else
			{
				var->kind = 2;  //unsigned short Ϊ2������
			}
		}
		if (strstr(var->type, "int") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 3;  //int Ϊ3������
			}
			else
			{
				var->kind = 4;  //unsigned int Ϊ4������
			}
		}
		if (strstr(var->type, "long") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 5;  //long Ϊ5������
			}
			else
			{
				var->kind = 6;  //unsigned long Ϊ6������
			}
		}
	}
}

bool PanMinB3(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
		flag = true;
	return flag;
}

void M_analysisB3(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		if (!strcmp(mig->Name, "strcpy") || !strcmp(mig->Name, "strcat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");              //����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո����Դ
			s++;
			s++;
			sscanf(s, "%[^)]", mig->yuan);
		}
		else if (!strcmp(mig->Name, "strncpy") || !strcmp(mig->Name, "memcpy") || !strcmp(mig->Name, "strncat"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->Mudi);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp);
			mig->n = atoi(temp);
		}
		else if (!strcmp(mig->Name, "sscanf"))
		{
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^,]", mig->yuan);
			s = strstr(s, ",");//�����м�������ʽ�����
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", mig->Mudi);
		}


	}
}

void H_analysisB3(char s[MaxChar], struct HuanChong* h)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };

	if (strstr(s, "[") != NULL)//���ҵ������ţ�˵��������������
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //�������к��о�����ֵ��ʾ�����Сʱ
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//Ҳ�����˳�ʼ��
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			}
		}
		else //�������в����о�����ֵ��ʾ�����Сʱ����������ֱ����ʾ��������ʱ�����˳�ʼ�������������ʱĬ�Ͻ����ַ���������г�ʼ��                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//�����������Զ��淶��ʽ���µĿո����
			h->realSize = h->size;
		}
	}
	if (strstr(s, "char*") != NULL || strstr(s, "short*") != NULL || strstr(s, "int*") || strstr(s, "long*") != NULL)
	{
		if (strstr(s, "HeapAlloc") == NULL)
		{
			sscanf(s, "%[^*]", h->type);
			s = strstr(s, "* ");//Ĭ��*�ź���һ���ո�
			s++;
			s++;
			sscanf(s, "%[^=]", h->Name);
		}
		else
		{
			sscanf(s, "%[^=]", h->Name);
			s = strstr(s, "(");
			s++;
			sscanf(s, "%[^)]", h->type);
			s = strstr(s, ",");//����s++�ƶ���λ����ΪVS������ֺź��Զ��淶��ʽʹ�ö��ź���Ĭ����һ���ո�
			s++;
			s++;
			s = strstr(s, ",");
			s++;
			s++;
			sscanf(s, "%[^)]", temp1);
			h->size = atoi(temp1);
		}
	}
}

bool PanCalB3(char s[MaxChar])//�ж��Ƿ���ڼ���
{
	bool flag = 0;
	if (strstr(s, "+") != NULL)
	{
		flag = 1;
	}
	else
	{
		if (strstr(s, "*") != NULL)
		{
			if (strstr(s, "malloc") != NULL)
			{
				flag = 1;
			}
			else if (strstr(s, "=") != NULL)
			{
				flag = 1;
			}
			else
				flag = 0;
		}
	}
	return flag;
}

void C_analysisB3(char s[MaxChar], struct Calcu* c)
{
	if (strstr(s, "+") != NULL)
	{
		sscanf(s, "%[^ =]", c->mudi);
		s = strstr(s, "=");
		s++;
		s++;
		sscanf(s, "%[^ +]", c->yuan1);
		s = strstr(s, "+");
		s++;
		s++;
		sscanf(s, "%[^;]", c->yuan2);
	}
	else if (strstr(s, "*") != NULL && strstr(s, "malloc") == NULL && strstr(s, "short*") == NULL && strstr(s, "int*") == NULL && strstr(s, "long*") == NULL)
	{
		sscanf(s, "%[^ =]", c->mudi);
		s = strstr(s, "=");
		s++;
		s++;
		sscanf(s, "%[^ *]", c->yuan1);
		s = strstr(s, "*");
		s++;
		s++;
		sscanf(s, "%[^;]", c->yuan2);
	}
	else if (strstr(s, "*") != NULL && strstr(s, "malloc") != NULL)
	{
		s = strstr(s, "malloc");//����ǰ��ת��ָ�����Ͳ���
		s = strstr(s, "(");
		s++;
		if (strstr(s, "*") != NULL)//�Դ��ڳ˺ţ�������ռ��С�д��ڳ˺�
		{
			sscanf(s, "%[^ *]", c->mudi);
			strcpy(c->yuan1, c->mudi);
			s = strstr(s, "*");
			s++;
			s++;
			sscanf(s, "%[^;]", c->yuan2);
		}
	}
}




int INTSym()
{
	int n = 0;
	int flag = 0;
	int migflag = 0;
	int sflag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "INTSymOF.cpp";//Ԥ���������INTSymOF.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;
	FILE* fp1, * fp2;

	struct Var* v;
	struct MiGan* m;
	struct FunctionB4* f;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionB4*)malloc(sizeof(struct FunctionB4));

	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncB4(fp2);

	rewind(fp2);

	f = f->next;
	

	int len;

	while (f != NULL)
	{
		m = f->mlist->next;
		v = f->vlist->next;
		while (m != NULL)
		{
			migflag = 1;
			len = m->n;
			if (len < 0)
				migflag = 2;//memcpy���е�������������n���ָ���

			if (migflag != 2)
				m = m->next;
			else
				break;
		}

		if (migflag == 2)
			OF = 2;
		else
			OF = 3;

		if (OF == 2)
		{
			if (m == NULL)
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  δ���������������\n");
			}
			else
			{
				printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
				printf("Jarvis>  ��������������ܷ����ڵ�%d��\n", m->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �У������ڵ� %d �� \n", f->begin, f->end);
			printf("Jarvis>  δ���������������\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB4* CreateFuncB4(FILE* fp)
{   //�������γ�����
	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionB4* funhead, * funtail, * funnew;


	funhead = (struct FunctionB4*)malloc(sizeof(struct FunctionB4));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncB4(line1))//�Ǻ����壬�����˺�����
		{
			funnew = (struct FunctionB4*)malloc(sizeof(struct FunctionB4));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;


			funnew->mlist = mtail;
			funnew->vlist = vtail;

			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (PanMinB4(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					M_analysisB4(line2, mnew);

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
		}
	}
	return funhead;
}

bool PanFuncB4(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

bool PanMinB4(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "strcpy") != NULL || strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strcat") != NULL || strstr(s, "strncat") != NULL || strstr(s, "sscanf") != NULL || strstr(s, "vfscanf") != NULL || strstr(s, "fscanf") != NULL || strstr(s, "vscanf") != NULL || strstr(s, "vsscanf") != NULL || strstr(s, "sprintf") != NULL || strstr(s, "vsprintf") != NULL || strstr(s, "gets") != NULL || strstr(s, "getchar") != NULL || strstr(s, "fgetc") != NULL || strstr(s, "getc") != NULL || strstr(s, "read") != NULL)
		flag = true;
	return flag;
}

void M_analysisB4(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };
	if (strstr(s, "strncpy") != NULL || strstr(s, "memcpy") != NULL || strstr(s, "memncpy") != NULL || strstr(s, "strncat") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		s = strstr(s, "(");
		s++;
		sscanf(s, "%[^,]", mig->Mudi);
		s = strstr(s, ",");
		s++;
		s++;
		sscanf(s, "%[^,]", mig->yuan);
		s = strstr(s, ",");
		s++;
		s++;
		sscanf(s, "%[^)]", temp);
		mig->n = atoi(temp);

	}
}




int GSH()
{
	int n = 0;
	int flag = 0;
	int migflag = 0;
	int sflag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "GSH.cpp";//Ԥ���������GSH.cpp�м��ļ�
	char MuDi[20] = { 0 };
	char Yuan[20] = { 0 };
	int MudiSize = 0;
	int YuanSize = 0;

	FILE* fp1, * fp2;

	struct Var* v;
	struct MiGan* m;
	struct FunctionR5* f;
	v = (struct Var*)malloc(sizeof(struct Var));
	m = (struct MiGan*)malloc(sizeof(struct MiGan));
	f = (struct FunctionR5*)malloc(sizeof(struct FunctionR5));
	printf("Jarvis>  INPUT THE FILENAME:\n");
	scanf("%s", infile);
	fp1 = fopen(infile, "r");
	fp2 = fopen(outfile, "w");
	PreTreat(fp1, fp2, infile, outfile);

	fclose(fp1);
	fclose(fp2);


	fp2 = fopen(outfile, "r");
	f = CreateFuncR5(fp2);

	system("pause");
	return 0;
}

struct FunctionR5* CreateFuncR5(FILE* fp)
{   //�������γ�����
	FILE* fpStart;
	char outfile2[20] = "GSH.cpp";
	fpStart = fopen(outfile2, "r");

	int row = 0;
	int NumOfZuo = 0, NumOfYou = 0, NumOfFu = 0;
	char line1[MaxChar] = { 0 };
	char line2[MaxChar] = { 0 };

	struct Var* vhead, * vtail, * vnew;
	struct MiGan* mhead, * mtail, * mnew;
	struct FunctionR5* funhead, * funtail, * funnew;


	funhead = (struct FunctionR5*)malloc(sizeof(struct FunctionR5));
	funtail = funhead;
	funtail->next = NULL;

	while (!feof(fp))
	{
		fgets(line1, MaxChar, fp);

		row++;

		if (PanFuncR5(line1))//�Ǻ����壬�����˺�����
		{
			int output = 0;
			funnew = (struct FunctionR5*)malloc(sizeof(struct FunctionR5));
			funnew->begin = row;
			vhead = (struct Var*)malloc(sizeof(struct Var));
			vtail = vhead;
			vtail->next = NULL;
			mhead = (struct MiGan*)malloc(sizeof(struct MiGan));
			mtail = mhead;
			mtail->next = NULL;


			funnew->mlist = mtail;
			funnew->vlist = vtail;


			funtail->next = funnew;
			funtail = funnew;
			funtail->next = NULL;

			NumOfZuo = NumOfChar(line1, "{");
			NumOfFu = NumOfFu + NumOfZuo;
			do
			{
				fgets(line2, MaxChar, fp);

				row++;

				NumOfZuo = NumOfChar(line2, "{");
				NumOfFu = NumOfFu + NumOfZuo;
				NumOfYou = NumOfChar(line2, "}");
				NumOfFu = NumOfFu - NumOfYou;

				if (PanMinR5(line2))
				{
					mnew = (struct MiGan*)malloc(sizeof(struct MiGan));
					mnew->row = row;

					if (M_analysisR5(line2, mnew) == 1)
					{
						output = 1;
						printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �� \n", funnew->begin);
						printf("Jarvis>  ��ʽ���ַ����������ڵ�%d��\n", mnew->row);
						FILE* temp = fpStart;
						Show(temp, mnew->row);
					}
					else if (M_analysisR5(line2, mnew) == 2)
					{
						output = 1;
						printf("Jarvis>  ��ǰ������ʼ�ڵ� %d �� \n", funnew->begin);
						printf("Jarvis>  ��ʽ���ַ���������ܷ����ڵ�%d��\n", mnew->row);
						Show(fpStart, mnew->row);
					}
					else if (M_analysisR5(line2, mnew) == 3)
					{
						printf("Jarvis>  δ������ʽ���ַ�������\n");
					}

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
			if (output == 1)
			{
				printf("Jarvis>  ��ǰ���������ڵ�%d��\n", funnew->end);
			}
		}
	}
	return funhead;
}

bool PanFuncR5(char s[MaxChar])//�ж��Ƿ��ҵ�����������Ǻ�������
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//��δ�ҵ��ֺ�ʱ������Ϊ�����������Ǻ�����
				flag = 1;
		}
	}
	return flag;
}

bool PanMinR5(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()��fgetc()��getc()��read(),sscanf()��fscanf()��vfscanf()��vscanf()��vsscanf()
{
	bool flag = 0;
	if (strstr(s, "printf") != NULL)
		flag = 1;
	return flag;
}

int M_analysisR5(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };//Ĭ�ϰٷֺź���ֻ��һ����ʽ����
	int num = 0;
	int realnum = 0;
	char* pt;
	if (strstr(s, "printf") != NULL)
	{
		sscanf(s, "%[^(]", mig->Name);
		while (strstr(s, "%") != NULL)
		{
			num++;
			s = strstr(s, "%");
			s++;
			sscanf(s, "%1c", &temp[num]);//��1��num��¼�˸�����ʽ����
		}

		s = strstr(s, "\"");
		s = strstr(s, ",");
		s++;
		while (strstr(s, ",") != NULL)
		{
			realnum++;
			s = strstr(s, ",");
			s++;
		}

		if (num > realnum&& temp[num] == 'x')
		{
			return 1;
		}
		else if (num > realnum&& temp[num] != 'x')
		{
			return 2;
		}
		else
			return 3;


	}
}