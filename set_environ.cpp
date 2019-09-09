#include"header.h"
void set_environ()
{
	//string line;
	cout<<"setenv called\n";
	ifstream filein("vmshrc.txt");
	int lv1, len, i;
	string var, val;
	char varstring[50], valstring[150];
	for(string line; getline(filein, line);)
	{
		//cout<<"LL "<<line<<endl;
		lv1=0;
		for(len=0; line[lv1+len] != '='; len++);
		var = line.substr(lv1, len);

		lv1 = len+1;
		for(len=0; line[lv1+len] != '\n' && line[lv1+len] != '\0'; len++);	
		val = line.substr(lv1, len);
		strcpy(varstring, var.c_str());
		strcpy(valstring, val.c_str());
		cout<<varstring<<'='<<valstring<<endl;
		//unsetenv(varstring);
		i = setenv(varstring, valstring, 1);
		if(i == 0)
			cout<<"success "<<varstring<<"\n";
		else
			cout<<"fail env"<<endl;
	}
	/*char dir[30];
	chdir(getenv("HOME"));
	getcwd(dir,30);
	cout<<dir<<endl;*/
}