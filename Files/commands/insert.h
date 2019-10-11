





int countCols(char *file)
{
		FILE *fptr;
		fptr=fopen(file,"r");
		string s="";
		char ch;
		ch=fgetc(fptr);
		while(ch!='/')
		{
			s=s+tostr(ch);
			ch=fgetc(fptr);
		}
		fclose(fptr);
		s=removeSpaceToOne(s);
		s=makeQuery(s);
		vector<string> words;
		processWords(words,s);
		return words.size();
}











bool checkInsertQuery(vector<string> words,string db)
{
	
	

	
	if(words.size()<5)
	    {
	       __display_error__(SIZE);
    	   return false;
        }
        
        
        	string file=db+"/"+words[2]+".db";
	char searchFile[file.length()+1];
	strcpy(searchFile,file.c_str());
	
	
	 if(!(words[1]=="into"))
	   {
	   	   __display_error__(TABLEKEYWORD);
	       return false;
	   }
	else if(!(words[3]=="values"))
	   {
	   	  __display_error__(MISSINGWORD);
	      return false;
       }
    else if(!(words[4]=="("))
	   {
	   	  __display_error__(BRACKETS);
	      return false;
       }
	else if(words[5]==")")
	   {
	   	   __display_error__(NOCOLUMNS);
	      return false;
       }
	else if(!(words[words.size()-1]==")"))
	   {
	   	   __display_error__(BRACKETS);
	      return false;
	   }
	else if(access(searchFile,F_OK)==-1)
	   {
	   	__display_error__(NOTEXIST);
	      return false;
	   }
	else{
		int count=0;
		int inCount=countCols(searchFile);
		for(int i=5;i<words.size()-1;i++)
		{
			count++;
			if(i%2==1)
			{
				if(words[i]==","||words[i]=="("||words[i]==")")
				{ __display_error__(BRACKETS);return false;}
			}
			else{
				if(!(words[i]==","))
				{__display_error__(INVALID);
				return false;
			    }
			}
		}
		
		if(count!=inCount)
		{
			__display_error__(MISSINGCOL);
				return false;
		}
	}
	
	return true;
}









void processInsertQuery(vector<string> words,string db)
{
	
	bool result = checkInsertQuery(words,db);
	if(!result)
     return;
	else
	{
		FILE *fptr;
		string file=db+"/"+words[2]+".db";
		char newfile[file.length()+1];
	    strcpy(newfile,file.c_str());
		fptr=fopen(newfile,"a");
		fprintf(fptr,"|");
		for(int i=5;i<words.size()-1;i++)
		{
			if(i%2==1)
			{ 
			  string temp=words[i];
			  char wrd[temp.length()+1];
	          strcpy(wrd,temp.c_str());
			  fprintf(fptr,"%s",wrd);
		    }
		    else
		    {
		    	fprintf(fptr,"|");
			}
		}
		fprintf(fptr,"|\n");
		fclose(fptr);

		
		cout<<" Query Processed ::  1 Row Inserted "<<endl<<endl;
	}	
}


