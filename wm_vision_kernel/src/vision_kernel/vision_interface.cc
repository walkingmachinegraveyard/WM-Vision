/*
 * Copyright 2012-2013 Walking Machine
 *
 * Project: Walking Machine Sara robot 2012-2013
 * Package: wm_vision_kernel
 *
 * Creation date: 02/07/2013
 *
 * Programmer: Julien Côté
 *
 * Description: The vision interface was the interface between the wm_vision_kernel ans ROS.
 *
 */

#include "../../include/vision_kernel/vision_interface.h"

#include <ros/ros.h>

#include "../../include/vision_kernel/vision_parser.h"

/**
 * Creates the initial catalog map holding the paths to the trees
 * configuration files
 */
VisionInterface::VisionInterface() {
  // Parse catalog.info for the cfvf paths, store the info in path_map
  try {
    VisionParser::ParseCatalogCFVF(path_map_);
  } catch(const std::exception& e) {
      throw e;
  }
}

/**
 * The method used by the ros:Service when it is called
 *
 * @param request contains the parameters as defined in visionInterface.srv
 * @param response contains the return value as defined in visionInterface.srv
 * @return  True if succeeded, False if failed and won't send the Response
 */
bool VisionInterface::CallbackFlow(
    wm_vision_kernel::wm_vision_interface_flow::Request& request,
    wm_vision_kernel::wm_vision_interface_flow::Response& response) {

  float frequency = (request.frequency == 0 ? 30 : request.frequency);

  std::string flow_name;

  // Store request paramter into a std::pair
  std::pair<std::string, std::string> key(request.task_name,
                                          request.object_name);

  // Exit if the requested task isn't in catalog.info
  auto path_iterator = path_map_.find(key);
  if(path_iterator == path_map_.end()) {
    return false;
  } else {
    flow_name = path_iterator->second;
  }

	// Look within the tasks collection to see if the task already exists
	auto flow_iterator = flow_container_.find(key);
	if(flow_iterator != flow_container_.end()) {
    if(request.action == "stop") {
      flow_iterator->second->Stop();
      flow_container_.erase(flow_iterator);
    } else if(request.action == "start") {
      //task_iterator->second->Start();
    } else if(request.action == "set_frequency") {
      flow_iterator->second->set_wanted_frequency(frequency);
    } else {
      response.topic_name = "invalid Action name";
    }
  } else {
    CreateFlow(request.task_name, request.object_name, flow_name, frequency);
    response.topic_name = flow_name;
  }
	return true;
}

/**
 * Create a vision flow
 * @param id_task the task to execute. Refer to the enum for the names
 * @param id_object The object, person or gesture to be found
 * @param tree_name The name of the vision_tree to call
 */
void VisionInterface::CreateFlow(const std::string &task_name,
                                 const std::string &object_name,
                                 const std::string &flow_name,
                                 const float &frequency) {
  std::shared_ptr<VisionFlow> vision_flow(new VisionFlow(flow_name, frequency));
  ros::NodeHandle node_handle;
  std::string cfvf_path;

  if (!node_handle.getParamCached("cfvf_path",cfvf_path))  // Get rosparam cfvf_path
	  cfvf_path = "/home/escaladeur/wm_workspace/wm_sofware/src/wm_vision/config/cfvf";  //DO NOT COMMIT

  try {
    VisionParser::ParseVisionFlow(std::string(cfvf_path + flow_name + ".cfvf"),
                                  *vision_flow);
  } catch(const std::exception& e) {
    ROS_INFO("%s", e.what());
  }

  std::pair<std::string,std::string> key(task_name, object_name);
  flow_container_[key] = vision_flow;
  vision_flow->Start();
}
