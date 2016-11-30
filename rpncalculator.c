#include <FPT.h>
#include <string.h>
#include <ctype.h>

//could have used 
//if (strcmp(term, "add") == 0)....instead of char by char

double stack[1000];
int stackIndex = 0;

int checkNumber(char term[100]) { //returns 1 if it's a number, 0 if not

  int i;
  int check = 0;
  
  for (i = 0; i < 100; i++) {

    if ( term[i] == '\0' ) { 
      break;
    }
    else if ( term[i] < 48 || term[i] > 57 ) { //if any part of the term is NOT a digit (these are dec values), check goes up and this will invalidate it
      check++;
    }


    //this check is weird - if you have more than one decimal, it will just cut it off and everything after
    if ( term[i] == '.' ) { //if one of the terms is a decimal, check goes back to what it would have been
      check = check - 1;
    }

    if (term[0] == '-' ) { //same as above, for negative
      check = check - 1;
    }

  }

  if (check > 0) { //term was not a nonnegative whole number
    return 0;
  }
  else { //term was a nonnegative whole number!
    return 1;
  }

}

void add() { //adds top two terms on the stack
  //printf("there are %d numbers on the stack at time of add\n", stackIndex);
  //printf("the top number is %lf\n", stack[stackIndex - 1]);
  //printf("the next number is %lf\n", stack[stackIndex - 2]);

  stack[stackIndex - 2] = stack[stackIndex - 2] + stack[stackIndex - 1];
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void sub() {
  stack[stackIndex - 2] = stack[stackIndex - 2] - stack[stackIndex - 1];
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void mul() { 
  stack[stackIndex - 2] = stack[stackIndex - 2] * stack[stackIndex - 1];
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void RPNdiv() {
  stack[stackIndex - 2] = stack[stackIndex - 2] / stack[stackIndex - 1];
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void idiv() {
  div_t output;

  output = div(stack[stackIndex - 2], stack[stackIndex - 1]);

  stack[stackIndex - 2] = output.rem ;
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void mod() {
  stack[stackIndex - 2] = fmod( stack[stackIndex - 2], stack[stackIndex - 1]);
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void RPNsqrt() {  
  stack[stackIndex - 1] = sqrt( stack[stackIndex - 1] );
}

void RPNsin() {
  stack[stackIndex - 1] = sin( stack[stackIndex - 1] );
}

void RPNcos() {
  stack[stackIndex - 1] = cos( stack[stackIndex - 1] );
}

void pstack() {
  
  printf("you have %d number(s) on the stack\n", stackIndex);

  int j;
  for (j = 0; j < stackIndex; j++) {
  printf("%lf ", stack[j]);
  }
  printf("\n");

}

void pop() { //works
  stackIndex = stackIndex - 1; //DOESN'T CLEAR STACK[STACKINDEX - 1]
}

void roll() {

  double temp[1000];
  int i;
  int j = 0;
  int newindex;

  double rollwidth = stack[stackIndex - 2];
  double roll = stack[stackIndex - 1];

  pop();
  pop();

  for (i = 1; i <= rollwidth; i++) { //puts rollwidth amount of terms into temp array
    temp[j] = stack[stackIndex - i] ;
    j++;
  }

  for (i = 1; i <= rollwidth; i++) { //puts temp array into the right places

    if (i >= roll) { 
      newindex = fmod(i, roll) ;
      stack[stackIndex - i] = temp[ newindex ]; 
    }
    else {
      newindex = fmod(i, roll) + fmod(rollwidth, roll) ;
      stack[stackIndex - i] = temp[ newindex  ]; 
    }
  }
  
}

void exch() { //works
  double temp1 = stack[stackIndex - 1];
  double temp2 = stack[stackIndex - 2]; 

  stack[stackIndex - 1] = temp2;
  stack[stackIndex - 2] = temp1;
}

void RPNindex() { //works
  int index = stack[stackIndex - 1];
  stack[stackIndex - 1] = stack[stackIndex - (2 + index)] ; //check this

}

void copy() {

  int copyNum = stack[stackIndex - 1];
  pop();

  double copy[copyNum];
  int copyIndex;
  int i = copyNum;

  for (copyIndex = 0; copyIndex < copyNum; copyIndex++) {
    copy[copyIndex] = stack[stackIndex - i];
    i = i - 1;
  }

  for (copyIndex = 0; copyIndex < copyNum; copyIndex++) {
    stackIndex++;
    stack[stackIndex - 1] = copy[copyIndex];
  }
 

}

void RPNdup() {

stackIndex++;
stack[stackIndex - 1] = stack[stackIndex - 2];

}

int main() {

  char term[100] ;
  int n ;

  while (0 == 0) {
    n = scanf("%s",term) ; //returns 0 if at the end of the list of terms
    if (n != 1) { break ; } //breaks from loop if at the end of the list of terms

    if (term[0] == 'a' && term[1] == 'd' && term[2] == 'd') { 
      add();
    }

    else if (term[0] == 's' && term[1] == 'u' && term[2] == 'b') { 
      sub();
    }

    else if (term[0] == 'm' && term[1] == 'u' && term[2] == 'l') { 
      mul();
    }

    else if (term[0] == 'd' && term[1] == 'i' && term[2] == 'v') { 
      RPNdiv();
    }
    
    else if (term[0] == 'i' && term[1] == 'd' && term[2] == 'i' && term[3] == 'v') { 
      idiv();
    }
    
    else if (term[0] == 'm' && term[1] == 'o' && term[2] == 'd') { 
      mod();
    }
    
    else if (term[0] == 's' && term[1] == 'q' && term[2] == 'r' && term[3] == 't') {
      RPNsqrt();
    }
    
    else if (term[0] == 's' && term[1] == 'i' && term[2] == 'n') { 
      RPNsin();
    }
    
    else if (term[0] == 'c' && term[1] == 'o' && term[2] == 's') { 
      RPNcos();
    }
    
    else if (term[0] == 'p' && term[1] == 's' && term[2] == 't' && term[3] == 'a' && term[4] == 'c' && term[5] == 'k') {
      pstack();
    }

    else if (term[0] == 'p' && term[1] == 'o' && term[2] == 'p') { 
      pop();
    }

    else if (term[0] == 'e' && term[1] == 'x' && term[2] == 'c' && term[3] == 'h') { 
      exch();
    }

    else if (term[0] == 'i' && term[1] == 'n' && term[2] == 'd' && term[3] == 'e' && term[4] == 'x') {
      RPNindex();
    }

    else if (term[0] == 'd' && term[1] == 'u' && term[2] == 'p') { 
      RPNdup();
    }

    else if (term[0] == 'r' && term[1] == 'o' && term[2] == 'l' && term[3] == 'l') { 
      roll();
    }

    else if (term[0] == 'c' && term[1] == 'o' && term[2] == 'p' && term[3] == 'y') { 
      copy();
    }

    else if (checkNumber(term) == 1) {
      sscanf(term, "%lf", &stack[stackIndex]); //scans term into stack if it's a number
      stackIndex++; //bumps up stackIndex
    }
  }

}

