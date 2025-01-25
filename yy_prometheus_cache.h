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

#include <mutex>

#include "yy_cpp/yy_flat_set.h"

#include "yy_prometheus_metric_data.h"

namespace yafiyogi::yy_prometheus {

class MetricDataCache final
{
  public:
    void Add(const MetricData & p_metric_data);
    void Add(const MetricDataVector & p_metric_data);

    template<typename Visitor>
    void Visit(Visitor && visitor)
    {
      std::unique_lock lck{m_cache_mtx};

      m_store.visit(std::forward<Visitor>(visitor));
    }

  private:
    using store_type = yy_data::flat_set<MetricData>;
    store_type m_store{};

    std::mutex m_cache_mtx{};
};

using MetricDataCachePtr = std::shared_ptr<MetricDataCache>;

} // namespace yafiyogi::yy_prometheus
