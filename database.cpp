#include<bits/stdc++.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>

using namespace std;
#include "Files/base.h"
#include "Files/queryProcessor.h"

static string db="";

int main()
{
	
	string s="";
	cout<<"Query> ";
	getline(cin,s);
	s=::tolwr(s);
	
	while(s!="exit"&&s!="quit")
	{
		
	     if(s=="clear")
		   system("cls");
		 else if(s=="help")
		{
			system("cls");
			cout<<"HELP Words and Queries >>"<<endl;
            //	Display words;
            cout<<endl;
            string s1="temp";
            while(s1!="")
            {
            	cout<<"Press ENTER to go back"<<endl;
            	getline(cin,s1);
			}
			system("cls");
		}
		else if(s!="")
		{
		    s=removeSpaceToOne(s);
		    if(s!=" ")
	    	{
	    		s=makeQuery(s);
	    		s=removeSpaceToOne(s);
			    vector<string> words;
			    processWords(words,s);
			    if(words[0]!="use"&&db!="")
				process(words,db);
				else if(words[0]=="use")
				{
					if(words.size()<=2)
					  {
					  db=words[1];
					  string cmdstr="md dbs\\"+db;
					  char cmd[cmdstr.length()+1];
					  db="dbs\\"+db;
					  char DB[db.length()+1];
	                  strcpy(cmd,cmdstr.c_str());
						strcpy(DB,db.c_str());
	                  DIR* dir=opendir(DB);
	                  if(ENOENT==errno)
					  system(cmd);
			        	}
					  else
					  	__display_error__(INVALIDUSE);
				}
				else{
					cout<<"Specify DB first Ex:   use <Db_name>\n";
				}
	         }
	    }
     	cout<<"Query> ";
		getline(cin,s);
	    s=tolwr(s);

	}
}
