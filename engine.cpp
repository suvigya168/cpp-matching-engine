#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Order {
private:
    int orderId;
    std::string ticker;
    bool isBuy;
    double price;
    int quantity;

public:
    // Constructor (Optimized with const reference for string)
    Order(int id, const std::string& t, bool buy, double p, int q) {
        orderId = id;
        ticker = t;
        isBuy = buy;
        price = p;
        quantity = q;
    }

    // Getters
    int getOrderId() const { return orderId; }
    std::string getTicker() const { return ticker; }
    bool getIsBuy() const { return isBuy; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setter
    void setQuantity(int q) { quantity = q; }
};

class OrderBook {
private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

public:
    // Add order
    void addOrder(const Order& newOrder) {
        if (newOrder.getIsBuy())
            buyOrders.push_back(newOrder);
        else
            sellOrders.push_back(newOrder);
    }

    // Matching engine
    void matchOrders() {
        // Sort buy orders (highest price first - Descending)
        std::sort(buyOrders.begin(), buyOrders.end(),
            [](const Order& a, const Order& b) {
                return a.getPrice() > b.getPrice();
            });

        // Sort sell orders (lowest price first - Ascending)
        std::sort(sellOrders.begin(), sellOrders.end(),
            [](const Order& a, const Order& b) {
                return a.getPrice() < b.getPrice();
            });

        int i = 0, j = 0;

        while (i < buyOrders.size() && j < sellOrders.size()) {
            Order &buy = buyOrders[i];
            Order &sell = sellOrders[j];

            // Check if match possible
            if (buy.getPrice() >= sell.getPrice()) {

                int matchedQty = std::min(buy.getQuantity(), sell.getQuantity());

                std::cout << "EXECUTION: "
                     << matchedQty << " shares of "
                     << buy.getTicker()
                     << " at $" << sell.getPrice()
                     << std::endl;

                // Update quantities
                buy.setQuantity(buy.getQuantity() - matchedQty);
                sell.setQuantity(sell.getQuantity() - matchedQty);

                // Move to next order if fulfilled
                if (buy.getQuantity() == 0) i++;
                if (sell.getQuantity() == 0) j++;
            }
            else {
                break; // No more matches possible at current spread
            }
        }
    }
};

int main() {
    OrderBook ob;

    // Sample Orders
    ob.addOrder(Order(1, "TATA", true, 150, 100));
    ob.addOrder(Order(2, "TATA", false, 149, 50));
    ob.addOrder(Order(3, "TATA", true, 148, 70));
    ob.addOrder(Order(4, "TATA", false, 147, 60));
    ob.addOrder(Order(5, "TATA", true, 151, 40));
    ob.addOrder(Order(6, "TATA", false, 150, 80));

    // Run matching engine
    ob.matchOrders();

    return 0;
}