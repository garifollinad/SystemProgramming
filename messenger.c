#include "uapi/asm-generic/errno.h"
#include <linux/slab.h>
#include "uapi/asm-generic/errno-base.h"
#include <linux/uaccess.h>

typedef struct _ptr_msg ptr_msg;

struct _ptr_msg{
  ptr_msg* previous;
  int len;
  char* message;
};
unsigned long flags;
static ptr_msg *bottom = NULL;
static ptr_msg *top = NULL;

int msg_insert( char *buffer, int len ) {
   ptr_msg* msg = kmalloc(sizeof(ptr_msg), GFP_KERNEL);

   if (!msg) {
    local_irq_restore(flags);
    return(-15);
  }

  msg->previous = NULL;
  msg->len = len;
  msg->message = kmalloc(len, GFP_KERNEL);

  ssize_t size;
  size = copy_from_user(msg->message, buffer, len);
  printk(msg->message);

  if (bottom == NULL) {
    bottom = msg;
    top = msg;
  } 
 else {
    msg->previous = top;
    top = msg;
  }
  return 0;
}

int msg_get( char* buffer, int len ) {

  if (top != NULL) {
    ptr_msg* msg = top;
    int nLen = msg->len;
    top = msg->previous;

    if(buffer == NULL){
    local_irq_restore(flags);
    return(-21);
  }

    printk(msg->message);

    copy_to_user(buffer, msg->message, nLen);

    kfree(msg->message);
    kfree(msg);

    return nLen;
  }

  return -15;
}
