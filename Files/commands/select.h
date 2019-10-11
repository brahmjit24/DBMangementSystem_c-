
vector<string> getHeadings(string db,string file)
{
		FILE *fptr;
    	  string f1=db+"/"+file+".db";
		  char newfile[f1.length()+1];
	      strcpy(newfile,f1.c_str());
		  fptr=fopen(newfile,"r");
		  string colname="";
	    	char ch;
		    ch=fgetc(fptr);
		while(ch!='/')
		{
			colname=colname+tostr(ch);
			ch=fgetc(fptr);
		}
		
		fclose(fptr);
		colname=removeSpaceToOne(colname);
		colname=makeQuery(colname);
		colname=removeSpaceToOne(colname);
		colname=Stringify(colname);
		vector<string> words;
		processWords(words,colname);
		return words;
}

int exists(string s,vector<string> words,int whereIndex)
{
	int size=words.size();
	int index=-1;
	for(int i=0;i<size;i++)
	{
		if(s==words[i])
		index=i;
	}
	if( index>0 && index!=whereIndex+2)
	return -2;
	else
	return index;
}

int isPresent(string word,string db,string file)
{
        vector<string> words=getHeadings(db,file);
		int size=words.size();
		for(int i=0;i<size;i++)
		{
			if(words[i]==word)
			return i;
		}
		return -1;
}

vector< vector<string> > getdata(vector<string> words,int colIndex,string db)
{
			vector< vector<string> > data;
	      FILE *fptr;
    	  string file=db+"/"+words[colIndex]+".db";
		  char newfile[file.length()+1];
	      strcpy(newfile,file.c_str());
		  fptr=fopen(newfile,"r");
		  string s="";
		  string colname="";
		  char ch;
	      ch=fgetc(fptr);
		  while(ch!='/')
	    	{
			colname=colname+tostr(ch);
			ch=fgetc(fptr);
		   }
		  	colname=Stringify(colname);
		   vector<string> wordsHead;
	    	processWords(wordsHead,colname);
	    	data.push_back(wordsHead);
	    	ch=fgetc(fptr);
	    	while(ch!='\n')
	    	{
//			colname=colname+tostr(ch);
			ch=fgetc(fptr);
		   }
		   ch=fgetc(fptr);
		   ch=fgetc(fptr);
		while(ch!=EOF)
		{s="";
		while(ch!='\n')
		{
			s=s+tostr(ch);
			ch=fgetc(fptr);
		}
		ch=fgetc(fptr);
		s=Stringify(s);
		vector<string> words;
		processWords(words,s);
		data.push_back(words);
		
	    }
		 fclose(fptr);
		 
		 return data;
}
int flag=-1;
vector<int> colDisplay;
bool checkSelectQuery(vector<string> words,string db)
{	
	
	
	int size=words.size();
	 flag=-1;
	for(int i=1;i<size;i++ )
	if(words[i]=="from")
	{
		flag=i;break;
	}
	if(flag==-1)
	{
		__display_error__(FROMMIS);
    	   return false;
	}
    
    int wordsBetween=0;
    for(int i=1;words[i]!="from";i++)
    {
    	wordsBetween++;
	}
	
	if(wordsBetween +2>=words.size())
	{
		__display_error__(INVALID);
	      return false;
	}
	    string file=db+"/"+words[wordsBetween+2]+".db";
	char searchFile[file.length()+1];
	strcpy(searchFile,file.c_str());
     if(access(searchFile,F_OK)==-1)
	   {
	   	__display_error__(NOTEXIST);
	      return false;
	   }
	   
    if(words.size()>flag+2)
    {
    	int whereIndex=flag+2;
    	int eqlIndex=flag+4;
    	int colIndex=flag+3;
    	int fileIndex=flag+1;
    	if(exists("!",words,whereIndex)>=0)
    	{
    		eqlIndex++;
		}
    	else if(exists("!",words,whereIndex)==-2)
    	{
    		__display_error__(INVALID);
		  return false;
		}
        
    	if(words.size()<flag+5||words.size()>eqlIndex+2)
    	{
    	 __display_error__(INVALID);
		  return false;
		}
    	if(words[flag+2]!="where")
    	{
    		__display_error__(INVALID);
		  return false;
		}
		else if(flag+2==words.size()-1)
		{
				__display_error__(INCOMPLETE);
		  return false;
		}
		else if(isPresent(words[colIndex],db,words[fileIndex])==-1)
		{	__display_error__(INVALID);
		  return false;
		  }
		else if(words[eqlIndex]!="=")
		{
				__display_error__(MISEQL);
			return false;
		}
		else{
			//other stuff
		}
	}
	else
	{
		if(flag!=words.size()-2)
		{
				__display_error__(INVALID);
		  return false;
		}
	}
	if(wordsBetween==0)
	{
		__display_error__(MISSINGCOL);
    	   return false;
	}
	else if(wordsBetween>=1)
	{
	  for(int i=1;i<=wordsBetween ;i++)
	  {
	  	if(wordsBetween==1&&words[1]=="*")
	  	return true;
	  	if(i%2==1)
			{
				if(words[i]==","||words[i]=="("||words[i]==")")
				{ __display_error__(INVALID);return false;}
				else if(!(words[i][0]>=97&&words[i][0]<=122))
				 {__display_error__(COLNAME);return false;}
				 else{
				 	int present=(isPresent(words[i],db,words[wordsBetween+2]));
				 	if(present==-1)
				 	{
				 		__display_error__(INVALIDCOL);
						 return false;
					 }
					 else{
					 	colDisplay.push_back(present);
					 }
				 }
			}
			else{
				if(!(words[i]==","))
				{__display_error__(INVALID);
				return false;
			    }
			}
		  }	
	}
	else {
		__display_error__(INVALID);
    	   return false;
	}
	

	return true;
}


