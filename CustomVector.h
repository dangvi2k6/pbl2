#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <cstddef>   // Để dùng size_t, ptrdiff_t
#include <stdexcept> // Để dùng std::out_of_range
#include <new>       // Để dùng bad_alloc
#include <initializer_list> // Để hỗ trợ initializer_list (nếu cần, nhưng không bắt buộc ở đây)

// Template class Vector<T> tùy chỉnh
template <typename T>
class Vector {
private:
    T* data_;         // Con trỏ đến mảng động
    size_t size_;     // Số lượng phần tử hiện tại
    size_t capacity_; // Dung lượng hiện tại của mảng

    // Hàm helper để resize mảng khi cần
    void resize(size_t new_capacity) {
        if (new_capacity < size_) {
            new_capacity = size_;
        }
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]); // Sử dụng move để tối ưu
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Iterator type (đơn giản là pointer để tương thích với algorithm như remove_if)
    typedef T* iterator;
    typedef const T* const_iterator;

    // Constructor mặc định: vector rỗng
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // Constructor với initializer_list (tùy chọn, nhưng hữu ích nếu cần)
    Vector(std::initializer_list<T> init) : Vector() {
        for (const auto& elem : init) {
            push_back(elem);
        }
    }

    // Destructor: giải phóng bộ nhớ
    ~Vector() {
        clear();
        delete[] data_;
    }

    // push_back: Thêm phần tử vào cuối (copy)
    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize(new_capacity);
        }
        data_[size_++] = value;
    }

    // emplace_back: Thêm phần tử trực tiếp (forward args)
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize(new_capacity);
        }
        new (&data_[size_++]) T(std::forward<Args>(args)...);
    }

    // erase: Xóa phần tử tại iterator, trả về iterator tiếp theo
    iterator erase(iterator pos) {
        if (pos < begin() || pos >= end()) {
            throw std::out_of_range("Iterator out of range");
        }
        size_t index = pos - begin();
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        data_[--size_].~T(); // Gọi destructor cho phần tử cuối
        return begin() + index;
    }

    // begin: Trả về iterator đầu
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }

    // end: Trả về iterator cuối (sau phần tử cuối cùng)
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    // size: Số lượng phần tử
    size_t size() const { return size_; }

    // empty: Kiểm tra rỗng
    bool empty() const { return size_ == 0; }

    // clear: Xóa tất cả phần tử
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T(); // Gọi destructor
        }
        size_ = 0;
    }

    // operator[]: Truy cập phần tử theo index (không kiểm tra bound để giống vector chuẩn)
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    // reserve: Dự trữ dung lượng (tùy chọn, nhưng hữu ích để tối ưu)
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            resize(new_capacity);
        }
    }

    // pop_back: Xóa phần tử cuối (nếu cần, dù không thấy dùng trực tiếp nhưng hữu ích)
    void pop_back() {
        if (!empty()) {
            data_[--size_].~T();
        }
    }
};

#endif // CUSTOM_VECTOR_H