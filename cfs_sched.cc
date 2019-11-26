#include<iostream>
#include<memory>
#include<string>
#include<utility>
#include<istream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include"llrb_multimap.h"

class Task {
 public:
  Task();
  Task(char name, unsigned int start_t, unsigned int dur, int vrun):
  identifier(name), start_time(start_t), duration(dur), vruntime(vrun) {}
  ~Task();
  const char get_identifier() {return identifier;}
  const int get_start_time() {return start_time;}
  const int get_duration() {return duration;}
  const int get_vruntime() {return vruntime;}
  void dec_duration() {duration--;}
  void inc_vruntime() {vruntime++;}
 private:
  char identifier;
  int start_time;
  int duration;
  int vruntime;
};

Task::Task() {
}

Task::~Task() {
}

bool min(Task* task1, Task* task2)
{ return task1->get_start_time() < task2->get_start_time(); }
bool min_identifier(Task* task1, Task* task2)
{ return task1->get_identifier() < task2->get_identifier(); }

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cerr << "Usage: " << argv[0] << " <task_file.dat>" << std::endl;
    exit(1);
  }

  std::ifstream task_list;
  task_list.open(argv[1]);
  if (!task_list.good()) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    exit(1);
  }

  std::string task;
  std::vector<Task*> tasks, current_tasks;
  int min_vruntime = 0;

  // Inserting Tasks into a Vector
  while (getline(task_list, task)) {
    std::istringstream is(task);
    char name;
    int start_t;
    int dur;
    while (is >> name >> start_t >> dur) {
      Task* t = new Task(name, start_t, dur, min_vruntime);
      tasks.push_back(t);
    }
  }

  std::sort(tasks.begin(), tasks.end(), min);
  std::sort(tasks.begin(), tasks.end(), min_identifier);

  int tick_value = 0;
  LLRB_multimap<int, Task*> task_manager;

  int running_tasks = 0;
  while (tasks.size() || current_tasks.size() || task_manager.Size()) {
    for (unsigned int i = 0; i < tasks.size(); i++) {
      if (tasks[i]->get_start_time() == tick_value) {
        if (min_vruntime >= 1) {
           tasks[i]->inc_vruntime();
           task_manager.Insert(tasks[i]->get_vruntime(), tasks[i]);
           running_tasks++;
        } else {
          task_manager.Insert(min_vruntime, tasks[i]);
          running_tasks++;
        }
      }
    }

    if (running_tasks == 0) {
      std::cout << tick_value << " [" << running_tasks << "]: " <<
      "_" << std::endl;
      tick_value++;
      continue;
    }

    if (current_tasks.size() == 0) {
      int key = task_manager.Min();
      Task* value = task_manager.Get(key);
      current_tasks.push_back(value);
      task_manager.Remove(key, value);
    }

    if (task_manager.Size() != 0) {
      min_vruntime = task_manager.Min();
    }

    current_tasks[0]->inc_vruntime();
    current_tasks[0]->dec_duration();

    if (current_tasks[0]->get_duration() == 0) {
      std::cout << tick_value << " [" << running_tasks << "]: " <<
      current_tasks[0]->get_identifier() << "*" << std::endl;
    } else {
      std::cout << tick_value << " [" << running_tasks << "]: " <<
      current_tasks[0]->get_identifier() << std::endl;
    }

    if (current_tasks[0]->get_duration() == 0) {
      // reverse needed if they don't overlap
      std::reverse(tasks.begin(), tasks.end());
      // pop tasks from the tasks vector in order for outest while loop to stop
      tasks.pop_back();
      tasks.shrink_to_fit();
      current_tasks.pop_back();
      current_tasks.shrink_to_fit();
      running_tasks--;
    } else if (current_tasks[0]->get_vruntime() > min_vruntime) {
      task_manager.Insert(current_tasks[0]->get_vruntime(), current_tasks[0]);
      current_tasks.pop_back();
      current_tasks.shrink_to_fit();
    }

    tick_value++;
  }
  return 0;
}
