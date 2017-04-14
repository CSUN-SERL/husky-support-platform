
#include <voice_recognition/CommandParser.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <unistd.h>
#include <iostream>
#include <string>
#include <lcar_msgs/lcar_msgs/ui_adapter.h>

#define ever ;;


//int main(int argc, char **argv)
//{
//    // TODO Auto-generated method stub
//    for(ever)
//    {
//
//        std::string input;
//        std::cout << "What is your command?" << std::endl;
//
//
//        std::getline(std::cin, input);
//
//        boost::to_upper(input);
//
//        CommandParser cmd;
//
//        cmd.parse(input);
//    }
//
//    return 0;
//}

CommandParser::CommandParser()
{
    this->initialize();

}



CommandParser::~CommandParser(){}

void CommandParser::parse(std::string& command)
{
    convertCmd(command);
//    boost::to_upper(command);


    vehicleCheck = false;
    numCount =false;
    arg1, arg2 = 0;

    for (int i = 0; i < commandChain.size();i++)
    {

        if (commandChain[i].compare("DRONE") == 0){

            vehicleName = "DRONE";
            vehicleCheck = true;
            vehicleNum.push_back((commandChain[i + 1]));
            i++;
        }
        else if (commandChain[i].compare("HUSKY") == 0) {

            vehicleName = "HUSKY";
            vehicleCheck = true;
            vehicleNum.push_back((commandChain[i + 1]));
            i++;

        }
        else
        {

            int j = 0;
            for (j = i;j < commandChain.size();j++)
            {

                if (checkForDigit(commandChain[j]) == false)
                {
                    vehicleCheck = true;

                    if (commandChain[j]!="BY"  && commandChain[j]!="DOT" && commandChain[j]!="POINT" )
                    {
                        partialcmd += commandChain[j] + " ";


                    }
                    else if (commandChain[j-1].compare("WAY") == 0)
                    {

                        partialcmd +=  commandChain[j] + " ";

                    }
                }


                //a vehicle is already called or command called so digits are not the vehicle number and are digits for the command
                else if (vehicleCheck == true)
                {

                    // if its a number and the first number given
                    if (checkForDigit(commandChain[j]) == true && numCount == false)
                    {

                        numCount = true;
                        arg1 = boost::lexical_cast<int>(commandChain[j]);
                    }
                    else
                    {
                        arg2 = boost::lexical_cast<int>(commandChain[j]);
                    }
                }

            }
            i = j;
        } //else

    } //for (int i = 0; i < commandChain.size();i++)



//    update();
    boost::algorithm::trim(partialcmd);
    if (!vehicleNum.empty())
    {


        std::cout << std::string("FOR ") << vehicleName << std::string(" VEHICLES: ") << std::endl;
        for (int i = 0; i < vehicleNum.size();i++)
        {
            //if cmd has it


                CMDPtr = CMD[partialcmd];

                std::cout << vehicleNum[i] << std::string(" - Command: ") << (this->*CMDPtr)() << std::endl;


        }
        vehicleNum.clear();
    }
    else
    {
        CMDPtr = CMD[partialcmd];

        std::cout << std::string("FOR CURRENT VEHICLE: ") << std::endl;


        std::cout << std::string("Command: ") << (this->*CMDPtr)()  << std::endl;

    }
}

