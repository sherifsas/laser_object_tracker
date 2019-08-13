/*********************************************************************
*
* BSD 3-Clause License
*
*  Copyright (c) 2019, Piotr Pokorski
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, this
*     list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3. Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from
*     this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include "laser_object_tracker/filtering/aggregate_segmented_filtering.hpp"

namespace laser_object_tracker {
namespace filtering {
AggregateSegmentedFiltering::AggregateSegmentedFiltering(
    std::vector<std::unique_ptr<BaseSegmentedFiltering>>&& filters) {
  for (auto& filter : filters) {
    if (filter->isTrivial()) {
      trivial_filters_.push_back(std::move(filter));
    } else {
      non_trivial_filters_.push_back(std::move(filter));
    }
  }
}

bool AggregateSegmentedFiltering::shouldFilter(const data_types::LaserScanFragment& fragment) const {
  return std::any_of(trivial_filters_.begin(),
                     trivial_filters_.end(),
                     [&fragment](const auto& filter) {return filter->shouldFilter(fragment);});
}

void AggregateSegmentedFiltering::filter(std::vector<data_types::LaserScanFragment>& fragments) const {
  for (auto& filter : non_trivial_filters_) {
    filter->filter(fragments);
  }

  BaseSegmentedFiltering::filter(fragments);
}

void AggregateSegmentedFiltering::add(std::unique_ptr<BaseSegmentedFiltering> filter) {
  if (filter->isTrivial()) {
    trivial_filters_.push_back(std::move(filter));
  } else {
    non_trivial_filters_.push_back(std::move(filter));
  }
}
}  // namespace filtering
}  // namespace laser_object_tracker
