//use the Dijkstra algorithm to drive the 2*3 car to find all the mission points
//the car will drive to the nearest mission point and then drive to the next mission point

class steelLazy_Copilot : public steelCopilot
{
public:
    steelLazy_Copilot(steelCar* car);
    ~steelLazy_Copilot();

    void update(float dt);
    void reset();

    void setMission(steelMission* mission);
    void setMissionPoint(int index);
};