#include"header.h"

#define max_word_len 100
#define max_words 100

char** input(bool& pflag, bool& rflag)
{
    char **ptr;
    char ch;
    int lv1 = -1, lv2=0;
    bool line_end = false;
    bool enter;
    pflag = false;
    rflag = false;
    ptr = new char*[max_words];
    /*if(ptr[1] == NULL)
        cout<<"NULL func\n";*/
    //ptr = NULL;
    do{
        ch = getchar();
        lv2=0;
        //cout<<"beg lv1 lv2 "<<lv1<<' '<<lv2<<endl;
        enter = true;
        while(ch == '\n' || ch == ' ')
        {
            //cout<<"parsing space\n";
            if(ch == '\n')
            {
                //cout<<"encountered newline\n";
                line_end = true;
                enter = false;
                break;
            }
            ch = getchar();
        }
        //cout<<"extra spaces\n";
        //ptr[lv1] = NULL;
        if(enter)
        {
            //cout<<"incrementing lv1\n";
            ++lv1;
            //cout<<"incremened to "<<lv1<<endl;
            ptr[lv1] = new char[max_word_len];
            //cout<<"allotted mem to ptr"<<lv1<<endl;
            while(1)
            {
                //++lv1;
                if(ch != ' ' && ch != '\n' && ch != '\0')
                {
                    //cout<<"inserting character "<<ch<<" at "<<lv1<<' '<<lv2<<endl;
                    ptr[lv1][lv2] = ch;
                    if(ch == '>')
                        rflag = true;
                    else if(ch == '|')
                        pflag = true;
                    //cout<<"inserted "<<ptr[lv1][lv2]<<endl;
                    ++lv2;
                    ch = getchar();
                }
                else if(ch == ' ')
                {
                    //cout<<"space break\n";
                    break;
                }

                //ch = getchar();
                else if(ch == '\n')
                {
                    line_end = true;
                    //cout<<"breakin away\n";
                    break;
                }
            }
            //cout<<"inserted "<<ptr[lv1]<<" at index "<<lv1<<endl;
        }
        else
            break;
        //cout<<"end lv1 lv2 "<<lv1<<' '<<lv2<<endl;
    }while(!line_end);

    //cout<<"setin index "<<lv1+1<<" to null\n";
    ptr[lv1+1] = NULL;
    //cout<<ptr[0]<<endl;
    /*if(ptr[1] == NULL)
        cout<<"NULL\n";*/
    return ptr;
}