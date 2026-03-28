#ifndef MGENGINE_FRLIST_H
#define MGENGINE_FRLIST_H

#include <vector>
#include <shared_mutex>

class FastRefHandle {
public:
    int Id;
    int Generation;
    
public:
    explicit FastRefHandle() {
        this->Id = -1;
        this->Generation = -1;
    }
    
    explicit FastRefHandle(const int id, const int generation) {
        this->Id = id;
        this->Generation = generation;
    }
};

// FastRefList is a fast reference data structure.
// It tries to strike a balance between the speed of adding, removing, iterating and accessing data, 
// with the following priority: access, iration, adding, removing
// Thread safe by design.
template<class T>
class FastRefList {
    class FastRefContainer {
    public:
        T data;
        int generation;
        bool isFreed;
        
    public:
        FastRefContainer(T&& newData, const int generation) : data(newData), generation(generation), isFreed(false) {}
    };
    
    std::shared_mutex mutex;
    
    std::vector<FastRefContainer> refs;
    std::vector<int> freeList;
    
public:
    size_t capacity() {
        std::unique_lock lock(this->mutex);
        
        return refs.size();
    }
    
    size_t size() {
        std::unique_lock lock(this->mutex);
        
        return refs.size() - freeList.size();
    }
    
    // This method adds the provided data and returns a handle which can be used to access this data later using the get() method.
    FastRefHandle add(T&& data) {
        std::unique_lock lock(this->mutex);
        
        if (freeList.empty()) {
            refs.push_back(FastRefContainer(std::move(data), 0));
            auto index = refs.size() - 1;
            return FastRefHandle(index, 0);
        }

        auto index = freeList.back();
        freeList.pop_back();

        auto& existingEntry = refs[index];
        if (!existingEntry.isFreed) {
            throw std::runtime_error("FastRefList synchronization error! freeList item pointed to a freed entry.");
        }
        existingEntry.data = std::move(data);
        existingEntry.generation++;
        existingEntry.isFreed = false;
        
        return FastRefHandle(index, existingEntry.generation);
    }
    
    // Method used for getting a reference to the data associated with the provided handle. 
    // Returns nullptr if the handle is invalid (data was removed, or handle was never valid).
    T* get(const FastRefHandle& handle) {
        if (handle.Id < 0 || handle.Id > refs.size()) {
            return nullptr;
        }

        std::shared_lock lock(this->mutex);
        auto& existingEntry = refs[handle.Id];
        if (existingEntry.generation != handle.Generation || existingEntry.isFreed) {
            return nullptr;
        }
        
        return &existingEntry.data;
    }
    
    // Removes the item referenced by the handle from the list.
    bool remove(const FastRefHandle& handle) {
        if (handle.Id < 0 || handle.Id > refs.size()) {
            return false;
        }

        std::unique_lock lock(this->mutex);
        auto& existingEntry = refs[handle.Id];
        if(existingEntry.generation != handle.Generation || existingEntry.isFreed) {
            return false;
        }
        
        existingEntry.isFreed = true;
        freeList.push_back(handle.Id);
        
        return true;
    }
};


#endif //MGENGINE_FRLIST_H