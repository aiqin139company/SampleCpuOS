#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

/*
	获取文件映射
*/
char *Get_FILE_MEM(char *FILE_NAME,int mode)
{
	static int fd,flag=0;
	static struct stat t_stat;
	static char *HZ_MEM;
	
	if(mode==0){
		/*打开字库文件*/
		fd = open(FILE_NAME,2);
		if(fd<0){
			printf("打开%s文件失败!\r\n",FILE_NAME);
			return NULL;
		}
		/*获取字库文件信息，这里只是需要文件大小*/
		fstat(fd,&t_stat);
		/*映射字库*/
		FILE_NAME = mmap(NULL,t_stat.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(FILE_NAME == NULL){
			perror("映射文件失败！\r\n");
		}
		flag = 1;
	}else{
		if(flag){
			munmap(FILE_NAME,t_stat.st_size);	/*解除映射*/
			close(fd);							/*关闭文件*/
		}
	}
	
	return FILE_NAME;
}


int main(int argc, char *argv[])
{
	if(argc!=2){
		printf("用法：./test test_file");
		return 0;
	}
	char *str = Get_FILE_MEM(argv[1],0);
	while(*str!=0){
		if((*str&0xff)>0x80){
			if(!(strncmp((char *)str,"包含",4))){
				printf("include ");
			}
			str += 2; 
		}else{
			switch(*str){
				case '\r': printf("\r\n");break;
				case '<' : printf("<");break;
				case '>' : printf(">");break;	
				case '"' : printf("\"");break;			
				case '(' : printf("(");break;
				case ')' : printf(")");break;
				case '#' : printf("#");break;
				case '{' : printf("{");break;
				case '}' : printf("}");break;
				case ';' : printf(";");break;
			}
			str ++;
		} 
	}
	
	return 0;
}