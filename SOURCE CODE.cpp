/*
                           ******** KEYWORDS AND PHRASES ********
   *************************************************************************************************
   * CELL: each of the 81 squares , holding either the problem numbers or the solution numbers.    * 
   *                                                                                               *
   * PROBLEM NUMBER: all the numbers that are given already in the GRID.                           *
   *                                                                                               *
   * SOLUTION NUMBER: all the numbers that a user will enter during the game                       *
   *                                                                                               * 
   * EMPTY CELL (or SOLUTION CELL ): a cell where the user will enters a number for the game and   *
   *                                can be edited.                                                 * 
   *                                                                                               *
   * FILLED CELL (or PROBLEM CELL):  a cell which is already filled with a number and can't        *        
   *                                 be edited.                                                    *
   * POSITION : cursor position w.r.t screen                                                       *
   *************************************************************************************************
*/
                                    
                                      
 
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h> //for gotoxy() and system("cls")
#include<ctype.h>   //for isdigit()
#include<malloc.h>

# define EMPTY_CELL 0 
# define gotoxy g    //macro substitution

# define ENTER_KEY  13
# define UP    72 
# define LEFT  75
# define DOWN  80
# define RIGHT 77

//-------------------------GLOBAL DECLARATIONS----------------------------//

int E=96;
int H=102;
int resume_status=0;

int GRID[9][9];  //matrix for storing the game

HANDLE hStdout, hStdin, hOut;
CONSOLE_CURSOR_INFO ConCurInf;

//-------------------------------------------------------------------------//


//-------------------SINGLE LINKED LIST DECLARATION---------------------------------//
struct SLL{
       
       int X_coordinate;
       int Y_coordinate;
       int value;
       
       struct SLL *next;
       
       } *header = NULL;
//------------------------------------------------------------------------//

//-------------------STRUCTURE DECLARATION----------------------------//

struct store{
       char game_code;
       int x;
       int y;
       int val;
       };
       
//------------------FUNCTION DECLARATIONS---------------------------------//


