#include <gtest/gtest.h>

#include "Utils/FastRefList.h"

TEST(FastRefList, Add) {
    FastRefList<int> list;
    
    int data = 5;
    const auto handle = list.add(std::move(data));
    ASSERT_EQ(list.size(), 1);
    ASSERT_GE(list.size(), list.capacity());
    
    const auto ret = list.get(handle);
    ASSERT_NE(ret, nullptr);
    ASSERT_EQ(*ret, 5);
}

TEST(FastRefList, Remove) {
    FastRefList<int> list;

    int data = 5;
    const auto handle = list.add(std::move(data));
    const auto ret = list.get(handle);

    ASSERT_NE(ret, nullptr);
    ASSERT_EQ(*ret, 5);
    ASSERT_EQ(list.size(), 1);
    
    const auto removeResult = list.remove(handle);
    ASSERT_TRUE(removeResult);
    ASSERT_EQ(list.size(), 0);
    
    const auto retAfterRemove = list.get(handle);
    ASSERT_EQ(retAfterRemove, nullptr);
}

TEST(FastRefList, CantRemoveTwice) {
    FastRefList<int> list;
    
    const auto handle = list.add(5);
    ASSERT_TRUE(list.remove(handle));
    ASSERT_FALSE(list.remove(handle));
}

TEST(FastRefList, CantGetAfterRemove) {
    FastRefList<int> list;
    
    const auto handle = list.add(5);
    auto ptr = list.get(handle);
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(*ptr, 5);

    ASSERT_TRUE(list.remove(handle));
    
    ptr = list.get(handle);
    ASSERT_EQ(ptr, nullptr);
}

TEST(FastRefList, CantGetAfterRemoveAndReinsert_GenerationsTest) {
    FastRefList<int> list;

    const auto oldHandle = list.add(5);
    auto ptr = list.get(oldHandle);
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(*ptr, 5);

    ASSERT_TRUE(list.remove(oldHandle));

    const auto newHandle = list.add(6);
    ASSERT_EQ(oldHandle.Id, newHandle.Id);
    ASSERT_NE(oldHandle.Generation, newHandle.Generation);
    
    ptr = list.get(newHandle);
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(*ptr, 6);

    ASSERT_EQ(list.get(oldHandle), nullptr);
}

TEST(FastRefList, AddAndRemoveMixed) {
    FastRefList<int> list;
    
    const int N = 1000;
    std::vector<FastRefHandle> handles;
    handles.reserve(N);
    for (int i = 0; i < N; ++i) {
        handles.push_back(list.add(std::move(i))); // NOLINT(*-move-const-arg)
    }

    ASSERT_EQ(list.size(), N);
    auto capacityAfterAdding = list.capacity();
    
    for (int i = 0; i < N; i += 2) {
        list.remove(handles[i]);
    }

    ASSERT_EQ(list.size(), N - (N / 2));
    
    for (int i = 0; i < N; i += 2) {
        handles[i] = list.add(N + i);
    }

    ASSERT_EQ(list.size(), N);
    ASSERT_EQ(list.capacity(), capacityAfterAdding);

    for (int i = 0; i < N; ++i) {
        auto val = list.get(handles[i]);
        ASSERT_NE(val, nullptr);
        if(i % 2 == 0) {
            ASSERT_EQ(*val, N + i);
        } else{
            ASSERT_EQ(*val, i);
        }
    }
}

void RunSimultaneously(const int threadCount, const std::function<void(int)> func) {
    std::shared_mutex waitToStartMtx;
    std::vector<std::thread> threads;

    waitToStartMtx.lock();
    for (int i = 0; i < threadCount; ++i) {
        int iCopy = i;
        threads.emplace_back([&, iCopy] {
           waitToStartMtx.lock_shared();
           func(iCopy);
           waitToStartMtx.unlock_shared();
        });
    }
    waitToStartMtx.unlock();

    for (int i = 0; i < threadCount; ++i) {
        threads[i].join();
    }
}

TEST(FastRefList, ThreadSynchronizationTest) {
    FastRefList<int> list;
    
    const int N = 10000;
    const int threadsN = 8;

    const auto handles = new FastRefHandle[N * threadsN];
    RunSimultaneously(threadsN, [&](int i) {
        for(int j = 0; j < N; j++) {
            handles[i * N + j] = list.add(std::move(j));
        }
    });
    
    ASSERT_EQ(list.size(), N * threadsN);

    for (int i = 0; i < threadsN; ++i) {
        for (int j = 0; j < N; ++j) {
            const auto index = i * N + j;
            auto ptr = list.get(handles[index]);
            ASSERT_NE(ptr, nullptr);
            ASSERT_EQ(*ptr, j);   
        }
    }
    
    // Test mixed add / remove
    RunSimultaneously(threadsN, [&] (int i) {
        for (int j = 0; j < N; j += 6) {
            for (int k = j; k < j + 6 && k < N ; ++k) {
                list.remove(handles[i * N + k]);
            }

            for (int k = j; k < j + 6 && k < N ; ++k) {
                handles[i * N + k] = list.add(std::move(k));
            }
        }
    });

    ASSERT_EQ(list.size(), threadsN * N);

    for (int i = 0; i < threadsN; ++i) {
        for (int j = 0; j < N; ++j) {
            auto val = list.get(handles[i * N + j]);
            ASSERT_NE(val, nullptr);
            ASSERT_EQ(*val, j);
        }
    }
}

struct CustomHandleProxy {
private:
    FastRefList<int>& ref;
    FastRefHandle handle;

public:
    static CustomHandleProxy create(FastRefList<int>& listRef, int&& data) {
        return CustomHandleProxy(listRef, listRef.add(std::move(data)));
    }
    
    int* get() const {
        return ref.get(this->handle);
    }
    
    CustomHandleProxy(FastRefList<int>& listRef, const FastRefHandle newHandle) : ref(listRef), handle(newHandle) {}
};


TEST(FastRefList, CustomHandleProxy) {
    FastRefList<int> list;

    const auto handle = CustomHandleProxy::create(list, 5);
    const auto ret = handle.get();

    ASSERT_NE(ret, nullptr);
    ASSERT_EQ(*ret, 5);
}