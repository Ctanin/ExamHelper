/*   This program uses GBK encoding,please open it in GBK format.
First write time:2024/4/8 12:56
Last edit time:2024/4/15 12:36
Version:V1.0.0 Stable-Version
Author:Ctanin
*/

#pragma GCC optimize(3)   //�����Ż�
#define MAXN 10001
#include<windows.h>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>
using namespace std;
typedef unsigned long long int UL;
typedef long long int LL;
typedef unsigned short US;
typedef double DB;
class User   //�û��ṹ��
{
    public:
        string name;
        string password;
        LL mark;
        UL last_problem;
};
bool is_login=false;   //��¼��־
LL problems_total;   //����Ŀ��
ifstream USER_IN,PROBLEM_IN,ANSWER_IN;   //�����ļ���
ofstream USER_OUT;   //д���ļ���
vector<User> users;   //�洢�û���Ϣ������
vector<User>::iterator now_user;   //��ǰ�û�������
string problems[MAXN],answers[MAXN],user_answer;   //���⡢�𰸼��û��Ļش�
inline void check_problem(string &problem)   //�������е�\�滻��\n
{
    for (LL n=0;n<problem.length();n++)
    {
        if (problem[n]=='\\')
        {
            problem[n]='\n';
        }
    }
}
inline void init(void)   //��ʼ������
{
    cout<<"��������ҳΪ936......"<<endl;
    system("chcp 936");
    cout<<"������ɫ......"<<endl;
    system("color f0");
    system("cls");   //����ҳ��
    USER_IN.open("user.lst",ios::in);
    if (USER_IN.is_open()!=true)   //����û���Ϣ�ļ��Ƿ�򿪣������򴴽�
    {
        system("type nul>user.lst");
        USER_IN.open("user.lst",ios::in);
    }
    User data;   //��ʱ����
    while (USER_IN>>data.name)   //�����û���Ϣ
    {
        USER_IN>>data.password;
        USER_IN>>data.mark;
        USER_IN>>data.last_problem;
        users.push_back(data);
    }
    PROBLEM_IN.open("problems.lst",ios::in);
    ANSWER_IN.open("answers.lst",ios::in);
    if (PROBLEM_IN.is_open()!=true||ANSWER_IN.is_open()!=true)   //�������Ƿ����
    {
        system("cls");
        cout<<"���������ļ��� ��ر���������°�װ"<<endl;
        system("pause");
    }
    PROBLEM_IN>>problems_total;
    for (LL n=0;n<=problems_total;n++)
    {
        getline(PROBLEM_IN,problems[n]);
        if (n!=0)
        {
            check_problem(problems[n]);
            ANSWER_IN>>answers[n];
        }
    }
}
inline void title_before_login(void)   //��¼ǰ����
{
    cout<<"��ӭʹ�ñ����-----�㻹δ��¼"<<endl<<endl;
    cout<<"��ѡ���ܣ�"<<endl;
    cout<<"0.��¼��ǰ�ᣩ"<<endl;
    cout<<"1.˳����ϰ"<<endl;
    cout<<"2.�����ȡ"<<endl;
    cout<<"3.����"<<endl;
    cout<<"4.��������"<<endl;
    cout<<"5.�˳�"<<endl;
    cout<<"���������ѡ��";
}
inline void title_after_login(void)   //��¼�����
{
    cout<<"��ӭʹ�ñ����"<<endl<<endl;
    cout<<now_user->name<<"ͬ־����ӭ������     "<<"��ǰ������"<<now_user->mark<<"��"<<endl;
    cout<<"��ѡ���ܣ�"<<endl;
    cout<<"1.˳����ϰ"<<endl;
    cout<<"2.�����ȡ"<<endl;
    cout<<"3.����"<<endl;
    cout<<"4.��������"<<endl;
    cout<<"5.�˳�"<<endl;
    cout<<"���������ѡ��";
}
inline void login_error(void)   //δ��¼��ʾ����
{
    system("cls");
    cout<<"�㻹δ��¼��3����Զ���ת"<<endl;
    Sleep(3000);
}
inline void input_error(void)   //�Ƿ�������ʾ����
{
    system("cls");
    cout<<"����������3����Զ���ת"<<endl;
    Sleep(3000);
}
inline void help(void)   //����������ʾ����
{
    system("cls");
    cout<<"��ǰ�汾��V1.0.0 Stable-Version"<<endl;
    cout<<"��Դ��ַ��https://github.com/Ctanin/ExamHelper"<<endl;
    cout<<"ע�⣺"<<endl;
    cout<<"1.�˳�ʱ��ʹ�ò˵��еġ��˳������ܣ������޷������û���Ϣ��"<<endl;
    cout<<"2.��Ҫ�޸�����ļ���"<<endl;
    cout<<"3.��������ʱ���뵽��user.lst���ļ���Ѱ�ң�"<<endl;
    cout<<"4.��Ҫ�˳���Ŀ���棬�����롰Quit�����س���ע���Сд����"<<endl;
    cout<<"5.�������к��ţ����벻Ҫ���ã�"<<endl<<endl;
    system("pause");
}
inline void show_user(void)   //����������ʾ����
{
    system("cls");
    cout<<"�û�����"<<now_user->name<<endl;
    cout<<"���룺"<<now_user->password<<endl;
    cout<<"�ϴ�˳����ɵ���"<<now_user->last_problem<<"��"<<endl;
    cout<<"������"<<now_user->mark<<endl<<endl;
    system("pause");
}
inline void save(void)   //�û���Ϣ���溯��
{
    USER_OUT.open("user.lst",ios::out);
    for (vector<User>::iterator it=users.begin();it!=users.end();it++)
    {
        USER_OUT<<it->name<<endl<<it->password<<endl<<it->mark<<endl<<it->last_problem<<endl;;
    }
}
vector<User>::iterator search(string user_name)   //�����û�����
{
    for (vector<User>::iterator it=users.begin();it!=users.end();it++)
    {
        if (it->name==user_name)
        {
            return it;
        }
    }
    return users.end();
}
int main()
{
    ios::sync_with_stdio(false);
    LL problem_order;
    US choice;   //������
    User data;   //��ʱ����
    init();
    for ( ; ; )
    {
START:  system("cls");
        if (is_login==false)
            title_before_login();
        else
            title_after_login();
        cin>>choice;
        switch (choice)
        {
            case 0:
                if (is_login==true)
                {
                    system("cls");
                    cout<<"���Ѿ���¼���ˣ�3����Զ���ת"<<endl;
                    Sleep(3000);
                    goto START;
                }
                system("cls");
                cout<<"��ѡ��"<<endl;
                cout<<"1.ע��"<<endl;
                cout<<"2.��¼"<<endl;
                cout<<"���������ѡ��";
                cin>>choice;
                switch (choice)
                {
                    case 1:
                        system("cls");
                        cout<<"�������û��������ɴ��пո񣩣�";
                        cin>>data.name;
                        if (search(data.name)!=users.end())
                        {
                            system("cls");
                            cout<<"��ͬ־�Ѵ��ڣ�3����Զ���ת"<<endl;
                            Sleep(3000);
                            goto START;
                        }
                        cout<<"���������루���ɴ��пո񣩣�";
                        cin>>data.password;
                        data.mark=0;
                        users.push_back(data);
                        now_user=search(data.name);
                        is_login=true;
                        goto START;
                    case 2:
                        system("cls");
                        cout<<"�������û�����";
                        cin>>data.name;
                        now_user=search(data.name);
                        if (now_user==users.end())
                        {
                            system("cls");
                            cout<<"�û������ڣ�3����Զ���ת"<<endl;
                            Sleep(3000);
                            goto START;
                        }
                        cout<<"���������룺";
                        cin>>data.password;
                        if (data.password!=now_user->password)
                        {
                            system("cls");
                            cout<<"�������3����Զ���ת"<<endl;
                            Sleep(3000);
                            goto START;
                        }
                        is_login=true;
                        goto START;
                    default:
                        input_error();
                        goto START;
                }
            case 1:
                if (is_login!=true)
                {
                    login_error();
                    goto START;
                }
                for (LL n=now_user->last_problem;n<=problems_total;n++)
                {
                    system("cls");
                    if (now_user->last_problem>problems_total)
                        n=now_user->last_problem=1;
                    else
                        now_user->last_problem=n;
                    cout<<problems[n]<<endl<<endl;
                    cout<<"��������Ĵ𰸣���������á�,����������";
                    cin>>user_answer;
                    if (user_answer=="Quit")   //�˳�
                      break;
                    if (user_answer==answers[n])
                    {
                        system("cls");
                        cout<<"�����������¬���￨һ���Σ� +2��"<<endl;
                        now_user->mark=now_user->mark+2;
                        Sleep(1000);
                    }
                    else
                    {
                        system("cls");
                        cout<<"�������ȥ�������������ɣ� -2��"<<endl;
                        now_user->mark=now_user->mark-2;
						cout<<"��ȷ�𰸣�"<<answers[n]<<endl;
						system("pause");
                    }
                }
                goto START;
            case 2:
                if (is_login!=true)
                {
                    login_error();
                    goto START;
                }
                for ( ; ; )
                {
                    system("cls");
                    srand(time(NULL));
                    problem_order=rand()%(problems_total+1);
                    cout<<problems[problem_order]<<endl<<endl;
                    cout<<"��������Ĵ𰸣���������á�,����������";
                    cin>>user_answer;
                    if (user_answer=="Quit")   //�˳�
                      break;
                    if (user_answer==answers[problem_order])
                    {
                        system("cls");
                        cout<<"�����������¬���￨һ���Σ� +2��"<<endl;
                        now_user->mark=now_user->mark+2;
						Sleep(1000);
                    }
                    else
                    {
                        system("cls");
                        cout<<"�������ȥ�������������ɣ� -2��"<<endl;
                        now_user->mark=now_user->mark-2;
                        cout<<"��ȷ�𰸣�"<<answers[problem_order]<<endl;
						system("pause");
                    }
                    
                }
                goto START;
            case 3:
                help();
                goto START;
            case 4:
                if (is_login!=true)
                {
                    login_error();
                    goto START;
                }
                show_user();
                goto START;
            case 5:
                save();
                goto END;
            default:
                input_error();
                goto START;
        }
    }
END:USER_IN.close();
    USER_OUT.close();   //�رճ���
     return 0;
}
