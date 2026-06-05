#include <iostream>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

static const int SIZE = 256;

class CircularBuffer
{
public:

    CircularBuffer():m_rdx(0), m_wdx(0)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_not_empty, NULL);
        pthread_cond_init(&m_not_full, NULL);
        
        std::cout << "Constructor\n";
    }

    ~CircularBuffer()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_not_full);
        pthread_cond_destroy(&m_not_empty);
        std::cout << "Destructor\n";
    }
    

    // Copy constructor
    CircularBuffer(const CircularBuffer& other)
        : m_rdx(other.m_rdx), m_wdx(other.m_wdx)
    {
        std::memcpy(m_buffer, other.m_buffer, SIZE);
        std::cout << "Copy constructor\n";
    }

    bool write(unsigned char byte)
    {
         pthread_mutex_lock(&m_mutex);
         std::cout << "writer got mutex\n";
         while ((m_wdx + 1) % SIZE == m_rdx) {
              std::cout << "Buffer full." << std::endl;
              pthread_cond_wait(&m_not_full, &m_mutex);
         }
         m_buffer[m_wdx] = byte;
         m_wdx = (m_wdx + 1) % SIZE;
         pthread_cond_signal(&m_not_empty);
         std::cout << "writer releaseing mutex\n";
         pthread_mutex_unlock(&m_mutex); 
         return true;
    }

    bool read(unsigned char *byte)
    {
         pthread_mutex_lock(&m_mutex);
         std::cout << "reader got mutex\n";
         while (m_rdx == m_wdx) {
              std::cout << "Buffer empty." << std::endl;
              pthread_cond_wait(&m_not_empty, &m_mutex);  //the condition that makes threads STOP waiting
         }
         *byte = m_buffer[m_rdx];
         m_rdx = (m_rdx + 1) % SIZE;
         pthread_cond_signal(&m_not_full);
         std::cout << "reader releaseing mutex\n";
         pthread_mutex_unlock(&m_mutex);
         return true;
    }

private:
     unsigned char m_buffer[SIZE];
     pthread_mutex_t m_mutex;
     pthread_cond_t m_not_empty;
     pthread_cond_t m_not_full;
     int m_rdx;
     int m_wdx;

};


void* reader_fn(void* arg) // thread
{
    CircularBuffer* buf = static_cast<CircularBuffer*>(arg);
    unsigned char byte;
    std::cout << "reader\n";
    while (1) {
        bool ok = buf->read(&byte);
        if (ok) {
            std::cout << "read byte = " << (int)byte << "\n";
        }
         
   }
    
}

void *writer_fn(void *arg)   // thread
{
     CircularBuffer* buf = static_cast<CircularBuffer*>(arg);
     std::cout << "writer\n";
     volatile int i = 0;
     while (1) {
         std::cout << "i = " << i << "\n";
         std::cout << "attempt write\n";
         bool ok = buf->write(i);
         if (ok) {
             i = (i + 1) % 256;
         }
         
     }
     return NULL;
}

int main()
{
    pthread_t t1, t2;

    CircularBuffer g_buffer;
    CircularBuffer b = g_buffer;

    std::vector<int> v1 = {1,2,3};
    std::vector<int> v2 = std::move(v1);

    //std::cout << "a.m_rdx = " << a.m_wdx << '\n';
    //std::cout << "b.m_wdx = " << b.m_wdx << '\n';
    pthread_create(&t1, NULL, writer_fn, &g_buffer);
    pthread_create(&t2, NULL, reader_fn, &g_buffer);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
