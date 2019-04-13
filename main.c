#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct node
{
   char data;
   struct node *link;
};

struct node *head,*tail;

int size=4,score=0,hiscore;

char matrix[10][50],food='F',poison='P';

int x[500],y[500],p=0,flag=0,flag1=0;

int fi,fj,px,py;

void create_snake(char x[])
{
  int i;
  head=tail=NULL;
  for(i=0;i<size;i++)
  {
    struct node *temp=malloc(sizeof(struct node)*size);
    temp->data=x[i];
    temp->link=NULL;
    if(head==NULL)
    head=tail=temp;
    else
    {
      tail->link=temp;
      tail=temp;
    }
  }
}

void create_food()
{
   int i,Flag=0;
   if(flag==0)
   {
    fi=rand()%9;
    fj=rand()%49;
    for(i=0;i<size;i++)
    {
      if(fi==x[i] && fj==y[i])
     {
       Flag=1;
       break;
     }
    }
    if(Flag==0)
    {
      matrix[fi][fj]=food;
      flag=1;
    }
     else
     create_food();
   }
}

void create_poison()
{
   int i,Flag=0;
   if(flag1==0)
   {
    px=rand()%9;
    py=rand()%49;
     for(i=0;i<size;i++)
    {
      if(px==x[i] && py==y[i])
     {
       Flag=1;
       break;
     }
    }
    if(Flag==0)
    {
      matrix[px][py]=poison;
      flag1=1;
    }
     else
     create_poison();
   }
}


int make_table()
{
  char b;
  if(p==1)
  printf("  press any key to start or 's' to load save game.\n");
  else
  printf("         press 'p' to pause/resume the game.\n");
  int i,k,j;
  printf("  Score: %d                       HI Score: %d\n",score,hiscore);
  printf(" ");
  for(k=0;k<50;k++)
  printf("=");
  printf("\n");
  for(i=0;i<10;i++)
  {
    printf("|");
    for(j=0;j<50;j++)
    {
      printf("%c",matrix[i][j]);
    }
    printf("|\n");
  }
  printf(" ");
  for(k=0;k<50;k++)
    printf("=");
    if(p==1)
    {
      while(1)
      {
         if(kbhit()==1)
         {
           while(kbhit())
           b=getch();
           break;
         }
      }
      if(b=='s')//file handling
      {
        return 1;
      }
      else
      return 0;
    }
}

void print_snake(int i,int j)
{
    int q=0,k=0;
    struct node *t;
    t=head;
    if(p!=size)
    {
     x[p]=i;
     y[p]=j;
     q=p;
    }
    else
    {
      for(k=0;k<size-1;k++)
      {
        x[k]=x[k+1];
        y[k]=y[k+1];
      }
      x[k]=i;
      y[k]=j;
      q=k;
    }
    while(q!=-1)
    {
      matrix[x[q]][y[q]]=t->data;
      t=t->link;
      q--;
    }
    if(p!=size)
    p++;
}

void add_node()
{
  struct node *temp,*temp1=malloc(sizeof(struct node)*size);
  temp=head;
  temp1->data='#';
  temp1->link=temp->link;
  temp->link=temp1;
}

void delete_node()
{
  struct node *temp;
  temp=head;
  while(temp!=NULL)
  {
      if(temp->link->link->link==NULL)
      {
        temp->link=temp->link->link;
        break;
      }
      temp=temp->link;
  }
}

void reset()
{
  int i,j;
  for(i=0;i<10;i++)
  {
    for(j=0;j<50;j++)
    {
        matrix[i][j]=' ';
    }
  }
  if(flag==0)
  create_food();
  else
  matrix[fi][fj]=food;
  if(flag1==0)

  create_poison();
  else
  matrix[px][py]=poison;
}

int restart()
{
  if(score>hiscore)
  {
     printf("\n\n                   NEW RECORD!!!!\n");
     FILE *f;
     f=fopen("score.txt","w");
     fprintf(f,"%d",score);
     fclose(f);
  }
  char b;
  printf("\n     <---Press 'r' to restart or 'x' to exit--->");
   while(b!='x' && b!='r')
      {
         if(kbhit()==1)
         {
           while(kbhit())
           b=getch();
         }
      }
     if(b=='x')
     exit(0);
     else
     {
       system("cls");
       size=4;
       score=0;
       p=0;
       flag=0;
       flag1=0;
       main();
     }
}