void gotoxy(int x, int y)    
{
    COORD ord;
    ord.X = x;
    ord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

int key_cursor(int, int, int);
/* sets an arrow(i.e "<--") at the first option and
   then lets you scroll up and down using
   the arrow keys.It returns 1 if first
   option is selected, 2 if second and
   so on.Works for n options.
   (x,y) are the coordinates of the
   position at which you want the arrow */
   
void print_sudoku();   
void design();  
void instructions(); 
void resume();
void ask_for_levels();
void play_level(int);
void draw_GRID();       
void fill_GRID(int);
void init_matrix();
void put_value_in_cell(char ,int , int);
void add_positions_to_SLL(int , int);
void fill_previous_numbers();
void add_solutions_to_SLL(char);
void fill_grid(int grid[9][9]);
void begin_game(int);
int check_GRID(int, int);
void delete_temp_cursor(int, int);
int pause_screen_options(int);
void get_cursor_position(int * , int *);
int check_coordinates(int , int);
int check_limit(int ,int ,int);
int check_GRID();
void end_game_message();
void free_SLL();
void print_GRID_solution(int level); 
int find_empty_cell(int grid[9][9],int*,int*);
int check_if_possible(int grid[9][9],int,int,int);
int Shiznit_Solve(int grid[9][9]);
void save_current_game(int);


//-------------------------------MAIN----------------------------//

int main()
{
    
   hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   
   SetConsoleTextAttribute(hStdout , FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);//setting text color
   
   hOut = GetStdHandle(STD_OUTPUT_HANDLE);  /* ------------------------------------*/
   
    ConCurInf.dwSize = 10;                  /*---REMOVING CURSOR FROM THE SCREEN---*/
    ConCurInf.bVisible = FALSE;             /*------------------------------------*/
 
   SetConsoleCursorInfo(hOut, &ConCurInf);  /*------------------------------------*/ 
   
   print_sudoku();
   
   design();
   
   g(43,35);
   printf("SUDOKU - YOUR DAYS ARE NUMB3R3D");
   g(43,36);
   printf("-------------------------------");
   g(52,39);
   printf("%c PLAY GAME",254);   /* OPENING SCREEN*/
   g(52,41);
   printf("%c RESUME GAME",254);
   g(52,43);
   printf("%c INSTRUCTIONS",254);
   g(52,45);
   printf("%c EXIT",254);
   
   int user_choice=key_cursor(68,39,4); //LETTING THE USER CHOOSE AN OPTION
   /* description of the arguments passed above:
                  68: X coordinate for the position to place the arrow
                  39: y coordinate for the position to place the arrow  
                  2:  this is evaluated by (last Y coordinate- first Y coordinate -2 )
                      i.e 45-39-2 = 4 */
   
   switch(user_choice)
   {
                      case 1:
                           system("cls");
                           ask_for_levels();
                           break;
                           
                      case 2:
                           system("cls");
                           resume();
                           break;
                           
                      case 3:
                           system("cls");
                           instructions();
                           break;
                           
                      case 4:
                           free_SLL();
                           exit(0);
  }//end of switch case


}//---------------------------end of MAIN------------------------------------------//


void print_sudoku()
{
    
g(30,11);
printf("    SSSSSSS  U      U  DDDDD     OOOOO   K  K   U      U    \n");
g(30,12);
printf("    SS       U      U  DD  DD   OO   OO  K K    U      U     \n"); 
g(30,13); 
printf("      SSS    U      U  DD   DD  OO   OO  KK     U      U  \n");
g(30,14);
printf("         SS  U      U  DD   DD  OO   OO  K K    U      U   \n");
g(30,15);
printf("    SSSSSSS  UUUUUUUU  DDDDDD    OOOO0   K  K   UUUUUUUU    \n"); 

for(int x=32;x<=86;x++)
{
        g(x,9);
        printf("%c",220);
}

for(int x=32;x<=86;x++)
{
        g(x,16);
        printf("%c",220);
}

for(int x=32;x<=86;x++)
{
        g(x,47);
        printf("%c",220);
}

for(int y=10;y<=47;y++)
{
        g(32,y);
        printf("%c",219);
}

for(int y=10;y<=47;y++)
{
        g(87,y);
        printf("%c",219);
}

}


void design()
{
     int vertical=179, horizontal=196;
     
     int x,y;
     for(y=20;y<=29;y++)
     {
                        g(49,y);
                        printf("%c",vertical);
     }
     
     for(x=50;x<=65;x++)
     {
                        g(x,19);
                        printf("%c",horizontal);
     }
     
     for(y=20;y<=29;y++)
     {
                        g(66,y);
                        printf("%c",vertical);
     }
     
     for(x=50;x<=65;x++)
     {
                        g(x,30);
                        printf("%c",horizontal);
     }
     
     for(y=23;y<=26;y+=3)
     {
                         g(50,y);
                         for(x=49;x<=66;x++)
                         {
                         g(x,y);
                         printf("%c",horizontal);
                         }
     }
     
     for(x=55;x<=60;x+=5)
     {
                         g(x,13);
                         for(y=20;y<=29;y++)
                         {
                                            g(x,y);
                                            printf("%c",vertical);
                         }
     }
     g(52,21);
     printf("S");
     g(58,21);
     printf("1");
     g(63,21);
     printf("U");

     g(52,25);
     printf("D");
     g(58,25);
     printf("2");
     g(63,25);
     printf("O");
     
     g(52,28);
     printf("K");
     g(58,28);
     printf("3");
     g(63,28);
     printf("U");
}
 
void instructions()
{
     system("cls");
     int l=254;
     g(55,10);
     printf("INSTRUCTIONS");
     g(55,11);
     printf("------------");
     
     g(35, 15);
     printf("A Sudoku Puzzle is a grid of 9X9 squares or cells, that has been");
     g(35,17);
     printf("sub-divided into 9 sub-grids or boxes, each consisiting of 3X3");
     g(35,19);
     printf("cells.");
     
     g(35, 23);
     printf("The objective of the game is to enter a digit from 1 through 9");
     g(35,25);
     printf("in each cell, in such a way that:");
     g(38,28);
     printf("%c Each horizontal ROW contains each digit exactly once.",l);
     g(38,30);
     printf("%c Each vertical COLUMN contains each digit exactly once.",l);
     g(38,32);
     printf("%c Each SUB_GRID or REGION ROW contains each digit exactly once.",l);
     
     g(55,38);
     printf("BACK");
     g(55,40);
     printf("EXIT");
     
     int user_choice=key_cursor(61,38,0);
     
     if(user_choice==1){
     system("cls");
     main();
     }
     
     if(user_choice==2)
     exit(0);
}

void resume()
{
     resume_status=1;
     
     char ch;
     
     FILE *fp= fopen("SUDOKU_SAVE_FILE.dat","rb");
     
     struct store s;
     
     fseek(fp, 0, SEEK_END);
     if(ftell (fp) == 0 || fp == NULL) // if file is empty, or doesn't exist, display message
     {
              resume_status=0;
              g(40,18);
              printf("CURRENTLY, THERE ARE NO SAVED GAMES !!!!");
              g(50,22);
              printf("BACK");
              g(50,24);
              printf("EXIT");
              
              int choice= key_cursor(56, 22, 2);
              
              if(choice ==1)
              {
              system("cls");          
              main();
              }
              
              if(choice==2)
              exit(0);
     }
     
     rewind(fp);
     while( fread (&s, sizeof(s), 1, fp))
     {
      ch=s.game_code;
     break;
     }

     if( ch == 'a' || ch== 'b' || ch== 'c' || ch== 'd' || ch== 'e')// if game codes are of easy games
     play_level(1);
     
     else
     play_level(2);
     
     fclose(fp);
}

void free_SLL()
{
     struct SLL *temp;
     
     if(header==NULL)
     return ;
     
     while(header!=NULL)
     {
        temp=header;
        free(temp);
                   
        header=header->next;
     
     }//end of while
             
}

int key_cursor(int x,int y,int n)
{
 int ch1,ch2,i=y;
 
 
 int k=1; //initially k=1, i.e the arrow is pointing to the first option 
 
 /*  k=1 for option 1
     k=2 for option 2
     k=3 for option 3  ... and so on till option n*/
     
     
 g(x,y);
 printf("<%c%c%c",196,196,196); //place the arrow at the coordinates (x,y)
 
 do{
      
      ch1=getch();
                    
      if(ch1== ENTER_KEY)// if the user has selected an option by clickin "ENTER KEY", the function will return the corresponding value to an option
      return k;
                    
      if(ch1!=224)  //first of the two ascii codes returned by the arrow keys
      continue;     //the first code is 224, and if ch1!=224, the compiler will
                   //keep expecting only arrow keys and enter key
                                   
      ch2=getch();  //second getch() for arrow keys
                  
      if((ch2==UP || ch2==LEFT) && i>y)//if up/left arrow key is pressed
      {
         
         g(x,i);
         printf("    ");// delete previous arrow
                                
         g(x,i-=2);
         printf("<%c%c%c",196,196,196);// draw next arrow
         k--; //on moving the arrow up, decrement value of k by 1
         
     }//end of if
                    
     if((ch2==RIGHT || ch2==DOWN) && i<=y+n)//if right/down arrow key is pressed
     {  
         g(x,i);
         printf("    ");              //remove arrow           
         
         g(x,i+=2);                 //increment Y coordinate by 2 (i.e go down)
         printf("<%c%c%c",196,196,196);  //print arrow again
         k++;                     //increment k by 1
     
     }//end of if
     
 }while(ch1);//end of do-while
     
}//end of function


void ask_for_levels()
{
    g(40,10);
    printf("SELECT A LEVEL");
    g(40,11);
    printf("--------------");
    
    g(44,20);
    printf("%c EASY",254);
    g(44,22);
    printf("%c HARD",254);
    g(44,24);
    printf("%c BACK TO MAIN MENU",254);
    
    int user_choice=key_cursor(65,20,2);//call the function, which will return a value corresponding to the given options
    
    if(user_choice==3)  //if "BACK TO MAIN MENU" is selected, call main() again
    {
      system("cls");
      fflush(stdin);
      main();
    }
    
    system("cls");
    play_level(user_choice);
}

void play_level(int level)
{
     g(53,8);
     
     if(level == 1) //if EASY level is chosen 
     printf("LEVEL - EASY");
     
     else
     printf("LEVEL - HARD");//if HARD level is chosen
     
     g(53,9);
     printf("------------");
     
     draw_GRID();              //create the GRID for the game
     
     fill_GRID(level);         //fill up the numbers to create the problem 
     
     begin_game(level);        // start game
     
     end_game_message();       // display message , if the game has been completed
}

void draw_GRID()
{
     
     int i,j,l=221;
     
     g(93,17);
     printf("- PRESS P (or p) to pause");
     g(93,18);
     printf("  the game and view options");
     
     g(93, 20);
     printf("- PRESS 0 to erase an entry");
     
     g(93, 22);
     printf("- Use ARROW KEYS to scroll");
     g(93,23);
     printf("  through the cells");
     
     l=221;
     int k=222;
     for(i=16;i<=51;i++)
     {
        g(35,i);
        printf("%c",k);
        g(53,i);
        printf("%c",k);
        g(71,i);
        printf("%c",l);
        g(89,i);
        printf("%c",l);
     }
     l=220;
     
     for(i=36;i<=88;i++)
     {
           g(i,15);
           printf("%c",l);
           g(i,27);
           printf("%c",l);
           g(i,39);
           printf("%c",l);
           g(i,51);
           printf("%c",l);
     }
     k=179;
     for(i=41;i<=89;i+=6)
     for(j=16;j<=50;j++)
     {
         if(i==53 || i==71 || i==89)
         continue;
         
         if(j==27 || j==39)
         continue;
         
         g(i,j);
         printf("%c",k);
     }
     
     
     for(i=36;i<=88;i++)
     for(j=19;j<=51;j+=4)
     {
         if(j==27 || j==39 || j==51)
         continue;
         
         if(i==53 || i==71)
         continue;
         
         if(j==19 || j==23 || j==31 || j==35 ||j==43 || j==47)
         if(i==41 || i==47 || i==59 || i==65 || i==77 || i==83)
                  continue;
                  
         if(j==23)
         if(i==41 || i==47 || i==59 || i==65 || i==71 || i==83)
                  continue;
         g(i,j);
         printf("%c",196);
     }
     
}

void fill_GRID(int level_selected)
{
     fflush(stdin);
     
     char game_code; //every game in the problem file begins with a game code (eg a,b,c,d,e)
     
     if(level_selected ==1 && !resume_status)
     {
                       ++E;
                       
                       if(E==102)
                       E=97;
                       
                       game_code=E;
     }
     
     if(level_selected ==2 && !resume_status)
      {                 
                       ++H;
                       
                       if(H==108)
                       H=103;
                       
                       game_code=H;
      }
     
     FILE *fp;  //file pointer
     
     int X=0,Y=0; //coordinates 
     
     if(resume_status)         //if a saved game has been chosen to resume
     {
         struct store s;
        fp= fopen("SUDOKU_SAVE_FILE.dat","rb");
        
        if(fp == NULL)
        printf("\nERROR WHILE OPENING THE DATA FILE!!!!!!!!\n");
        
        while( fread (&s, sizeof(s), 1, fp))
        {
        game_code= s.game_code;
        break;
        }
        
        if(game_code == E)
        E+=2;
        
        if(game_code == H)
        H+=2;
        
        fclose(fp);
     }
                   
     fp=fopen("SUDOKU_PROBLEMS_FILE.txt","r");   //opening text file, which holds the numbers for the problem
     
     if(fp==NULL)
     printf("\nERROR WHILE OPENING THE DATA FILE!!!!!!!!\n");
        
     
     char ch;
     
     init_matrix();   //initialize matrix , with every value = 0
     
     while( ( ch=fgetc(fp) ) != EOF)  //reading from file, one character at a time
     {
            if(ch==game_code)
            {
                       while( isdigit( ch = fgetc(fp)) ) 
                       {
                              
                       put_value_in_cell(ch,Y,X);      //places the value read from file, at the position w.r.t to cell
                       GRID[X][Y]=ch-'0';              //filling up the matrix simultaneously with the problem values
                       
                       ++X;               //incrementing X so that numbers will be filled column wise
                       
                       if(X==9)          //when X reaches maximum limit for a column (i.e 9)
                       {                 
                       X=0;             // make X=0 for a new column, and increment Y to move to a new column     
                       ++Y;
                       }
                       }//end of inner while loop
                       
            break;// once this game has been loaded, break out of the loop
                 
            }
     
     }//end of outer while loop
     
     fclose(fp);
     
     fflush(stdin);
     
     add_solutions_to_SLL(game_code);   //this function will add all the solutions of the current game to the SLL
     
     if(resume_status)
     fill_previous_numbers();
}

void init_matrix()
{
     for(int i=0;i<9;i++)
     for(int j=0;j<9;j++)
     GRID[i][j]=0;
     
}

void put_value_in_cell(char ch, int X, int Y)
{

     int X_coord= 38 + (X*6); //X coordinate of the number  w.r.t screen
          
     int Y_coord= 17 + (Y*4); //Y coordinate of the number w.r.t screen    
     
     
     if(ch!='0')      //0(in the file) is for blank space in the GRID, so ignoring a space and filling up only the problem numbers on the screen
     { 
     g(X_coord,Y_coord);
     SetConsoleTextAttribute(hStdout,FOREGROUND_RED);
     printf("%c",ch);
     }
                         /* the first cell of the GRID is at (38,17) with a difference of 6 units for X direction
                           and a difference of 4 in the Y- direction.
                           therefore, initially X=Y=0 for the first value, will place it at (38,17)*/  
                           
    else
    add_positions_to_SLL(X_coord , Y_coord);  //if a 0  is encountered, store it's "position" in the SLL
}


void add_positions_to_SLL(int x, int y)
{
     
     struct SLL *temp=header,*r=NULL;
     
     if(temp==NULL)
     {
                   temp=(struct SLL*)malloc(sizeof(struct SLL));
                   
                   temp->X_coordinate=x;
                   temp->Y_coordinate=y;
                   temp->value=0;
                   
                   temp->next=NULL;
                   
                   header=temp;
     }
     
     else
     {
         while(temp->next!=NULL)
         temp=temp->next;
         
         r=(struct SLL*)malloc(sizeof(struct SLL));;
         
         r->X_coordinate=x;
         r->Y_coordinate=y;
         r->value=0;
         
         r->next=NULL;
         temp->next=r;
         
     }
}
               
void fill_previous_numbers() 
{
     /* if a user has selected to resume a game, this function
       will fill all the previous numbers he previously entered,
       and have been saved as part of the saved game. */
       
     resume_status=0; 
     
     struct store s;
     FILE *fp = fopen("SUDOKU_SAVE_FILE.dat","rb"); //reading from binary file
     
     if(fp==NULL)
     printf("error!!!!!");
     
     rewind(fp);
     
     int i,j;
     
     while( fread (&s, sizeof(s), 1 , fp) )
     {
            SetConsoleTextAttribute(hStdout,FOREGROUND_INTENSITY);
            if(s.val>0){
            g(s.x, s.y);
            printf("%d",s.val);
            
            i= (s.x - 38)/6;
            j= (s.y - 17)/4;
            
            GRID[j][i]= s.val; 
            }   
     }
     
     fclose(fp);
}
                           
void add_solutions_to_SLL(char ch1)
{
     struct SLL *temp=header;
     
     char ch;
     
     int grid[9][9]= {{0, 0, 0, 0, 0, 0, 0, 0, 0},  //temporary matrix , for solving the problem
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}};
     
     fill_grid(grid);       // copy contents of GRID into grid
     
     Shiznit_Solve(grid);   //solve the current problem  
     
     for(int i=0;i<9;i++)
     {
             if (temp==NULL)
             break;
             for(int j=0;j<9;j++)
             {
                     if(GRID[j][i] == EMPTY_CELL) //storing solutions column wise
                     {
                           temp->value=grid[j][i];  //storing only the "solutions"
                           temp=temp->next;
                     }//end of if
             
             if(temp==NULL)
             break;
             }//end of for
     }//end of for
     
     fflush(stdin);   
}

