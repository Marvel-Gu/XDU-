/******************************************************************************/
//	���̣�AES
//	���ܣ�AES�ӡ������ļ�
//  ���ߣ�epsoft|MISTP

/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <afxwin.h>
#include <fstream.h>

#include "aes.h"

#define DECRYPT_FILE "AES��������.txt"
#define ENCRYPT_FILE "AES��������.txt"
//! Լ���ļ����2M
#define MAX_FILE	1024*1024*2

/******************************************************************************/
//	���ƣ�usage
//	���ܣ�������Ϣ
//  ������Ӧ�ó�������
//	���أ���ʾ��Ϣ

/******************************************************************************/
void Usage( const char *appname )
{
	printf( "\n\tusage: aes -e �����ļ� 128λ��Կ\n" );
	printf( "\tusage: aes -d �����ļ� 128λ��Կ\n" );
}

/******************************************************************************/
//	���ƣ�FileOut
//	���ܣ���/���ܽ���������ǰĿ¼�����ļ���
//  ������strOutָ������ַ��������������Сlen��strFileΪ����ļ�
//	���أ����³ɹ�����ʵ��������ȣ����򷵻�0

/******************************************************************************/
int FileOut( const void *strOut, int len, const char *strFile )
{
	FILE *fp = NULL;
	int iWrite=0;

	if( strOut == NULL || len ==0 )
		goto out;

	//! ���ļ����
	if( (fp = fopen( strFile,"wb" )) == NULL ) // ������д
		goto out;

	iWrite = fwrite( strOut, 1, len, fp );
	fclose(fp);

out:
	return iWrite;
}

/******************************************************************************/
//	���ƣ�CheckParse
//	���ܣ�У��Ӧ�ó�����ڲ���
//  ������argc����main������argc������argvָ��main������argv����
//	���أ��������Ϸ�����true�����򷵻�false
//  ��ע���򵥵���ڲ���У��

/******************************************************************************/
bool CheckParse( int argc, char** argv )
{
	if( (argc != 4) || 
		(argv[1][1]!='e' && argv[1][1]!='d') ||
		(strlen( argv[3] ) >(128/8) ) )
	{
		Usage( argv[0] );
		return false;
	}

	return true;
}

//! ����������(Use MFC in a Shared DLL)
int main( int argc, char **argv )
{
	//! �ڴ˴���д����......
	unsigned char s[100];//��Կ
	unsigned int c[100];//�ļ�����

	int n;
    printf("AES�ӽ��ܳ���\n");
	while(1)
	{
		cout<<"0.���ܣ�1.���ܣ�2.�˳�"<<endl;
		cin>>n;

		if(n == 2)
			break;
		else if(n == 0)
		{
			cout<<"��������Ҫ���ܵ��ļ�����"<<endl;
			char textfilename[100];
			gets(textfilename);

			fstream f1(textfilename,ios::in);
			int j=0;
			unsigned char p;
			while(f1>>p)
			{
				c[j] = (unsigned int)p;
				j++;
			}

			cout<<"��������Կ�ļ�����"<<endl;
			char keyfilename[100];
			gets(keyfilename);

			fstream f(keyfilename,ios::in);
			int i = 0;
			while(f>>s[i])
			{
				i++;
			}

			aes_encrypt(s,c);//AES����

			cout<<"��������ܺ���ļ���"<<endl;
			char textendfilename[100];
			gets(textendfilename);

			fstream f2(textendfilename,ios::out);
			for(int k=0;k<j;k++)
			{
				f2<<c[k]<<" ";
			}
			f.close();
			f1.close();
			f2.close();

			cout<<"���ܳɹ���"<<endl;
		}

		else if(n == 1)
		{
			cout<<"��������Ҫ���ܵ��ļ���"<<endl;
			char text2filename[100];
			gets(text2filename);

			fstream f3(text2filename,ios::in);
			unsigned int c2[100];
			int q=0;
			while(f3>>c2[q])
			{
				q++;
			}

			unsigned char s2[100];
			cout<<"�����������Կ�ļ���"<<endl;
			char key2[100];
			gets(key2);
			
			fstream f4(key2,ios::in);
			int pkey2=0;
			while(f4>>s2[pkey2])
			{
				pkey2++;
			}
			
			aes_decrypt(s2,c2);//AES����

			cout<<"��������ܺ���ļ���"<<endl;
			char textend2filename[100];
			gets(textend2filename);

			fstream f5(textend2filename,ios::out);
			for(int kp=0;kp<q;kp++)
			{
				f5<<(unsigned char)c2[kp];
			}
			f3.close();
			f4.close();
			f5.close();

			cout<<"���ܳɹ���"<<endl;
			
		}
		else
			cout<<"�����������������룡"<<endl;
	}

	return 0;
}