#include <iostream>
#include <memory>
#include <string>
#include <cassert>

namespace cpp_demo {

    class Employee {
    public:
        Employee(const std::string& t_name) : m_name(t_name){
            std::cout << "'" << m_name << "'" << " constructed !!!\n";
        }
        ~Employee(){
            std::cout <<"'"<< m_name <<"'"<< " destroyed !!!\n";
        }
    public:
        std::string m_name;
    };
}

int main()
{
    using namespace cpp_demo;

    // Allocate unique resource which is not copyable
    {
        std::unique_ptr<Employee> bob = std::make_unique<Employee>("Bob");

        // Alternative
        auto bob = std::make_unique<Employee>("Bob");

        std::cout << "Name = "<< bob->m_name << std::endl;

    }// Employee will be deleted here

    // Allocate a shared resource which is copyable
    {
        auto alice = std::make_shared<Employee>("Alice");

        auto trudy = alice; // Copied reference

        // HR obeserves alice, but does not increments reference count
        std::weak_ptr<Employee> hr = alice;
       
        // Does Alice exists ?
        if (auto alice_ref = hr.lock())
            assert("Alice" == alice_ref->m_name);

        // Alice has two references
        assert(alice.use_count() == 2);

        // Remove a reference
        trudy.reset();
        // Reference count is decremented
        assert(alice.use_count() == 1);        
    }

    return EXIT_SUCCESS;
}
