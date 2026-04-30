#include <iostream>

using namespace std;

class Foo {
    public:

    Foo(int x, int y) { m_z = x*y; m_p = new int[250];cout << "Foo initialized\n";}

    Foo(const Foo& other) {
        m_z = other.m_z;
        m_p = new int[250];
        copy(other.m_p, other.m_p + 250, m_p);
    }

    Foo& operator=(const Foo& other)
    {
    cout << "Assignment operator called\n";
    
    if (this == &other) return *this;  // self assignment guard
    
    delete[] m_p;                      // free existing memory
    m_z = other.m_z;                   // copy the int
    m_p = new int[250];                // fresh allocation
    copy(other.m_p, other.m_p + 250, m_p);  // copy the data
    
    return *this;
    }

    ~Foo() {delete[] m_p;cout << "Foo destroyed\n";}
    void print_object(const string& name);

   private:
          int m_z;
          int *m_p;
};

void Foo::print_object(const string& name) 
{
    cout << name << " -- m_z = " << m_z << "  m_p = " << m_p << endl;
}

int main() {
    Foo dumdum{2, 3};
    Foo dumdum3{1,1};
    Foo dumdum2 = dumdum;    // copy -- looks innocent
    cout << "copying dumdum2 from dumdum3\n";
    dumdum2 = dumdum3;
    dumdum.print_object("dumdum");
    dumdum2.print_object("dumdum2");
    dumdum3.print_object("dumdum3");
}
