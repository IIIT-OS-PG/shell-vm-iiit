#include"header.h"

void eval_pipe(char** ptr, bool rtflag)
{
    //cout<<"evaluating pipe\n";
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
        //cout<<"inital start end "<<start<<' '<<end<<endl;
        while(ptr[end] != NULL && strcmp(ptr[end], "|") != 0)
        {
            //cout<<"end "<<end<<endl;
            ++end;
            //cout<<"end again "<<end<<endl;
        }
        //cout<<"updated start end "<<start<<' '<<end<<endl;
        if(ptr[end] == NULL)
        {
            rend = true;
            //cout<<"reached NULL\n";
        }
        ptr[end] = NULL;
        
        dupptr = ptr+start;
        if(rend == true)
        {
            //cout<<"breaking away\n";
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
            //cout<<"lv updated "<<lv<<endl;
        }
        else
        {
            //cout<<"child\n";
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
            execvp(ptr[start], dupptr);
            _exit(status);
            //cout<<"exit child\n";
        }      
    }
    //cout<<"loop exit\n";
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