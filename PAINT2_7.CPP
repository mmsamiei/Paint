#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
int x,y,g,co;
int pic[24][80];
int far * scr=(int far *)0XB8000000;
int t;
void init();
void docommand(int i,char c);
char Getkey(int& );
void fill(int ,int);
int main()
{
 init();
 int i;
 char c=Getkey(i);
 docommand(i,c);
	while(i!=0 ||(int) c != 27)
	{
	c=Getkey(i);
	docommand(i,c);
	}
 return 0;
}

void init ()
{
 int far * scr=(int far *)0XB8000000;
 for(int i=0;i<2000;i++)
 {
	*(scr+i)=0X7f*256+32;
	if( (i % 80 == 0) || (i%80 == 79 ) || (i<80) || (i>1920) )
		*(scr+i)=0X40*256+32;
 }
		x=12;
		y=40;
		g=*(scr+80*x+y);
		co=0X7f;
		*(scr+80*x+y)=co*256+'*';
		*(scr+1920)=0X07*256+'1';
		*(scr+1921)=0X17*256+'2';
		*(scr+1922)=0X27*256+'3';
		*(scr+1923)=0X37*256+'4';
		*(scr+1924)=0X47*256+'5';
		*(scr+1925)=0X57*256+'6';
		*(scr+1926)=0X67*256+'7';
		*(scr+1927)=0X70*256+'8';
		*(scr+1935)=0X40*256+'i';
		*(scr+1936)=0X40*256+'n';
		*(scr+1937)=0X40*256+'s';
		*(scr+1938)=0X40*256+'e';
		*(scr+1939)=0X40*256+'r';
		*(scr+1940)=0X40*256+'t';
		*(scr+1941)=0X40*256+':';
		*(scr+1942)=0X40*256+'p';
		*(scr+1943)=0X40*256+'e';
		*(scr+1944)=0X40*256+'n';
		*(scr+1946)=0X40*256+'o';
		*(scr+1947)=0X40*256+'f';
		*(scr+1948)=0X40*256+'f';
		*(scr+1960)=0X40*256+'c';
		*(scr+1961)=0X40*256+'o';
		*(scr+1962)=0X40*256+'l';
		*(scr+1963)=0X40*256+'o';
		*(scr+1964)=0X40*256+'r';
		*(scr+1965)=0XFF*256+178;
		t=0;
}
char Getkey(int& c)
{
char I=getch();
if(I==0)
	{
	I=getch();
	c=1;
	}
else
	c=0;
return I;
}

void docommand(int i,char c)
{
if(!i)switch(c){
	case'1':
	case'2':
	case'3':
	case'4':
	case'5':
	case'6':
	case'7':co=0X0f+(c-'1')*16;
		*(scr+80*x+y)=co*256+'*';
		*(scr+1965)=co*256+177;
		if(t)	g=co*256;
		break;
	case'8':co=0X7f;
	*(scr+1965)=co*256+177;
	if(t)	g=co*256;
		break;
	case'f':*(scr+80*x+y)=g;
		fill(x,y);
		g=*(scr+80*x+y);
		*(scr+80*x+y)=co*256+'*';
		break;
	case's':
		for(int i=0;i<24;i++)
		    for(int j=0;j<80;j++)
			pic[i][j]=*(scr+80*i+j);
		    pic[x][y]=g;
		FILE *ptr;
		ptr=fopen("pic.bin","w");
		fwrite (pic , sizeof(int), sizeof(pic), ptr);
		fclose(ptr);
		break;
	case'l':
		FILE *load;
		char a='s';
		load=fopen("pic.bin","r");
		fread(pic,sizeof(int),80*25,load);
		fclose(load);
		for(i=0;i<24;i++)
			for(j=0;j<80;j++)
				*(scr+80*i+j)=pic[i][j];
			g=*(scr+80*x+y)=pic[x][y];
			*(scr+80*x+y)=co*256+'*';
		t=0;

	}
else{
	switch(c){
	case'R':t=!t;
		if(t)
			{
			*(scr+1946)=0X40*256+'o';
			*(scr+1947)=0X40*256+'n';
			*(scr+1948)=0X40*256+' ';
			g=co*256+32;//if in tike pak she!
			}
		else
			{
			*(scr+1946)=0X40*256+'o';
			*(scr+1947)=0X40*256+'f';
			*(scr+1948)=0X40*256+'f';
			g=co*256+32;
			}
	break;
	case'G':init();
	break;
	case'H':if(x>1 && !t)
		{
			*(scr+80*x+y)=g;
			g=*(scr+80*(x-1)+y);//co*256+32;
			x--;
			*(scr+80*x+y)=co*256+'*';
		}
		if(x>1 && t)
		{
			*(scr+80*x+y)=co*256+32;
			g=*(scr+80*(x-1)+y);
			x--;
			*(scr+80*x+y)=co*256+'*';
		}break;
	case'P':if(x<23 && !t)
		{
			*(scr+80*x+y)=g;
			g=*(scr+80*(x+1)+y);
			x++;
			*(scr+80*x+y)=co*256+'*';
		}
		if(x<23 && t)
		{
			*(scr+80*x+y)=co*256+32;
			g=*(scr+80*(x+1)+y);
			x++;
			*(scr+80*x+y)=co*256+'*';
		}break;
	case'K':if(y>1 && !t)
		{
			*(scr+80*x+y)=g;
			g=*(scr+80*x+y-1);
			y--;
			*(scr+80*x+y)=co*256+'*';
		}
		if(y>1 && t)
		{
			*(scr+80*x+y)=co*256+32;
			g=*(scr+80*x+y-1);
			y--;
			*(scr+80*x+y)=co*256+'*';
		}break;
	case'M':if(y<78 && !t)
		{
			*(scr+80*x+y)=g;
			g=*(scr+80*x+y+1);
			y++;
			*(scr+80*x+y)=co*256+'*';
		}
		if(y<78 && t)
		{
			*(scr+80*x+y)=co*256+32;
			g=*(scr+80*x+y+1);
			y++;
			*(scr+80*x+y)=co*256+'*';
		}break;
	}
	}


}

void fill(int m,int n)
{
	if( *(scr+80*m+n)/256 == co)return ;
	if( *(scr+80*m+n) != g )return ;
	*(scr+80*m+n)=co*256+32;
	fill(m-1,n);
	fill(m,n-1);
	fill(m+1,n);
	fill(m,n+1);
}
