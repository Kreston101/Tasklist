#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Task.h"
#include "DueDate.h"

//fp "C:\Users\ethan\Downloads\testdata.txt"
std::string title; //is this bad...?
void PrintTasklist(const std::vector<Task>& vec);
void PrintHPTask(const std::vector<Task>& vec);
void PrintLPTask(const std::vector<Task>& vec);
void SaveToFile(std::vector<Task>& vec, const std::string filepath);
void NewTask(std::vector<Task>& vec, const std::string& cmd);
void FinTask(std::vector<Task>& vec, const std::string& cmd);

//auto sort priority based on due date
//figure out if you're going to use the manual priority number

int main(int argc, char* argv[]) {
    std::vector<Task> TodoList;
    std::string filepath;
    if (argc > 1) {
        filepath = argv[1];
    }
    else {
        std::cout << "No file provided. Please enter the path manually: ";
        std::getline(std::cin, filepath);
    }
    if (filepath.find(" \" ") && !filepath.empty()) {
        filepath.pop_back();
        filepath.erase(0,1);
    }
    std::ifstream input(filepath);
    if (!input) {
        std::cout << "File cannot be opened\n";
        return 0;
    }
    //file read op starts here
    std::getline(input, title);
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        bool priority{}, completed{};
        short id{}, day{}, month{};
        std::string taskName;
        char drop;
        iss >> priority >> completed >> id >> day >> drop >> month >> std::ws;
        std::getline(iss, taskName);
        Task nTask(priority, completed, id, DueDate(day,month), taskName);
        TodoList.push_back(nTask);
    }
    //file read op ends here
    PrintTasklist(TodoList);
    std::string command{};
    //main program loop
    while (command[0] != 'q') {
        std::getline(std::cin, command);
        switch (command[0]) {
        case 'q':
            std::cout << "Quiting\n";
        case 's':
            SaveToFile(TodoList, filepath);
            std::cout << "Saved tasklist\n";
            break;
        case 'n':
            NewTask(TodoList, command);
            PrintTasklist(TodoList);
            break;
        case 'c': 
            FinTask(TodoList, command);
            PrintTasklist(TodoList);
            break;
        case 'u': //how?
            std::cout << "Updating task\n";
            PrintTasklist(TodoList);
            break;
        case 'o': //have fun
            std::cout << "Organised list with given filter\n";
            PrintTasklist(TodoList);
            break;
        default:
            std::cout << "Unrecognised\n";
            break;
        }
    }
}

void SaveToFile(std::vector<Task>& vec, std::string filepath) {
    std::ofstream output(filepath);
    if (!output) {
        std::cout << "File cannot be opened\n";
        return;
    }
    output << title << '\n';
    for (Task task : vec) {
        output << task.priority << ' '
            << task.completed << ' '
            << task.id << ' '
            << task.date << ' '
            << task.task << '\n';
    }
}

void NewTask(std::vector<Task>& vec, const std::string& cmd) { //this is mega unsafe but its personal use
    std::istringstream iss(cmd);
    bool priority{};
    short id{}, day{}, month{};
    std::string taskName;
    char drop; //first drop usually 'n'
    iss >> drop >> priority;
    if (!priority) {
        id = 100;
    }
    for (Task& task : vec) {
        if (task.id == id) {
            ++id;
        }
    }
    std::cout << "id set to " << id << '\n';
    iss >> day >> drop >> month >> std::ws;
    std::getline(iss, taskName); //add spliter for task and note section
    Task nTask(priority, 0, id, DueDate(day, month), taskName);
    vec.push_back(nTask);
}

void FinTask(std::vector<Task>& vec, const std::string& cmd) {
    short taskId{};
    std::istringstream iss(cmd);
    char drop{};
    iss >> drop >> taskId;
    for (Task& task : vec) {
        if (task.id == taskId) {
            std::cout << "found a task with given id " << taskId << '\n';
            task.completed = !task.completed;
        }
    }
}

void PrintTasklist(const std::vector<Task>& vec) {
    std::cout << title << '\n';
    std::cout << std::setw(55) << std::setfill('=') << '\n';
    std::cout << "Todo:\n";
    PrintHPTask(vec);
    std::cout << std::setw(55) << std::setfill('=') << '\n';
    std::cout << "Misc:\n";
    PrintLPTask(vec);
    std::cout << std::setw(55) << std::setfill('=') << '\n';
    std::cout << "Commands:\n";
    std::cout << "q - quit\ns - save\nn - new\nc - complete\nu - update\no - organise\n";
}

void PrintHPTask(const std::vector<Task>& vec) {
    int count{ 1 };
    for (Task task : vec) {
        if (task.priority) {
            std::cout << count++ << ". " << task << '\n';
        }
    }
}
void PrintLPTask(const std::vector<Task>& vec) {
    for (Task task : vec) {
        if (!task.priority) {
            std::cout << task << '\n';
        }
    }
}