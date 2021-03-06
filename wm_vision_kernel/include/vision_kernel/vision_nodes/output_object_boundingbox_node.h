/*
 * Copyright 2012-2013 Walking Machine
 *
 * Project: Walking Machine Sara robot 2012-2013
 * Package: wm_vision
 * Node: vision_kernel
 *
 * Creation date: 02/26/2013
 *
 * Programmer: Julien Côté
 *
 * Description: Outputs Object boundingbox via topic
 *
 */

#ifndef WM_VISION_INCLUDE_VISION_KERNEL_VISION_NODES_OUTPUT_OBJECT_BOUNDINGBOX_NODE_H_
#define WM_VISION_INCLUDE_VISION_KERNEL_VISION_NODES_OUTPUT_OBJECT_BOUNDINGBOX_NODE_H_

#include <ros/ros.h>

#include "../vision_node.h"
#include "../vision_node_factory.h"

class OutputObjectBoundingboxNode : public VisionNode {
 public:
  OutputObjectBoundingboxNode() {};
  virtual ~OutputObjectBoundingboxNode();

  Data Function(InputData input_data);
  void Init();

 private:
  ros::Publisher publisher_;
  REGISTER_DEC_TYPE(OutputObjectBoundingboxNode);
};

REGISTER_DEF_TYPE(OutputObjectBoundingboxNode);

#endif  // WM_VISION_INCLUDE_VISION_KERNEL_VISION_NODES_OUTPUT_OBJECT_BOUNDINGBOX_NODE_H_
