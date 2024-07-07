#include "ui.h"

void sgm_class_list(sscErrorHandle hError, mySession *session,ssdb_Connection_Handle connection,
        ssdb_Error_Handle error_handle,CMDPAIR *cmdp)
{
        ssdb_Request_Handle req_handle;
        int number_of_records,rec_sequence,common_int;
        const char **vector;
        int key;
	char sys_id[32];
        if(!get_variable(hError,cmdp,CHARTYPE,"sys_id",sys_id,&common_int,802))
                return;
        if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
        "select distinct class_id,class_desc from event_class where sys_id = '%s' order by class_desc",sys_id)))
        {
                sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                return;
        }

	if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
		if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
        	"select hostname from system where sys_id = '%s'",sys_id)))
		{
			sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
			return;
		}
		vector = ssdbGetRow(error_handle,req_handle);
		if(vector)
		{
			FormatedBody("There are no events in the database for system <b>%s</b>.",vector[0]);
			ssdbFreeRequest(error_handle,req_handle);
		}
		ssdbFreeRequest(error_handle,req_handle);
                return ;
        }
        else
        {
                Body("<select name=ev_class size=5>\n");
                for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
                {
                        vector = ssdbGetRow(error_handle,req_handle);
			if(vector)
				FormatedBody("<option value = %d > %s",atoi(vector[0]),vector[1]);
                }
                Body("</select>\n");
		Body("<p><input type=\"submit\" value=\"   Accept   \">\n");
        }
        ssdbFreeRequest(error_handle,req_handle);
}

void sgm_action_list(sscErrorHandle hError, mySession *session,ssdb_Connection_Handle connection,
        ssdb_Error_Handle error_handle,CMDPAIR *cmdp)
{
        ssdb_Request_Handle req_handle;
        int number_of_records,rec_sequence;
        const char **vector;
        int action_id,key,multiselect;
	char common_string[2];
	if(!get_variable(hError,cmdp,INTTYPE,"multiselect",common_string,&multiselect,800))
                return;

        if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
        "select action_id,action_desc from event_action where private = 0 order by action_desc")))
        {
                sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                return;
        }

	if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
                Body("<b>There are no actions in the database.</b>\n");
                ssdbFreeRequest(error_handle,req_handle);
                return ;
        }
        else
        {
                if (multiselect)
                         Body("<select name=actionid multiple size=5>\n");
                else
                        Body("<select name=actionid size=5>\n");
                for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
                {
                        vector = ssdbGetRow(error_handle,req_handle);
			if(vector)
				FormatedBody("<option value = %d > %s",atoi(vector[0]),vector[1]);
                }
                Body("</select>\n");
        }

        ssdbFreeRequest(error_handle,req_handle);
}

