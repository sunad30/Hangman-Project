#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int life=6,igc=0;
char *guess=(char *)calloc(20,sizeof(char)),cpu[20];
FILE *fp;

void abt()//about game
{ cleardevice();
 settextstyle(2,0,6);
 outtextxy(0,100,"This game was developed by");
 outtextxy(0,120,"R.Chinmaya,Shashwath Kumar and Sunad Suhas of PES University,");
 outtextxy(0,140,"electronic city");
 //need to add more details

}

void inst()//instructions
{ cleardevice();

 settextstyle(2,0,6);
 outtextxy(0,100,"The objective of this game is to guess the alphabets,");
 outtextxy(0,125,"using the given clues to complete the given word.");
 outtextxy(0,150,"If the guessed letter is in the word, it is filled in the blanks,");
 outtextxy(0,175,"else, the drawing of the hangman starts, body part by body part.");
 outtextxy(0,200,"You are allowed 6 guesses, exceeding which, you lose the game.");
}

void base()//support,rope and hanging bar
{
 line(0,20,0,70);//support
 line(0,40,250,40);//hanging bar
 line(250,142,250,40);//rope
 line(0,420,750,420);//floor
}

void inc1()//1st incorrect guess(face)
{
 circle(250,160,18);//
}

void inc2()//body
{
 line(250,178,250,280);
}

void inc3()//left hand
{
 line(217,189,250,200);
}

void inc4()//right hand
{
 line(280,190,250,200);//right hand
}

void inc5()//left leg
{
 line(230,320,250,280);
}

void inc6()//right leg
{
 line(270,320,250,280);
}


void release(int igc)//releases the guy  if the word is comple
{//igc is the number of incorrect guesses, if igc=6, game lost
 cleardevice();
 line(0,20,0,70);//support
 line(0,40,250,40);//hanging bar
 line(0,320,650,320);//floor
 if(igc==1)inc1();
 else if(igc==2){inc1();inc2();}
 else if(igc==3){inc1();inc2();inc3();}
 else if(igc==4){inc1();inc2();inc3();inc4();}
 else if(igc==5){inc1();inc2();inc3();inc4();inc5();}
 settextstyle(1,0,9);
 getch();
 cleardevice();
 outtextxy(120,160,"You Win");
// getch();
}

void gameover()//game lost
{
 line(0,20,0,70);//support
 line(0,40,250,40);//hanging bar
 line(250,142,250,40);//rope
 line(0,420,750,420);//floor
 inc1();inc2();inc3();inc4();inc5();inc6();line(250,142,250,40);//full structure
 getch();
  cleardevice();
 settextstyle(1,0,9);
 outtextxy(100,160,"Game over");
// settextstyle(1,0,3);
// outtextxy(getmaxx()-50,50,cpu);
}

void assign(int a)
{   cleardevice();
   int rand,l=0;
 randomize();
 if(a==1) //#singleplayer #yolo #escn
 {rand = random(10)+1;

  fp=fopen("cpuwords.txt","r");

  while(fgets(cpu,30,fp)!=NULL)
  { char *val = strtok(cpu,"\n");
    strcpy(cpu,val);
    l++;
    if(l==rand)
     break;
  }

  fclose(fp);
 }
 else if(a==2)//#ihavefriends #2player
  {
   gotoxy(10,10);
   printf("Enter the word to be guessed:");
   cin>>cpu;
  }
 for(int i=0;cpu[i];i++)
 {
  if(random(6)==0)
   guess[i]=cpu[i];
 }
}

void end()
{  cleardevice();
 if(life==0){gameover();}//add graphics
 //the above line is when you lose the game,i.e, player is hanged
 else release(igc);//releaes the person if the word is guessed correctly
 settextstyle(0,0,1);
 outtextxy(getmaxx()/2-50,getmaxy()-20,"Word:");
 outtextxy(getmaxx()/2,getmaxy()-20,cpu);
 getch();
}

void output(int igc)//to draw a body part for every incorrect guess
{
 base();
 settextstyle(0,0,1);
 outtextxy(getmaxx()-50,20,"life:");
 char ch[3];
 itoa(life,ch,10);
 outtextxy(getmaxx()-10,20,ch);
 if(igc==1){inc1();}
 else if(igc==2){inc1();inc2();}
 else if(igc==3){inc1();inc2();inc3();}
 else if(igc==4){inc1();inc2();inc3();inc4();}
 else if(igc==5){inc1();inc2();inc3();inc4();inc5();}
 else if(igc==6){inc1();inc2();inc3();inc4();inc5();inc6();}//add graphics
 gotoxy(5,20);
 for(int i=0;i<strlen(cpu);i++)
 {
  if(guess[i]==NULL)
   printf("-");
  else
   printf("%c",guess[i]);
 }
}

void gayme()
{char ch;int flag=0,i;
 while(life>0)
 {cleardevice();
   output(igc);
  cin>>ch;
  flag=0;
  for(i=0;i<strlen(cpu);i++)//checks if the letter exists and assigns the letter to guess
   {
    if(ch==cpu[i]) //the letter is entered and paced wherever it fits
     {guess[i]=cpu[i];
      flag=1;
     }
   }

  if(flag==0)
   {
    life=life -1;
    igc=igc+1;

   }
  if(strcmp(guess,cpu)==0)
   break;
 }
 end();

}

void start()
{
 int a;
 cleardevice();
 settextstyle(1,0,5);

  outtextxy(100,140,"1.Single player");
  outtextxy(100,180,"2.Two player");
  scanf("%d",&a);


 assign(a);
 gayme();
}

void menu()
{
 int opt;
 char chs;
 do
 {cleardevice();
  settextstyle(1,0,7);
  outtextxy(100,35,"Hangman");
  settextstyle(1,0,4);
  outtextxy(70,130,"1.Start Game");
  outtextxy(70,170,"2.Instructions");
  outtextxy(70,210,"3.About Game");
  outtextxy(70,250,"4.Exit");
  cin>>opt;
  cleardevice();
  switch(opt)
  {
   case 1:start();
	  break;
   case 2:inst();
	  break;
   case 3:abt();
	  break;
   case 4:exit(0);
	  break;
   default:cleardevice();cout<<"Invalid choice!";
  }
 getchar();
 cleardevice();
// gotoxy(15,15);
// cout<<"Back to menu?";cin>>chs;
 life=6;igc=0;
 guess=(char *)calloc(20,sizeof(char));
 }while(1);
//cleardevice();
//cout<<"Press any key to exit.";
}

void main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\TC\\BGI");
 menu();
 getch();
 closegraph();

}