void CommandParser::initialize()
{
	// TODO Auto-generated method stub
	Digit["ONE"] = "1";
	Digit["TWO"] = "2";
	Digit["THREE"] = "3";
	Digit["FOUR"] = "4";
	Digit["FIVE"] = "5";
	Digit["SIX"] = "6";
	Digit["SEVEN"] = "7";
	Digit["EIGHT"] = "8";
	Digit["NINE"] = "9";

	//functions starting with SET


	//VC1
	CMD["ARM"] = &CommandParser::arm;
	CMD["DISARM"] = &CommandParser::disarm;
	CMD["GET FLIGHT STATE"] = &CommandParser::getFlightState; //

	//VC2
	CMD["SET FLIGHT MODE STABILIZE"] = &CommandParser::setFlightModeStabilize;
	CMD["SET FLIGHT MODE LOITER"] = &CommandParser::setFlightModeLoiter;
	CMD["SET FLIGHT MODE LAND"] = &CommandParser::setFlightModeLand;
	CMD["SET FLIGHT MODE ALTITUDE HOLD"] = &CommandParser::setFlightModeAltitudeHold;
	CMD["SET FLIGHT MODE POSITION HOLD"] = &CommandParser::setFlightModePositionHold;
	CMD["SET FLIGHT MODE RETURN TO LAUNCH"] = &CommandParser::setFlightModeReturnToLaunch;
	CMD["SET FLIGHT MODE AUTO"] = &CommandParser::setFlightModeAuto;
	CMD["SET FLIGHT MODE OFF BOARD"] = &CommandParser::setFlightModeOffBoard;
	CMD["SET ALTITUDE"] = &CommandParser::setAltitude;

	//VC3

	CMD["STOP MISSION"] = &CommandParser::stopMission;
	CMD["PAUSE MISSION"] = &CommandParser::pauseMission;
	CMD["RESUME MISSION"] = &CommandParser::resumeMission;

	//VC4
        
        CMD["RUN SEARCH PATTERN A"]= &CommandParser::searchPatternA;
        CMD["RUN SEARCH PATTERN B"]= &CommandParser::searchPatternB;
        CMD["RUN SEARCH PATTERN C"]= &CommandParser::searchPatternC;

	//VC5
	CMD["SET GROUP"] = &CommandParser::setGroup;
	CMD["DELETE GROUP"] = &CommandParser::deleteGroup;

	//NVC1

	CMD["STOP PLAY"] = &CommandParser::stopPlay;
	CMD["RESUME PLAY"] = &CommandParser::resumePlay;
	CMD["PAUSE PLAY"] = &CommandParser::pausePlay;

	//NVC2

	CMD["ACCEPT ALL QUERIES"] = &CommandParser::acceptAllQueries;
	CMD["REJECT ALL QUERIES"] = &CommandParser::rejectAllQueries;

	//NVC3


        //formerly update function
        //VC1

	//VC2

	//VC3
	CMD["SCOUT BUILDING"] = &CommandParser::scoutBuilding;
	//VC4
	CMD["SET WAY POINT"] = &CommandParser::setWayPoint;
	//VC5

	//NVC1
	CMD["EXECUTE PLAY"] = &CommandParser::executePlay;
	//NVC2
	CMD["ACCEPT QUERY"] = &CommandParser::acceptQuery;
	CMD["REJECT QUERY"] = &CommandParser::rejectQuery;
	//NVC3
	CMD["DELETE ACCESS POINT"] = &CommandParser::deleteAccessPoint;
}

