#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <ctime>
#include <string>

using namespace std;

// Data Structures
struct User {
    string name;
    string phoneNumber;
    string gender;
    int userID;
};

struct Item {
    string name;
    double price;
};

// Globals
unordered_map<int, User> userDatabase; // Key: UserID, Value: User
list<Item> availableItems;
unordered_map<int, list<Item>> userCarts; // Key: UserID, Value: Cart
queue<int> checkoutQueue; // UserIDs in queue for checkout

// Functions
int registerUser() {
    User newUser;
    static int currentID = 0;

    cout << "Enter your name: ";
    cin >> newUser.name;
    cout << "Enter your phone number: ";
    cin >> newUser.phoneNumber;
    cout << "Enter your gender: ";
    cin >> newUser.gender;

    currentID++;
    newUser.userID = currentID;
    userDatabase[currentID] = newUser;

    cout << "Registration successful! Your user ID is: " << currentID << endl;
    return currentID;
}

void displayItems() {
    int count = 1;
    for (auto item : availableItems) {
        cout << count << ". " << item.name << " - $" << item.price << endl;
        count++;
    }
}

void addToCart(int userID) {
    int numOfItems, itemChoice;

    displayItems();
    cout << "Enter number of items you want to add: ";
    cin >> numOfItems;

    for (int i = 0; i < numOfItems; i++) {
        cout << "Enter item number to add to cart: ";
        cin >> itemChoice;
        auto it = next(availableItems.begin(), itemChoice - 1);
        userCarts[userID].push_back(*it);
    }
}

void checkout(int userID) {
    double totalAmount = 0;

    cout << "Items in your cart:" << endl;
    for (auto item : userCarts[userID]) {
        cout << item.name << " - $" << item.price << endl;
        totalAmount += item.price;
    }

    char choice;
    cout << "Confirm order? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        checkoutQueue.push(userID);
        cout << "Order confirmed! Proceeding to billing..." << endl;
    } else {
        cout << "Order cancelled." << endl;
    }
}

void generateBill(int userID) {
    double totalAmount = 0;

    cout << "User ID: " << userID << endl;
    cout << "Name: " << userDatabase[userID].name << endl;
    cout << "Phone: " << userDatabase[userID].phoneNumber << endl;
    cout << "Date and Time: " << time(0) << endl; // Simplified timestamp for now
    cout << "------------------------" << endl;

    for (auto item : userCarts[userID]) {
        cout << item.name << " - $" << item.price << endl;
        totalAmount += item.price;
    }

    totalAmount += 100; // Adding delivery charges
    cout << "Delivery Charges: $100" << endl;
    cout << "Total Amount: $" << totalAmount << endl;
    cout << "Thank you for shopping with us!" << endl;
}

int main() {
    // Sample items
    for (int i = 1; i <= 25; i++) {
        availableItems.push_back({"Item" + to_string(i), i * 10.0});
    }

    while (true) {
        cout << "1. Register\n2. Add to Cart\n3. Checkout\n4. Generate Bill\n5. Exit\nChoose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                registerUser();
                break;
            }
            case 2: {
                int userID;
                cout << "Enter User ID: ";
                cin >> userID;
                addToCart(userID);
                break;
            }
            case 3: {
                int userID;
                cout << "Enter User ID: ";
                cin >> userID;
                checkout(userID);
                break;
            }
            case 4: {
                if (checkoutQueue.empty()) {
                    cout << "No users in queue!" << endl;
                } else {
                    int userID = checkoutQueue.front();
                    checkoutQueue.pop();
                    generateBill(userID);
                }
                break;
            }
            case 5: {
                return 0;
            }
            default: {
                cout << "Invalid choice!" << endl;
            }
        }
    }

    return 0;
}