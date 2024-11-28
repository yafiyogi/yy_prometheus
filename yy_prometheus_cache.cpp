/*

  MIT License

  Copyright (c) 2024 Yafiyogi

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#include <cstddef>

#include <chrono>

#if ( defined(__GNUC__) && __GNUC__ > 12 ) && ! defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnrvo"
#endif

#include "spdlog/spdlog.h"

#if ( defined(__GNUC__) && __GNUC__ > 12 ) && ! defined(__clang__)
#pragma GCC diagnostic pop
#endif

#include "yy_cpp/yy_flat_set.h"

#include "yy_prometheus_metric_data.h"
#include "yy_prometheus_cache.h"

namespace yafiyogi::yy_prometheus {

void MetricDataCache::Add(const MetricData & p_metric_data)
{
  std::unique_lock lck{m_cache_mtx};

  m_store.emplace_or_assign(p_metric_data);
}

void MetricDataCache::Add(const MetricDataVector & p_metric_data)
{
  for(auto & metric_data : p_metric_data)
  {
    Add(metric_data);
  }
}

} // namespace yafiyogi::yy_prometheus
