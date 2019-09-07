#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
#define max_word_len 100
#define max_words 100
typedef long long ll;

void prompt()
{
    char hostname[50];
    char direc[50];
    getcwd(direc, 50);
    gethostname(hostname, 50);
    cout<<endl<<getenv("USER")<<'@';
    int id = getuid();
    cout<<hostname;
    cout<<" "<<direc<<' ';
    if(!id)
        cout<<"(#)";
    else
        cout<<"($)";
    cout<<" :";
}

/*void input(char **carrptr, string &str, bool &b)
{
    char ch;
    ch = getchar();
    int lv=0;
    while(ch != '\n' && ch != '\0')
    {
        str[lv] = ch;
        ++lv;
    }
    carrptr = new char[str.length()+1];
    int lv1 = 0, lv2 = 0, count=0;
    lv=0;
    while(count < str.length())
    {
        if(str[lv] == '|')
            b = true;
        if(str[lv] != ' ' && str[lv] != '\n' && str[lv] != '\0')
        {
            carrptr[lv1][lv2] = str[lv];
            ++lv2;
        }
        else
        {
            ++lv1;
            lv2=0;
        }
        ++count;
    }
    carrptr[lv+1] = NULL;
}*/ 

void child_handler(char** parr, bool pflag, bool rtflag);


void eval_pipe(char** ptr, bool rtflag)
{
    cout<<"evaluating pipe\n";
    int lv, count=0;
    int start, end;
    bool rend = false;
    //cout<<ptr[0]<<' '<<ptr[1]<<' '<<ptr[2]<<' '<<ptr[3]<<' '<<ptr[4]<<' '<<endl;
    
    char** dupptr;
    //int f = fork(), status;
    int fd[2];
    //pipe(fd);
    for(lv=0; ptr[lv] != NULL && !rend; lv++)
    {
        start = lv;
        end = lv+1;
        cout<<"inital start end "<<start<<' '<<end<<endl;
        while(ptr[end] != NULL && strcmp(ptr[end], "|") != 0)
        {
            cout<<"end "<<end<<endl;
            ++end;
            cout<<"end again "<<end<<endl;
        }
        cout<<"updated start end "<<start<<' '<<end<<endl;
        if(ptr[end] == NULL)
        {
            rend = true;
            cout<<"reached NULL\n";
        }
        ptr[end] = NULL;
        
        dupptr = ptr+start;
        if(rend == true)
        {
            cout<<"breaking away\n";
            break;
        }
        pipe(fd);
        int f = fork();
        int status;
        if(f)
        {
            //cout<<"parent executing child number "<<f<<endl;
            waitpid(f, &status, 0);
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            lv = end;
            cout<<"lv updated "<<lv<<endl;
        }
        else
        {
            cout<<"child\n";
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
            execvp(ptr[start], dupptr);
            _exit(status);
            cout<<"exit child\n";
        }      
    }
    cout<<"loop exit\n";
    if(!rtflag)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execvp(ptr[start], dupptr);    
    }
    else
    {
        child_handler(ptr+start, false, true);
    }
    
}
void child_handler(char** parr, bool pflag, bool rtflag)
{
    ll lv;
    int fd;
    bool decide;
    char pathh[30];
    getcwd(pathh, 30);
    for(lv=0; parr[lv] != NULL; lv++);
    if(pflag || rtflag)
    {
        if(!pflag && rtflag)
        {
            
            //cout<<"runnin\n";
            lv -= 2;
            //cout<<parr[lv+1]<<endl;
            //strcat(pathh, parr[lv+1]);
            //cout<<pathh<<endl;
            
            decide = (strcmp(parr[lv], ">") == 0)?true:false;
            if(!decide)
                fd = open(parr[lv+1], O_RDWR | O_CREAT | O_APPEND);
            else
                fd = open(parr[lv+1], O_WRONLY | O_CREAT | O_TRUNC );
            parr[lv] = NULL;
            chmod(parr[lv+1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
            cout<<"fd "<<fd<<endl;
            //close(1);
            dup2(fd, 1);
            execvp(parr[0], parr);
            close(fd);
            //cout<<"done dana done dan\n";
        }
        else
        {
            eval_pipe(parr, rtflag);    
        }



    }
    else
    {
        int s_f = execvp(parr[0], parr);
        if(s_f == -1)
            cout<<"\t\terror\n";
    }
}

void change_direc(char *cptr[], char pdir[30])
{
    char *path = cptr[1];
    char prevpath2[30];
    //cout<<"prev start "<<pdir<<endl;
    if(path == NULL || strlen(path) == 0 || strcmp(path, "~") == 0)
    {
        //cout<<"homepath\n";
        getcwd(pdir, 30);
        chdir(getenv("HOME"));
    }
    else if(strcmp(path, "-") == 0)
    {
        //cout<<"prevpath\n";
        getcwd(prevpath2, 30);
        chdir(pdir);
        strcpy(pdir, prevpath2);
    }
    else
    {
        //cout<<"normpath\n";
        getcwd(pdir, 30);
        int f = chdir(path);
        if(f == -1)
            cout<<"\t\tInvalid path\n";
    }
    //cout<<"prev end "<<pdir<<endl;
}

int main()
{
    //char *charr[10];
    char ch;
    int lv = -1;
    bool pipeflag, redirflag;
    char prevdir[30];
    getcwd(prevdir, 30);
    while(1)
    {
        pipeflag = false;
        redirflag = false;
        prompt();
        //cout<<"prompted\n";
        char **charr = new char*[max_words];
        
        //getcwd(currdir);
        //cout<<"allocated memory\n";
        //string str;
        //input(charr, str, &pipeflag);
        lv = -1;
    	do{
    	    ++lv;
    	    charr[lv] = new char[max_word_len];
    	    cin>>charr[lv];
            if(strcmp(charr[lv], "|") == 0)
                pipeflag = true;
            else if(strcmp(charr[lv], ">") == 0 || strcmp(charr[lv], ">>") == 0)
                redirflag = true;
    	    //cout<<lv<<" took inp of "<<charr[lv]<<endl;
    	    ch = getchar();

    	}while(ch != '\n');
    	++lv;
    	charr[lv] = NULL;
        int lv = 0;
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
        if(strlen(charr[0]) == 0)
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