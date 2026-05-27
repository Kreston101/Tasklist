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
bool SaveToFile(std::vector<Task>& vec);
bool NewTask(std::vector<Task>& vec, const std::string& cmd);

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
    //read op starts here
    std::getline(input, title);
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        bool priority{}, completed{};
        short num{}, day{}, month{};
        std::string taskAndNote;
        char drop;
        iss >> priority >> completed >> num >> day >> drop >> month >> std::ws;
        std::getline(iss, taskAndNote); // add splitter for task and note section
        Task nTask(priority, completed, num, DueDate(day,month), taskAndNote, "blah");
        TodoList.push_back(nTask);
    }
    //read op ends here
    PrintTasklist(TodoList);
    std::string command{};
    //main program loop
    while (command[0] != 'q') {
        std::getline(std::cin, command);
        switch (command[0]) {
        case 'q': //save quit? stop quit if save fail?
            std::cout << "Quiting\n";
        case 's': //what to do if fail? how do we write
            SaveToFile(TodoList);
            break;
        case 'n': //CHECK FORMATTING //we have decided to assume both code and the user are perfect, lmao
            std::cout << "New task was " << std::boolalpha << NewTask(TodoList, command) << '\n';
            PrintTasklist(TodoList);
            break;
        case 'c': //...this might eb difficult
            std::cout << "Marked <insert here> as complete\n";
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

bool SaveToFile(std::vector<Task>& vec) {

    return true;
}

bool NewTask(std::vector<Task>& vec, const std::string& cmd) { //this is mega unsafe but its personal use
    std::istringstream iss(cmd);
    bool priority{};
    short num{}, day{}, month{};
    std::string taskAndNote;
    char drop;
    iss >> drop >> priority >> num >> day >> drop >> month >> std::ws;
    std::getline(iss, taskAndNote); //add spliter for task and note section
    Task nTask(priority, 0, num, DueDate(day, month), taskAndNote, "blah");
    vec.push_back(nTask);
    return false;
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
    std::cout << "q - quit\ns - save\nn - new\nc - create\nu - update\no - organise\n";
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