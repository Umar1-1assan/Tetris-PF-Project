
/*
   Name : Muhammad Umar Hassan
   Roll_No : 22i-0942
   Class : CS-H
           Project
*/   
    
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

using namespace sf;
void next_piece();
void scoring(int l);
void bomb_create();
bool bomb_anamoly();
void bomb_function();
void shadow();
bool bcreate_anamoly();

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum,bool& hard,float& time, int& colorNext){
    if (timer>delay){
        int i=0;
        while(i<4){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            i++;
        }

       i=0;
       while(i<4)
       {
         point_1[i][1]++;             //How much Units Downwards
         i++;
       }

        if (!anamoly()){
        
           hard=0;
            int i=0;
            while(i<4)
            {
                   gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
                   i++;
            }
          colorNum=colorNext;
           

            //--- Un-Comment this Part When You Make BLOCKS array---//

                 i=0;
                 while(i<4){
                   point_1[i][1] = next_block[i][1];
                    point_1[i][0] = next_block[i][0];
                    i++;
                }
		colorNext=1+rand()%7;
           next_piece();


        }
        timer=0;
    }


}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

////////////////// Move the block //////////////////////////
  void move(int &delta_x)
  {
    int i=0;
    while(i<4)
    {
      point_2[i][1]=point_1[i][1];                   //Save coordinates 
      point_2[i][0]=point_1[i][0];
      i++;
    }
    i=0;
     while (i<4) {
       point_1[i][0]+=delta_x; 				//chage in x axis
       i++;
     }

    if(!(anamoly()))
    {
        int i=0;
        while(i<4)
         {
           point_2[i][1]=point_1[i][1]; 		///check and assigns previous coordinates if true
           point_2[i][0]=point_1[i][0];

           i++;
         }
     }

  }

 ///////////////////// Rotate the block /////////////////////////
  void rotate_blocks(int rotate)
   {
     if(rotate)
        {
          int p[2]={point_1[1][0],point_1[1][1]},x,y;				//stores cordinates of midlle blocks
           int i=0;
           while(i<4)
             {
                x=point_1[i][1]-p[1];						//temporary stores in x,y after changing
               y=point_1[i][0]-p[0];
               point_1[i][0]=p[0]-x;						//final transformation
               point_1[i][1]=p[1]+y;					
               i++;
             }
        }
      if(!(anamoly()))
      {
        int i=0;
        while(i<4)
         {
           point_2[i][1]=point_1[i][1];
           point_2[i][0]=point_1[i][0];						///check and assigns previous coordinates if true
           i++;
         }
      }
   }
 ///////////////////////// Check lines ///////////////////////
   void check_lines()
   {
   int l=0;
     int k=M-1;								//Checks through the whole Grid
       for(int i=M-1;i>0;i--)
        {
          int cnt=0;
          for(int j=0;j<N;j++)				
           {
             if(gameGrid[i][j])
               cnt+=1;
             gameGrid[k][j]=gameGrid[i][j];				//moves blocks downward if lines are removed
           }

           if(cnt<N)
           k--;
           else if(cnt==N)						//count lines for scoreing
            l++;
        }
        scoring(l);							//calling scoring function


   }
 //////////////////////// Reset values //////////////////////
   void reset_values(bool& rotate, int& delta_x)
   {
         rotate=0;
         delta_x=0;
   }


///////////////// Game over /////////////////////
void Game_over()
{
 int n;

    g_level==2?n=rand()%7:n=rand()%4;					//Firslty assigns new coordinates to block

  int i=0;
  while(i<4)
  {
   point_1[i][1]=BLOCKS[n][i]/2;
   point_1[i][0]=4+BLOCKS[n][i]%2;					
   i++;
   }
   i=0;
   while(i<M)
   {
      int j=0;
       while(j<N)
       {
        gameGrid[i][j]={0};						//removing Game Grid
         j++;
       }
        i++;
   }
}

////////////////// Next block ////////////////
void next_piece()
{
  int n;
    g_level==2?n=rand()%7:n=rand()%4;

            int i=0;
            while(i<4){
                    next_block[i][1] = BLOCKS[n][i] / 2;
                    next_block[i][0] = 4+BLOCKS[n][i] % 2;					//Making New block
                    i++;
                }
}
//////////////////// Check condition of bomb /////////////////////
bool shadow_anamoly()
{
  int i=0;
  while(i<4)
     {
       if (gameGrid[shadow_block[i][1]][shadow_block[i][0]])  					//checks for shadow 
       return 0;
       else if (shadow_block[i][1]>=M)
        return 0;
        i++;
      }
    return 1;
}
/////////////////////// Shadow positioning /////////////////////////
void shadow_state()
 {
   int i=0;
   while(i<4)
        {
           shadow_block[i][1]=point_1[i][1];							//assgns piece to shadow
           shadow_block[i][0]=point_1[i][0];
           i++;
        }

       i=0;
      while(i<4)
       {
          while(shadow_anamoly()){
             for(int j=0;j<4;j++)							//check game Grid and changes y coordinates accordingly
                shadow_block[j][1]++;
             }
          int k=0;
          while(k<4)
          {
             shadow_block[k][1]--;
             k++;
           }
           i++;
       }
 }
 /////////// Create bomb /////////////
void bomb_create()
{
   for(int i=0;i<2;i++)									//Creates bomb on random position
  bomb_block[0][i]=rand()%10;
    if(!anamoly()&&bomb_anamoly())							//checks if position is valid
        bomb_create();
}
/////////////// BOMB WORKING ///////////////
void bomb_function(bool& bomb_state)							
{
  if(colorbomb==gameGrid[bomb_block[0][1]][bomb_block[0][0]])       			//check ing color and acting accordingly
      {
          int i=0;
  	 while(i<M)
  	 {
  	    int j=0;
  	     while(j<N)
  	     {
  	      gameGrid[i][j]={0};
  	       j++;
  	     }
  	      i++;
  		 }
      }
     else if(colorbomb!=gameGrid[bomb_block[0][1]][bomb_block[0][0]] && bomb_block[0][1]!=M)
       {
         int i=bomb_block[0][1];
         int j=bomb_block[0][0];
         gameGrid[i][j+1]=0;
         gameGrid[i+1][j]=0;
         gameGrid[i][j]=0;
       }
      bomb_state=0;
     bomb_create();


}

//////////////// Check the condition of bomb///////////////////
bool bomb_anamoly()
{
        if (gameGrid[bomb_block[0][1]][bomb_block[0][0]])				//checking condition for falling bomb
            return 0;
        else if (bomb_block[0][1]>=M)
            return 0;
    return 1;
}
///////////////// BOMB FALLING /////////////////////////
void bomb_fall(bool& bomb_state)
{
  float delay;
  delay=0.3;
  if(timerbomb>delay)									//falling bomb as in given code
  {
   bomb_block[0][1]+=1;
   if(!bomb_anamoly())							
   {
      bomb_function(bomb_state);
   }
   }

   timerbomb=0;

}
// Calculating high score ///////////
void scoring(int l)
{
      switch(l)
      {
             case 3:
                Game_score+=(60*g_level);						//adding scores based on lines removed
                break;
             case 2:
                Game_score+=(30*g_level);
                break;
             case 4:
                Game_score+=(100*g_level);
                break;
             case 1:
                Game_score+=(10*g_level);
                break;
       }
              if(Game_score>High_score)							//changing Highscore
                High_score=Game_score;					
}
  



///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