void save(int k,int i,int j)
{
     int I=0;
     FILE *f,*fp;
     fp=fopen("Extras.txt","w");
     f=fopen("save_snake_food.txt","w");
     fprintf(fp,"%d\n",size);
     fprintf(fp,"%d\n",k);
     fprintf(fp,"%d\n",score);
     fprintf(fp,"%d\n",p);
     fprintf(fp,"%d\n",flag);
     fprintf(fp,"%d\n",flag1);
     fprintf(fp,"%d\n",i);
     fprintf(fp,"%d\n",j);
     struct node *temp;
     temp=head;
     while(temp!=NULL)
     {
       fprintf(f,"%c %d %d\n",temp->data,x[I],y[I]);
       temp=temp->link;
       I++;
     }
     fprintf(f,"%c %d %d\n",food,fi,fj);
     fprintf(f,"%c %d %d\n",poison,px,py);
     fclose(f);
     fclose(fp);
}

int main()
{
  char c[100];
  FILE *f;
  f=fopen("score.txt","r");
  fgets(c,10,f);
  hiscore=atoi(c);
  fclose(f);
  char b,prev='d';
  int speed=70,h=1;
  create_snake("H##T");
  int i=0,j=0,k=0;
  reset();
  while(1)
  {
   print_snake(i,j);
   int Y=make_table();
   if(Y==1)
   {
      printf("\n\t\t   Loading...");
      Sleep(1000);
         int u=0,m[50],n[50];
         FILE *f,*fp;
         fp=fopen("Extras.txt","r");
          fscanf(fp,"%d\n",&size);
          fscanf(fp,"%d\n",&k);
          fscanf(fp,"%d\n",&score);
          fscanf(fp,"%d\n",&p);
          fscanf(fp,"%d\n",&flag);
          fscanf(fp,"%d\n",&flag1);
          fscanf(fp,"%d\n",&i);
          fscanf(fp,"%d\n",&j);
          char Snake[size],name;
          f=fopen("save_snake_food.txt","r");
         while( fscanf(f,"%c %d %d\n",&Snake[u],&x[u],&y[u]) != EOF )
         {
          if(Snake[u]=='T')
          break;
          u++;
         }
         fscanf(f,"%c %d %d\n",&food,&fi,&fj);
         fscanf(f,"%c %d %d\n",&poison,&px,&py);
         create_snake(Snake);
         fclose(f);
         fclose(fp);
         p=-1;
   }
   if(kbhit()==1)
   {
    while(kbhit())
    b=getch();
    if(b!='s' && b!='a' && b!='w' && b!='d' && b!='p');
    else if(b==prev);
    else if(b=='p')
    {
      Beep(5000,80);
      printf("\n                   Game paused!!!\n    Press 's' to to save the game or 'x' to exit.    ");
      b='x';
      while(1)
      {
         if(kbhit()==1)
         {
           while(kbhit())
           b=getch();
           if(b=='p' || b=='s' || b=='x')
           break;
         }
      }
       if(b=='p')
       Beep(5000,80);
       else if(b=='x')
       {
         exit(0);
       }
       else //file handling
       {
         printf("\n\t\t   Saving game...");
         Sleep(1000);
         save(k,i,j);
       }
    }
    else
    {
     if(b=='s' && k!=2)
     k=1;
     else if(b=='d' && k!=3)
     k=0;
     else if(b=='w' && k!=1)
     k=2;
     else if(b=='a'&& k!=0)
     k=3;
     prev=b;
    }
   }
   if(k==0)
   {
    j++;
   }
   else if(k==1)
   {
     i++;
   }
   else if(k==2)
   {
     i--;
   }
   else if(k==3)
   {
     j--;
   }
   if(i==-1 || j==-1 || j>49 || i>9)
   {
     Beep(500,100);
     printf("\a\n       The snake hit the wall Game Over!!!!");
     restart();
   }
   else if(matrix[i][j]!=' ')
   {
     if(matrix[i][j]==food)
    {
      Beep(5000,80);
      score+=100;
      size++;
      add_node();
      flag=0;
     }
     else if(matrix[i][j]==poison)
     {
       Beep(600,1000);
       score=score-50;
       if(score<0)
       score=0;
       delete_node();
       size--;
       if(size==2)
       {
         printf("\a\n       The snake died of poison Game Over!!!!");
         restart();
       }
       p--;
       if(k==0)
       {
        j--;
       }
       else if(k==1)
       {
        i--;
       }
       else if(k==2)
       {
        i++;
       }
       else if(k==3)
       {+-
        j++;
       }
       flag1=0;
     }
     else
     {
      printf("\a\n       The snake bit itself Game Over!!!!");
      restart();
     }
   }
   if(matrix[i][j]!=food)
   Sleep(speed);
   score++;
   if(score>=(1000)*h && speed!=0)
   {
    Beep(1200,100);
    speed=speed-10;
    h++;
   }
   reset();
   system("cls");
  }
}
