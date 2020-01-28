#ifndef _POINT_
#define _POINT_

#include <cstring>

template <typename T>
class PointND
{
    private:
        T* coords;
        int dim;
        void init();
    public:
        PointND(T* coords, int dim);
        PointND(const PointND & pts);
        ~PointND();
        bool operator == (const PointND & pts);
        PointND operator = (const PointND & pts);
        T getAtAxis(int axis) const;
        void print();
};

template <typename T>
void PointND<T>::init()
{
    coords = nullptr;
    dim = 0;
}

template <typename T>
PointND<T>::PointND(T* coords, int dim)
{
    init();
    this->dim = dim;
    this->coords = new T[this->dim];
    if (!this->coords)
    {
        throw "out of memory";
    }
    memcpy(this->coords, coords, sizeof(T) * this->dim);
}


template <typename T>
PointND<T>::PointND(const PointND<T> & pts)
{
    init();
    this->dim = pts.dim;
    this->coords = new T[dim];
    if (!this->coords)
    {
        throw "out of memory";
    }
    memcpy(this->coords, pts.coords, sizeof(T) * dim);
}


template <typename T>
PointND<T>::~PointND()
{
    if (coords)
    {
        delete[] coords;
        coords = nullptr;
        dim = 0;
    }
}

template <typename T>
bool PointND<T>::operator == (const PointND & pts)
{
    if (dim != pts.dim)
        return false;
    for (int i = 0; i < dim; i++)
        if (coords[i] != pts.coords[i])
            return false;
    return true;
}

template <typename T>
PointND<T> PointND<T>::operator = (const PointND<T> & pts)
{
    if (coords)
    {
        delete[] coords;
        coords = nullptr;
    }
    dim = pts.dim;
    coords = new T[dim];
    memcpy(coords, pts.coords, sizeof(T) * dim);
    return *this;
}


template <typename T>
T PointND<T>::getAtAxis(int axis) const
{
    return coords[axis];
}

template <typename T>
void PointND<T>::print()
{
  for (int i = 0; i < dim; i++)
  {
    std::cout << coords[i] << '\t';
  }
  std::cout << std::endl;
}

#endif
