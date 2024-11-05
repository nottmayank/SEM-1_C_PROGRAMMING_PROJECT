#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_SEATS 40

typedef struct {
    int seatNumber;
    int isBooked;
    char passengerName[50];
} Seat;

typedef struct {
    int busID;
    char busName[50];
    char origin[30];
    char destination[30];
    int totalSeats;
    Seat seats[MAX_SEATS];
} Bus;

Bus buses[MAX_BUSES];
int busCount = 0;


void addDefaultBuses();
void addBus();
void viewAllBuses();
void bookSeat();
void viewBookings();

int main() {
    int choice;

    
    addDefaultBuses();

    while (1) {
        printf("\n=== Bus Booking System ===\n");
        printf("1. View All Buses\n");
        printf("2. Add New Bus\n");
        printf("3. Book Seat\n");
        printf("4. View Bookings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllBuses();
                break;
            case 2:
                addBus();
                break;
            case 3:
                bookSeat();
                break;
            case 4:
                viewBookings();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}


void addDefaultBuses() {
    strcpy(buses[0].busName, "Express Delhi-Mumbai");
    strcpy(buses[0].origin, "Delhi");
    strcpy(buses[0].destination, "Mumbai");
    buses[0].totalSeats = 30;
    buses[0].busID = 1;
    for (int i = 0; i < buses[0].totalSeats; i++) {
        buses[0].seats[i].seatNumber = i + 1;
        buses[0].seats[i].isBooked = 0;
    }
    busCount++;

    strcpy(buses[1].busName, "Chennai-Bangalore Shuttle");
    strcpy(buses[1].origin, "Chennai");
    strcpy(buses[1].destination, "Bangalore");
    buses[1].totalSeats = 35;
    buses[1].busID = 2;
    for (int i = 0; i < buses[1].totalSeats; i++) {
        buses[1].seats[i].seatNumber = i + 1;
        buses[1].seats[i].isBooked = 0;
    }
    busCount++;

    strcpy(buses[2].busName, "Jaipur-Agra Service");
    strcpy(buses[2].origin, "Jaipur");
    strcpy(buses[2].destination, "Agra");
    buses[2].totalSeats = 40;
    buses[2].busID = 3;
    for (int i = 0; i < buses[2].totalSeats; i++) {
        buses[2].seats[i].seatNumber = i + 1;
        buses[2].seats[i].isBooked = 0;
    }
    busCount++;
}


void addBus() {
    if (busCount >= MAX_BUSES) {
        printf("Cannot add more buses. Maximum limit reached.\n");
        return;
    }

    Bus *bus = &buses[busCount];
    bus->busID = busCount + 1;

    printf("Enter Bus Name: ");
    scanf(" %[^\n]", bus->busName);

    printf("Enter Origin: ");
    scanf(" %[^\n]", bus->origin);

    printf("Enter Destination: ");
    scanf(" %[^\n]", bus->destination);

    printf("Enter Total Seats (Max %d): ", MAX_SEATS);
    scanf("%d", &bus->totalSeats);

    if (bus->totalSeats > MAX_SEATS) {
        printf("Invalid seat count. Setting to max allowable seats (%d).\n", MAX_SEATS);
        bus->totalSeats = MAX_SEATS;
    }

    for (int i = 0; i < bus->totalSeats; i++) {
        bus->seats[i].seatNumber = i + 1;
        bus->seats[i].isBooked = 0;
        strcpy(bus->seats[i].passengerName, "");
    }

    busCount++;
    printf("Bus added successfully!\n");
}


void viewAllBuses() {
    printf("\n--- List of Buses ---\n");
    for (int i = 0; i < busCount; i++) {
        Bus bus = buses[i];
        printf("Bus ID: %d\n", bus.busID);
        printf("Bus Name: %s\n", bus.busName);
        printf("Origin: %s\n", bus.origin);
        printf("Destination: %s\n", bus.destination);
        printf("Total Seats: %d\n", bus.totalSeats);
        printf("---------------------\n");
    }
}


void bookSeat() {
    int busID, seatNumber;
    char passengerName[50];

    printf("Enter Bus ID to book: ");
    scanf("%d", &busID);

    if (busID <= 0 || busID > busCount) {
        printf("Invalid Bus ID.\n");
        return;
    }

    Bus *bus = &buses[busID - 1];

    printf("Enter Seat Number (1 - %d): ", bus->totalSeats);
    scanf("%d", &seatNumber);

    if (seatNumber <= 0 || seatNumber > bus->totalSeats) {
        printf("Invalid Seat Number.\n");
        return;
    }

    Seat *seat = &bus->seats[seatNumber - 1];

    if (seat->isBooked) {
        printf("Seat already booked.\n");
        return;
    }

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", passengerName);

    seat->isBooked = 1;
    strcpy(seat->passengerName, passengerName);

    printf("Seat booked successfully!\n");
}


void viewBookings() {
    int busID;

    printf("Enter Bus ID to view bookings: ");
    scanf("%d", &busID);

    if (busID <= 0 || busID > busCount) {
        printf("Invalid Bus ID.\n");
        return;
    }

    Bus bus = buses[busID - 1];

    printf("\n--- Bookings for Bus %s ---\n", bus.busName);
    for (int i = 0; i < bus.totalSeats; i++) {
        if (bus.seats[i].isBooked) {
            printf("Seat Number: %d, Passenger Name: %s\n", bus.seats[i].seatNumber, bus.seats[i].passengerName);
        }
    }
}

