#include <iostream>
using namespace std;

struct Booking {
    int roomNumber;
    char guestName[50];
    char phoneNumber[15];
    int numberOfDays;
    Booking* next;   
};

Booking* head = NULL;   

void addBooking() {
    Booking* newBooking = new Booking;

    cout << "\nEnter Room Number: ";
    cin >> newBooking->roomNumber;

    cout << "Enter Guest Name: ";
    cin.ignore();              
    cin.getline(newBooking->guestName, 50);

    cout << "Enter Phone Number: ";
    cin.getline(newBooking->phoneNumber, 15);

    cout << "Enter Number of Days: ";
    cin >> newBooking->numberOfDays;

    newBooking->next = NULL;

    if (head == NULL) {
        head = newBooking;
    }
    else {
        Booking* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBooking;
    }

    cout << "\nBooking Added Successfully!\n";
}

void displayBookings() {
    if (head == NULL) {
        cout << "\nNo Bookings Available.\n";
        return;
    }

    Booking* temp = head;
    cout << "\n---- All Bookings ----\n";
    while (temp != NULL) {
        cout << "Room Number: " << temp->roomNumber << endl;
        cout << "Guest Name: " << temp->guestName << endl;
        cout << "Phone Number: " << temp->phoneNumber << endl;
        cout << "Stay Duration (days): " << temp->numberOfDays << endl;
        cout << "-------------------------\n";
        temp = temp->next;
    }
}

void searchBooking() {
    if (head == NULL) {
        cout << "\nNo Bookings Available.\n";
        return;
    }

    int room;
    cout << "\nEnter Room Number to Search: ";
    cin >> room;

    Booking* temp = head;
    while (temp != NULL) {
        if (temp->roomNumber == room) {
            cout << "\nBooking Found:\n";
            cout << "Guest Name: " << temp->guestName << endl;
            cout << "Phone Number: " << temp->phoneNumber << endl;
            cout << "Number of Days: " << temp->numberOfDays << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "\nBooking Not Found!\n";
}

void deleteBooking() {
    if (head == NULL) {
        cout << "\nNo Bookings Available.\n";
        return;
    }

    int room;
    cout << "\nEnter Room Number to Delete: ";
    cin >> room;

    Booking* temp = head;
    Booking* prev = NULL;

    if (temp != NULL && temp->roomNumber == room) {
        head = temp->next; 
        delete temp;        
        cout << "\nBooking Deleted Successfully!\n";
        return;
    }

    while (temp != NULL && temp->roomNumber != room) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "\nBooking Not Found!\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "\nBooking Deleted Successfully!\n";
}

void updateBooking() {
    if (head == NULL) {
        cout << "\nNo Bookings Available.\n";
        return;
    }

    int room;
    cout << "\nEnter Room Number to Update: ";
    cin >> room;

    Booking* temp = head;
    while (temp != NULL) {
        if (temp->roomNumber == room) {
            cout << "\nEnter New Guest Name: ";
            cin.ignore();
            cin.getline(temp->guestName, 50);

            cout << "Enter New Phone Number: ";
            cin.getline(temp->phoneNumber, 15);

            cout << "Enter New Stay Duration: ";
            cin >> temp->numberOfDays;

            cout << "\nBooking Updated Successfully!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "\nBooking Not Found!\n";
}

void menu() {
    cout << "\n===== Hotel Management System =====\n";
    cout << "1. Add Booking\n";
    cout << "2. Display All Bookings\n";
    cout << "3. Search Booking\n";
    cout << "4. Update Booking\n";
    cout << "5. Delete Booking\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    while (true) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: addBooking(); break;
            case 2: displayBookings(); break;
            case 3: searchBooking(); break;
            case 4: updateBooking(); break;
            case 5: deleteBooking(); break;
            case 6: cout << "\nExiting Program...\n"; return 0;
            default: cout << "\nInvalid Choice! Try Again.\n";
        }
    }
}

