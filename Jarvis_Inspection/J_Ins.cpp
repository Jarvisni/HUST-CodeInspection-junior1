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
//以上关键字暂时支持到99标准，若更新仅需添加几个关键字
//默认一行一个语句


typedef struct Function {   //每个函数默认最多三个参数，名字均小于20，类型名均小于10
	char re_value[10];      //单独的函数链表，用来记录文件中所有函数，用于比较
	char Name[20];
	int parasum;
	char para1[10];
	char para2[10];
	char para3[10];
	struct Function* next;
}Function;

typedef struct FuncList {   //内部子函数的链表
	char Name[20];
	struct FuncList* next;
}FuncList;

typedef struct List {      //总体上各函数链表，其中包含子函数链表的头指针
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


int CFG();                                       //CFG使用此函数
void CFG_THR1(char s1[MaxChar], char s2[MaxChar]);//CFG多线程使用此函数
void CFG_THR2(char s1[MaxChar], char s2[MaxChar]);//CFG多线程使用此函数
void CFG_THR3(char s1[MaxChar], char s2[MaxChar]);//CFG多线程使用此函数
void CFG_THR4(char s1[MaxChar], char s2[MaxChar]);//CFG多线程使用此函数
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


int string_same();//字符串匹配使用此函数
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

int main()       //空函数参数默认有一个空格,不考虑指针型参数，int*会读为int
{
	int op = 0, op2 = 0;
	while (op != 4)
	{
		op2 = 0;
		system("cls");
		printf("%s", logo1);
		printf("Welcome to Jarvis Inspection!\n");
		printf("You Can Analyse The Homology or Discover The Loophole\n");
		printf("Please Choose from below(input 1 or 2) : 1、同源性检测  2、漏洞检测\n");
		printf("input 4 to quit the exe\n");
		scanf("%d", &op);
		if (op == 1)
		{
			while (op2 != 4)
			{
				system("cls");
				printf("%s", logo1);
				printf("Which kind of homology analysis would you choose?\n");
				printf("(input 1 or 2 or 3) 1、字符串  2、CFG  3、多线程CFG\n");
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
					printf("Jarvis>  输入想要将哪个文件作为比较模板(例如 3.c)\n");
					scanf("%s", infile1);
					printf("Jarvis>  输入四个将与之进行比较的文件(例如4 4 4 4）\n");
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
				printf("(input 1~6) 1、栈溢出  2、堆溢出  3、整数宽度溢出  4、整数运算溢出  5、整数符号溢出  6、格式化字符串漏洞  \n");
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
	ifstream filein(fileInput.c_str());//读取输入文件
	ofstream fileout(fileOutput);      //预处理后程序保存到"temp1.cpp"中
	unsigned int i, j, k;
	unsigned int size;
	string instring, outstring;           //字符串 instring,outstring
	bool flag = false;                      //用于标记
	while (getline(filein, instring))     //读取文件内容
	{
		size = instring.size();
		outstring = "";                 //outstring预设空
		flag = false;                   //flag初始化
		for (i = 0; i < size; )         //进行这一行内的处理
		{
			if (instring[i] == '\t' || instring[i] == '\n')
			{
				i++;
				continue;
			}

			while (instring[i] == ' ')//用于实现行前多空格预处理，若有空格则仅留下一个
			{
				i++;
				flag = true;
			}
			if (flag == true)
			{
				outstring += " ";
				flag = false;
			}

			if (instring[i] == '/' && instring[i + 1] == '/')  //对于单行注释进行处理，注释均是单独的或行或块
			{
				break;
			}
			else if (instring[i] == '/' && instring[i + 1] == '*') //对于多行注释进行处理，需要直到*/的全消灭，考虑到下一个字符间的空格
			{
				while (instring[i] != '*')
				{
					if (instring[i] == '\n')
					{
						fileout << outstring << endl;  //把字符串outstring保存到fileout;
						getline(filein, instring);     //默认/**/此种注释不会出现在末行
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


			j = i;//此处j和i均是消灭注释后再次遇到的非空格非注释字符的位置
			if (instring[j] == ';')
			{
				outstring += "_SEMI";   //有分号就进行了替换
				break;                  //一行之中分号结尾，默认分号后没有语句，且没有空行无字符语句（待完善）
			}
			else if (instring[j] == '{')
			{
				outstring += "_LSP";    //有左大括号进行了替换，默认左右大括号单独成行（待完善）
				break;                  //一行之中遇到左右大括号默认此行只有一个符号
			}
			else if (instring[j] == '}')
			{
				outstring += "_RSP";    //有右大括号进行了替换，默认左右大括号单独成行（待完善）
				break;                  //一行之中遇到左右大括号默认此行只有一个符号
			}
			else if (instring[j] == '(')
			{
				outstring += "_LP";    //有左括号进行了替换
				i = j + 1;               //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == ')')
			{
				outstring += "_RP";    //有右括号进行了替换
				i = j + 1;               //从下一个字符继续进行预处理
				if (i >= size) break;  //存在以右括号结尾的语句
				continue;
			}
			else if (instring[j] == '[')
			{
				outstring += "_LSB";    //有左方括号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == ']')
			{
				outstring += "_RSB";    //有右方括号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '+')
			{
				outstring += "_PLUS";    //有加号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '-')
			{
				outstring += "_MINUS";    //有减括号进行了替换
				i = j + 1;                  //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '*')
			{
				outstring += "_MULTIPLED";    //有乘号进行了替换
				i = j + 1;                      //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '/')
			{
				outstring += "_DIVIDED";    //有除号进行了替换
				i = j + 1;                    //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '=')
			{
				outstring += "_ASSIGN";    //有等号进行了替换
				i = j + 1;                 //从下一个字符继续进行预处理
				continue;
			}


			while (instring[j] != ' ' && instring[j] != '(' && instring[j] != ')' && instring[j] != ';' && instring[j] != '+' && instring[j] != '-' && instring[j] != '*' && instring[j] != '/' && instring[j] != '=')//以上都不是，则从第一个非空格直到下一次遇到空格中间的字符串可能是关键字或是标识符
				j++;
			string temp = instring.substr(i, j - i);
			for (rint k = 0; k < 37; k++)
			{
				if (KeyWord[k] == temp)
				{
					outstring += KeyToken[k];   //有关键字进行了替换
					flag = true;
					break;
				}
			}
			if (flag == true)  //再次处理空格后移向下一非空格非注释   感觉需要把这一段整个循环多次
			{
				flag = false;
				i = j;
				continue;
			}
			else               //不是关键字，而是标识符
			{
				outstring += "_ID";   //有标识符进行了替换
				i = j;
				continue;
			}

		}
		if (outstring == "")
			fileout << outstring;          //空字符串就什么都不用输出
		else
			fileout << outstring << endl;  //把字符串outstring保存到fileout

	}
}

void pretreat1_2(string fileInput, string fileOutput)
{
	ifstream filein(fileInput.c_str());//读取输入文件
	ofstream fileout(fileOutput);      //预处理后程序保存到"temp1.cpp"中
	unsigned int i, j, k;
	unsigned int size;
	string instring, outstring;           //字符串 instring,outstring
	bool flag = false;                    //用于标记
	while (getline(filein, instring))     //读取文件内容
	{
		size = instring.size();
		outstring = "";                 //outstring预设空
		flag = false;                   //flag初始化
		for (i = 0; i < size; )         //进行这一行内的处理
		{
			if (instring[i] == '\t' || instring[i] == '\n')
			{
				i++;
				continue;
			}

			while (instring[i] == ' ')//用于实现行前多空格预处理，若有空格则仅留下一个
			{
				i++;
				flag = true;
			}
			if (flag == true)
			{
				outstring += " ";
				flag = false;
			}

			if (instring[i] == '/' && instring[i + 1] == '/')  //对于单行注释进行处理，注释均是单独的或行或块
			{
				break;
			}
			else if (instring[i] == '/' && instring[i + 1] == '*') //对于多行注释进行处理，需要直到*/的全消灭，考虑到下一个字符间的空格
			{
				i += 2;
				while (instring[i] != '*')
				{
					if (i == size)
					{
						fileout << outstring;		   //把字符串outstring保存到fileout;
						getline(filein, instring);     //默认/**/此种注释不会出现在末行
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


			j = i;//此处j和i均是消灭注释后再次遇到的非空格非注释字符的位置
			if (instring[j] == ';')
			{
				outstring += "_SEMI";   //有分号就进行了替换
				break;                  //一行之中分号结尾，默认分号后没有语句，且没有空行无字符语句（待完善）
			}
			else if (instring[j] == '{')
			{
				outstring += "_LSP";    //有左大括号进行了替换，默认左右大括号单独成行（待完善）
				break;                  //一行之中遇到左右大括号默认此行只有一个符号
			}
			else if (instring[j] == '}')
			{
				outstring += "_RSP";    //有右大括号进行了替换，默认左右大括号单独成行（待完善）
				break;                  //一行之中遇到左右大括号默认此行只有一个符号
			}
			else if (instring[j] == '(')
			{
				outstring += "_LP";    //有左括号进行了替换
				i = j + 1;               //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == ')')
			{
				outstring += "_RP";    //有右括号进行了替换
				i = j + 1;               //从下一个字符继续进行预处理
				if (i >= size) break;  //存在以右括号结尾的语句
				continue;
			}
			else if (instring[j] == '[')
			{
				outstring += "_LSB";    //有左方括号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == ']')
			{
				outstring += "_RSB";    //有右方括号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '+')
			{
				outstring += "_PLUS";    //有加号进行了替换
				i = j + 1;                //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '-')
			{
				outstring += "_MINUS";    //有减括号进行了替换
				i = j + 1;                  //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '*')
			{
				outstring += "_MULTIPLED";    //有乘号进行了替换
				i = j + 1;                      //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '/')
			{
				outstring += "_DIVIDED";    //有除号进行了替换
				i = j + 1;                    //从下一个字符继续进行预处理
				continue;
			}
			else if (instring[j] == '=')
			{
				outstring += "_ASSIGN";    //有等号进行了替换
				i = j + 1;                 //从下一个字符继续进行预处理
				continue;
			}


			while (instring[j] != ' ' && instring[j] != '(' && instring[j] != ')' && instring[j] != ';' && instring[j] != '+' && instring[j] != '-' && instring[j] != '*' && instring[j] != '/' && instring[j] != '=')//以上都不是，则从第一个非空格直到下一次遇到空格中间的字符串可能是关键字或是标识符
				j++;
			string temp = instring.substr(i, j - i);
			for (rint k = 0; k < 37; k++)
			{
				if (KeyWord[k] == temp)
				{
					outstring += KeyToken[k];   //有关键字进行了替换
					flag = true;
					break;
				}
			}
			if (flag == true)  //再次处理空格后移向下一非空格非注释   感觉需要把这一段整个循环多次
			{
				flag = false;
				i = j;
				continue;
			}
			else               //不是关键字，而是标识符
			{
				outstring += "_ID";   //有标识符进行了替换
				i = j;
				continue;
			}

		}
		if (outstring == "")
			fileout << outstring;          //空字符串就什么都不用输出,此时outstring为空
		else
			fileout << outstring;          //把字符串outstring保存到fileout

	}
}

void Getnext(int next[], string t)  //KMP中的next函数
{
	int j = 0, k = -1;
	next[0] = -1;
	while (j < t.length() - 1)
	{
		if (k == -1 || t[j] == t[k])
		{
			j++; k++;
			if (t[j] == t[k])		//当两个字符相同时，就跳过
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
		else j = next[j];              //j回退。。。
	}
	if (j >= t.length())
		return (i - (t.length()));         //匹配成功，返回子串的位置
	else
		return (-1);                  //没找到
}

int string_same()
{
	string fileInput_1, fileOutput_1;
	string fileInput_2, fileOutput_2;

	printf("Jarvis>  请输入想要进行检查的文件名：（比如1.cpp）\n");
	cin >> fileInput_1;
	fileOutput_1 = "temp1.cpp";
	pretreat1_1(fileInput_1, fileOutput_1);

	printf("Jarvis>  请输入想要用于对比的文件名：（比如2.cpp）\n");
	cin >> fileInput_2;
	fileOutput_2 = "temp2.cpp";
	pretreat1_2(fileInput_2, fileOutput_2);

	ifstream filein(fileOutput_2.c_str());//读取输入文件
	string instring;
	getline(filein, instring);
	int total = instring.length();
	double ratio;
	double sameThing = 0;

	ifstream fileintemp(fileOutput_1.c_str());//读取输入文件
	string temp;
	while (getline(fileintemp, temp))     //读取文件内容
	{
		if (KMP(instring, temp) != (-1))
		{
			sameThing += temp.length();
		}
	}
	ratio = sameThing / total;
	printf("Jarvis>  第一个文件和第二个文件的相似度为  %lf  \n", ratio);
	if (ratio <= 0.2)
		printf("Jarvis>  几率很小，Congratulations！\n");
	else if (ratio <= 0.5)
		printf("Jarvis>  几率中等，请多加注意！\n");
	else
		printf("Jarvis>  请不要抄袭他人代码！WARNING PLEASE DO NOT COPY\n");

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
							flag2 = strstr(temp, "*/");//直到找到一行里面有右边的符号，无需操作继续循环会取下一行继续运行
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
		if (PanFunc(line))           //是函数体开头，而不是函数声明，则进入此函数体
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

			int NumOfZuo = 0;  //同一函数体对应的左右大括号一定是一样数量的
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

struct Function* CreateFunction(FILE* fp)  //对于函数的使用默认只能是全部填充完整的使用，且空格需要严格添加
{
	struct Function* head, * tail;
	char line[MaxChar] = { 0 };

	head = (struct Function*)malloc(sizeof(struct Function));
	head->next = NULL;
	tail = head;

	while (!(feof(fp)))
	{
		fgets(line, MaxChar, fp);
		if (PanDuan(line))//判断为函数声明或者函数体开头，而不是对于函数的使用，此处用来生成所有各不相同的函数链接形成的链表
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
					if (strcmp(temp->Name, newNode->Name) == 0)//用于判断是否这个函数已经写过了
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

bool PanDuan(char s[MaxChar])  //判断
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
	sscanf(s, "%[^ ]", f->re_value);//第一部分为返回值
	s = strstr(s, " ");
	s++;                                          //此时里面有空格让找到吗？

	sscanf(s, "%[^(]", f->Name);//第二部分为名字
	s = strstr(s, "(");
	s++;							             //此时里面有让找到吗？

	int temp;
	temp = NumOfChar(s, ",");
	f->parasum = temp + 1;//参数数量为逗号数量多一个

	if (temp == 0)//此时仅有一个参数
	{
		sscanf(s, "%[^ ]", f->para1);
	}
	else if (temp == 1)//此时有两个参数
	{
		sscanf(s, "%[^ ]", f->para1);
		s = strstr(s, ",");//由于逗号后面总是跟有空格，所以此处移动两次
		s++;
		s++;
		sscanf(s, "%[^ ]", f->para2);
	}
	else if (temp == 2)//此时有三个参数，最多考虑到三个参数情况
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

bool PanFunc(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
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

int CFG()      //空函数参数默认有一个空格,不考虑指针型参数，int*会读为int
{
	printf("Jarvis>  请输入想要进行检查的文件名：（比如3.c）\n");
	FILE* fp1, * fp2, * fp3, * fp4;
	struct List* list1;
	struct List* list2;
	scanf("%s", infile1);
	printf("Jarvis>  请输入想要用于对比的文件名：（比如4）\n");
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

	printf("\n注：CFG图中第一竖列为程序中的函数体出现顺序，每一行后面几列为第一列中函数体内包含的子函数出现顺序\n");
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
	int FunNum = 0;   //函数体链表中函数体个数,默认全部声明，空格到位
	int f1Num = 0;    //第一个函数体中的子函数个数
	int SameNum = 0;  //两个函数体中函数名相同的个数
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
		f1 = L1->head;//改成f1=L1->head->next;删去这两行
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//改成f2=L2->head->next;删去这两行
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //从第二个链表中找到和第一个链表中相同的函数体入口
				f2head = f2;
				while (f1->next != NULL)  //若函数体内有子函数，则标记flag2为1，否则0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //每次f2从头来和f1进行比较

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
				else if (!flag2 && f2head->next == NULL)   //当有两个函数体但是内部都没有子函数，此时无法断定，默认此时两个函数体相同
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //当有两个函数体但是第一个内部没有子函数而第二个有，此时默认两个函数体不相同
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
		if (!flag1)//即没有和第一个函数体一样的第二个函数体，此时对于此第一个函数体对应的可能性为0
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
	printf("由CFG图进行比较可知两者相似度为：%.5lf \n", ratio);
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

	printf("\n注：CFG图中第一竖列为程序中的函数体出现顺序，每一行后面几列为第一列中函数体内包含的子函数出现顺序\n");
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
	int FunNum = 0;   //函数体链表中函数体个数,默认全部声明，空格到位
	int f1Num = 0;    //第一个函数体中的子函数个数
	int SameNum = 0;  //两个函数体中函数名相同的个数
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
		f1 = L1->head;//改成f1=L1->head->next;删去这两行
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//改成f2=L2->head->next;删去这两行
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //从第二个链表中找到和第一个链表中相同的函数体入口
				f2head = f2;
				while (f1->next != NULL)  //若函数体内有子函数，则标记flag2为1，否则0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //每次f2从头来和f1进行比较

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
				else if (!flag2 && f2head->next == NULL)   //当有两个函数体但是内部都没有子函数，此时无法断定，默认此时两个函数体相同
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //当有两个函数体但是第一个内部没有子函数而第二个有，此时默认两个函数体不相同
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
		if (!flag1)//即没有和第一个函数体一样的第二个函数体，此时对于此第一个函数体对应的可能性为0
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
	printf("由CFG图进行比较可知两者相似度为：%.5lf \n", ratio);
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

	printf("\n注：CFG图中第一竖列为程序中的函数体出现顺序，每一行后面几列为第一列中函数体内包含的子函数出现顺序\n");
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
	int FunNum = 0;   //函数体链表中函数体个数,默认全部声明，空格到位
	int f1Num = 0;    //第一个函数体中的子函数个数
	int SameNum = 0;  //两个函数体中函数名相同的个数
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
		f1 = L1->head;//改成f1=L1->head->next;删去这两行
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//改成f2=L2->head->next;删去这两行
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //从第二个链表中找到和第一个链表中相同的函数体入口
				f2head = f2;
				while (f1->next != NULL)  //若函数体内有子函数，则标记flag2为1，否则0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //每次f2从头来和f1进行比较

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
				else if (!flag2 && f2head->next == NULL)   //当有两个函数体但是内部都没有子函数，此时无法断定，默认此时两个函数体相同
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //当有两个函数体但是第一个内部没有子函数而第二个有，此时默认两个函数体不相同
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
		if (!flag1)//即没有和第一个函数体一样的第二个函数体，此时对于此第一个函数体对应的可能性为0
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
	printf("由CFG图进行比较可知两者相似度为：%.5lf \n", ratio);
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

	printf("\n注：CFG图中第一竖列为程序中的函数体出现顺序，每一行后面几列为第一列中函数体内包含的子函数出现顺序\n");
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
	int FunNum = 0;   //函数体链表中函数体个数,默认全部声明，空格到位
	int f1Num = 0;    //第一个函数体中的子函数个数
	int SameNum = 0;  //两个函数体中函数名相同的个数
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
		f1 = L1->head;//改成f1=L1->head->next;删去这两行
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//改成f2=L2->head->next;删去这两行
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //从第二个链表中找到和第一个链表中相同的函数体入口
				f2head = f2;
				while (f1->next != NULL)  //若函数体内有子函数，则标记flag2为1，否则0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //每次f2从头来和f1进行比较

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
				else if (!flag2 && f2head->next == NULL)   //当有两个函数体但是内部都没有子函数，此时无法断定，默认此时两个函数体相同
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //当有两个函数体但是第一个内部没有子函数而第二个有，此时默认两个函数体不相同
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
		if (!flag1)//即没有和第一个函数体一样的第二个函数体，此时对于此第一个函数体对应的可能性为0
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
	printf("由CFG图进行比较可知两者相似度为：%.5lf \n", ratio);
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

	printf("\n注：CFG图中第一竖列为程序中的函数体出现顺序，每一行后面几列为第一列中函数体内包含的子函数出现顺序\n");
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
	int FunNum = 0;   //函数体链表中函数体个数,默认全部声明，空格到位
	int f1Num = 0;    //第一个函数体中的子函数个数
	int SameNum = 0;  //两个函数体中函数名相同的个数
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
		f1 = L1->head;//改成f1=L1->head->next;删去这两行
		f1 = f1->next;
		FunNum++;
		strcpy(L1Name, f1->Name);
		while (L2->next != NULL)
		{
			L2 = L2->next;
			f2 = L2->head;//改成f2=L2->head->next;删去这两行
			f2 = f2->next;
			strcpy(L2Name, f2->Name);
			if (strcmp(L1Name, L2Name) == 0 || XiangTong(L1Name, L2Name))
			{
				flag1 = 1;                //从第二个链表中找到和第一个链表中相同的函数体入口
				f2head = f2;
				while (f1->next != NULL)  //若函数体内有子函数，则标记flag2为1，否则0
				{
					f1 = f1->next;
					f1Num++;

					flag2 = 1;
					f2 = f2head;          //每次f2从头来和f1进行比较

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
				else if (!flag2 && f2head->next == NULL)   //当有两个函数体但是内部都没有子函数，此时无法断定，默认此时两个函数体相同
				{
					ratio = 1.0;
					Allratio[k] = ratio;
				}
				else if (!flag2 && f2head->next != NULL)  //当有两个函数体但是第一个内部没有子函数而第二个有，此时默认两个函数体不相同
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
		if (!flag1)//即没有和第一个函数体一样的第二个函数体，此时对于此第一个函数体对应的可能性为0
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
	printf("由CFG图进行比较可知两者相似度为：%.5lf \n", ratio);
	return;
}




int SOF()
{
	int n = 0;
	int flag = 0;
	int OF = 0;
	char infile[20] = { 0 };
	char outfile[20] = "SOF.cpp";//预处理后生成SOF.cpp中间文件
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
					printf("Jarvis>  栈溢出发生在第%d行\n", m->row);
					Show(fp2, m->row);
					system("pause");
				}
				else if (OF == 2)
				{
					printf("Jarvis>  第%d行存在敏感函数但未产生栈溢出\n", m->row);
					system("pause");
				}
			}
			else if (flag == 0)
			{
				printf("Jarvis>  暂未发现敏感函数\n");
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
{   //函数体形成链表
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

		if (PanFuncR4(line1))//是函数体，则进入此函数体
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

bool PanFuncR4(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
				flag = 1;
		}
	}
	return flag;
}

void V_analysisR4(char s[MaxChar], struct Var* var)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };

	if (strstr(s, "[") != NULL) //能找到左方括号，说明含有数组类型
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", var->type);

		s = strstr(s, " ");
		s++;

		sscanf(s, "%[^[]", var->Name);
		s = strstr(s, "[");
		s++;

		if (*s != ']') //方括号中含有具体数值表示数组大小时
		{
			sscanf(s, "%[^]]", temp1);
			var->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//也进行了初始化
			{
				sscanf(s, "%[^;]", temp2);
				var->realSize = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			}
		}
		else //方括号中不含有具体数值表示数组大小时，即方括号直接显示完整，此时进行了初始化数组操作，此时默认仅对字符串数组进行初始化                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			var->size = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			var->realSize = var->size;
		}
	}
	else //不是数组
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

			if (strstr(s, "=") == NULL) //没有等号，即没有进行初始化数组操作
			{
				s = strstr(s, " ");
				s++;
				sscanf(s, "%[^;]", var->Name);
			}
			else //有等号
			{
				s = strstr(s, " ");
				s++;
				sscanf(s, "%[^=]", var->Name);
			}
		}
	}
}

bool PanMinR4(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
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
			s = strstr(s, ",");              //两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格
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
			s = strstr(s, ",");//跳过中间描述格式的语句
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
	printf("Jarvis>  原代码： %s  \n", line1);
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
	char outfile[20] = "HOF.cpp";//预处理后生成HOF.cpp中间文件
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
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  堆溢出发生在第%d行\n", m->row);
				Show(fp2, m->row);
			}
			else if (OF == 2)
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  堆溢出可能发生在第%d行\n", m->row);
				Show(fp2, m->row);
			}
			else if (OF == 3)
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  第%d行存在敏感函数但未产生堆溢出\n", m->row);
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
{   //函数体形成链表
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

		if (PanFuncB1(line1))//是函数体，则进入此函数体
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
				{//printf中的int字符会引起错误
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

bool PanFuncB1(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
				flag = 1;
		}
	}
	return flag;
}

void V_analysisB1(char s[MaxChar], struct Var* var)
{
	char temp1[100] = { 0 };
	char temp2[100] = { 0 };


	//不是数组
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

		if (strstr(s, "=") == NULL) //没有等号，即没有进行初始化数组操作
		{
			s = strstr(s, " ");
			s++;
			sscanf(s, "%[^;]", var->Name);
		}
		else //有等号
		{
			s = strstr(s, " ");
			s++;
			sscanf(s, "%[^=]", var->Name);
		}
	}

}

bool PanMinB1(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
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
			s = strstr(s, ",");              //两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格才是源
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
			s = strstr(s, ",");//跳过中间描述格式的语句
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

	if (strstr(s, "[") != NULL)//能找到左方括号，说明含有数组类型
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //方括号中含有具体数值表示数组大小时
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//也进行了初始化
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			}
		}
		else //方括号中不含有具体数值表示数组大小时，即方括号直接显示完整，此时进行了初始化数组操作，此时默认仅对字符串数组进行初始化                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			h->realSize = h->size;
		}
	}
	if (strstr(s, "char*") != NULL || strstr(s, "short*") != NULL || strstr(s, "int*") || strstr(s, "long*") != NULL)
	{
		if (strstr(s, "HeapAlloc") == NULL)
		{
			sscanf(s, "%[^*]", h->type);
			s = strstr(s, "* ");//默认*号后有一个空格
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
			s = strstr(s, ",");//两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格
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
	char outfile[20] = "INTwidthOF.cpp";//预处理后生成INTwidthOF.cpp中间文件
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
		while (XT != NULL) //赋值语句溢出
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
			if (lkind < rkind)//存在导致宽度溢出的情况
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
				if (strstr(bj->num, v->Name))//存在对其边界检查
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
				if (!strcmp(h->Name, MuDi))//敏感函数目标数组和缓冲区相同
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


		if (xtflag == 2 && migflag == 2 && bjflag != 2)//赋值语句左边小于右边，敏感函数的目标数组与之相同，溢出
			OF = 1;
		if (xtflag == 2 && migflag == 2 && bjflag == 2)//可能溢出
			OF = 2;
		if ((xtflag == 2 && migflag != 2) || (xtflag == 0 && bjflag == 2))//无赋值语句或无敏感函数或有边界检查，不溢出
			OF = 3;
		if (OF == 1)
		{
			if (XT == NULL || m == NULL)
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  未产生整数宽度溢出\n");
			}
			else
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  由第%d行引起的整数宽度溢出发生在第%d行\n", XT->row, m->row);
				Show(fp2, XT->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 2)
		{
			if (XT == NULL || m == NULL)
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  未产生整数宽度溢出\n");
			}
			else
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  由第%d行引起的整数宽度溢出可能发生在第%d行\n", XT->row, m->row);
				Show(fp2, XT->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
			printf("Jarvis>  未产生整数宽度溢出\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB2* CreateFuncB2(FILE* fp)
{   //函数体形成链表
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

		if (PanFuncB2(line1))//是函数体，则进入此函数体
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
				{//printf中的int字符会引起错误
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

bool PanFuncB2(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
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
		if (strstr(s, "unsigned ") != NULL)  //前面是否有unsigned
		{
			sscanf(s, "%[^ ]", var->type);
			strcat(var->type, " ");//先给unsigned
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^ ]", temp);
			strcat(var->type, temp);//再给后面的类型
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}
		else
		{
			sscanf(s, "%[^ ]", var->type);//直接给类型
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}


		if (strstr(var->type, "short") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 1;  //short 为1号类型
			}
			else
			{
				var->kind = 2;  //unsigned short 为2号类型
			}
		}
		if (strstr(var->type, "int") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 3;  //int 为3号类型
			}
			else
			{
				var->kind = 4;  //unsigned int 为4号类型
			}
		}
		if (strstr(var->type, "long") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 5;  //long 为5号类型
			}
			else
			{
				var->kind = 6;  //unsigned long 为6号类型
			}
		}
	}
}

bool PanMinB2(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
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
			s = strstr(s, ",");              //两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格才是源
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
			s = strstr(s, ",");//跳过中间描述格式的语句
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

	if (strstr(s, "[") != NULL)//能找到左方括号，说明含有数组类型
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //方括号中含有具体数值表示数组大小时
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//也进行了初始化
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			}
		}
		else //方括号中不含有具体数值表示数组大小时，即方括号直接显示完整，此时进行了初始化数组操作，此时默认仅对字符串数组进行初始化                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
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

	if (strstr(s, "=") != NULL)//存在等号时
	{
		temp1 = strstr(temp1, "=");
		temp1++;
		temp1++;//自动添加的空格

		sscanf(temp1, "%[^;]", temp2);

		for (int i = 0; i < strlen(temp2); i++)
		{
			if (!(temp2[i] >= '0' && temp2[i] <= '9'))
				continue;
			else  //等号右边存在0-9时，即不为字母赋值时
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
	char outfile[20] = "INTcalcuOF.cpp";//预处理后生成INTcalcuOF.cpp中间文件
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
				if (!strcmp(h->Name, MuDi))//敏感函数目标数组和缓冲区相同
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

		if (cflag == 2 && migflag == 2)//目标变量不为long型时并且敏感函数的目标数组与之相同
			OF = 2;
		else
			OF = 3;

		if (OF == 2)
		{
			if (c == NULL || m == NULL)
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  未产生整数运算溢出\n");
			}
			else
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  由第%d行引起的整数运算溢出可能发生在第%d行\n", c->row, m->row);
				Show(fp2, c->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
			printf("Jarvis>  未产生整数运算溢出\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB3* CreateFuncB3(FILE* fp)
{   //函数体形成链表
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

		if (PanFuncB3(line1))//是函数体，则进入此函数体
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
				{//printf中的int字符会引起错误
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

bool PanFuncB3(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
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
		if (strstr(s, "unsigned ") != NULL)  //前面是否有unsigned
		{
			sscanf(s, "%[^ ]", var->type);
			strcat(var->type, " ");//先给unsigned
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^ ]", temp);
			strcat(var->type, temp);//再给后面的类型
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}
		else
		{
			sscanf(s, "%[^ ]", var->type);//直接给类型
			s = strstr(s, " ");
			s++;

			sscanf(s, "%[^;]", var->Name);
		}


		if (strstr(var->type, "short") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 1;  //short 为1号类型
			}
			else
			{
				var->kind = 2;  //unsigned short 为2号类型
			}
		}
		if (strstr(var->type, "int") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 3;  //int 为3号类型
			}
			else
			{
				var->kind = 4;  //unsigned int 为4号类型
			}
		}
		if (strstr(var->type, "long") != NULL)
		{
			if (strstr(var->type, "unsigned ") == NULL)
			{
				var->kind = 5;  //long 为5号类型
			}
			else
			{
				var->kind = 6;  //unsigned long 为6号类型
			}
		}
	}
}

bool PanMinB3(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
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
			s = strstr(s, ",");              //两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格才是源
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
			s = strstr(s, ",");//跳过中间描述格式的语句
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

	if (strstr(s, "[") != NULL)//能找到左方括号，说明含有数组类型
	{
		if (strstr(s, "*") == NULL && (strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL))
			sscanf(s, "%[^ ]", h->type);
		s = strstr(s, " ");
		s++;
		sscanf(s, "%[^[]", h->Name);
		s = strstr(s, "[");
		s++;
		if (*s != ']')  //方括号中含有具体数值表示数组大小时
		{
			sscanf(s, "%[^]]", temp1);
			h->size = atoi(temp1);
			if (strstr(s, "=") != NULL)//也进行了初始化
			{
				sscanf(s, "%[^;]", temp2);
				h->realSize = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			}
		}
		else //方括号中不含有具体数值表示数组大小时，即方括号直接显示完整，此时进行了初始化数组操作，此时默认仅对字符串数组进行初始化                
		{
			s = strstr(s, "=");
			sscanf(s, "%[^;]", temp2);
			h->size = (strlen(temp2) - 4);//减四是由于自动规范格式导致的空格出现
			h->realSize = h->size;
		}
	}
	if (strstr(s, "char*") != NULL || strstr(s, "short*") != NULL || strstr(s, "int*") || strstr(s, "long*") != NULL)
	{
		if (strstr(s, "HeapAlloc") == NULL)
		{
			sscanf(s, "%[^*]", h->type);
			s = strstr(s, "* ");//默认*号后有一个空格
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
			s = strstr(s, ",");//两个s++移动两位是因为VS中输入分号后自动规范格式使得逗号后面默认有一个空格
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

bool PanCalB3(char s[MaxChar])//判断是否存在计算
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
		s = strstr(s, "malloc");//跳过前面转换指针类型部分
		s = strstr(s, "(");
		s++;
		if (strstr(s, "*") != NULL)//仍存在乘号，即后面空间大小中存在乘号
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
	char outfile[20] = "INTSymOF.cpp";//预处理后生成INTSymOF.cpp中间文件
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
				migflag = 2;//memcpy等中第三个参数出现n出现负数

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
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  未产生整数符号溢出\n");
			}
			else
			{
				printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
				printf("Jarvis>  整数符号溢出可能发生在第%d行\n", m->row);
				Show(fp2, m->row);
			}
		}
		else if (OF == 3)
		{
			printf("Jarvis>  当前函数开始于第 %d 行，结束于第 %d 行 \n", f->begin, f->end);
			printf("Jarvis>  未产生整数符号溢出\n");
		}

		f = f->next;
		if (f == NULL)
			break;

	}
	system("pause");
	return 0;
}

struct FunctionB4* CreateFuncB4(FILE* fp)
{   //函数体形成链表
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

		if (PanFuncB4(line1))//是函数体，则进入此函数体
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

bool PanFuncB4(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
				flag = 1;
		}
	}
	return flag;
}

bool PanMinB4(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
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
	char outfile[20] = "GSH.cpp";//预处理后生成GSH.cpp中间文件
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
{   //函数体形成链表
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

		if (PanFuncR5(line1))//是函数体，则进入此函数体
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
						printf("Jarvis>  当前函数开始于第 %d 行 \n", funnew->begin);
						printf("Jarvis>  格式化字符串错误发生在第%d行\n", mnew->row);
						FILE* temp = fpStart;
						Show(temp, mnew->row);
					}
					else if (M_analysisR5(line2, mnew) == 2)
					{
						output = 1;
						printf("Jarvis>  当前函数开始于第 %d 行 \n", funnew->begin);
						printf("Jarvis>  格式化字符串错误可能发生在第%d行\n", mnew->row);
						Show(fpStart, mnew->row);
					}
					else if (M_analysisR5(line2, mnew) == 3)
					{
						printf("Jarvis>  未发生格式化字符串错误\n");
					}

					mtail->next = mnew;
					mtail = mnew;
					mtail->next = NULL;
				}

			} while (NumOfFu);

			funnew->end = row;
			if (output == 1)
			{
				printf("Jarvis>  当前函数结束于第%d行\n", funnew->end);
			}
		}
	}
	return funhead;
}

bool PanFuncR5(char s[MaxChar])//判断是否找到函数体而不是函数声明
{
	bool flag = 0;
	if (strstr(s, "(") != NULL)
	{
		if (strstr(s, "void") != NULL || strstr(s, "int") != NULL || strstr(s, "long") != NULL || strstr(s, "short") != NULL || strstr(s, "float") != NULL || strstr(s, "double") != NULL || strstr(s, "char") != NULL)
		{
			if (strstr(s, ";") == NULL)//当未找到分号时，即不为函数声明而是函数体
				flag = 1;
		}
	}
	return flag;
}

bool PanMinR5(char s[MaxChar])//strcpy,strncpy,memcpy,memncpy,strcat,strncat, sprintf(),vsprintf(),gets(),getchar()、fgetc()、getc()、read(),sscanf()、fscanf()、vfscanf()、vscanf()、vsscanf()
{
	bool flag = 0;
	if (strstr(s, "printf") != NULL)
		flag = 1;
	return flag;
}

int M_analysisR5(char s[MaxChar], struct MiGan* mig)
{
	char temp[20] = { 0 };//默认百分号后面只有一个格式符号
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
			sscanf(s, "%1c", &temp[num]);//从1到num记录了各个格式符号
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