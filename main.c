#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define ENTER 13
#define TAB 9
#define BKSPC 8
#define N 20
#define M 40

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int k,l,Field[N][M],x,y,Gy,Head,Tail,Game,Frogs,a,b,var,dir,score,Highscore,level,nm;
FILE *fp,*f;
struct user{
    char fullName[50];
    char email[50];
    char password[50];
    char username[50];
};

struct user user;

void takeinput(char ch[50]){
    fgets(ch,50,stdin);
    ch[strlen(ch)-1]=0;

}

char generateUsername(char email[50],char username[50]){
    for(int i =0;i<strlen(email);i++){
        if(email[i]=='@') break;
        else username[i]=email[i];
    }
}

void takepassword(char pwd[50]){
        int i;
        char ch;
        while(1){
            ch=getch();
            if(ch==ENTER || ch==TAB){
                pwd[i]='\0';
                break;

            }else if(ch == BKSPC){
                if(i>0){
                    i--;
                    printf("\b \b");
                }
            }else{
                pwd[i++]=ch;
                printf("* \b");
            }
        }
}

InitializationSnakeGame(){
    f=fopen("highScore.txt","r");
    fscanf(f,"%d",&Highscore);
   // fread(&user,sizeof(score),1,f);
   // fscanf(f,"&d",&Highscore);
    fclose(f);
        for(k=0;k<N;k++){
            for(l=0;l<M;l++){
                Field[k][l]=0;
            }
        }
        x=N/2; y=M/2; Gy=y; Head=5; Tail=1,Game=0,Frogs=0,dir=KEY_RIGHT,score=0,level=1,nm=50;

        for(k=0;k<Head;k++){
            Gy++;
            Field[x][Gy-Head]=k+1;

        }

}

printGame(){
  //f=fopen("HighScore.txt","r");
  // fread(Highscore,sizeof(score),1,f);
 printf("\n");
     printf("\t\t\t\t\t\t********SNAKE GAMEE********\n");
     printf("\n");
     for(k=0;k<=M+1;k++){
        if(k==0){
            printf("\t\t%c",201);
        }else if(k==M+1){
            printf("%c",187);
        }else{
            printf("%c",205);
        }
     }

     printf("\tCurrent Score: %d  HighScore: %d level: %d",score,Highscore,level);
     printf("\n");
     for(k=0;k<N;k++){
        printf("\t\t%c",186);
        for(l=0;l<M;l++){
          if(Field[k][l]==0){
            printf(" ");
          }
          if(Field[k][l]>0&&Field[k][l]!=Head){
            printf("%c",176);
          }
          if(Field[k][l]==Head){
            printf("%c",178);
          }
          if(Field[k][l]==-1){
            printf("%c",15);
          }
          if(l==M-1){
            printf("%c\n",186);
          }
        }
     }
      for(k=0;k<=M+1;k++){
        if(k==0){
            printf("\t\t%c",200);
        }else if(k==M+1){
            printf("%c",188);
        }else{
            printf("%c",205);
        }
     }

}


Random(){
    srand(time(0));
        a=1+rand()%18;
        b=1+rand()%38;
        if(Frogs==0&&Field[a][b]==0){
            Field[a][b]=-1;
            Frogs =1;
        }
}


