/*   This program uses GBK encoding,please open it in GBK format.
First write time:2024/4/8 12:56
Last edit time:2024/4/15 12:36
Version:V1.0.0 Stable-Version
Author:Ctanin
*/

#pragma GCC optimize(3)   //臭氧优化
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
class User   //用户结构体
{
    public:
        string name;
        string password;
        LL mark;
        UL last_problem;
};
bool is_login=false;   //登录标志
LL problems_total;   //总题目数
ifstream USER_IN,PROBLEM_IN,ANSWER_IN;   //读入文件流
ofstream USER_OUT;   //写出文件流
vector<User> users;   //存储用户信息的向量
vector<User>::iterator now_user;   //当前用户迭代器
string problems[MAXN],answers[MAXN],user_answer;   //问题、答案及用户的回答
inline void check_problem(string &problem)   //将问题中的\替换成\n
{
    for (LL n=0;n<problem.length();n++)
    {
        if (problem[n]=='\\')
        {
            problem[n]='\n';
        }
    }
}
inline void init(void)   //初始化函数
{
    cout<<"调整代码页为936......"<<endl;
    system("chcp 936");
    cout<<"调整颜色......"<<endl;
    system("color f0");
    system("cls");   //调整页面
    USER_IN.open("user.lst",ios::in);
    if (USER_IN.is_open()!=true)   //检测用户信息文件是否打开，若否则创建
    {
        system("type nul>user.lst");
        USER_IN.open("user.lst",ios::in);
    }
    User data;   //临时对象
    while (USER_IN>>data.name)   //读入用户信息
    {
        USER_IN>>data.password;
        USER_IN>>data.mark;
        USER_IN>>data.last_problem;
        users.push_back(data);
    }
    PROBLEM_IN.open("problems.lst",ios::in);
    ANSWER_IN.open("answers.lst",ios::in);
    if (PROBLEM_IN.is_open()!=true||ANSWER_IN.is_open()!=true)   //检查题库是否存在
    {
        system("cls");
        cout<<"致命错误：文件损坏 请关闭软件并重新安装"<<endl;
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
inline void title_before_login(void)   //登录前标题
{
    cout<<"欢迎使用本软件-----你还未登录"<<endl<<endl;
    cout<<"请选择功能："<<endl;
    cout<<"0.登录（前提）"<<endl;
    cout<<"1.顺序练习"<<endl;
    cout<<"2.随机抽取"<<endl;
    cout<<"3.帮助"<<endl;
    cout<<"4.个人中心"<<endl;
    cout<<"5.退出"<<endl;
    cout<<"请输入你的选择：";
}
inline void title_after_login(void)   //登录后标题
{
    cout<<"欢迎使用本软件"<<endl<<endl;
    cout<<now_user->name<<"同志，欢迎回来！     "<<"当前分数："<<now_user->mark<<"分"<<endl;
    cout<<"请选择功能："<<endl;
    cout<<"1.顺序练习"<<endl;
    cout<<"2.随机抽取"<<endl;
    cout<<"3.帮助"<<endl;
    cout<<"4.个人中心"<<endl;
    cout<<"5.退出"<<endl;
    cout<<"请输入你的选择：";
}
inline void login_error(void)   //未登录提示函数
{
    system("cls");
    cout<<"你还未登录！3秒后自动跳转"<<endl;
    Sleep(3000);
}
inline void input_error(void)   //非法输入提示函数
{
    system("cls");
    cout<<"操作码有误！3秒后自动跳转"<<endl;
    Sleep(3000);
}
inline void help(void)   //帮助界面显示函数
{
    system("cls");
    cout<<"当前版本：V1.0.0 Stable-Version"<<endl;
    cout<<"开源地址：https://github.com/Ctanin/ExamHelper"<<endl;
    cout<<"注意："<<endl;
    cout<<"1.退出时请使用菜单中的“退出”功能，否则无法保存用户信息；"<<endl;
    cout<<"2.不要修改题库文件；"<<endl;
    cout<<"3.忘记密码时，请到“user.lst”文件中寻找；"<<endl;
    cout<<"4.若要退出题目界面，请输入“Quit”并回车（注意大小写）；"<<endl;
    cout<<"5.本程序有后门，但请不要乱用；"<<endl<<endl;
    system("pause");
}
inline void show_user(void)   //个人中心显示函数
{
    system("cls");
    cout<<"用户名："<<now_user->name<<endl;
    cout<<"密码："<<now_user->password<<endl;
    cout<<"上次顺序完成到："<<now_user->last_problem<<"题"<<endl;
    cout<<"分数："<<now_user->mark<<endl<<endl;
    system("pause");
}
inline void save(void)   //用户信息保存函数
{
    USER_OUT.open("user.lst",ios::out);
    for (vector<User>::iterator it=users.begin();it!=users.end();it++)
    {
        USER_OUT<<it->name<<endl<<it->password<<endl<<it->mark<<endl<<it->last_problem<<endl;;
    }
}
vector<User>::iterator search(string user_name)   //查找用户函数
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
    US choice;   //操作码
    User data;   //临时对象
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
                    cout<<"你已经登录过了！3秒后自动跳转"<<endl;
                    Sleep(3000);
                    goto START;
                }
                system("cls");
                cout<<"请选择："<<endl;
                cout<<"1.注册"<<endl;
                cout<<"2.登录"<<endl;
                cout<<"请输入你的选择：";
                cin>>choice;
                switch (choice)
                {
                    case 1:
                        system("cls");
                        cout<<"请输入用户名（不可带有空格）：";
                        cin>>data.name;
                        if (search(data.name)!=users.end())
                        {
                            system("cls");
                            cout<<"该同志已存在！3秒后自动跳转"<<endl;
                            Sleep(3000);
                            goto START;
                        }
                        cout<<"请输入密码（不可带有空格）：";
                        cin>>data.password;
                        data.mark=0;
                        users.push_back(data);
                        now_user=search(data.name);
                        is_login=true;
                        goto START;
                    case 2:
                        system("cls");
                        cout<<"请输入用户名：";
                        cin>>data.name;
                        now_user=search(data.name);
                        if (now_user==users.end())
                        {
                            system("cls");
                            cout<<"用户不存在！3秒后自动跳转"<<endl;
                            Sleep(3000);
                            goto START;
                        }
                        cout<<"请输入密码：";
                        cin>>data.password;
                        if (data.password!=now_user->password)
                        {
                            system("cls");
                            cout<<"密码错误！3秒后自动跳转"<<endl;
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
                    cout<<"请输入你的答案（多个答案请用“,”隔开）：";
                    cin>>user_answer;
                    if (user_answer=="Quit")   //退出
                      break;
                    if (user_answer==answers[n])
                    {
                        system("cls");
                        cout<<"答对啦！奖励卢比扬卡一日游！ +2分"<<endl;
                        now_user->mark=now_user->mark+2;
                        Sleep(1000);
                    }
                    else
                    {
                        system("cls");
                        cout<<"答错啦！去古拉格挖土豆吧！ -2分"<<endl;
                        now_user->mark=now_user->mark-2;
						cout<<"正确答案："<<answers[n]<<endl;
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
                    cout<<"请输入你的答案（多个答案请用“,”隔开）：";
                    cin>>user_answer;
                    if (user_answer=="Quit")   //退出
                      break;
                    if (user_answer==answers[problem_order])
                    {
                        system("cls");
                        cout<<"答对啦！奖励卢比扬卡一日游！ +2分"<<endl;
                        now_user->mark=now_user->mark+2;
						Sleep(1000);
                    }
                    else
                    {
                        system("cls");
                        cout<<"答错啦！去古拉格挖土豆吧！ -2分"<<endl;
                        now_user->mark=now_user->mark-2;
                        cout<<"正确答案："<<answers[problem_order]<<endl;
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
    USER_OUT.close();   //关闭程序
     return 0;
}
