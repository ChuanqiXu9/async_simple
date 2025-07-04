/*
 * Copyright (c) 2022, Alibaba Group Holding Limited;
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <mutex>
#include <thread>
#include "async_simple/coro/Lazy.h"
#include "async_simple/coro/SpinLock.h"
#include "async_simple/executors/SimpleExecutor.h"
#include "async_simple/test/unittest.h"

namespace async_simple {
namespace coro {

class SpinLockTest : public FUTURE_TESTBASE {
public:
    SpinLockTest() : _executor(2) {}
    void caseSetUp() override {}
    void caseTearDown() override {}

    executors::SimpleExecutor _executor;
};

TEST_F(SpinLockTest, testLockImmediately) {
    std::atomic<int> latch(5);
    SpinLock spin;
    auto data = 0;
    auto addOne = [&]() -> Lazy<> {
        auto scopeLock = co_await spin.coScopedLock();
        data++;
        latch--;
        co_return;
    };
    addOne().via(&_executor).start([](Try<void> var) {});
    addOne().via(&_executor).start([](Try<void> var) {});
    addOne().via(&_executor).start([](Try<void> var) {});
    addOne().via(&_executor).start([](Try<void> var) {});
    addOne().via(&_executor).start([](Try<void> var) {});
    while (latch) {
    }
    EXPECT_EQ(5, data);
}

TEST_F(SpinLockTest, testLockYield) {
    std::atomic<int> latch(5);
    executors::SimpleExecutor executor(1);
    SpinLock spin(128);
    auto data = 0;
    auto addOneForgetUnlock = [&]() -> Lazy<> {
        co_await spin.coLock();
        data++;
        latch--;
        co_return;
    };
    auto addOne = [&]() -> Lazy<> {
        auto scopeLock = co_await spin.coScopedLock();
        data++;
        latch--;
        co_return;
    };
    auto assertDataEqual = [&]() -> Lazy<> {
        EXPECT_EQ(1, data);
        spin.unlock();
        co_return;
    };
    addOneForgetUnlock().via(&executor).start([](auto) {});
    addOne().via(&executor).start([](auto) {});
    addOne().via(&executor).start([](auto) {});
    addOne().via(&executor).start([](auto) {});
    addOne().via(&executor).start([](auto) {});
    assertDataEqual().via(&executor).start([](auto) {});
    while (latch) {
    }
    EXPECT_EQ(5, data);
}

TEST_F(SpinLockTest, testSyncLock) {
    SpinLock spin;
    auto data = 0;

    std::function<void()> addOne = [&]() {
        spin.lock();
        data++;
        spin.unlock();
    };

    std::function<void()> subOne = [&]() {
        ScopedSpinLock scope_lock(spin);
        data--;
    };

    std::vector<std::thread> ts;
    for (auto i = 0; i < 100; i++) {
        ts.push_back(std::thread(addOne));
        ts.push_back(std::thread(subOne));
    }
    for (auto& t : ts) {
        t.join();
    }

    EXPECT_EQ(0, data);
}

TEST_F(SpinLockTest, testSpinLockCancel) {
    using namespace std::chrono_literals;
    executors::SimpleExecutor executor(1);
    SpinLock lock;
    std::unique_lock l(lock);
    auto test = [&executor](Lazy<void>&& lazy, bool ok, bool cancelFirst) {
        auto signal = async_simple::Signal::create();
        std::promise<void> p;
        if (cancelFirst) {
            signal->emits(SignalType::Terminate);
        }
        std::move(lazy)
            .setLazyLocal(signal.get())
            .via(&executor)
            .start([&p, ok](Try<void>&& result) {
                EXPECT_EQ(result.hasError(), !ok);
                p.set_value();
            });
        if (!cancelFirst) {
            std::this_thread::sleep_for(10ms);
            signal->emits(SignalType::Terminate);
        }
        p.get_future().wait();
    };
    for (int i = 0; i <= 1; ++i) {
        test([&]() -> Lazy<void> { co_await lock.coScopedLock(); }(), false, i);
        test(
            [&]() -> Lazy<void> {
                co_await lock.coLock();
                lock.unlock();
            }(),
            false, i);
        test(
            [&]() -> Lazy<void> {
                lock.tryLock();
                co_return;
            }(),
            true, i);
    }
}

}  // namespace coro
}  // namespace async_simple
