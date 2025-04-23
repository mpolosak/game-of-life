#include <memory>
#include <iostream>

class Matrix
{
public:
    Matrix() = default;
    Matrix(Matrix &&other) = default;
    Matrix(int width, int height)
        : height(height)
    {
        array = std::make_unique<bool[]>(width * height);
    };
    void swap(Matrix &other)
    {
        array.swap(other.array);
        int tmp = this->height;
        this->height = other.height;
        other.height = tmp;
    }
    bool *operator[](int x)
    {
        return &(this->array[x * height]);
    }
    bool *operator[](int x) const
    {
        return &(this->array[x * height]);
    }
    Matrix &operator=(Matrix &&other) = default;

private:
    std::unique_ptr<bool[]> array;
    int height;
};