ResetScreenPosition(){
        HANDLE hOut;
        COORD Position;
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        Position.X=0;
        Position.Y=0;
        SetConsoleCursorPosition(hOut,Position);
}
int getChar_noBlcok(){
    if(_kbhit()){
        return _getch();
    }else
        return -1;
}
movement(){
            var = getChar_noBlcok();
          //  72 up arrow
          //80 down a

            if(((var==KEY_RIGHT||var==KEY_LEFT)||(var==KEY_UP||var==KEY_DOWN))
                &&abs(dir-var)>2){
                dir=var;
            }
            if(dir==KEY_RIGHT){
                y++;
                if(Field[x][y]!=0&&Field[x][y]!=-1){
                    GameOver();
                }
                if(y==M-1){
                    y=0;
                }
                if(Field[x][y]==-1){
                    Frogs=0;
                    score+= 10;
                    Tail -=2;
                }
                Head++;
                Field[x][y]=Head;
            }
            if(dir==KEY_LEFT){
                y--;
                  if(Field[x][y]!=0&&Field[x][y]!=-1){
                    GameOver();
                }
                if(y==0){
                    y=M-1;
                }
                 if(Field[x][y]==-1){
                    Frogs=0;
                    score+= 10;
                     Tail -=2;
                }
                Head++;
                Field[x][y]=Head;
            }
      if(dir==KEY_DOWN){
                x++;
                  if(Field[x][y]!=0&&Field[x][y]!=-1){
                    GameOver();
                }
                 if(x==N){

                   x=0;
                }
                 if(Field[x][y]==-1){
                    Frogs=0;
                    score+= 10;
                     Tail -=2;
                }
                Head++;
                Field[x][y]=Head;
            }
             if(dir==KEY_UP){
                x--;
                  if(Field[x][y]!=0&&Field[x][y]!=-1){
                    GameOver();
                }
                 if(x==-1){
                    x=N-1;
                }
                if(Field[x][y]==-1){
                    Frogs=0;
                    score+= 10;
                     Tail -=2;
                }
                Head++;
                Field[x][y]=Head;
            }

     if(score>nm){
        level++;
        nm+=50;
     }
}

TailRemove(){
 for(k=0;k<N;k++){
            for(l=0;l<M;l++){
                if(Field[k][l]==Tail){
         Field[k][l]=0;

                }
            }
        }
        Tail++;
}

StartGame(){
        /*int num;
         scanf("%d",&num);
         if(num==1){
               menubar();
         }*/
         InitializationSnakeGame();
         while(Game==0){
            printGame();
            ResetScreenPosition();
            Random();
            movement();
            TailRemove();
            Sleep(99);
         }

}

GameOver(){
    int n;
    printf("\a");
    Sleep(1500);
    system("cls");
    if(score>Highscore){
        printf(" New HightScore %d!!!!\n\n",score);
        system("pause");
        f=fopen("HighScore.txt","w");
  // fwrite(Highscore,sizeof(score),1,f);
   fprintf(f,"%d",score);
        fclose(f);
    }
    system("cls");
    printf("\n\n          Game Over!  ");
    printf("              Score : %d \n",score);
    Game =1;

    printf("\n\n\nTo Rematch Press 1: \n For Menu options press 2: \n");
    scanf("%d",&n);
    switch(n){
    case 1:
        system ("cls");
        StartGame();
        break;
    case 2:
         system ("cls");
         menubar();
         break;
    default:
        printf(" Kindly Press any key between 1/2 or any other key to exit. ");

    }
}
CheckLevel(){
    printf("\t\t\t\t\t\tLevels\t\t\t\n\n\n");
    printf("\t\t\t\tThe Levels Increases each time \n\t\t\t the snake addes 50 to its scores.\t\t\t\t\t\t\n\n\n ");
    printf("\t\t\t\t\t\tLevel 1 ->50\n");
    printf("\t\t\t\t\t\tLevel 2 ->100\n");
    printf("\t\t\t\t\t\tLevel 3 ->150\n");
    printf("\t\t\t\t\t\tLevel n->score+50\n");

     int num;
         printf("Enter 1 to get back to menubar.........\n");
         scanf("%d",&num);
         if(num==1){
                system ("cls");
               menubar();
         }

}

CheckLeaderboard(){
    printf("\t\tLeaderBoard\n ");
    printf("Username: %s         HighScore:%d\n ",user.username,Highscore);
 int num;
         printf("Enter 1 to get back to menubar.........\n");
         scanf("%d",&num);
         if(num==1){
             system ("cls");
               menubar();
         }
}

menubar(){
    printf("========================================================================================================================\n");
        int num;
        printf("\t\t\t\t\t\t ***SNAKE GAME***\n\n");
        printf("\t\t\t\t\t\t 1. Start\n");
        printf("\t\t\t\t\t\t 2. Level\n");
        printf("\t\t\t\t\t\t 3. Leader Board\n");
        printf("\t\t\t\t\t\t 4. Exit\n\n");
        printf("\t\t\t\t\tPress to action (1, 2, 3, 4)....\n");
        scanf("%d",&num);
         while(num>4||num==0){
                printf("Kindly Enter number between 1 and 4:  ");
                scanf("%d",&num);
     }
        switch(num){

        case 1:
             system ("cls");
            StartGame();
            break;
        case 2:
             system ("cls");
            CheckLevel();
            break;
        case 3:
             system ("cls");
            CheckLeaderboard();
            break;
        case 4:

            system ("cls");
            IntroPage();
            break;
        default:
            printf("\t\t\t\t\tEnter positive number between (1-4)..........\n");

     break;
        }
 printf("\n========================================================================================================================\n");
}

