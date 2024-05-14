/*
 * Copyright (C) 2024 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <thread>
#include <future>

#include "platoon_control/platoon_control.hpp"

//Create publisher node to set initial pose and twist
class TestPublisher : rclcpp::Node
{
    public:
    TestPublisher() : Node ("test_node"){

        auto twist_pub = create_publisher<geometry_msgs::msg::TwistStamped>("vehicle/twist",1);
        geometry_msgs::msg::TwistStamped twist_msg;
        twist_msg.twist.linear.x = 0.0;

        twist_pub->publish(twist_msg);

        auto pose_pub = create_publisher<geometry_msgs::msg::PoseStamped>("current_pose", 1);
        geometry_msgs::msg::PoseStamped pose_msg;
        pose_msg.pose.position.x = 0.0;
        pose_msg.pose.position.y = 0.0;

        pose_pub->publish(pose_msg);
    }

};




TEST(PlatoonControlPluginTest, test2)
{
    rclcpp::NodeOptions options;
    auto worker_node = std::make_shared<platoon_control::PlatoonControlPlugin>(options);

    worker_node->configure();
    worker_node->activate();

    auto test_node = TestPublisher();

    carma_planning_msgs::msg::TrajectoryPlan tp;
    carma_planning_msgs::msg::TrajectoryPlanPoint point1;
    point1.x = 1.0;
    point1.y = 1.0;

    carma_planning_msgs::msg::TrajectoryPlanPoint point2;
    point2.x = 10.0;
    point2.y = 10.0;

    carma_planning_msgs::msg::TrajectoryPlanPoint point3;
    point3.x = 20.0;
    point3.y = 20.0;

    tp.trajectory_points = {point1, point2, point3};

    carma_planning_msgs::msg::TrajectoryPlanPoint out = worker_node->get_lookahead_trajectory_point(tp);
    EXPECT_EQ(out.x, 10.0);

}