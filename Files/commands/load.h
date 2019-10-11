

bool checkLoadQuery(vector<string> words,string db)
{	
    
    if(words.size()!=4)
	    {
	       __display_error__(SIZE);
	       __display_error__(INVALID);
    	   return false;
        }
	
	string file=db+"/"+words[1]+".db";
	char searchFile[file.length()+1];
	strcpy(searchFile,file.c_str());
	 file=db+"/"+words[3]+".db";
	char searchFile2[file.length()+1];
	strcpy(searchFile2,file.c_str());
	
	
	 if(!(words[2]=="as"))
	   {
	   	   __display_error__(ASKEYWORD);
	       return false;
	   }
	else if(access(searchFile,F_OK)==-1)
	   {
	   	__display_error__(NOTEXIST);
	      return false;
	   }
	else if(access(searchFile2,F_OK)!=-1)
	   {
	   	cout<<searchFile2;
	   	__display_error__(ALREADYEXIST);
	      return false;
	   }
	return true;
}





void processLoadQuery(vector<string> words,string db)
{
	
	bool result = checkLoadQuery(words,db);
	if(!result)
     return;
	else{
	
	    string f1=db+"/"+words[1]+".db";
	    char file[f1.length()+1];
	    strcpy(file,f1.c_str());
		string f2=db+"/"+words[3]+".db";
	    char file2[f2.length()+1];
	    strcpy(file2,f2.c_str());
        FILE *fptr,*fptr2;
		fptr=fopen(file,"r");
		fptr2=fopen(file2,"w");
		string s="";
		char ch;
		ch=fgetc(fptr);
		while(ch!=EOF)
		{
			fprintf(fptr2,"%c",ch);
			ch=fgetc(fptr);
		}
		fclose(fptr2);
		fclose(fptr);
		cout<<"Query Processed :: Data Loaded from "<<toupr(words[1])<<" to "<<toupr(words[3])<<endl<<endl;
	}	
	
	
}


