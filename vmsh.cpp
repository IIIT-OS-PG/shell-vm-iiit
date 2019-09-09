#include"header.h"

int main()
{
    //char *charr[10];
    char ch;
    int lv = -1;
    bool pipeflag, redirflag;
    char prevdir[30];
    bool record = false;
    getcwd(prevdir, 30);
    while(1)
    {
        pipeflag = false;
        redirflag = false;
        prompt();
        //cout<<"prompted\n";
        char **charr = input(pipeflag, redirflag);
        
        //getcwd(currdir);
        //cout<<"allocated memory\n";
        //string str;
        //input(charr, str, &pipeflag);
        //while(charr[lv])
          //  cout<<charr[lv++]<<endl;
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
        if(charr[0] == NULL)
            continue;
        if(strcmp(charr[0], "exit") == 0)
        {
            break;
            //delete charr;
        }
        else if(strcmp(charr[0], "cd") == 0)
        {

            change_direc(charr, prevdir);
        }
        /*if(strcmp(charr[0], "cd") == 0)
        {
            int f = chdir(charr+)
        }*/
        else
        {
            int f = fork();
            int status;
            if(f)
            {
                //cout<<"     inside parent\n";
                waitpid(f, &status, 0);
                //cout<<"     parent's wait ended\n";
            }
            else
            {
                //cout<<"     inside child\n";
                child_handler(charr, pipeflag, redirflag);
                _exit(status);
            }    
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