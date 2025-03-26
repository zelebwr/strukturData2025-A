#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
using namespace std;

class Commit {
public:
    string message;
    string hash;
    time_t timestamp;
    Commit* next;

    Commit(string msg, string h) {
        message = msg;
        hash = h;
        timestamp = time(0);
        next = nullptr;
    }
};

class Branch {
public:
    string name;
    Commit* head;

    Branch(string branchName) {
        name = branchName;
        head = nullptr;
    }

    void addCommit(string msg, string hash) {
        Commit* newCommit = new Commit(msg, hash);
        newCommit->next = head;
        head = newCommit;
    }

    void showCommitHistory() {
        Commit* temp = head;
        while (temp) {
            cout << "Commit: " << temp->hash << " | " << temp->message << "\n";
            temp = temp->next;
        }
    }
};

class Repository {
public:
    string repoName;
    unordered_map<string, Branch*> branches;
    string currentBranch;
    unordered_map<string, string> files;
    unordered_map<string, string> stagedFiles;

    Repository(string name) {
        repoName = name;
        currentBranch = "main";
        branches[currentBranch] = new Branch(currentBranch);
    }

    void createBranch(string branchName) {
        if (branches.find(branchName) == branches.end()) {
            branches[branchName] = new Branch(branchName);
            cout << "Branch " << branchName << " created.\n";
        } else {
            cout << "Branch already exists.\n";
        }
    }

    void switchBranch(string branchName) {
        if (branches.find(branchName) != branches.end()) {
            currentBranch = branchName;
            cout << "Switched to branch " << branchName << "\n";
        } else {
            cout << "Branch does not exist.\n";
        }
    }

    void modifyFile(string fileName, string content) {
        files[fileName] = content;
        cout << "File " << fileName << " modified.\n";
    }

    void stageFile(string fileName) {
        if (files.find(fileName) != files.end()) {
            stagedFiles[fileName] = files[fileName];
            cout << "File " << fileName << " staged.\n";
        } else {
            cout << "File does not exist.\n";
        }
    }

    void commitChanges(string msg) {
        if (stagedFiles.empty()) {
            cout << "No files staged for commit.\n";
            return;
        }
        string hash = to_string(time(0));
        branches[currentBranch]->addCommit(msg, hash);
        stagedFiles.clear();
        cout << "Committed: " << msg << " (" << hash << ")\n";
    }

    void showStatus() {
        cout << "Current branch: " << currentBranch << "\n";
        if (stagedFiles.empty()) {
            cout << "No changes staged for commit.\n";
        } else {
            cout << "Staged files:\n";
            for (auto& file : stagedFiles) {
                cout << " - " << file.first << "\n";
            }
        }
    }

    void showCommitLog() {
        cout << "Commit history for branch " << currentBranch << "\n";
        branches[currentBranch]->showCommitHistory();
    }
};

int main() {
    Repository repo("MyRepo");
    string command;
    while (true) {
        cout << "\nEnter command (add, commit, branch, switch, status, log, exit): ";
        cin >> command;
        if (command == "add") {
            string file, content;
            cout << "Enter file name: "; cin >> file;
            cout << "Enter content: "; cin >> content;
            repo.modifyFile(file, content);
            repo.stageFile(file);
        } else if (command == "commit") {
            string msg;
            cout << "Enter commit message: "; cin.ignore(); getline(cin, msg);
            repo.commitChanges(msg);
        } else if (command == "branch") {
            string branchName;
            cout << "Enter new branch name: "; cin >> branchName;
            repo.createBranch(branchName);
        } else if (command == "switch") {
            string branchName;
            cout << "Enter branch name to switch to: "; cin >> branchName;
            repo.switchBranch(branchName);
        } else if (command == "status") {
            repo.showStatus();
        } else if (command == "log") {
            repo.showCommitLog();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command.\n";
        }
    }
    return 0;
}
