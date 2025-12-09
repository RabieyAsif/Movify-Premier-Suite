#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Movie structure
struct Movie {
    int id;
    char title[50];
    char genre[20];
    int duration;
    float price;
    int totalRating;
    int ratingCount;
};

// Snack structure
struct Snack {
    char name[20];
    float price;
};

// Global arrays
Movie movies[10] = {
    {1, "The Silent Dawn", "Drama", 128, 1000, 0, 0},
    {2, "Galaxy Quest", "Sci-Fi", 140, 1200, 0, 0},
    {3, "Shadow Realm", "Thriller", 110, 900, 0, 0},
    {4, "Beyond the Stars", "Adventure", 135, 1100, 0, 0},
    {5, "Mystic River", "Mystery", 115, 950, 0, 0},
    {6, "Lost Horizons", "Drama", 125, 1050, 0, 0},
    {7, "Eternal Night", "Horror", 130, 1150, 0, 0},
    {8, "Solar Winds", "Sci-Fi", 150, 1250, 0, 0},
    {9, "Hidden Truths", "Crime", 120, 1000, 0, 0},
    {10, "Infinite Loop", "Sci-Fi", 145, 1300, 0, 0}
};

Snack snacks[5] = {
    {"Popcorn", 250},
    {"Soda", 150},
    {"Nachos", 200},
    {"Hotdog", 180},
    {"Candy", 100}
};

// Seat Map
char seats[6][8];

// Viewer Type
int viewerType = 1;
float viewerDiscount = 0;

// Will store last booking summary
string lastReceipt = "";

// Initialize seats
void initSeats() {
    for(int i=0;i<6;i++)
        for(int j=0;j<8;j++)
            seats[i][j] = 'O';
}

// Welcome Screen
void welcomeScreen() {
    cout << "\n=============================================\n";
    cout << "          WELCOME TO MOVIFY PREMIER SUITE     \n";
    cout << "=============================================\n";
    cout << "        Your Ultimate Cinema Experience!      \n";
    cout << "---------------------------------------------\n";
}

// Choose viewer type
void chooseViewerType() {
    cout << "\nChoose Viewer Type:\n";
    cout << "1. Regular (0% off)\n2. Student (10% off)\n";
    cout << "3. Senior (15% off)\n4. Premium (20% off)\n";
    cout << "Your choice: ";
    
    while(!(cin >> viewerType) || viewerType < 1 || viewerType > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Choose 1-4: ";
    }

    if(viewerType==2) viewerDiscount=10;
    else if(viewerType==3) viewerDiscount=15;
    else if(viewerType==4) viewerDiscount=20;
    else viewerDiscount=0;

    cout << "Discount applied: " << viewerDiscount << "%\n";
}

// Show movies
void showMovies(Movie *m, int size) {
    cout << "\nMovies:\n";
    for(int i=0;i<size;i++){
        cout << m[i].id << ". " << m[i].title 
             << " | Genre: " << m[i].genre
             << " | Duration: " << m[i].duration << " min"
             << " | Price: " << m[i].price;
        if(m[i].ratingCount>0){
            float avg = (float)m[i].totalRating / m[i].ratingCount;
            cout << " | Rating: " << avg << "/5";
        }
        cout << "\n";
    }
}

// Show seats
void showSeats() {
    cout << "\nSeats (O=available, X=booked):\n  1 2 3 4 5 6 7 8\n";
    for(int i=0;i<6;i++){
        cout << char('A'+i) << " ";
        for(int j=0;j<8;j++)
            cout << seats[i][j] << " ";
        cout << "\n";
    }
}

// Order snacks
float orderSnacks() {
    float total = 0;
    char choice;
    cout << "\nDo you want to order snacks? (y/n): ";
    cin >> choice;
    if(choice!='y' && choice!='Y') return 0;

    int opt;
    while(true){
        cout << "\nSnacks Menu:\n";
        for(int i=0;i<5;i++)
            cout << i+1 << ". " << snacks[i].name << " | " << snacks[i].price << " PKR\n";
        cout << "6. Done\nChoose snack: ";
        while(!(cin >> opt) || opt < 1 || opt > 6) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid option! Choose 1-6: ";
        }

        if(opt==6) break;

        total += snacks[opt-1].price;
        cout << snacks[opt-1].name << " added.\n";
    }
    return total;
}

