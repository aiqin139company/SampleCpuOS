#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

/*
	��ȡ�ļ�ӳ��
*/
char *Get_FILE_MEM(char *FILE_NAME,int mode)
{
	static int fd,flag=0;
	static struct stat t_stat;
	static char *HZ_MEM;
	
	if(mode==0){
		/*���ֿ��ļ�*/
		fd = open(FILE_NAME,2);
		if(fd<0){
			printf("��%s�ļ�ʧ��!\r\n",FILE_NAME);
			return NULL;
		}
		/*��ȡ�ֿ��ļ���Ϣ������ֻ����Ҫ�ļ���С*/
		fstat(fd,&t_stat);
		/*ӳ���ֿ�*/
		FILE_NAME = mmap(NULL,t_stat.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(FILE_NAME == NULL){
			perror("ӳ���ļ�ʧ�ܣ�\r\n");
		}
		flag = 1;
	}else{
		if(flag){
			munmap(FILE_NAME,t_stat.st_size);	/*���ӳ��*/
			close(fd);							/*�ر��ļ�*/
		}
	}
	
	return FILE_NAME;
}


int main(int argc, char *argv[])
{
	if(argc!=2){
		printf("�÷���./test test_file");
		return 0;
	}
	char *str = Get_FILE_MEM(argv[1],0);
	while(*str!=0){
		if((*str&0xff)>0x80){
			if(!(strncmp((char *)str,"����",4))){
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