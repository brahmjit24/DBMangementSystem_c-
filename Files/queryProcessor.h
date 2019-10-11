#include "commands/create.h"
#include "commands/insert.h"
#include "commands/print.h"
#include "commands/load.h"
#include "commands/select.h"
void process(vector<string> words,string db)
{
	switch(hash(words[0]))
	{
		case create :{
			            processCreateQuery(words,db);     
		             	break;
		                }
		case insert :{
						processInsertQuery(words,db);
		             	break;
		                }
       	case select :{
       					processSelectQuery(words,db);
		             	break;
		                }
		case print :{
						processPrintQuery(words,db);   
		             	break;
		                }
		case load :{
						processLoadQuery(words,db);   
		             	break;
		                }
		default:{
			
		  cout<<"  101 :: Invalid Command\n\n";
		}
	}
}


