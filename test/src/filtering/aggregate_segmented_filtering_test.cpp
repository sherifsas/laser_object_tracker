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

#include <gtest/gtest.h>

#include "laser_object_tracker/filtering/aggregate_segmented_filtering.hpp"

#include "test/utils.hpp"
#include "test/filtering/mocks.hpp"

TEST(AggregatedSegmentedFilteringTest, ShouldFilterTest) {
//  std::unique_ptr<test::FilterMock> mock_filter_1(new test::FilterMock()),
//                                    mock_filter_2(new test::FilterMock()),
//                                    mock_filter_3(new test::FilterMock());

  test::FilterMock mock;


//  EXPECT_CALL(*mock_filter_1, shouldFilter(testing::_))
//      .WillOnce(testing::Return(false))
//      .WillOnce(testing::Return(true))
//      .WillOnce(testing::Return(false))
//      .WillOnce(testing::Return(false))
//      .WillOnce(testing::Return(false));

//  EXPECT_CALL(*mock_filter_2, shouldFilter(testing::_))
//      .WillOnce(testing::Return(false))
//      .WillOnce(testing::Return(true))
//      .WillOnce(testing::Return(false))
//      .WillOnce(testing::Return(false));

//  EXPECT_CALL(*mock_filter_3, shouldFilter(testing::_))
//      .WillOnce(testing::Return(true))
//      .WillOnce(testing::Return(false));

//  std::vector<std::unique_ptr<laser_object_tracker::filtering::BaseSegmentedFiltering>> filters;
//  filters.push_back(std::move(mock_filter_1));
//  filters.push_back(std::move(mock_filter_2));

//  laser_object_tracker::filtering::AggregateSegmentedFiltering filter(std::move(filters));

//  laser_object_tracker::data_types::LaserScanFragment fragment;
//  EXPECT_FALSE(filter.shouldFilter(fragment));
//  EXPECT_TRUE(filter.shouldFilter(fragment));
//  EXPECT_TRUE(filter.shouldFilter(fragment));

//  filter.add(std::move(mock_filter_3));
//  EXPECT_TRUE(filter.shouldFilter(fragment));
//  EXPECT_FALSE(filter.shouldFilter(fragment));
}