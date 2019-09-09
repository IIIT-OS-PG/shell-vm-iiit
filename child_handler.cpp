#include"header.h"

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
            //cout<<"fd "<<fd<<endl;
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