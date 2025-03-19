#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// ------------------- Commit Class (Linked List Node) -------------------
class Commit {
public:
    string message;
    string hash;
    Commit* prev; // Linked list to track commit history

    Commit(string msg, string h, Commit* prevCommit = nullptr)
        : message(msg), hash(h), prev(prevCommit) {}
};

// ------------------- Branch Class -------------------
class Branch {
public:
    string name;
    Commit* head; // Last commit in the branch

    Branch(string branchName) : name(branchName), head(nullptr) {}

    void addCommit(string msg, string hash) {
        head = new Commit(msg, hash, head);
    }

    void showCommitHistory() {
        Commit* temp = head;
        while (temp) {
            cout << "Commit: " << temp->hash << " - " << temp->message << endl;
            temp = temp->prev;
        }
    }
};

// ------------------- Repository Class -------------------
class Repository {
private:
    unordered_map<string, Branch*> branches;
    string activeBranch;
    unordered_map<string, string> workingTree;
    unordered_map<string, string> stagingArea;
    unordered_map<string, string> remoteTracking;

public:
    Repository() {
        branches["main"] = new Branch("main");
        activeBranch = "main";
    }

    void modifyFile(string filename, string content) {
        workingTree[filename] = content;
    }

    void stageFile(string filename) {
        if (workingTree.find(filename) != workingTree.end()) {
            stagingArea[filename] = workingTree[filename];
        } else {
            cout << "File does not exist in working directory.\n";
        }
    }

    void commit(string message) {
        if (stagingArea.empty()) {
            cout << "No changes to commit.\n";
            return;
        }

        string hash = "commit_" + to_string(rand() % 10000);
        branches[activeBranch]->addCommit(message, hash);
        stagingArea.clear();
        cout << "Committed: " << hash << " - " << message << endl;
    }

    void showStatus() {
        cout << "Active branch: " << activeBranch << endl;
        cout << "Unstaged changes:\n";
        for (auto& file : workingTree) {
            if (stagingArea.find(file.first) == stagingArea.end())
                cout << "- " << file.first << endl;
        }
        cout << "Staged changes:\n";
        for (auto& file : stagingArea) {
            cout << "- " << file.first << endl;
        }
    }

    void createBranch(string branchName) {
        if (branches.find(branchName) != branches.end()) {
            cout << "Branch already exists.\n";
            return;
        }
        branches[branchName] = new Branch(branchName);
        cout << "Created branch: " << branchName << endl;
    }

    void switchBranch(string branchName) {
        if (branches.find(branchName) == branches.end()) {
            cout << "Branch does not exist.\n";
            return;
        }
        activeBranch = branchName;
        cout << "Switched to branch: " << activeBranch << endl;
    }

    void showBranches() {
        for (auto& branch : branches) {
            cout << (branch.first == activeBranch ? "* " : "  ") << branch.first << endl;
        }
    }

    void push(unordered_map<string, string>& remoteRepo) {
        remoteRepo = stagingArea;
        stagingArea.clear();
        remoteTracking = remoteRepo;
        cout << "Pushed changes to remote.\n";
    }

    void pull(unordered_map<string, string>& remoteRepo) {
        for (auto& file : remoteRepo) {
            workingTree[file.first] = file.second;
        }
        cout << "Pulled latest changes from remote.\n";
    }

    void merge(string targetBranch) {
        if (branches.find(targetBranch) == branches.end()) {
            cout << "Branch does not exist.\n";
            return;
        }

        // Simulate merge conflict handling
        cout << "Merging " << targetBranch << " into " << activeBranch << "...\n";
        if (rand() % 2 == 0) {
            cout << "Merge conflict detected! Resolve manually.\n";
        } else {
            cout << "Merge successful!\n";
            branches[activeBranch]->head = branches[targetBranch]->head;
        }
    }
};

// ------------------- CLI Interface -------------------
void runCLI(Repository& repo, unordered_map<string, string>& remoteRepo) {
    string command;
    while (true) {
        cout << "\n> ";
        cin >> command;

        if (command == "exit") break;
        else if (command == "status") repo.showStatus();
        else if (command == "commit") {
            cout << "Enter commit message: ";
            string msg;
            cin.ignore();
            getline(cin, msg);
            repo.commit(msg);
        }
        else if (command == "add") {
            cout << "Enter filename: ";
            string file;
            cin >> file;
            repo.stageFile(file);
        }
        else if (command == "modify") {
            cout << "Enter filename: ";
            string file, content;
            cin >> file;
            cout << "Enter content: ";
            cin.ignore();
            getline(cin, content);
            repo.modifyFile(file, content);
        }
        else if (command == "branch") {
            cout << "Enter branch name: ";
            string branch;
            cin >> branch;
            repo.createBranch(branch);
        }
        else if (command == "switch") {
            cout << "Enter branch name: ";
            string branch;
            cin >> branch;
            repo.switchBranch(branch);
        }
        else if (command == "branches") repo.showBranches();
        else if (command == "push") repo.push(remoteRepo);
        else if (command == "pull") repo.pull(remoteRepo);
        else if (command == "merge") {
            cout << "Enter target branch: ";
            string branch;
            cin >> branch;
            repo.merge(branch);
        }
        else {
            cout << "Unknown command.\n";
        }
    }
}

// ------------------- Main Function -------------------
int main() {
    Repository repo;
    unordered_map<string, string> remoteRepo;
    runCLI(repo, remoteRepo);
    return 0;
}
