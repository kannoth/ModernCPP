#include <iostream>
#include <memory>
#include <string>
#include <cassert>

// Smart pointers with inter dependency. The destructors
// will never be called unless we use a weak_ptr for the
// Child object.
namespace cpp_demo {

    // Declaration forward for compiler
    class Parent;

    class Child{
    public:
        std::shared_ptr<Parent> m_has_parent;

        ~Child(){
            std::cout << "Child destroyed" << std::endl;
        }
    };

    class Parent{
    public:
        //std::shared_ptr<Child> m_has_child;
        std::weak_ptr<Child> m_has_child;

        ~Parent(){
            std::cout << "Parent destroyed "<< std::endl;
        }
    };
}

int main()
{
    using namespace cpp_demo;
    
    auto child = std::make_shared<Child>();
    auto parent = std::make_shared<Parent>();

    child->m_has_parent = parent;
    parent->m_has_child = child;

    return EXIT_SUCCESS;
}
