#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <climits>
using namespace std;

class Node {
    public:
    string label;
    int price, rating; 
    Node* next;
    Node() : next(NULL), label(""), price(0), rating(0) {} // Constructor to initialize the node
};

class hashSet {
    Node** buckets; // Pointer to an array of linked lists (buckets)
    int bucketCount;
    
    unsigned int hashFunction(const string& value) {
        unsigned int hash = 5381; // algo djb2
        for (char c : value) {
            hash = ((hash << 5) + hash) + c; // main operation for hash function
        }
        return hash % bucketCount;
    }
    
    public: 
    hashSet(int datasetSize) : bucketCount(int(datasetSize / 0.7)) {
        // initialize the amount of buckets there is
        buckets = new Node*[bucketCount];
        
        // initialize each bucket to NULL
        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = NULL;
        }
    }
    
    ~hashSet() {
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            // Traverse the linked list and delete each node
            while (current) {
                Node* toDelete = current; // putting current Node in another temporary variable
                current = current->next; // move current Node to the next node
                delete toDelete; // Free the node memory
            }
        }
        delete[] buckets; // Free the memory allocated for buckets
    }
    
    // Function to add a value in the beginning of the bucket of the hash set
    void add(const string& label, int attr1, int attr2) {
        // check if the value already exists to avoid duplicates
        if (contains(label)) {
            cout << "Value '" << label << "' already exists." << endl;
            return; // Value already exists, do not add again
        }

        // calculate the index for the hash table
        unsigned int index = hashFunction(label);

        // Create a new node and add it to the front of the list
        Node* newNode = new Node();
        newNode->label = label; // Assign the value to the new node
        newNode->price = attr1; // Assign the value to the new node
        newNode->rating = attr2; // Assign the value to the new node
        newNode->next = buckets[index]; // Point to the current head of the list
        buckets[index] = newNode; // Update the head of the list to the new node
    }

    bool contains(const string& label) {
        unsigned int index = hashFunction(label);
        Node* current = buckets[index];
        // traverse the linked list at the index
        while (current) {
            if (current->label == label) return true; // Found the value
            current = current->next;
        }
        return false; // Not found
    }


    void remove(const string& label) {
        // check if the value exists in the hash set
        unsigned int index = hashFunction(label);
        Node* current = buckets[index];
        
        while (current) {
            if (current->label == label) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete; // Free the node memory
                cout << "Value '" << label << "' has been removed." << endl; // Value removed
                return; // Value removed
            }
            current = current->next;
        }
        
        // If we reach here, the value was not found
        cout << "Value '" << label << "' not found." << endl; // Value not found
    }
    
    
    void printHashSet() {
        for (size_t i = 0; i < bucketCount; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = buckets[i];
            int counter = 0;
            while (current) {
                cout << counter << ". " << current->label << "," << current->price << "," << current->rating << " -> "; // Print the node's value
                counter++; // Increment the counter for each node in the bucket
                current = current->next; // Move to the next node
            }
            cout << "NULL" << endl;
        }
    }

    void printPriceSkyline() {
        if (!buckets) {
            cout << "HashSet is empty." << endl; // HashSet is empty
            return;
        }

        // find min price
        int minPrice = INT_MAX; // initialized as the max price
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            while (current) {
                if (current->price < minPrice) {
                    minPrice = current->price;
                }
                current = current->next;
            }
        }

        cout << "\n=== Price Skyline (Lowest Price: " << minPrice << ") ===\n";
        int counter = 1;
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            while (current) {
                if (current->price == minPrice) { // Print only the nodes with the minimum price
                    cout << counter << ". Product: " << current->label 
                         << " | Price: " << current->price 
                         << " | Rating: " << current->rating << endl;
                    counter++; // Increment the counter for each node in the bucket
                }
                current = current->next; // Move to the next node
            }
        }
    }

    void printRatingSkyline() {
        if (!buckets) {
            cout << "HashSet is empty." << endl; // HashSet is empty
            return;
        }

        int maxRating = 0; // initialized as the max rating
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            while (current) {
                if (current->rating > maxRating) {
                    maxRating = current->rating;
                }
                current = current->next;
            }
        }

        cout << "\n=== Rating Skyline (Highest Rating: " << maxRating << ") ===\n";
        int counter = 1;
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            while (current) {
                if (current->rating == maxRating) { // Print only the nodes with the minimum rating
                    cout << counter << ". Product: " << current->label 
                         << " | Price: " << current->price 
                         << " | Rating: " << current->rating << endl;
                    counter++; // Increment the counter for each node in the bucket
                }
                current = current->next; // Move to the next node
            }
        }
    }

    void printTopSkyline() {
        cout << "\n=== Top Skyline ===\n";
        int counter = 1;

        // Traverse through all buckets and check for skyline products
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            while (current) {
                bool dominated = false; 

                // Check against all other products
                for (int j = 0; j < bucketCount; j++) {
                    Node* other = buckets[j];
                    while (other) {
                        if (current == other) {
                            other = other->next;
                            continue;
                        }
                        if ((other->price <= current->price) && 
                            (other->rating >= current->rating) &&
                            (other->price < current->price || other->rating > current->rating)) {
                            dominated = true;
                            break;
                        }
                        other = other->next;
                    }
                    if (dominated) break;
                }
                
                if (!dominated) {
                    cout << counter << ". Product: " << current->label
                         << " | Price: " << current->price
                         << " | Rating: " << current->rating << endl;
                    counter++; // Increment the counter for each node in the bucket
                }
                current = current->next;
            }
        }
    }

    int getBucketCount() const {
        return bucketCount; // Return the number of buckets in the hash set
    }

};

