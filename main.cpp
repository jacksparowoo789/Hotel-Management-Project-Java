#include <iostream>
#include <string>
using namespace std;

// =======================================================
// STRUCTURES
// =======================================================

// Hotel data (for sorting/filtering)
struct Hotel {
    string name;
    string location;
    int availableRooms;
    float rating;
};

// Doubly linked list for guest record
struct Guest {
    string name;
    int roomNumber;
    Guest *prev;
    Guest *next;
};

// Node for Queue & Stack
struct Node {
    string name;
    Node* next;
};

// =======================================================
// GLOBAL HEADS
// =======================================================
Guest* head = NULL;      // Guest linked list head
Guest* tail = NULL;
Node* frontQ = NULL;     // Queue front
Node* rearQ = NULL;      // Queue rear
Node* topS = NULL;       // Stack top

// =======================================================
// HELPER FUNCTIONS FOR LINKED LIST
// =======================================================
void checkIn(string name, int room) {
    Guest* newGuest = new Guest();
    newGuest->name = name;
    newGuest->roomNumber = room;
    newGuest->next = NULL;
    newGuest->prev = NULL;

    if (head == NULL) {
        head = tail = newGuest;
    } else {
        tail->next = newGuest;
        newGuest->prev = tail;
        tail = newGuest;
    }

    cout << "\n✅ Guest " << name << " checked into Room " << room << " successfully!\n";
}

void push(string name); // forward declare

void checkOut(string name) {
    Guest* temp = head;
    while (temp != NULL && temp->name != name)
        temp = temp->next;

    if (temp == NULL) {
        cout << "\n❌uest not found!\n";
        return;
    }

    if (temp == head)
        head = head->next;
    if (temp == tail)
        tail = tail->prev;
    if (temp->prev)
        temp->prev->next = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;

    cout << "\n👋 Guest " << temp->name << " checked out successfully!\n";
    push(temp->name); // add to recent checkout stack
    delete temp;
}

void displayGuests() {
    if (head == NULL) {
        cout << "\n😶 No guests currently checked in.\n";
        return;
    }
    Guest* temp = head;
    cout << "\n🏨 Current Guests in Hotel:\n";
    while (temp != NULL) {
        cout << "• " << temp->name << " - Room " << temp->roomNumber << endl;
        temp = temp->next;
    }
}

// =======================================================
// QUEUE FUNCTIONS (Waitlist)
// =======================================================
void enqueue(string name) {
    Node* newNode = new Node();
    newNode->name = name;
    newNode->next = NULL;

    if (rearQ == NULL)
        frontQ = rearQ = newNode;
    else {
        rearQ->next = newNode;
        rearQ = newNode;
    }

    cout << "\n⏳ " << name << " added to waitlist.\n";
}

void dequeue() {
    if (frontQ == NULL) {
        cout << "\n❌ Waitlist empty!\n";
        return;
    }
    Node* temp = frontQ;
    cout << "\n✅ " << temp->name << " removed from waitlist (assigned room).\n";
    frontQ = frontQ->next;
    if (frontQ == NULL) rearQ = NULL;
    delete temp;
}

void displayWaitlist() {
    if (frontQ == NULL) {
        cout << "\n😴 Waitlist empty.\n";
        return;
    }
    Node* temp = frontQ;
    cout << "\n🧾 Current Waitlist:\n";
    while (temp != NULL) {
        cout << "• " << temp->name << endl;
        temp = temp->next;
    }
}

// =======================================================
// STACK FUNCTIONS (Recent Checkouts)
// =======================================================
void push(string name) {
    Node* newNode = new Node();
    newNode->name = name;
    newNode->next = topS;
    topS = newNode;
}

void pop() {
    if (topS == NULL) {
        cout << "\n❌ No recent checkouts.\n";
        return;
    }
    Node* temp = topS;
    cout << "\n♻️ Removed recent checkout: " << temp->name << endl;
    topS = topS->next;
    delete temp;
}

void displayRecentCheckouts() {
    if (topS == NULL) {
        cout << "\n🕳️ No recent checkouts.\n";
        return;
    }
    Node* temp = topS;
    cout << "\n🧳 Recent Checkouts:\n";
    while (temp != NULL) {
        cout << "• " << temp->name << endl;
        temp = temp->next;
    }
}