void fill_grid(int grid[9][9])//copy contents of GRID in grid
{
     
     for(int i=0; i<9; i++)
     for(int j=0; j<9; j++)
     grid[i][j]=GRID[i][j];
     
}
                 
void begin_game(int level)
{
     SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY);
     
     ConCurInf.bVisible = FALSE;  //cursor off
     SetConsoleCursorInfo(hOut, &ConCurInf);
            
     int current_X=38;
     int current_Y=17;
     
     int i,j; 
     int x,y;
     
     g(38,17);
     int key_pressed;
     
     while(1) //start solving the game.
     {
           SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY);
           get_cursor_position(&current_X , &current_Y);
           g(current_X, current_Y);
           
            x=current_X-1;  
            y=current_Y+1;
            
            g(x, y);
            printf("___");// printing a temporary cursor
            
            g(current_X, current_Y);
            
            key_pressed=getch();
            
            if(key_pressed == 'P' || key_pressed == 'p')    //pressing P or p to pause the screen
            {
                 x=current_X;
                 y=current_Y;
                 delete_temp_cursor(x,y);
                 
                 if( pause_screen_options(level) )          //if returned value is TRUE, the while loop breaks and function ends
                 break;
                 
                 else
                 g(current_X,current_Y);
            } 
            /*the value (for the above function) returned is TRUE only in two cases, if the game 
            ends completely and correctly, or if the user decided to "SOLVE" the game*/
            
                
            else if( isdigit(key_pressed) )                //if a number (between 0-9) is pressed
            {
                 get_cursor_position(&current_X , &current_Y); //get current cursor position
                 
                     if( check_coordinates(current_X , current_Y) ) //check if the cell is empty or not
                     {
                     i = (current_X - 38) / 6;      
                     j = (current_Y - 17) / 4;
                     
                     if(key_pressed =='0')                 // if 0 is pressed, put an empty space on that position
                     printf(" ");
                     
                     else                                  // else, put that number in that cell, and store it to the GRID
                     printf("%c",key_pressed);
                     
                     GRID[j][i] = key_pressed-'0';  //if it is a number, put that number in GRID
                                                    //if 0 is pressed, change cell value to 0
                     }//end of if
                   
                   g(current_X,current_Y);//keep the cursor at the same position after a key has been pressed
            
            }//end of else-if  
            
            if(key_pressed!=224)continue;
            
            else{
                 key_pressed=getch(); //second getch() for arrow keys
                 
                 get_cursor_position(&current_X , &current_Y);
                 
                 switch (key_pressed)
                 {
                        case UP :
                             if(check_limit(UP, current_X, current_Y)) //checking that the cursor does not cross the grid boundaries
                             {
                             delete_temp_cursor(current_X, current_Y); // deleteing temporary cursor
                             g(current_X, current_Y - 4);
                             }
                             break;
                             
                        case RIGHT :
                             if(check_limit(RIGHT, current_X, current_Y))
                             {
                             delete_temp_cursor(current_X, current_Y);
                             g(current_X + 6, current_Y);
                             }
                             break;
                             
                        case DOWN :
                             if(check_limit(DOWN, current_X, current_Y))
                             {
                             delete_temp_cursor(current_X, current_Y);
                             gotoxy(current_X, current_Y + 4);
                             }
                             break;
                             
                        case LEFT :
                             if(check_limit(LEFT, current_X, current_Y))
                             {
                             delete_temp_cursor(current_X, current_Y);
                             gotoxy(current_X - 6, current_Y);
                             }
                             break;
                 }//end of switch case
            
            }//end of else
                 
     }//end of while           
            
}           

