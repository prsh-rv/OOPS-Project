#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// ==================== Vehicle Class (Base) ====================
class Vehicle {
protected:
    string vehicleNumber;
    string vehicleType;
    time_t entryTime;

public:
    Vehicle(string num, string type) : vehicleNumber(num), vehicleType(type) {
        entryTime = time(0);
    }

    virtual ~Vehicle() {}

    string getVehicleNumber() const { return vehicleNumber; }
    string getVehicleType() const { return vehicleType; }
    time_t getEntryTime() const { return entryTime; }
    void setEntryTime(time_t t) { entryTime = t; }

    virtual double getHourlyRate() const = 0;

    virtual void displayInfo() const {
        cout << "Vehicle: " << vehicleNumber << " | Type: " << vehicleType;
    }
};

// ==================== Derived Vehicle Classes ====================
class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num, "Bike") {}
    
    double getHourlyRate() const override {
        return 10.0;
    }
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num, "Car") {}
    
    double getHourlyRate() const override {
        return 20.0;
    }
};

class Truck : public Vehicle {
public:
    Truck(string num) : Vehicle(num, "Truck") {}
    
    double getHourlyRate() const override {
        return 40.0;
    }
};

// ==================== Parking Slot Class ====================
class ParkingSlot {
private:
    int slotNumber;
    string slotType;
    bool isOccupied;
    Vehicle* parkedVehicle;

public:
    ParkingSlot(int num, string type) 
        : slotNumber(num), slotType(type), isOccupied(false), parkedVehicle(nullptr) {}

    int getSlotNumber() const { return slotNumber; }
    string getSlotType() const { return slotType; }
    bool getOccupiedStatus() const { return isOccupied; }
    Vehicle* getParkedVehicle() const { return parkedVehicle; }

    bool parkVehicle(Vehicle* vehicle) {
        if (!isOccupied && vehicle->getVehicleType() == slotType) {
            parkedVehicle = vehicle;
            isOccupied = true;
            return true;
        }
        return false;
    }

    Vehicle* removeVehicle() {
        if (isOccupied) {
            Vehicle* temp = parkedVehicle;
            parkedVehicle = nullptr;
            isOccupied = false;
            return temp;
        }
        return nullptr;
    }

    void displaySlot() const {
        if (isOccupied) {
            cout << "[X]";
        } else {
            cout << "[ ]";
        }
    }
};

// ==================== Ticket Class ====================
class Ticket {
private:
    string ticketId;
    string vehicleNumber;
    int slotNumber;
    time_t entryTime;
    double hourlyRate;

public:
    Ticket(string vNum, int slot, double rate, time_t entry = 0) 
        : vehicleNumber(vNum), slotNumber(slot), hourlyRate(rate) {
        if (entry == 0) {
            entryTime = time(0);
        } else {
            entryTime = entry;
        }
        ticketId = "TKT" + to_string(entryTime) + to_string(slot);
    }

    string getTicketId() const { return ticketId; }
    string getVehicleNumber() const { return vehicleNumber; }
    int getSlotNumber() const { return slotNumber; }
    time_t getEntryTime() const { return entryTime; }
    double getHourlyRate() const { return hourlyRate; }

    void displayTicket() const {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║         PARKING TICKET             ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "Ticket ID: " << ticketId << endl;
        cout << "Vehicle: " << vehicleNumber << endl;
        cout << "Slot: " << slotNumber << endl;
        cout << "Entry Time: " << ctime(&entryTime);
        cout << "Rate: ₹" << hourlyRate << "/hour" << endl;
        cout << "════════════════════════════════════" << endl;
    }
};

// ==================== Payment Class ====================
class Payment {
private:
    double amount;
    time_t paymentTime;
    string paymentMethod;

public:
    Payment(double amt, string method) 
        : amount(amt), paymentMethod(method) {
        paymentTime = time(0);
    }

    void displayReceipt(string vehicleNum, double hours, double rate) const {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║         PAYMENT RECEIPT            ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "Vehicle: " << vehicleNum << endl;
        cout << "Duration: " << fixed << setprecision(2) << hours << " hours" << endl;
        cout << "Rate: ₹" << rate << "/hour" << endl;
        cout << "Amount: ₹" << amount << endl;
        cout << "Method: " << paymentMethod << endl;
        cout << "Time: " << ctime(&paymentTime);
        cout << "════════════════════════════════════" << endl;
        cout << "    Thank you! Visit again!" << endl;
        cout << "════════════════════════════════════" << endl;
    }
};

// ==================== Monthly Pass Class ====================
class MonthlyPass {
private:
    string passId;
    string vehicleNumber;
    time_t startDate;
    time_t expiryDate;
    bool isActive;

public:
    MonthlyPass(string vNum, time_t start = 0) : vehicleNumber(vNum) {
        if (start == 0) {
            startDate = time(0);
        } else {
            startDate = start;
        }
        expiryDate = startDate + (30 * 24 * 60 * 60);
        passId = "PASS" + to_string(startDate);
        isActive = true;
    }

