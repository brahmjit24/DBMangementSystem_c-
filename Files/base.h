 enum commands{
create,
insert,
select,
print,
load
};

 enum ERRS{
INVALID,
SIZE,
TABLEKEYWORD,
BRACKETS,
ALREADYEXIST,
NOCOLUMNS,
COLNAME,
NOTEXIST,
MISSINGWORD,
MISSINGCOL,
ASKEYWORD,
INVALIDUSE,
FROMMIS,
INVALIDCOL,
INCOMPLETE,
MISEQL,
NODATAFOUND
};


int hash(string s)
{
	if(s=="create")
	return create;
	if(s=="insert")
	return insert;
	if(s=="select")
	return select;
	if(s=="print")
	return print;
	if(s=="load")
	return load;
	
	
	return -1;
}


string tolwr(string s)
{
	transform(s.begin(),s.end(),s.begin(),::tolower);
	return s;
}


string toupr(string s)
{
	transform(s.begin(),s.end(),s.begin(),::toupper);
	return s;
}

string tostr(char c)
{
   string x="";
   
   return c+x;	
}

string removeSpaceToOne(string s)
{
	s=" "+s+" ";
	int len=s.length();
	int i=1;
	while(i!=len)
	{
		if((s[i-1]==' '||s[i-1]=='~')&&s[i]==' ')
		{
			s[i]='~';
		}
		
		i++;
	}
	i=0;
	string emp="";
	while(i<len)
    {
		if(s[i]=='~')
	     {
		 s.replace(i,1,emp);
		 i--;
	     }
	     i++;
    }
	return s;
}


string makeQuery(string s)
{
	int i=0;
	int len=s.length();
	while(i<len)
    {
		if(s[i]=='('||s[i]==')'||s[i]==','||s[i]=='='||s[i]=='!')
	     {
            char c=s[i];
	     	string insert=" "+tostr(c)+" ";
		    s.replace(i,1,insert);
	     	 if(i+2<len)
	        	 {
				 i=i+2;
				 len+=2;
			}
	     }
	     i++;
    }
	return s;
}

void __display_error__(int error)
{
	switch(error)
	{
		default:
		case INVALID:     cout<<"  101 :: Invalid Command\n\n";
		                   break;
        case SIZE:        cout<<"  102 :: Query Size Inappropriate \n\n";
		                   break;
        case TABLEKEYWORD:cout<<"  103 :: Table Keyword not properly placed\n\n";
		                   break;
        case BRACKETS:    cout<<"  104 :: Brackets Inappropriate \n\n";
		                   break;
        case ALREADYEXIST:cout<<"  105 :: Table Already Exists \n\n";
		                   break;
        case NOCOLUMNS:   cout<<"  106 :: No Columns Specified  \n\n";
		                   break;
		case COLNAME:   cout<<"  107 :: Columns NAME invalid  \n\n";
		                   break;
		case NOTEXIST:   cout<<"  108 :: Table doesnot exists  \n\n";
		                   break;
		case MISSINGWORD:   cout<<"  109 :: Keyword Missing OR Misplaced  \n\n";
		                   break;
		case MISSINGCOL:   cout<<"  110 ::  Missing column  \n\n";
		                   break;
		case ASKEYWORD:   cout<<"  111 ::  Missing / Missedplaced AS Keyword  \n\n";
		                   break;
		case INVALIDUSE:   cout<<"  112 ::  Invalid USE Command  \n\n";
		                   break;
		case FROMMIS:   cout<<"  113 ::  Missing FROM keyword  \n\n";
		                   break;
		case INVALIDCOL:   cout<<"  114 ::  Invalid COLUMN name  \n\n";
		                   break;
		case INCOMPLETE:   cout<<"  115 ::  Incomplete Command  \n\n";
		                   break;	
		case MISEQL:   cout<<"  116 ::  Missing / Missedplaced =  \n\n";
		                   break;	
		case NODATAFOUND :   cout<<"  117 ::  No Data Found  \n\n";
		                   break;					   	                   
   }
	
}



void processWords(vector<string> &words,string s)
{
	int len=s.length();
	int strt=0;
	int i=0;
	while(i<len)
	{
		if(s[i]==' ')
		{
			string temp=s.substr(strt,i-strt);
			strt=i+1;
			if(temp!=" "&&temp!="")
			{
				words.push_back(temp);
			}
		}
		
		
		
		i++;
	}
}

