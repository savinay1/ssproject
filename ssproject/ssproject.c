#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
void fn();
int locctr;
int main()
{
		char inst[22],label[5],addr[3], inst2[40],inst3[40],operand[5],mne[5];
		int start;
		int addr1;
		int inst1[21][1];
		int i=4,j=0,l;
		FILE *sp,*sp1,*ip,*symp;

		sp=fopen("source.txt","r");
		sp1=fopen("source1.txt","w");
		ip=fopen("dest.txt","w");


		while(fgets(inst2,40,sp))
		{

				if(inst2[0]=='.')
				{
						fgets(inst2,40,sp);
				}
				fputs(inst2,sp1);
		}
		fclose(sp);
		fclose(sp1);
		sp1=fopen("source1.txt","r");
		fscanf(sp1,"%d   %s %s",&l,label,mne);

		if(strcmp(mne,"START")==0)
		{
				fscanf(sp1,"%x",&addr1);

			fprintf(ip,"%d   %s %s %x\n",l,label,mne,addr1);

				start=addr1;
		}
		else
		{
			fscanf(sp1,"%s",operand);
			fprintf(ip,"%d   %s %s %s\n",l,label,mne,operand);
				start=0;
		}
		inst1[0][j]=start;
		for(i=1;i<21;i++)
		{
				inst1[i][j]=start+3;
				start=inst1[i][j];
		}

		for(i=1;i<21;i++)
		{
			//fscanf(sp,"%s",s);

			fscanf(sp1,"%d %s  %s %s",&l,label,mne,inst3);

			if(strcmp(mne,"BYTE")==0)
			{

				if(inst3[0]=='X')
				{
								inst1[i][j]=inst1[i-1][j]+1; }
    					  else
    	  				{
    				 	 int len=strlen(inst3)-3;
						 	inst1[i][j]=inst1[i-1][j]+len;
							inst1[i+1][j]=inst1[i][j]+3;
						}
    			}
				else
						if(strcmp(mne,"RESB")==0)
						{
								inst1[i][j]=inst1[i-1][j]+atoi(inst3);

						}
						else
								if(strcmp(mne,"RESW")==0)
								{
										inst1[i][j]=inst1[i-1][j]+atoi(inst3)*3;
								}


		}

		fclose(sp1);
		sp1=fopen("source1.txt","r");

	//printf("%d",inst1[20][j]);
		fgets(inst2,30,sp1);
		i=0;
		while(1)
		{
				fgets(inst2,4,sp1);
				fputs(inst2,ip);

				 if((inst1[i][j])<=15)
					fprintf(ip," %x   ",inst1[i][j]);
				else
						if((inst1[i][j])<=225)
						fprintf(ip," %x  ",inst1[i][j]);
						else
								if((inst1[i][j])<=3375)
						fprintf(ip," %x ",inst1[i][j]);
						else
						fprintf(ip," %x",inst1[i][j]);


				fgets(inst2,40,sp1);

						fputs(inst2,ip);
				locctr=inst1[i][j];
				char *x=strstr(inst2,"end");
				if(x)
					break;
				else
						i++;

		}
	//	printf("%x",locctr);

		fclose(ip);
		fclose(sp1);
		ip=fopen("dest.txt","r");
		symp=fopen("sym.txt","w");
		fgets(inst3,40,ip);

				//fgets(inst3,40,ip);
		while(fgets(inst3,40,ip))
		{
				i=4;
				if(inst3[9]!='-')
				{
					while(inst3[i]!=' ')
					{
						fprintf(symp,"%c",inst3[i]);
						i++;
					}
				}
				else
						continue;

					while(i<=8)
					{
						fprintf(symp," ");
						i++;
					}
					i=9;
					while(inst3[i]!=' ')
					{
							fprintf(symp,"%c",inst3[i]);

							i=i+1;
					}

					fprintf(symp,"\n");
		}
		fclose(ip);
		fclose(symp);
		fn();


}