    string getVehicleNumber() const { return vehicleNumber; }
    string getPassId() const { return passId; }
    time_t getStartDate() const { return startDate; }
    time_t getExpiryDate() const { return expiryDate; }
    
    bool checkValidity() const {
        return isActive && (time(0) < expiryDate);
    }

    void displayPass() const {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║         MONTHLY PASS               ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "Pass ID: " << passId << endl;
        cout << "Vehicle: " << vehicleNumber << endl;
        cout << "Start Date: " << ctime(&startDate);
        cout << "Valid till: " << ctime(&expiryDate);
        cout << "Status: " << (checkValidity() ? "✓ Active" : "✗ Expired") << endl;
        cout << "════════════════════════════════════" << endl;
    }
};

// ==================== Parking Floor Class ====================
class ParkingFloor {
private:
    int floorNumber;
    vector<ParkingSlot*> slots;

public:
    ParkingFloor(int num, int bikeSlots, int carSlots, int truckSlots) 
        : floorNumber(num) {
        int slotNum = floorNumber * 100;
        
        for (int i = 0; i < bikeSlots; i++) {
            slots.push_back(new ParkingSlot(++slotNum, "Bike"));
        }
        for (int i = 0; i < carSlots; i++) {
            slots.push_back(new ParkingSlot(++slotNum, "Car"));
        }
        for (int i = 0; i < truckSlots; i++) {
            slots.push_back(new ParkingSlot(++slotNum, "Truck"));
        }
    }

    ~ParkingFloor() {
        for (auto slot : slots) {
            delete slot;
        }
    }

    int getFloorNumber() const { return floorNumber; }

    ParkingSlot* findAvailableSlot(string vehicleType) {
        for (auto slot : slots) {
            if (!slot->getOccupiedStatus() && slot->getSlotType() == vehicleType) {
                return slot;
            }
        }
        return nullptr;
    }

    ParkingSlot* findSlotByNumber(int slotNum) {
        for (auto slot : slots) {
            if (slot->getSlotNumber() == slotNum) {
                return slot;
            }
        }
        return nullptr;
    }

    void displayFloorStatus() const {
        cout << "\n--- Floor " << floorNumber << " ---" << endl;
        cout << "Bikes:  ";
        for (auto slot : slots) {
            if (slot->getSlotType() == "Bike") {
                slot->displaySlot();
                cout << " ";
            }
        }
        cout << "\nCars:   ";
        for (auto slot : slots) {
            if (slot->getSlotType() == "Car") {
                slot->displaySlot();
                cout << " ";
            }
        }
        cout << "\nTrucks: ";
        for (auto slot : slots) {
            if (slot->getSlotType() == "Truck") {
                slot->displaySlot();
                cout << " ";
            }
        }
        cout << endl;
    }

    int getAvailableCount(string type) const {
        int count = 0;
        for (auto slot : slots) {
            if (!slot->getOccupiedStatus() && slot->getSlotType() == type) {
                count++;
            }
        }
        return count;
    }
};

// ==================== Smart Parking System ====================
class SmartParkingSystem {
private:
    vector<ParkingFloor*> floors;
    map<string, Ticket*> activeTickets;
    map<string, MonthlyPass*> monthlyPasses;
    double totalRevenue;

    // File storage functions
    void saveTicketsToFile() {
        ofstream file("parking_tickets.txt");
        for (auto& pair : activeTickets) {
            Ticket* t = pair.second;
            file << t->getVehicleNumber() << ","
                 << t->getSlotNumber() << ","
                 << t->getHourlyRate() << ","
                 << t->getEntryTime() << "\n";
        }
        file.close();
    }

    void loadTicketsFromFile() {
        ifstream file("parking_tickets.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string vNum, slotStr, rateStr, timeStr;
            
            getline(ss, vNum, ',');
            getline(ss, slotStr, ',');
            getline(ss, rateStr, ',');
            getline(ss, timeStr, ',');

            int slot = stoi(slotStr);
            double rate = stod(rateStr);
            time_t entry = stoll(timeStr);

            Ticket* ticket = new Ticket(vNum, slot, rate, entry);
            activeTickets[vNum] = ticket;

            // Recreate vehicle and park it
            Vehicle* vehicle = nullptr;
            if (rate == 10.0) vehicle = new Bike(vNum);
            else if (rate == 20.0) vehicle = new Car(vNum);
            else if (rate == 40.0) vehicle = new Truck(vNum);

            if (vehicle) {
                vehicle->setEntryTime(entry);
                for (auto floor : floors) {
                    ParkingSlot* s = floor->findSlotByNumber(slot);
                    if (s) {
                        s->parkVehicle(vehicle);
                        break;
                    }
                }
            }
        }
        file.close();
    }

