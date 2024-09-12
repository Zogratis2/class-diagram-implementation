#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Function to convert a string to uppercase
string to_upper(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Function to convert a string to lowercase
string to_lower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class Product {
private: 
    string product_Id; 
    string name;
    double price;

public:
    string get_product_Id() const { return product_Id; }
    string get_name() const { return name; }
    double get_price() const { return price; }

    Product(const string& product_Id, const string& name, double price) 
        : product_Id(product_Id), name(name), price(price) {}
};

class ShoppingCart {
private:
    int cart_Id;
    int customer_Id;
    vector<Product> products; // To store products in the cart

public:
    void add_product(const Product& product) {
        products.push_back(product);
    }

    void remove_product(const string& product_Id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (to_upper(it->get_product_Id()) == to_upper(product_Id)) {
                products.erase(it);
                cout << "Product removed from cart.\n";
                return;
            }
        }
        cout << "Product not found in cart.\n";
    }

    double calculate_total() const {
        double total = 0.0;
        for (const Product& product : products) {
            total += product.get_price();
        }
        return total;
    }

    void view_cart() const {
        if (products.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }
        
        cout << setw(20) << "Product ID" << setw(25) << "Name" << setw(15) << "Price" << endl;
        cout << "---------------------------------------------------------------" << endl;
        for (const Product& product : products) {
            cout << setw(20) << product.get_product_Id() << setw(25) << product.get_name() << setw(15) << product.get_price() << endl;
        }
        cout << "---------------------------------------------------------------" << endl;
        cout << "Total Price: $" << calculate_total() << endl;
    }

    void checkout() {
        if (products.empty()) {
            cout << "Your cart is empty. Add products before checking out.\n";
            return;
        }

        view_cart();
        cout << "Checkout successful!\n";
        products.clear(); // Empty the cart after checkout
    }
};

int main() {
    // Sample products
    vector<Product> products = {
        Product("SKYFLAKES", "Product A", 10.99),
        Product("MILO", "Product B", 15.99),
        Product("PORK", "Product C", 20.99),
        Product("FILLET", "Product D", 25.99),
        Product("BOOK ISANG KAIBIGAN", "Product E", 30.99)
    };

    ShoppingCart shoppingCart;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. View Products" << endl;
        cout << "2. View Shopping Cart" << endl;
        cout << "3. Add Product to Cart" << endl;
        cout << "4. Remove Product from Cart" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << setw(15) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
                cout << "---------------------------------------------------------------" << endl;
                for (const Product& product : products) {
                    cout << setw(15) << product.get_product_Id() << setw(20) << product.get_name() << setw(10) << product.get_price() << endl;
                }
                cout << "---------------------------------------------------------------" << endl;
                break;
            case 2:
                shoppingCart.view_cart();
                break;
            case 3: {
                string product_Id;
                cout << "Enter Product ID to add to cart: ";
                cin >> product_Id;
                product_Id = to_upper(product_Id); // Convert to uppercase for uniformity
                bool found = false;
                for (const Product& product : products) {
                    if (to_upper(product.get_product_Id()) == product_Id) {
                        shoppingCart.add_product(product);
                        cout << "Product added to cart.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Product not found.\n";
                }
                break;
            }
            case 4: {
                string product_Id;
                cout << "Enter Product ID to remove from cart: ";
                cin >> product_Id;
                shoppingCart.remove_product(product_Id);
                break;
            }
            case 5:
                shoppingCart.checkout();
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
