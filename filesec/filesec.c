#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){


	char en[3] = "-e";
	//printf("%s",en);
	char de[3] = "-d";
	//printf("argv[1] %s",argv[1]);
	char *check = argv[1];	
	//printf("check[0] = %s\n",check[0]);
	//printf("check[1] = %s\n",check[1]);
	
	if(check[1]=='e'&& argv[2]!=NULL)
	{
		// encryption
		FILE *fptr1;
		char *arr = argv[2];
		fptr1 = fopen(arr,"r");
		
		char name[10];
		strncpy(name,argv[2],9);
		char *enc = "_enc.txt";
		name[9] = '\0';
		char *filename = strcat(name,enc);
		FILE* fptr2 = fopen(filename,"w");


		char c = fgetc(fptr1);
		while(c!=EOF)
		{
			//c += 100;
			int a = c;
			if((a>=65 && a<=90))
			{
				a = a-65;
				a = a+100;
				a = a%26;
				a = a+65;
			}
			else if (a>=97 && a<=122)
			{
				a = a - 97;
				a = a+100;
				a = a%26;
				a = a+97;
			}
			else
			{
				c = a;
			}
			c = a;
			fputc(c,fptr2);
			c = fgetc(fptr1);
		}
		//printf("executed\n");
		fclose(fptr1);
		fclose(fptr2);
	}
	else if(check[1] == 'd' && argv[2]!=NULL)
	{
		// decryption
		FILE *fptr1;
		char *arr = argv[2];
		fptr1 = fopen(arr,"r");

		char name[10];
		strncpy(name,argv[2],9);
		char *dec = "_dec.txt";
		name[9] = '\0';
		char *filename = strcat(name,dec);
		FILE* fptr2 = fopen(filename,"w");
		char c = fgetc(fptr1);
		while(c!=EOF)
		{
			//c -= 100;
			int a = c;
			if(a>=65 && a<=90)
			{
				a = a-65;
				a = a-100;
				a = a%26;
				a = a+65;
			}

			else if(a>=97 && a<=122)
			{
				a = a - 97;
				a = a - 100;
				a = a%26;
				a = a+97;
			}
			else
			{
				c = a;
			}
			c = a;
			fputc(c,fptr2);
			c = fgetc(fptr1);
		}
		//printf("decrypted");
		fclose(fptr1);
		fclose(fptr2);

	}

	else if (argc<0)
	{
		printf("Usage:\n");
		printf("filesec -e|-d \n");
	}


	else
	{
		printf("Usage:\n");
		printf("filesec -e|-d %s",argv[2]);

	}
	//printf("completed\n");
	return 0;
}	
