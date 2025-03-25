#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h> // for sleep()

using namespace std;

// Product class
class Product {
public:
    int id;
    string name;
    double price;

    Product(int pid = 0, string pname = "", double pprice = 0.0) {
        id = pid;
        name = pname;
        price = pprice;
    }
};

// ShoppingCart class
class ShoppingCart {
private:
    Product cart[50]; // Array to hold products
    int cartSize;

public:
    ShoppingCart() {
        cartSize = 0;
    }

    // Function to add a product to the cart
    void addToCart(Product product) {
        if (cartSize < 50) {
            cart[cartSize] = product;
            cartSize++;
            cout << "Product added to cart: " << product.name << endl;
        } else {
            cout << "Cart is full! Cannot add more items.\n";
        }
        sleep(1);
    }

    // Function to remove a product from the cart by ID
    void removeFromCart(int productId) {
        bool found = false;
        for (int i = 0; i < cartSize; i++) {
            if (cart[i].id == productId) {
                found = true;
                for (int j = i; j < cartSize - 1; j++) {
                    cart[j] = cart[j + 1];
                }
                cartSize--;
                cout << "Product removed from cart.\n";
                break;
            }
        }
        if (!found) {
            cout << "Product not found in the cart.\n";
        }
        sleep(1);
    }

    // Function to view the cart
    void viewCart() {
        system("CLS");
        if (cartSize == 0) {
            cout << "Your cart is empty.\n";
        } else {
            cout << "Your Shopping Cart:\n";
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price\n";
            cout << "------------------------------------------\n";
            for (int i = 0; i < cartSize; i++) {
                cout << setw(10) << cart[i].id << setw(20) << cart[i].name << setw(10) << cart[i].price << endl;
            }
        }
        sleep(2);
    }

    // Function to place an order with delivery details
    void placeOrder() {
        system("CLS");
        if (cartSize == 0) {
            cout << "Your cart is empty. Add items before placing an order.\n";
            sleep(2);
            return;
        }

        string province, city, street, houseNo, phoneNumber;

        cout << "Enter Delivery Details:\n";
        cout << "Province: ";
        cin.ignore(); // Clear input buffer
        getline(cin, province);
        cout << "City: ";
        getline(cin, city);
        cout << "Street: ";
        getline(cin, street);
        cout << "House No: ";
        getline(cin, houseNo);
        cout << "Phone Number: ";
        getline(cin, phoneNumber);

        system("CLS");
        cout << "Order Summary:\n";
        double total = 0.0;
        for (int i = 0; i < cartSize; i++) {
            total += cart[i].price;
        }
        cout << "Total Amount: $" << total << endl;
        cout << "Delivery Details:\n";
        cout << "Province: " << province << "\nCity: " << city << "\nStreet: " << street 
             << "\nHouse No: " << houseNo << "\nPhone: " << phoneNumber << endl;
        cout << "Order placed successfully!\n";
        sleep(3);
    }

    // Function to make payment
    void makePayment() {
        system("CLS");
        if (cartSize == 0) {
            cout << "Nothing to pay. Add items to the cart first.\n";
            sleep(2);
            return;
        }

        int paymentMethod;
        string paymentNumber;

        cout << "Choose Payment Method:\n";
        cout << "1. JazzCash\n";
        cout << "2. EasyPaisa\n";
        cout << "3. Bank Account\n";
        cout << "Enter your choice: ";
        cin >> paymentMethod;

        switch (paymentMethod) {
        case 1:
            cout << "Enter JazzCash account number: ";
            cin >> paymentNumber;
            cout << "Processing payment through JazzCash...\n";
            break;

        case 2:
            cout << "Enter EasyPaisa account number: ";
            cin >> paymentNumber;
            cout << "Processing payment through EasyPaisa...\n";
            break;

        case 3:
            cout << "Enter Bank account number: ";
            cin >> paymentNumber;
            cout << "Processing payment through Bank Account...\n";
            break;

        default:
            cout << "Invalid payment method. Payment cancelled.\n";
            sleep(2);
            return;
        }

        sleep(2);
        cout << "Payment successful! Thank you for shopping.\n";
        cartSize = 0; // Clear the cart after payment
        sleep(2);
    }
};

// Main function
int main() {
    ShoppingCart cart;
    Product products[] = {
        Product(1, "Laptop", 1000.00),
        Product(2, "Smartphone", 700.00),
        Product(3, "Headphones", 100.00),
        Product(4, "Keyboard", 50.00),
        Product(5, "Mouse", 30.00),
    };

    int choice, productId;
    while (true) {
        system("CLS");
        cout << "Welcome to the Ecommerce Cart System\n";
        cout << "1. Add to Cart\n";
        cout << "2. Remove from Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Place Order\n";
        cout << "5. Make Payment\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("CLS");
            cout << "Available Products:\n";
            for (auto& product : products) {
                cout << "ID: " << product.id << ", Name: " << product.name << ", Price: $" << product.price << endl;
            }
            cout << "Enter Product ID to add to cart: ";
            cin >> productId;
            for (auto& product : products) {
                if (product.id == productId) {
                    cart.addToCart(product);
                    break;
                }
            }
            break;

        case 2:
            cout << "Enter Product ID to remove from cart: ";
            cin >> productId;
            cart.removeFromCart(productId);
            break;

        case 3:
            cart.viewCart();
            break;

        case 4:
            cart.placeOrder();
            break;

        case 5:
            cart.makePayment();
            break;

        case 6:
            cout << "Exiting the system. Thank you for visiting!\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
            sleep(1);
        }
    }

    return 0;
}