int pause_screen_options(int level)
{
    SetConsoleTextAttribute(hStdout , FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    
    ConCurInf.bVisible = FALSE; //cursor off
 
    SetConsoleCursorInfo(hOut, &ConCurInf);
     
     int current_X=0, current_Y=0;
     int x=0,y=0;
     
     get_cursor_position(&current_X , &current_Y);
     
     
     g(10,30);
     printf("%c RESUME",254);
     g(10,32);
     printf("%c CHECK",254);
     g(10,34);
     printf("%c SOLVE",254);
     g(10,36);
     printf("%c NEW GAME",254);
     g(10,38);
     printf("%c EXIT",254);
     
     int user_choice=key_cursor(23,30,6);
     
     get_cursor_position(&x,&y);
     
     while((x--)>=21)  //remove the arrow after the option has been selected
     {
     g(x,y);
     printf(" ");
     }
     
     if(user_choice==1)
       return 0;
     
     if(user_choice==2)
     return check_GRID(current_X, current_Y);
     
     if(user_choice==3)
     {
        print_GRID_solution(level);
        return 1;
     }
     
     if(user_choice==4)
     {
        system("cls");
        
        free_SLL(); // clear contents of SLL
        
        play_level(level);
     }
                       
     if(user_choice==5)
     {
                       g(18,40);
                       printf("YES");
                       g(18,42);
                       printf("NO");
                       
                       user_choice= key_cursor(22,40,0);
                       
                       get_cursor_position(&x,&y);
                               
                       if(user_choice == 2)           //if the user doesn't want to quit, return back to the game
                       {
                                         g(18,40);
                                         printf("            "); // hiding 'YES'
                                         g(18,42);
                                         printf("            ");// hiding  'NO'
                                         g(current_X, current_Y);
                                         return 0;
                       }//end of if
                       
                       if(user_choice == 1)         //ask if the user wants to save the game
                       {
                                      system("cls");
                                      
                                      g(30,10);
                                      printf("DO YOU WANT TO SAVE THIS GAME??");
                                      
                                      g(34,12);
                                      printf("YES");
                                      g(34,14);
                                      printf("NO");
                                      
                                      user_choice=key_cursor(38,12,0);
                                      
                                      if(user_choice==2)
                                      exit(0);
                                      
                                      if(user_choice==1)
                                      save_current_game(level);
                                      
                       }//end of if
                                      
     } //end of if                              
}

void delete_temp_cursor(int x, int y)
{
         --x;
         ++y;
         
         gotoxy(x,y);
         printf("   ");
         }    
void get_cursor_position(int *x, int *y)  //function to get the coordinates of the current cursor position
{ 
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE); 
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo)) 
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
		
	*x = screenBufferInfo.dwCursorPosition.X; 
	*y = screenBufferInfo.dwCursorPosition.Y;
}

