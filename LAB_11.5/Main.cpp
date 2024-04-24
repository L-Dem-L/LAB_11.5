#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Drink {
    double strength;
};

struct ChocolateProduct {
    double weight;
    string filling;
};

struct Product {
    string type;
    double calorie;
    double price;
    Drink drink; // for drinks
    ChocolateProduct chocolate; // for chocolate products
};

// Function to write data to a file
void writeToFile(const string& filename, const vector<Product>& products) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file for writing.\n";
        return;
    }
    for (const auto& product : products) {
        file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    }
    file.close();
}

// Function to append a record to a file
void appendToFile(const string& filename, const Product& product) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) {
        cerr << "Failed to open file for appending.\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    file.close();
}

// Function to replace a record in a file
void replaceInFile(const string& filename, const Product& product, int index) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Failed to open file for replacing.\n";
        return;
    }
    file.seekp(index * sizeof(Product));
    file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
    file.close();
}

// Function to delete data from a file
void deleteFromFile(const string& filename, const string& type) {
    vector<Product> products;
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Failed to open file for reading.\n";
        return;
    }
    Product product;
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (product.type != type) {
            products.push_back(product);
        }
    }
    file.close();

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Failed to open file for writing.\n";
        return;
    }
    for (const auto& prod : products) {
        outFile.write(reinterpret_cast<const char*>(&prod), sizeof(Product));
    }
    outFile.close();
}

// Function to find chocolate products with maximum weight and specified filling
void findMaxWeightChocolate(const vector<Product>& products, const string& filling) {
    double maxWeight = 0;
    for (const auto& product : products) {
        if (product.type == "chocolate" && product.chocolate.weight > maxWeight && product.chocolate.filling == filling) {
            maxWeight = product.chocolate.weight;
        }
    }
    if (maxWeight > 0) {
        cout << "Chocolate products with maximum weight (" << maxWeight << " g) and filling '" << filling << "':" << endl;
        for (const auto& product : products) {
            if (product.type == "chocolate" && product.chocolate.weight == maxWeight && product.chocolate.filling == filling) {
                cout << "Type: " << product.type << ", Weight: " << product.chocolate.weight << " g, Price: " << product.price << " UAH, Calorie: " << product.calorie << " kcal" << endl;
            }
        }
    }
    else {
        cout << "No chocolate products with such filling were found." << endl;
    }
}

// Function to find products that match specified calorie and price criteria
void findProductsByCriteria(const vector<Product>& products, double maxCalorie, double maxPrice) {
    cout << "Products that match specified calorie and price criteria:" << endl;
    for (const auto& product : products) {
        if (product.calorie <= maxCalorie && product.price <= maxPrice) {
            cout << "Type: " << product.type << ", Weight: " << product.chocolate.weight << " g, Price: " << product.price << " UAH, Calorie: " << product.calorie << " kcal" << endl;
        }
    }
}

int main() {
    vector<Product> products;

    while (true) {
        cout << "1. Add product to file\n";
        cout << "2. Replace data in file\n";
        cout << "3. Delete alcoholic drinks from file\n";
        cout << "4. Find chocolate products with maximum weight and specified filling\n";
        cout << "5. Compile a menu of products based on calorie and price\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            Product newProduct;
            cout << "Enter data for the new product:" << endl;
            cout << "Type (drink/chocolate): ";
            cin >> newProduct.type;
            cout << "Calorie: ";
            cin >> newProduct.calorie;
            cout << "Price: ";
            cin >> newProduct.price;
            if (newProduct.type == "drink") {
                cout << "Strength: ";
                cin >> newProduct.drink.strength;
            }
            else if (newProduct.type == "chocolate") {
                cout << "Weight: ";
                cin >> newProduct.chocolate.weight;
                cout << "Filling: ";
                cin >> newProduct.chocolate.filling;
            }
            products.push_back(newProduct);
            appendToFile("products.bin", newProduct);
            break;
        }
        case 2: {
            int index;
            cout << "Enter the index of the product to replace: ";
            cin >> index;
            if (index >= 0 && index < products.size()) {
                Product newData;
                cout << "Enter new data for the product:" << endl;
                cout << "Type (drink/chocolate): ";
                cin >> newData.type;
                cout << "Calorie: ";
                cin >> newData.calorie;
                cout << "Price: ";
                cin >> newData.price;
                if (newData.type == "drink") {
                    cout << "Strength: ";
                    cin >> newData.drink.strength;
                }
                else if (newData.type == "chocolate") {
                    cout << "Weight: ";
                    cin >> newData.chocolate.weight;
                    cout << "Filling: ";
                    cin >> newData.chocolate.filling;
                }
                products[index] = newData;
                replaceInFile("products.bin", newData, index);
            }
            else {
                cout << "Invalid product index." << endl;
            }
            break;
        }
        case 3: {
            deleteFromFile("products.bin", "drink");
            cout << "Alcoholic drinks have been successfully deleted from the file." << endl;
            break;
        }
        case 4: {
            string filling;
            cout << "Enter the name of the filling to search for: ";
            cin >> filling;
            findMaxWeightChocolate(products, filling);
            break;
        }
        case 5: {
            double maxCalorie, maxPrice;
            cout << "Enter the maximum calorie: ";
            cin >> maxCalorie;
            cout << "Enter the maximum price: ";
            cin >> maxPrice;
            findProductsByCriteria(products, maxCalorie, maxPrice);
            break;
        }
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