int main() {
    auto startAll = chrono::high_resolution_clock::now(); 

    auto startDataRetrieval = chrono::high_resolution_clock::now(); // Start time for data retrieval
    // local variables
    hashSet skylineSet(1000); 
    ifstream iFile("./ind_500_2_product.csv");
        if (!iFile) { // check if the file opened successfully
            cout << "Error opening file" << endl;
            return 1;
        }

    string line = "";
    getline(iFile, line); // Skip the header line

    while (getline(iFile, line)) { // Read each line from the file
        size_t first_comma = line.find(',');
        size_t second_comma = line.find(',', first_comma + 1);
        size_t third_comma = line.find(',', second_comma + 1);

        if (first_comma == string::npos || 
            second_comma == string::npos || 
            third_comma == string::npos) {
            cout << "Invalid line: " << line << endl;
            continue;
        }

        string label = line.substr(first_comma + 1, second_comma - first_comma - 1);
        string attr1_str = line.substr(second_comma + 1, third_comma - second_comma - 1);
        string attr2_str = line.substr(third_comma + 1);

        // attr1_str.erase(remove_if(attr1_str.begin(), attr1_str.end(), ::isspace), attr1_str.end());
        // attr2_str.erase(remove_if(attr2_str.begin(), attr2_str.end(), ::isspace), attr2_str.end());

        try {
            int attr1 = stoi(attr1_str);
            int attr2 = stoi(attr2_str);
            skylineSet.add(label, attr1, attr2);
        } catch (...) {
            cout << "Error parsing line: " << line << endl;
        }
    }

    auto endDataRetrieval = chrono::high_resolution_clock::now(); // End time for data retrieval

    // skylineSet.printHashSet(); // Print the hash set

    auto startPriceSkyline = chrono::high_resolution_clock::now(); 
    skylineSet.printPriceSkyline(); 
    auto endPriceSkyline = chrono::high_resolution_clock::now(); 

    auto startRatingSkyline = chrono::high_resolution_clock::now(); 
    skylineSet.printRatingSkyline(); 
    auto endRatingSkyline = chrono::high_resolution_clock::now(); 

    auto startTopSkyline = chrono::high_resolution_clock::now(); 
    skylineSet.printTopSkyline(); 
    auto endTopSkyline = chrono::high_resolution_clock::now(); 

    auto endAll = chrono::high_resolution_clock::now(); 

    chrono::duration<double> durationDataRetrieval = endDataRetrieval - startDataRetrieval; 
    chrono::duration<double> durationPriceSkyline = endPriceSkyline - startPriceSkyline; 
    chrono::duration<double> durationRatingSkyline = endRatingSkyline - startRatingSkyline; 
    chrono::duration<double> durationTopSkyline = endTopSkyline - startTopSkyline; 
    chrono::duration<double> durationAll = endAll - startAll; 

    cout << "\n=== Performance Measurement ===\n";
    cout << "Data Retrieval Time: " << durationDataRetrieval.count() << " seconds" << endl;
    cout << "Price Skyline Calculation Time: " << durationPriceSkyline.count() << " seconds" << endl;
    cout << "Rating Skyline Calculation Time: " << durationRatingSkyline.count() << " seconds" << endl;
    cout << "Top Skyline Calculation Time: " << durationTopSkyline.count() << " seconds" << endl;
    cout << "Total Execution Time: " << durationAll.count() << " seconds" << endl;
    cout << "Total Memory Usage: " << sizeof(skylineSet) + (sizeof(Node) * skylineSet.getBucketCount()) << " bytes" << endl; // Print the total memory usage
}