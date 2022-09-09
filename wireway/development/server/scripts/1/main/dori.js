var radioPort = 'COM9';

function setup() {
    
    this.radio(radioPort).begin('xbee');
    this.radio(radioPort).addActuator('aerador', '40B95211');
    this.radio(radioPort).addActuator('circuito', '40B95212');
    
    this.getCmp('aeradoras').on(function(data) {
        this.radio(radioPort).send('aerador', data);
    }.bind(this));
    
    this.getCmp('circuitoAgua').on(function(data) {
        this.radio(radioPort).send('circuito', data);
    }.bind(this));
    
    this.radio(radioPort).onData(function(packet) {
        var data = packet.split(';');
        var amonia = data[0] + '%';
        var acidoCarbonico = data[1] + '%';
        var gasSulfidrico = data[2] + '%';
        this.getCmp('amonia').setValue(amonia);
        this.getCmp('acidoCarbonico').setValue(acidoCarbonico);
        this.getCmp('gasSulfidrico').setValue(gasSulfidrico);
    }.bind(this));
    
}

function loop() {
    
}