std::string CommandParser::arm()
{
    std::string txt = "[ARM]";
    emit gcs::UIAdapter::Instance()->Arm(1,true);
    return txt;
}
std::string CommandParser::disarm()
{
    std::string txt = "[DISARM]";
    emit gcs::UIAdapter::Instance()->Arm(1,false);

    return txt;
}std::string CommandParser::getFlightState()
{
    std::string txt = "[GET FLIGHT STATE]";
    //Command not available to emit yet 
    return txt;
}std::string CommandParser::setFlightModeStabilize()
{

    std::string txt = "[SET FLIGHT MODE STABILIZE]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"STABILIZED");
    return txt;
}std::string CommandParser::setFlightModeLoiter()
{
    std::string txt = "[SET FLIGHT MODE LOITER]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"AUTO.LOITER");    
    return txt;
}std::string CommandParser::setFlightModeLand()
{
    std::string txt = "[SET FLIGHT MODE LAND]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"AUTO.LAND");
    return txt;
}std::string CommandParser::setFlightModeAltitudeHold()
{
    std::string txt = "[SET FLIGHT MODE ALTITUDE HOLD]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"ALTCTL");
    return txt;
}std::string CommandParser::setFlightModePositionHold()
{
    std::string txt = "[SET FLIGHT MODE POSITION HOLD]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"POSCTL");
    return txt;
}std::string CommandParser::setFlightModeReturnToLaunch()
{
    std::string txt = "[SET FLIGHT MODE RETURN TO LAUNCH]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::setFlightModeAuto()
{
    std::string txt = "[SET FLIGHT MODE AUTO]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"AUTO");
    return txt;
}std::string CommandParser::setFlightModeOffBoard()
{
    std::string txt = "[SET FLIGHT MODE OFF BOARD]";
    emit gcs::UIAdapter::Instance()->SetMode(1,"OFFBOARD");
    return txt;
}std::string CommandParser::setAltitude()
{
    std::string txt = "[SET ALTITUDE]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::stopMission()
{
    std::string txt = "[STOP MISSION]";
    emit gcs::UIAdapter::Instance()->CancelMission(1);
    return txt;
}std::string CommandParser::pauseMission()
{
    std::string txt = "[PAUSE MISSION]";
    emit gcs::UIAdapter::Instance()->PauseMission(1);
    return txt;
}std::string CommandParser::resumeMission()
{
    std::string txt = "[RESUME MISSION]";
    emit gcs::UIAdapter::Instance()->ResumeMission(1);
    return txt;
}std::string CommandParser::setGroup()
{
    std::string txt = "[SET GROUP]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::deleteGroup()
{
    std::string txt = "[DELETE GROUP]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::stopPlay()
{
    std::string txt = "[STOP PLAY]";
    emit gcs::UIAdapter::Instance()->CancelPlay();
    return txt;
}std::string CommandParser::resumePlay()
{
    std::string txt = "[RESUME PLAY]";
    emit gcs::UIAdapter::Instance()->ResumePlay();
    return txt;
}std::string CommandParser::pausePlay()
{
    std::string txt = "[PAUSE PLAY]";
    emit gcs::UIAdapter::Instance()->PausePlay();
    return txt;
}std::string CommandParser::acceptAllQueries()
{
    std::string txt = "[ACCEPT ALL QUERIES]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::rejectAllQueries()
{
    std::string txt = "[REJECT ALL QUERIES]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::searchPatternA()
{
    std::string txt = "[RUN SEARCH PATTERN A ]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::searchPatternB()
{
    std::string txt = "[RUN SEARCH PATTERN B ]";
    //Command not available to emit yet
    return txt;
}std::string CommandParser::searchPatternC()
{
    std::string txt = "[RUN SEARCH PATTERN C ]";
    //Command not available to emit yet
    return txt;
}


std::string CommandParser::rejectQuery()
{
   // TODO Auto-generated method stub
        std::string txt = "[REJECT QUERY FOR " + boost::lexical_cast<std::string>(arg1) + " ]";
        //Command not available to emit yet
	return txt;
}

std::string CommandParser::acceptQuery()
{
// TODO Auto-generated method stub

	std::string txt = "[ACCEPT QUERY FOR " + boost::lexical_cast<std::string>(arg1) + " ]";
        //Command not available to emit yet
	 return txt;
}

std::string CommandParser::executePlay()
{
// TODO Auto-generated method stub
	std::string txt = "[EXECUTE PLAY FOR " + boost::lexical_cast<std::string>(arg1) +" ]";
         emit gcs::UIAdapter::Instance()->ExecutePlay(arg1);
	 return txt;
}

std::string CommandParser::deleteAccessPoint()
{
// TODO Auto-generated method stub
	std::string txt = "[DELETE ACCESS POINT FOR " + boost::lexical_cast<std::string>(arg1) + " ]";
        //Command not available to emit yet
	 return txt;
}

std::string CommandParser::setWayPoint()
{
// TODO Auto-generated method stub

        std::string txt = "[SET WAY POINT FOR LAT: " + boost::lexical_cast<std::string>(arg1) + " AND LNG: " + boost::lexical_cast<std::string>(arg2) + " ]";
        emit gcs::UIAdapter::Instance()->SetWayPoint(1,arg1,arg2,0);
        return txt;
}

std::string CommandParser::scoutBuilding()
{
// TODO Auto-generated method stub

	std::string txt = "[SCOUT BUILDING FOR " + boost::lexical_cast<std::string>(arg1) + " ]";
        emit gcs::UIAdapter::Instance()->ScoutBuilding(1,arg1);
        return txt;
}

bool CommandParser::checkForDigit(const std::string &s)
{
    bool validInteger = false;
    if(s.size()==0) return false;
    for(int i=0; i<s.size(); i++) {
        if((s[i]>='0' && s[i]<='9')==false) {
            return false;
        }
    }
    return true;
}

//Converts string into an Array of strings and letter digits into one number
void CommandParser::convertCmd(const std::string& input)
{

   using namespace boost::algorithm;
   split(command, input, is_any_of(" "));

   for (int i = 0; i < command.size(); i++)
    {
        if (Digit.find(command[i]) != Digit.end())
        {
                num = Digit[command[i]];
                int j = i + 1;
                while (j < command.size() && Digit.find(command[j]) != Digit.end())
                {
                        num += Digit[command[j]];
                        j++;
                }
                commandChain.push_back(num);
                i = j - 1;
        }
        else
        {
                commandChain.push_back(boost::to_upper_copy(command[i]));
        }


   }
}