void sgm_type_list(sscErrorHandle hError, mySession *session,ssdb_Connection_Handle connection,
        ssdb_Error_Handle error_handle,CMDPAIR *cmdp)
{
        ssdb_Request_Handle req_handle;
        int number_of_records,rec_sequence;
        const char **vector;
        int action_id,key,multiselect,selectvar,classidtype,common_int;
	char class_desc[80],sys_id[32],common_string[2];
        classidtype = 0;

	if(!get_variable(hError,cmdp,INTTYPE,"multiselect",common_string,&multiselect,801))
                return;
	if(!get_variable(hError,cmdp,CHARTYPE,"sys_id",sys_id,&common_int,802))
                return;
	
        if ((key = sscFindPairByKey(cmdp,0,"ev_class")) < 0)
        {
                if ((key = sscFindPairByKey(cmdp,0,"actionid")) < 0)
                {
                        sscError(hError,"Invalid Request Parameter1\n");
                        return;
                }
                if (sscanf(cmdp[key].value,"%d",&selectvar) != 1)
                {
                        sscError(hError,"Invalid Request Parameter2\n");
                        return;
                }
        }
        else
        {
                if (sscanf(cmdp[key].value,"%d",&selectvar) != 1)
                {
                        sscError(hError,"Invalid Request Parameter\n");
                        return;
                }
                classidtype = 1;
        }

	if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
	"select class_desc from event_class where class_id = %d and sys_id='%s'",selectvar,sys_id)))
	{
		sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
		return;
	}

	if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
	{
		Body("<b>The event class description could not be read</b>\n");
		ssdbFreeRequest(error_handle,req_handle);
                return ;
        }
	vector = ssdbGetRow(error_handle,req_handle);
	if(vector)
		strcpy(class_desc,vector[0]);
	else
		strcpy(class_desc,"Unknown");
	ssdbFreeRequest(error_handle,req_handle);	
        if (classidtype)
        {
                if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
                "select type_id,type_desc from event_type where class_id = %d and sys_id='%s' order by type_desc",selectvar,sys_id)))
                {
                        sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                        return;
                }
        }
        else
        {
                if(!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
                        "select DISTINCT event_class.class_id, event_class.class_desc,"
                        "event_type.type_id, event_type.type_desc "
                        "from event_class,event_type,event_actionref "
                        "where event_actionref.action_id = %d "
                        "and event_type.type_id = event_actionref.type_id "
                        "and event_class.class_id = event_type.class_id "
			"and event_class.sys_id = '%s' "
                        "order by event_class.class_id, event_type.type_id",selectvar,sys_id)))
                {
                        sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                        return;
                }

        }

	if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
                Body("<b>There are no events in the database.</b>\n");
                ssdbFreeRequest(error_handle,req_handle);
                return ;
        }
        else
        {
		FormatedBody("Choose an event from class <b>%s</b>:<p>",class_desc);
                if (classidtype)
                {
                if (multiselect)
                        Body("<select name=event_type multiple size=10>\n");
                else
                        Body("<select name=event_type size=10>\n");
                for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
                {
                        vector = ssdbGetRow(error_handle,req_handle);
			if(vector)
				FormatedBody("<option value = %d > %s",atoi(vector[0]),vector[1]);
                }
                Body("</select>\n");
                }
                else
                {
                        if (multiselect)
                                Body("<select name=event_type multiple size=10>\n");
                        else
                                Body("<select name=event_type size=10>\n");
                        for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
                        {
                                vector = ssdbGetRow(error_handle,req_handle);
				if(vector)
					FormatedBody("<option value = %d > %s&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%s",atoi(vector[2]),vector[1],vector[3]);
                        }
                Body("</select>\n");
                }
        ssdbFreeRequest(error_handle,req_handle);
	Body("<p> <input type = \"submit\" value = \"   Accept   \">\n");
        }
}


int read_java_scritps(const char *screen_name,const char *screen_end)
{
        FILE *fp;
        char buffer[256];
        fp = fopen("/var/esp/ssc/javascripts","r");
        if ( fp == NULL )
             return 0;
             
        memset(buffer,0,256);
        while (strcasecmp(buffer,screen_name) && !feof(fp))
        {
                fgets(buffer,256,fp);
                buffer[strlen(buffer)-1] = '\0';
        }
        if (feof(fp))
                return 0;
        fgets(buffer,256,fp);
        buffer[strlen(buffer)-1] = '\0';
        while (strcasecmp(buffer,screen_end))
        {
                FormatedBody("%s\n",buffer);
                fgets(buffer,256,fp);
                buffer[strlen(buffer)-1] = '\0';
        }
        fclose(fp);
        return 1;
}

int getnumrecords (sscErrorHandle hError,ssdb_Error_Handle error_handle,ssdb_Request_Handle req_handle)
{
        int number_of_records;

        number_of_records = ssdbGetNumRecords(error_handle,req_handle);

        if(ssdbGetLastErrorCode(error_handle) != SSDBERR_SUCCESS)
        {
                sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                return 0;
        }
        return number_of_records;
}

void create_help(sscErrorHandle hError,char *helpfile)
{
        int fd;
        char buffer[1024];
        memset(buffer,0,1024);
	unlink("/var/esp/ssc/help.html");
        if ((fd = open("/var/esp/ssc/help.html",O_CREAT | O_RDWR,0777)) < 0)
		return;
        sprintf(buffer,"<html> <head> <title>SGI Embedded Support Partner - Help</title></head>\n"
                "<frameset cols=\"170,*\" border=0>\n"
                "<frame src=\"/help_navigator.html\" name=\"help_index\" scrolling=\"auto\"\n"
                "marginheight=8 marginwidth=8 border=0 frameborder=0 framespacing=0>\n"
                "<frame src=\"/help_contents.html#%s\" name=\"help_main\"\n"
                "scrolling=\"auto\" marginheight=8 marginwidth=8 border=0 frameborder=0 framespacing=0>\n"
                "<noframes>\n"
                "<body bgcolor=\"#FFFFFF\">Your browser does not support frames. "
                "Please install a browser that supports frames.\n"
                "</body>\n"
                "</noframes>\n"
                "</frameset> </html>\n",helpfile);
        write(fd,buffer,strlen(buffer));
        close(fd);
}

