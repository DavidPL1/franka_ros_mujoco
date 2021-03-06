/*********************************************************************
 * Copyright 2017 Franka Emika GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Changes made for franka_mujoco:
 *  - namespace
 *********************************************************************/

#pragma once
#include <franka_mujoco/joint.h>
#include <hardware_interface/controller_info.h>
#include <hardware_interface/interface_resources.h>
#include <hardware_interface/internal/hardware_resource_manager.h>
#include <boost/optional.hpp>

namespace franka_mujoco {

/**
 * Can be used to check conrollers in franka_mujoco. It also can distinguish between gripper and arm controllers.
 */
class ControllerVerifier
{
public:
	/**
	 * Creates a ControllerVerifier object to check controllers for franka_mujoco
	 * @param joints map of joint names and joints including gripper joints
	 * @param arm_id prefix of the joints.
	 */
	ControllerVerifier(const std::map<std::string, std::shared_ptr<franka_mujoco::Joint>> &joints,
	                   const std::string &arm_id);

	/**
	 * Checks if a set of joint_names only contains the joints that are used for the arm
	 */
	bool areArmJoints(const std::set<std::string> &resources) const;

	/**
	 * Checks if a controller can be used in the franka_hw_mujoco package
	 */
	bool isValidController(const hardware_interface::ControllerInfo &controller) const;

	/**
	 * Checks if a set of joint_names only contains the joints that are used for the gripper
	 */
	bool areFingerJoints(const std::set<std::string> &resources) const;

	/**
	 * Checks if a controller wants to use the finger joints with the effort interface
	 */
	bool isClaimingGripperController(const hardware_interface::ControllerInfo &info) const;

	/**
	 * Checks if a controller that uses the joints of the arm (not gripper joints) claims a position, velocity or effort
	 * interface.
	 */
	bool isClaimingArmController(const hardware_interface::ControllerInfo &info) const;

	/**
	 * Returns the control method of a hardware interface
	 */
	static boost::optional<ControlMethod> determineControlMethod(const std::string &hardware_interface);

private:
	std::vector<std::string> joint_names_;
	std::string arm_id_;

	static bool hasControlMethodAndValidSize(const hardware_interface::InterfaceResources &resources);
};
} // namespace franka_mujoco