int check_coordinates(int x,int y) 
{
    
    struct SLL *temp=header;       /*checks if the cell at (x,y) holds a problem number or not.
                                            returns 1 if the cell is to be filled or has a solution number
                                            returns 0 if it is a problem number*/
    while(temp!=NULL)  
    {
       
          if(temp->X_coordinate==x && temp->Y_coordinate==y)
          return 1;
          
          temp=temp->next;
    }
    
    return 0;
}

int check_limit(int arrow_key, int x, int y)
{
    if(arrow_key == UP    && y==17)          //limit of UP arrow key
    return 0;
    
    if(arrow_key == LEFT  && x==38)         //limit of LEFT arrow key
    return 0;
    
    if(arrow_key == DOWN  && y==49)        //limit of DOWN arrow key
    return 0;
    
    if(arrow_key == RIGHT && x==86)        //limit of RIGHT arrow key
    return 0;
    
    return 1;    
}
                 
int check_GRID(int current_X, int current_Y) 
{
     /* functions traverses the matrix, and does one of the three things:
                  1. if the numbers filled by the user are correct ( if the game is yet not complete)
                     it will place the cursor to the "last" unsolved cell.
                     
                  2. if there is a wrong value in a cell, it places the cursor in that cell.
                  
                  3. if the game is complete, and all the numbers have been filled correctly, the user
                     is declared the winner, and the game ends. */
     
     int i,j, user_choice=1;
     int counter=0;

     struct SLL*temp=header;
     
     while(temp!=NULL)
     {
                      i= (temp->X_coordinate - 38)/6;
                      j= (temp->Y_coordinate - 17)/4;
                      
                      if(GRID[j][i] == 0 && counter!=2) //when counter==2, a cell with a wrong value has been found, therefore it will stop looking for empty cells.
                      counter=1;                    
                      
                      if(GRID[j][i]!=0 && GRID[j][i] != temp->value)// if an incorrect value(s) is/are found, then display value(s) in red color
                      {
                      counter=2;
                      i = (temp->X_coordinate - 38) / 6;
                      j = (temp->Y_coordinate - 17) / 4;
                      g(temp->X_coordinate, temp->Y_coordinate);
                      SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_RED);//pointing every incorrect value with color red
                      printf("%d",GRID[j][i]);
                      }
                      
                      temp=temp->next;
                      
     }//end of while loop
     
     /*at the end of the above loop, 'counter' can have either of the 3 values
       if counter=0 , then, the game has been solved correctly and completely.
       
       if counter=1, then, the numbers uptil that point have been filled corectly,
        but there are unfilled cells
        
       if counter=2, there is a cell with a wrong value.*/
       
    if(counter==0)
    {
                  system("cls");
                  g(40,25);
                  printf("WELL DONE, YOU HAVE SOLVED THE GAME CORRECTLY !!!!"); 
                  
                  free_SLL();       
                  
                  return 1; //returning TRUE if the game has been solved correctly and completely.
    }//end of if
    
    
    g(current_X, current_Y);  //return back to the position, from where the game was paused
    return 0;  
}


