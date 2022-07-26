/*
 * Copyright 1996-2022 Cyberbotics Ltd.
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
 */

#include <stdio.h>
#include <stdlib.h>

#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>

static int time_step;

static void step() {
  if (wb_robot_step(time_step) == -1) {
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}

static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do
    step();
  while (start_time + sec > wb_robot_get_time());
}


int main(int argc, char **argv) {
  wb_robot_init();

  time_step = (int)wb_robot_get_basic_time_step();
  wb_keyboard_enable(time_step);

  WbDeviceTag motors[7];
  WbDeviceTag gripper[3];
  motors[1] = wb_robot_get_device("joint_1");
  motors[2] = wb_robot_get_device("joint_2");
  motors[3] = wb_robot_get_device("joint_3");
  motors[4] = wb_robot_get_device("joint_4");
  motors[5] = wb_robot_get_device("joint_5");
  motors[6] = wb_robot_get_device("joint_6");
  gripper[1] = wb_robot_get_device("joint_base_to_jaw_1");
  gripper[2] = wb_robot_get_device("joint_base_to_jaw_2");

  // set the motor velocity
  // first we make sure that every joint is at its initial position
  wb_motor_set_position(motors[1], 0.0);
  wb_motor_set_position(motors[2], 0.0);
  wb_motor_set_position(motors[3], 0.0);
  wb_motor_set_position(motors[4], 0.0);
  wb_motor_set_position(motors[5], 0.0);
  wb_motor_set_position(motors[6], 0.0);
  wb_motor_set_position(gripper[1], 0.0);
  wb_motor_set_position(gripper[2], 0.0);

  // set the motors speed. Here we set it to 1 radian/second
  wb_motor_set_velocity(motors[1], 1.0);
  wb_motor_set_velocity(motors[2], 1.0);
  wb_motor_set_velocity(motors[3], 1.0);
  wb_motor_set_velocity(motors[4], 1.0);
  wb_motor_set_velocity(motors[5], 1.0);
  wb_motor_set_velocity(motors[6], 1.0);
  wb_motor_set_velocity(gripper[1], 1.0);
  wb_motor_set_velocity(gripper[2], 1.0);

  wb_motor_set_velocity(motors[1], 0.5);
  wb_motor_set_velocity(motors[2], 0.5);
  wb_motor_set_velocity(motors[3], 0.5);

  wb_motor_set_position(motors[1], 1.5);
  wb_motor_set_position(motors[2], 0.70);
  wb_motor_set_position(gripper[1], 0.01);
  wb_motor_set_position(gripper[2], 0.01);
  passive_wait(4.2);
  wb_motor_set_position(motors[3], 0.5);
  passive_wait(1.2);
  wb_motor_set_position(gripper[1], 0.0);
  wb_motor_set_position(gripper[2], 0.0);
  passive_wait(1.5);
  wb_motor_set_position(motors[3], 0.3);
  passive_wait(1.2);
  wb_motor_set_position(motors[1], 0.0);
  passive_wait(5.0);
  wb_motor_set_position(motors[3], 0.5);
  passive_wait(0.5);
  wb_motor_set_position(gripper[1], 0.01);
  wb_motor_set_position(gripper[2], 0.01);
  passive_wait(0.5);
  wb_motor_set_position(motors[2], 0.0);
  wb_motor_set_position(motors[3], 0.0);
  
  wb_robot_cleanup();
  return 0;
}