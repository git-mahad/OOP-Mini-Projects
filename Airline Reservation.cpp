#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <unistd.h> 
using namespace std;

class Flight {
private:
    int flightNumber;
    string destination;
    string departureTime;
    int totalSeats;
    int availableSeats;

public:
    Flight(int fNumber, string dest, string dTime, int seats)
        : flightNumber(fNumber), destination(dest), departureTime(dTime), totalSeats(seats), availableSeats(seats) {}

    int getFlightNumber() const { return flightNumber; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    int getAvailableSeats() const { return availableSeats; }

    bool bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        }
        return false;
    }

    bool cancelSeat() {
        if (availableSeats < totalSeats) {
            availableSeats++;
            return true;
        }
        return false;
    }

    void displayFlightDetails() const {
        cout << setw(10) << flightNumber << setw(20) << destination
             << setw(20) << departureTime << setw(15) << availableSeats << endl;
    }
};

// Passenger class to represent a passenger
class Passenger {
private:
    string name;
    int age;
    string passportNumber;

public:
    Passenger(string pname, int page, string pPassportNumber)
        : name(pname), age(page), passportNumber(pPassportNumber) {}

    string getName() const { return name; }
    string getPassportNumber() const { return passportNumber; }

    void displayPassengerDetails() const {
        cout << setw(20) << name << setw(10) << age << setw(20) << passportNumber << endl;
    }
};

class Reservation {
private:
    static int reservationIDCounter;
    int reservationID;
    Passenger passenger;
    Flight* flight;

public:
    Reservation(Passenger p, Flight* f)
        : reservationID(++reservationIDCounter), passenger(p), flight(f) {}

    int getReservationID() const { return reservationID; }
    Passenger getPassenger() const { return passenger; }
    Flight* getFlight() const { return flight; }

    void displayReservationDetails() const {
        cout << "Reservation ID: " << reservationID << endl;
        cout << "Passenger Name: " << passenger.getName() << endl;
        cout << "Flight Number : " << flight->getFlightNumber() << endl;
        cout << "Destination   : " << flight->getDestination() << endl;
        cout << "Departure Time: " << flight->getDepartureTime() << endl;
    }
};

int Reservation::reservationIDCounter = 1000;

class FlightReservationSystem {
private:
    vector<Flight> flights;
    vector<Reservation> reservations;

public:
    void addSampleFlights() {
        flights.emplace_back(101, "New York", "10:00 AM", 50);
        flights.emplace_back(102, "Los Angeles", "12:30 PM", 60);
        flights.emplace_back(103, "Chicago", "3:15 PM", 40);
        flights.emplace_back(104, "Miami", "6:45 PM", 30);
    }

    void displayAllFlights() {
        system("CLS");
        if (flights.empty()) {
            cout << "No flights available.\n";
            sleep(2);
            return;
        }

        cout << setw(10) << "Flight No" << setw(20) << "Destination"
             << setw(20) << "Departure Time" << setw(15) << "Seats Available\n";
        cout << "---------------------------------------------------------------\n";
        for (const auto& flight : flights) {
            flight.displayFlightDetails();
        }
        sleep(3);
    }

    void makeReservation() {
        system("CLS");
        if (flights.empty()) {
            cout << "No flights available for reservation.\n";
            sleep(2);
            return;
        }

        displayAllFlights();

        int flightNumber;
        cout << "\nEnter Flight Number to book: ";
        cin >> flightNumber;

        Flight* selectedFlight = nullptr;
        for (auto& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                selectedFlight = &flight;
                break;
            }
        }

        if (selectedFlight == nullptr) {
            cout << "Invalid Flight Number. Reservation failed.\n";
            sleep(2);
            return;
        }

        if (selectedFlight->getAvailableSeats() == 0) {
            cout << "No available seats on this flight.\n";
            sleep(2);
            return;
        }

        string name, passportNumber;
        int age;
        cin.ignore(); // Clear input buffer
        cout << "Enter Passenger Name: ";
        getline(cin, name);
        cout << "Enter Passenger Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Passport Number: ";
        getline(cin, passportNumber);

        Passenger passenger(name, age, passportNumber);
        if (selectedFlight->bookSeat()) {
            reservations.emplace_back(passenger, selectedFlight);
            cout << "Reservation successful! Your Reservation ID is " << reservations.back().getReservationID() << ".\n";
        } else {
            cout << "Failed to book a seat.\n";
        }
        sleep(2);
    }

    void cancelReservation() {
        system("CLS");
        if (reservations.empty()) {
            cout << "No reservations to cancel.\n";
            sleep(2);
            return;
        }

        int reservationID;
        cout << "Enter Reservation ID to cancel: ";
        cin >> reservationID;

        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if (it->getReservationID() == reservationID) {
                Flight* flight = it->getFlight();
                if (flight->cancelSeat()) {
                    cout << "Reservation ID " << reservationID << " canceled successfully.\n";
                    reservations.erase(it);
                    sleep(2);
                    return;
                }
            }
        }
        cout << "Reservation ID not found.\n";
        sleep(2);
    }

    void displayAllReservations() {
        system("CLS");
        if (reservations.empty()) {
            cout << "No reservations to display.\n";
            sleep(2);
            return;
        }

        for (const auto& reservation : reservations) {
            reservation.displayReservationDetails();
            cout << "-----------------------------------------\n";
        }
        sleep(3);
    }
};

int main() {
    FlightReservationSystem system;
    system.addSampleFlights();
    int choice;

    while (true) {
        system("CLS");
        cout << "------ Airline Reservation System ------\n";
        cout << "1. Display All Flights\n";
        cout << "2. Make Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. Display All Reservations\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.displayAllFlights();
            break;
        case 2:
            system.makeReservation();
            break;
        case 3:
            system.cancelReservation();
            break;
        case 4:
            system.displayAllReservations();
            break;
        case 5:
            cout << "Exiting the system. Thank you!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
            sleep(1);
        }
    }
    return 0;
}
