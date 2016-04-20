#include "friso_API.h"
#include "friso.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define __LENGTH__ 15
#define __INPUT_LENGTH__ 20480
#define ___EXIT_INFO___                    \
    println("Thanks for trying friso.");        \
break;

#define ___ABOUT___                    \
    println("+-----------------------------------------------------------+");    \
    println("| friso - a chinese word segmentation writen by c.          |");    \
    println("| bug report email - chenxin619315@gmail.com.               |");    \
    println("| or: visit http://code.google.com/p/friso.                 |");    \
    println("|     java edition for http://code.google.com/p/jcseg       |");    \
    println("| type 'quit' to exit the program.                          |");    \
    println("+-----------------------------------------------------------+");

	
const char* CONF_FILE = "../friso.ini";
const char* SRC_FILE = "./dict_test.txt";
const char* DST_FILE = "./rst.txt";
	
/*
**@param:[out]文件buffer，输出。
**@param:lpszFilename:文件名
**@brief:读取文件，写入buffer
**@return:1,成功；其他代表失败。
**
*/
int ReadFile(char **FileStr,const char* lpszFilename)
{
    if(!lpszFilename||(strlen(lpszFilename)==0))
	{
		printf("file %s is not exist!\n", lpszFilename);
        exit(-1);
	} 
	
	//sFileText = "";

	FILE* fp = fopen(lpszFilename,"rb");

	if(!fp){
		printf("file open error!\n", lpszFilename);
		/*int err(0); 
		errno_t ret = _get_errno(&err); 
		cout << "err = " << ret << endl;
		*/
	
		char buffer[256] = {0};
		char * errorMessage = strerror_r(errno, (char*)buffer, 256); // get string message from errno
		printf("errorMsg = %s\n", errorMessage);
		exit(-1);
	}//if 

	fseek(fp,0L,SEEK_END);
	long lSize = ftell(fp);
	printf("%s size = %d\n", lpszFilename, lSize);
	fseek(fp,0L,SEEK_SET);

	if(lSize>0){
	char* lpszFileText = (char*)calloc(lSize+1,sizeof(char));
	if(lpszFilename==NULL){
		fclose(fp);
		printf("file mapping err!\n");
		exit(-1);
	} 

	fread(lpszFileText,sizeof(char),lSize,fp);
	*FileStr=lpszFileText;
	} //if 

	fclose(fp);
	printf("end of ReadFile() fileName: %s\n", lpszFilename);

    return 1;
}//*/

/*
**@param:pszRst:待写入文件；
**@param:nRstLen:待写入长度。
**@brief:分词结果写入文件
**@return:空
**
*/
void writeFile(const char* pszRst, int nRstLen)
{
	int fd = open(DST_FILE, O_WRONLY|O_CREAT);
	write(fd, pszRst, nRstLen);
	close(fd);
}

/*
**@param:pszIniPath 配置ini文件路径
**@brief:分词接口
**@return:无
**
*/
void word_divide(char* pszIniPath)
{
	clock_t s_time, e_time;
    char line[__INPUT_LENGTH__] = {0};
    int i = 0;
    fstring __path__ = NULL, mode = NULL;

    friso_t friso;
    friso_config_t config;
    friso_task_t task;

    s_time = clock();

    //initialize
    friso = friso_new();
    config = friso_new_config();
    if ( friso_init_from_ifile(friso, config, pszIniPath) != 1 ) {
        printf("fail to initialize friso and config.");
        friso_free_config(config);
		friso_free(friso);
		exit(-1);
    }

    switch ( config->mode ) 
    {
        case __FRISO_SIMPLE_MODE__:
            mode = "Simple";
            break;
        case __FRISO_COMPLEX_MODE__:
            mode = "Complex";
            break;
        case __FRISO_DETECT_MODE__:
            mode = "Detect";
            break;
    }

    e_time = clock();

    printf("Initialized in %fsec\n", (double) ( e_time - s_time ) / CLOCKS_PER_SEC );
    printf("Mode: %s\n", mode);
    printf("+-Version: %s (%s)\n", friso_version(), friso->charset == FRISO_UTF8 ? "UTF-8" : "GBK" );
    ___ABOUT___;

    //set the task.
    task = friso_new_task();
	
	//read file
	char *source = NULL;
	(void)ReadFile(&source, SRC_FILE);
	printf("after read: source = %s\n", source);
	//
	friso_set_text( task, source );
    println("The words divided result is:");
	s_time = clock();
	int iLen = (1 + strlen(source))*sizeof(char);
	printf("strlen(source) = %d\n", iLen);
	char* pszDestBuf = (char*)malloc(2 * iLen);
	memset(pszDestBuf, 0, 2 * iLen);
	while ((config->next_token(friso, config, task )) != NULL ) 
	{
		strcat(pszDestBuf, task->token->word);
		strcat(pszDestBuf, "\n");
		printf("%s \n", task->token->word );
	}
	
	e_time = clock();
	printf("\nDone, cost < %fsec\n", ( (double)(e_time - s_time) ) / CLOCKS_PER_SEC );
		
	//write to result file
	printf("strlen(pszDestBuf) = %d\n", 1 + strlen(pszDestBuf));
	writeFile(pszDestBuf, 1 + strlen(pszDestBuf));
	
	if (NULL != pszDestBuf)
	{
		free(pszDestBuf);
		pszDestBuf = NULL;
	}
	
    friso_free_task( task );
    //error block.
    friso_free_config(config);
    friso_free(friso);
	
	
}

int main()
{
	(void)word_divide(CONF_FILE);
	return 0;
}
