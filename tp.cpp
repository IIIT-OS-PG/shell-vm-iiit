#include<iostream>
#include<termios.h>
#include<unistd.h>

using namespace std;


int main()
{
    //char ch;
    struct termios p1, p2;
       int x =  tcgetattr(0, &p1);
       p2 = p1;
      p1.c_lflag &= (ICANON | ECHO);
      //p1.c_lflag &= IEXTEN;
       cout<<x<<endl;
       int lv = 10;
       char ch;
       string str;
    tcsetattr(0, TCSANOW,  &p1);
    while(lv--)
    {
        ch = getchar();
       // cout<<ch<<endl;

    }

    tcsetattr(0, TCSANOW,  &p2);
    lv = 10;
   /* while(lv--)
    {
        ch = getchar();
        cout<<ch<<endl;
    }*/
}

