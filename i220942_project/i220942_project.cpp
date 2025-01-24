/*
   Name : Muhammad Umar Hassan
   Roll_No : 22i-0942
   Class : CS-H
         Project
*/



/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace std;
using namespace sf;

int main(){
    srand(time(0));
   
    ////////////////////Rendering Window and Loading Files////////////////////
    
    RenderWindow window(VideoMode(320, 480), title1);
    Texture obj1, obj2, obj3;  //Declare variables for Textures  
    obj1.loadFromFile("img/tiles.png");	
    obj3.loadFromFile("img/frame.png");	 			  //Loading Files
     obj2.loadFromFile("img/background.png");
     
     Texture  t , nb ,b , men, help, HS , p , go, lev;     //Declare variables for Textures  
      t.loadFromFile("img/shadow.png");
      nb.loadFromFile("img/tiles.png");
      b.loadFromFile("img/tiles.png"); 
      men.loadFromFile("img/Menu.png");
      help.loadFromFile("img/Help.png");
      HS.loadFromFile("img/High_score.png");
      p.loadFromFile("img/pause.png");
      go.loadFromFile("img/Game_over.png");
      lev.loadFromFile("img/Game_level.png"); 
       Font font;	
      font.loadFromFile("img/text.otf");
      
    Sprite sprite(obj1), background(obj2), frame(obj3);
    Sprite shadow(t), next_b(nb), bomb(b) , Menu(men), Help(help), hs(HS) , pause(p), game_over(go), level(lev);
                                                            //Assigned Different Variables of pages
                                                            
   ///////////////////////Declaring Early variables/////////////                                                         
    
    int delta_x=0, colorNum=1, colorNext=1;  //colorNum=1--7
    float timer=0, delay=0.3;
    bool rotate=0,hard=0,bomb_state1=0,bomb_state=0;
    Clock clock;
   
    next_piece();				///Making Next Piece
    colorNext=1+rand()%7;			//assigning color of Nect piece
    
    
    float overall_time=0; 			////Variable for Kepping track of playing time
    int con=0,h=0,score=0,Game=0,wait=0,gameover=0,Gam=0,bombcount=1;  // some conditions for Drawing pages
    
    
  while(window.isOpen()){
  
    
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
         timerbomb=timer;
         
         if(overall_time>=600 || g_level==2)				///Condition for Increaing Speed wile playing
           {
             delay=0.2;
           }
         
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();
                                          //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                   
               else if(e.key.code==Keyboard::H)                ///Display Help Page     
                {
                 h=1;
               	 con=1;
       		     }      
       		else if(e.key.code==Keyboard::S)               ///Display  Score page      
       	       { 
       	         score=1;
       	           con=1;
       	       }          
       	       else if( e.key.code==Keyboard::B)              ///Come Back from pages
       	       {
       	              con=0;    
       	               h=0;
       	               score=0;  
       	 	}   
              else if(e.key.code==Keyboard::N)               ///For starting New game      
              {
               
                 game_level=1;                
                   Game=1;
                   Gam=1;
                   Game_over();
                   wait=0;                     
                   gameover=0;   
                   Game_score=0;        
                   overall_time=0;     
                   bombcount=1;  
              }
              else if(e.key.code==Keyboard::Escape)                     //To Exit Window
                   window.close();       
              else if(e.key.code==Keyboard::P)  			//To Pause the game
              {
                   wait=1;                  
               } 
              else if(e.key.code==Keyboard::C) 				//To continue the game
               {
                  wait=0;
               } 
              else if(e.key.code==Keyboard::M)				//To go to Menu After game over
                {
                  con=0;
                  Game=0;
                }
                else if (e.key.code == Keyboard::Num2)   		///Deciding Game Level
                {      
                    g_level=2;
                    game_level=0;       //Game level page status                
                 }   
                else if (e.key.code == Keyboard::Num1)  		///Deciding Game Level
               {    
                    g_level=1;
                    game_level=0;
               } 
               else if (e.key.code == Keyboard::Space)
                    hard=1;  
               else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                     
                  	     
       	      }
       	      
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
         
        

       
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
        ////////////////////Game Functions/////////////////////
        if(Gam==1&&wait==0&&game_level==0)		//Start Game if Conditions are fulfilled
        {
            if (overall_time/500==1&&bombcount<=4)                      //for sending bomb
                 {
                    bomb_state1=1;
                    bomb_state=1;   
                    colorbomb=1+rand()%7;
                    bombcount++;
                  }  
      
          
         						
          if(hard)					//Condition for Hard Drop
          {
            delay=0;
          }
           fallingPiece(timer,delay,colorNum,hard,time,colorNext);       //Calling Faling Piece Function
            move(delta_x);							//Caling Move Function
            rotate_blocks(rotate);  						//Caling Rotate Function
                  
           if(!anamoly())							//For Game over
            {
             gameover=1;
            }
            check_lines();   							//For Destroying Complete Lines
            reset_values(rotate,delta_x);					//For reseting Basic Conditions
          shadow_state();							//For checking Shadow Status
          
          if(overall_time<600&&g_level==1)							//For reset Delay for 1st Part 
            delay=0.3;
         if(overall_time>=600||g_level==2)						//For reset delay of First Part
            delay=0.2;
          
           if(bomb_state1)							//For Bomb Function
         {
            bomb_create();							//Calling Bomb Function
         } 
         if(bomb_state)								//For Falling Bomb if It is Present																																													
         bomb_fall(bomb_state);          
         bomb_state1=0;								//For falsinf !st condition of bomb
         
         
         
         overall_time+=0.01;							//For  Increamenting The Game Time
         
         }
               //Example: fallingPiece() function is called here
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        
        
        ///////////////////////////////////Drawing Pages and Blocks///////////////
        window.clear(Color::Black);					//Clearing The Window
        window.draw(background);					//Drawing BackGround
        
        if(Game==1&&wait==0&&game_level==0)
        {
        window.draw(frame);						//Drawing Frame
        
        //////////////////////Drawing Game Grid//////////////
        for(int i=0;i<M;i++){
           for(int j=0;j<N;j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        /////////////////////////////////assigning color //////////////////////
        next_b.setTextureRect(IntRect(colorNext*18,0,18,18));
        shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
        sprite.setTextureRect(IntRect(colorNum*18,0,18,18)); 
        bomb.setTextureRect(IntRect(colorbomb*18,0,18,18));
        for(int i=0;i<4;i++)
          {
            ///////////////Drawing Next block///////////////////
            next_b.setPosition(next_block[i][0]*18+180,next_block[i][1]*18+170);
          
  
        //////////////////////////////////Drawing shadow///////////////////////////
            
            shadow.setPosition(point_1[i][0]*18+28,shadow_block[i][1]*18+30);
                     
         /////////////////////Drawing blocks/////////////            
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);sprite.move(28,31);
                  ////////////draiwing on window/////////
            window.draw(next_b);
             window.draw(shadow); 
            window.draw(sprite);         
          }
           ////////////////////////////////////Drawing bomb block///////////////////////
           
           bomb.setPosition(bomb_block[0][0]*18+(28),bomb_block[0][1]*18+30);
        if(bomb_state)
           {         
            window.draw(bomb);
           }      
             ////////////////////////////Displaying score//////////////////////
           Text t;  
            t.setFont(font); 
            t.setCharacterSize(30);     
            t.setFillColor(Color::White);
                      
            t.setString(to_string(Game_score));  
            t.setPosition(250,300);        
            window.draw(t);
            
            /////////////////////////////Displaying gameover///////////////////
          if(gameover)
          {
            window.draw(game_over);
            Gam=0;
            con=1;
          }
          
        }
        
        if(con==0&&Game==0&&game_level==0)
       window.draw(Menu);                        ////////Drawing menu////////// 
      else if (h) 
        window.draw(Help);                      ////////Drawing help//////////
      else if(score)
      {
         window.draw(hs);                       //////// Drawing score////////
            Text t;  
            t.setFont(font); 
            t.setCharacterSize(30);     
            t.setFillColor(Color::White);
            
            
                                                      
            t.setString(to_string(High_score));
            t.setPosition(150,155);
            
            window.draw(t);
         
      }   
      else if(wait==1)
         window.draw(pause);                          ////////////Drawing pause menu//////////
      else if(game_level)
      {
         window.draw(level);                         //////// Drawing level/////////////
                    
      }     
          
        //---The Final on Which Everything is Drawn Over is Loaded---//
        
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
