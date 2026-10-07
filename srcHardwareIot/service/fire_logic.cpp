#include "fire_logic.h"
#include "../config/config.h"
#include "../communication/mqtt.h"

FireStatus detectFire(const SensorData& data) {
    bool flameDetected = data.flameDetected;

    bool gasWarning = data.gasValue >= GAS_WARN_THRESHOLD;

    bool gasFire = data.gasValue >= GAS_FIRE_THRESHOLD;

    bool temperatureWarning = data.temperature >= TEMPERATURE_WARN_THRESHOLD;

    bool temperatureFire = data.temperature >= TEMPERATURE_FIRE_THRESHOLD;
    
    bool aiFire = cameraFire, aiSmoke = cameraSmoke;
    
    if((aiFire && temperatureFire) || 
        (aiFire && gasFire) || 
        (aiFire && flameDetected && 
        (gasWarning || temperatureWarning)) ||
        (flameDetected && temperatureFire) ||
        (flameDetected && gasFire) ||
        (temperatureFire && gasFire)
    ){
        return FIRE;
    }

    if(aiFire || aiSmoke || flameDetected || gasWarning || temperatureWarning){
        return WARNING;
    }
    
    return NORMAL;
}


const char* fireStatusToString(FireStatus status) {

    switch (status) {
        case NORMAL:
            return "NORMAL";

        case WARNING:
            return "WARNING";

        case FIRE:
            return "FIRE";

        default:
            return "UNKNOWN";
    }
}