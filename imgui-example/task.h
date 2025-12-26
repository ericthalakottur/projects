#include <cstdio>
#include <vector>
#include <string.h>

const int TASK_NAME_MAX_LENGTH = 100;

typedef struct Task
{
    int id;
    bool completed;
    char* task_name;

    Task(int id, bool completed, char* new_task_name): id(id), completed(completed)
    {
        task_name = new char[TASK_NAME_MAX_LENGTH];
        strcpy(task_name, new_task_name);
    }

    char* get_name()
    {
        char* formatted_name = new char[TASK_NAME_MAX_LENGTH + 20];
        sprintf(formatted_name, "%d. %s", this->id, this->task_name);
        return formatted_name;
    }

    friend bool operator<(const Task& a, const Task& b)
    {
        size_t a_len = strlen(a.task_name);
        size_t b_len = strlen(b.task_name);
        return a_len < b_len;
    }
} Task;


class Tasks
{
    private:
        int current_task_id;
        std::vector<Task> pending_tasks;
        std::vector<Task> completed_tasks;

    public:
    Tasks()
    {
        this->current_task_id = 1;
        this->pending_tasks = {};
        this->completed_tasks = {};
    }

    int get_new_task_id();
    void add_task(char* task_name);
    void update_task_list();
    std::vector<Task>& get_pending_tasks();
    std::vector<Task>& get_completed_tasks();
};
