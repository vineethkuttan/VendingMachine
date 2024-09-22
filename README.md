## Vending Machine
### Question
Architect and write skeleton code for a modular vending machine. Vending machines should have a base which handles taking money, credit card, etc... and accepts pluggable racks which contain spindles which hold/dispense product. This question would be more to see how Candidates design the software, if they use SOLID principles, Design Patterns, etc...
### High-Level Architecture
- *Vending Machine*: Handles payment processing (cash, credit card, etc.).
- *Pluggable Racks*: Each rack can be plugged into the base and contains spindles for dispensing products.
- *Spindles*: Hold and dispense products.

### Key Components
- Payment System: Interface for different payment methods.
- Vending Machine Base: Manages the overall operation and integrates with racks.
- Rack: Pluggable component that holds spindles.
- Spindle: Mechanism to hold and dispense products.

### Design Patterns Used
- **Strategy Pattern**: For different payment methods.
- **State Pattern**:For Managing different states of the Vending Machine
- **Singleton(Thread Safe)** : For maintaining Consistency and Integrity for Vending Machine

### Explanation
- **PaymentMethod**: An interface for different payment methods.
- **CashPayment** and **CardPayment**: Concrete implementations of the PaymentMethod.
- **Spindle**: Represents a spindle that can dispense products.
- **Rack**: Contains multiple spindles and can dispense products from a specific spindle.
- **VendingMachine** : Manages the payment system and racks, and coordinates the dispensing of products.

### Classes, Interfaces and Enumerations
- The Product class represents a product in the vending machine, with properties such as name and price.
- The Coin and Note enums represent the different denominations of coins and notes accepted for CashPayment.
- The Inventory class manages the available products and their quantities in the vending machine.
- The VendingMachineState interface defines the behavior of the vending machine in different states, such as idle, Select, and dispense.
- The IdleState,SelectState, and DispenseState classes implement the VendingMachineState interface and define the specific behaviors for each state.
- The VendingMachine class is the main class that represents the vending machine. It follows the Singleton pattern to ensure only one instance of the vending machine exists.
- The VendingMachine class maintains the current state, paymentMethod provides methods for state transitions and payment handling.