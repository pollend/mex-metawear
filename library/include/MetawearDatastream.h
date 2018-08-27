//
// Created by Michael on 8/20/2018.
//

#ifndef MEX_METAWEAR_METAWEARDATASTREAM_H
#define MEX_METAWEAR_METAWEARDATASTREAM_H

#include <mutex>
#include <vector>

template <class T>
class MetawearDataStream {
friend class MetawearWrapperBase;
private:
    std::mutex m_data_lock;
    T* m_payload;
    bool m_looped;
    unsigned int m_head;
    unsigned int m_bottom;
    unsigned int m_size;
public:
    bool push(const T entry) {
        m_data_lock.lock();
        m_payload[m_head] = entry;
        m_head = (m_head + 1) % m_size;
        if(m_head == m_bottom ){
            m_bottom = (m_head+1) % m_size;
            m_looped = true;
        }
        m_data_lock.unlock();
        return true;
    }


    MetawearDataStream(unsigned int maxEntries):
            m_head(0),
            m_bottom(0),
            m_looped(false),
            m_size(maxEntries),
            m_payload(new T[maxEntries]),
            m_data_lock() {
    }

    ~MetawearDataStream(){
        delete[] m_payload;
    };


    int size() {
        return m_size;
    }

    std::vector<T> dump() {
        m_data_lock.lock();
        std::vector<T> result;
        if(m_looped)
            result.push_back(m_payload[m_head]);
        while (m_bottom != m_head) {
            result.push_back(m_payload[m_bottom]);
            m_bottom = (m_bottom + 1) % m_size;
        }

        m_looped = false;
        m_bottom = 0;
        m_head = 0;

        m_data_lock.unlock();
        return result;
    }
};


#endif //MEX_METAWEAR_METAWEARDATASTREAM_H
