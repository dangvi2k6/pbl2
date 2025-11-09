#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <new>  // Thêm để dùng placement new

template <typename T>
class MyVector {
private:
    T* data;           
    size_t capacity;   
    size_t count;      

    void resizeCapacity() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        
        // Cấp phát bộ nhớ thô (không gọi constructor)
        T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));
        
        // Copy từng phần tử sang vùng nhớ mới
        for (size_t i = 0; i < count; i++) {
            new (&newData[i]) T(data[i]);  // Placement new - copy constructor
        }
        
        // Hủy các object cũ
        for (size_t i = 0; i < count; i++) {
            data[i].~T();
        }
        
        // Giải phóng bộ nhớ cũ
        ::operator delete(data);
        
        data = newData;
        capacity = newCapacity;
    }

public:
    typedef T* iterator;
    typedef const T* const_iterator;

    // Constructor mặc định
    MyVector() : data(nullptr), capacity(0), count(0) {}

    // Constructor từ initializer_list
    MyVector(std::initializer_list<T> init) : data(nullptr), capacity(0), count(0) {
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
    }

    // Destructor
    ~MyVector() {
        // Hủy tất cả object
        for (size_t i = 0; i < count; i++) {
            data[i].~T();
        }
        // Giải phóng bộ nhớ
        ::operator delete(data);
    }

    // Copy constructor
    MyVector(const MyVector& other) : data(nullptr), capacity(0), count(0) {
        if (other.count > 0) {
            reserve(other.count);
            for (size_t i = 0; i < other.count; i++) {
                new (&data[i]) T(other.data[i]);
            }
            count = other.count;
        }
    }

    // Copy assignment operator
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            // Hủy các object hiện tại
            for (size_t i = 0; i < count; i++) {
                data[i].~T();
            }
            ::operator delete(data);
            
            data = nullptr;
            capacity = 0;
            count = 0;
            
            if (other.count > 0) {
                reserve(other.count);
                for (size_t i = 0; i < other.count; i++) {
                    new (&data[i]) T(other.data[i]);
                }
                count = other.count;
            }
        }
        return *this;
    }

    // Assignment từ initializer_list
    MyVector& operator=(std::initializer_list<T> init) {
        clear();
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
        return *this;
    }

    // push_back
    void push_back(const T& value) {
        if (count >= capacity) {
            resizeCapacity();
        }
        new (&data[count]) T(value);  // Placement new - copy constructor
        count++;
    }

    // emplace_back
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (count >= capacity) {
            resizeCapacity();
        }
        new (&data[count]) T(args...);  // Placement new - construct in-place
        count++;
    }

    // pop_back
    void pop_back() {
        if (count > 0) {
            count--;
            data[count].~T();  // Hủy object
        }
    }

    // operator[]
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // back
    T& back() {
        return data[count - 1];
    }

    const T& back() const {
        return data[count - 1];
    }

    // size
    size_t size() const {
        return count;
    }

    // empty
    bool empty() const {
        return count == 0;
    }

    // clear
    void clear() {
        for (size_t i = 0; i < count; i++) {
            data[i].~T();
        }
        count = 0;
    }

    // begin
    iterator begin() {
        return data;
    }

    const_iterator begin() const {
        return data;
    }

    // end
    iterator end() {
        return data + count;
    }

    const_iterator end() const {
        return data + count;
    }

    // erase (single element)
    iterator erase(iterator pos) {
        if (pos < begin() || pos >= end()) {
            return end();
        }
        
        // Hủy phần tử tại pos
        pos->~T();
        
        // Dịch chuyển các phần tử sau về phía trước
        for (iterator it = pos; it != end() - 1; ++it) {
            new (it) T(*(it + 1));  // Copy construct
            (it + 1)->~T();         // Hủy bản cũ
        }
        
        count--;
        return pos;
    }

    // erase (range)
    iterator erase(iterator first, iterator last) {
        if (first >= last || first >= end()) {
            return end();
        }
        
        size_t numToErase = last - first;
        
        // Hủy các phần tử trong range
        for (iterator it = first; it != last; ++it) {
            it->~T();
        }
        
        // Dịch chuyển các phần tử sau last về vị trí first
        iterator dest = first;
        for (iterator src = last; src != end(); ++src, ++dest) {
            new (dest) T(*src);  // Copy construct
            src->~T();            // Hủy bản cũ
        }
        
        count -= numToErase;
        return first;
    }

    // insert
    iterator insert(iterator pos, const T& value) {
        size_t index = pos - begin();
        
        if (count >= capacity) {
            resizeCapacity();
            pos = begin() + index;
        }
        
        // Dịch chuyển các phần tử sau pos về phía sau
        if (count > index) {
            new (&data[count]) T(data[count - 1]);  // Construct phần tử cuối
            for (size_t i = count - 1; i > index; i--) {
                data[i] = data[i - 1];
            }
        }
        
        // Insert phần tử mới
        if (index < count) {
            data[index] = value;
        } else {
            new (&data[index]) T(value);
        }
        
        count++;
        return begin() + index;
    }

    // resize
    void resize(size_t newSize, const T& value = T()) {
        if (newSize > capacity) {
            reserve(newSize);
        }
        
        // Hủy các phần tử thừa nếu giảm size
        for (size_t i = newSize; i < count; i++) {
            data[i].~T();
        }
        
        // Khởi tạo các phần tử mới nếu tăng size
        for (size_t i = count; i < newSize; i++) {
            new (&data[i]) T(value);
        }
        
        count = newSize;
    }

    // reserve
    void reserve(size_t newCapacity) {
        if (newCapacity <= capacity) return;
        
        // Cấp phát bộ nhớ mới
        T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));
        
        // Copy các phần tử sang vùng nhớ mới
        for (size_t i = 0; i < count; i++) {
            new (&newData[i]) T(data[i]);
        }
        
        // Hủy các object cũ
        for (size_t i = 0; i < count; i++) {
            data[i].~T();
        }
        
        // Giải phóng bộ nhớ cũ
        ::operator delete(data);
        
        data = newData;
        capacity = newCapacity;
    }

    // at
    T& at(size_t index) {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // front
    T& front() {
        return data[0];
    }

    const T& front() const {
        return data[0];
    }

    // capacity getter
    size_t get_capacity() const {
        return capacity;
    }
};

#endif // MY_VECTOR_H