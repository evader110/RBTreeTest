#include "brtasktree.h"
#include "vm_task.h"
#include <iostream>
using namespace std;

int main()
{
    int numTasks = 0;
    VM_Task* tasks;
    RB_Task_Tree t;
    cin >> numTasks;
    tasks = new VM_Task[numTasks];

    for(int i = 0; i < numTasks;i++)
      t.insert(&tasks[i]);
    t.display(t.getRoot());
    cout << t.getRoot()->key << endl;
    return 0;
}