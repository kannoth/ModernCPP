#include <iostream>
#include <cassert>
#include <vector>
#include <memory>

namespace cpp_demo {

    class Buffer {
    public:
        // Constructor
        Buffer(size_t t_size) : m_data(new char[t_size]), m_size(t_size){}

        // Destructor
        ~Buffer() {
            delete[] m_data; 
         }
    
        char* m_data;
        size_t m_size;
    };

    class BufferV2 {
    public:
        // Constructor
        BufferV2(size_t t_size) { 
            m_data = new char[t_size];
            m_size = t_size;
        }

        // Destructor
        ~BufferV2() {
            delete[] this->m_data;
        }

        // Copy constructor
        BufferV2(const BufferV2& t_other) {
            this->m_data = new char[t_other.m_size];
            std::copy(t_other.m_data, t_other.m_data + t_other.m_size, this->m_data);
            this->m_size = t_other.m_size;
        }

        // Copy Assignment operator
        BufferV2& operator=(const BufferV2& t_other) {

            if (&t_other == this)
                return *this;

            delete[] this->m_data;
            std::copy(t_other.m_data, t_other.m_data + t_other.m_size, this->m_data);
            this->m_size = t_other.m_size;

            return *this;
        }

        // Move constuctor
        BufferV2(BufferV2&& t_other) {
            this->m_data = t_other.m_data;
            this->m_size = t_other.m_size;
            // Consumed the other resource
            t_other.m_data = nullptr;
            t_other.m_size = 0;
        }

        // Move assignment operator
        BufferV2& operator=(BufferV2&& t_other) {
            if (&t_other == this)
                return *this;

            delete[] this->m_data;

            this->m_data = t_other.m_data;
            this->m_size = t_other.m_size;
            // Consumed the other resource
            t_other.m_data = nullptr;
            t_other.m_size = 0;

            return *this;
        }


        char* m_data;
        size_t m_size;
    };
}

void BufferDemo() {
    using namespace cpp_demo;

    auto buffer = new Buffer(10);

    std::cout << "Buffer size :" << buffer->m_size << std::endl;


    //Buffer b2 = buffer; //Copy constructor
}

void BufferV2Demo_Copy() {

    using namespace cpp_demo;

    BufferV2 buff(300);
    // Copy constructors
    BufferV2 other_buff = buff;  // Invokes copy constructor
    BufferV2 other_buff2(buff);  // Invokes copy constructor

    BufferV2 buff_1(300);
    BufferV2 buff_2(400);
    // Copy assignment
    // buff_1 = buff_2; // Inovkes buffer assignment constructor

}

void BufferV2Demo_Move() {

    using namespace cpp_demo;

    BufferV2 buff(300);

    BufferV2 buff_2(std::move(buff)); // Move construtor invoked

    buff = std::move(buff_2);

    int a = 4;
}

// Unique pointer ownership exchange
void ownershipChange() {

    std::unique_ptr<std::vector<int>> int_res_0;
    {
        std::unique_ptr<std::vector<int>> int_res_1;
        {
            // Created resource
            auto int_res_2 = std::make_unique<std::vector<int>>();
            int_res_2->resize(3);
            int_res_2->at(0) = 3;
            int_res_2->at(1) = 1;
            int_res_2->at(2) = 4;

            // Transferring ownership
            int_res_1 = std::move(int_res_2); // no copies
        }
        // Transferring ownership
        int_res_0 = std::move(int_res_1); // no copies
    }

    std::vector<int> v{ 3, 1, 4 };
    assert(*int_res_0.get() == v);
}

int main()
{
    BufferV2Demo_Copy();
    BufferV2Demo_Move();

    ownershipChange();

    return EXIT_SUCCESS;
}