login(fname,uname,upas,umeail){

int usrFound = 0;
char Username[50];
char Pword[50];
printf("========================================================================================================================\n");
printf("========================================================================================================================\n");

printf("\nEnter your username:\t");
        takeinput(Username);
        printf("\nEnter your password:\t");
        takepassword(Pword);

        fp=fopen("Users.txt","r");

         system ("cls");
        while(fread(&user,sizeof(struct user),1,fp)){
                printf("========================================================================================================================\n");
printf("========================================================================================================================\n");
            if(!strcmp(uname,Username)){
                if(!strcmp(upas, Pword)){

                  /* printf("\t\t\t\t\t\tWelcome %s",uname);
                    printf("\n\n\t\t\t\t\t\t|Full Name: \t%s",fname);
                    printf("\n\t\t\t\t\t\t|Email: \t%s",umeail);
                    printf("\n\t\t\t\t\t\t|Username:\t%s\n",uname);*/

                    menubar();




                }else{
                     printf("\n\n\t\t\t\t\t\tInvalid Password!\n");
                     Beep(800,300);
                }
                usrFound =1;
            }

            if(usrFound==0){
                printf("\n\n\t\t\t\t\t\tUser is not registerd.\n");
                Beep(800,300);
            }
                     printf("========================================================================================================================\n");
                     printf("========================================================================================================================\n");

            fclose(fp);
}}

Register(int opt){


    //struct user user;

    char password2[50];
     switch(opt){
    case 1:
                     printf("========================================================================================================================\n");

           printf("========================================================================================================================\n");
        printf("\t\t\t\t\t\tEnter your full name: \t");
        takeinput(user.fullName);
        printf("\t\t\t\t\t\tEnter your email: \t");
        takeinput(user.email);

        printf("\t\t\t\t\t\tEnter your password: \t");
        takepassword(user.password);
        printf("\n\t\t\t\t\t\tConfirm your password: \t");
        takepassword(password2);
             printf("\n========================================================================================================================\n");
           printf("\n========================================================================================================================\n");

        if(!strcmp(user.password,password2)){
            generateUsername(user.email,user.username);
            fp=fopen("Users.txt","w");
            fwrite(&user,sizeof(struct user),1,fp);
            if(fwrite !=0){
              printf("\nUser registration is successful.\n Your username is %s.\n",user.username);
            printf("Press any key to continue.........");
              getch();
                 fclose(fp);
                 system ("cls");
                 login(user.fullName,user.username,user.password,user.email);


             // login(user.fullName,user.username,user.password,user.email,user.phone);
            } else printf("\nSorry! Something went wrong!");



        }else{
            printf("\nPassword didn't matched.\n");
            Beep(750,300);
        }
        break;
    case 2:

        login(user.fullName,user.username,user.password,user.email);

            break;

        }


     }

IntroPage(){

   int opt=0;

               printf("========================================================================================================================\n");

    printf("\n\t\t\t\t\t\tWELCOME To The ultimate Game of\t\t\t\t\n");
     printf("\n\t\t\t\t\t\t\tSNAKESSSS\t\t\t\t\n");
             printf("========================================================================================================================\n");

      printf("\n\t\t\t\tEnter in the Game through login panel by pressing 2\n");
     printf("\n\t\t\t\tHaven't signed up yet? Sign up first by pressing 1\n");
     printf("Enter your choice(1/2): \n");
     scanf("%d",&opt);
     while(opt>2){
        printf("Kindly Enter number between 1 and 2:  ");
         scanf("%d",&opt);
     }
     fgetc(stdin);
   system ("cls");
Register(opt);
}


int main()
{
     system("color 0b");
      IntroPage();

    return 0;
}
