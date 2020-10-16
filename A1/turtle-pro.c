/**
 * CSC A48 - Intro to Computer Science II, Summer 2020
 * 
 * This is the program file where you will implement your solution for
 * assignment 1. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will need to have read the handout carefully. Parts where you have to 
 * implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive and will
 * check that your solution is *correct*, not only that it provides 
 * functionality.
 * 
 * Developed by Mustafa Quraish for CSCA48
 * (c) Mustafa Quraish 2020
 */
#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode {

  char cmd[10];
  int val;
  struct cmdnode* next;
  struct cmdnode* loop_head;

} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */


  // creating new CmdNode
  CmdNode* new = (CmdNode*)calloc(1, sizeof(CmdNode));

  // checking if it is a valid command
  if(strcmp(cmd, "penup") == 0 || strcmp(cmd, "pendown") == 0 || strcmp(cmd, "left") == 0 || strcmp(cmd, "loop") == 0 || 
     strcmp(cmd, "right") == 0 || strcmp(cmd, "forward") == 0 || strcmp(cmd, "backward") == 0 || strcmp(cmd, "colour") == 0){
    
    // setting the values given to the new CmdNode
    strcpy(new -> cmd, cmd);
    new -> val = val;
    new -> next = NULL;
  
  }else{

    // print Invalid command if the values are invalid
    printf("Invalid command.\n");
    return NULL;
  }

  return new; // returns the new CmdNode
}

/*---------------------------------------------------------------------------*/

void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */


  int line = 0;

  // looping through the entire linked list
  while(head != NULL){
    
    if(strcmp(head -> cmd, "right") == 0 || strcmp(head -> cmd, "left") == 0 ||  strcmp(head -> cmd, "penup") == 0 || strcmp(head -> cmd, "pendown") == 0){

      // printing for commands without values
      printf("%3d: %s\n", line, head -> cmd);
      line++;
    }else if(strcmp(head -> cmd, "loop") == 0){
      printf("%3d: %s %d\n", line, head -> cmd, head -> val);
      line++;

      CmdNode* p = head -> loop_head;
      while(p != NULL){
        if(strcmp(p -> cmd, "right") == 0 || strcmp(p -> cmd, "left") == 0 ||  strcmp(p -> cmd, "penup") == 0 || strcmp(p -> cmd, "pendown") == 0){

        // printing for commands without values
          printf("  %3d: %s\n", line, p -> cmd);

        }else{

          // printing for commands with values
          printf("  %3d: %s %d\n", line, p -> cmd, p -> val);

        }
        p = p -> next;
        line++;
      }
    }else{

      // printing for commands with values
      printf("%3d: %s %d\n", line, head -> cmd, head -> val);
      line++;
    }

    head = head -> next;
    
  }

  return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */

  // current line number
  int line = 0;

  // loops through the entire linked list
  while(head != NULL){
    
    // checks if the current command is the same as the one being searched
    if(strcmp(head -> cmd, cmd) == 0){

      if(strcmp(head -> cmd, "right") == 0 || strcmp(head -> cmd, "left") == 0 ||  strcmp(head -> cmd, "penup") == 0 || strcmp(head -> cmd, "pendown") == 0){

        // printing for commands without values
        printf("%3d: %s\n", line, head -> cmd);
        line++;
      }else{

        // printing for commands with values
        printf("%3d: %s %d\n", line, head -> cmd, head -> val);
        line++;
      }
    }else if(strcmp(head -> cmd, "loop") == 0){
      line++;
      CmdNode* p = head -> loop_head;
      while(p != NULL){
        if(strcmp(p -> cmd, cmd) == 0){
          if(strcmp(p -> cmd, "right") == 0 || strcmp(p -> cmd, "left") == 0 ||  strcmp(p -> cmd, "penup") == 0 || strcmp(p -> cmd, "pendown") == 0){

            // printing for commands without values
            printf("%3d: %s\n", line, p -> cmd);

          }else{

            // printing for commands with values
            printf("%3d: %s %d\n", line, p -> cmd, p -> val);

          }
        }
        line++;
        p = p -> next;
      }
    }else{
      line++;
    }
    head = head -> next;

  }

  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */

  // line number counter
  int line = 0;

  // loops through entire linked list
  while(head != NULL){
    line++;
    if(head -> loop_head != NULL){
      CmdNode* p = head -> loop_head;
      while(p != NULL){
        line++;
        p = p -> next;
      }
    }
    head = head -> next;
  }

  return line;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */

  CmdNode* old = head;

  // loops through entire linked list until the last one
  if(head != NULL){
    while(head -> next != NULL){
      head = head -> next;
    }
  }

  // for the case when head is NULL
  if(head == NULL){
    old = new_CmdNode;
  }else{
    head -> next = new_CmdNode;
  }

  return old;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommandBefore(CmdNode *head, CmdNode *new_CmdNode, int cmdNum) {
  /**
   * This function inserts a new node *before* a given Node in the linked list. 
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to insert new_CmdNode 
   * *before* the corresponding node in the linked list.
   *
   * --------------------------------------------------------------------------
   *  
   * For instance, if your initial list was
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * And you added "pendown" before cmdNum = 2, then you will have
   * 
   *    0: penup
   *    1: forward 200
   *    2: pendown
   *    3: right
   *    4: forward 50
   * 
   * --------------------------------------------------------------------------
   * 
   * If there is no command with the given cmdNum (cmdNum >= list size), 
   * then print "Invalid Command Number.\n" to the screen and *do not* 
   * insert the new node.
   * 
   * Returns a pointer to the head of the linked list with the new node added 
   * into it.
   * 
   * TODO: Implement this function
   */


  
  CmdNode* prev = NULL;
  CmdNode* old = head;

  // gives error message if cmdNum is out of bounds
  if(cmdNum >= countCommands(head)){
    printf("Invalid Command Number.\n");
  }else{

    // going to the desired command
    for(int i = 0; i < cmdNum; i++){
      prev = head;
      head = head -> next;
    }
    // insert the new node into the linked list
    if(prev != NULL){
      // for the case when inserting not at head
      prev -> next = new_CmdNode;
      new_CmdNode -> next = head;
    }else{
      // for the case when inserting at head
      new_CmdNode -> next = old;
      old = new_CmdNode;
    }
  }

  return old;
}

