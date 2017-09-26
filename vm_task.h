#ifndef __VM_TASK_H
#define __VM_TASK_H

#include <iostream>
using namespace std;

class VM_Task
{
    private:
    string task_name;   //Debug value

    int task_quota;     //Cycles required for task to run to completion
    int task_progress;  //Current progress. task_progress/task_quota = % completion
    int task_priority;  //Priority level. Drops during priority schedule

    //Init value for task_priority. Reset priority after running priority schedule
    int origin_priority;

    public:
    VM_Task(string name, int quota): task_quota(quota), task_name(name){task_progress = 0;}

    VM_Task() //Array constructor (this will be called during init for VM_Task[])
    {
        cin >> task_name;

        cin >> task_quota;

        cin >> task_priority;
        origin_priority = task_priority;

        task_progress = 0;
    }

    ~VM_Task(){}

    //Restore values from init. Useful for runnning multiple schedules
    //  on same dataset.
    //TODO: Add to this
    void reset()
    {
        task_priority = origin_priority;
        task_progress = 0;
    }

    //Determine if task should run in next scheduled pass
    bool isFinished() const
    {
        return (task_progress >= task_quota)?true:false;
    }

    string getTaskName(){return task_name;}

    //Priority getter/setter
    int getPriority(){return task_priority;}
    void setPriority(int pri){task_priority = pri;}

    //Progress getter/setter
    int getProgress(){return task_progress;}
    void setProgress(int pro){task_progress = pro;}

    //Quota getter/setter
    int getQuota(){return task_quota;}
    void setQuota(int quota){task_quota = quota;}

    //Simulates the task using processor time
    void execute()
    {
        /*float bars = (static_cast<float>(task_progress)/task_quota)*10;
        cout << task_name << "\t[";
        for(int i = 0; i < bars; i++)
        {
            cout << "=";
        }
        for(int j = (bars==5||bars==0?0:1); j < 10-bars; j++)
        {
            cout << " ";
        }
        cout << "]\t" << static_cast<int>(bars*10) << "%" << endl;*/
        
        task_progress++;
    }
};

#endif //__VM_TASK_H