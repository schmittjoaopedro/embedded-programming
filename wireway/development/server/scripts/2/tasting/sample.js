var value = 0;

function setup() {
    this.getCmp('dig2').setValue(value);
}

function loop() {
    
    if(value === 0) value = 1;
    else value = 0;
    
    this.getCmp('dig2').setValue(value);
    this.delay(1000);
    
}