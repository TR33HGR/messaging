#include <future>

#define TEST_TIMEOUT_BEGIN std::promise<bool> promisedFinished; \
    auto futureResult = promisedFinished.get_future(); \
    std::thread([this](std::promise<bool>& finished) {

#define TEST_TIMEOUT_END(X)  finished.set_value(true); \
    }, std::ref(promisedFinished)).detach(); \
    EXPECT_TRUE(futureResult.wait_for(std::chrono::milliseconds(X)) != std::future_status::timeout);