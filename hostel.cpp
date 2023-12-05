#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

const int NUM_HOSTELS = 2;
const int NUM_ROOMS_PER_HOSTEL = 10;

class Student {
public:
    std::string name;
    std::string mobileNumber;
    std::string address;
    std::string gender;  

    Student(const std::string& n, const std::string& mobile, const std::string& addr, const std::string& gen)
        : name(n), mobileNumber(mobile), address(addr), gender(gen) {}
};

class HostelReservationSystem {
private:
    bool rooms[NUM_HOSTELS][NUM_ROOMS_PER_HOSTEL];
    std::vector<Student> reservations;

public:
    HostelReservationSystem() {
        // Initialize all rooms as available
        for (int i = 0; i < NUM_HOSTELS; ++i) {
            for (int j = 0; j < NUM_ROOMS_PER_HOSTEL; ++j) {
                rooms[i][j] = true;
            }
        }
    }

    void displayAvailableRooms() {
        std::cout << "Available Rooms:\n";
        for (int i = 0; i < NUM_HOSTELS; ++i) {
            std::cout << "Hostel " << (i + 1) << ": ";
            for (int j = 0; j < NUM_ROOMS_PER_HOSTEL; ++j) {
                if (rooms[i][j]) {
                    std::cout << std::setw(3) << (j + 1) << " ";
                }
            }
            std::cout << "\n";
        }
    }

    bool reserveRoom(const std::string& name, const std::string& mobile, const std::string& address,
                     const std::string& gender, int roomNumber) {
        int hostelNumber;
        if (gender == "boys") {
            hostelNumber = 1;
        } else if (gender == "girls") {
            hostelNumber = 2;
        } else {
            std::cout << "Invalid gender.\n";
            return false;
        }

        if (roomNumber < 1 || roomNumber > NUM_ROOMS_PER_HOSTEL) {
            std::cout << "Invalid room number.\n";
            return false;
        }

        if (rooms[hostelNumber - 1][roomNumber - 1]) {
            rooms[hostelNumber - 1][roomNumber - 1] = false;
            reservations.emplace_back(name, mobile, address, gender);
            if(hostelNumber==1)
            {
                std::cout << "Room reserved successfully for boys\n";
            }
            else if(hostelNumber==2)
            {
                std::cout << "Room reserved successfully for girl\n";
            }
            return true;
        } else {
            std::cout << "Room is already reserved.\n";
            return false;
        }
    }

    void displayReservations() {
        std::cout << "\nCurrent Reservations:\n";
        for (const auto& student : reservations) {
            std::cout << "Name: " << student.name << "\n";
            std::cout << "Mobile: " << student.mobileNumber << "\n";
            std::cout << "Address: " << student.address << "\n";
            std::cout << "Gender: " << student.gender << "\n\n";
        }
    }
};

int main() {
    HostelReservationSystem hostelSystem;

    while (true) {
        std::cout << "\n1. Display available rooms\n";
        std::cout << "2. Reserve a room\n";
        std::cout << "3. Display reservations\n";
        std::cout << "4. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                hostelSystem.displayAvailableRooms();
                break;

            case 2: {
                std::string name, mobile, address, gender;
                int roomNumber;

                std::cout << "Enter your name: ";
                std::cin.ignore(); 
                std::getline(std::cin, name);

                std::cout << "Enter your mobile number: ";
                std::cin >> mobile;

                std::cout << "Enter your address: ";
                std::cin.ignore(); 
                std::getline(std::cin, address);

                std::cout << "Enter your gender (boys/girls): ";
                std::cin >> gender;

                std::cout << "Enter room number: ";
                std::cin >> roomNumber;

                hostelSystem.reserveRoom(name, mobile, address, gender, roomNumber);
                break;
            }

            case 3:
                hostelSystem.displayReservations();
                break;
            case 4:
                std::cout << "Exiting program.\n";
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}