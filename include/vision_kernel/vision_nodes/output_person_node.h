/*
 * Copyright 2012-2013 Walking Machine
 *
 * Project: Walking Machine Sara robot 2012-2013
 * Package: wm_vision
 * Node: wm_visionKernel
 *
 * Creation date: 02/26/2013
 *
 * Programmer: Julien Côté
 *
 * Description: Outputs person information via topic
 *
 */

#ifndef OUTPUT_PERSON_NODE_H_
#define OUTPUT_PERSON_NODE_H_

#include <ros/publisher.h>
#include "../data.h"
#include "../vision_node.h"
#include "../vision_node_factory.h"

class OutputPersonNode : public VisionNode {
 public:
  OutputPersonNode();
  virtual ~OutputPersonNode();

  Data Function(InputData input_data);
  void Init();

 private:
  ros::Publisher publisher_;
  REGISTER_DEC_TYPE(OutputPersonNode);
};

  REGISTER_DEF_TYPE(OutputPersonNode);

#endif /* OUTPUT_PERSON_NODE_H_ */
