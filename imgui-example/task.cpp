#include <vector>
#include "task.h"

int Tasks::get_new_task_id()
{
    return this->current_task_id++;
}
void Tasks::add_task(char* task_name)
{
  Task task = {this->get_new_task_id(), false, task_name};
  this->pending_tasks.push_back(task);
}

void Tasks::update_task_list()
{
    for(size_t i = 0; i < this->pending_tasks.size(); i++)
    {
        if (this->pending_tasks[i].completed)
        {
            this->completed_tasks.push_back(this->pending_tasks[i]);
            this->pending_tasks.erase(this->pending_tasks.begin() + i);
        }
    }
    for(size_t i = 0; i < this->completed_tasks.size(); i++)
    {
        if (!this->completed_tasks[i].completed)
        {
            this->pending_tasks.push_back(this->completed_tasks[i]);
            this->completed_tasks.erase(this->completed_tasks.begin() + i);
        }
    }
}

std::vector<Task>& Tasks::get_pending_tasks()
{
    return this->pending_tasks;
}

std::vector<Task>& Tasks::get_completed_tasks()
{
    return this->completed_tasks;
}