void modifiedPrint(vector<int> cols,vector< vector<string> > data,vector<int> rows)
{
	int size=data.size();
	int sizeCol=cols.size();
	for(int i=0;i<data[0].size();i++)
		{
			data[0][i]=toupr(data[0][i]);
		}
		 for(int i=0;i<rows.size();i++)
		 {
		 	
		 	for(int j=0;j<sizeCol;j++)
		 	{
		 		
		 		cout<<data[rows[i]][cols[j]]<<"  ";
			 }
			 cout<<endl;
		 }
		 
}


vector<int> generateCondition(vector<string> words,int where,vector< vector<string> > data)
{
	int colsearch=where+1;
	int index;
	vector<string> head=data[0];
	for(int i=0;i<data[0].size();i++)
	{
		if(data[0][i]==words[colsearch])
		{
			index=i;
			break;
		}
	}
	vector<int> rows;
	rows.push_back(0);
	
	if(words[where+2]=="!")
	{
		for(int i=1;i<data.size();i++)
     	{
		if(data[i][index]!=words[where+4])
	    	{
			rows.push_back(i);
	    	}
    	}
	}
	else{
	for(int i=1;i<data.size();i++)
	{
		if(data[i][index]==words[where+3])
		{
			rows.push_back(i);
		}
	}
}
	return rows;
	
}

void processSelectQuery(vector<string> words,string db)
{
	
	bool result = checkSelectQuery(words,db);
	if(!result)
     return;
	else{
		vector< vector<string> > data=getdata(words,flag+1,db);
		
		vector<int> rows;
		if(words.size()>flag+2)
		{
			rows=generateCondition(words,flag+2,data);
		}
		else{
			for(int i=0;i<data.size();i++)
			{
				rows.push_back(i);
			}
		}
	   if(words[1]=="*")
	   {  
           colDisplay.clear();
           if(rows.size()==1)
            {
        	__display_error__(NODATAFOUND);
	    	}
	    	else{
           for(int i=0;i<data[0].size();i++)
			{
				colDisplay.push_back(i);
			}
		   modifiedPrint(colDisplay,data,rows);
        	}
		    colDisplay.clear();
		   }
       else{
            if(rows.size()==1)
            {
        	__display_error__(NODATAFOUND);
	    	}
     		else{
        	modifiedPrint(colDisplay,data,rows);
            }
            
            
       	    colDisplay.clear();
       	
	   }

	}	
	
	
}


