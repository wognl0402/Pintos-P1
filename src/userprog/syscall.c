#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

#define PHYS_TOP ((void *) 0x08048000)

static int (*syscall_case[20]) (struct intr_frame *f);

static void syscall_handler (struct intr_frame *);
static void valid_usrptr (const void *uaddr);

static int syscall_halt_ (struct intr_frame *f){
  return -1;
}
static int syscall_exit_ (struct intr_frame *f){
  
  return -1;
}
static int syscall_exec_ (struct intr_frame *f){
  return -1;
}
static int syscall_wait_ (struct intr_frame *f){
  return -1;
}
static int syscall_create_ (struct intr_frame *f){
  return -1;
} 
static int syscall_remove_ (struct intr_frame *f){
  return -1;
} 

static int syscall_open_ (struct intr_frame *f){
  return -1;
}

static int syscall_filesize_ (struct intr_frame *f){
  return -1;
}

static int syscall_read_ (struct intr_frame *f){
  return -1;
}

static int syscall_write_ (struct intr_frame *f){
  return -1;
}

static int syscall_seek_ (struct intr_frame *f){
  return -1;
}


static int syscall_tell_ (struct intr_frame *f){
  return -1;
}


static int syscall_close_ (struct intr_frame *f){
  return -1;
}


static int syscall_mmap_ (struct intr_frame *f){
  return -1;
}


static int syscall_munmap_ (struct intr_frame *f){
  return -1;
}


static int syscall_chdir_ (struct intr_frame *f){
  return -1;
}


static int syscall_mkdir_ (struct intr_frame *f){
  return -1;
}


static int syscall_readdir_ (struct intr_frame *f){
  return -1;
}


static int syscall_isdir_ (struct intr_frame *f){
  return -1;
}


static int syscall_inumber_ (struct intr_frame *f){
  return -1;
}



void
syscall_init (void) 
{
  //syscall 0~4
  syscall_case[SYS_HALT] = &syscall_halt_;
  syscall_case[SYS_EXIT] = &syscall_exit_;
  syscall_case[SYS_EXEC] = &syscall_exec_;
  syscall_case[SYS_WAIT] = &syscall_wait_;
  syscall_case[SYS_CREATE] = &syscall_create_;
  //syscall 5~9
  syscall_case[SYS_REMOVE] = &syscall_remove_;
  syscall_case[SYS_OPEN] = &syscall_open_;
  syscall_case[SYS_FILESIZE] = &syscall_filesize_;
  syscall_case[SYS_READ] = &syscall_read_;
  syscall_case[SYS_WRITE] = &syscall_write_;
  //syscall 10~12
  syscall_case[SYS_SEEK] = &syscall_seek_;
  syscall_case[SYS_TELL] = &syscall_tell_;
  syscall_case[SYS_CLOSE] = &syscall_close_;
  //syscall for P3 13,14
  syscall_case[SYS_MMAP] = &syscall_mmap_;
  syscall_case[SYS_MUNMAP] =&syscall_munmap_;
  //syscall for P4 15~19
  syscall_case[SYS_CHDIR] = &syscall_chdir_;
  syscall_case[SYS_MKDIR] = &syscall_mkdir_;
  syscall_case[SYS_READDIR] = &syscall_readdir_;
  syscall_case[SYS_ISDIR] = &syscall_isdir_;
  syscall_case[SYS_INUMBER] = &syscall_inumber_;

  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{

  int syscall_num = * (int *) f->esp;
//  int syscall_num;
/*  asm volatile ("movl %0, %%esp; popl %%eax" : "=a" (syscall_num) : "g" (f->esp));
*/	
  if (syscall_case[syscall_num] (f) == -1){
	printf("%d call made\n", syscall_num);
	return;
  }
  printf ("system call!\n");
  thread_exit ();
}

static void valid_usrptr (const void *uaddr){
  if (uaddr >= PHYS_BASE){
	//SOMETHING preventing 'leak' should be inserted
	return;
  }

  if (uaddr < PHYS_TOP){
	return;
  }

  if ((pagedir_get_page (thread_current ()->pagedir, uaddr))==NULL){
	//SOEMTHING preventing 'leak'
	return;
  }
}
