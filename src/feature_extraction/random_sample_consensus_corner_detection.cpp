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

#include "laser_object_tracker/feature_extraction/random_sample_consensus_corner_detection.hpp"

#include <pcl/io/pcd_io.h>

namespace laser_object_tracker {
namespace feature_extraction {

RandomSampleConsensusCornerDetection::RandomSampleConsensusCornerDetection(double distance_threshold,
                                                                           int max_iterations,
                                                                           double probability) :
    sample_consensus_(ModelType::Ptr(nullptr), 0.0) {
  sample_consensus_.setDistanceThreshold(distance_threshold);
  sample_consensus_.setMaxIterations(max_iterations);
  sample_consensus_.setProbability(probability);
}

bool RandomSampleConsensusCornerDetection::extractFeature(const data_types::LaserScanFragment& fragment,
                                                          Eigen::VectorXd& feature) {
  if (fragment.empty()) {
    throw std::invalid_argument("Passed fragment is empty.");
  }

  data_types::PointCloudType::ConstPtr point_cloud_ptr = fragment.pointCloud().makeShared();
  if (sample_consensus_.getSampleConsensusModel()) {
    sample_consensus_.getSampleConsensusModel()->setInputCloud(
        data_types::PointCloudType::ConstPtr(point_cloud_ptr));
  } else {
    sample_consensus_.setSampleConsensusModel(ModelType::Ptr(
        new ModelType(point_cloud_ptr, true)));
  }

  if (!sample_consensus_.computeModel()) {
    return false;
  }

  Eigen::VectorXf coefficients;
  sample_consensus_.getModelCoefficients(coefficients);

  Eigen::Hyperplane<double, 2> line_1 = Eigen::Hyperplane<double, 2>::Through(
      Eigen::Vector2d(coefficients(0),
                      coefficients(1)),
      Eigen::Vector2d(coefficients(0) + coefficients(2),
                      coefficients(1) + coefficients(3))),
      line_2 = Eigen::Hyperplane<double, 2>::Through(
      Eigen::Vector2d(coefficients(0),
                      coefficients(1)),
      Eigen::Vector2d(coefficients(0) - coefficients(3),
                      coefficients(1) + coefficients(2)));

  PointType min, max;
  pcl::getMinMax3D(*point_cloud_ptr, min, max);

  feature.resize(6);
  feature.template head<2>() = coefficients.template head<2>().cast<double>();
  feature.template segment<2>(2) = line_1.projection(Eigen::Vector2d(min.x, min.y));
  feature.template tail<2>() = line_2.projection(Eigen::Vector2d(max.x, max.y));

  return true;
}

double RandomSampleConsensusCornerDetection::getDistanceThreshold() {
  return sample_consensus_.getDistanceThreshold();
}

void RandomSampleConsensusCornerDetection::setDistanceThreshold(double distance_threshold) {
  sample_consensus_.setDistanceThreshold(distance_threshold);
}

int RandomSampleConsensusCornerDetection::getMaxIterations() {
  return sample_consensus_.getMaxIterations();
}

void RandomSampleConsensusCornerDetection::setMaxIterations(int max_iterations) {
  sample_consensus_.setMaxIterations(max_iterations);
}

double RandomSampleConsensusCornerDetection::getProbability() {
  return sample_consensus_.getProbability();
}

void RandomSampleConsensusCornerDetection::setProbability(double probability) {
  sample_consensus_.setProbability(probability);
}
}  // namespace feature_extraction
}  // namespace laser_object_tracker
