# 🚗 Parking Management System (C++)

A **menu-driven console application** that simulates a **Parking Management System** for managing multiple floors, vehicle parking, payments, and monthly passes.  
It automatically saves and loads data (vehicles, passes, and revenue) using local text files.

---

## 📜 Features

✅ **Multi-Floor Parking**  
- Supports multiple floors with customizable slot distribution for **Bikes**, **Cars**, and **Trucks**.  
- Displays real-time availability and occupancy.

✅ **Vehicle Entry & Exit System**  
- Assigns available parking slots automatically.  
- Generates **Parking Tickets** on entry.  
- Calculates charges based on hourly rates.  
- Accepts different payment methods (Cash/Card/UPI).  

✅ **Monthly Pass System**  
- Allows users to purchase and view **monthly passes**.  
- Pass holders can park and exit without payment during validity.  
- Pass validity automatically expires after 30 days.

✅ **Revenue Management**  
- Tracks and displays **total system revenue**.  
- Persists data even after restarting the application.

✅ **File Persistence (Data Saving)**  
- Saves all data to text files:
  - `parking_tickets.txt`
  - `monthly_passes.txt`
  - `revenue.txt`
- Automatically loads previous data at startup.

---

## 🏗️ Project Structure

SmartParkingSystem/
│
├── main.cpp # Main program (contains all class definitions and logic)
├── parking_tickets.txt # Saved active parking tickets (auto-generated)
├── monthly_passes.txt # Saved monthly passes (auto-generated)
├── revenue.txt # Stores total revenue
└── README.md # Documentation file


---

## 🧩 Classes Overview

| Class | Description |
|--------|-------------|
| `Vehicle` | Base class for all vehicle types (Bike, Car, Truck). |
| `Bike`, `Car`, `Truck` | Derived vehicle classes with specific hourly rates. |
| `ParkingSlot` | Represents individual parking slots and handles vehicle assignment. |
| `Ticket` | Manages ticket generation, storage, and display. |
| `Payment` | Handles billing and receipt printing. |
| `MonthlyPass` | Manages monthly passes and validity checking. |
| `ParkingFloor` | Represents each parking floor with multiple slots. |
| `SmartParkingSystem` | Core class that controls all features and file operations. |

---

## ⚙️ Hourly Rates

| Vehicle Type | Rate (₹/hour) |
|---------------|---------------|
| Bike | ₹10 |
| Car | ₹20 |
| Truck | ₹40 |

---

## 💰 Monthly Pass

| Pass Type | Duration | Cost |
|------------|-----------|------|
| All Vehicles | 30 days | ₹500 |

---

## 🧾 File Persistence

The system automatically **saves and loads data** between runs.

| File | Purpose |
|-------|----------|
| `parking_tickets.txt` | Stores active vehicle parking details |
| `monthly_passes.txt` | Stores active monthly passes |
| `revenue.txt` | Stores cumulative total revenue |

---

## 🖥️ How to Run

### 🔧 Using Terminal / Command Prompt

1. **Compile the code**
   ```bash
   g++ main.cpp -o parking_system
   ```

2. **Run the executable**
    ```bash
    ./parking_system
    ```
**🪟 On Windows (Code::Blocks / Dev C++ / Visual Studio)**

    Create a new C++ Console Project.
    Copy and paste the full main.cpp code into your project.
    Build and Run.

---

## 🧭 Menu Options ##

When you run the program, you’ll see:

          MAIN MENU 
1. View Parking Status
2. Park Vehicle (Entry)
3. Exit Vehicle (With Payment)
4. Purchase Monthly Pass
5. View Monthly Pass Details
6. View Revenue Statistics
0. Exit System
 

## 🧠 Example Workflow ##
➤ Park a Vehicle
Enter vehicle number: MH12AB1234
Enter vehicle type (Bike/Car/Truck): Car
✅ The system allocates a slot, generates a ticket, and displays entry details.

➤ Exit a Vehicle
Enter vehicle number: MH12AB1234
Payment method (Cash/Card/UPI): UPI
✅ The system calculates charges, prints a payment receipt, and frees the slot.

➤ Purchase Monthly Pass
Enter vehicle number: MH12XY7890
✅ Creates a new monthly pass valid for 30 days.

➤ View Revenue
Displays total revenue earned and system statistics.

## 📊 Example Output (Ticket & Receipt) ##
**🎫 Parking Ticket**

Ticket ID: TKT1730665123101
Vehicle: MH12AB1234
Slot: 101
Entry Time: Wed Nov  5 14:45:23 2025
Rate: ₹20/hour

---

**💳 Payment Receipt**

Vehicle: MH12AB1234
Duration: 1.00 hours
Rate: ₹20/hour
Amount: ₹20
Method: UPI
Time: Wed Nov  5 15:45:23 2025

    Thank you! Visit again!


🧹 Data Storage Notes
Files are automatically created in the same directory as the executable.
Do not delete text files if you want to keep historical data.
To reset the system:
Delete parking_tickets.txt, monthly_passes.txt, and revenue.txt.

## 🏁 Exit Message ##

**When exiting the system:**

         Thank you for using our system!   
             Data saved successfully      