void end_game_message()
{
       ConCurInf.bVisible = FALSE; //cursor off
 
       SetConsoleCursorInfo(hOut, &ConCurInf);
     
     g(40,28);
     printf("%c MAIN MENU",254);
     g(40,30);
     printf("%c CHANGE LEVELS",254);
     g(40,32);
     printf("%c EXIT",254);
     
     int user_choice=key_cursor(57,28,2);
     
     if(user_choice ==1)
     {
         system("cls");
         free_SLL();
         main();
     }
     
     if(user_choice==2)
     {
        system("cls");
        ask_for_levels();
     }
     
     if(user_choice==3)
     exit(0);
}

void print_GRID_solution(int level)
{
     int l=254;
     
     struct SLL*temp=header;
     
     while(temp!=NULL)
     {
                      g(temp->X_coordinate, temp->Y_coordinate);
                      printf("%d",temp->value);
                      
                      temp=temp->next;
     }
     
     free_SLL();
     
     g(10,30);
     printf("         ");
     g(10,32);
     printf("         ");
     g(10,34);
     printf("%c MAIN MENU",l);
     g(10,36);
     printf("%c NEW GAME",l);
     g(10,38);
     printf("%c EXIT",l);
     
     int user_choice= key_cursor(23,34,2);
     
     if(user_choice==1)
     {
            system("cls");
            main();
     }
     
     if(user_choice==2)
     {
        system("cls");
        play_level(level);
     }
     
     if(user_choice==3)
     exit(0);
}

