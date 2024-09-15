
let lastRequestTime = 0;
const skipTime = 50;
var stoped = false;

var m1 = document.getElementById('m1');
var m2 = document.getElementById('m2');
var m3 = document.getElementById('m3');
var m4 = document.getElementById('m4');

var s1 = document.getElementById('s1');
var s2 = document.getElementById('s2');
var s3 = document.getElementById('s3');
var s4 = document.getElementById('s4');

var joy = new JoyStick('joystick',{
    height : 200,
    width : 200,
    internalFillColor  : '#fff',
    internalLineWidth  : 5,
    internalStrokeColor  : '#ddc9c9',
    externalLineWidth  : 5,
    externalStrokeColor  : '#fff'
},function(data){
    data.x= Number(data.x);
    data.y = Number(data.y);

        if(data.x == 0 && data.y == 0){
            
            handleData(data);
            return;
        }

    skipper(() => {
        console.log(`${data.cardinalDirection} | X:${data.xPosition} | Y:${data.yPosition} | x:${data.x} | y:${data.y}`);
        handleData(data);
      });

    
});

function skipper(callback) {
    const currentTime = Date.now();
    if (currentTime - lastRequestTime >= skipTime) {
      lastRequestTime = currentTime;
      callback();
    }
  }

function mapRange(value, inMin, inMax, outMin, outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
  }

function handleData(data){
    if(data.y > 0){
        controlAllMotors('forward');
        setAllMotorsSpeed(mapRange(Math.abs(data.y),0,100,0,255));
        stoped = false;
    }else if(data.y < 0){
        stoped = false;
        controlAllMotors('backward');
        setAllMotorsSpeed(mapRange(Math.abs(data.y),0,100,0,255));
    }
    

    if (data.x > 0) {
        let degree = mapRange(data.x, 0, 100, 90, 180); 
        controlAllServos(degree);
    } else if (data.x < 0) {
        let degree = mapRange(data.x, -100, 0, 0, 90); 
        controlAllServos(degree);
    }
    
    if(!stoped && data.y == 0){
        controlAllMotors('stop');
        stoped = true;
    }
}

function controlAllServos(degree){
    if (s1.checked) {
        fetch(`/s1/direction?angle=${degree}`);
    }
    if (s2.checked) {
        fetch(`/s2/direction?angle=${degree}`);
    }
    if (s3.checked) {
        fetch(`/s3/direction?angle=${degree}`);
    }
    if (s4.checked) {
        fetch(`/s4/direction?angle=${degree}`);
    }
}

function controlAllMotors(action) {
    if(m1.checked){
        fetch(`/m1/direction/${action}`);
    }
  
   if(m2.checked){
    fetch(`/m2/direction/${action}`);
   }
    if(m3.checked){
        fetch(`/m3/direction/${action}`);
    }
    if(m4.checked){
        fetch(`/m4/direction/${action}`);
    }
}
function setAllMotorsSpeed(speed) {
    if (m1.checked) {
        fetch(`/m1/speed?speed=${speed}`);
    }
    if (m2.checked) {
        fetch(`/m2/speed?speed=${speed}`);
    }
    if (m3.checked) {
        fetch(`/m3/speed?speed=${speed}`);
    }
    if (m4.checked) {
        fetch(`/m4/speed?speed=${speed}`);
    }
}

function controlMotor(motor, action) {
    fetch(`/m${motor}/direction/${action}`);
}
function setMotorSpeed(motor) {
    const speed = document.getElementById(`speed${motor}`).value;
    fetch(`/m${motor}/speed?speed=${speed}`);
}