// =======================================================
// HOTEL DATA FUNCTIONS
// =======================================================
void printHotelData(Hotel hotels[], int size) {
    cout << "\n🏨 Hotel Data:\n";
    for (int i = 0; i < size; i++) {
        cout << "\nHotel Name: " << hotels[i].name;
        cout << "\nLocation: " << hotels[i].location;
        cout << "\nRating: " << hotels[i].rating;
        cout << "\nRooms Available: " << hotels[i].availableRooms << "\n";
    }
}

void sortByName(Hotel hotels[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (hotels[i].name > hotels[j].name) {
                swap(hotels[i], hotels[j]);
            }
        }
    }
    cout << "\n🔤 Hotels sorted by Name!\n";
}

void sortByRating(Hotel hotels[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (hotels[i].rating < hotels[j].rating) {
                swap(hotels[i], hotels[j]);
            }
        }
    }
    cout << "\n⭐ Hotels sorted by Highest Rating!\n";
}

void printHotelsByLocation(Hotel hotels[], int size, string loc) {
    cout << "\n📍 Hotels in " << loc << ":\n";
    for (int i = 0; i < size; i++) {
        if (hotels[i].location == loc) {
            cout << "• " << hotels[i].name << " (Rating: " << hotels[i].rating << ", Rooms: " << hotels[i].availableRooms << ")\n";
        }
    }
}

void sortByAvailableRooms(Hotel hotels[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (hotels[i].availableRooms < hotels[j].availableRooms) {
                swap(hotels[i], hotels[j]);
            }
        }
    }
    cout << "\n🏠 Hotels sorted by Maximum Available Rooms!\n";
}

// =======================================================
// PRINT USER BOOKING DATA (Active Guests)
// =======================================================
void printUserBookings() {
    cout << "\n🧾 Current User Bookings:\n";
    displayGuests();
}

// =======================================================
// MAIN MENU
// =======================================================
void menu(Hotel hotels[], int size) {
    int choice;
    do {
        cout << "\n\n========== HOTEL MANAGEMENT SYSTEM ==========\n";
        cout << "1. Check-In Guest\n";
        cout << "2. Check-Out Guest\n";
        cout << "3. Show All Guests\n";
        cout << "4. Show Waitlist\n";
        cout << "5. Show Recent Checkouts\n";
        cout << "6. Show All Hotels\n";
        cout << "7. Sort Hotels by Name\n";
        cout << "8. Sort Hotels by Rating\n";
        cout << "9. Sort Hotels by Rooms\n";
        cout << "10. Show Hotels in Bangalore\n";
        cout << "11. Show Booking Data\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        int room;

        switch (choice) {
        case 1:
            cout << "Enter Guest Name: ";
            cin >> name;
            cout << "Enter Room Number: ";
            cin >> room;
            checkIn(name, room);
            break;
        case 2:
            cout << "Enter Guest Name to Check-Out: ";
            cin >> name;
            checkOut(name);
            break;
        case 3:
            displayGuests();
            break;
        case 4:
            displayWaitlist();
            break;
        case 5:
            displayRecentCheckouts();
            break;
        case 6:
            printHotelData(hotels, size);
            break;
        case 7:
            sortByName(hotels, size);
            break;
        case 8:
            sortByRating(hotels, size);
            break;
        case 9:
            sortByAvailableRooms(hotels, size);
            break;
        case 10:
            printHotelsByLocation(hotels, size, "Bangalore");
            break;
        case 11:
            printUserBookings();
            break;
        case 12:
            cout << "\n👋 Exiting system... Bye!\n";
            break;
        default:
            cout << "\n⚠️ Invalid choice!\n";
        }
    } while (choice != 12);
}

// =======================================================
// MAIN FUNCTION
// =======================================================
int main() {
    Hotel hotels[5] = {
        {"Taj_Palace", "Bangalore", 15, 4.8},
        {"Marriott", "Delhi", 12, 4.6},
        {"Holiday_Inn", "Bangalore", 8, 4.2},
        {"Leela", "Mumbai", 20, 4.9},
        {"Hyatt", "Goa", 10, 4.4}
    };

    menu(hotels, 5);
    return 0;
}