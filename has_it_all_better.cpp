#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

// Abstract Interface class
class ICar {
public:
    //ICar(const string& color) { } // Constructor to initialize color
    virtual void drive() = 0; // Pure virtual function (must be implemented)

    virtual void honk() = 0;
    virtual ~ICar() = default; // Virtual destructor for polymorphic cleanup
};

// Engine class; non abstract
class Engine {
    int hp; 
public:
    Engine(int horsepower) : hp(horsepower) { } // Constructor with initializer list

    void start() const {
        std::cout << "Engine starting with " << hp << " horsepower.\n";
    }

    int get_hp() const { return hp; } // Getter for horsepower
};

// Forward declaration for Foo
class Foo {
public:
    Foo() { std::cout << "Foo created.\n"; }
    ~Foo() { std::cout << "Foo destroyed.\n"; }
};

// Derived class: Sedan
class Sedan : public ICar {
public:
    // Constructor with initialization list
    Sedan(const vector<string>& list, string color, int year) // Pass Large Objects by const reference 
                                      // to avoid copying the vector unnecessarily. 
        : m_col(color), m_Engine(200), m_tires(list), m_y(year) {
        std::cout << "Sedan constructed with color: " << m_col << " and " 
                  << m_tires.size() << " tires.\n";
    }

    ~Sedan() override {
        std::cout << "Destructing Sedan\n";
    }

    void drive() override {
        std::cout << "Driving a " << m_y << " " << m_col << " sedan smoothly on the road.\n";
    }

    void publicHonk() { // Public method to invoke honk()
        honk();
    }
    
    void set_foo(const std::shared_ptr<Foo>& tmp) {
        m_pFoo = tmp;
    }

protected:
    void honk() override {
        std::cout << "Sedan with " << m_Engine.get_hp() 
                  << " horsepower, honking: Beep! Beep!\n";
    }

private:
    Engine m_Engine; // Composition: Sedan "has-a" Engine
    const int m_y; // Constant member variable
    string m_col;
    vector<string> m_tires; // List of tires
    std::shared_ptr<Foo> m_pFoo; // Shared pointer to Foo
};

// Main function
int main() {
    // Create a vector of tire names
    vector<string> tires = { "Front Left", "Front Right", "Rear Left", "Rear Right" };

    // Create a Sedan object
    Sedan mySedan(tires, "Silver", 2023);

    // Call the drive method
    mySedan.drive();
    mySedan.publicHonk();

    // Initialize Foo pointer using make_shared
    std::shared_ptr<Foo> pFoo = std::make_shared<Foo>();
    mySedan.set_foo(pFoo);

    // Create a Sedan object on the heap
    std::shared_ptr<Sedan> mySedan1 = std::make_shared<Sedan>(tires, "Blue", 2024);
    mySedan1->drive();
    mySedan1->set_foo(pFoo);

    return 0;
}
