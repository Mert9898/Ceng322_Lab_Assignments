//250201017 Yağmur Nisa Şekerci
//260201011 Mert Ayaz Özkan

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/mm.h> // Add this to use `get_mm_rss()`

MODULE_LICENSE("GPL");

static int upid = 0;
module_param(upid, int, 0);
MODULE_PARM_DESC(upid, "User Process ID");

static char *upname = NULL;
module_param(upname, charp, 0);
MODULE_PARM_DESC(upname, "User Process Name");

struct task_struct *task;

static int proc_info_module_show(struct seq_file *m, void *v)
{   char state = task_state_to_char(task); 
    seq_printf(m, "Name: %s\n", task->comm);
    seq_printf(m, "PID: %d\n", task->pid);
    seq_printf(m, "PPID: %d\n", task->real_parent->pid);
    seq_printf(m, "UID: %d\n", task->cred->uid.val);


    if (task->mm && task_state_index(task) == TASK_RUNNING) { // use `task_state_index()` instead of `task->state`
        unsigned long rss = get_mm_rss(task->mm);
        unsigned long rss_kb = rss * PAGE_SIZE / 1024;
        seq_printf(m, "Memory Usage: %lu KB\n", rss_kb);
    }
    seq_printf(m, "State: %c\n", state);

    // Construct the path using the known PID
    seq_printf(m, "Path: /proc/%d\n", task->pid);
    // Note: This path construction assumes that the process exists and has a valid PID.

    return 0;
}

static int proc_info_module_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_info_module_show, NULL);
}

// Replace struct file_operations with struct proc_ops
static const struct proc_ops proc_info_module_fops = {
    .proc_open = proc_info_module_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init proc_info_module_init(void)
{
    struct proc_dir_entry *entry;

    printk(KERN_INFO "proc_info_module: loading module.\n");

    if (upid > 0)
    {
        task = pid_task(find_vpid(upid), PIDTYPE_PID);
        if (!task)
        {
            printk(KERN_ERR "proc_info_module: No task found with PID %d\n", upid);
            return 2;
        }
    }
    else if (upname)
    {
        for_each_process(task)
        {
            if (strcmp(task->comm, upname) == 0)
            {
                break;
            }
        }
        if (!task)
        {
            printk(KERN_ERR "proc_info_module: No task found with name %s\n", upname);
            return 2;
        }
    }
    else
    {
        printk(KERN_ERR "proc_info_module: No PID or name provided\n");
        return 2;
    }

    entry = proc_create("proc_info_module", 0, NULL, &proc_info_module_fops);
    if (!entry)
    {
        printk(KERN_ERR "proc_info_module: Failed to create /proc file\n");
        return 1;
    }

    printk(KERN_INFO "proc_info_module: module loaded.\n");
    return 0;
}

static void __exit proc_info_module_exit(void)
{
    remove_proc_entry("proc_info_module", NULL);
    printk(KERN_INFO "proc_info_module removed\n");
}

module_init(proc_info_module_init);
module_exit(proc_info_module_exit);
