#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

void getPidByName(char* task_name)
{
	    DIR *dir;
	    struct dirent *ptr;
            FILE *fp;
            char filepath[50];//大小随意，能装下cmdline文件的路径即可
	    char cur_task_name[50];//大小随意，能装下要识别的命令行文本即可
	    char buf[BUF_SIZE];
	    dir = opendir("/proc"); //打开路径
	    if (NULL != dir)
	{
	 while ((ptr = readdir(dir)) != NULL) //循环读取路径下的每一个文
	 {       //如果读取到的是"."或者".."则跳过，读取到的不是文件夹名字也
		 if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0)) 								continue;	
		 if (DT_DIR != ptr->d_type) continue;
		 sprintf(filepath, "/proc/%s/status", ptr->d_name);//生成要读取的文件的路径		 
		 fp = fopen(filepath, "r");//打开文件
		 if (NULL != fp)
		 {																 if( fgets(buf, BUF_SIZE-1, fp)== NULL ){											   fclose(fp);continue;}
			 sscanf(buf, "%*s %s", cur_task_name);					
			 if (!strcmp(task_name, cur_task_name))												        printf("PID:  %s\n", ptr->d_name);
		
		fclose(fp);}
	 }							            
	 closedir(dir);//关闭路径			
	}
}

void main(int argc, char** argv)
{
	    char task_name[50];
	    scanf("%s",task_name);
	    getPidByName(task_name);
}