// Give movie review
void giveReview(Movie *m, int size, int movieId) {
    for(int i=0;i<size;i++){
        if(m[i].id==movieId){
            int rate;
            cout << "Rate this movie (1-5): ";
            while(!(cin >> rate) || rate < 1 || rate > 5){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid rating. Enter 1-5: ";
            }
            m[i].totalRating += rate;
            m[i].ratingCount++;
            cout << "Thanks for rating!\n";
            break;
        }
    }
}

// Book seat
void bookSeat(Movie *m, int size) {
    int movieId;
    cout << "Enter movie ID to book (0 to go back): ";
    while(!(cin >> movieId)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a valid movie ID: ";
    }
    if(movieId==0) return;

    float price = 0;
    bool found = false;
    for(int i=0;i<size;i++){
        if(m[i].id == movieId){
            price = m[i].price;
            found = true;
            break;
        }
    }
    if(!found){
        cout << "Movie ID not found!\n";
        return;
    }

    showSeats();

    char seat[3];
    cout << "Choose seat (e.g., A1): ";
    cin >> seat;
    int row = seat[0]-'A';
    int col = seat[1]-'1';

    if(row<0 || row>5 || col<0 || col>7){
        cout << "Invalid seat!\n";
        return;
    }

    if(seats[row][col]=='X'){
        cout << "Seat already booked!\n";
        return;
    }

    seats[row][col]='X';

    float snackCost = orderSnacks();
    float finalPrice = price * (100-viewerDiscount)/100 + snackCost;

    cout << "\a"; // booking sound

    // Order Summary
    cout << "\n----------- ORDER SUMMARY -----------\n";
    cout << "Movie: " << m[movieId-1].title << endl;
    cout << "Genre: " << m[movieId-1].genre << endl;
    cout << "Duration: " << m[movieId-1].duration << " minutes\n";
    cout << "Seat: " << seat << endl;
    cout << "Snacks Total: " << snackCost << " PKR\n";
    cout << "Final Amount: " << finalPrice << " PKR\n";
    cout << "-------------------------------------\n";

    // Save summary to string
    lastReceipt =
    "----------- MOVIFY BOOKING RECEIPT -----------\n"
    "Movie: " + string(m[movieId-1].title) + "\n" +
    "Genre: " + string(m[movieId-1].genre) + "\n" +
    "Duration: " + to_string(m[movieId-1].duration) + " minutes\n" +
    "Seat: " + string(seat) + "\n" +
    "Snacks Total: " + to_string(snackCost) + " PKR\n" +
    "Final Amount: " + to_string(finalPrice) + " PKR\n"
    "----------------------------------------------\n";

    giveReview(m, size, movieId);

    cout << "\nThank you for choosing Movify Premier Suite!\n";
    cout << "Enjoy your show!\n";
}

// Save receipt to file
void downloadReceipt() {
    if(lastReceipt == "") {
        cout << "No booking available to save!\n";
        return;
    }

    ofstream file("BookingReceipt.txt");
    file << lastReceipt;
    file.close();

    cout << "Your receipt has been saved as 'BookingReceipt.txt'.\n";
}

// View saved receipt from file
void viewSavedReceipt() {
    ifstream file("BookingReceipt.txt");
    if (!file) {
        cout << "No saved receipt found!\n";
        return;
    }

    cout << "\n-------- SAVED BOOKING RECEIPT --------\n";

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }

    cout << "---------------------------------------\n";

    file.close();
}

int main() {
    welcomeScreen();
    initSeats();

    chooseViewerType();

    int choice;
    while(true){
        cout << "\n1. Show Movies\n2. Book Ticket\n3. Download Booking Receipt\n4. View Saved Receipt\n5. Exit\nChoose: ";
        while(!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Choose 1-5: ";
        }

        if(choice == 1) {
            showMovies(movies, 10);
        }
        else if(choice == 2) {
            bookSeat(movies, 10);
        }
        else if(choice == 3) {
            downloadReceipt();
        }
        else if(choice == 4) {
            viewSavedReceipt();
        }
        else if(choice == 5) {
            break;
        }
        else {
            cout << "Invalid option!\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}