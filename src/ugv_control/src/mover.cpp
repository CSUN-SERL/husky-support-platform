#include "UGVControl.h"
#include "Position.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "husky");
  
  UGVControl moveTester;
  ros::spin(); 
  return 0;
}