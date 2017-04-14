#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H


#include <string>
#include <map>
#include <vector>
#include <list>

class CommandParser
{
	// Initialization 
public:
    
    CommandParser();
    ~CommandParser();
    void parse(std::string& command);
    
 private:
        std::string (CommandParser::*CMDPtr)();    
        std::map<std::string, std::string> Digit;
        std::map<std::string, std::string (CommandParser::*)()> CMD;
        
	std::string num;
        std::string vehicleName;
	std::string partialcmd;
	std::vector<std::string> command;
	std::vector<std::string> commandChain;
	std::vector<std::string> vehicleNum;
        

	int arg1;
      int arg2;
        
	bool checkVehicle;
	bool isInteger;
	bool vehicleCheck;
	bool numCount;
       
	void initialize();
        
       //Functions STARTS
        
        std::string arm();
        std::string disarm();
        std::string getFlightState();
        std::string setFlightModeStabilize();
        std::string setFlightModeLoiter();
        std::string setFlightModeLand();
        std::string setFlightModeAltitudeHold();
        std::string setFlightModePositionHold();
        std::string setFlightModeReturnToLaunch();
        std::string setFlightModeAuto();
        std::string setFlightModeOffBoard();
        std::string setAltitude();
        std::string stopMission();
        std::string pauseMission();
        std::string resumeMission();
        std::string setGroup();
        std::string deleteGroup();
        std::string stopPlay();
        std::string resumePlay();
        std::string pausePlay();
        std::string acceptAllQueries();
        std::string rejectAllQueries();

     
	std::string rejectQuery();

	std::string acceptQuery();

	std::string executePlay();

	std::string deleteAccessPoint();

	std::string setWayPoint();

	std::string scoutBuilding();
        
        std::string searchPatternA();
        std::string searchPatternB();
        std::string searchPatternC();
        
        //Functions ENDS

        bool checkForDigit(const std::string &s);

        void convertCmd(const std::string &input2);

};


#endif