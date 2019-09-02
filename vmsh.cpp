#include<iostream>
#include<string.h>
using namespace std;
#define max_word_len = 20;
#define max_words = 50;

int main()
{
    char *charr[10];
    char ch;
    int lv = -1;
    while(1)
    {
    	do{
    	    ++lv;
    	    charr[lv] = new char[10];
    	    cin>>charr[lv];
    	    cout<<lv<<" took inp of "<<charr[lv]<<endl;
    	    ch = getchar();
    	}while(ch != '\n');
    	++lv;
    	charr[lv] = NULL;
    	cout<<"loop done\n";
    	while(lv>-1)
    	{
        	cout<<lv<<endl;
        	if(charr[lv])
            	cout<<charr[lv]<<endl;
        	else
            	cout<<"nulla\n";
            --lv;
    	}
    }
}