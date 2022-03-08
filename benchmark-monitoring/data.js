window.BENCHMARK_DATA = {
  "lastUpdate": 1646720559534,
  "repoUrl": "https://github.com/ChuanqiXu9/async_simple",
  "entries": {
    "C++ Benchmark": [
      {
        "commit": {
          "author": {
            "email": "68680648+ChuanqiXu9@users.noreply.github.com",
            "name": "Chuanqi Xu",
            "username": "ChuanqiXu9"
          },
          "committer": {
            "email": "68680648+ChuanqiXu9@users.noreply.github.com",
            "name": "Chuanqi Xu",
            "username": "ChuanqiXu9"
          },
          "distinct": true,
          "id": "54bd3c4c43b4163e00d64a9ac790689bee7ddb64",
          "message": "Enable Performance CI",
          "timestamp": "2022-03-08T13:52:45+08:00",
          "tree_id": "aff877f6ae5e21bf01111647305fbd7aaf52d95c",
          "url": "https://github.com/alibaba/async_simple/commit/54bd3c4c43b4163e00d64a9ac790689bee7ddb64"
        },
        "date": 1646718999611,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "async_simple_Lazy_chain",
            "value": 24355.384206787337,
            "unit": "ns/iter",
            "extra": "iterations: 29557\ncpu: 23774.682816253346 ns\nthreads: 1"
          },
          {
            "name": "async_simple_Lazy_collectAll",
            "value": 9914210.692307698,
            "unit": "ns/iter",
            "extra": "iterations: 65\ncpu: 9855347.692307692 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "yedeng.yd@linux.alibaba.com",
            "name": "Chuanqi Xu",
            "username": "ChuanqiXu9"
          },
          "committer": {
            "email": "yedeng.yd@linux.alibaba.com",
            "name": "Chuanqi Xu",
            "username": "ChuanqiXu9"
          },
          "distinct": true,
          "id": "de8c6a0b81d8bc74be0550506d5daee2c9177369",
          "message": "Split Performance CI",
          "timestamp": "2022-03-08T14:20:50+08:00",
          "tree_id": "7634b5a4015bb7be386ddc0a1533d04302cdc5ef",
          "url": "https://github.com/ChuanqiXu9/async_simple/commit/de8c6a0b81d8bc74be0550506d5daee2c9177369"
        },
        "date": 1646720558618,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "async_simple_Lazy_chain",
            "value": 20916.67684241998,
            "unit": "ns/iter",
            "extra": "iterations: 33380\ncpu: 20910.51527860995 ns\nthreads: 1"
          },
          {
            "name": "async_simple_Lazy_collectAll",
            "value": 9928800.936507734,
            "unit": "ns/iter",
            "extra": "iterations: 63\ncpu: 9928480.952380953 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}