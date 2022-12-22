#include <linux/module.h>    
#include <linux/kernel.h>
#include <linux/init.h>       
#include <linux/list.h>
#include <linux/moduleparam.h>
#include <linux/cred.h>
#include <linux/resource.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/unistd.h>
#include <asm/current.h>
#include <linux/syscalls.h>

static int givenpid;
module_param(givenpid,int,0644);
static int __init printProcessInfo(void)
{
  struct task_struct *task;

  task = pid_task(find_vpid(givenpid), PIDTYPE_PID);

  printk("pid: %d", task->pid);
  printk("\n");
  printk("ID-USER: %d", task->cred->uid.val);
  printk("\n");
  printk("pgid: %d", task->group_leader->pid);
  printk("\n");
  printk("CMD_PTH: %s", task->comm);
  printk("\n");

  return 0;
}


static void __exit exitNow(void){
    printk("Leaving");
}

module_init(printProcessInfo);
module_exit(exitNow);