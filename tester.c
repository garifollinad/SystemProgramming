#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE  
#include <fcntl.h> 
#include <errno.h>
#include <unistd.h>
#include "unistd_64.h"

int test1(void);
int test2(void);
int test3(void);

int main(int argc, char** argv) {

  int t = 0;
  int n;

  printf("Type int you want to test? \n");
  scanf(" %i", &n);
  switch(n){
    case 2:
    t = test2();
    break;
    case 3:
    t = test3();
    break;
    default:
    t = test1();
  return t;
}
}

int test1(void){
  char *msg = "Salem Alem!";
  int t = syscall(__NR_msg_insert, msg, -1);
 
  return t;
}

int test2(void){
  char *msg_in = "Salem Alem!";
  char *msg_out = NULL;
  syscall(__NR_msg_insert, msg_in, strlen(msg_in)+1);
  int t = syscall(__NR_msg_get, msg_out, 30);
  return t;
}

int test3(void){
  char *msg_in = "Salem Alem!";
  char msg_out[30];
  int len;
  syscall(__NR_msg_insert, msg_in, strlen(msg_in)+1);
  len = syscall(__NR_msg_get, msg_out, 30);
  return 0;
}