int Shiznit_Solve(int grid[9][9])
{
    int r, c,num;
 
    if (!find_empty_cell(grid, &r, &c)) //if all cells are complete, return TRUE
       return 1; 
 
    for (num = 1; num <= 9; num++)
    {
        if (check_if_possible(grid, r, c, num))
        {
            grid[r][c] = num;
 
            if (Shiznit_Solve(grid))
                return 1;
 
            grid[r][c] = EMPTY_CELL;//if the earlier number didn't work, start with another number
        }
    }
    return 0; // backtracking (recursively)
}

int find_empty_cell(int grid[9][9],int *r, int *c)
{
    int i=*r;
    int j=*c;
    for (i=0; i<9;i++)
    for (j=0;j<9;j++)
    if (grid[i][j] == EMPTY_CELL)
    {
    *r=i;
    *c=j;               
    return 1;
}
    return 0;
    
}


int check_row(int grid[9][9], int r, int num)
{
    for (int c = 0;c<9;c++)
        if (grid[r][c] == num)
            return 1;
    return 0;
}

int check_col(int grid[9][9],int c, int num)
{
    for (int r=0;r<9;r++)
        if (grid[r][c] == num)
            return 1;
    return 0;
}

int check_box(int grid[9][9], int box_first_row, int box_first_col, int num)
{
    for (int r= 0;r<3;r++)
        for (int c=0;c<3;c++)
            if (grid[r+box_first_row][c+box_first_col] == num)
                return 1;
    return 0;
}

