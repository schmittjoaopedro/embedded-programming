var xbeePort = "/dev/ttyUSB0";
var ventilator = "0", fogger = "0";

function setup () {
    
    this.xbee(xbeePort);
    this.xbee(xbeePort).addActuator("estufa", "0013A20040D591B5");
    
    this.xbee(xbeePort).onReceiveData(function(data) {
        
        var rawData = data.split(";");
        
        this.getCmp("temperature").setValue(rawData[0]);
        this.getCmp("humidity").setValue(rawData[1]);
        this.getCmp("pressure").setValue(rawData[2]);
        this.getCmp("soilHumidity").setValue(rawData[3]);
        this.getCmp("rain").setValue(rawData[4]);
        
    }.bind(this));
    
    this.getCmp("ventilator").on(function(data) {
        ventilador = data + "";
        this.xbee(xbeePort).sendActuatorData("estufa", fogger + ventilador);
    }.bind(this));
    
    this.getCmp("fogger").on(function(data) {
        fogger = data + "";
        this.xbee(xbeePort).sendActuatorData("estufa", fogger + ventilador);
    }.bind(this));
    
}
function loop () { }