int get_variable(sscErrorHandle hError,CMDPAIR *cmdp,int type, char *varname,char *string,int *intval,int errornum)
{
	int key;


	if ((key = sscFindPairByKey(cmdp,0,varname)) < 0)
	{
		Body("<HTML> <HEAD> <TITLE>SGI Embedded Support Partner - ver.1.0</TITLE> </HEAD>\n");
		Body("<body bgcolor=\"#ffffcc\">\n");
		TableBegin("border=0 cellpadding=0 cellspacing=0 width=100%");
		RowBegin("");
			CellBegin("bgcolor=\"#cccc99\" width=15");
				Body("&nbsp;&nbsp;&nbsp;&nbsp;\n");
			CellEnd();
			CellBegin("bgcolor=\"#cccc99\"");
				Body("<B>SERVER ERROR</B>\n");
			CellEnd();
		RowEnd();
		RowBegin("");
			CellBegin("colspan=2");
				Body("&nbsp;<p>&nbsp;\n");
			CellEnd();
		RowEnd();
		RowBegin("");
			CellBegin("");
				Body("&nbsp;\n");
			CellEnd();

			CellBegin("");
			FormatedBody("System group manager plugin server error. Error #: %d",errornum);
			CellEnd();
			RowEnd();
		TableEnd();
		Body("</body></html>\n");
		return 0;
	}
	if(type)
	{
		if (sscanf(cmdp[key].value,"%d",intval) != 1)
		{
			Body("<HTML> <HEAD> <TITLE>SGI Embedded Support Partner - ver.1.0</TITLE> </HEAD>\n");
			Body("<body bgcolor=\"#ffffcc\">\n");
			TableBegin("border=0 cellpadding=0 cellspacing=0 width=100%");
			RowBegin("");
				CellBegin("bgcolor=\"#cccc99\" width=15");
					Body("&nbsp;&nbsp;&nbsp;&nbsp;\n");
				CellEnd();
				CellBegin("bgcolor=\"#cccc99\"");
					Body("<B>SERVER ERROR</B>\n");
				CellEnd();
			RowEnd();
			RowBegin("");
				CellBegin("colspan=2");
					Body("&nbsp;<p>&nbsp;\n");
				CellEnd();
			RowEnd();
			RowBegin("");
				CellBegin("");
					Body("&nbsp;\n");
				CellEnd();

				CellBegin("");
					FormatedBody("System group manager plugin server error. Error #: %d",errornum);
					CellEnd();
					RowEnd();
			TableEnd();
			Body("</body></html>\n");
			return 0;
		}
	}
	else
	{
		if (cmdp[key].value && cmdp[key].value[0])
			strcpy(string,cmdp[key].value);
		else
		{
			Body("<HTML> <HEAD> <TITLE>SGI Embedded Support Partner - ver.1.0</TITLE> </HEAD>\n");
			Body("<body bgcolor=\"#ffffcc\">\n");
			TableBegin("border=0 cellpadding=0 cellspacing=0 width=100%");
			RowBegin("");
				CellBegin("bgcolor=\"#cccc99\" width=15");
					Body("&nbsp;&nbsp;&nbsp;&nbsp;\n");
				CellEnd();
				CellBegin("bgcolor=\"#cccc99\"");
					Body("<B>SERVER ERROR</B>\n");
				CellEnd();
			RowEnd();
			RowBegin("");
				CellBegin("colspan=2");
					Body("&nbsp;<p>&nbsp;\n");
				CellEnd();
			RowEnd();
			RowBegin("");
				CellBegin("");
					Body("&nbsp;\n");
				CellEnd();

				CellBegin("");
					FormatedBody("System group manager plugin server error. Error #: %d",errornum);
					CellEnd();
					RowEnd();
                        TableEnd();
                        Body("</body></html>\n");
			return 0;
		}
	}
	return 1;
}