    void savePassesToFile() {
        ofstream file("monthly_passes.txt");
        for (auto& pair : monthlyPasses) {
            MonthlyPass* p = pair.second;
            file << p->getVehicleNumber() << ","
                 << p->getPassId() << ","
                 << p->getStartDate() << ","
                 << p->getExpiryDate() << "\n";
        }
        file.close();
    }

    void loadPassesFromFile() {
        ifstream file("monthly_passes.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string vNum, passId, startStr, expiryStr;
            
            getline(ss, vNum, ',');
            getline(ss, passId, ',');
            getline(ss, startStr, ',');
            getline(ss, expiryStr, ',');

            time_t start = stoll(startStr);
            MonthlyPass* pass = new MonthlyPass(vNum, start);
            monthlyPasses[vNum] = pass;
        }
        file.close();
    }

    void saveRevenueToFile() {
        ofstream file("revenue.txt");
        file << totalRevenue;
        file.close();
    }

    void loadRevenueFromFile() {
        ifstream file("revenue.txt");
        if (file.is_open()) {
            file >> totalRevenue;
            file.close();
        }
    }

public:
    SmartParkingSystem(int numFloors) : totalRevenue(0.0) {
        for (int i = 1; i <= numFloors; i++) {
            floors.push_back(new ParkingFloor(i, 5, 5, 2));
        }
        loadTicketsFromFile();
        loadPassesFromFile();
        loadRevenueFromFile();
    }

    ~SmartParkingSystem() {
        saveTicketsToFile();
        savePassesToFile();
        saveRevenueToFile();

        for (auto floor : floors) {
            delete floor;
        }
        for (auto& pair : activeTickets) {
            delete pair.second;
        }
        for (auto& pair : monthlyPasses) {
            delete pair.second;
        }
    }

    void displayParkingStatus() {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║    PARKING SYSTEM STATUS           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        
        for (auto floor : floors) {
            floor->displayFloorStatus();
        }

        cout << "\n--- Available Slots Summary ---" << endl;
        int totalBike = 0, totalCar = 0, totalTruck = 0;
        for (auto floor : floors) {
            totalBike += floor->getAvailableCount("Bike");
            totalCar += floor->getAvailableCount("Car");
            totalTruck += floor->getAvailableCount("Truck");
        }
        cout << "Bikes: " << totalBike << " | Cars: " << totalCar << " | Trucks: " << totalTruck << endl;
        cout << "Legend: [ ] = Available, [X] = Occupied" << endl;
    }

    bool parkVehicle(string vehicleNum, string vehicleType) {
        if (monthlyPasses.find(vehicleNum) != monthlyPasses.end()) {
            if (monthlyPasses[vehicleNum]->checkValidity()) {
                cout << "\n✓ Monthly pass holder detected!" << endl;
            }
        }

        Vehicle* vehicle = nullptr;
        if (vehicleType == "Bike") {
            vehicle = new Bike(vehicleNum);
        } else if (vehicleType == "Car") {
            vehicle = new Car(vehicleNum);
        } else if (vehicleType == "Truck") {
            vehicle = new Truck(vehicleNum);
        } else {
            cout << "✗ Invalid vehicle type!" << endl;
            return false;
        }

        for (auto floor : floors) {
            ParkingSlot* slot = floor->findAvailableSlot(vehicleType);
            if (slot) {
                slot->parkVehicle(vehicle);
                Ticket* ticket = new Ticket(vehicleNum, slot->getSlotNumber(), vehicle->getHourlyRate());
                activeTickets[vehicleNum] = ticket;
                ticket->displayTicket();
                cout << "✓ Vehicle parked successfully on Floor " << floor->getFloorNumber() << "!" << endl;
                saveTicketsToFile();
                return true;
            }
        }

        cout << "✗ No available slot for " << vehicleType << "!" << endl;
        delete vehicle;
        return false;
    }

