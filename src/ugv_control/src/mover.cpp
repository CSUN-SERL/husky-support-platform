#include "UGVControl.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "husky");
  UGVControl moveTester;
  moveTester.crawl(10);
  moveTester.turn(10);
  ros::spin(); 
  return 0;
}