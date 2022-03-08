#include "async_simple/Future.h"
#include "benchmark/benchmark.h"

void Future_chain(benchmark::State& state);
void Future_collectAll(benchmark::State& state);