    bool exitVehicle(string vehicleNum, string paymentMethod) {
        if (activeTickets.find(vehicleNum) == activeTickets.end()) {
            cout << "✗ No active ticket found for this vehicle!" << endl;
            return false;
        }

        Ticket* ticket = activeTickets[vehicleNum];
        int slotNum = ticket->getSlotNumber();

        Vehicle* vehicle = nullptr;
        ParkingSlot* slot = nullptr;
        for (auto floor : floors) {
            slot = floor->findSlotByNumber(slotNum);
            if (slot) {
                vehicle = slot->removeVehicle();
                break;
            }
        }

        if (!vehicle) {
            cout << "✗ Error: Vehicle not found in slot!" << endl;
            return false;
        }

        bool isPassHolder = false;
        if (monthlyPasses.find(vehicleNum) != monthlyPasses.end()) {
            if (monthlyPasses[vehicleNum]->checkValidity()) {
                isPassHolder = true;
            }
        }

        if (!isPassHolder) {
            time_t exitTime = time(0);
            double seconds = difftime(exitTime, ticket->getEntryTime());
            double hours = seconds / 3600.0;
            
            if (hours < 1.0) hours = 1.0;
            
            double amount = hours * ticket->getHourlyRate();
            totalRevenue += amount;

            Payment payment(amount, paymentMethod);
            payment.displayReceipt(vehicleNum, hours, ticket->getHourlyRate());
        } else {
            cout << "\n✓ Monthly pass holder - No charges!" << endl;
            monthlyPasses[vehicleNum]->displayPass();
        }

        delete vehicle;
        delete ticket;
        activeTickets.erase(vehicleNum);
        saveTicketsToFile();
        saveRevenueToFile();

        cout << "\n✓ Vehicle exited successfully!" << endl;
        return true;
    }

    void purchaseMonthlyPass(string vehicleNum) {
        if (monthlyPasses.find(vehicleNum) != monthlyPasses.end()) {
            if (monthlyPasses[vehicleNum]->checkValidity()) {
                cout << "✗ Active monthly pass already exists!" << endl;
                monthlyPasses[vehicleNum]->displayPass();
                return;
            }
        }

        MonthlyPass* pass = new MonthlyPass(vehicleNum);
        monthlyPasses[vehicleNum] = pass;
        
        cout << "\n✓ Monthly pass purchased successfully!" << endl;
        cout << "Amount Paid: ₹500" << endl;
        pass->displayPass();
        savePassesToFile();
    }

    void viewMonthlyPass(string vehicleNum) {
        if (monthlyPasses.find(vehicleNum) != monthlyPasses.end()) {
            monthlyPasses[vehicleNum]->displayPass();
        } else {
            cout << "\n✗ No monthly pass found for this vehicle!" << endl;
        }
    }

    void displayRevenue() const {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║      REVENUE STATISTICS            ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "Total Revenue: ₹" << fixed << setprecision(2) << totalRevenue << endl;
        cout << "Active Vehicles: " << activeTickets.size() << endl;
        cout << "Monthly Pass Holders: " << monthlyPasses.size() << endl;
        cout << "════════════════════════════════════" << endl;
    }
};

// ==================== Main Application ====================
int main() {
    SmartParkingSystem parking(3);
    int choice;
    
    cout << "\n╔═══════════════════════════════════════╗" << endl;
    cout << "║         PARKING MANAGEMENT SYSTEM     ║" << endl;
    cout << "╚═══════════════════════════════════════╝" << endl;

    while (true) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. View Parking Status" << endl;
        cout << "2. Park Vehicle (Entry)" << endl;
        cout << "3. Exit Vehicle (With Payment)" << endl;
        cout << "4. Purchase Monthly Pass" << endl;
        cout << "5. View Monthly Pass Details" << endl;
        cout << "6. View Revenue Statistics" << endl;
        cout << "0. Exit System" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string vehicleNum, vehicleType, paymentMethod;

        switch (choice) {
            case 1:
                parking.displayParkingStatus();
                break;

            case 2:
                cout << "\n--- VEHICLE ENTRY ---" << endl;
                cout << "Enter vehicle number: ";
                getline(cin, vehicleNum);
                cout << "Enter vehicle type (Bike/Car/Truck): ";
                getline(cin, vehicleType);
                parking.parkVehicle(vehicleNum, vehicleType);
                break;

            case 3:
                cout << "\n--- VEHICLE EXIT ---" << endl;
                cout << "Enter vehicle number: ";
                getline(cin, vehicleNum);
                cout << "Payment method (Cash/Card/UPI): ";
                getline(cin, paymentMethod);
                parking.exitVehicle(vehicleNum, paymentMethod);
                break;

            case 4:
                cout << "\n--- PURCHASE MONTHLY PASS ---" << endl;
                cout << "Enter vehicle number: ";
                getline(cin, vehicleNum);
                parking.purchaseMonthlyPass(vehicleNum);
                break;

            case 5:
                cout << "\n--- VIEW MONTHLY PASS ---" << endl;
                cout << "Enter vehicle number: ";
                getline(cin, vehicleNum);
                parking.viewMonthlyPass(vehicleNum);
                break;

            case 6:
                parking.displayRevenue();
                break;

            case 0:
                cout << "\n╔════════════════════════════════════╗" << endl;
                cout << "║  Thank you for using our system!   ║" << endl;
                cout << "║       Data saved successfully      ║" << endl;
                cout << "╚════════════════════════════════════╝" << endl;
                return 0;

            default:
                cout << "\n✗ Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}