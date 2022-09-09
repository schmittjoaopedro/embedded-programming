
function setup() {
    
    this.xbee("/dev/ttyUSB0").onReceiveData(function(data) {
        print(data);
    });
    this.xbee("/dev/ttyUSB0").addActuator("actuator", "0013A20040D591B5");
    
}


function loop() {
    
    this.delay(30000);
    this.xbee("/dev/ttyUSB0").sendActuatorData("actuator", "11");
    this.delay(30000);
    this.xbee("/dev/ttyUSB0").sendActuatorData("actuator", "00");
    
}