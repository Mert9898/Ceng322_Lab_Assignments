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

MODULE_LICENSE("GPL");

static int upid = 0;
module_param(upid, int, 0);
MODULE_PARM_DESC(upid, "User Process ID");

static char *upname = NULL;
module_param(upname, charp, 0);
MODULE_PARM_DESC(upname, "User Process Name");

struct task_struct *task;

static int proc_info_module_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Name: %s\n", task->comm);
    seq_printf(m, "PID: %d\n", task->pid);
    seq_printf(m, "PPID: %d\n", task->real_parent->pid);
    seq_printf(m, "UID: %d\n", task->cred->uid.val);

    char state;
    switch (task->state)
    {
    case TASK_RUNNING:
        state = 'R';
        break;
    case TASK_INTERRUPTIBLE:
        state = 'S';
        break;
    case TASK_UNINTERRUPTIBLE:
        state = 'D';
        break;
    case TASK_STOPPED:
        state = 'T';
        break;
    default:
        state = 'X';
        break;
    }

    if (task->mm && task->state == TASK_RUNNING) {
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

static const struct file_operations proc_info_module_fops = {
    .owner = THIS_MODULE,
    .open = proc_info_module_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
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
