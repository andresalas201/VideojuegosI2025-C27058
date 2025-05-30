/**
 * @file Pool.hpp
 * @brief Generic pool container implementation with polymorphic interface
 */

#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @brief Abstract base interface for pool containers
 * 
 * This interface provides a common base for all pool implementations,
 * enabling polymorphic usage of different pool types.
 */
class IPool {
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~IPool() = default;
};

/**
 * @brief Template-based generic pool container
 * @tparam TComponent The type of objects stored in the pool
 * 
 * A pool is a container that manages a collection of objects of type TComponent.
 * It provides efficient storage and access to elements through vector-based
 * implementation with dynamic resizing capabilities.
 */
template <class TComponent>
class Pool : public IPool {
private:
    std::vector<TComponent> data; ///< Internal storage for pool elements

public:
    /**
     * @brief Constructs a pool with specified initial size
     * @param size Initial capacity of the pool (default: 1000)
     * 
     * Creates a pool container with the specified initial size.
     * The pool will be pre-allocated to hold 'size' elements.
     */
    Pool(int size = 1000) { data.resize(size); }

    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~Pool() = default;

    /**
     * @brief Checks if the pool is empty
     * @return true if the pool contains no elements, false otherwise
     */
    bool IsEmpty() { return data.empty(); }

    /**
     * @brief Gets the current size of the pool
     * @return The number of elements currently in the pool
     */
    int GetSize() const { return static_cast<int>(data.size()); }

    /**
     * @brief Resizes the pool to accommodate n elements
     * @param n New size for the pool
     * 
     * Changes the pool capacity to hold exactly n elements.
     * If n is smaller than current size, elements may be lost.
     * If n is larger, new default-constructed elements are added.
     */
    void Resize(int n) { data.resize(n); }

    /**
     * @brief Removes all elements from the pool
     * 
     * Clears the pool content, making it empty.
     * The capacity may remain unchanged for performance reasons.
     */
    void Clear() { data.clear(); }

    /**
     * @brief Adds an element to the end of the pool
     * @param object The element to add to the pool
     * 
     * Appends the given object to the end of the pool,
     * increasing the pool size by one.
     */
    void Add(TComponent object) { data.push_back(object); }

    /**
     * @brief Sets the element at the specified index
     * @param index The position where to set the element
     * @param object The element to place at the given index
     * 
     * @warning No bounds checking is performed. Accessing invalid
     * indices results in undefined behavior.
     */
    void Set(int index, TComponent object) { data[index] = object; }

    /**
     * @brief Gets a reference to the element at the specified index
     * @param index The position of the element to retrieve
     * @return Reference to the element at the given index
     * 
     * @warning No bounds checking is performed. Accessing invalid
     * indices results in undefined behavior.
     */
    TComponent& Get(unsigned int index) { return static_cast<TComponent&>(data[index]); }

    /**
     * @brief Array subscript operator for element access
     * @param index The position of the element to retrieve
     * @return Reference to the element at the given index
     * 
     * Provides array-like access to pool elements.
     * 
     * @warning No bounds checking is performed. Accessing invalid
     * indices results in undefined behavior.
     */
    TComponent& operator[](unsigned int index) { return static_cast<TComponent&>(data[index]); }
};

#endif // POOL_HPP