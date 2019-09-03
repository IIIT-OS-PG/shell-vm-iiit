#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
using namespace std;
#define max_word_len 20
#define max_words 50

int main()
{
    //char *charr[10];
    char ch;
    int lv = -1;
    while(1)
    {
        cout<<getenv("USER")<<'@';
        //cout<<getenv("HOSTNAME");
        cout<<':'<<getenv("PWD")<<": ";

        char **charr = new char*[max_words];
    	do{
    	    ++lv;
    	    charr[lv] = new char[max_word_len];
    	    cin>>charr[lv];
    	    //cout<<lv<<" took inp of "<<charr[lv]<<endl;
    	    ch = getchar();
    	}while(ch != '\n');
    	++lv;
    	charr[lv] = NULL;
        //cout<<"     lv end "<<lv<<endl;
    	//cout<<"loop done\n";
    	/*while(lv>-1)
    	{
        	cout<<lv<<endl;
        	if(charr[lv])
            	cout<<charr[lv]<<endl;
        	else
            	cout<<"null\n";
            --lv;
    	}*/
        if(strcmp(charr[0], "exit") == 0)
        {
            break;
            //delete charr;
        }
        int f = fork();
        if(f)
        {
            //cout<<"     inside parent\n";
            wait(NULL);
            //cout<<"     parent's wait ended\n";
        }
        else
        {
            //cout<<"     inside child\n";
            int s_f = execvp(charr[0], charr);
            if(s_f == -1)
                cout<<"     error\n";
            //cout<<"     exiting child\n";
            exit(0);
        }
        //cout<<f<<"      deleting memory\n";
        --lv;
        //cout<<"lv "<<lv<<endl;
        while(lv>-1)
        {
            //cout<<f<<"      deleting "<<charr[lv]<<endl;
            delete charr[lv];
            //cout<<f<<"      deleted\n";
            --lv;
        }
        //cout<<f<<"      deleted indivs\n";
        delete charr;
    }
    
    return 0;
}