#include <iostream>
#include <ctime>
#include <iomanip>
#include <utility>
#include <string>
using namespace std;

struct gameData {
    string username;
    int
        score,
        level;
    time_t timestamp;
    gameData* next;

    gameData(string user, int sc, int lvl) {
        username = user;
        score = sc;
        level = lvl;
        timestamp = time(nullptr);
        next = nullptr;
    }
}; 

class leaderboard {
    gameData* head;

    public: 
        leaderboard() {
            head = nullptr;
        }

        void addTrackEnd(string usr, int sc, int lvl) {
            gameData* newRecord = new gameData(usr, sc, lvl);
            if (!head) {
                head = newRecord;
            } else {
                gameData* temp = head;
                // traverse to the end of the list
                while (temp->next) temp = temp->next;
                temp->next = newRecord;
            }
        }

        static bool ascending(const string& a, const string& b) {
            return a < b; // Ascending order
        }
        
        static bool descending(const string& a, const string& b) {
            return a > b; // Descending order
        }

        static string getUsername(gameData* data) {
            return data->username;
        }
        
        static string getScoreAsString(gameData* data) {
            return to_string(data->score); // Convert score to string for comparison
        }

        static string getLevelAsString(gameData* data) {
            return to_string(data->level); // Convert level to string for comparison
        }

        static string getTimestampAsString(gameData* data) {
            return to_string(data->timestamp); // Convert timestamp to string for comparison
        }

        void sortList(bool (*compare)(const string&, const string&), string (*getMember)(gameData*)) {
            if (!head || !head->next) return; // No need to sort if the list is empty or has one node
        
            bool swapped;
            do {
                swapped = false;
                gameData* prev = nullptr;
                gameData* curr = head;
                gameData* nextNode = head->next;
        
                while (nextNode) {
                    if (!compare(getMember(curr), getMember(nextNode))) {
                        // Swapping the actual nodes
                        if (prev) {
                            prev->next = nextNode;
                        } else {
                            head = nextNode; // Update head if swapping the first two nodes
                        }
                        curr->next = nextNode->next;
                        nextNode->next = curr;
        
                        // Move prev pointer only when swapping
                        prev = nextNode;
                        nextNode = curr->next;
        
                        swapped = true;
                    } else {
                        // Move both pointers forward
                        prev = curr;
                        curr = nextNode;
                        nextNode = nextNode->next;
                    }
                }
            } while (swapped);
        }
        

        void playGame(leaderboard& leaderboard) {
            string username;
            int score = 0, level = 1;
        
            cout << "\nEnter your username: ";
            cin >> username;
        
            srand(time(0));
            int number = rand() % 100 + 1; // Random number between 1 and 100
            int guess, attempts = 0;
        
            cout << "Guess a number between 1 and 100: ";
            while (true) {
                cin >> guess;
                attempts++;
                if (guess == number) {
                    cout << "Correct! You guessed it in " << attempts << " attempts!\n";
                    score = 100 - attempts;  // Higher score for fewer attempts
                    level = (score > 80) ? 3 : (score > 50) ? 2 : 1;
                    break;
                } else if (guess < number) {
                    cout << "Too low, try again: ";
                } else {
                    cout << "Too high, try again: ";
                }
            }
        
            leaderboard.addTrackEnd(username, score, level);
            cout << "Game Over! Your score: " << score << ", Level: " << level << endl;
        }

        void sortMenu() {
            int option;
            char order;
        
            cout << "Sort by:\n"
                 << "1. Username\n"
                 << "2. Score\n"
                 << "3. Level\n"
                 << "4. Timestamp\n"
                 << "Enter your choice: ";
            cin >> option;
        
            while (option < 1 || option > 4) {
                cout << "Invalid choice. Please enter a valid choice [1-4]: ";
                cin >> option;
            }
        
            cout << "(A)scending or (D)escending? ";
            cin >> order;
        
            while (order != 'A' && order != 'D' && order != 'a' && order != 'd') {
                cout << "Invalid choice. Please enter a valid choice [A/D]: ";
                cin >> order;
            }
        
            bool ascendingOrder = (order == 'A' || order == 'a');
        
            switch (option) {
                case 1:
                    cout << "sorting by username\n";
                    ascendingOrder ? sortList(ascending, getUsername) : sortList(descending, getUsername);
                    break;
                case 2:
                    ascendingOrder ? sortList(ascending, getScoreAsString) : sortList(descending, getScoreAsString);
                    break;
                case 3:
                    ascendingOrder ? sortList(ascending, getLevelAsString) : sortList(descending, getLevelAsString);
                    break;
                case 4:
                    ascendingOrder ? sortList(ascending, getTimestampAsString) : sortList(descending, getTimestampAsString);
                    break;
            }
        }

        void displayLeaderboard() {
            if (!head) {
                cout << "Leaderboard is empty.\n";
                return;
            }
    
            cout << "\n===== Leaderboard =====\n";
            cout << left << setw(12) << "Username"
                << setw(2) << "Timestamp"
                << setw(10) << "Score"
                << setw(5) << "Level\n";
            cout << "-----------------------------------------------------------\n";

            gameData* temp = head;
            while (temp) {
                // Convert timestamp to string and remove the newline character
                string timeStr = ctime(&(temp->timestamp));
                timeStr.pop_back(); // Removes the last newline from ctime()

                cout << left << setw(12) << temp->username
                    << setw(27) << timeStr
                    << setw(10) << temp->score
                    << setw(10) << temp->level << endl;

                temp = temp->next;
            }
            cout << "-----------------------------------------------------------\n";
        }
};

int main() {
    leaderboard leaderboard;
    int choice;

    do {
        cout << "\n===== CLI Mini-Game Menu =====\n";
        cout << "1. Play Game\n";
        cout << "2. View Leaderboard\n";
        cout << "3. Sort Leaderboard\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                leaderboard.playGame(leaderboard);
                break;
            case 2:
                leaderboard.displayLeaderboard();
                break;
            case 3:
                leaderboard.sortMenu();
                break;
            case 4:
                cout << "Exiting game. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}