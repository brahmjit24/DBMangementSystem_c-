
vector< vector<string> > data;



string Stringify(string s)
{
	int i=0;
	int len=s.length();
	string emp=" ";
	while(i<len)
    {
		if(s[i]=='|'||s[i]==',')
	     {
		 s.replace(i,1,emp);
		 
	     }
	     i++;
    }
	return s;
}






bool checkPrintQuery(vector<string> words,string db)
{	
	
	if(words.size()!=2&&words.size()!=5)
	    {
	       __display_error__(INVALID);
    	   return false;
        }
    string file=db+"/"+words[1]+".db";
	char searchFile[file.length()+1];
	strcpy(searchFile,file.c_str());
     if(access(searchFile,F_OK)==-1)
	   {
	   	__display_error__(NOTEXIST);
	      return false;
	   }
	   
	   if(words.size()==5&&(!(words[2]=="(")||(!(words[3]=="sorted")&&!(words[3]=="revsorted"))||!(words[4]==")")))
	   {
	   	__display_error__(INVALID);
	   	return false;
	   }
	   
	return true;
}






void printData(vector< vector<string> > data)
{
	int size=data.size();
		 for(int i=0;i<size;i++)
		 {
		 	for(int j=0;j<data[i].size();j++)
		 	{
		 		cout<<data[i][j]<<"  ";
			 }
			 cout<<endl;
		 }
		 
}

void printSorted(vector< vector<string> > data)
{
	sort(data.begin(),data.end());
	printData(data);
}
void printRevSorted(vector< vector<string> > data)
{
	sort(data.begin(),data.end());
	int size=data.size();
		 for(int i=size-1;i>=0;i--)
		 {
		 	for(int j=0;j<data[i].size();j++)
		 	{
		 		cout<<data[i][j]<<"  ";
			 }
			 cout<<endl;
		 }
}



void printHeadings(string colnames)
{
	colnames=Stringify(colnames);
	vector<string> words;
	processWords(words,colnames);
	int size=words.size();
	for(int i=0;i<size;i++)
	{
		cout<<toupr(words[i])<<"  ";
	}
	cout<<"\n";		 
}






void processPrintQuery(vector<string> words,string db)
{
	
	bool result = checkPrintQuery(words,db);
	if(!result)
     return;
	else{
		  
          
          FILE *fptr;
    	  string file=db+"/"+words[1]+".db";
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
		
		 if(words.size()==2)
		 {cout<<" Query Processed :: Table "<<toupr(words[1])<<" :- "<<endl<<endl;
		  printHeadings(colname);
		 printData(data);
	     }
		 else
		 {cout<<" Query Processed :: Sorted Table "<<toupr(words[1])<<" :- "<<endl<<endl;
		  printHeadings(colname);
		  if(words[3]=="sorted")
		 printSorted(data);
		 else if(words[3]=="revsorted")
		 printRevSorted(data);
		 }
		 data.clear();

	}	
	
	
}