/*---------------------------------------------------------------------------*/

void updateCommand(CmdNode *head, int cmdNum, char cmd[10], int val) {
  /**
   * This function updates a specific node in the linked list based on the 
   * input parameters.
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to update the 'cmd' and 
   * 'val' fields of this node.
   * 
   * If there is no command with the given cmdNum, then print 
   * "Invalid Command Number.\n" to the screen, and if 'cmd' is not a correct 
   * command, then print "Invalid command.\n". In both these cases, do *not* 
   * modify the list.
   * 
   * TODO: Implement this function
   */

  int is_valid = 1;
  CmdNode* p = head;

  // checking if cmdNum is within bounds
  if(cmdNum >= countCommands(head)){

    printf("Invalid Command Number.\n");
    is_valid = 0;

  }

  // checking if cmd is a valid command
  if(!(strcmp(cmd, "penup") == 0 || strcmp(cmd, "pendown") == 0 || strcmp(cmd, "left") == 0 || 
     strcmp(cmd, "right") == 0 || strcmp(cmd, "forward") == 0 || strcmp(cmd, "backward") == 0 || strcmp(cmd, "colour") == 0)){

    printf("Invalid Command.\n");
    is_valid = 0;

  }

  // if cmd is a valid command, update the info of the selected CmdNode
  if(is_valid){
    for(int i = 0; i < cmdNum; i++){
      p = p -> next;
    }
    strcpy(p -> cmd, cmd);
    p -> val = val;
  }
  return;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommand(CmdNode *head, int cmdNum) {
  /**
   * This function deletes the node from the linked list that corresponds to 
   * the line number cmdNum. If there is no command with the given cmdNum, then 
   * the function does nothing.
   * 
   * Returns a pointer to the head of the linked list (which may have changed 
   * as a result of the deletion)
   *
   * TODO: Implement this function
   */

  CmdNode* freeing;
  CmdNode* prev;

  // check if head is empty
  if(head != NULL){
    // if the command is the head of the linked list
    if(cmdNum == 0){
      freeing = head;
      head = head -> next;
    
    // if the requested command is out of bound
    }else if(cmdNum > countCommands(head)){
      return head;
    // deleters the command
    }else{
      CmdNode* p = head;
      for(int i = 0; i < cmdNum; i++){
        prev = p;
        p = p -> next;
      }
      prev -> next = p -> next;
      freeing = p;
    }
    free(freeing);
  }

  return head;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */

  CmdNode* next;

  // checking if the linked list is empty
  while (head != NULL){
    
    // checking if the current command is a loop command
    if(strcmp(head -> cmd, "loop") == 0){

      // deletes all commands in the loop
      CmdNode* lh = head -> loop_head;
      CmdNode* loop_next;
      while(lh != NULL){
        loop_next = lh -> next;
        free(lh);
        lh = loop_next;
      }
    }

    // deletes all the commands that are not in a loop
    next = head -> next;
    free(head);
    head = next;

  }

  return NULL;
}

/*---------------------------------------------------------------------------*/


void insertCommandLoop(CmdNode* loop, CmdNode* new){

  // checking if loop is NULL
  if(loop != NULL){

    // checking if the loop head is null
    if(loop -> loop_head != NULL){
      // appending to the end of the loop
      CmdNode* p = loop -> loop_head;
      while(p -> next != NULL){
        p = p -> next;
      }
      p -> next = new;
    }else{
      // case where the command is the new loop head
      loop -> loop_head = new;
    }
  }

}


void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX
   *       - y increases as you go down, up till SIZEY
   * 
   *                 (0,0)                  (SIZEX, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *                (0, SIZEY)            (SIZEX, SIZEY)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX / SIZEY 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward 512 (or SIZEX) pixels, and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * We have already implemented a drawLine() function (in imgUtils.c) which 
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */

  // int right[2] = {1, 0};
  // int left[2] = {-1, 0};
  // int up[2] = {0, -1};
  // int down[2] = {0, 1};

  // a 2d array of direction multipliers, right, down, left, up
  int direction[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

  // current status of the turtle
  int current_dir = 0;
  int current_pos[2] = {0,0};
  int current_color = 0;
  int pen = 1;

  // loops through entire linked list
  while(head != NULL){
    // if the command is penup
    if(strcmp(head -> cmd, "penup") == 0){
      // set pen to be 0
      pen = 0;
    
    // if command is pendown
    }else if(strcmp(head -> cmd, "pendown") == 0){
      // set pen to be 1
      pen = 1;
    
    // if command is colour
    }else if(strcmp(head -> cmd, "colour") == 0){

      // set current_colour to be the given colour
      current_color = head -> val;
    
    // if command is right
    }else if(strcmp(head -> cmd, "right") == 0){

      // change the current direction to the right of the current direction
      current_dir = (current_dir + 1) % 4;
      if(current_dir < 0){
        current_dir += 4;
      }
    }else if(strcmp(head -> cmd, "left") == 0){

      // change the current direction to the left of the current direction
      current_dir = (current_dir - 1) % 4;
      if(current_dir < 0){
        current_dir += 4;
      }

    // if the command is forward
    }else if(strcmp(head -> cmd, "forward") == 0){

      // check boundaries and if all is in boundaries
      if((current_pos[0] + (head -> val * direction[current_dir][0])) < SIZEX &&
        (current_pos[1] + (head -> val * direction[current_dir][1])) < SIZEY &&
        (current_pos[0] + (head -> val * direction[current_dir][0])) >= 0 &&
        (current_pos[1] + (head -> val * direction[current_dir][1])) >= 0){

        // draw the line from old position to new position if pen is down
        if(pen){
          drawLine(im, current_pos[0], current_pos[1],
          (current_pos[0] + (head -> val * direction[current_dir][0])), 
          (current_pos[1] + (head -> val * direction[current_dir][1])), current_color);
        }

        // change from old current location to the new location
        current_pos[0] += (head -> val * direction[current_dir][0]);
        current_pos[1] += (head -> val * direction[current_dir][1]);
      }else{

        int new_pos[2] = {current_pos[0], current_pos[1]};

        // checking if x coordinate is out of bound, and set to max/min possible value
        if((current_pos[0] + (head -> val * direction[current_dir][0])) >= SIZEX){
          new_pos[0] = SIZEX-1;
        }else if((current_pos[0] + (head -> val * direction[current_dir][0])) < 0){
          new_pos[0] = 0;
        }else{
          new_pos[0] = (current_pos[0] + (head -> val * direction[current_dir][0]));
        }

        // checking if y coordinate is out of bound, and set to max/min possible value
        if((current_pos[1] + (head -> val * direction[current_dir][1])) >= SIZEY){
          new_pos[1] = SIZEY-1;
        }else if((current_pos[1] + (head -> val * direction[current_dir][1])) < 0){
          new_pos[1] = 0;
        }else{
          new_pos[1] = (current_pos[1] + (head -> val * direction[current_dir][1]));
        }


        // draws line at new values that are within the bounds
        if(pen){
          drawLine(im, current_pos[0], current_pos[1], new_pos[0], new_pos[1] ,current_color);
        }

        // updating the current position to the new position
        current_pos[0] = new_pos[0];
        current_pos[1] = new_pos[1];
      }

    // if the command is backward
    }else if(strcmp(head -> cmd, "backward") == 0){

      // check boundaries and if all is in boundaries
      if((current_pos[0] - (head -> val * direction[current_dir][0])) < SIZEX &&
        (current_pos[1] - (head -> val * direction[current_dir][1])) < SIZEY &&
        (current_pos[0] - (head -> val * direction[current_dir][0])) >= 0 &&
        (current_pos[1] - (head -> val * direction[current_dir][1])) >= 0){


        // draw the line from old position to new position
        if(pen){
          drawLine(im, current_pos[0], current_pos[1],
          (current_pos[0] - (head -> val * direction[current_dir][0])), 
          (current_pos[1] - (head -> val * direction[current_dir][1])), current_color);
        }

        // change from old current location to the new location
        current_pos[0] -= (head -> val * direction[current_dir][0]);
        current_pos[1] -= (head -> val * direction[current_dir][1]);
      }else{

        int new_pos[2] = {current_pos[0], current_pos[1]};

        // checking if x coordinate is out of bound, and set to max/min possible value
        if((current_pos[0] - (head -> val * direction[current_dir][0])) >= SIZEX){
          new_pos[0] = SIZEX-1;
        }else if((current_pos[1] - (head -> val * direction[current_dir][1])) >= SIZEY){
          new_pos[1] = SIZEY-1;
        }
        else{
          new_pos[0] = (current_pos[0] - (head -> val * direction[current_dir][0]));
        }

        // checking if y coordinate is out of bound, and set to max/min possible value
        if((current_pos[0] - (head -> val * direction[current_dir][0])) < 0){
          new_pos[0] = 0;
        }else if((current_pos[1] - (head -> val * direction[current_dir][1])) < 0){
          new_pos[1] = 0;
        }else{
          new_pos[0] = (current_pos[0] - (head -> val * direction[current_dir][0]));
        }


        // draws line at new values that are within the bounds
        if(pen){
          drawLine(im, current_pos[0], current_pos[1], new_pos[0], new_pos[1] ,current_color);
        }

        // updating the current position to the new position
        current_pos[0] = new_pos[0];
        current_pos[1] = new_pos[1];
      }

    // if the command is loop
    }else if(strcmp(head -> cmd, "loop") == 0){

      // loops through the commands inside the loop as many times as specified
      for(int i = 0; i < head -> val; i++){
        CmdNode* p = head -> loop_head;

        // looping through all the commands in the loop once
        while(p != NULL){
          // if the command is penup
          if(strcmp(p -> cmd, "penup") == 0){
            // set pen to be 0
            pen = 0;
          
          // if command is pendown
          }else if(strcmp(p -> cmd, "pendown") == 0){
            // set pen to be 1
            pen = 1;
          
          // if command is colour
          }else if(strcmp(p -> cmd, "colour") == 0){

            // set current_colour to be the given colour
            current_color = p -> val;
          
          // if command is right
          }else if(strcmp(p -> cmd, "right") == 0){

            // change the current direction to the right of the current direction
            current_dir = (current_dir + 1) % 4;
            if(current_dir < 0){
              current_dir += 4;
            }
          }else if(strcmp(p -> cmd, "left") == 0){

            // change the current direction to the left of the current direction
            current_dir = (current_dir - 1) % 4;
            if(current_dir < 0){
              current_dir += 4;
            }

          // if the command is forward
          }else if(strcmp(p -> cmd, "forward") == 0){

            // check boundaries and if all is in boundaries
            if((current_pos[0] + (p -> val * direction[current_dir][0])) < SIZEX &&
              (current_pos[1] + (p -> val * direction[current_dir][1])) < SIZEY &&
              (current_pos[0] + (p -> val * direction[current_dir][0])) >= 0 &&
              (current_pos[1] + (p -> val * direction[current_dir][1])) >= 0){

              // draw the line from old position to new position if pen is down
              if(pen){
                drawLine(im, current_pos[0], current_pos[1],
                (current_pos[0] + (p -> val * direction[current_dir][0])), 
                (current_pos[1] + (p -> val * direction[current_dir][1])), current_color);
              }

              // change from old current location to the new location
              current_pos[0] += (p -> val * direction[current_dir][0]);
              current_pos[1] += (p -> val * direction[current_dir][1]);
            }else{

              int new_pos[2] = {current_pos[0], current_pos[1]};

              // checking if x coordinate is out of bound, and set to max/min possible value
              if((current_pos[0] + (p -> val * direction[current_dir][0])) >= SIZEX){
                new_pos[0] = SIZEX-1;
              }else if((current_pos[0] + (p -> val * direction[current_dir][0])) < 0){
                new_pos[0] = 0;
              }else{
                new_pos[0] = (current_pos[0] + (p -> val * direction[current_dir][0]));
              }

              // checking if y coordinate is out of bound, and set to max/min possible value
              if((current_pos[1] + (p -> val * direction[current_dir][1])) >= SIZEY){
                new_pos[1] = SIZEY-1;
              }else if((current_pos[1] + (p -> val * direction[current_dir][1])) < 0){
                new_pos[1] = 0;
              }else{
                new_pos[1] = (current_pos[1] + (p -> val * direction[current_dir][1]));
              }


              // draws line at new values that are within the bounds
              if(pen){
                drawLine(im, current_pos[0], current_pos[1], new_pos[0], new_pos[1] ,current_color);
              }

              // updating the current position to the new position
              current_pos[0] = new_pos[0];
              current_pos[1] = new_pos[1];
            }

          // if the command is backward
          }else if(strcmp(p -> cmd, "backward") == 0){

            // check boundaries and if all is in boundaries
            if((current_pos[0] - (p -> val * direction[current_dir][0])) < SIZEX &&
              (current_pos[1] - (p -> val * direction[current_dir][1])) < SIZEY &&
              (current_pos[0] - (p -> val * direction[current_dir][0])) >= 0 &&
              (current_pos[1] - (p -> val * direction[current_dir][1])) >= 0){


              // draw the line from old position to new position
              if(pen){
                drawLine(im, current_pos[0], current_pos[1],
                (current_pos[0] - (p -> val * direction[current_dir][0])), 
                (current_pos[1] - (p -> val * direction[current_dir][1])), current_color);
              }

              // change from old current location to the new location
              current_pos[0] -= (p -> val * direction[current_dir][0]);
              current_pos[1] -= (p -> val * direction[current_dir][1]);
            }else{

              int new_pos[2] = {current_pos[0], current_pos[1]};

              // checking if x coordinate is out of bound, and set to max/min possible value
              if((current_pos[0] - (p -> val * direction[current_dir][0])) >= SIZEX){
                new_pos[0] = SIZEX-1;
              }else if((current_pos[1] - (p -> val * direction[current_dir][1])) >= SIZEY){
                new_pos[1] = SIZEY-1;
              }
              else{
                new_pos[0] = (current_pos[0] - (p -> val * direction[current_dir][0]));
              }

              // checking if y coordinate is out of bound, and set to max/min possible value
              if((current_pos[0] - (p -> val * direction[current_dir][0])) < 0){
                new_pos[0] = 0;
              }else if((current_pos[1] - (p -> val * direction[current_dir][1])) < 0){
                new_pos[1] = 0;
              }else{
                new_pos[0] = (current_pos[0] - (p -> val * direction[current_dir][0]));
              }


              // draws line at new values that are within the bounds
              if(pen){
                drawLine(im, current_pos[0], current_pos[1], new_pos[0], new_pos[1] ,current_color);
              }

              // updating the current position to the new position
              current_pos[0] = new_pos[0];
              current_pos[1] = new_pos[1];
            }

          }
          p = p -> next;

        }
      }
    }
    head = head -> next;
    
  }
  
  // set the end coordinates to whatever the ending current position is at
  *endX = current_pos[0];
  *endY = current_pos[1];

  return;
}

/*---------------------------------------------------------------------------*/
// All done!