int get_variable_variable(sscErrorHandle hError,CMDPAIR *cmdp,int type, char *varname,char *string,int *intval,int errornum)
{
        int key;


        if ((key = sscFindPairByKey(cmdp,0,varname)) < 0)
        {
                Body("<HTML> <HEAD> <TITLE>SGI Embedded Support Partner - ver.1.0</TITLE> </HEAD>\n");
                Body("<body bgcolor=\"#ffffcc\">\n");
                TableBegin("border=0 cellpadding=0 cellspacing=0 width=100%");
                RowBegin("");
                        CellBegin("bgcolor=\"#cccc99\" width=15");
                                Body("&nbsp;&nbsp;&nbsp;&nbsp;\n");
                        CellEnd();
                        CellBegin("bgcolor=\"#cccc99\"");
                                Body("<B>SERVER ERROR</B>\n");
                        CellEnd();
                RowEnd();
                RowBegin("");
                        CellBegin("colspan=2");
                                Body("&nbsp;<p>&nbsp;\n");
                        CellEnd();
                RowEnd();
                RowBegin("");
                        CellBegin("");
                                Body("&nbsp;\n");
                        CellEnd();

                        CellBegin("");
                        FormatedBody("System group manager plugin server error. Error #: %d",errornum);
                        CellEnd();
                        RowEnd();
                TableEnd();
                Body("</body></html>\n");
                return 0;
        }
        if(type)
        {
                if (sscanf(cmdp[key].value,"%d",intval) != 1)
                {
                        return -1;
                }
        }
        else
        {
                if (cmdp[key].value && cmdp[key].value[0])
                        strcpy(string,cmdp[key].value);
                else
			strcpy(string,"");
        }
        return 1;
}

void create_custom_list(sscErrorHandle hError, mySession *session,ssdb_Connection_Handle connection,
        ssdb_Error_Handle error_handle,CMDPAIR *cmdp)
{
	ssdb_Request_Handle req_handle;
        int number_of_records,rec_sequence;
        const char **vector;
        int action_id,key,multiselect,selectvar,classidtype,ev_class,common_int;
        char class_desc[80],sys_id[32],common_string[2];

	if(!get_variable(hError,cmdp,INTTYPE,"ev_class",common_string,&ev_class,803))
                return;
        if(!get_variable(hError,cmdp,CHARTYPE,"sys_id",sys_id,&common_int,804))
                return;

	if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
        "select class_desc from event_class where class_id = %d and sys_id = '%s'",ev_class,sys_id)))
        {
                sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                return;
        }

        if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
                Body("<b>The event class description could not be read</b>\n");
                ssdbFreeRequest(error_handle,req_handle);
                return ;
        }

        vector = ssdbGetRow(error_handle,req_handle);

        if(vector)
                strcpy(class_desc,vector[0]);
        else
                strcpy(class_desc,"Unknown");
        ssdbFreeRequest(error_handle,req_handle);

	if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
	"select type_id,type_desc from event_type where class_id = %d and type_id >= 8400000 and sys_id = '%s' order by type_desc",ev_class,sys_id)))
	{
		sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
		return;
	}

        if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
                FormatedBody("There are no custom events in the <b>%s</b> class that can be deleted.",class_desc);
                ssdbFreeRequest(error_handle,req_handle);
                return ;
        }
        else
        {
		FormatedBody("Choose event(s) from class <b>%s</b>:<p>",class_desc);
		Body("<select name=event_type multiselect size=10>\n");
		for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
		{
			vector = ssdbGetRow(error_handle,req_handle);
			if(vector)
				FormatedBody("<option value = %d>%s",atoi(vector[0]),vector[1]);
			ssdbFreeRequest(error_handle,req_handle);
		}
		Body("</select>\n");
		Body("<p><input type=\"SUBMIT\" value=\"   Accept   \">\n");
	}
}

