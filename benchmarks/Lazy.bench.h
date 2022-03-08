#include "async_simple/coro/Lazy.h"
#include "benchmark/benchmark.h"

void async_simple_Lazy_chain(benchmark::State& state);
void async_simple_Lazy_collectAll(benchmark::State& state);
void RescheduleLazy_chain(benchmark::State& state);
void RescheduleLazy_collectAll(benchmark::State& state);
