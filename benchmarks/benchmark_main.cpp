#include "Future.bench.h"
#include "Lazy.bench.h"

BENCHMARK(Future_chain);
BENCHMARK(Future_collectAll);
BENCHMARK(async_simple_Lazy_chain);
BENCHMARK(async_simple_Lazy_collectAll);
BENCHMARK(RescheduleLazy_chain);
BENCHMARK(RescheduleLazy_collectAll);
BENCHMARK_MAIN();
