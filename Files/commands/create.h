
bool checkCreateQuery(vector<string> words,string db)
{
	
	
	string file=db+"/"+words[2]+".db";
	char searchFile[file.length()+1];
	strcpy(searchFile,file.c_str());
	
	
	if(words.size()<=4)
	    {
	       __display_error__(SIZE);
    	   return false;
        }
	else if(!(words[1]=="table"))
	   {
	   	   __display_error__(TABLEKEYWORD);
	       return false;
	   }
	else if(!(words[3]=="("))
	   {
	   	  __display_error__(BRACKETS);
	      return false;
       }
	else if(words[4]==")")
	   {
	   	   __display_error__(NOCOLUMNS);
	      return false;
       }
	else if(!(words[words.size()-1]==")"))
	   {
	   	   __display_error__(BRACKETS);
	      return false;
	   }
	else if(access(searchFile,F_OK)!=-1)
	   {
	   	__display_error__(ALREADYEXIST);
	      return false;
	   }
	else{
		for(int i=4;i<words.size()-1;i++)
		{
			if(i%2==0)
			{
				if(words[i]==","||words[i]=="("||words[i]==")")
				{ __display_error__(BRACKETS);return false;}
				else if(!(words[i][0]>=97&&words[i][0]<=122))
				 {__display_error__(COLNAME);return false;}
			}
			else{
				if(!(words[i]==","))
				{__display_error__(INVALID);
				return false;
			    }
			}
			
			
		}
	}
	
	return true;
}









void processCreateQuery(vector<string> words,string db)
{
	
	bool result = checkCreateQuery(words,db);
	if(!result)
     return;
	else{
		FILE *fptr;
		string file=db+"/"+words[2]+".db";
		char newfile[file.length()+1];
	    strcpy(newfile,file.c_str());
		fptr=fopen(newfile,"w");
		for(int i=4;i<words.size()-1;i++)
		{
			string temp=words[i];
			char wrd[temp.length()+1];
	        strcpy(wrd,temp.c_str());
			fprintf(fptr,"%s",wrd);
		}
		fprintf(fptr,"    / {These are Column names seperated by , }      \n\n");
		fclose(fptr);
		
		
		cout<<" Query Processed :: Table "<<toupr(words[2])<<" created"<<endl<<endl;
	}	
	
	
}