int check_if_possible(int grid[9][9],int r, int c, int num)
{

    return (!check_row(grid,r, num) && !check_col(grid,c, num) && !check_box(grid, r - r%3 , c - c%3, num));
}


void save_current_game(int level)
{
     
     FILE *fp = fopen("SUDOKU_SAVE_FILE.dat","wb"); //opening binary file
     
     if(fp==NULL)
     printf("error, while opening file!!!!!!!!!!");
     
     struct SLL* temp= header;
     
     struct store s;
     
     int i,j;
     
     rewind(fp);
     
     if(level ==1)  
     s.game_code=E;
     
     if(level==2)
     s.game_code=H;
     
     int check=0;
     
     while(temp!=NULL)
     {
                      i= (temp->X_coordinate - 38) /6; // reading from SLL, which stores the position and value of each solution cell  
                      j= (temp->Y_coordinate - 17) /4;   
                      
                      if(GRID[j][i]) //if a user has filled a solution cell, we need to store it, in order to display them when the user decides to resume the game
                      {
                                    s.x=temp->X_coordinate;  //storing x- coordinate
                                    s.y=temp->Y_coordinate;  // storing y- coordinate
                                    s.val= GRID[j][i]; // storing the value
                                    
                                    fwrite(&s, sizeof(s), 1, fp); // saving to binary file
                      }//end of if
                      
                      temp=temp->next;
     }//end of while
      
      if(!check) //if the user didn't enter any number
      {
      s.val=s.x=s.y=0;
      fwrite(&s, sizeof(s), 1, fp);
      }
      fclose(fp); 
      system("cls");
      g(39,22);
      printf("YOUR GAME HAS BEEN SAVED !!!");   
     free_SLL();
}