void generate_list_of_systems(sscErrorHandle hError, mySession *session,ssdb_Connection_Handle connection,
        ssdb_Error_Handle error_handle,CMDPAIR *cmdp)
{

	ssdb_Request_Handle req_handle;
        int number_of_records,rec_sequence,common_int,multiselect;
        const char **vector;
        char common_string[2];

	if(!get_variable(hError,cmdp,INTTYPE,"multiselect",common_string,&multiselect,805))
                return;

	if (!(req_handle = ssdbSendRequest(error_handle,connection,SSDB_REQTYPE_SELECT,
            "select sys_id,hostname,sys_serial,sys_type,ip_addr from system where active=1")))
        {
                sscError(hError,"Database API Error: \"%s\"\n\n",ssdbGetLastErrorString(error_handle));
                return;
        }

        if ((number_of_records = getnumrecords(hError,error_handle,req_handle)) == 0)
        {
                Body("<b>The system information could not be read</b>\n");
                ssdbFreeRequest(error_handle,req_handle);
                return ;
        }

        vector = ssdbGetRow(error_handle,req_handle);

        if(vector)
        {
		TableBegin("border=4 cellpadding=6 cellspacing=1");
		RowBegin("valign=top align=center");
			CellBegin("colspan=2");
				Body("<b>System Name</b>\n");
			CellEnd();
			CellBegin("");
				Body("<b>IP Type</b>\n");
                        CellEnd();
                        CellBegin("");
                                Body("<b>System Serial Number</b>\n");
                        CellEnd();
                        CellBegin("");
                                Body("<b>IP Address</b>\n");
                        CellEnd();
		RowEnd();
		if(multiselect)
		{
			RowBegin("valign=top");
				CellBegin("");
					Body("<INPUT TYPE=\"CHECKBOX\" NAME=\"sys_id\" onClick=\"process_allcheck();\" value=0>\n");
				CellEnd();
				CellBegin("colspan=4");
					Body("All systems on a site\n");
				CellEnd();
			RowEnd();
		}
		for (rec_sequence = 0; rec_sequence < number_of_records; rec_sequence++)
                {
			if(vector)
			{
				RowBegin("valign=top");
					CellBegin("");
						if(multiselect)
							FormatedBody("<INPUT TYPE=\"CHECKBOX\" NAME=\"sys_id\" onClick=\"document.SystemAvail.sys_id[0].checked = 0;\" value=\"%s\">",vector[0]);
						if(!multiselect)
							FormatedBody("<INPUT TYPE=\"RADIO\" NAME=\"sys_id\" value=\"%s\">",vector[0]);
					CellEnd();
					CellBegin("");
						FormatedBody("%s",vector[1]);
					CellEnd();
					CellBegin("");
						FormatedBody("IP%d",atoi(vector[3]));
					CellEnd();
					CellBegin("");
						FormatedBody("%s",vector[2]);
					CellEnd();
					CellBegin("");
						FormatedBody("%s",vector[4]);
					CellEnd();
				RowEnd();
			}
			vector = ssdbGetRow(error_handle,req_handle);
		}
		TableEnd();
	}
	else
		Body("There are no systems in the database.\n");
	ssdbFreeRequest(error_handle,req_handle);
}

void makedate (time_t timeval, char *dateout, char *event_time)
{
        struct tm *timeptr;
        time_t timein = timeval;
        timeptr = localtime(&timein);
        strftime(dateout,20,"%m/%d/%Y",timeptr);
        strftime(event_time,20,"%X",timeptr);
}

long maketime(const char *dateval1,int startend)
{
        time_t timevalue;
        struct tm timestruct;
        struct tm *timeptr;
        char dateval[40];
        int i;
        char *p;
        strcpy (dateval,dateval1);
        p = strtok(dateval,"/");
        i = atoi(p);
        i = i - 1;
        timestruct.tm_mon = i;
        p = strtok(NULL,"/");
        timestruct.tm_mday = atoi(p);
        p = strtok(NULL,"/");
        i = atoi(p);
        i = i - 1900;
        timestruct.tm_year = i;
	timestruct.tm_isdst = -1;
        if (!startend)
        {
                timestruct.tm_sec = 00;
                timestruct.tm_min = 00;
                timestruct.tm_hour = 00;
        }
        else
        {
                timestruct.tm_sec = 60;
                timestruct.tm_min = 59;
                timestruct.tm_hour = 23;
        }
        timevalue =  mktime(&timestruct);
        return (timevalue);
}
