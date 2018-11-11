#include<stdio.h>
#include<string.h>
#include<stdlib.h>
extern int locctr;
void fn()
{
		FILE *dp,*op,*opt,*sympt;
		dp=fopen("dest.txt","r");
		op=fopen("final.txt","w");
		sympt=fopen("sym.txt","r");
		opt=fopen("optab.txt","r");
		int lno,addr,opcode,addr1,txtcnt=1,txtstart,length[10],j=0,sa;
		char mne[10],inst[200],operand[10],name[6],inst1[10]="i",op1[10],inst2[10]=";";
		fscanf(dp,"%d %s %s %x",&lno,mne,inst,&addr);
		sa=addr;
	//	printf("%s",mne);
		memmove(name,mne,6);
		fprintf(op,"H^%-6s^%06x^%06x\n",name,addr,locctr-addr);
	   	fprintf(op,"T^%06x^  ",addr);
		txtstart=addr;
			fclose(sympt);
			fclose(opt);
		while(strcmp(inst1,"end")!=0&&!feof(dp))
		{
				sympt=fopen("sym.txt","r");
				opt=fopen("optab.txt","r");
				fscanf(dp,"%d %x %s %s %s",&lno,&addr,mne,inst1,operand);
				//fscanf(dp,"%d %x %s %s %s",&lno,&addr,mne,inst,operand);
			do
			{


				fscanf(opt,"%s %x",inst2,&opcode);


			}
			while(strcmp(inst1,inst2)!=0&&!feof(opt));
			fclose(opt);
			while(strcmp(operand,op1)!=0&&!feof(sympt))
			{
					fscanf(sympt,"%x %s",&addr1,op1);
					//fgets(inst,40,dp)
			}
			fclose(sympt);

			if(txtcnt<=10)
			{
					if(strcmp(inst1,"RESB")!=0 && strcmp(inst1,"RESW")!=0 && strcmp(inst1,"end")!=0)
			{
					if(strcmp(inst1,"RSUB")==0)
							addr1=0x0;
					if(strcmp(inst1,"WORD")==0)
					{
							addr1=atoi(operand);
							opcode=0x00;
					}

					if(strcmp(inst1,"BYTE")==0)
					{
							int i=2;
							fprintf(op,"^");
							while(operand[i]!='`')
							{
									addr1=operand[i];
									fprintf(op,"%x",addr1);
									i++;
							}
					}
					if(strcmp(inst1,"BYTE")!=0)
					{
							if(addr<0xfff)

							fprintf(op,"^%02x0%03x",opcode,addr1);
							else
									fprintf(op,"^%02x%03x",opcode,addr1);

					}
					length[j]=addr;
			}

					txtcnt++;
			}
			else
			{
					length[j]=addr-txtstart;
					txtstart=addr;
					j++;


					if(strcmp(inst1,"RESB")!=0 && strcmp(inst1,"RESW")!=0 && strcmp(inst1,"end")!=0)
						{
								fprintf(op,"\n");
								fprintf(op,"T^%06x^  ",addr);


									if(strcmp(inst1,"RSUB")==0)
							addr1=0x0;
								if(addr1>0xf)
					{
							fprintf(op,"^%x00%x",opcode,addr1);
					}else

							fprintf(op,"^%x000%x",opcode,addr1);


						}
					txtcnt=1;
			}


		}
		fclose(op);
		if(txtcnt<=10)
		{
			length[j]-=txtstart;
			j++;
		}

//printf("\n%x",length[0]);
int length1[10],i;
for(i=0;i<=1;i++)
{
		length1[i]=length[i];
}

op=fopen("final.txt","r+");
i=0;



			while(1){
				fgets(inst,200,op);
				if(feof(op))
								break;
				fscanf(op,"%s",inst);
				fseek(op,0,SEEK_CUR);
				fprintf(op,"%02x",length1[i]);
				i++;
			}


			fprintf(op,"\nE^%06x",sa);



			fclose(op);

}
